/****************************************************************************************
 * *  pa3 - By: Ryan Hui, rhui1
 * *  Graph.c File
 * *  Graph ADT File
 * *****************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "List.h"
#include "Graph.h"

struct NodeObj { //Struct for Node.
	int data;
	struct NodeObj* prev;
	struct NodeObj* next;
} NodeObj;

typedef struct GraphObj { //Struct for Node.
    List *neighbors; //Array of Lists for ith element for neighbors of vertex i.
    int *color; //Int array for ith element's color for vertex i.
    int *parent; //Int array for ith element's parent of vertex i.
    int order; //Number of vertices.
    int size; //Number of edges.
    int *discover; //Int array for ith element's discover of vertex i.
    int *finish; //Int array for ith element's finish of vertex i.
} GraphObj;

//Helper functions.
bool getEmpty(List Q) { //Returns true if empty.
	if(Q == NULL) { //If List L is empty
		fprintf(stderr, "List is empty\n");
		exit(EXIT_FAILURE);
	}
	return(length(Q) == 0); //Return List L length equals to 0.
}

Graph newGraph(int n) { //Returns a Graph pointing to a newly created GraphObj.
    Graph G = malloc(sizeof(GraphObj)); //Allocate memory for Graph G.
    G->neighbors = calloc(n + 1, sizeof(List)); //Allocate memory for Graph neighbors.
    G->color = calloc(n + 1, sizeof(int)); //Allocate memory for Graph color.
    G->parent = calloc(n + 1, sizeof(int)); //Allocate memory for Graph parent.
    G->discover = calloc(n + 1, sizeof(int)); //Allocate memory for Graph discover.
    G->finish = calloc(n + 1, sizeof(int)); //Allocate memory for Graph finish.
    G->order = n; //Set number of vertices.
    G->size = 0; //Set number of edges to 0.

    //Setting for each element.
    for(int i = 0; i <= n; i += 1) { //Loop through vertices.
        G->neighbors[i] = newList(); //Intialize each element in neighbors with newList().
        G->color[i] = 0; //Set each vertex color to WHITE.
        G->parent[i] = NIL; //Set each vertex parent to NIL.
        G->discover[i] = UNDEF; //Set discover element to UNDEF.
        G->finish[i] = UNDEF; //Set finsih element to UNDEF.
    }
    return G; //Return Graph.
}

void freeGraph(Graph* pG) { //Frees all heap memory in Graph.
    if(pG != NULL && *pG != NULL) { //Checks if pG is not NULL.
		for(int i = 0; i <= (*pG)->order; i+=1) { //Loop through Graph vertices.
            List element = ((*pG)->neighbors[i]); //Set element to ith element of Graph neighbor.
            freeList(&element); //Free each List element in neighbors.
        }
        //Free Graph pointers.
        free((*pG)->neighbors);
        free((*pG)->color);
        free((*pG)->parent);
        free((*pG)->discover);
        free((*pG)->finish);
        free(*pG); //Free *pG.
		*pG = NULL; //Set *pG to NULL.
	}
}

/*** Access functions ***/
int getOrder(Graph G) { //Returns Graph order.
    if(G == NULL) { //Check if Graph is null.
		fprintf(stderr, "Order Graph is null\n");
		exit(EXIT_FAILURE);
    }
    return(G->order);
}

int getSize(Graph G) { //Returns Graph size.
    if(G == NULL) { //Check if Graph is null.
		fprintf(stderr, "Size Graph is null\n");
		exit(EXIT_FAILURE);
    }
    return(G->size);
}

int getParent(Graph G, int u) { //Return Graph parent.
    if(G == NULL) { //Check if Graph is null.
		fprintf(stderr, "Parent Graph is null\n");
		exit(EXIT_FAILURE);
    }
    if(u < 1 || u > getOrder(G)) { //Precondition u must be in range 1 and getOrder(G).
        fprintf(stderr, "Parent Failed precondition.\n");
        exit(EXIT_FAILURE);
    }
    return(G->parent[u]);
}

