CFLAGS=-O2 -Wall

dotify : main.o image.o sample.o
	gcc $(CFLAGS) main.o image.o sample.o -o dotify

main.o : main.cpp image.h sample.h
	gcc -c $(CFLAGS) main.cpp -o main.o

image.o : image.cpp image.h
	gcc -c $(CFLAGS) image.cpp -o image.o

sample.o : sample.cpp sample.h
	gcc -c $(CFLAGS) sample.cpp -o sample.o
