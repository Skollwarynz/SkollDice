#include "../include/src.h"
#include <signal.h>
#include <string.h>
#include "../include/globals.h"

FILE* rand_reader = NULL;
Dices types_and_number_of_dices[7] = {
    {0, D4},  {0, D6},  {0, D8},  {0, D10},
    {0, D12}, {0, D20}, {0, D100}
};

lv_obj_t *text_D4;
lv_obj_t *text_D6;
lv_obj_t *text_D8;
lv_obj_t *text_D10;
lv_obj_t *text_D12;
lv_obj_t *text_D20;
lv_obj_t *text_D100;
lv_obj_t *label_output;
lv_obj_t *screen;

void shutdown_app(lv_event_t * e){
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_CLICKED){
      if (screen != NULL) {
          lv_obj_delete(screen);
      }
      lv_display_t * display = lv_display_get_default();
      if (display != NULL) {
          lv_display_delete(display);
      }
      lv_deinit();
      fclose(rand_reader);
      exit(0);
    }
}

void clear_textarea(){
  const char* D4 = lv_textarea_get_text(text_D4);
  types_and_number_of_dices[0].n = atoi(D4);
  lv_textarea_set_text(text_D4, "");
  const char* D6 = lv_textarea_get_text(text_D6);
  types_and_number_of_dices[1].n = atoi(D6);
  lv_textarea_set_text(text_D6, "");
  const char* D8 = lv_textarea_get_text(text_D8);
  types_and_number_of_dices[2].n = atoi(D8);
  lv_textarea_set_text(text_D8, "");
  const char* D10 = lv_textarea_get_text(text_D10);
  types_and_number_of_dices[3].n = atoi(D10);
  lv_textarea_set_text(text_D10, "");
  const char* D12 = lv_textarea_get_text(text_D12);
  types_and_number_of_dices[4].n = atoi(D12);
  lv_textarea_set_text(text_D12, "");
  const char* D20 = lv_textarea_get_text(text_D20);
  types_and_number_of_dices[5].n = atoi(D20);
  lv_textarea_set_text(text_D20, "");
  const char* D100 = lv_textarea_get_text(text_D100);
  types_and_number_of_dices[6].n = atoi(D100);
  lv_textarea_set_text(text_D100, "");
}

static void calculate (lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);

    if(code == LV_EVENT_CLICKED) {

        char results[9] = "bob";    
        if(label_output != NULL)
          lv_label_set_text(label_output, "");
        clear_textarea();
        int index_dices = 0;
        while (index_dices < 7) {
          int number_of_generations = types_and_number_of_dices[index_dices].n;
          if (label_output != NULL && (number_of_generations > 0)) {
              snprintf(results, sizeof(results), "D%d: ", types_and_number_of_dices[index_dices].dices_type); 
              lv_label_ins_text(label_output, LV_LABEL_POS_LAST, results);
          }
          for (int i = 0; i < number_of_generations; i++) {
            #if defined(_WIN32) || defined(_WIN64)
              int value = windows_random(types_and_number_of_dices[index_dices].dices_type);   
            #else
              int value = simple_discard_method(
                types_and_number_of_dices[index_dices].dices_type, rand_reader);
            #endif
          if (label_output != NULL) {
            sprintf(results,"%d ",value);
            lv_label_ins_text(label_output, LV_LABEL_POS_LAST, results);
          }
          }
            if (label_output != NULL && (number_of_generations > 0)) {
              lv_label_ins_text(label_output, LV_LABEL_POS_LAST, "\n");
            }
          index_dices++;
        }
    }
}

