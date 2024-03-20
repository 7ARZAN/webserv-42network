# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tarzan <elakhfif@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/11 11:38:20 by tarzan            #+#    #+#              #
#    Updated: 2024/03/20 02:41:46 by elakhfif         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Routes

SRC = Routes.cpp

OBJ = build/Routes.o

FLAGS = -Wall -Wextra -Werror

all: build $(NAME)

build:
	if [ ! -d "build" ]; then mkdir build; fi

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
