NAME	:= so_long
CFLAGS	:= -Wextra -Wall -Werror -Wunreachable-code -Ofast
LIBMLX	:= ./MLX42
LIBFT   := ./libft

HEADERS	:= -I $(LIBMLX)/include -I ./include
LIBS	:= $(LIBFT)/libft.a $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
SRCS	:= main.c check_map.c draw_map.c
OBJS	:= ${SRCS:.c=.o}

all: libmlx $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build -DDEBUG=1 && make -C $(LIBMLX)/build -j4

libft:
	@make -C $(LIBFT)

$(NAME):	$(OBJS) $(LIBMLX) $(LIBFT) ./include/so_long.h
	$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)
	@echo "so_long compiled!"

%.o: %.c
	@echo "Compiling: $(notdir $<)"
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

clean:
	@rm -rf $(OBJS)
	@rm -rf $(LIBMLX)/build

fclean: clean
	@rm -rf $(NAME)

re: clean all

.PHONY: all, clean, fclean, re, libmlx, libft
