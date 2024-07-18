CFLAGS = -Wall -Wextra -Werror -Wformat=2 -flto -ffast-math -pedantic -O3 
CC = g++
AR = ar
NAME = libconfpp.a
OBJ = build/parse.o build/common.o build/config.o build/search.o

all: build $(NAME)

build:
	if [ ! -d "build/" ]; then \
		mkdir build; \
	fi

build/%.o: src/%.cpp
	$(CC) $< $(CFLAGS) -c -o $@



$(NAME): $(OBJ) 
	$(AR) -crs $(NAME) $(OBJ)

clean :
	rm -rf build/
	rm -rf *.dSYM

fclean : clean
	rm -rf $(NAME)

re : fclean all

test : re 
	g++ tests/main.cpp libconfpp.a -o test
	./test ./tests/lib.conf

.SILENT: build fclean clean
