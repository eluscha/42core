NAME		= megaphone
CXX			= c++
CPPFLAGS	= -Wall -Werror -Wextra -std=c++98

#Sources

SRC_FILES = megaphone

SRCS = $(addsuffix .cpp, $(SRC_FILES))
OBJS = $(SRCS:.cpp=.o) 

###

all:		$(NAME)

$(NAME):	$(OBJS)
			@$(CXX) $(CPPFLAGS) $(OBJS) -o $@
			@echo "megaphone executable compiled!"

%.o: %.cpp
			@echo "Compiling: $<"
			@$(CXX) $(CPPFLAGS) -c $<

clean:
			@$(RM) -f $(OBJS)
			@echo "object files removed!"

fclean:			clean
			@$(RM) -f $(NAME)
			@echo "executable file removed!"

re:				fclean all
			@echo "Cleaned and rebuilt everything!"


.PHONY:		all clean fclean re
