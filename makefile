all: ./
	g++ -std=c++11 -c -g -fpermissive ./source/ShaderManager.cpp -I./include/ -I./lib/ -lGL -lX 2> errors.txt
