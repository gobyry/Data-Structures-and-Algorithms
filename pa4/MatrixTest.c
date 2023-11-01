/****************************************************************************************
 * *  pa4 - By: Ryan Hui, rhui1
 * *  MatrixTest.c
 * *  Matrix Test File
 * *****************************************************************************************/

#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include"Matrix.h"

int main(){
     int n=100000;
     Matrix A = newMatrix(n);
     Matrix B = newMatrix(n);
     Matrix C, CC, D, DD, E, EE, F, FF, G, GG, H, HH;

     //Change Entry.
     changeEntry(A, 1,2,2); changeEntry(B, 1,3,3);
     changeEntry(A, 1,3,2); changeEntry(B, 1,1,1);
     changeEntry(A, 1,2,4); changeEntry(B, 1,1,1);
     changeEntry(A, 2,1,5); changeEntry(B, 2,1,1);
     changeEntry(A, 2,2,4); changeEntry(B, 2,3,2);
     changeEntry(A, 2,2,7); changeEntry(B, 2,1,3);
     changeEntry(A, 3,1,3); changeEntry(B, 3,3,2);
     changeEntry(A, 3,1,9); changeEntry(B, 3,1,2);
     changeEntry(A, 3,2,8); changeEntry(B, 3,2,3);
     changeEntry(A, 4,4,4); changeEntry(B, 4,1,2);
     changeEntry(A, 5,6,7); changeEntry(B, 5,8,9);

     printf("NNZ of A.\n");
     printf("%d\n", NNZ(A));
     printMatrix(stdout, A);
     printf("\n");

     printf("NNZ of B.\n");
     printf("%d\n", NNZ(B));
     printMatrix(stdout, B);
     printf("\n");

     printf("Scalar Multiple 0.5 of A.\n");
     C = scalarMult(0.5, A);
     printf("%d\n", NNZ(C));
     printMatrix(stdout, C);
     printf("\n");

     printf("Scalar Multiple 2.5 of B.\n");
     CC = scalarMult(1.5, B);
     printf("%d\n", NNZ(CC));
     printMatrix(stdout, CC);
     printf("\n");

     printf("Sum of A and B.\n");
     D = sum(A, B);
     printf("%d\n", NNZ(D));
     printMatrix(stdout, D);
     printf("\n");

     printf("Sum of B and B.\n");
     DD = sum(B, B);
     printf("%d\n", NNZ(DD));
     printMatrix(stdout, DD);
     printf("\n");

     printf("Difference of A and A.\n");
     E = diff(A, A);
     printf("%d\n", NNZ(E));
     printMatrix(stdout, E);
     printf("\n");

     printf("Difference of B and A.\n");
     EE = diff(B, A);
     printf("%d\n", NNZ(E));
     printMatrix(stdout, E);
     printf("\n");

     printf("Transpose of A.\n");
     FF = transpose(A);
     printf("%d\n", NNZ(FF));
     printMatrix(stdout, FF);
     printf("\n");

     printf("Transpose of B.\n");
     F = transpose(B);
     printf("%d\n", NNZ(F));
     printMatrix(stdout, F);
     printf("\n");

     printf("Product of A and B.\n");
     GG = product(A, B);
     printf("%d\n", NNZ(GG));
     printMatrix(stdout, GG);
     printf("\n");

     printf("Product of B and B.\n");
     G = product(B, B);
     printf("%d\n", NNZ(G));
     printMatrix(stdout, G);
     printf("\n");

     printf("Copy of A.\n");
     H = copy(A);
     printf("%d\n", NNZ(H));
     printMatrix(stdout, H);
     printf("\n");

     printf("Copy of B.\n");
     HH = copy(B);
     printf("%d\n", NNZ(HH));
     printMatrix(stdout, HH);
     printf("\n");

     printf("Matrix equality.\n");
     printf("A = A is %s\n", equals(A, A)?"true":"false" );
     printf("A = B is %s\n", equals(A, B)?"true":"false" );
     printf("A = C is %s\n", equals(A, C)?"true":"false" );
     printf("A = D is %s\n", equals(A, D)?"true":"false" );
     printf("A = E is %s\n", equals(A, E)?"true":"false" );
     printf("A = F is %s\n", equals(A, F)?"true":"false" );
     printf("A = G is %s\n", equals(A, G)?"true":"false" );
     printf("A = H is %s\n", equals(A, H)?"true":"false" );
     printf("\n");

     makeZero(A);
     printf("Matrix A after make zero.\n");
     printf("%d\n", NNZ(A));
     printMatrix(stdout, A);

     freeMatrix(&A);
     freeMatrix(&B);
     freeMatrix(&C);
     freeMatrix(&CC);
     freeMatrix(&D);
     freeMatrix(&DD);
     freeMatrix(&E);
     freeMatrix(&EE);
     freeMatrix(&F);
     freeMatrix(&FF);
     freeMatrix(&G);
     freeMatrix(&GG);
     freeMatrix(&H);
     freeMatrix(&HH);

     return EXIT_SUCCESS;
}

