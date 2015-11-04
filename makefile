all: ./
	g++ -std=c++11 -c -g -fpermissive -I./TinyShaders.h -lGL -lX 2> errors.txt
