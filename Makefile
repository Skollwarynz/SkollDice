# Compilatore e flag
CC = gcc
CFLAGS = -Wall -Wextra -O3 \
         -I./SkollDice \
         -I./SkollDice/include \
         -I./SkollDice/src \
         -I./SkollDice/dependencies \
         -I./SkollDice/dependencies/lvgl

# Flag di SDL2
SDL_CFLAGS := $(shell pkg-config --cflags sdl2)
SDL_LDFLAGS := $(shell pkg-config --libs sdl2)

CFLAGS += $(SDL_CFLAGS)

# File sorgente del tuo progetto
SRC = SkollDice/src/main.c SkollDice/src/random_dice.c

# Sorgenti core di LVGL (prendiamo solo le cartelle indispensabili per SDL2)
LVGL_DIR = SkollDice/dependencies/lvgl
LVGL_SRC = \
    $(wildcard $(LVGL_DIR)/src/core/*.c) \
    $(wildcard $(LVGL_DIR)/src/draw/*.c) \
    $(wildcard $(LVGL_DIR)/src/draw/sw/*.c) \
    $(wildcard $(LVGL_DIR)/src/draw/sw/blend/*.c) \
    $(wildcard $(LVGL_DIR)/src/font/*.c) \
    $(wildcard $(LVGL_DIR)/src/hal/*.c) \
    $(wildcard $(LVGL_DIR)/src/โหd/*.c) \
    $(wildcard $(LVGL_DIR)/src/indev/*.c) \
    $(wildcard $(LVGL_DIR)/src/layouts/*.c) \
    $(wildcard $(LVGL_DIR)/src/stdlib/*.c) \
    $(wildcard $(LVGL_DIR)/src/misc/*.c) \
    $(wildcard $(LVGL_DIR)/src/widgets/*.c) \
    $(wildcard $(LVGL_DIR)/src/drivers/sdl/*.c) \
    $(wildcard $(LVGL_DIR)/src/osal/*.c) \
    $(wildcard $(LVGL_DIR)/src/*.c)

# Tutti gli oggetti da compilare
OBJ = $(SRC:.c=.o) $(LVGL_SRC:.c=.o)

# Nome dell'eseguibile finale
TARGET = SkollDice_AppImage

all: $(TARGET)

$(TARGET): $(OBJ)
	@echo "Linking $(TARGET)..."
	$(CC) $(OBJ) -o $(TARGET) $(SDL_LDFLAGS) -lm -lpthread

%.o: %.c
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Pulizia dei file oggetto..."
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean
