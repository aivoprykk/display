# The following five lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.16)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(lvgl_demo_2)

idf_build_get_property(lv_conf LV_CONF_PATH)
if(lv_conf)
idf_build_set_property(COMPILE_OPTIONS "-DLV_CONF_PATH=${lv_conf}" APPEND)
endif()
