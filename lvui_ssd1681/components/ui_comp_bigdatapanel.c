// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.0
// LVGL version: 8.3.6
// Project name: squareline_proj_1_54_02

#include "../ui.h"


// COMPONENT BigDataPanel

lv_obj_t * ui_BigDataPanel_create(lv_obj_t * comp_parent)
{

    lv_obj_t * cui_BigDataPanel;
    cui_BigDataPanel = lv_obj_create(comp_parent);
    lv_obj_set_width(cui_BigDataPanel, lv_pct(100));
    lv_obj_set_height(cui_BigDataPanel, lv_pct(100));
    lv_obj_clear_flag(cui_BigDataPanel, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_border_width(cui_BigDataPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(cui_BigDataPanel, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(cui_BigDataPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(cui_BigDataPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(cui_BigDataPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(cui_BigDataPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t * cui_DataLabel;
    cui_DataLabel = lv_label_create(cui_BigDataPanel);
    lv_obj_set_width(cui_DataLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(cui_DataLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(cui_DataLabel, 0);
    lv_obj_set_y(cui_DataLabel, 6);
    lv_obj_set_align(cui_DataLabel, LV_ALIGN_CENTER);
    lv_label_set_text(cui_DataLabel, "129.90");

    lv_obj_t * cui_InfoLabel;
    cui_InfoLabel = lv_label_create(cui_BigDataPanel);
    lv_obj_set_width(cui_InfoLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(cui_InfoLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(cui_InfoLabel, lv_pct(1));
    lv_obj_set_y(cui_InfoLabel, lv_pct(-8));
    lv_obj_set_align(cui_InfoLabel, LV_ALIGN_BOTTOM_LEFT);
    lv_label_set_text(cui_InfoLabel, "km/h");
    lv_obj_add_flag(cui_InfoLabel, LV_OBJ_FLAG_HIDDEN);     /// Flags

    lv_obj_t ** children = lv_mem_alloc(sizeof(lv_obj_t *) * _UI_COMP_BIGDATAPANEL_NUM);
    children[UI_COMP_BIGDATAPANEL_BIGDATAPANEL] = cui_BigDataPanel;
    children[UI_COMP_BIGDATAPANEL_DATALABEL] = cui_DataLabel;
    children[UI_COMP_BIGDATAPANEL_INFOLABEL] = cui_InfoLabel;
    lv_obj_add_event_cb(cui_BigDataPanel, get_component_child_event_cb, LV_EVENT_GET_COMP_CHILD, children);
    lv_obj_add_event_cb(cui_BigDataPanel, del_component_child_event_cb, LV_EVENT_DELETE, children);
    ui_comp_BigDataPanel_create_hook(cui_BigDataPanel);
    return cui_BigDataPanel;
}

