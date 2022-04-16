CXX:=g++
CXXFLAGS=-std=c++17 -Wall -Werror -g -O0

all: .always sudoku

sudoku: main.cpp
	$(CXX) $(CXXFLAGS) -o bin/$@ $<


.always:
	mkdir -p bin

clean:
	rm bin/*
	

