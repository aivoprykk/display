
if(CONFIG_DISPLAY_DRIVER_SSD1680)
if(CONFIG_DISPLAY_USE_LVGL)
set(src_dir lvui_ssd1680)
set(source_file driver_ssd1680.c)
else()
set(src_dir epd_driver)
if(CONFIG_HAS_SCREEN_DEPG0213BN)
set(source_file ${src_dir}/depg0213bn.c)
else()
set(source_file ${src_dir}/gdey0213b74.c)
endif()
endif()
elseif(CONFIG_DISPLAY_DRIVER_SSD1681)
if(CONFIG_DISPLAY_USE_LVGL)
set(src_dir lvui_ssd1681)
set(source_file driver_ssd1681.c)
else()
set(src_dir epd_driver)
if(CONFIG_HAS_SCREEN_GDEU0154F67)
set(source_file ${src_dir}/gdey0154d67.c)
endif()
endif()
elseif(CONFIG_DISPLAY_DRIVER_ST7789)
set(src_dir lvui_st7789)
set(source_file driver_st7789.c)
endif()

if(CONFIG_DISPLAY_USE_LVGL)
FILE(GLOB SOURCES ${source_file} ${src_dir}/*.c ${src_dir}/components/*.c ${src_dir}/screens/*.c ${src_dir}/images/*.c ${src_dir}/fonts/*.c)
SET(INCLUDES include ${src_dir} ${src_dir}/components)
else()
FILE(GLOB SOURCES ${source_file})
SET(INCLUDES include ${src_dir})
endif()

if(CONFIG_DISPLAY_DRIVER_SSD1680)
if(CONFIG_DISPLAY_USE_LVGL)
MESSAGE ("REQUIRES driver logger_common lvgl esp_lcd esp_lcd_panel_ssd1680 lvui_common")
idf_component_register(SRCS ${SOURCES}
    INCLUDE_DIRS ${INCLUDES}
    REQUIRES logger_common lvgl esp_lcd 
    PRIV_REQUIRES driver esp_lcd_panel_ssd1680 lvui_common
)
else()
MESSAGE ("REQUIRES driver logger_common epd")
idf_component_register(SRCS ${SOURCES}
    INCLUDE_DIRS ${INCLUDES}
    REQUIRES logger_common epd
    PRIV_REQUIRES driver
)
endif()
elseif(CONFIG_DISPLAY_DRIVER_SSD1681)
if(CONFIG_DISPLAY_USE_LVGL)
MESSAGE ("REQUIRES driver logger_common lvgl esp_lcd esp_lcd_panel_ssd1681 lvui_common")
idf_component_register(SRCS ${SOURCES}
    INCLUDE_DIRS ${INCLUDES}
    REQUIRES logger_common lvgl esp_lcd 
    PRIV_REQUIRES driver esp_lcd_panel_ssd1681 lvui_common
)
else()
MESSAGE ("REQUIRES driver logger_common epd")
idf_component_register(SRCS ${SOURCES}
    INCLUDE_DIRS ${INCLUDES}
    REQUIRES logger_common epd
    PRIV_REQUIRES driver
)
endif()
else()
MESSAGE ("REQUIRES driver logger_common lvgl esp_lcd lvui_common")
idf_component_register(SRCS ${SOURCES}
    INCLUDE_DIRS ${INCLUDES}
    REQUIRES logger_common lvgl esp_lcd
    PRIV_REQUIRES driver lvui_common
)
endif()