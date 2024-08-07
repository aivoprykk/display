
SET (REQ lvgl esp_lcd)
SET (PRIVREQ driver logger_common esp_timer esp_lcd_panel_ssd1680)

if(CONFIG_DISPLAY_DRIVER_SSD1680 OR CONFIG_DISPLAY_DRIVER_SSD1681)
set(source_file driver_ssd168x.c)
set(PRIVREQ driver logger_common esp_timer esp_lcd_panel_ssd1680)
elseif(DEFINED CONFIG_DISPLAY_DRIVER_ST7789)
set(source_file driver_st7789.c)
set(PRIVREQ driver logger_common esp_timer)
endif()

set(src_dir lvui_ssd1680)

if(CONFIG_BMX_ENABLE)
list(APPEND PRIVREQ bmx280)
endif(CONFIG_BMX_ENABLE)

if(CONFIG_DISPLAY_USE_LVGL)

SET(lvcommon_dir lvui_common)
FILE(GLOB LSRCS  ${lvcommon_dir}/*.c)
FILE(GLOB FONTS ${lvcommon_dir}/fonts/ui_font*.c)

if(CONFIG_DISPLAY_DRIVER_ST7789)
    FILE(GLOB IMAGES ${lvcommon_dir}/img16b/*.c)
else()
    FILE(GLOB IMAGES ${lvcommon_dir}/img8b/*.c)
endif()

SET(SRCS ${source_file})
FILE(GLOB SOURCES ${src_dir}/*.c ${src_dir}/screens/*.c)
SET(INCS include ${src_dir} ${lvcommon_dir}/include)

endif(CONFIG_DISPLAY_USE_LVGL)

MESSAGE(STATUS "REQ: ${REQ}")
MESSAGE(STATUS "PRIVREQ: ${PRIVREQ}")

idf_component_register(SRCS ${LSRCS} ${SRCS} ${SOURCES} ${FONTS} ${IMAGES}
    INCLUDE_DIRS ${INCS}
    PRIV_INCLUDE_DIRS ${PRIVINCS}
    REQUIRES ${REQ}
    PRIV_REQUIRES ${PRIVREQ}
)
