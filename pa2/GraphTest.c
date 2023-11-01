/****************************************************************************************
 * *  pa2 - By: Ryan Hui, rhui1
 * *  GraphTest.c File
 * *  Graph Test File
 * *****************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Graph.h"
#include "List.h"

int main(int argc, char* argv[]){
   //Intializes variables and creates the 3 lists.
   int i, d, n=50;
   Graph G = NULL;

   // Build graph G
   G = newGraph(n); //Graph size of 50.
   for(i=1; i<n; i++){ //Loop through 1 to 50 vertices.
      if( i%5!=0 ) addEdge(G, i, i+1); //Adds edge based on the condition.
      if( i<=25  ) addEdge(G, i, i+5); //Adds edge based on the condition.
   }
   //Adds edges to the following vertices.
   addEdge(G, 1, 5); //Adds edge 5 to 1st vertex.
   addEdge(G, 10, 15); //Adds edge 15 to 10th vertex.
   addEdge(G, 45, 50); //Adds edge 50 to 45th vertex.

   // Print adjacency list representation of G
   printf("Graph G\n");
   printGraph(stdout, G);

   //Build Graph H
   int x = 20;
   Graph H = NULL;
   H = newGraph(x); //Graph size of 20.
   for(i=1; i<n; i++){ //Loop through 1 to 10 vertices.
      if(i <= 10) {
         addEdge(H, i+1, i+2);
         addEdge(H, i+2, i+3);
      }
      if(i >= 10 && i < 20) {
         addEdge(H, i, i + 1);
      }
   }
   addEdge(H, 20, 20); //Adds edge 20 to 20th vertex.
   addEdge(H, 1, 1); //Adds edge 1 to 1st vertex.
   addEdge(H, 10, 10); //Adds edge 10 to 10th vertex.

   // Print adjacency list representation of H
   printf("\n");
   printf("Graph H.\n");
   printGraph(stdout, H);

   addArc(G, 20, 19); //Testing addArc function.
   addArc(H, 20, 19);
   addArc(G, 3, 4);
   addArc(H, 6, 8);

   printf("\n");
   int j;
   //Breadth First Search
   printf("Distance between sources for Graph G (BFS).\n");
   for(i = 1; i < n; i += 1) {
      BFS(G, i);
      for(j = 0; j < n; j += 2) {
      }
      d = getDist(G, j);
      printf("%d ", d);
   }
   printf("\n");
   printf("\n");


   printf("Distance between sources for Graph H (BFS).\n");
   for(i = 1; i < x; i += 1) {
      BFS(H, i);
      for(j = 0; j < x; j += 2) {
      }
      d = getDist(H, j);
      printf("%d ", d);
   }
   printf("\n");

   printf("\n");
   printf("Printing Graph G and H with BFS.\n");

   printf("\n");
   printf("Graph G.\n");
   printGraph(stdout, H);

   printf("\n");
   printf("Graph H.\n");
   printGraph(stdout, H);

   printf("\n");
   printf("Get Path for Graph G (Vertex 45).\n");

   List L = newList();
   i = 45;
   getPath(L, G, i);
   printList(stdout, L);
   clear(L);

   printf("\n");
   printf("Get Path for Graph H (Vertex 15).\n");

   i = 15;
   getPath(L, H, i);
   printList(stdout, L);

   int p1 = getParent(G, i);
   int p2 = getParent(H, i);

   printf("\n");
   printf("\n");
   printf("Printing Parents for Graph G (v = 45) and H (v = 15).\n");
   printf("Parent of G is %d.\n", p1);
   printf("Parent of H is %d.\n", p2);

   p1 = getSource(G);
   p2 = getSource(H);

   printf("\n");
   printf("Printing Sources for Graph G and H.\n");
   printf("Source of G is %d.\n", p1);
   printf("Source of H is %d.\n", p2);

   p1 = getOrder(G);
   p2 = getOrder(H);
   int p3 = getSize(G);
   int p4 = getSize(H);
   printf("\n");
   printf("Printing Order and Size for Graph G and H.\n");
   printf("Order of G is %d.\n", p1);
   printf("Order of H is %d.\n", p2);
   printf("Size of G is %d.\n", p3);
   printf("Size of H is %d.\n", p4);

   printf("\n");
   // Free objects
   printf("Make NULL.\n");
   makeNull(G);
   makeNull(H);

   printf("Print NULLed Graph G.\n");
   printGraph(stdout, G);

   printf("\n");
   printf("Print NULLed Graph H.\n");
   printGraph(stdout, H);

   printf("\n");
   printf("Free Graph.\n");
   freeGraph(&G);
   freeGraph(&H);

   return(0);
}

/* OUTPUT
Graph G
1: 2 5 6
2: 1 3 7
3: 2 4 8
4: 3 5 9
5: 1 4 10
6: 1 7 11
7: 2 6 8 12
8: 3 7 9 13
9: 4 8 10 14
10: 5 9 15 15
11: 6 12 16
12: 7 11 13 17
13: 8 12 14 18
14: 9 13 15 19
15: 10 10 14 20
16: 11 17 21
17: 12 16 18 22
18: 13 17 19 23
19: 14 18 20 24
20: 15 19 25
21: 16 22 26
22: 17 21 23 27
23: 18 22 24 28
24: 19 23 25 29
25: 20 24 30
26: 21 27
27: 22 26 28
28: 23 27 29
29: 24 28 30
30: 25 29
31: 32
32: 31 33
33: 32 34
34: 33 35
35: 34
36: 37
37: 36 38
38: 37 39
39: 38 40
40: 39
41: 42
42: 41 43
43: 42 44
44: 43 45
45: 44 50
46: 47
47: 46 48
48: 47 49
49: 48 50
50: 45 49

Graph H.
1: 1 1
2: 3
3: 2 4 4
4: 3 3 5 5
5: 4 4 6 6
6: 5 5 7 7
7: 6 6 8 8
8: 7 7 9 9
9: 8 8 10 10
10: 9 9 10 10 11 11 11
11: 10 10 10 12 12 12
12: 11 11 11 13 13
13: 12 12 14
14: 13 15
15: 14 16
16: 15 17
17: 16 18
18: 17 19
19: 18 20
20: 19 20 20

Distance between sources for Graph G (BFS).
-1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 5 4 3 2 1 4 3 2 1

Distance between sources for Graph H (BFS).
-1 17 16 15 14 13 13 12 11 10 9 8 7 6 5 4 3 2 1

Printing Graph G and H with BFS.

Graph G.
1: 1 1
2: 3
3: 2 4 4
4: 3 3 5 5
5: 4 4 6 6
6: 5 5 7 7 8
7: 6 6 8 8
8: 7 7 9 9
9: 8 8 10 10
10: 9 9 10 10 11 11 11
11: 10 10 10 12 12 12
12: 11 11 11 13 13
13: 12 12 14
14: 13 15
15: 14 16
16: 15 17
17: 16 18
18: 17 19
19: 18 20
20: 19 19 20 20

Graph H.
1: 1 1
2: 3
3: 2 4 4
4: 3 3 5 5
5: 4 4 6 6
6: 5 5 7 7 8
7: 6 6 8 8
8: 7 7 9 9
9: 8 8 10 10
10: 9 9 10 10 11 11 11
11: 10 10 10 12 12 12
12: 11 11 11 13 13
13: 12 12 14
14: 13 15
15: 14 16
16: 15 17
17: 16 18
18: 17 19
19: 18 20
20: 19 19 20 20

Get Path for Graph G (Vertex 45).
49 50 45
Get Path for Graph H (Vertex 15).
19 18 17 16 15

Printing Parents for Graph G (v = 45) and H (v = 15).
Parent of G is 0.
Parent of H is 16.

Printing Sources for Graph G and H.
Source of G is 49.
Source of H is 19.

Printing Order and Size for Graph G and H.
Order of G is 50.
Order of H is 20.
Size of G is 70.
Size of H is 35.

Make NULL.
Print NULLed Graph G.
1:
2:
3:
4:
5:
6:
7:
8:
9:
10:
11:
12:
13:
14:
15:
16:
17:
18:
19:
20:
21:
22:
23:
24:
25:
26:
27:
28:
29:
30:
31:
32:
33:
34:
35:
36:
37:
38:
39:
40:
41:
42:
43:
44:
45:
46:
47:
48:
49:
50:

Print NULLed Graph H.
1:
2:
3:
4:
5:
6:
7:
8:
9:
10:
11:
12:
13:
14:
15:
16:
17:
18:
19:
20:

Free Graph.
*/
