NAME = Converter
CXX = c++
FLAGS = -Wall -Wextra -Werror -std=c++98

SRCS = main.cpp ScalarConverter.cpp

OBJ_DIR = objs
OBJS = $(SRCS:%.cpp=$(OBJ_DIR)/%.o)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(FLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	@$(CXX) $(FLAGS) $(OBJS) -o $(NAME)

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re