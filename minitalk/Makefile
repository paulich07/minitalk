# === Colors ===
RED     	= \033[0;31m
GREEN   	= \033[0;32m
YELLOW  	= \033[0;33m
BLUE    	= \033[0;34m
MAGENTA 	= \033[0;35m
CYAN    	= \033[0;36m
RESET   	= \033[0m
BOLD		= \033[1m
UNDERLINE 	= \033[4;32m
GREEN_BG 	= \033[42m

TARGETS = client server

SRC_DIR		=	src
OBJ_DIR		=	obj
HEADERS_DIR =	include
LIBFT_DIR	=	libs/libft

# Sources
CLIENT_SRCS = 	$(SRC_DIR)/client.c \
				$(SRC_DIR)/utils.c \

SERVER_SRCS = 	$(SRC_DIR)/server.c

# Compiler
CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(SRC_DIR) -I$(HEADERS_DIR) -I$(LIBFT_DIR) -DBUFFER_SIZE=8
LDFLAGS = -L$(LIBFT_DIR) -lft

LIBFT = $(LIBFT_DIR)/libft.a

# Objects
CLIENT_OBJS = $(CLIENT_SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
SERVER_OBJS = $(SERVER_SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(TARGETS)

client: $(CLIENT_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(CLIENT_SRCS) $(LIBFT) -o client 

server: $(SERVER_OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(SERVER_SRCS) $(LIBFT) -o server

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo "---- Compiling $< ----> $@ ----"
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@echo "---- Create folder $@"
	mkdir -p $(OBJ_DIR)

$(LIBFT):
	@echo "$(RED)---- libft.a non trovata ---- $(RESET)"

clean:
	@echo "---- Removing $(CLIENT_OBJS)" $(SERVER_OBJS)
	rm -rf $(OBJ_DIR)

fclean: clean
	@echo "---- Removing executables $(TARGETS)"
	rm -f $(TARGETS)

re: fclean all