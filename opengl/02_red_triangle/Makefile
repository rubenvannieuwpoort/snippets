all: build/main build/fragmentshader.fs build/vertexshader.vs

build/main: src/main.cpp
	mkdir -p build
	g++ src/main.cpp src/shader.cpp -lglfw -lOpenGL -lGLEW -o build/main

build/vertexshader.vs: src/vertexshader.vs
	mkdir -p build
	cp src/vertexshader.vs build/vertexshader.vs

build/fragmentshader.fs: src/fragmentshader.fs
	mkdir -p build
	cp src/fragmentshader.fs build/fragmentshader.fs

.PHONY: clean
clean:
	rm -rf build
