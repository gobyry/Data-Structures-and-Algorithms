/****************************************************************************************
 * *  pa2 - By: Ryan Hui, rhui1
 * *  List.h
 * *  List Header File
 * *****************************************************************************************/

#pragma once
#include <stdio.h>

typedef struct NodeObj* Node; //Define Node.

typedef struct ListObj* List; //Define List.

//
List newList(void);

void freeList(List* pL);

//
int length(List L);

int index(List L);

int front(List L);

int back(List L);

int get(List L);

bool equals(List A, List B);

//
void clear(List L);

void set(List L, int x);

void moveFront(List L);

void moveBack(List L);

void movePrev(List L);

void moveNext(List L);

void prepend(List L, int x);

void append(List L, int x);

void insertBefore(List L, int x);

void insertAfter(List L, int x);

void deleteFront(List L);

void deleteBack(List L);

void delete(List L);

//
void printList(FILE* out, List L);

List copyList(List L);

List concatList(List A, List B);










