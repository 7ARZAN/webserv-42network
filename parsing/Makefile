# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tarzan <elakhfif@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/13 20:47:30 by tarzan            #+#    #+#              #
#    Updated: 2024/04/06 02:06:09 by elakhfif         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = conf

SRC = main.cpp config_file.cpp

HEADER = config_file.hpp

OBJ = build/main.o build/config_file.o

CXX = clang++

CXXFLAGS = -Wall -Wextra -Werror -std=c++98

all: build $(NAME)
	
build:
	mkdir -p build

build/%.o: %.cpp $(HEADER)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(NAME): $(OBJ) $(HEADER)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -rf build
	if [ -f "meme.txt" ]; then rm meme.txt; fi

fclean: clean
	rm -rf $(NAME)

re: fclean all

run: all
	./$(NAME)

.PHONY: all clean fclean re
