all: glad.o main.o 
	rm -f main
	g++ glad.o main.o -o main -ldl -lglfw -lGL -lX11 -lpthread -lXrandr -lXi
	rm -f *.o

glad.o: glad.c
	gcc glad.c -c

main.o: main.cpp
	g++ main.cpp -c
