# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tarzan <elakhfif@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/11 11:38:20 by tarzan            #+#    #+#              #
#    Updated: 2024/03/13 21:14:28 by tarzan           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Routes

SRC = Routes.cpp

OBJ = build/Routes.o

FLAGS = -Wall -Wextra -Werror

all: build $(NAME)

build:
	mkdir -p build

build/%.o: %.cpp $(HEADER)
	clang++ $(FLAGS) -c $< -o $@

$(NAME): $(OBJ)
	clang++ $(FLAGS) $(OBJ) -o $(NAME)

%.o: %.cpp
	clang++ $(FLAGS) -c $< -o $@

clean:
	rm -rf build

fclean: clean
	rm -f $(NAME)