int getDiscover(Graph G, int u) { //Return Graph discover.
    if(G == NULL) { //Check if Graph is null.
		fprintf(stderr, "Discover Graph is null\n");
		exit(EXIT_FAILURE);
    }
    if(u < 1 || u > getOrder(G)) { //Precondition u must be in range 1 and getOrder(G).
        fprintf(stderr, "Discover Failed precondition.\n");
        exit(EXIT_FAILURE);
    }
    return(G->discover[u]);
}

int getFinish(Graph G, int u) { //Return Graph finish.
    if(G == NULL) { //Check if Graph is null.
		fprintf(stderr, "Finish Graph is null\n");
		exit(EXIT_FAILURE);
    }
    if(u < 1 || u > getOrder(G)) { //Precondition u must be in range 1 and getOrder(G).
        fprintf(stderr, "Finish Failed precondition.\n");
        exit(EXIT_FAILURE);
    }
    return(G->finish[u]);
}

/*** Manipulation procedures ***/
void addEdge(Graph G, int u, int v) { //Inserts new edge joining u to v. Add u to adjacency List of v, add v to adjacency List of u.
    if(G == NULL) { //Check if Graph is null.
		fprintf(stderr, "Edge Graph is null\n");
		exit(EXIT_FAILURE);
    }
    if(u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)) { //Precondition u and v must be in range 1 to getOrder(G).
        fprintf(stderr, "Edge Failed precondition u and v must be in range of 1 to getOrder(G).\n");
        exit(EXIT_FAILURE);
    }
    List LU = G->neighbors[u]; //Set List LU equal to G neighbors for the u element.
    List LV = G->neighbors[v]; //Set List LV equal to G neighbors for the v element.
    moveFront(LU); //Move cursor to the front of List LU.
    moveFront(LV); //Move cursor to the front of List LV.

    //Maintain lists in sorted order by increasing labels.
    while (index(LU) >= 0 && get(LU) < v) { //Loop through List LU.
        moveNext(LU);
    }
    if(getEmpty(LU)) { //If List LU is empty.
        append(LU, v); //Append v to List LU.
    }
    else { //Else List LU is not empty.
        if (index(LU) == -1) { //If cursor is undefined in LU.
            append(LU, v); //Append v to List LU.
        }
        else { //Else cursor is defined in LU.
            insertBefore(LU, v); //Insert v before cursor for List LU.
        }
    }

    //Maintain lists in sorted order by increasing labels.
    while (index(LV) >= 0 && get(LV) < u) { //Loop through List LV.
        moveNext(LV);
    }
    if(getEmpty(LV)) { //If List LV is empty.
        append(LV, u); //Append v to List LV.
    }
    else { //Else List LV is not empty.
        if (index(LV) == -1) { //If cursor is undefined in LV.
        append(LV, u); //Append u to List LU.
        }
        else { //Else cursor is defined in LV.
        insertBefore(LV, u); //Insert u before cursor for List LV.
        }
    }
    G->size += 1; //Increment the number of edges by 1.
}

void addArc(Graph G, int u, int v) { //Insert new directed edge from u to v. Add v to adjacency List of u.
    if(G == NULL) { //Check if Graph is null.
		fprintf(stderr, "Arc Graph is null\n");
		exit(EXIT_FAILURE);
    }
    if(u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)) { //Precondition u and v must be in range 1 to getOrder(G).
        fprintf(stderr, "Arc Failed precondition u and v must be in range of 1 to getOrder(G).\n");
        exit(EXIT_FAILURE);
    }
    List LU = G->neighbors[u]; //Set List LU equal to G neighbors for the u element.
    moveFront(LU); //Move cursor to the front of List LU.

    //Check before adding arc in case of duplicate.
    for (moveFront(LU); index(LU) >= 0; moveNext(LU)) { //Loop through adjacency List LU.
        if (get(LU) == v) { //If element LU equals v, there is a duplicate.
            return; //Do nothing.
        }
    }
    moveFront(LU); //Reset cursor.

    //Maintain lists in sorted order by increasing labels.
    while (index(LU) >= 0 && get(LU) < v) { //Loop through List LU.
        moveNext(LU);
    }
    if(getEmpty(LU)) { //If List LU is empty.
        append(LU, v); //Append v to List LU.
    }
    else { //Else List LU is not empty.
        if (index(LU) == -1) { //If cursor is undefined in LU.
            append(LU, v); //Append v to List LU.
        }
        else { //Else cursor is defined in LU.
            insertBefore(LU, v); //Insert v before cursor for List LU.
        }
    }
    G->size += 1; //Increment the number of edges by 1.
}

