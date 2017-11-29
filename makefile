animalbin: main.o animal.o
	gcc -o animalbin main.o animal.o
main.o: main.c pr5.h
	gcc -c -std=gnu90 main.c
animal.o: animal.c pr5.h
	gcc -c -std=gnu90 animal.c
