#ifndef D4C88E55_0DD9_45F6_9691_993AEF4B695D
#define D4C88E55_0DD9_45F6_9691_993AEF4B695D

#define EMPTY_VS 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
#define EMPTY_GROUP 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
#define GRP_C(mode) mode, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
#define GRP_3_11 \
        /* Timing - Group 3~11: all empty */ \
        EMPTY_GROUP, EMPTY_GROUP, EMPTY_GROUP, EMPTY_GROUP, \
        EMPTY_GROUP, EMPTY_GROUP, EMPTY_GROUP, EMPTY_GROUP, EMPTY_GROUP
#define GRP_2_11(mode) GRP_C(mode), GRP_3_11
#define GRP_FAST_0(mode) EMPTY_GROUP, EMPTY_GROUP, GRP_C(mode), GRP_3_11
#define VSC \
        /* LUT 0 VS Group 0~11 */ \
        0x80, 0x48, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
        /* LUT 1 VS Group 0~11 */ \
        0x40, 0x48, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
        /* LUT 2 VS Group 0~11, keep the same as LUT0 for Black-White e-Paper */ \
        0x80, 0x48, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
        /* LUT 3 VS Group 0~11, keep the same as LUT1 for Black-White e-Paper */ \
        0x40, 0x48, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
        /* LUT 4 VS Group 0~11, seems useless, just keep all zero */ \
        EMPTY_VS
#define PHASE_CTRLC 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x00, 0x00, 0x00
#define OTHER_0(mode) mode, 0x17, 0x41, 0x00, 0x32, 0x20

#define SSD1681_WAVESHARE_1IN54_REFRESH_TIME           0x01
#define SSD1681_WAVESHARE_1IN54_V2_LUT_FULL_REFRESH ((const uint8_t[]) { \
        VSC, \
        /* --- */ \
        /* Only Group0~2 are used */ \
        /* Group 0  TP[*A] TP[*B] SR[*AB] TP[*C] TP[*D] SR[*CD] RP[*] */ \
        GRP_C(0xa), \
        /* Group 1  TP[*A] TP[*B] SR[*AB] TP[*C] TP[*D] SR[*CD] RP[*] */ \
        0xA, 0x2, 0x00, 0xA, 0x2, 0x00, SSD1681_WAVESHARE_1IN54_REFRESH_TIME, \
        /* Group 2  TP[*A] TP[*B] SR[*AB] TP[*C] TP[*D] SR[*CD] RP[*] */ \
        GRP_2_11(0x0a), \
        /* --- */ \
        PHASE_CTRLC, \
        /* --- Other register params, do not transfer together with data above */ \
        OTHER_0(0x22) \
})

#define SSD1681_WAVESHARE_1IN54_V2_LUT_FAST_REFRESH ((const uint8_t[]) { \
        VSC, \
        /* --- */ \
        /* Only Group0~2 are used */ \
        GRP_FAST_0(0x0a), \
        /* --- */ \
        PHASE_CTRLC, \
        /* --- Other register params, do not transfer together with data above */ \
        OTHER_0(0x22) \
})

#define PARTIAL_UPDATE_LUT_SIZE 159

// NOTE: After several refreshes using SSD1681_WAVESHARE_1IN54_V2_LUT_FAST_REFRESH, you may notice the WHITE color
// goes GRAY and contrast decrease a lot. Use the LUT below to avoid that issue.
// NOTE: The LUT below will have the source output "keep previous output before power off", so the service life may be affected.
#define SSD1681_WAVESHARE_1IN54_V2_LUT_FAST_REFRESH_KEEP ((const uint8_t[]) { \
        VSC, \
        GRP_FAST_0(0x0a), \
        /* --- */ \
        PHASE_CTRLC, \
        /* --- Other register params, do not transfer together with data above */ \
        OTHER_0(0x07) \
})

#endif /* D4C88E55_0DD9_45F6_9691_993AEF4B695D */
