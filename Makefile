CFLAGS = -Wall -Wextra -Werror -Wformat=2 -ffast-math -pedantic -ggdb -O3 -std=c++98
CC = g++
NAME = webserver
LIBCONFPP = lib/libconfpp/libconfpp.a
OBJ = build/main.o build/connection.o build/RequestParsing.o build/log.o build/monitor.o \
      build/Response.o build/DELETEmethod.o build/GETmethod.o build/POSTmethod.o \
      build/multipart.o build/handleCGI.o

SRC = src/main.cpp src/connection.cpp src/RequestParsing.cpp src/log.cpp src/monitor.cpp \
      src/Response.cpp src/GETmethod.cpp src/POSTmethod.cpp src/DELETEmethod.cpp src/multipart.cpp \
      src/handleCGI.cpp \

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
