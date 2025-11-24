# set(lvui_path ../../../../../main/lvui)
# set(imgpath ${lvui_path}/img8b)
# set(fontpath ${lvui_path}/fonts)
# set(lvpath ${lvui_path})

# FILE(GLOB SRCS ${lvpath}/screens/ui_*.c ${lvpath}/ui_*.c)
# FILE(GLOB FONTS ${fontpath}/ui_font*.c)
# FILE(GLOB IMGS ${imgpath}/ui_img*.c)

idf_build_get_property(lv_conf LV_CONF_PATH)
if(lv_conf)
if(LVGL_VERSION_MAJOR GREATER 8)
    idf_build_set_property(COMPILE_OPTIONS "-DLV_CONF_PATH=\"${lv_conf}\"" APPEND)
else()
    idf_build_set_property(COMPILE_OPTIONS "-DLV_CONF_PATH=${lv_conf}" APPEND)
endif()
endif()

FILE(GLOB SRCS ui_*.c)

idf_component_register(SRCS main.c img_bitmap.c lvgl_demo_ui.c ${SRCS}
                       INCLUDE_DIRS "."
                       REQUIRES driver)
