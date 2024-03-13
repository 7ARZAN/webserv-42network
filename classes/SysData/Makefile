# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tarzan <elakhfif@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/11 11:38:20 by tarzan            #+#    #+#              #
#    Updated: 2024/03/12 21:48:06 by tarzan           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = System

SRC = SysData.cpp

OBJ = build/SysData.o

CXXFLAGS = -Wall -Wextra -Werror

all: build $(NAME)

build:
	mkdir -p build

$(NAME): $(OBJ)
	clang++ $(CXXFLAGS) $(OBJ) -o $(NAME)

build/%.o: %.cpp
	clang++ $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf build

fclean: clean
	rm -rf $(NAME)
