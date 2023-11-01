/****************************************************************************************
*  pa1 - By: rhui1
*  ListTest.c
*  Test client for List ADT
*****************************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"List.h"

int main(int argc, char* argv[]){

    //New list test.
    List A = newList();
    List B = newList();
    List C = NULL;
    int i = 0;

    //Append, prepend test.
    for(i=1; i<=35; i++){ //Loop through 1 - 35
        append(A,i); //Add i to end of the list.
        prepend(B,i); //Add i to the beginning of the list.
    }
    printf("\n");
    printf("List Tests.\n");
    printf("The original list A: ");
    printList(stdout,A); //print List A
    printf("\n");

    printf("---------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("Print List Test.\n");
    //Print list test.
    printf("Appended 100.\n");
    append(A, 100); //Append 100
    printList(stdout,A); //print List A
    printf("\n");

    printf("Prepended 100.\n");
    prepend(B, 100); //Prepend 100.
    printList(stdout,B); //print List B
    printf("\n");

    printf("---------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("Moving Tests.\n");

    printf("Getting indices for List A.\n");
    for(moveFront(A); index(A)>=0; moveNext(A)){ //
        printf("%d ", get(A));
    }
    printf("\n");
    printf("Getting indices for List B.\n");
    for(moveBack(B); index(B)>=0; movePrev(B)){ //
        printf("%d ", get(B));
    }

    C = copyList(A); //Copies List C to List A
    printf("\n");
    printf("Getting indices for List C up to index 10.\n");
    for(moveFront(C); index(C)<10; moveNext(C)){ //
        printf("%d ", get(C));
    }

    printf("\n");
    printf("---------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("Print Equal Tests.\n");
    printf("List A,B,C: \n");

    C = copyList(A); //Copies List C to List A
    printList(stdout,A); //print List A
    printf("\n");

    printList(stdout,B); //print List B
    printf("\n");

    printList(stdout,C); //print List C
    printf("\n");

    printf("List A == List B: %s\n", equals(A,B)?"true":"false"); //See if List A = List B
    printf("List B == List C: %s\n", equals(B,C)?"true":"false");
    printf("List C == List A: %s\n", equals(C,A)?"true":"false");
    printf("List A == List A: %s\n", equals(C,A)?"true":"false");

    printf("---------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("More Moving Tests.\n");
    moveFront(A);
    printf("Inserted 1001 before index 1.\n");
    for(i=0; i<0; i++) moveNext(A); // at index 1
    insertBefore(A, 1001);
    printList(stdout,A);
    printf("\n");

    printf("Insert 2002 after index 20.\n");
    for(i=0; i<20; i++) moveNext(A); // at index 20
    insertAfter(A, 2002);
    printList(stdout,A);
    printf("\n");

    printf("Appended 3003 and prepended 1111.\n");
    append(A, 3003);
    prepend(A, 1111);
    printList(stdout,A);

    printf("\n");
    printf("---------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("Deleting tests.\n");

    delete(A);
    printf("Original List is: ");
    printList(stdout,A);
    printf("\n");

    deleteFront(A);
    printf("Deleting front element gives: ");
    printList(stdout,A);
    printf("\n");

    deleteFront(A);
    printf("Deleting front element again gives: ");
    printList(stdout,A);
    printf("\n");

    deleteBack(A);
    printf("Deleteing back element gives: ");
    printList(stdout,A);
    printf("\n");

    printf("Current list length is: ");
    printf("%d\n", length(A));

    printf("---------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("Clearing and length.\n");

    clear(A);
    printf("After clearing: ");
    printf("%d\n", length(A));

    append(A, 1);
    printf("Appending 1 to an empty list: ");
    printList(stdout,A);
    printf("\n");

    //Frees Lists.
    freeList(&A);
    freeList(&B);
    freeList(&C);

    return(0);
    }

    /*
    Output of this program:
    List Tests.
    The original list A: 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35
    ---------------------------------------------------------------------------------------------------------------------------------------------
    Print List Test.
    Appended 100.
    1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 100
    Prepended 100.
    100 35 34 33 32 31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1
    ---------------------------------------------------------------------------------------------------------------------------------------------
    Moving Tests.
    Getting indices for List A.
    1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 100
    Getting indices for List B.
    1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 100
    Getting indices for List C up to index 10.
    1 2 3 4 5 6 7 8 9 10
    ---------------------------------------------------------------------------------------------------------------------------------------------
    Print Equal Tests.
    List A,B,C:
    1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 100
    100 35 34 33 32 31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1
    1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 100
    List A == List B: false
    List B == List C: false
    List C == List A: true
    List A == List A: true
    ---------------------------------------------------------------------------------------------------------------------------------------------
    More Moving Tests.
    Inserted 1001 before index 1.
    1001 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32 33 34 35 100
    Insert 2002 after index 20.
    1001 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 2002 22 23 24 25 26 27 28 29 30 31 32 33 34 35 100
    Appended 3003 and prepended 1111.
    1111 1001 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 2002 22 23 24 25 26 27 28 29 30 31 32 33 34 35 100 3003
    ---------------------------------------------------------------------------------------------------------------------------------------------
    Deleting tests.
    Original List is: 1111 1001 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 2002 22 23 24 25 26 27 28 29 30 31 32 33 34 35 100 3003
    Deleting front element gives: 1001 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 2002 22 23 24 25 26 27 28 29 30 31 32 33 34 35 100 3003
    Deleting front element again gives: 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 2002 22 23 24 25 26 27 28 29 30 31 32 33 34 35 100 3003
    Deleteing back element gives: 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 2002 22 23 24 25 26 27 28 29 30 31 32 33 34 35 100 0
    Current list length is: 36
    ---------------------------------------------------------------------------------------------------------------------------------------------
    Clearing and length.
    After clearing: 0
    Appending 1 to an empty list: 1
    */
