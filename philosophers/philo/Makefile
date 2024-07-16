NAME		= philo
CC			= cc
CFLAGS		= -Wall -Werror -Wextra

#Sources

SRCS = main.c
OBJS = $(SRCS:.c=.o) 

###

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(OBJS) -o $(NAME)

.c.o:
			@echo "Compiling: $<"
			@$(CC) $(CFLAGS) -c $< -o $@

clean:
			@rm -f $(OBJS)

fclean:			clean
			@rm -f $(NAME)

re:				fclean all
			@echo "Cleaned and rebuilt everything for philo!"

norm:
			@norminette $(SRCS)
			@norminette -R CheckDefine ./include

.PHONY:		all clean fclean re norm 
