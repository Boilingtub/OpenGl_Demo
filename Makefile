src_files=src/main.cpp src/glad/glad.c src/render/stb_image.cpp
SRC=src
OUT=output
OBJ=objects
LIBS= -lGL -lglfw 
CFLAGS=
CC=g++
main: src/main.cpp
	$(CC) $(CFLAGS) $(src_files) $(LIBS) -o $(OUT)/main
	./$(OUT)/main

release: src/main.cpp
	$(CC) $(CFLAGS) -Ofast $(src_files) $(LIBS) -o $(OUT)/main
	./$(OUT)/main
