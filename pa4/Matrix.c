/****************************************************************************************
 * *  pa4 - By: Ryan Hui, rhui1
 * *  Matrix.c
 * *  Matrix ADT File
 * *****************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "List.h"
#include "Matrix.h"

struct EntryObj { //Struct for Entry
    int col;
    double num;
} EntryObj;

struct MatrixObj { //Struct for Matrix.
    List* rows;
    int size;
    int nzE;
} MatrixObj;

Entry newEntry(int col, double num) { //Returns a new Entry.
    Entry E = calloc(1, sizeof(EntryObj)); //Allocate memory for Entry.
    //Set Entry pointers.
    E->col = col;
    E->num = num;
    return(E);
}

Matrix newMatrix(int n) { //Returns a new Matrix.
    Matrix M = calloc(1, sizeof(MatrixObj)); //Allocate memory for Matrix.
    //Set Matrix pointers.
    M->rows = calloc(n + 1, sizeof(List*)); //Allocate memory for Matrix rows.
    M->size = n; //Set Matrix size.
    M->nzE = 0; //Set non-zero element size.

    for(int i = 0; i <= n; i += 1) {
        M->rows[i] = newList(); //Create List of Lists for Matrix rows for Matrix size.
    }
    return(M); //Return newly created Matrix M.
}

void freeEntry(Entry* pE) { //Frees Entry.
    if(pE != NULL && *pE != NULL) { //Checks that Entry pointer is not NULL.
        free(*pE); //Free *pE.
		*pE = NULL; //Set pE to NULL.
    }
}

void freeMatrix(Matrix* pM) { //Frees Matrix.
    if(pM != NULL && *pM != NULL) { //Checks that Matrix pointer is not NULL.
		for(int i = 0; i <= size(*pM); i += 1) { //Loop through Matrix size.
            for(moveFront((*pM)->rows[i]); index((*pM)->rows[i]) >= 0 && length((*pM)->rows[i]) != 0; moveNext((*pM)->rows[i])) {
                Entry fE = (get((*pM)->rows[i]));
                freeEntry(&fE);
            }
            freeList(&(*pM)->rows[i]); //Frees each List of List index.
        }
        free((*pM)->rows); //Free Matrix rows.
        free(*pM); //Free *pM.
		*pM = NULL; //Set pM to NULL.
    }
}


//*** Access functions ***//
int size(Matrix M) { //Returns size of Matrix M.
    if(M == NULL) { //Check if Matrix is NULL.
		fprintf(stderr, "Matrix size is NULL\n");
		exit(EXIT_FAILURE);
    }
    return(M->size);
}

int NNZ(Matrix M) { //Returns number of non-zeo elements in Matrix M.
    if(M == NULL) { //Check if Matrix is NULL.
		fprintf(stderr, "NMZ is NULL\n");
		exit(EXIT_FAILURE);
    }
    return(M->nzE);
}

int equals(Matrix A, Matrix B) { //Returns true of matrices are equal, false otherwise.
    if(A == NULL || B == NULL) { //If Matrix A or Matrix B is NULL.
		fprintf(stderr, "Equals matrix is NULL.\n");
        exit(EXIT_FAILURE);
	}
    if(A == B) { //If Matrices are equal.
        return true;
    }
    if(size(A) != size(B)) { //If Matrices size are not equal.
        return false;
    }
    //Initialize Entries and Lists.
    Entry eA;
    Entry eB;
    List lA;
    List lB;

    for(int i = 1; i <= size(A); i += 1) { //Loop through size of Matrix A.
        //Set Lists A and B values to Matrices A and B rows.
        lA = A->rows[i];
        lB = B->rows[i];

        //Reset Lists A and B.
        moveFront(lA);
        moveFront(lB);

        while(index(lA) >= 0 && index(lB) >= 0) { //Loop through Lists A and B.
            //Set Entries equal to List A and B values.
            eA = (Entry)get(lA);
            eB = (Entry)get(lB);

            if(eA->col != eB->col)  { //If Entry columns are not equal.
                return false;
            }
            if(eA->num != eB->num) { //If Entry numbers are not equal.
                return false;
            }
            if(index(lA) != index(lB)) { //If Lists index are not equal.
                return false;
            }
            if(length(lA) != length(lB)) { //If Lists length are not equal.
                return false;
            }
            moveNext(lA); //Move onto next element for List A.
            moveNext(lB); //Move onto next element for List B.
        }
    }
    return true; //Matrices are equal.
}

