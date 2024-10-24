NAME		:= cub3d
CFLAGS		:= -Wextra -Wall -Werror -Wunreachable-code -Ofast -g
SRC_DIR		:= ./src/
LIBMLX		:= ./MLX42
LIBFT   	:= ./libft

HEADERS		:= -I $(LIBMLX)/include/MLX42/ -I ./include
LIBS		:= $(LIBFT)/libft.a $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

SRC_FILES	:= main map_helpers check_map draw_map txtr_img_utils draw_fts move_player
B_SRC_FILES	:= $(addsuffix _bonus, $(SRC_FILES))

SRCS 		:= $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJS 		:= $(SRCS:.c=.o)

all: $(LIBFT) $(LIBMLX) $(NAME)

$(LIBMLX):
	@if [ ! -d $(LIBMLX) ]; then \
        echo "Directory $(LIBMLX) does not exist. Cloning repository..."; \
        git submodule add https://github.com/codam-coding-college/MLX42.git; \
    fi
	@cmake $(LIBMLX) -B $(LIBMLX)/build -DDEBUG=0 && make -C $(LIBMLX)/build -j4

$(LIBFT):	
	@make -C $(LIBFT)

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
	@make clean -C $(LIBFT)
	@echo "libft object files cleaned"

fclean: clean
	@rm -f $(NAME)
	@rm -rf $(LIBMLX)/build
	@rm -f .libmlx_done

re: fclean all
	@echo "Cleaned and rebuilt everything!"

norm:
	@norminette $(SRCS) $(BONUS_SRCS)
	@make norm -C $(LIBFT)
	@norminette -R CheckDefine ./include/*.h

.PHONY: all, clean, fclean, re, libmlx, libft, bonus
