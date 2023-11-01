/****************************************************************************************
 * *  pa4 - By: Ryan Hui, rhui1
 * *  List.h
 * *  List Header File
 * *****************************************************************************************/

#pragma once

typedef struct NodeObj* Node; //Define Node.

typedef struct ListObj* List; //Define List.

//
List newList(void);

void freeList(List* pL);

//
int length(List L);

int index(List L);

void* front(List L);

void* back(List L);

void* get(List L);

//bool equals(List A, List B);

//
void clear(List L);

void set(List L, void* x);

void moveFront(List L);

void moveBack(List L);

void movePrev(List L);

void moveNext(List L);

void prepend(List L, void*x);

void append(List L, void*);

void insertBefore(List L, void*);

void insertAfter(List L, void*);

void deleteFront(List L);

void deleteBack(List L);

void delete(List L);

//
void printList(FILE* out, List L);

List copyList(List L);

List concatList(List A, List B);


