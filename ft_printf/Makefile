NAME		= libftprintf.a
INCLUDE		= include
LIBFT		= libft
SRC_DIR		= src/
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
			@cp $(LIBFT)/libft.a .
			@mv libft.a $(NAME)
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
			@$(RM) -f $(LIBFT)/libft.a
			@echo "ft_printf executable files cleaned!"
			@echo "libft executable files cleaned!"

re:				fclean all
			@echo "Cleaned and rebuilt everything for ft_printf!"

norm:
			@norminette $(SRCS) $(LIBFT)
			@norminette -R CheckDefine $(INCLUDE)

.PHONY:		all clean fclean re norm
