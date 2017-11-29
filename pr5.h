#ifndef ANIMALS_H
#define ANIMALS_H

typedef struct animal * Animal;

void input2(FILE* ptrF);
void input3(FILE* ptrF);
void printAnimal(Animal theAnimal);
void input5(FILE* ptrF);
void printCSV(FILE* ptrF);
void updateAnimal(FILE* theFilePtr);
void toString(FILE* theFilePtr);
#endif
