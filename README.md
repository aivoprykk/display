# GPS Logger Display Component

A comprehensive display management system for ESP32-based GPS loggers, supporting multiple display types including e-paper, LCD, and AMOLED displays with LVGL-based UI rendering and power-optimized refresh modes.

## Features

### Display Type Support
- **E-Paper Displays (SSD168x)**: Low-power e-paper displays with partial, fast, and full refresh modes
- **LCD Displays (ST7789)**: Color LCD displays for real-time updates
- **AMOLED Displays (RM67162)**: High-resolution AMOLED displays with QSPI support
- **QEMU Emulation**: Virtual display for development and testing

### Power Management
- **E-Paper Optimized**: Intelligent refresh scheduling to minimize power consumption
- **Task Management**: Background display task with pause/resume capabilities
- **Refresh Modes**: Full, fast, and partial refresh options for e-paper displays
- **Power Control**: Hardware power management for backlight and display power

### UI Framework Integration
- **LVGL Support**: Lightweight Vector Graphics Library for rich UI components
- **Event System**: ESP Event framework integration for UI state management
- **Rotation Support**: Display rotation configuration (0°, 90°, 180°, 270°)
- **Timer-Based Updates**: Periodic UI refresh with configurable intervals

### Hardware Abstraction
- **SPI Interface**: Configurable SPI host and bus settings
- **GPIO Configuration**: Flexible pin mapping for different hardware variants
- **Multiple SPI Modes**: Support for regular SPI, QSPI, and OSPI for high-speed displays

## Supported Hardware

### E-Paper Displays
- **SSD1680**: 2.13" Waveshare e-paper display
- **SSD1681**: 1.54" Waveshare e-paper display
- **Partial Refresh**: Optimized for low-power text updates
- **LUT Tables**: Custom lookup tables for optimal refresh performance

### LCD Displays
- **ST7789**: 240x320 RGB LCD with parallel RGB interface
- **Backlight Control**: PWM backlight management
- **High Refresh Rate**: Real-time display updates

### AMOLED Displays
- **RM67162**: High-resolution AMOLED with QSPI interface
- **Quad SPI**: 4-lane SPI for maximum bandwidth
- **TE Synchronization**: Tearing effect signal support

## Installation

### ESP-IDF Integration
Add to your `main/CMakeLists.txt`:
```cmake
idf_component_register(SRCS "main.c"
                      INCLUDE_DIRS "."
                      REQUIRES display lvgl)
```

### PlatformIO
Add to your `platformio.ini`:
```ini
[env]
lib_deps =
    https://github.com/aivoprykk/esp-gps-logger.git#components/display
    lvgl/lvgl@^8.3.0
```

## Configuration

### Kconfig Options
Configure via `idf.py menuconfig` or PlatformIO:

- **DISPLAY_ENABLED**: Enable/disable display module
- **DISPLAY_USE_LVGL**: Enable LVGL graphics library
- **DISPLAY_TASK_STACK_SIZE**: Display task stack size (default 5632/3840)
- **SPI Configuration**: Host selection (SPI1/SPI2/SPI3) and pin assignments
- **Display-Specific Settings**: GPIO pins for power, backlight, reset, etc.

### Hardware-Specific Configuration
The component auto-detects display type based on board configuration:
- **LilyGO T-Display S3**: ST7789 LCD
- **LilyGO T-Display S3 AMOLED**: RM67162 AMOLED
- **LilyGO T5**: SSD168x e-paper
- **QEMU**: Virtual display for testing

## Usage

### Basic Initialization
```c
#include "display.h"

// Initialize display with operations structure
static display_op_t display_ops = {
    .screen_cb = screen_update_callback,
    .ui_init = ui_initialize,
    .ui_deinit = ui_deinitialize
};

display_t *display = display_init(NULL, &display_ops);
if (!display) {
    ESP_LOGE(TAG, "Failed to initialize display");
    return;
}

// Start display task
display_task_start();
```

### E-Paper Display Management
```c
// Request different refresh types
display_request_full_refresh(false);    // Full refresh
display_request_fast_refresh();         // Fast refresh
display_request_partial_refresh();      // Partial refresh

// Task control for power management
display_task_pause();                   // Pause display updates
display_task_resume();                  // Resume updates
display_task_resume_for_times(5, 100, 5000, false); // Resume for 5 updates
```

### UI Event Handling
```c
// Register for UI events
esp_event_handler_register(UI_EVENT, ESP_EVENT_ANY_ID, ui_event_handler, NULL);

static void ui_event_handler(void* arg, esp_event_base_t event_base,
                              int32_t event_id, void* event_data) {
    switch (event_id) {
        case UI_EVENT_FLUSH_START:
            ESP_LOGI(TAG, "Display flush started");
            break;
        case UI_EVENT_FLUSH_DONE:
            ESP_LOGI(TAG, "Display flush completed");
            break;
    }
}
```