//*** Manipulation procedures ***//
void makeZero(Matrix M) { //Resets Matrix M.
    if(M == NULL) { //Check if Matrix is NULL.
		fprintf(stderr, "Make zero is NULL\n");
		exit(EXIT_FAILURE);
    }
    Entry fE; //Intialize Free Entry.

    for(int i = 1; i <= size(M); i += 1) { //Loop through size of Matrix M.
        for(moveFront(M->rows[i]); index(M->rows[i]) >= 0; moveNext(M->rows[i])) {
            fE = (Entry)get(M->rows[i]); //Set free Entry to Matrix row at ith element.
            freeEntry(&fE); //Clear each Entry.
        }
        clear(M->rows[i]); //Clear Matrix row at ith element.
    }

    //Reset Matrix pointers.
    M->nzE = 0;
}

void changeEntry(Matrix M, int i, int j, double x) { //Changes ith row and jth column of Matrix M to value x.
    if(M == NULL) { //Check if Matrix is NULL.
		fprintf(stderr, "Change entry is NULL.\n");
		exit(EXIT_FAILURE);
    }

    if(i < 1 || i > size(M) || j < 1 || j > size(M)) { // Pre: 1<=i<=size(M), 1<=j<=size(M)
        fprintf(stderr, "Change entry failed precondition. %d %d\n", i, j);
        exit(EXIT_FAILURE);
    }

    Entry eR; //Intialize Entry row.
    List lR = M->rows[i]; //Set List row to Matrix row at ith element.

    for(moveFront(lR); index(lR) >= 0; moveNext(lR)) { //Loop through Matrix M rows.
        eR = (Entry)get(lR); //Entry row equals value of List row.

        if(eR->col >= j) { //If Entry column is invalid.
            break;
        }
    }

    if(index(lR) >= 0 && eR->col == j) { //If List row index exists and column equals j.
        if(x != 0) { //If x value doesn't equal 0.
            eR->num = x; //Set Entry row number equal to x.
        }
        else { //Else x value is 0.
            freeEntry(&eR);
            delete(lR); //Delete index at List row.
            M->nzE-=1; //Decrement Matrix M non zero elements by 1
        }
    }
    else { //Else Entry was not found.
        if(x != 0) { //If x value doesn't equal 0.
            Entry nE = newEntry(j, x); //Create new Entry with values j and x.
            if(index(lR) >=0) {  //If index of List row exists.
                insertBefore(lR, nE); //Insert new Entry before List row.
            }
            else { //Else index of List row doesn't exist.
                append(lR, nE); //Append new Entry to List row.
            }
            M->nzE+=1; //Increment non zero element by 1.
        }
    }
}

//*** Matrix Arithmetic operations ***//
Matrix copy(Matrix A) { //Returns copy of Matrix.
    Matrix MC = newMatrix(size(A)); //Make new Matrix copy with size of Matrix A.
    List lR; //Intialize List for Matrix A's rows.
    Entry eR; //Intialize Entry for Matrix A's rows.

    for(int i = 1; i <= size(A); i += 1) { //Loop through Matrix A size.
        //Copy over Matrix rows.
        for(moveFront(A->rows[i]); index(A->rows[i]) >= 0; moveNext(A->rows[i])) { //Loop through Matrix A rows.
            lR = A->rows[i]; //Set List row equal to Matrix row value for the ith element.
            eR = (Entry)get(lR); //Set Entry equal to value of Matrix A row for element i.
            changeEntry(MC, i, eR->col, eR->num); //Change entry for Matrix copy.
        }
    }
    MC->size = size(A); //Set Matrix copy size equal to size of Matrix A.

    return(MC);
}

