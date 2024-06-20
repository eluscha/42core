NAME		:= so_long
CFLAGS		:= -Wextra -Wall -Werror -Wunreachable-code -Ofast
SRC_DIR		:= ./src/
LIBMLX		:= ./MLX42
LIBFT   	:= ./libft

HEADERS		:= -I $(LIBMLX)/include/MLX42/ -I ./include
LIBS		:= $(LIBFT)/libft.a $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

SRC_FILES	:= main check_map draw_map
SRCS 		:= $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJS 		:= $(SRCS:.c=.o) 

all: $(NAME)

libmlx:	.libmlx_done

.libmlx_done:
	@touch $@
	@cmake $(LIBMLX) -B $(LIBMLX)/build -DDEBUG=1 && make -C $(LIBMLX)/build -j4

libft:	.libft_done

.libft_done:
	@touch $@
	@make -C $(LIBFT)

$(NAME):	$(OBJS) .libmlx_done .libft_done ./include/so_long.h
	$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)
	@echo "so_long compiled!"

.c.o:
	@echo "Compiling:  $(notdir $<)"
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)
	
clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -f $(NAME)
	@rm -rf $(LIBMLX)/build
	@rm -f .libmlx_done .libft_done

re: clean all

.PHONY: all, clean, fclean, re, libmlx, libft
