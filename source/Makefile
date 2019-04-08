all: glad.o shader.o main.o 
	rm -f main
	g++ glad.o shader.o main.o -o main -ldl -lglfw -lGL -lX11 -lpthread -lXrandr -lXi
	rm -f *.o

glad.o: glad.c
	gcc glad.c -c

shader.o : shader.cpp
	g++ shader.cpp -c

main.o: main.cpp
	g++ main.cpp -c
