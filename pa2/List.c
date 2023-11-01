/****************************************************************************************
 * *  pa2 - By: Ryan Hui, rhui1
 * *  List.c
 * *  List ADT File
 * *****************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "List.h"

typedef struct NodeObj { //Struct for Node.
	int data;
	struct NodeObj* prev;
	struct NodeObj* next;
} NodeObj;

typedef struct ListObj { //Struct for List.
	Node front;
	Node back;
	Node cursor;
	int length;
	int index;
	int data;
} ListObj;

//Helper functions
Node newNode(void) { //Node constructor function.
	Node N;
	N = malloc(sizeof(struct NodeObj)); //Allocate memory for new Node N.
	//Set Node pointers.
	N->prev = NULL;
	N->next = NULL;
	N->data = 0; //Set Node N data to 0.
	return(N);
}

void freeNode(Node* pN) { //Frees *pN and sets it to NULL
	if(pN != NULL && *pN != NULL) {
		free(*pN); //Free *pN.
		*pN = NULL; //Set pN to NULL.
	}
}

bool isEmpty(List L) { //Returns true if empty.
	if(L == NULL) { //If List L is empty
		fprintf(stderr, "List is empty\n");
		exit(EXIT_FAILURE);
	}
	return(L->length == 0); //Return List L length equals to 0.
}

//Constructor-Destructor Functions.
List newList(void) { //Creates and returns a new empty List.
	List L;
	L = malloc(sizeof(ListObj)); //Create List L.

	//Setting pointers.
	L->front = NULL;
	L->back = NULL;
	L->cursor = NULL;
	L->length = 0;
	L->index = -1;
	return(L); //Return created List L.
}

void freeList(List* pL) { //Frees *pL and sets it to NULL
	if(pL != NULL && *pL != NULL) {
		clear(*pL); //Clear all elements in the List.
		free(*pL); //Free *pL.
		*pL = NULL; //Set pL to NULL.
	}
}

int length(List L) { //Returns size of List L.
	if(L == NULL) {
		fprintf(stderr, "Length List is null.\n");
		exit(EXIT_FAILURE);
	}
	return(L->length); //Return length.
}

int index(List L) { //Returns index of List L.
	if(L == NULL) {
		fprintf(stderr, "Index List is null\n");
		exit(EXIT_FAILURE);
	}
	return(L->index); //Return index.
}

int front(List L) { //Returns the front element of List L.
	if(L == NULL) { //Check if List L is NULL.
		fprintf(stderr, "Front List is null.\n");
		exit(EXIT_FAILURE);
	}
	if(isEmpty(L)) { //Check if List L is empty.
		fprintf(stderr, "List is empty.\n");
		exit(EXIT_FAILURE);
	}
	if(length(L) < 0) { //Pre: length() > 0.
        fprintf(stderr, "Length precondition is not met.\n");
        exit(EXIT_FAILURE);
    }
	return(L->front->data); //Return front element.
}

int back(List L) { //Returns the back element of List L.
	if(L == NULL) { //Check if List L is NULL.
        fprintf(stderr, "Back List is null.\n");
        exit(EXIT_FAILURE);
    }
    if(isEmpty(L)) { //Check if List L is empty.
        fprintf(stderr, "List is empty.\n");
        exit(EXIT_FAILURE);
	}
	if(length(L) < 0) { //Pre: length() > 0
        fprintf(stderr, "Length precondition is not met.\n");
        exit(EXIT_FAILURE);
    }
	return(L->back->data); //Return back element.
}

int get(List L) { //Returns the cursor element of List L.
	if(L == NULL) { //Check if List L is NULL.
        fprintf(stderr, "Get List is null.\n");
        exit(EXIT_FAILURE);
    }
    if(isEmpty(L)) { //Check if List L is empty.
        fprintf(stderr, "List is empty.\n");
        exit(EXIT_FAILURE);
    }
	if(length(L) <= 0 || index(L) < 0) { //Pre: length() > 0, index() >= 0.
        fprintf(stderr, "Length/index preconditions are not met.\n");
        exit(EXIT_FAILURE);
    }
	return(L->cursor->data); //Return cursor element.
}

bool equals(List A, List B) { //Returns true for same state.
	if(A == NULL || B == NULL) { //If List A or List B are NULL.
		fprintf(stderr, "Equals List is null.\n");
        exit(EXIT_FAILURE);
	}
	if(length(A) != length(B)) { //Check that the length of List A and B are not equal.
		return false;
	}
	moveFront(A); //Set cursor to front for List A.
	moveFront(B); //Set cursor to front for List B.
	while(index(A) >= 0 && index(B) >= 0) { //While List A and List B index have elements.
		if(get(A) != get(B)) { //If List A cursor element doesn't equal List B cursor element.
			return false; //Return false.
		}
		moveNext(A); //Set cursor one step back for List A.
		moveNext(B); //Set cursor one step back for List B.
	}
	return true; //Returns true for same state.
}

//Manipulation functions.
void clear(List L) { //Reset List L to original empty state.
	if(L == NULL) { //Check if List L is NULL.
        printf("Clear List is null.\n");
        exit(EXIT_FAILURE);
    }
	while(length(L) > 0) { //Loop through and clear length of List L.
		deleteFront(L); //Clear the front element.
	}
	//Resetting pointers.
	L->front = NULL;
	L->back = NULL;
	L->cursor = NULL;
	L->length = 0;
	L->index = -1;
}

void set(List L, int x) { //Overwrites cursor element.
	if(L == NULL) { //Check if List L is NULL.
        fprintf(stderr, "Set List is null.\n");
        exit(EXIT_FAILURE);
    }
	if(length(L) <= 0 || index(L) < 0) { //Pre: length() > 0, index() >= 0.
        fprintf(stderr, "Length/index preconditions are not met.\n");
        exit(EXIT_FAILURE);
    }
	L->cursor->data = x; //Overwrites cursor element with x.
}

void moveFront(List L) { //Set cursor under front element.
	if(L == NULL) { //Check if List L is NULL.
        fprintf(stderr, "MoveFront List is null.\n");
        exit(EXIT_FAILURE);
    }
	if(isEmpty(L)) { //Check if List L is empty.
		return; //Do nothing if empty.
	}
	L->cursor = L->front; //Set cursor under front element.
	L->index = 0; //Set index to 0.
}

void moveBack(List L) { //Set cursor under back element.
	if(L == NULL) { //Check if List L is NULL.
        fprintf(stderr, "MoveBack List is null.\n");
        exit(EXIT_FAILURE);
    }
	if(isEmpty(L)) { //Check if List L is empty.
		return; //Do nothing if empty.
	}
	L->cursor = L->back; //Set cursor under back element.
	L->index = length(L) - 1; //Set List L index to back of element.
}

void movePrev(List L) { //Move cursor one step foward.
	if(L == NULL || L->cursor == NULL) { //Check if List L or List L cursor is NULL.
		return; //Do nothing if undefined.
	}
	if(isEmpty(L)) { //Check if List L is empty.
		fprintf(stderr, "List is empty.\n");
		exit(EXIT_FAILURE);
	}
	if(L->cursor == L->front) { //If cursor is at front and defined.
		L->cursor = NULL; //Cursor becomes undefined.
	}
	else { //Else cursor is not at front and defined.
		L->cursor = L->cursor->prev; //Move cursor one step toward the front of List L.
	}
	if(L->cursor != NULL) { //If List L cursor is not at the end of index.
		L->index-=1; //Decrement index by 1.
	}
	else { //Else if cursor is at
		L->index = -1; //Reset List L index to -1.
	}
}

void moveNext(List L) { //Move cursor one step backward.
	if(L == NULL || L->cursor == NULL) { //Check if List L or List L cursor is NULL.
		return; //Do nothing if undefined.
	}
	if(isEmpty(L)) { //Check if List L is empty.
		fprintf(stderr, "List is empty.\n");
		exit(EXIT_FAILURE);
	}
	if(L->cursor == L->back) { //If cursor is at back and defined.
		L->cursor = NULL; //Cursor becomes undefined.
	}
	else { //Else cursor is not at back and defined.
		L->cursor = L->cursor->next; //Move cursor one step toward the back of List L.
	}
	if(L->cursor != NULL) { //If List L cursor is not NULL.
		L->index+=1; //Increment List L index by 1.
	}
	else { //Else if NULL.
		L->index = -1; //Reset List L index to -1.
	}
}

void prepend(List L, int x) { //Insert new element into List L before front element.
	Node N = newNode(); //Create Node N.
	N->data = x; //Set Node N data to x.

	if(isEmpty(L)) { //If List L is empty, prepend data as only element.
		L->front = N; //Set List L front to Node N.
		L->back = N; //Set List L back to Node N.
		L->index = -1; //Reset List L index.
	}
	else { //If List L is non empty.
		N->next = L->front; //Prepend Node data x into List L front.
		L->front->prev = N; //Set front previous to Node N.
		L->front = N; //Set List L front to Node N.
		L->index+=1; //Increment List L index by 1.
	}
	L->length+=1; //Increment List L length by 1.
}

void append(List L, int x) { //Insert new element into List L after front element.
	Node N = newNode(); //Create Node N.
	N->data = x; //Set Node N data to x.

	if(isEmpty(L)) { //If List L is empty, append data as only element.
		L->front = N; //Set List L front to Node N.
		L->back = N; //Set List L back to Node N.
	}
	else { //If List L is non empty, append data.
		N->prev = L->back; //Append Node data x into List L back.
		L->back->next = N; //Set back next to Node N.
		L->back = N; //Set List L back to Node N.
	}
	L->length+=1; //Increment List L length by 1.
}

void insertBefore(List L, int x) { //Insert new element before cursor.
	if(L == NULL) { //Check if List L is NULL.
        fprintf(stderr, "InsertBefore List is null.\n");
        exit(EXIT_FAILURE);
    }
	if(length(L) <= 0 || index(L) < 0) { //Pre: length() > 0, index() >= 0.
        fprintf(stderr, "Length/index preconditions are not met.\n");
        exit(EXIT_FAILURE);
    }
	Node N = newNode(); //Create Node N.
	//Set Node pointers.
	N->data = x; //Set Node N data to x.

	if(L->cursor == L->front) { //If List L cursor is at List L front.
		N->prev = NULL; //Set Node N previous to NULL.
		N->next = L->front; //Insert Node x data into List L front.
		L->front->prev = N; //Set List L front previous to Node N.
		L->front = N; //Set List L front to Node N.
	}
	else { //If List L cursor not at List L front, insert N before current curosr.
		N->prev = L->cursor->prev; //Set previous N to List L previous cursor.
		N->next = L->cursor; //Set next Node to List L cursor.
    	L->cursor->prev->next = N; //Set List L next previous cursor to Node N.
    	L->cursor->prev = N; //Set List L previous cursor to Node N.
	}
    L->length+=1; //Increment length by 1.
	L->index+=1; //Increment index by 1.
}

void insertAfter(List L, int x) { //Insert new element after cursor.
	if(L == NULL) { //Check if List L is NULL.
        fprintf(stderr, "InsertAfter List is null.\n");
        exit(EXIT_FAILURE);
    }
	if(length(L) <= 0 || index(L) < 0) { //Pre: length() > 0, index() >= 0.
        fprintf(stderr, "Length/index preconditions are not met.\n");
        exit(EXIT_FAILURE);
    }
	Node N = newNode(); //Create Node N.
	N->data = x; //Set Node N data to x.

	if(L->cursor != L->back) { //If List L cursor next is not NULL.
		N->prev = L->cursor; //Set Node N previous to List L cursor.
		N->next = L->cursor->next; //Set Node N next to List L cursor next.
		L->cursor->next->prev = N; //Set List L cursor next previous equal to Node N.
		L->cursor->next = N; //Set List L cursor next equal to N.
		L->length+=1; //Increment length by 1.
	}
	else { //If List L cursor next is NULL.
		L->cursor->next = N; //Set List L cursor next equal to Node N.
		N->prev = L->cursor; //Set Node N previous to List L cursor.
		L->back = N; //Set List L back equal to Node N.
		L->length+=1; //Increment length by 1.
	}
}

void deleteFront(List L) { //Delete front element.
	if(L == NULL) { //Check if List L is NULL.
        fprintf(stderr, "DeleteFront List is null.\n");
        exit(EXIT_FAILURE);
    }
	if(length(L) <= 0) { //Pre: length() > 0
        fprintf(stderr, "Length preconditions are not met.\n");
        exit(EXIT_FAILURE);
	}
	Node N = L->front; //Set Node N equal to List L front.
	if(length(L) == 1) { //If List L length equals 1.
		L->front = NULL; //Set List L front to NULL.
		L->back = NULL; //Set List L back to NULL.
		L->index = -1; //Reset List L index to -1.
		L->length = 0; //Set List L length to 0.
	}
	else { //Else Node N doesn't equal List L front.
		L->front = N->next; //Set List L front equal to Node N next.
		L->length-=1; //Decrement List L length by 1.
		if(L->index == 0) { //If List L index equals 0.
			L->index = -1; //Reset List L index to -1.
		}
		else { //Else List L index does not equal.
			L->index-=1; //Decrement List L index by 1.
		}
	}
	freeNode(&N); //Free Node N.
}

void deleteBack(List L) { //Delete back element.
	if(L == NULL) { //Check if List L is NULL.
        fprintf(stderr, "DeleteBack List is null.\n");
        exit(EXIT_FAILURE);
    }
	if(length(L) <= 0) { //Pre: length() > 0
        fprintf(stderr, "Length preconditions are not met.\n");
        exit(EXIT_FAILURE);
	}
	Node N = L->back; //Set Node N equal to List L back.
	L->back = N->prev; //Set List L back equal to Node N previous.
	L->length-=1; //Decrement List L length by 1.

	//Check cusor position after deleting.
	if(L->index == length(L)) { //If List L index equals List L length;
		L->index = -1; //Reset List L index to - 1.
	}
	freeNode(&N); //Free Node N.
}

void delete(List L) { //Delete cursor element.
	if(L == NULL || L->cursor == NULL) { //Check if List L or List L cursor is NULL.
        fprintf(stderr, "Delete List is null.\n");
        exit(EXIT_FAILURE);
    }
	if(length(L) <= 0 || index(L) < 0) { //Pre: length() > 0, index() >= 0.
        fprintf(stderr, "Length/index preconditions are not met.\n");
        exit(EXIT_FAILURE);
    }
	Node N = L->cursor; //Set Node N equal to List L cursor
	L->cursor = NULL; //Set List L cursor to NULL

	if(N == L->back) { //If List L cursor equalst List L back.
		L->back = N->prev; //List L back equals Node N previous.
	}
	if(N == L->front) { //If List L cursor equals List L front.
		L->front = N->next; //Set List L front to Node N next.
	}
	else { //Else List L cursor doesn't equal List L front.
		N->prev->next = N->next; //Set Node N previous next equal to Node N next.
	}
	L->length-=1; //Decrement length by 1.

	//When deleting, cursor is -1 eveyrtime.
	L->index = -1; //Reset List L index to -1.

	freeNode(&N); //Free Node N.
}

//Other functions.
void printList(FILE* out, List L) { //Prints to outfile.
	Node N = 0; //Initalize Node N.
	for(N = L->front; N != NULL; N = N->next) { //Loop through each Node in List L.
		fprintf(out, "%d ", N->data); //Print Node N data into  outfile.
	}
}

List copyList(List L) { //Returns a List with same sequence as List L.
	if(L == NULL) { //Check if List L is NULL.
        fprintf(stderr, "CopyList List is null.\n");
        exit(EXIT_FAILURE);
    }
	List NL = newList(); //Create new list NL with newList function.

	Node N = L->front; //Set Node N to the front of List L.
	while(N != NULL) { //While List L is not empty.
		append(NL, N->data); //Append Node data to List NL.
		if(N == L->back) { //If Node N equals the back element of List L.
			break;
		}
		N = N->next; //Set Node N to Node N next.
	}
	return(NL); //Return List NL.
}

//Optional.
List concatList(List A, List B) { //Return concatenated new list of List A and List B
	return(A);
	return(B);
}
