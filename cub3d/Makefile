NAME		:= cub3d
CFLAGS		:= -Wextra -Wall -Werror -Wunreachable-code -Ofast -g
SRC_DIR		:= ./src/
LIBMLX		:= ./MLX42/build/libmlx42.a
LIBFT   	:= ./libft/libft.a

HEADERS		:= -I MLX42/include/MLX42/ -I ./include
LIBS		:= $(LIBFT) $(LIBMLX) -ldl -lglfw -pthread -lm

SRC_FILES	:= main map_helpers check_map draw_map txtr_img_utils draw_fts move_player
B_SRC_FILES	:= $(addsuffix _bonus, $(SRC_FILES))

SRCS 		:= $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJS 		:= $(SRCS:.c=.o)

all: $(LIBFT) $(LIBMLX) $(NAME)

$(LIBMLX):
	@if [ ! -d ./MLX42 ]; then \
        echo "Directory ./MLX42 does not exist. Cloning repository..."; \
        git submodule add https://github.com/codam-coding-college/MLX42.git; \
    fi
	@cmake ./MLX42 -B ./MLX42/build -DDEBUG=0 && make -C ./MLX42/build -j4

$(LIBFT):	
	@make -sC ./libft

$(NAME):	$(OBJS) ./include/cub3d.h 
	@rm -f .bonus 
	$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)
	@echo "cub3d compiled!"

.c.o:
	@echo "Compiling:  $(notdir $<)"
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)
	
clean:
	@rm -rf $(OBJS) .libft_done
	@echo "cub3d object files cleaned!"
	@make clean -C ./libft
	@echo "libft object files cleaned"

fclean: clean
	@rm -f $(NAME)
	@rm -rf ./MLX42/build
	@rm -f .libmlx_done

re: fclean all
	@echo "Cleaned and rebuilt everything!"

norm:
	@norminette $(SRCS) $(BONUS_SRCS)
	@make norm -C ./libft
	@norminette -R CheckDefine ./include/*.h

.PHONY: all, clean, fclean, re, libmlx, libft, bonus
