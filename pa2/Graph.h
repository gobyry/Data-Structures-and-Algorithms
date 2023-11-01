/****************************************************************************************
 * *  pa2 - By: Ryan Hui, rhui1
 * *  Graph.h File
 * *  Graph Header File
 * *****************************************************************************************/

#pragma once

/*** Constants ***/
#define INF -1 //Negative int value.
#define NIL 0 //Non-positive int value.

typedef struct NodeObj* Node; //Define Node.

typedef struct ListObj* List; //Define List.

typedef struct GraphObj* Graph; //Define Graph.

/*** Constructors-Destructors ***/
Graph newGraph(int n);

void freeGraph(Graph* pG);

/*** Access functions ***/
int getOrder(Graph G);

int getSize(Graph G);

int getSource(Graph G);

int getParent(Graph G, int u);

int getDist(Graph G, int u);

void getPath(List L, Graph G, int u);

/*** Manipulation procedures ***/
void makeNull(Graph G);

void addEdge(Graph G, int u, int v);

void addArc(Graph G, int u, int v);

void BFS(Graph G, int s);

/*** Other operations ***/
void printGraph(FILE* out, Graph G);
