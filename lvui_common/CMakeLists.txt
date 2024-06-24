SET(SOURCES "")
SET(SRCS "ui_common.c" "")
SET(IMAGES "")
SET(FONTS "")
SET(INCS "")
SET(REQ "")
SET(PRIVREQ "")

SET(SOURCES
    ui_common.c
    ui_helpers.c
    ui_events.c
)

FILE(GLOB SRCS components/ui_*.c lv_ui_comp/*.c)

FILE(GLOB FONTS fonts/ui_font*.c)

if(CONFIG_DISPLAY_DRIVER_ST7789)
    FILE(GLOB IMAGES img16b/*.c)
else()
    FILE(GLOB IMAGES img8b/*.c)
endif()

SET(INCS "include" "lv_ui_comp")
SET(REQ ${REQ} lvgl)
SET(PRIVREQ ${PRIVREQ} logger_common)

idf_component_register(
    SRCS ${SOURCES} ${SRCS} ${IMAGES} ${FONTS}
    INCLUDE_DIRS ${INCS}
    REQUIRES ${REQ}
    PRIV_REQUIRES ${PRIVREQ}
)

UNSET(REQ)
UNSET(PRIVREQ)
