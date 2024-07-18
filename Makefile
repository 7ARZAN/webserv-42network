CFLAGS = -Wall -Wextra -Werror -Wformat=2 -flto -ffast-math -pedantic -ggdb
CC = g++
NAME = webserver
LIBCONFPP = lib/libconfpp/libconfpp.a
OBJ = build/main.o build/connection.o build/RequestParsing.o
SRC = src/main.cpp src/connection.cpp src/RequestParsing.cpp

INCLUDES = lib/libconfpp/includes

all: build $(NAME)

build/%.o: src/%.cpp
	$(CC) -I$(INCLUDES) $< $(CFLAGS) -c -o $@

build:
	if [ ! -d "build/" ]; then \
		mkdir build; \
	fi

$(LIBCONFPP):
	$(MAKE) -C lib/libconfpp

$(NAME): $(OBJ) $(LIBCONFPP) $(INCLUDES)
	$(CC) $(CFLAGS) $(OBJ) $(LIBCONFPP) -I$(INCLUDES) -o $(NAME)

clean :
	$(MAKE) fclean -C lib/libconfpp
	rm -rf build/

fclean : clean
	rm -rf $(NAME)

re : fclean $(LIBCONFPP) all

test : re
	./$(NAME) tests/default.conf

.SILENT: build fclean clean
