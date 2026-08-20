CC = gcc
CFLAGS = -Wall -Wextra -I. -ISkollDice/include -ISkollDice/src -Idependencies/lvgl -Idependencies/lvgl/include -Idependencies/lvgl/src/drivers/sdl $(shell pkg-config --cflags sdl2)
LDFLAGS = $(shell pkg-config --libs sdl2) -lm

SRC = SkollDice/src/main.c \
      SkollDice/src/random_dice.c \
      dependencies/lvgl/src/drivers/sdl/lv_sdl_window.c \
      dependencies/lvgl/src/drivers/sdl/lv_sdl_mouse.c \
      dependencies/lvgl/src/drivers/sdl/lv_sdl_keyboard.c \
      dependencies/lvgl/src/drivers/sdl/lv_sdl_mousewheel.c

all:
	$(CC) $(CFLAGS) $(SRC) -Ldependencies/lvgl -llvgl $(LDFLAGS) -o SkollDice

clean:
	rm -f SkollDice