Matrix transpose(Matrix A) { //Returns transposed Matrix.
    Matrix MT = newMatrix(size(A)); //Create new Matrix for transposing.
    List lR; //Intialize List for Matrix A's rows.
    Entry eR; //Intialize Entry for Matrix A's rows.

    for(int i = 1; i <= size(A); i += 1) { //Loop through Matrix A size.
        //Copy over Matrix rows.
        for(moveFront(A->rows[i]); index(A->rows[i]) >= 0; moveNext(A->rows[i])) { //Loop through Matrix A rows.
            lR = A->rows[i]; //Set List row equal to Matrix row value for the ith element.
            eR = (Entry)get(lR); //Set Entry equal to value of Matrix A row for element i.
            changeEntry(MT, eR->col, i, eR->num); //Change entry for Matrix transpose.
        }
    }
    return(MT);
}

Matrix scalarMult(double x, Matrix A) { //Returns scalar multiple of Matrix A.
    Matrix MSM = newMatrix(size(A)); //Create new Matrix for scalar multiple.
    List lR; //Intialize List for Matrix A's rows.
    Entry eR; //Intialize Entry for Matrix A's rows.

    if(x == 0) { //If x equals 0.
        return(MSM); //Return empty newly created Matrix.
    }

    for(int i = 1; i <= size(A); i += 1) { //Loop through size of Matrix A.
        for(moveFront(A->rows[i]); index(A->rows[i]) >= 0; moveNext(A->rows[i])) { //Loop through Matrix A rows.
            lR = A->rows[i]; //Set List row equal to Matrix row value for the ith element.
            eR = (Entry)get(lR); //Set Entry equal to value of Matrix A row for element i.
            changeEntry(MSM, i, eR->col, eR->num * x); //Change entry based for scalar multiple of Matrix A.
        }
    }
    return(MSM);
}

Matrix sum(Matrix A, Matrix B) { //Returns sum of Matrix A and B.
    if(size(A) != size(B)) { // pre: size(A)==size(B)
        fprintf(stderr, "Sum failed precondition.\n");
        exit(EXIT_FAILURE);
    }
    if(A == NULL || B == NULL) {
        fprintf(stderr, "Sum is NULL.\n");
        exit(EXIT_FAILURE);
    }
    Matrix MS = newMatrix(size(A)); //Create Matrix sum to hold added values.
    Matrix MC = copy(B); //Create Matrix copy of Matrix B.

    for(int i = 1; i <= size(A); i += 1) { //Loop through size of Matrix A.

        List lA = A->rows[i]; //Create List for Matrix A row values.
        moveFront(lA); //Start at the beginning of lA.

        List lB = MC->rows[i]; //Creat List for Matrix B row values.
        moveFront(lB); //Start at the beginning of lB.

        while(index(lA) >= 0 && index(lB) >= 0) { //While List lA and lB aren't empty.
            //Set Entries with List of rows.
            Entry eA = (Entry)get(lA);
            Entry eB = (Entry)get(lB);

            if(eA->col == eB->col) { //If column exits in both Lists.
                changeEntry(MS, i, eA->col, eA->num + eB->num); //Add the values of of eA and eB together.
                //printf("%f\n", eA->num + eB->num);
                moveNext(lA);
                moveNext(lB);
            }
            else if(eA->col < eB->col) { //Else if eA column is less than eB column.
                changeEntry(MS, i, eA->col, eA->num); //Change entry to be eA column and value.
                moveNext(lA);
            }
            else if (eB->col < eA->col) { //Else if eB column is less than eA column.
                changeEntry(MS, i, eB->col, eB->num); //Change entry to be eA column and value.
                moveNext(lB);
            }
        }
        while(index(lA) >= 0) { //If cursor for lA is out of position.
            Entry eA = (Entry)get(lA); //Set entry eA.
            changeEntry(MS, i, eA->col, eA->num); //Change entry to be eA column and value.
            moveNext(lA);
        }
        while(index(lB) >= 0) { //If cursor for lB is out of position.
            Entry eB = (Entry)get(lB); //Set entry eB.
            changeEntry(MS, i, eB->col, eB->num); //Change entry to be eB column and value.
            moveNext(lB);
        }
    }
    //Free Matrix MC.
    freeMatrix(&MC);

    return(MS);
}

