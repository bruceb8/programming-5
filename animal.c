#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "pr5.h"

#pragma pack(1)
//Definition of the animal object.
struct animal {
	short int id;
	char name[20];
	char species[35];
	char size;
	short int age;
};
//Function printAnimal() prints the animal object's attibutes.
//
//PRE: Function takes in an object of type Animal to print it's 
//attributes to the console.
//
//POST: none

void printAnimal(Animal theAnimal) {
		printf("%hd,%s,%s,%c,%hd\n", theAnimal->id, theAnimal->name, theAnimal->species, theAnimal->size, theAnimal->age);
}
//Function toString() takes in a binary file byte by byte and compares each byte's decimal equivalent to 
//see if it falls within the range of 32-127. If so the ASCII equivalent char is printed if not a space
//is printed.
//
//PRE: the Function takes in a pointer pointing to the file to be read.
//
//POST: none.

void toString(FILE* theFilePtr) {
    int count = 0;
    while(!feof(theFilePtr)) {
        if (count % 80 == 0) {
            printf("\n");
        }
        char temp;
        fread(&temp, 1, 1, theFilePtr);
        if (temp > 32 && temp < 127){
            printf("%c", temp);
        } else {
            printf(" ");
        }
        count++;
	}
}
//Takes in a file pointer and reads the file as a set of 4 byte ints
//pre: takes a file ptr to an existing binary file animalbin.dat
//post: none
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
//Searches the binary file based on a sorted list of ID values and prints the
//animal associated with that ID
//pre: animal.dat is a sorted lists of animal data structures
//post: none
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
	//int flag = -1;
	Animal tempAn = malloc(sizeof(struct animal));
	if(idSearch >= 1 && idSearch <= size/temp){
	//for(i = 0; i < size; i+=temp){
	fseek(ptrF,(idSearch - 1)* temp, SEEK_SET);
	fread(tempAn, sizeof(struct animal), 1, ptrF);
	
			printAnimal(tempAn);
	
	} else {
		printf("ERROR That ID value does not exist.\n");
	}
	free(tempAn);

}
//Function updateAnimal() prompts the user for an animal ID. The function then skips to that ID number's information 
//and prompts the user to update the animal's information.
//
//PRE: the function takes in a pointer pointing to the file to be updated. This is like passing a parameter by reference.
//The user is promted to enter an animal's ID number. The function will use the ID number to find the animal's information,
//and then the user will be prompted again to update that information. 
//
//POST: the function updates the animal's information

void updateAnimal(FILE* theFilePtr) {
    short int ID;
	int maxId;
	fseek(theFilePtr, 0, SEEK_END);
	maxId = (ftell(theFilePtr))/(sizeof(struct animal));
	rewind(theFilePtr);
	//printf("%d", maxId);
    Animal thing = malloc(sizeof(struct animal));
	if (thing == NULL) {
		printf("memory could not be allocated correctly.");
	}
    printf("Please enter an animal ID.");
    scanf("%hd", &ID);
	while(getchar() != '\n') {;}
	while(ID < 0 || ID > maxId) {
		printf("Invalid ID.\n");
    	printf("Please enter an animal ID.");
    	scanf("%hd", &ID);	
		while(getchar() != '\n') {;}
	}
	//ID--;
	thing->id = ID;

	
    fseek(theFilePtr, ((ID - 1) * sizeof(struct animal)), SEEK_SET);
    printf("Update the animal's name.");
    scanf("%[^\n]", thing->name);
	while(getchar() != '\n') {;}
    printf("Update the animal's species.");
    scanf("%[^\n]", thing->species);
	while(getchar() != '\n') {;}
    printf("Update the animal's size.");
    scanf("%c", &(thing->size));
	while(getchar() != '\n') {;}
    printf("Update the animal's age.");
    scanf("%hd", &(thing->age));
	while(getchar() != '\n') {;}

    fwrite(thing, sizeof(struct animal), 1, theFilePtr);
    
    printf("%hd %s %s %c %hd\n", thing->id, thing->name, thing->species, thing->size, thing->age);
    
    free(thing);
}
//Deletes the specified animal struct if it exists and truncates the file
//to accomodate the shrunken data file
//pre: sorted by ID list of animal structs
//post: a smaller list with the specified element deleted
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
	Animal tempAn = malloc(sizeof(struct animal));
	//for(i = 0; i < size; i+=temp){
	if(idSearch >= 1 && idSearch <= size/temp){
		fseek(ptrF,(idSearch)* temp, SEEK_SET);
					
		 for(i = (idSearch)* temp; i < size; i+=temp) {
				fread(tempAn, sizeof(struct animal), 1, ptrF);	
				int pos = ftell(ptrF);
				tempAn->id--;
				fseek(ptrF, -2 * (sizeof(struct animal)), SEEK_CUR);
				fwrite(tempAn, sizeof(struct animal), 1, ptrF);
				fseek(ptrF, sizeof(struct animal), SEEK_CUR);
			}
		ftruncate(fileno(ptrF), size - temp);
	}else {
		printf("ERROR That ID value does not exist.\n");
	}

	free(tempAn);
	
}

//prints the binary file of animal structs to a csv file
//pre: the file exists
//post: none
void printCSV(FILE* ptrF){
	FILE* fileX = fopen("animals.csv", "w");
	fseek(ptrF, 0, SEEK_END);
	int size = ftell(ptrF);
	int i;
	int temp = sizeof(struct animal);
	rewind(ptrF);
	Animal tempAn = malloc(sizeof(struct animal));
	for(i = 0; i < size; i+=temp){
		fread(tempAn, sizeof(struct animal), 1, ptrF);

		fprintf(fileX, "%hd,%s,%s,%c,%hd,,\n", tempAn->id, tempAn->name, tempAn->species, tempAn->size, tempAn->age);
	}
	fclose(fileX);
	free(tempAn);
}