/*
Output of this program:
NNZ of A.
8
1: (2, 4.0) (3, 2.0)
2: (1, 5.0) (2, 7.0)
3: (1, 9.0) (2, 8.0)
4: (4, 4.0)
5: (6, 7.0)

NNZ of B.
9
1: (1, 1.0) (3, 3.0)
2: (1, 3.0) (3, 2.0)
3: (1, 2.0) (2, 3.0) (3, 2.0)
4: (1, 2.0)
5: (8, 9.0)

Scalar Multiple 0.5 of A.
8
1: (2, 2.0) (3, 1.0)
2: (1, 2.5) (2, 3.5)
3: (1, 4.5) (2, 4.0)
4: (4, 2.0)
5: (6, 3.5)

Scalar Multiple 2.5 of B.
9
1: (1, 1.5) (3, 4.5)
2: (1, 4.5) (3, 3.0)
3: (1, 3.0) (2, 4.5) (3, 3.0)
4: (1, 3.0)
5: (8, 13.5)

Sum of A and B.
13
1: (1, 1.0) (2, 4.0) (3, 5.0)
2: (1, 8.0) (2, 7.0) (3, 2.0)
3: (1, 11.0) (2, 11.0) (3, 2.0)
4: (1, 2.0) (4, 4.0)
5: (6, 7.0) (8, 9.0)

Sum of B and B.
9
1: (1, 2.0) (3, 6.0)
2: (1, 6.0) (3, 4.0)
3: (1, 4.0) (2, 6.0) (3, 4.0)
4: (1, 4.0)
5: (8, 18.0)

Difference of A and A.
0

Difference of B and A.
0

Transpose of A.
8
1: (2, 5.0) (3, 9.0)
2: (1, 4.0) (2, 7.0) (3, 8.0)
3: (1, 2.0)
4: (4, 4.0)
6: (5, 7.0)

Transpose of B.
9
1: (1, 1.0) (2, 3.0) (3, 2.0) (4, 2.0)
2: (3, 3.0)
3: (1, 3.0) (2, 2.0) (3, 2.0)
8: (5, 9.0)

Product of A and B.
8
1: (1, 16.0) (2, 6.0) (3, 12.0)
2: (1, 26.0) (3, 29.0)
3: (1, 33.0) (3, 43.0)
4: (1, 8.0)

Product of B and B.
11
1: (1, 7.0) (2, 9.0) (3, 9.0)
2: (1, 7.0) (2, 6.0) (3, 13.0)
3: (1, 15.0) (2, 6.0) (3, 16.0)
4: (1, 2.0) (3, 6.0)

Copy of A.
8
1: (2, 4.0) (3, 2.0)
2: (1, 5.0) (2, 7.0)
3: (1, 9.0) (2, 8.0)
4: (4, 4.0)
5: (6, 7.0)

Copy of B.
9
1: (1, 1.0) (3, 3.0)
2: (1, 3.0) (3, 2.0)
3: (1, 2.0) (2, 3.0) (3, 2.0)
4: (1, 2.0)
5: (8, 9.0)

Matrix equality.
A = A is true
A = B is false
A = C is false
A = D is false
A = E is true
A = F is false
A = G is false
A = H is true

Matrix A after make zero.
0
*/
