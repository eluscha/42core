NAME		:= minishell
LIBFT		:= ./libft
INCLUDE		:= ./include
SRC_DIR		:= ./
CC			:= cc
CFLAGS		:= -Wall -Werror -Wextra -g
HEADERS		:= -I $(INCLUDE)
LIBS		:= $(LIBFT)/libft.a -lreadline

SRC_FILES	:= main
SRCS		:= $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJS		:= $(SRCS:.c=.o) 


###

all:		$(NAME)

libft:	.libft_done

.libft_done:
	@touch $@
	@make -C $(LIBFT)

$(NAME):	.libft_done $(OBJS) $(INCLUDE)
	$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $@
	@echo "minishell compiled!"

.c.o:
	@echo "Compiling:  $(notdir $<)"
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

clean:
	@rm -rf $(OBJS) .libft_done
	@echo "minishell object files cleaned!"
	@make clean -C $(LIBFT)
	@echo "libft object files cleaned"

fclean: clean
	@rm -f $(NAME)

re: fclean all
	@echo "Cleaned and rebuilt everything for minishell!"

norm:
	@norminette $(SRCS)
	@make norm -C $(LIBFT)
	@norminette -R CheckDefine $(INCLUDE)

.PHONY: all, clean, fclean, re, libft
