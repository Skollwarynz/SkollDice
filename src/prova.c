#include "lvgl/lvgl.h"
#include <unistd.h>
#include <SDL2/SDL.h>
#include <stdio.h>

static void event_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);

    if(code == LV_EVENT_CLICKED) {
        printf("SBORRAAAAH\n");
        LV_LOG_USER("Clicked");
    }
}

static void palle(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_CLICKED) { 
        printf("calcolo in corsooooo\n");
    }
}

void genrate_GUI() {
  lv_init();
  lv_sdl_window_create(270, 480);
  lv_obj_t *screen = lv_obj_create(lv_screen_active());
  lv_obj_set_size(screen, lv_pct(100), lv_pct(100));
  lv_obj_set_style_max_width(screen, 270, LV_PART_MAIN);
  lv_obj_set_style_max_height(screen, 480, LV_PART_MAIN);
  lv_indev_t * mouse = lv_sdl_mouse_create();
  static int32_t col_dsc[] = {LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};
  static int32_t row_dsc[] = {LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};

  // creation of the grid component
  lv_obj_t * grid = lv_obj_create(lv_screen_active());
  lv_obj_set_size(grid, lv_pct(100), lv_pct(50));
  lv_obj_set_layout(grid, LV_LAYOUT_GRID);
  lv_obj_set_grid_dsc_array(grid, col_dsc, row_dsc);  

//  button setups
  lv_obj_t *button_D4 = lv_button_create(grid);
  lv_obj_t *label_D4 = lv_label_create(button_D4);
  lv_obj_add_event_cb(button_D4, event_handler, LV_EVENT_ALL, NULL);
  lv_label_set_text(label_D4, "D4");
  lv_obj_set_grid_cell(button_D4, LV_GRID_ALIGN_STRETCH, 0, 1,
                                LV_GRID_ALIGN_STRETCH, 0, 1);

  lv_obj_t *button_D6 = lv_button_create(grid);
  lv_obj_t *label_D6 = lv_label_create(button_D6);
  lv_obj_add_event_cb(button_D6, event_handler, LV_EVENT_ALL, NULL);
  lv_label_set_text(label_D6, "D6");
  lv_obj_set_grid_cell(button_D6, LV_GRID_ALIGN_STRETCH, 1, 1,
                                LV_GRID_ALIGN_STRETCH, 0, 1);


  lv_obj_t *button_D8 = lv_button_create(grid);
  lv_obj_t *label_D8 = lv_label_create(button_D8); 
  lv_obj_add_event_cb(button_D8, event_handler, LV_EVENT_ALL, NULL);
  lv_label_set_text(label_D8, "D8");
  lv_obj_set_grid_cell(button_D8, LV_GRID_ALIGN_STRETCH, 2, 2,
                                LV_GRID_ALIGN_STRETCH, 0, 1);


  lv_obj_t *button_D10 = lv_button_create(grid);
  lv_obj_t *label_D10 = lv_label_create(button_D10);
  lv_obj_add_event_cb(button_D10, event_handler, LV_EVENT_ALL, NULL);
  lv_label_set_text(label_D10, "D10");
  lv_obj_set_grid_cell(button_D10, LV_GRID_ALIGN_STRETCH, 0, 1,
                                LV_GRID_ALIGN_STRETCH, 1, 1);

  lv_obj_t *button_D12 = lv_button_create(grid);
  lv_obj_t *label_D12 = lv_label_create(button_D12);
  lv_obj_add_event_cb(button_D12, event_handler, LV_EVENT_ALL, NULL);
  lv_label_set_text(label_D12, "D12");
  lv_obj_set_grid_cell(button_D12, LV_GRID_ALIGN_STRETCH, 1, 1,
                                LV_GRID_ALIGN_STRETCH, 1, 1);

  lv_obj_t *button_D20 = lv_button_create(grid);
  lv_obj_t *label_D20 = lv_label_create(button_D20);
  lv_obj_add_event_cb(button_D20, event_handler, LV_EVENT_ALL, NULL);
  lv_label_set_text(label_D20, "D20");
  lv_obj_set_grid_cell(button_D20, LV_GRID_ALIGN_STRETCH, 2, 2,
                                LV_GRID_ALIGN_STRETCH, 1, 1);
  
  lv_obj_t * output_flex = lv_obj_create(lv_screen_active());
  lv_obj_set_size(output_flex, lv_pct(100), lv_pct(50));
  lv_obj_set_flex_flow(output_flex, LV_FLEX_FLOW_COLUMN);
  lv_obj_align(output_flex, LV_ALIGN_BOTTOM_MID, 0, 0);

  lv_obj_t *button_D100 = lv_button_create(output_flex);
  lv_obj_t *label_D100 = lv_label_create(button_D100);
  lv_label_set_text(label_D100, "D100");
  lv_obj_set_size(button_D100, LV_PCT(100), 40);
  lv_obj_add_event_cb(button_D100, event_handler, LV_EVENT_ALL, NULL);
  
  lv_obj_t *button_calculation = lv_button_create(output_flex);
  lv_obj_t *label_calculation = lv_label_create(button_calculation);
  lv_label_set_text(label_calculation, "Calculate");
  lv_obj_add_event_cb(button_calculation, palle, LV_EVENT_ALL, NULL);
  
  lv_obj_t *label_output = lv_label_create(output_flex);
  lv_label_set_text(label_output, "Risultati");

  lv_obj_center(screen);
}
