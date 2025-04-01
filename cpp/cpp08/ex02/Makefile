NAME		:= exec
CXX			:= c++
CPPFLAGS	:= -Wall -Werror -Wextra -std=c++98

TEMPLCLASS	:= MutantStack
HEADERS		:= $(addsuffix .hpp, $(TEMPLCLASS)) 
TEMPLATES	:= $(addsuffix .tpp, $(TEMPLCLASS))

SRCS 		:= main.cpp
OBJS 		:= $(SRCS:.cpp=.o) 

###

all:		$(NAME)

$(NAME):	$(OBJS) $(HEADERS) $(TEMPLATES)
			@$(CXX) $(CPPFLAGS) $(OBJS) -o $@
			@echo "$(NAME) executable compiled!"

%.o: %.cpp	$(HEADERS) $(TEMPLATES)
			@echo "Compiling: $<"
			@$(CXX) $(CPPFLAGS) -c $<

clean:
			@rm -f $(OBJS)
			@echo "Object files removed!"

fclean:			clean
			@rm -f $(NAME)
			@echo "Executable file removed!"

re:				fclean all
			@echo "Cleaned and rebuilt everything!"


.PHONY:		all clean fclean re