Matrix diff(Matrix A, Matrix B) { //Returns difference of Matrix A and B.
    if(size(A) != size(B)) { // pre: size(A)==size(B)
        fprintf(stderr, "Diff failed precondition.\n");
        exit(EXIT_FAILURE);
    }
    Matrix N = scalarMult(-1, B); //Get the scalar multiple of B and -1 to make Matrix B negative.

    Matrix MD = sum(A, N); //Get the sum of Matrices A and -B which results in the difference.

    //Free Matrix N.
    freeMatrix(&N);

    return(MD);
}

Matrix product(Matrix A, Matrix B) { //Returns product of Matrix A and B.
    if(size(A) != size(B)) { // pre: size(A)==size(B)
        fprintf(stderr, "Product failed precondition.\n");

    }

    Matrix MP = newMatrix(size(A)); //Create new Matrix product with size of Matrix A.

    Matrix MT = transpose(B);

    double product = 0.0;

    for(int i = 1; i <= size(A); i += 1 ) { //Loop through size of Matrix A for i.
        List lA = A->rows[i]; //Create List for Matrix A row values.

        if(length(lA) != 0 ) { //If length of lA is not 0, don't run code to save time looping.

            for(int j = 1; j <= size(A); j += 1) { //Loop through size of Matrix B for j.

                List lB = MT->rows[j]; //Creat List for Matrix B row values.
                moveFront(lA); //Start at the beginning of lA.

                moveFront(lB); //Start at the beginning of lB.

                if(length(lB) != 0) { //If length of lB is not 0.

                    product = 0; //Reset product value.

                    while(index(lA) >= 0 && index(lB) >= 0) { //While List lA and lB aren't empty.

                        //Set Entries with List of rows.
                        Entry eA = (Entry)get(lA);
                        Entry eB = (Entry)get(lB);

                        if(eA->col == eB->col) { //If column exits in both Lists.
                            product += (eA->num * eB->num); ////Multiply the values of of eA and eB together.
                            moveNext(lA);
                            moveNext(lB);
                        }
                        else if(eA->col < eB->col) { //Else if eA column is less than eB column.
                            moveNext(lA);
                        }
                        else if (eB->col < eA->col) { //Else eB column is less than eA column.
                            moveNext(lB);
                        }
                    }
                    if(product != 0) { //If the product isn't equal to 0.
                        Entry nE = newEntry(j, product); //Set new Entry.
                        append(MP->rows[i], nE); //Append new Entry to Matrix product.
                        MP->nzE += 1; //Increment non-zero elements by 1.
                    }
                }
            }
        }
    }
    //Free Matrix MT.
    freeMatrix(&MT);

    return(MP);
}

void printMatrix(FILE* out, Matrix M) { //Prints Matrix M to outfile.
    //Print Matrix structure provided by tutor Mike.
    Entry eP = NULL;
    int tracker = 0;
    for(int i = 1; i <= size(M); i++) {
        tracker  = 0;
        moveFront((M->rows[i]));
        if (index(M->rows[i]) >= 0) {
            eP = (Entry)get(M->rows[i]);
            if(eP) {
                fprintf(out, "%d: ", i);
                tracker = 1;
            }
        }
        while(index((M->rows[i])) >= 0) {
            eP = (Entry)get(M->rows[i]);
            if(eP) {
                fprintf(out, "(%d, %.1f) ", eP->col, eP->num);
            }
            moveNext(M->rows[i]);
        }
        if(tracker == 1) {
            fprintf(out, "\n");
        }
    }
}
