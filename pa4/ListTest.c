/****************************************************************************************
 * *  pa4 - By: Ryan Hui, rhui1
 * *  ListTest.c
 * *  List Test File
 * *****************************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"List.h"

int main(int argc, char* argv[]){
 List A = newList();
   List B = newList();
   List C = newList();
   int X[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30};
   int i, u=-1, v=-2, w=-3;
   bool equal = false;

   // initialize Lists A and B
   for(i=1; i<=20; i++){
      append(A, &X[i]);
      prepend(B, &X[i]);
   }

   for(i=1; i<=10; i++){
      prepend(A, &X[i]);
      append(B, &X[i]);
   }

   printf("Printing List A forward.\n");
   // print both lists of integers in forward direction
   for(moveFront(A); index(A)>=0; moveNext(A)){
      printf("%d ", *(int*)get(A));
   }
   printf("\n");
   printf("\n");

   printf("Printing List B forward.\n");
   for(moveFront(B); index(B)>=0; moveNext(B)){
      printf("%d ", *(int*)get(B));
   }
   printf("\n");
   printf("\n");


   printf("Printing List A ints backwards.\n");
   // print both lists of integers in backward direction
   for(moveBack(A); index(A)>=0; movePrev(A)){
      printf("%d ", *(int*)get(A));
   }
   printf("\n");
   printf("\n");

   printf("Printing List B ints backwards.\n");
   for(moveBack(B); index(B)>=0; movePrev(B)){
      printf("%d ", *(int*)get(B));
   }
   printf("\n");
   printf("\n");

   // make a shallow copy of A
   moveFront(A);
   while(index(A)>=0 ){
      append(C, get(A));
      moveNext(A);
   }
   printf("Printing List A copy forwards.\n");
   // print the copy in forward direction
   for(moveFront(C); index(C)>=0; moveNext(C)){
      printf("%d ", *(int*)get(C));
   }
   printf("\n");
   printf("\n");


   printf("Checking equality.\n");
   // check shallow equality of A and C by comparing pointers
   equal = (length(A)==length(C));

   moveFront(A);
   moveFront(C);
   while( index(A)>=0 && equal){
      equal = ( get(A)==get(C) );
      moveNext(A);
      moveNext(C);
   }

   printf("A equals B is %s\n", (equal?"true":"false") );

   moveFront(A);
   moveFront(B);
   while( index(A)>=0 && equal){
      equal = ( get(A)==get(B) );
      moveNext(A);
      moveNext(B);
   }

   printf("A equals C is %s\n", (equal?"true":"false") );

   moveFront(B);
   moveFront(C);
   while( index(B)>=0 && equal){
      equal = ( get(B)==get(C) );
      moveNext(B);
      moveNext(C);
   }

   printf("B equals C is %s\n", (equal?"true":"false") );

   printf("\n");
   printf("Printing index.\n");
   moveFront(A);
   for(i=0; i<5; i++) moveNext(A);     // at index 5
   printf("index(A)=%d\n", index(A));
   insertBefore(A, &u);                // now at index 6
   printf("index(A)=%d\n", index(A));
   for(i=0; i<9; i++) moveNext(A);     // at index 15
   printf("index(A)=%d\n", index(A));
   insertAfter(A, &v);                 // doesn't change index
   printf("index(A)=%d\n", index(A));
   for(i=0; i<5; i++) movePrev(A);     // at index 10
   printf("index(A)=%d\n", index(A));
   delete(A);                          // index is now undefined
   printf("index(A)=%d\n", index(A));
   moveBack(A);                        // now at index 20
   printf("index(A)=%d\n", index(A));
   for(i=0; i<10; i++) movePrev(A);    // at index 10
   printf("index(A)=%d\n", index(A));
   set(A, &w);
   moveFront(A);
   printf("index(A)=%d\n", index(A)); //Index at 0
   moveBack(A);
   printf("index(A)=%d\n", index(A)); //Index at 30.
   movePrev(A);
   printf("index(A)=%d\n", index(A)); //Index at 29
   moveNext(A);
   printf("index(A)=%d\n", index(A)); //Index at 30

   printf("\n");

   printf("Printing List A normally.\n");
   // print A in forward and backward direction
   for(moveFront(A); index(A)>=0; moveNext(A)){
      printf("%d ", *(int*)get(A));
   }
   printf("\n");
   printf("\nPrinting List B backwards.\n");
   for(moveBack(B); index(B)>=0; movePrev(B)){
      printf("%d ", *(int*)get(B));
   }
   printf("\n");

   printf("\nPrinting List C backwards.\n");
   for(moveBack(C); index(C)>=0; movePrev(C)){
      printf("%d ", *(int*)get(C));
   }
   printf("\n");
   printf("\n");

   printf("Length of List A.\n");
   // check length of A, before and after clear()
   printf("%d\n", length(A));
   clear(A);
   printf("Length of List A after clearing.\n");
   printf("%d\n", length(A));

   freeList(&A);
   freeList(&B);
   freeList(&C);

   return 0;
}


/*
Printing List A forward.
10 9 8 7 6 5 4 3 2 1 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20

Printing List B forward.
20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 1 2 3 4 5 6 7 8 9 10

Printing List A ints backwards.
20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 1 2 3 4 5 6 7 8 9 10

Printing List B ints backwards.
10 9 8 7 6 5 4 3 2 1 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20

Printing List A copy forwards.
10 9 8 7 6 5 4 3 2 1 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20

Checking equality.
A equals B is true
A equals C is false
B equals C is false

Printing index.
index(A)=5
index(A)=6
index(A)=15
index(A)=15
index(A)=10
index(A)=-1
index(A)=30
index(A)=20
index(A)=0
index(A)=30
index(A)=29
index(A)=30

Printing List A normally.
10 9 8 7 6 -1 5 4 3 2 1 2 3 4 5 -2 6 7 8 9 -3 11 12 13 14 15 16 17 18 19 20

Printing List B backwards.
10 9 8 7 6 5 4 3 2 1 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20

Printing List C backwards.
20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 1 2 3 4 5 6 7 8 9 10

Length of List A.
31
Length of List A after clearing.
0
*/
