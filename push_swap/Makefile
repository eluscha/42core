NAME		= push_swap
LIBFT		= libft
INCLUDE		= include
SRC_DIR		= src/
CC			= cc
CFLAGS		= -Wall -Werror -Wextra -I

#Sources

SRC_FILES = push_swap dbl_lnk_list stack_operations info_tb count_ops solve_fts ops_struct_fts

SRCS = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJS = $(SRCS:.c=.o) 

###

all:		$(NAME)

$(NAME):	$(OBJS) $(INCLUDE)/push_swap.h
			@make -C $(LIBFT)
			$(CC) $(OBJS) $(LIBFT)/libft.a -ldl -o $(NAME)
			@echo "push_swap compiled!"

.c.o:
			@echo "Compiling: $<"
			@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
			@rm -f $(OBJS)
			@echo "push_swap object files cleaned!"
			@make clean -C $(LIBFT)
			@echo "libft object files cleaned"

fclean:			clean
			@rm -f $(NAME)
			@make fclean -C $(LIBFT)

re:				fclean all
			@echo "Cleaned and rebuilt everything for push_swap!"

norm:
			@norminette $(SRCS)
			@norminette -R CheckDefine $(INCLUDE)
			@make norm -C $(LIBFT)

.PHONY:		all clean fclean re norm bonus
