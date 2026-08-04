#include "lvgl/lvgl.h"
#include <unistd.h>

int main(void) {
  lv_init();

  /* Crea la finestra SDL per PC */
  lv_display_t *disp = lv_sdl_window_create(800, 480);
  lv_group_t *g = lv_group_create();
  lv_group_set_default(g);

  lv_indev_t *mouse = lv_sdl_mouse_create();
  lv_indev_t *keyboard = lv_sdl_keyboard_create();
  lv_indev_set_group(keyboard, g);

  /* Test UI */
  lv_obj_t *label = lv_label_create(lv_screen_active());
  lv_label_set_text(label, "Hello LVGL!");
  lv_obj_center(label);

  lv_obj_t *D4_button = lv_button_create(lv_screen_active());
  lv_obj_t *D4_label = lv_label_create(D4_button);
  lv_label_set_text(D4_label, "D4");

  lv_obj_t *D6_button = lv_button_create(lv_screen_active());
  lv_obj_t *D6_label = lv_label_create(D6_button);
  lv_label_set_text(D6_label, "D6");

  lv_obj_t *D8_button = lv_button_create(lv_screen_active());
  lv_obj_t *D8_label = lv_label_create(D8_button);
  lv_label_set_text(D8_label, "D8");

  lv_obj_t *D10_button = lv_button_create(lv_screen_active());
  lv_obj_t *D10_label = lv_label_create(D10_button);
  lv_label_set_text(D10_label, "D10");

  lv_obj_t *D12_button = lv_button_create(lv_screen_active());
  lv_obj_t *D12_label = lv_label_create(D12_button);
  lv_label_set_text(D12_label, "D12");

  lv_obj_t *D20_button = lv_button_create(lv_screen_active());
  lv_obj_t *D20_label = lv_label_create(D20_button);
  lv_label_set_text(D20_label, "D20");

  lv_obj_t *D100_button = lv_button_create(lv_screen_active());
  lv_obj_t *D100_label = lv_label_create(D100_button);
  lv_label_set_text(D100_label, "D100");
  while (1) {
    uint32_t time_till_next = lv_timer_handler();
    usleep(time_till_next * 1000);
  }

  return 0;
}
