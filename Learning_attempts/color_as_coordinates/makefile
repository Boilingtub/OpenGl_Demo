src_files=src/main.cpp src/glad/glad.c src/render/draw_basics.cpp src/Window/window.cpp
SRC=src
OUT=output
OBJ=objects
LIBS= -lglfw -lGL
obj_files=$(substr .cpp,.o,$(src_files))
main: src/main.cpp
	g++ $(src_files) $(LIBS) -o $(OUT)/main
	./$(OUT)/main


