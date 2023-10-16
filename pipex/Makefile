NAME		= pipex
LIBFT		= libft
INCLUDE		= include
SRC_DIR		= src/
CC			= cc
CFLAGS		= -Wall -Werror -Wextra -I

#Sources

SRC_FILES = pipex

SRCS = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJS = $(SRCS:.c=.o) 

###

all:		$(NAME)

bonus:		$(NAME)

$(NAME):	$(OBJS)
			@make -C $(LIBFT)
			@mv $(LIBFT)/libft.a .
			$(CC) $(OBJS) libft.a -ldl -o $(NAME)
			@echo "pipex compiled!"

.c.o:
			@echo "Compiling: $<"
			@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
			@$(RM) -f $(OBJS)
			@echo "pipex object files cleaned!"
			@make clean -C $(LIBFT)

fclean:			clean
			@rm -f $(NAME)
			@echo "pipex executable files cleaned!"
			@make clean -C $(LIBFT)

re:				fclean all
			@echo "Cleaned and rebuilt everything for pipex!"

norm:
			@norminette $(SRCS)
			@norminette -R CheckDefine $(INCLUDE)
			@make norm -C $(LIBFT)

.PHONY:		all clean fclean re norm
