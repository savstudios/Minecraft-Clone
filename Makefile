all:
	g++ -o main src/main.cpp src/glad.c -Iinclude -Lsrc/lib -lglfw3dll