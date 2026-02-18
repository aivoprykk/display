#ifndef D09B5E31_D09E_4ABC_A9C4_88C5EF43B2E7
#define D09B5E31_D09E_4ABC_A9C4_88C5EF43B2E7

#define EMPTY_VS 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
#define EMPTY_GROUP 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

#define GRP_C(mode) mode, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

#define KEEP_BIT 0x22 // no keep to prevent gray accumulation
/// DISP_UPDATE_CTRL, GATE_DRIVING_VOLTAGE, SRC_DRIVING_VOLTAGES[3], VCOM_REG 
#define OTHER_0(mode) mode, 0x17, 0x41, 0x00, 0x32, 0x20
#define OTHER_1(mode) mode, 0x17, 0x41, 0x00, 0x32, 0x36

#define LUT0 0x80, 0x48, 0x40
#define LUT1 0x40, 0x48, 0x80  /* This is the WEAK white pattern */
#define LUT2 0x80, 0x48, 0x40
#define LUT3 0x40, 0x48, 0x80
#define LUTE 0x00, 0x00, 0x00

#define GRP_F0 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
#define GRP_F1 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
#define GRP_F2 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

#define GRP_F10 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
#define GRP_F11 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
#define GRP_F12 0x0a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

#define VSC \
        LUT0, EMPTY_VS, \
        LUT1, EMPTY_VS, \
        LUT2, EMPTY_VS, \
        LUT3, EMPTY_VS, \
        LUTE, EMPTY_VS

#define VS1 \
        0x80, 0x4A, 0x40, EMPTY_VS, \
        0x40, 0x4A, 0x80, EMPTY_VS, \
        0x80, 0x4A, 0x40, EMPTY_VS, \
        0x40, 0x4A, 0x80, EMPTY_VS, \
        LUTE, EMPTY_VS

#define VS2 \
        0x00, 0x40, 0x00, EMPTY_VS, \
        0x80, 0x80, 0x00, EMPTY_VS, \
        0x40, 0x40, 0x00, EMPTY_VS, \
        0x00, 0x80, 0x00, EMPTY_VS, \
        LUTE, EMPTY_VS

#define GRP_FULL_0_2(time, mode) \
        0x0a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
        0x0a, 0x02, 0x00, 0x0a, 0x02, 0x00, time, \
        GRP_C(mode)

#define GRP_3_11 \
        /* Timing - Group 3~11: all empty */ \
        EMPTY_GROUP, EMPTY_GROUP, EMPTY_GROUP, EMPTY_GROUP, \
        EMPTY_GROUP, EMPTY_GROUP, EMPTY_GROUP, EMPTY_GROUP, EMPTY_GROUP
#define GRP_2_11(mode) GRP_C(mode), GRP_3_11

#define GRP_FULL_0(time, mode) GRP_FULL_0_2(time, mode), GRP_3_11

#define PHASE_CTRLC 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x00, 0x00, 0x00
#define PHASE_CTRL1 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x00, 0x00, 0x00
#define PHASE_CTRL0 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

#define SSD1680_WAVESHARE_2IN13_V2_LUT_FULL_REFRESH_0 ((const uint8_t[]) { \
        VSC, \
        GRP_FULL_0(0x01, 0x0a), \
        PHASE_CTRLC, \
        OTHER_0(KEEP_BIT) \
})

// 0x00 ~ 0xff   blink 1 time ~ 256 times to refresh
#define SSD1680_WAVESHARE_2IN13_V2_LUT_FULL_REFRESH_1 ((const uint8_t[]) { \
        VS1, \
        GRP_FULL_0(0x01, 0x0a), \
        PHASE_CTRLC, \
        OTHER_1(KEEP_BIT) \
})

// toimib, kiire 62.3108ms DEPG0213BN, 71.3116ms GDEY0213B74 partial

#define LUT_FAST_REFRESH_0 ((const uint8_t[]) { \
        VSC, \
        GRP_F0, \
        GRP_F1, \
        GRP_F2, \
        GRP_3_11, \
        PHASE_CTRLC, \
        OTHER_0(KEEP_BIT) \
})

// toimib, aeglasem 0.9s partial
// toimib, 86.3077ms partial 
#define SSD1680_WAVESHARE_2IN13_V2_LUT_FAST_REFRESH_1 ((const uint8_t[]) { \
        VS2, \
        GRP_C(0x08), \
        GRP_C(0x1), \
        GRP_2_11(0x1), \
        PHASE_CTRLC, \
        OTHER_1(KEEP_BIT) \
})

#define PARTIAL_UPDATE_LUT_SIZE 159

#endif /* D09B5E31_D09E_4ABC_A9C4_88C5EF43B2E7 */
