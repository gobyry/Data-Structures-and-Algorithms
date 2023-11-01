/****************************************************************************************
 * *  pa2 - By: Ryan Hui, rhui1
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

struct ListObj { //Struct for List.
	Node front;
	Node back;
	Node cursor;
	int length;
	int index;
	int data;
} ListObj;

typedef struct GraphObj { //Struct for Node.
    List *neighbors; //Array of Lists for ith element for neighbors of vertex i.
    int *color; //Int array for ith element's color for vertex i.
    int *parent; //Int array for ith element's parent of vertex i.
    int *distance; //Int array for ith element distance from vertext i.
    int order; //Number of vertices.
    int size; //Number of edges.
    int source; //Last used source vertex.
} GraphObj;

//Helper functions.
bool getEmpty(List Q) { //Returns true if empty.
	if(Q == NULL) { //If List L is empty
		fprintf(stderr, "List is empty\n");
		exit(EXIT_FAILURE);
	}
	return(Q->length == 0); //Return List L length equals to 0.
}

Graph newGraph(int n) { //Returns a Graph pointing to a newly created GraphObj.
    Graph G = malloc(sizeof(GraphObj)); //Allocate memory for Graph G.
    G->neighbors = calloc(n + 1, sizeof(ListObj)); //Allocate memory for Graph neighbors.
    G->color = calloc(n + 1, sizeof(int)); //Allocate memory for Graph color.
    G->parent = calloc(n + 1, sizeof(int)); //Allocate memory for Graph parent.
    G->distance = calloc(n + 1, sizeof(int)); //Allocate memory for Graph distance.
    G->order = n; //Set number of vertices.
    G->size = 0; //Set number of edges to 0.
    G->source = NIL; //Set last used vertex to NIL.

    //Setting for each element.
    for(int i = 0; i <= n; i += 1) { //Loop through vertices.
        G->neighbors[i] = newList(); //Intialize each element in neighbors with newList().
        G->color[i] = 0; //Set each vertex color to WHITE.
        G->parent[i] = NIL; //Set each vertex parent to NIL.
        G->distance[i] = INF; //Set each vertex distance to INF.
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
        free((*pG)->distance);
        free(*pG); //Free *pG.
		*pG = NULL; //Set *pG to NULL.
	}
}

/*** Access functions ***/
int getOrder(Graph G) { //Returns Graph order.
    if(G == NULL) { //Check if Graph is null.
		fprintf(stderr, "Graph is null\n");
		exit(EXIT_FAILURE);
    }
    return(G->order);
}

int getSize(Graph G) { //Returns Graph size.
    if(G == NULL) { //Check if Graph is null.
		fprintf(stderr, "Graph is null\n");
		exit(EXIT_FAILURE);
    }

    return(G->size);
}

int getSource(Graph G) { //Return Graph source.
    if(G == NULL) { //Check if Graph is null.
		fprintf(stderr, "Graph is null\n");
		exit(EXIT_FAILURE);
    }
    return(G->source);
}

int getParent(Graph G, int u) { //Return Graph parent.
    if(G == NULL) { //Check if Graph is null.
		fprintf(stderr, "Graph is null\n");
		exit(EXIT_FAILURE);
    }
    if(u < 1 || u > getOrder(G)) { //Precondition u must be in range 1 and getOrder(G).
        fprintf(stderr, "Failed precondition.\n");
        exit(EXIT_FAILURE);
    }
    return(G->parent[u]);
}

int getDist(Graph G, int u) { //Returns the distance from most recent source or INF if BFS() hasn't been called.
    if(G == NULL) { //Check if Graph is null.
		fprintf(stderr, "Graph is null\n");
		exit(EXIT_FAILURE);
    }
    if(u < 1 || u > getOrder(G)) { //Precondition u must be in range 1 and getOrder(G).
        fprintf(stderr, "Failed precondition.\n");
        exit(EXIT_FAILURE);
    }
    if(getSource(G) == NIL) { //If BFS() hasn't been called.
        return INF; //Return NULL.
    }
    return(G->distance[u]);
}

