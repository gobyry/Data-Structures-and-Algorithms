/****************************************************************************************
 * *  pa1 - By: rhui1
 * *  Lex.c
 * *  Lex Program File
 * *****************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "List.h"

#define MAX_LEN 300

int main(int argc, char* argv[]) {

	//Initialize file pointers.
	FILE *in = NULL;
   	FILE *out = NULL;

	int line_count = 0;

	//Step 1.
	//Command line checking.
	if(argc != 3) { //If there are not 2 command line arguments.
		fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]); //Print error message.
		exit(EXIT_FAILURE);
	}

	//Open infile.
	in = fopen(argv[1], "r");
      	if(in == NULL) { //If infile is NULL, print error message.
      		fprintf(stderr, "Unable to open file %s for reading\n", argv[1]);
      		exit(EXIT_FAILURE);
   	}

	//Open outfile.
	out = fopen(argv[2], "w");
   	if(out == NULL) { //If outfile is NULL, print error message.
      		fprintf(stderr, "Unable to open file %s for writing\n", argv[2]);
      		exit(EXIT_FAILURE);
   	}

	//Step 2.
	char n[MAX_LEN]; //Create character array n that has 300 elements.

	//Count number of lines n in input file.
	while(fgets(n, MAX_LEN, in) != NULL) { //fgets through infile.
		line_count+=1;
	}

	//Create string array.
	char** string_array = (char**)calloc(line_count, sizeof(char*)); //Allocate memory for each element in string array.
	rewind(in); //Rewind file pointer to the beginning of the file.

	int i = 0;
	//Loop through line count.
	while(fgets(n, MAX_LEN, in) != NULL) { //Fgets through infile.
		string_array[i] = (char*)calloc(strlen(n) + 1, sizeof(char)); //Allocate memory for each index in string array.
		strcpy(string_array[i], n); //String copy element n for element i of string array.
		i += 1; //Increment i by 1 for each n line length.
	}

	//Create list whose elements are the indices of the above string array.
	List NL = newList(); //Create List NL with newList().

	//Step 3.
	//Insert indices by looping through line count.
	for(int i = 0; i < line_count; i += 1 ) { //Loop through line count from infile.
		bool checker = false; //Create checker for the loop and insertion.
		moveFront(NL); //Move cursor to the front of NL.
		while(index(NL) >= 0 && !checker) { //While index is greater than or equal to 0.
			if(strcmp(string_array[i], string_array[get(NL)]) < 0) { //If string compare string array index and string array NL to see alphabetical order.
				insertBefore(NL, i); //Insert element i into NL before the front cursor.
				checker = true; //Break out of loop.
			}
			moveNext(NL); //Move cursor to the next element in List NL.
		}
		if((index(NL) == -1) && !checker) { //If NL index is out of bounds or inserted is false.
			append(NL, i); //Append index i to List NL.
		}
		else { //Else if conditions aren't met.
			continue; //Continue the loop.
		}
	}

	//Step 4.
	//Print array in alphabetical order to output file.
	for(moveFront(NL); index(NL) >= 0; moveNext(NL)) { //Loop through List NL and move cursor until end of List.
		fprintf(out, "%s", string_array[get(NL)]); //Print out each element string array according to NL.
	}

	//Delete and Clear List NL.
	deleteFront(NL);
	deleteBack(NL);
	delete(NL);
	clear(NL);

	//Free allocated memory used.
	freeList(&NL); //Frees List NL.

	for(int i = 0; i < line_count; i += 1) { //Frees every element in string array.
		free(string_array[i]);
	}
	free(string_array); //Frees string array.

	//Close infile and outfile.
	fclose(in);
	fclose(out);

	return 0;
}

