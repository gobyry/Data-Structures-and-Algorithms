/****************************************************************************************
 * *  pa4 - By: Ryan Hui, rhui1
 * *  Sparse.c
 * *  Sparse Program File
 * *****************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "List.h"
#include "Matrix.h"

int main(int argc, char* argv[]) {

	//Initialize file pointers.
	FILE *in = NULL;
	FILE *out = NULL;

    //Declare variables.
    int n = 0;
	int a = 0;
	int b = 0;

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

    //Scan for size of Matrices.
	fscanf(in, " %d %d %d", &n, &a, &b);

    //Create two matrices with scanned n.
	Matrix A = newMatrix(n);
	Matrix B = newMatrix(n);

    //Populate Matrix A.
    int row = 0;
    int col = 0;
    double val = 0;

	for(int i = 0; i < a; i += 1) { //Loop through scanned value fo a.
        fscanf(in, " %d %d %lf", &row, &col, &val);
        changeEntry(A, row, col, val);
	}

    //Populate Matrix B.
    for(int i = 0; i < b; i += 1) { //Loop through scanned value of b.
        fscanf(in, " %d %d %lf", &row, &col, &val);
        changeEntry(B, row, col, val);
    }

    //Print Matrix A.
    fprintf(out, "A has %d non-zero entries:\n", NNZ(A));
    printMatrix(out, A);

    //Print Matrix B.
    fprintf(out, "\nB has %d non-zero entries:\n", NNZ(B));
    printMatrix(out, B);

    //Print scalar multi[ple of A by 1.5.
    fprintf(out, "\n(1.5)*A =\n");
    Matrix C = scalarMult(1.5, A);
    printMatrix(out, C);

    //Print sum of A nd B.
    fprintf(out, "\nA+B =\n");
    Matrix D = sum(A, B);
    printMatrix(out, D);

    //Print sum of A and A.
    fprintf(out, "\nA+A =\n");
    Matrix E = sum(A, A);
    printMatrix(out, E);

    //Print difference of A from B.
    fprintf(out, "\nB-A =\n");
    Matrix F = diff(B, A);
    printMatrix(out, F);

    //Print difference of A and A.
    fprintf(out, "\nA-A =\n");
    Matrix G = diff(A, A);
    printMatrix(out, G);

    //Print transpose of A.
    fprintf(out, "\nTranspose(A) =\n");
    Matrix H = transpose(A);
    printMatrix(out, H);

    //Print product of A and B.
    fprintf(out, "\nA*B =\n");
    Matrix I = product(A, B);
    printMatrix(out, I);

    //Print product of B and B.
    fprintf(out, "\nB*B =\n");
    Matrix J = product(B, B);
    printMatrix(out, J);

    //Free Matrices.
    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&C);
    freeMatrix(&D);
    freeMatrix(&E);
    freeMatrix(&F);
    freeMatrix(&G);
    freeMatrix(&H);
    freeMatrix(&I);
    freeMatrix(&J);

    //Close files.
    fclose(in);
    fclose(out);

    return 0;
}