void getPath(List L, Graph G, int u) { //Appends List L the vertices to the shortest path in G or NIL if path doesn't exist.
    if(G == NULL) { //Check if Graph is null.
		fprintf(stderr, "Graph is null\n");
		exit(EXIT_FAILURE);
    }
    if(u < 1 || u > getOrder(G)) { //Precondition u must be in range 1 and getOrder(G).
        fprintf(stderr, "Failed precondition 1 <= u <= getOrder(G).\n");
        exit(EXIT_FAILURE);
    }
    if(getSource(G) == NIL) { //Precondition getSource(G) != NIL.
        fprintf(stderr, "Failed precondition getSource(G) != NIL.\n");
        exit(EXIT_FAILURE);
    }
    if(u == getSource(G)) { //If vertex u is shortest path to G.
        append(L, u); //Append vertex u to List L.
    }
    else if(getDist(G, u) == INF ) { //If path in G doesn't exist.
        append(L, NIL); //Append NIL to List L.
    }
    else { //Else find path from u to vertex.
        int parent = getParent(G, u); //Set parent value.
        getPath(L, G, parent); //Call getPath.
        append(L, u); //Append vertex u to List L.
    }
}

/*** Manipulation procedures ***/
void makeNull(Graph G) { //Deletes all edges in G and restores to no edge state.
    if(G == NULL) { //Check if Graph is null.
		fprintf(stderr, "Graph is null\n");
		exit(EXIT_FAILURE);
    }
    for(int i = 0; i <= getOrder(G); i += 1) { //Loop through number of vertices in G.
        clear(G->neighbors[i]); //Clear neighbors of the vertex for each ith element.
    }
    G->size = 0; //Set G vertices to 0.
}

void addEdge(Graph G, int u, int v) { //Inserts new edge joining u to v. Add u to adjacency List of v, add v to adjacency List of u.
    if(G == NULL) { //Check if Graph is null.
		fprintf(stderr, "Graph is null\n");
		exit(EXIT_FAILURE);
    }
    if(u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)) { //Precondition u and v must be in range 1 to getOrder(G).
        fprintf(stderr, "Failed precondition u and v must be in range of 1 to getOrder(G).\n");
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
		fprintf(stderr, "Graph is null\n");
		exit(EXIT_FAILURE);
    }
    if(u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)) { //Precondition u and v must be in range 1 to getOrder(G).
        fprintf(stderr, "Failed precondition u and v must be in range of 1 to getOrder(G).\n");
        exit(EXIT_FAILURE);
    }
    List LU = G->neighbors[u]; //Set List LU equal to G neighbors for the u element.
    moveFront(LU); //Move cursor to the front of List LU.

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

void BFS(Graph G, int s) { //Runs Breadth First Search algorithm on Graph G.
    //Follow the pseudocode for BFS
    int x = 0;
    int y = 0;

    for(x = 0; x <= getOrder(G); x += 1) { //Loop through vertices.
         if(x != s) { //Exclude s.
            G->color[x] = 0; //Color is white.
            G->distance[x] = INF;
            G->parent[x] = NIL;
         }
    }
    G->color[s] = 1; //Color is gray.
    G->distance[s] = 0;
    G->parent[s] = NIL;
    List Q = newList(); //Create new List Q.
    append(Q, s);
    while(!getEmpty(Q)) { //While List Q is not empty.
        x = front(Q);
        deleteFront(Q);
        for (moveFront(G->neighbors[x]); index(G->neighbors[x]) >= 0; moveNext(G->neighbors[x])) { //Loop through adjacent List Q for x.
            y = (get(G->neighbors[x])); //For y in List Q x.
            if(G->color[y] == 0) { //Color is white.
                G->color[y] = 1; //Color is gray.
                G->distance[y] = G->distance[x] + 1;
                G->parent[y] = x;
                append(Q, y);
            }
        }
        G->color[x] = 2; //Color is black.
    }
    G->source = s; //Set source to s.
    freeList(&Q); //Free List Q.
}

/*** Other operations ***/
void printGraph(FILE* out, Graph G) { //Prints the Graph.
    for(int i = 1; i <= getOrder(G); i += 1) { //Loops through vertices.
        fprintf(out, "%d: ", i); //Print vertex.
        for (moveFront(G->neighbors[i]); index(G->neighbors[i]) >= 0; moveNext(G->neighbors[i])) { //Loop through List neighbors.
           fprintf(out, "%d ", get(G->neighbors[i])); //Print neighbor's vertex.
        }
        fprintf(out, "\n"); //New line after each pair.
    }
}
