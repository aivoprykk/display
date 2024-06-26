
SET (REQ lvgl esp_lcd)
SET (PRIVREQ driver logger_common esp_timer esp_lcd_panel_ssd1680)

if(CONFIG_DISPLAY_DRIVER_SSD1680)
if(CONFIG_DISPLAY_USE_LVGL)
set(src_dir lvui_ssd1680)
set(source_file driver_ssd1680.c)
set(REQ lvgl esp_lcd)
set(PRIVREQ driver logger_common esp_lcd_panel_ssd1680)
else()
set(src_dir epd_driver)
if(CONFIG_HAS_SCREEN_DEPG0213BN)
set(source_file ${src_dir}/depg0213bn.c)
else()
set(source_file ${src_dir}/gdey0213b74.c)
endif()
set(PRIVREQ driver logger_common epd)
endif()
elseif(CONFIG_DISPLAY_DRIVER_SSD1681)
if(CONFIG_DISPLAY_USE_LVGL)
set(src_dir lvui_ssd1681)
set(source_file driver_ssd1681.c)
set(REQ lvgl esp_lcd)
set(PRIVREQ driver logger_common esp_lcd_panel_ssd1681)
else()
set(src_dir epd_driver)
if(CONFIG_HAS_SCREEN_GDEY0154D67)
set(source_file ${src_dir}/gdey0154d67.c)
endif()
set(PRIVREQ driver logger_common epd)
endif()
elseif(CONFIG_DISPLAY_DRIVER_ST7789)
set(src_dir lvui_st7789)
set(source_file driver_st7789.c)
set(REQ lvgl esp_lcd)
set(PRIVREQ driver logger_common)
endif()

if(CONFIG_BMX_ENABLE)
list(APPEND PRIVREQ bmx280)
endif(CONFIG_BMX_ENABLE)

if(CONFIG_DISPLAY_USE_LVGL)

## lvui_common
SET(lvcommon_dir lvui_common)
FILE(GLOB LSRCS  ${lvcommon_dir}/*.c ${lvcommon_dir}/lv_ui_comp/*.c)
FILE(GLOB FONTS ${lvcommon_dir}/fonts/ui_font*.c)
if(CONFIG_DISPLAY_DRIVER_ST7789)
    FILE(GLOB IMAGES ${lvcommon_dir}/img16b/*.c)
else()
    FILE(GLOB IMAGES ${lvcommon_dir}/img8b/*.c)
endif()

SET(SRCS ${source_file})
FILE(GLOB SOURCES ${src_dir}/*.c ${src_dir}/screens/*.c)
SET(INCS include ${src_dir} ${lvcommon_dir}/include ${lvcommon_dir}/lv_ui_comp)

else(CONFIG_DISPLAY_USE_LVGL)

SET(SRCS ${src_dir}/epd_driver_common.c ${source_file})
SET(INCS include ${src_dir}/include)
SET(PRIVINCS ${src_dir})

endif(CONFIG_DISPLAY_USE_LVGL)

MESSAGE(STATUS "REQ: ${REQ}")
MESSAGE(STATUS "PRIVREQ: ${PRIVREQ}")

idf_component_register(SRCS ${LSRCS} ${SRCS} ${SOURCES} ${FONTS} ${IMAGES}
    INCLUDE_DIRS ${INCS}
    PRIV_INCLUDE_DIRS ${PRIVINCS}
    REQUIRES ${REQ}
    PRIV_REQUIRES ${PRIVREQ}
)
