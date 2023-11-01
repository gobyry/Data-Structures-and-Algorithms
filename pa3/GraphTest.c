/****************************************************************************************
 * *  pa3 - By: Ryan Hui, rhui1
 * *  GraphTest.c File
 * *  Graph Test File
 * *****************************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>
#include"List.h"
#include"Graph.h"


int main(int argc, char* argv[]){
   int i, n=16;
   List S = newList();
   Graph G = newGraph(n);
   Graph T=NULL, C=NULL;

   for(i=1; i<=n; i++) append(S, i);

   //Adds to 1-16.
   for(i = 1; i <= n; i += 1) { //Adds arc to Graph G.
      addArc(G, i, 1);
   }

   addArc(G, 1,2);
   addArc(G, 1,5);
   addArc(G, 2,5);
   addArc(G, 2,6);
   addArc(G, 3,2);
   addArc(G, 3,4);
   addArc(G, 3,6);
   addArc(G, 3,7);
   addArc(G, 3,8);
   addArc(G, 6,5);
   addArc(G, 6,7);
   addArc(G, 8,4);
   addArc(G, 8,7);

   //Populate 8-16.
   for(i = 8; i < n; i += 1) {
      addArc(G, i, 2);
   }

   printf("Graph G:\n");
   printGraph(stdout, G);

   DFS(G, S);
   Graph GC = copyGraph(G);

   fprintf(stdout, "\n");
   printf("Graph G after DFS:\n");
   printGraph(stdout, GC);

   Graph GT = transpose(GC);
   fprintf(stdout, "\n");
   printf("Graph GC Transposing:\n");
   printGraph(stdout, GT);

   fprintf(stdout, "\n");
   fprintf(stdout, "Stats of Graph G.\n");
   fprintf(stdout, "x:  d  f  p\n");
   for(i=1; i<=n; i++){
      fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(G, i), getFinish(G, i), getParent(G, i));
   }
   fprintf(stdout, "\n");
   printList(stdout, S);
   fprintf(stdout, "\n");

   T = transpose(G);
   C = copyGraph(G);
   fprintf(stdout, "\n");
   printGraph(stdout, C);
   fprintf(stdout, "\n");
   printGraph(stdout, T);
   fprintf(stdout, "\n");

   DFS(T, S);
   fprintf(stdout, "\n");
   fprintf(stdout, "Stats of Transposed Graph G.\n");
   fprintf(stdout, "x:  d  f  p\n");
   for(i=1; i<=n; i++){
      fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(T, i), getFinish(T, i), getParent(T, i));
   }
   fprintf(stdout, "\n");
   printList(stdout, S);
   fprintf(stdout, "\n");

   freeList(&S);
   freeGraph(&G);
   freeGraph(&T);
   freeGraph(&C);
   return(0);


}

