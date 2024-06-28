NAME		:= so_long
CFLAGS		:= -Wextra -Wall -Werror -Wunreachable-code -Ofast
SRC_DIR		:= ./src/
BONUS_DIR	:= ./src/bonus/
LIBMLX		:= ./MLX42
LIBFT   	:= ./libft

HEADERS		:= -I $(LIBMLX)/include/MLX42/ -I ./include
LIBS		:= $(LIBFT)/libft.a $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

SRC_FILES	:= main map_helpers check_map check_path draw_map txtr_img_utils draw_fts hook_fts move_player
B_SRC_FILES	:= $(addsuffix _bonus, $(SRC_FILES))

SRCS 		:= $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJS 		:= $(SRCS:.c=.o)

BONUS_SRCS	:= $(addprefix $(BONUS_DIR), $(addsuffix .c, $(B_SRC_FILES)))
BONUS_OBJS	:= $(BONUS_SRCS:.c=.o)

all: $(NAME)

libmlx:	.libmlx_done

.libmlx_done:
	@touch $@
	@cmake $(LIBMLX) -B $(LIBMLX)/build -DDEBUG=0 && make -C $(LIBMLX)/build -j4

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
	
.bonus:		$(BONUS_OBJS) .libmlx_done .libft_done ./include/so_long_bonus.h
	@touch $@
	$(CC) $(BONUS_OBJS) $(LIBS) $(HEADERS) -o $(NAME)
	@echo "so_long with bonus compiled!"

bonus:		.bonus

clean:
	@rm -rf $(OBJS) $(BONUS_OBJS) .bonus .libft_done
	@echo "so_long object files cleaned!"
	@make clean -C $(LIBFT)
	@echo "libft object files cleaned"

fclean: clean
	@rm -f $(NAME)
	@rm -rf $(LIBMLX)/build
	@rm -f .libmlx_done

re: fclean all
	@echo "Cleaned and rebuilt everything for so_long!"

norm:
	@norminette $(SRCS)
	@make norm -C $(LIBFT)
	@norminette -R CheckDefine ./include/so_long.h ./include/libft.h

.PHONY: all, clean, fclean, re, libmlx, libft, bonus
