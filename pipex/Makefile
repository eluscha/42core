NAME		= pipex
LIBFT		= libft
INCLUDE		= include
SRC_DIR		= src/
BONUS_DIR	= src/bonus/
CC			= cc
CFLAGS		= -Wall -Werror -Wextra -I

#Sources

SRC_FILES = pipex children manage_cmd error
BONUS_SRC_FILES = pipex_bonus children_bonus manage_cmd_bonus manage_pipes_bonus error_bonus

SRCS = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJS = $(SRCS:.c=.o) 

BONUS_SRCS = $(addprefix $(BONUS_DIR), $(addsuffix .c, $(BONUS_SRC_FILES)))
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

###

all:		$(NAME)

$(NAME):	$(OBJS)
			@make -C $(LIBFT)
			$(CC) $(OBJS) $(LIBFT)/libft.a -ldl -o $(NAME)
			@echo "pipex compiled!"

.bonus:		$(BONUS_OBJS)
			@touch $@
			@make -C $(LIBFT)
			$(CC) $(BONUS_OBJS) $(LIBFT)/libft.a -ldl -o $(NAME)

bonus:		.bonus

.c.o:
			@echo "Compiling: $<"
			@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
			@rm -f $(OBJS) $(BONUS_OBJS) .bonus
			@echo "pipex object files cleaned!"
			@make clean -C $(LIBFT)
			@echo "libft executable files cleaned"

fclean:			clean
			@rm -f $(NAME)
			@make fclean -C $(LIBFT)

re:				fclean all
			@echo "Cleaned and rebuilt everything for pipex!"

norm:
			@norminette $(SRCS)
			@norminette -R CheckDefine $(INCLUDE)
			@make norm -C $(LIBFT)

.PHONY:		all clean fclean re norm bonus
