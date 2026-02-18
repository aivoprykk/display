#include "display_private.h"
#include <string.h>

#define CONFIG_USE_CUSTOM_LUT 1
#if defined(CONFIG_USE_CUSTOM_LUT)
#include "ssd168x_waveshare_lut.h"
#ifdef CONFIG_SSD168X_PANEL_SSD1681
static const uint8_t lut_base_25c[] = _1681_LUT_FAST_REFRESH_KEEP;
static const uint8_t lut_base_25c_full[] = _1681_LUT_FULL_REFRESH;
#else
#include "ssd1680_waveshare_2in13_lut.h"
static const uint8_t lut_base_25c[] = _1680_LUT_FAST_REFRESH_0;
static const uint8_t lut_base_25c_full[] = _1680_LUT_FULL_REFRESH_1;
#endif
size_t lut_base_25c_size = lengthof(lut_base_25c);
size_t lut_base_25c_full_size = lengthof(lut_base_25c_full);
#endif


// Temperature compensation offsets structure
typedef struct {
    int8_t temp;            // Temperature in °C
    int8_t vcom_offset;      // VCOM voltage adjustment
    int8_t gate_offset;      // Gate voltage adjustment
    uint8_t phase_mult;      // Phase timing multiplier
    bool   extra_cycle;      // Add extra refresh cycle
} temp_comp_t;

// LUT mode enumeration
typedef enum {
    LUT_MODE_FAST_REFRESH,
    LUT_MODE_FULL_REFRESH
} lut_mode_t;

// Temperature compensation table
const temp_comp_t temp_comp_table[] = {
    // Temp (°C), vcom, gate, phase_mult, extra_cycle
    { -10,   +12,   +8,   120, true  },  // Very cold
    {   0,    +8,   +6,   110, true  },  // Cold
    {  10,    +4,   +3,   105, false },  // Cool
    {  20,    +2,   +1,   102, false },  // Mild
    {  25,     0,    0,   100, false },  // Room temp (reference)
    {  30,    -2,   -1,    98, false },  // Warm
    {  40,    -4,   -3,    95, false },  // Hot
    {  50,    -8,   -6,    90, true  },  // Very hot
};

#define TEMP_COMP_COUNT (sizeof(temp_comp_table) / sizeof(temp_comp_t))

// Compensated LUT structure
typedef struct {
    uint8_t lut[159];        // The compensated LUT data
    bool extra_cycle;        // Whether to perform extra refresh cycle
} compensated_lut_t;

// Static buffer for the current compensated LUT
static compensated_lut_t current_lut;
static bool lut_initialized = false;
static lut_mode_t current_mode = LUT_MODE_FAST_REFRESH;

// Initialize the LUT generator with base LUT
void init_lut_generator(lut_mode_t mode) {
    if (!lut_initialized || mode != current_mode) {
        const uint8_t *base_lut;
        if (mode == LUT_MODE_FULL_REFRESH) {
            base_lut = lut_base_25c_full;
        } else {
            base_lut = lut_base_25c;
        }
        memcpy(current_lut.lut, base_lut, sizeof(current_lut.lut));
        current_lut.extra_cycle = false;
        current_mode = mode;
        lut_initialized = true;
    }
}
uint8_t apply_offset(uint8_t base, int8_t offset);
temp_comp_t get_compensation_values(float temp);

// Generate temperature-compensated LUT
compensated_lut_t* generate_temp_compensated_lut(float temperature, lut_mode_t mode) {
    if (!lut_initialized || mode != current_mode) {
        init_lut_generator(mode);
    }

    temp_comp_t comp = get_compensation_values(temperature);

    current_lut.extra_cycle = comp.extra_cycle;

    // Apply compensation to each phase (first 153 bytes)
    for (int i = 0; i < 153; i++) {
        uint8_t value = current_lut.lut[i];

        // Only compensate voltage/timing bytes (not control bytes)
        if (i % 7 < 3) {  // First 3 bytes of each 7-byte group are voltages
            // Apply voltage compensation
            if (i % 7 == 0) {  // VCOM
                value = apply_offset(value, comp.vcom_offset);
            } else {  // Gate voltages
                value = apply_offset(value, comp.gate_offset);
            }

            // Apply timing compensation
            if (i % 7 >= 1 && i % 7 <= 2) {
                value = (value * comp.phase_mult) / 100;
            }
        }

        current_lut.lut[i] = value;
    }
    // Apply compensation to control registers (bytes 153-158)
    // 153: DISP_UPDATE_CTRL
    current_lut.lut[153] = apply_offset(current_lut.lut[153], comp.gate_offset);
    // 154: Gate driving voltage
    current_lut.lut[154] = apply_offset(current_lut.lut[154], comp.gate_offset);
    // 155-157: Source driving voltages
    for (int i = 155; i <= 157; i++) {
        current_lut.lut[i] = apply_offset(current_lut.lut[i], comp.gate_offset);  // Assuming source uses same as gate
    }
    // 158: VCOM register
    current_lut.lut[158] = apply_offset(current_lut.lut[158], comp.vcom_offset);

    return &current_lut;
}

int16_t linear_interpolate(int16_t a, int16_t b, float ratio) {
    return a + (int16_t)((b - a) * ratio + 0.5f);
}

uint8_t apply_offset(uint8_t base, int8_t offset) {
    int16_t result = base + offset;
    if (result < 0x00) return 0x00;
    if (result > 0xFF) return 0xFF;
    return (uint8_t)result;
}

temp_comp_t get_compensation_values(float temp) {
    // Clamp temperature to table range
    if (temp <= temp_comp_table[0].temp) {
        return temp_comp_table[0];
    }
    if (temp >= temp_comp_table[TEMP_COMP_COUNT - 1].temp) {
        return temp_comp_table[TEMP_COMP_COUNT - 1];
    }

    // Find the two closest temperature points
    int lower_idx = 0;
    for (int i = 0; i < TEMP_COMP_COUNT - 1; i++) {
        if (temp >= temp_comp_table[i].temp && 
            temp <= temp_comp_table[i + 1].temp) {
            lower_idx = i;
            break;
        }
    }
    int upper_idx = lower_idx + 1;

    // Linear interpolation between temperature points
    temp_comp_t result;
    float ratio = (temp - temp_comp_table[lower_idx].temp) / 
                  (temp_comp_table[upper_idx].temp - temp_comp_table[lower_idx].temp);

    result.vcom_offset = linear_interpolate(
        temp_comp_table[lower_idx].vcom_offset,
        temp_comp_table[upper_idx].vcom_offset,
        ratio
    );

    result.gate_offset = linear_interpolate(
        temp_comp_table[lower_idx].gate_offset,
        temp_comp_table[upper_idx].gate_offset,
        ratio
    );

    result.phase_mult = (uint8_t)linear_interpolate(
        (int16_t)temp_comp_table[lower_idx].phase_mult,
        (int16_t)temp_comp_table[upper_idx].phase_mult,
        ratio
    );

    result.extra_cycle = (temp < 15 || temp > 35) ? true : false;

    return result;
}
