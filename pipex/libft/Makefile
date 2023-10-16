NAME		= libft.a
INCLUDE		= include
LIBFT		= libft
SRC_DIR		= ft_printf/
CC			= cc
CFLAGS		= -Wall -Werror -Wextra -I
RM			= rm -f
AR			= ar rcs

#Sources

SRC_FILES = ft_printf helpers printers1 printers2 printers3 modify_tab

SRCS = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJS = $(SRCS:.c=.o) 

###

all:		$(NAME)

bonus:		$(NAME)

$(NAME):	$(OBJS)
			@make -C $(LIBFT)
			@mv $(LIBFT)/libft.a .
			@$(AR) $(NAME) $(OBJS)
			@echo "ft_printf compiled!"

.c.o:
			@echo "Compiling: $<"
			@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
			@$(RM) -f $(OBJS)
			@echo "ft_printf object files cleaned!"
			@make clean -C $(LIBFT)
			@echo "libft object files cleaned!"

fclean:			clean
			@$(RM) -f $(NAME)
			@echo "libft librarary deleted!"

re:				fclean all
			@echo "Cleaned and rebuilt everything for ft_printf!"

norm:
			@norminette $(SRCS)
			@norminette -R CheckDefine $(INCLUDE)
			@make norm -C $(LIBFT)

.PHONY:		all clean fclean re norm
