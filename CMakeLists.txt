if(DEFINED CONFIG_DISPLAY_DRIVER_QEMU)
set(source_file driver_qemu.c)
elseif(DEFINED CONFIG_DISPLAY_DRIVER_ST7789)
set(source_file driver_st7789.c)
elseif(DEFINED CONFIG_DISPLAY_DRIVER_RM67162)
set(source_file driver_rm67162.c)
elseif(CONFIG_DISPLAY_DRIVER_SSD168X)
set(source_file driver_ssd168x.c)
endif()

SET(SRCS ${source_file} display_driver.c display.c)
SET(INCS include)
set(LV_CONF_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lv_conf.h)

if(CONFIG_DISPLAY_ENABLED)

if(CONFIG_DISPLAY_USE_LVGL)
SET(lvcommon_dir lvui_common)
FILE(GLOB LSRCS  ${lvcommon_dir}/*.c)
FILE(GLOB FONTS ${lvcommon_dir}/fonts/ui_font*.c)

if(CONFIG_DISPLAY_DRIVER_ST7789 OR CONFIG_DISPLAY_DRIVER_QEMU)
    FILE(GLOB IMAGES ${lvcommon_dir}/img16b/*.c)
else()
    FILE(GLOB IMAGES ${lvcommon_dir}/img8b/*.c)
endif()

set(src_dir lvui)
FILE(GLOB SOURCES ${src_dir}/*.c ${src_dir}/screens/*.c)
SET(INCS ${INCS} ${src_dir} ${lvcommon_dir}/include)

endif()
endif()

idf_component_register(SRCS ${LSRCS} ${SRCS} ${SOURCES} ${FONTS} ${IMAGES}
    INCLUDE_DIRS ${INCS}
    PRIV_INCLUDE_DIRS ${PRIVINCS}
    PRIV_REQUIRES driver esp_timer logger_common
)

idf_build_set_property(LV_CONF_PATH ${LV_CONF_PATH})

if(CONFIG_DISPLAY_ENABLED)
    target_link_libraries(${COMPONENT_LIB} PUBLIC idf::lvgl)
    target_link_libraries(${COMPONENT_LIB} PUBLIC idf::esp_lcd)
endif()

if(CONFIG_DISPLAY_DRIVER_RM67162)
    target_link_libraries(${COMPONENT_LIB} PRIVATE idf::esp_lcd_panel_rm67162)
endif()

if(CONFIG_DISPLAY_DRIVER_SSD168X)
    target_link_libraries(${COMPONENT_LIB} PRIVATE idf::esp_lcd_panel_ssd1680)
endif()

if(CONFIG_BMX_ENABLE)
    target_link_libraries(${COMPONENT_LIB} PRIVATE idf::esp-idf-bmx280)
endif()