### Display Control
```c
// Rotation control
display_set_rotation(1);  // 90 degrees clockwise

// Get update counters
uint32_t buf_updates = display_get_buf_update_count();
uint32_t flush_count = display_get_flush_count();

// Power management
display_shut_down();  // Turn off display
```

## LVGL Integration

### Screen Callback Implementation
```c
static uint32_t screen_update_callback(void *user_data) {
    // Update LVGL screen content
    lv_timer_handler();  // Process LVGL timers

    // Return update interval in milliseconds
    return 16;  // ~60 FPS
}
```

### UI Initialization
```c
static void ui_initialize(void) {
    // Initialize LVGL
    lv_init();

    // Create display driver
    lv_display_t *disp = lv_display_create(HOR_RES, VER_RES);
    lv_display_set_flush_cb(disp, lvgl_flush_cb);

    // Create UI elements
    create_ui_elements();
}

static void lvgl_flush_cb(lv_display_t *disp, const lv_area_t *area, lv_color_t *color_p) {
    // Flush LVGL buffer to display hardware
    display_refresh_lock(portMAX_DELAY);
    // ... hardware-specific flush code ...
    display_refresh_unlock();

    lv_display_flush_ready(disp);
}
```

## Power Optimization

### E-Paper Display Strategies
- **Partial Refresh**: For text updates and small changes
- **Fast Refresh**: For image updates with acceptable ghosting
- **Full Refresh**: For complete screen changes (every few minutes)
- **Task Scheduling**: Intelligent pause/resume based on activity

### LCD Display Optimization
- **Backlight PWM**: Adjustable brightness for power savings
- **Update Batching**: Group multiple UI changes into single refresh
- **Sleep Modes**: Hardware power-down when not in use

## API Reference

### Core Functions
- `display_init()` / `display_uninit()`: Initialize/deinitialize display
- `display_task_start()`: Start background display task
- `display_refresh_lock()` / `display_refresh_unlock()`: Thread-safe refresh control

### E-Paper Specific (CONFIG_LCD_IS_EPD)
- `display_task_pause()` / `display_task_resume()`: Task control
- `display_request_full_refresh()`: Force full screen refresh
- `display_request_fast_refresh()`: Request fast refresh
- `display_request_partial_refresh()`: Request partial refresh

### Display Control
- `display_set_rotation()`: Set display rotation (0-3)
- `display_get_buf_update_count()`: Get buffer update counter
- `display_get_flush_count()`: Get flush operation counter
- `display_shut_down()`: Power down display

## Troubleshooting

### Common Issues
1. **Display Not Initializing**: Check SPI pin configuration and power connections
2. **E-Paper Ghosting**: Use full refresh periodically to clear ghost images
3. **LVGL Performance**: Ensure adequate task stack size and update intervals
4. **SPI Conflicts**: Verify SPI host selection doesn't conflict with other peripherals

### Debug Information
```c
// Check display status
ESP_LOGI(TAG, "Buffer updates: %lu", display_get_buf_update_count());
ESP_LOGI(TAG, "Flush count: %lu", display_get_flush_count());
ESP_LOGI(TAG, "Off-screen counter: %u", display_get_offscreen_counter());
```

### Log Levels
Configure via Kconfig:
- TRACE: Detailed LVGL and SPI operations
- DEBUG: Display driver initialization and task management
- INFO: Major display operations and events
- ERROR: Critical display failures

## Development

### Adding New Display Drivers
1. Create `driver_newdisplay.c` following the existing driver pattern
2. Implement required functions: `init`, `flush`, `power_on/off`
3. Add Kconfig options for GPIO and SPI configuration
4. Update `driver_vendor.h` with new driver declarations

### LVGL Customization
- Modify `lv_conf.h` for feature enable/disable
- Adjust color depth and buffer sizes based on display capabilities
- Configure theme and font settings for optimal appearance

### Testing
Run included examples:
```bash
cd examples/display_demo
idf.py build flash monitor
```

## Dependencies

- ESP-IDF v4.4+
- LVGL v8.3+ (when CONFIG_DISPLAY_USE_LVGL enabled)
- logger_common component
- esp_lcd drivers

## Hardware Compatibility

### Tested Boards
- **LilyGO T5 v2.13**: SSD1680/SSD1681 e-paper displays
- **LilyGO T-Display S3**: ST7789 LCD display
- **LilyGO T-Display S3 AMOLED**: RM67162 AMOLED display
- **QEMU ESP32**: Virtual display for development

### Pin Configuration
Display pins are auto-configured based on board selection in Kconfig. Manual override available for custom hardware.

## License

See LICENSE file in component directory.
