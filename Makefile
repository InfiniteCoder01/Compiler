run: occ
	./occ

occ: main.cpp init.hpp character.hpp compiler/*.hpp
	g++ main.cpp -o occ -std=c++2a