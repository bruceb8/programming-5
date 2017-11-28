#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "pr5.h"

#pragma pack(1)
struct animal {
	short int id;
	char name[20];
	char species[35];
	char size;
	short int age;
};

void printAnimal(Animal theAnimal) {
		printf("%hd,%s,%s,%c,%hd\n", theAnimal->id, theAnimal->name, theAnimal->species, theAnimal->size, theAnimal->age);
}

void input2(FILE* ptrF) {
	fseek(ptrF, 0, SEEK_END);
	int size = ftell(ptrF);
	int i;
	int temp;
	rewind(ptrF);
	for(i = 4; i < size + 4; i+=4) {
		fread(&temp, sizeof(int), 1, ptrF);
		printf("%10d ", temp);
		if(i%(36) == 0 && i != 0){
		printf("\n");
		}
	}
	printf("\n");
	rewind(ptrF);
}

void input3(FILE* ptrF) {
	//printf("WOW WE IN");
	//printf("%d", sizeof(struct animal));
	short int idSearch;
	printf("Enter the ID you want to find:\n");
	scanf("%hd", &idSearch);
	while(getchar() != '\n') {;}
	fseek(ptrF, 0, SEEK_END);
	int size = ftell(ptrF);
	int i;
	int temp = sizeof(struct animal);
	rewind(ptrF);
	Animal tim = malloc(sizeof(struct animal));
	for(i = 0; i < size; i+=temp){
		fread(tim, sizeof(struct animal), 1, ptrF);
		//if(idSearch == tim->id) {
				printAnimal(tim);
		//}
	}
	free(tim);

}


void input5(FILE* ptrF) {
	short int idSearch;
	printf("Enter the ID you want to delete:\n");
	scanf("%hd", &idSearch);
	while(getchar() != '\n') {;}
	fseek(ptrF, 0, SEEK_END);
	int size = ftell(ptrF);
	int i;
	int temp = sizeof(struct animal);
	rewind(ptrF);
	Animal tim = malloc(sizeof(struct animal));
	int flag = -1;	
	for(i = 0; i < size; i+=temp){
		fread(tim, sizeof(struct animal), 1, ptrF);
		if(idSearch == tim->id && flag < 0) {
				//printAnimal(tim);
				flag = 100;
				//fread(tim, sizeof(struct animal), 1, ptrF);
				//i++;				
		} else if(flag > 0) {
			int pos = ftell(ptrF);
			tim->id--;
			fseek(ptrF, 0, pos - sizeof(struct animal));
			fwrite(tim, sizeof(struct animal), 1, ptrF);
			fseek(ptrF, 0, pos);
		}
	}
	free(tim);
	ftruncate(fileno(ptrF), ftell(ptrF));
}










