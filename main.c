#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "pr5.h"


int main() {
	int input = -1;
	FILE* ptrF = fopen("animals.dat", "rb+");
	while(input != 0) {
		printf("Please enter a number between 1 and 5 for operations and 0 to exit\n");
		scanf("%d", &input);
		while(getchar() != '\n') {;}
		while(input != 1 && input != 2 && input != 3 && input != 4 && input != 5 && input != 0) {
			printf("The input is not correct, please enter 1, 2, 3, 4, or 5\n");
			scanf("%d", &input);
			while(getchar() != '\n') {;}
		}
		if(input == 1) {
			toString(ptrF);
		} else if(input == 2) {
			input2(ptrF);
		}else if(input == 3) {
			input3(ptrF);
		}else if(input ==4) {
			updateAnimal(ptrF);
		}else if(input == 5) {
			input5(ptrF);
		}
	}
	
	

	printCSV(ptrF);
	
	//printf("YEEAAAAAH BOUIIIIIII");
	fclose(ptrF);
	

	return 1;
}

