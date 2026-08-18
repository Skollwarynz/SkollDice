-include .env
export

CC = gcc

BOT_SRC_DIR = src
BOT_INC_DIR = include
DEP_DIR = dependencies/lib/concord

CFLAGS = -Wall -Wextra \
         -I$(BOT_INC_DIR) \
         -I$(DEP_DIR)/include \
         -I$(DEP_DIR)/cog-utils \
         -I$(DEP_DIR)/core \
         -I$(DEP_DIR)/gencodecs

# Aggiunto -lm in fondo per la libreria matematica standard (log10, pow, ecc.)
LDFLAGS = -L$(DEP_DIR)/lib -ldiscord -lcurl -lpthread -lm

BOT_SRCS = $(wildcard $(BOT_SRC_DIR)/*.c)
BOT_OBJS = $(BOT_SRCS:.c=.o)

TARGET = bot

unexport BOT_SRCS BOT_OBJS BOT_SRC_DIR BOT_INC_DIR

all: concord_lib $(TARGET)

concord_lib:
	$(MAKE) -C $(DEP_DIR) static

$(TARGET): $(BOT_OBJS)
	$(CC) $(BOT_OBJS) -o $(TARGET) $(LDFLAGS)

$(BOT_SRC_DIR)/%.o: $(BOT_SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

run: all
	./$(TARGET)

clean:
	rm -f $(BOT_SRC_DIR)/*.o $(TARGET)
	$(MAKE) -C $(DEP_DIR) clean

.PHONY: all concord_lib run clean