int main(int argc, char *argv[]){
  lv_init();
  lv_sdl_window_create(540, 960);
  lv_obj_t *screen = lv_obj_create(lv_screen_active());
  lv_obj_set_size(screen, lv_pct(100), lv_pct(100));

  lv_obj_set_style_max_width(screen, 540, LV_PART_MAIN);
  lv_obj_set_style_max_height(screen, 960, LV_PART_MAIN);
 
  lv_group_t * g = lv_group_create();
  lv_group_set_default(g);
  lv_indev_t * wheel = lv_sdl_mousewheel_create();
  lv_indev_set_group(wheel, g);
  lv_sdl_mouse_create();
  lv_indev_t * kb_indev = lv_sdl_keyboard_create();
  static int32_t col_dsc[] = {LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};
  static int32_t row_dsc[] = {LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_FR(1), LV_GRID_TEMPLATE_LAST};

  // creation of the grid component
  lv_obj_t * grid = lv_obj_create(lv_screen_active());
  lv_obj_set_size(grid, lv_pct(100), lv_pct(50));
  lv_obj_set_layout(grid, LV_LAYOUT_GRID);
  lv_obj_set_grid_dsc_array(grid, col_dsc, row_dsc);  

//  button setups
  text_D4 = lv_textarea_create(grid);
  lv_textarea_set_placeholder_text(text_D4, "D4");
  lv_textarea_set_one_line(text_D4, true); //  
  lv_obj_set_grid_cell(text_D4, LV_GRID_ALIGN_STRETCH, 0, 1,
                                LV_GRID_ALIGN_STRETCH, 0, 1);
  lv_group_add_obj(g, text_D4);
  lv_indev_set_group(kb_indev, g);
  lv_group_focus_obj(text_D4);

  text_D6 = lv_textarea_create(grid);
  lv_textarea_set_placeholder_text(text_D6, "D6");
  lv_textarea_set_one_line(text_D6, true); //  
  lv_obj_set_grid_cell(text_D6, LV_GRID_ALIGN_STRETCH, 1, 1,
                                LV_GRID_ALIGN_STRETCH, 0, 1);
  lv_group_add_obj(g, text_D6);
  lv_indev_set_group(kb_indev, g);
  lv_group_focus_obj(text_D6);

  text_D8 = lv_textarea_create(grid);
  lv_textarea_set_placeholder_text(text_D8, "D8");
  lv_textarea_set_one_line(text_D8, true); //  
  lv_obj_set_grid_cell(text_D8, LV_GRID_ALIGN_STRETCH, 2, 1,
                                LV_GRID_ALIGN_STRETCH, 0, 1);
  lv_group_add_obj(g, text_D8);
  lv_indev_set_group(kb_indev, g);
  lv_group_focus_obj(text_D8);

  text_D10 = lv_textarea_create(grid);
  lv_textarea_set_placeholder_text(text_D10, "D10");
  lv_textarea_set_one_line(text_D10, true); //  
  lv_obj_set_grid_cell(text_D10, LV_GRID_ALIGN_STRETCH, 0, 1,
                                LV_GRID_ALIGN_STRETCH, 1, 1);
  lv_group_add_obj(g, text_D10);
  lv_indev_set_group(kb_indev, g);
  lv_group_focus_obj(text_D10);
  
  text_D12 = lv_textarea_create(grid);
  lv_textarea_set_placeholder_text(text_D12, "D12");
  lv_textarea_set_one_line(text_D12, true); //  
  lv_obj_set_grid_cell(text_D12, LV_GRID_ALIGN_STRETCH, 1, 1,
                                LV_GRID_ALIGN_STRETCH, 1, 1);
  lv_group_add_obj(g, text_D12);
  lv_indev_set_group(kb_indev, g);
  lv_group_focus_obj(text_D12);

  text_D20 = lv_textarea_create(grid);
  lv_textarea_set_placeholder_text(text_D20, "D20");
  lv_textarea_set_one_line(text_D20, true); //  
  lv_obj_set_grid_cell(text_D20, LV_GRID_ALIGN_STRETCH, 2, 1,
                                LV_GRID_ALIGN_STRETCH, 1, 1);
  lv_group_add_obj(g, text_D20);
  lv_indev_set_group(kb_indev, g);
  lv_group_focus_obj(text_D20);
  
  lv_obj_t * output_flex = lv_obj_create(lv_screen_active());
  lv_obj_set_size(output_flex, lv_pct(100), lv_pct(50));
  lv_obj_set_flex_flow(output_flex, LV_FLEX_FLOW_COLUMN);
  lv_obj_align(output_flex, LV_ALIGN_BOTTOM_MID, 0, 0);

  text_D100 = lv_textarea_create(grid);
  lv_textarea_set_placeholder_text(text_D100, "D100");
  lv_textarea_set_one_line(text_D100, true); //  
  lv_obj_set_grid_cell(text_D100, LV_GRID_ALIGN_STRETCH, 0, 1,
                                LV_GRID_ALIGN_STRETCH, 2, 2);
  lv_group_add_obj(g, text_D100);
  lv_indev_set_group(kb_indev, g);
  lv_group_focus_obj(text_D100);

  lv_obj_t *button_of_shutdown = lv_button_create(output_flex);
  lv_obj_t *label_of_shutdown = lv_label_create(button_of_shutdown);
  lv_label_set_text(label_of_shutdown, "Close app");
  lv_obj_add_event_cb(button_of_shutdown, shutdown_app, LV_EVENT_ALL, NULL);

  #if defined(_WIN32) || defined(_WIN64)
  #else
    rand_reader = fopen("/dev/urandom", "rb");
  #endif
  
  lv_obj_t *button_calculation = lv_button_create(output_flex);
  lv_obj_t *label_calculation = lv_label_create(button_calculation);
  lv_label_set_text(label_calculation, "Calculate");
  
  label_output = lv_label_create(output_flex);
  lv_label_set_text(label_output, "Results");
  lv_obj_set_width(label_output, lv_pct(100));
  lv_label_set_long_mode(label_output, LV_LABEL_LONG_WRAP);
  lv_obj_set_clickable(label_output, true);
  lv_obj_set_scroll_chain(label_output, true);

  lv_obj_add_event_cb(button_calculation, calculate, LV_EVENT_ALL, NULL);
  lv_obj_center(screen);

  // while infinito per il gioco che funzioni piu di una volta prob su raylib
while (1) { 
    uint32_t time_till_next = lv_timer_handler();

    if (time_till_next > 10) {
        time_till_next = 10;
    }

    SDL_Delay(time_till_next);
}

  return 0;
}