void visit(Graph G, List S, int *time, int x) { //Visit all children of a given vertex and assigns the color.
   //Implement visit pseudocode.
    //Intialize variable.
    int y = 0;

    G->discover[x] = (++(*time)); //Set discover to ++time.
    G->color[x] = 1; //Set color to gray.

    for(moveFront(G->neighbors[x]); index(G->neighbors[x]) >= 0; moveNext(G->neighbors[x])) { //Loop through adjacency List for x.
        y = (get(G->neighbors[x])); //For y in List Q x.
        if(G->color[y] == 0) { //If color is white.
                G->parent[y] = x; //Set y parent to x.
                visit(G, S, time, y); //Call visit on y.
        }
    }
    G->color[x] = 2; //Set color to black.
    prepend(S, x); //Visited black color and add to stack.
    G->finish[x] = (++(*time)); //Set finish to ++time.
}

void DFS(Graph G, List S) { //Performs Depth First Search
    //Implement DFS pseudocode.
    //Intialize variables.
    int SL = length(S); //Set SL equal to length of List S.
    int x = 0;
    for(x = 0; x <= getOrder(G); x += 1) { //Loop through adjacent List S for x.
        G->color[x] = 0; //Color is white.
        G->parent[x] = NIL; //Parent is NIL.
    }
    int time = 0; //Set time equal to 0.
    for(moveFront(S); index(S) >= 0; moveNext(S)) { //Loop through adjacent List S for x.
        x = (get(S)); //For x in List S.
        if(G->color[x] == 0) { //If color is white.
            visit(G, S, &time, x); //Visit x.
        }
    }
    for(int i = 0; i < SL; i += 1) { //Loop through S length.
        deleteBack(S); //Clear back List values.
    }
}

// Other Functions
Graph transpose(Graph G) { //Returns a reference to a new graph object representing transpose of Graph G.
    Graph GT = newGraph(getOrder(G)); //Create new Graph GT with vertices of G.
    int y = 0;

    for(int x = 1; x <= getOrder(G); x += 1) { //Loop through vertices in Graph G.
        for (moveFront(G->neighbors[x]); index(G->neighbors[x]) >= 0; moveNext(G->neighbors[x])) { //Loop through adjacency List for x.
            y = (get(G->neighbors[x])); //For y in List Q x.
            addArc(GT, y, x); //Add arc from Graph G to Grag GT.
        }
    }
    return(GT);
}

Graph copyGraph(Graph G) { //Returns a reference to a new graph that is a copy of Graph G.
    Graph GC = newGraph(getOrder(G)); //Create new Graph GT with vertices of G.

    for(int x = 1; x <= getOrder(G); x += 1) { //Loop through vertices in Graph G.
        //Copy over adjacency List for x.
        for(moveFront(G->neighbors[x]); index(G->neighbors[x]) >= 0; moveNext(G->neighbors[x])) { //Loop through adjacency List for x.
            addArc(GC, x, get(G->neighbors[x])); //Copy over Graph G arc to Graph GC.
        }

        //Copy over pointers from Graph G to GC.
        GC->color[x] = G->color[x];
        GC->parent[x] = G->parent[x];
        GC->discover[x] = G->discover[x];
        GC->finish[x] = G->finish[x];
    }
    return(GC);
}

void printGraph(FILE* out, Graph G) { //Prints the Graph.
    for(int i = 1; i <= getOrder(G); i += 1) { //Loops through vertices.
        fprintf(out, "%d: ", i); //Print vertex.
        for (moveFront(G->neighbors[i]); index(G->neighbors[i]) >= 0; moveNext(G->neighbors[i])) { //Loop through List neighbors.
           fprintf(out, "%d ", get(G->neighbors[i])); //Print neighbor's vertex.
        }
        fprintf(out, "\n"); //New line after each pair.
    }
}
