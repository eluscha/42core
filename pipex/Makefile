NAME		= pipex
LIBFT		= libft
INCLUDE		= include
SRC_DIR		= src/
CC			= cc
CFLAGS		= -Wall -Werror -Wextra -I

#Sources

SRC_FILES = pipex children cmds error heredoc

SRCS = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJS = $(SRCS:.c=.o) 

###

all:		$(NAME)

bonus:		$(NAME)

$(NAME):	$(OBJS)
			@make -C $(LIBFT)
			$(CC) $(OBJS) $(LIBFT)/libft.a -ldl -o $(NAME)
			@echo "pipex compiled!"

.c.o:
			@echo "Compiling: $<"
			@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
			@rm -f $(OBJS)
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

.PHONY:		all clean fclean re norm
