/****************************************************************************************
 * *  pa2 - By: Ryan Hui, rhui1
 * *  FindPath.c File
 * *  Find Path Program File
 * *****************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Graph.h"
#include "List.h"

#define MAX_LEN 300

int main(int argc, char* argv[]) {

	//Initialize file pointers.
	FILE *in = NULL;
	FILE *out = NULL;

    //Declare variables.
    int n = 0; //Graph size variable.
    int u = 0; //Vertex variable.
    int v = 0; //Edge variable.
    int d = 0; //Distance variable.

    //Command line checking.
	if(argc != 3) { //If there are not 2 command line arguments.
		fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]); //Print error message.
		exit(EXIT_FAILURE);
	}

	//Open infile.
	in = fopen(argv[1], "r");
      	if(in == NULL) { //If infile is NULL, print error message.
      		fprintf(stderr, "Unable to open file %s for reading\n", argv[1]);
      		exit(EXIT_FAILURE);
   	}

	//Open outfile.
	out = fopen(argv[2], "w");
   	if(out == NULL) { //If outfile is NULL, print error message.
      		fprintf(stderr, "Unable to open file %s for writing\n", argv[2]);
      		exit(EXIT_FAILURE);
   	}

    //Perform first scan of infile for size of graph.
    fscanf(in, "%d", &n);

    //Create Graph G with scanned infile size.
    Graph G = newGraph(n); //Create new Graph.
    List L = newList(); //Create new List L.

    //Loop and scan through infile.
    while(fscanf(in, "%d %d", &u, &v) != EOF && (u != 0 && v != 0)) { //Scan until EOF and reached last two 0s.
        addEdge(G, u, v); //Add edges to scanned integers
    }

    //Print graph to outfile.
    printGraph(out, G);
    fprintf(out, "\n");

    //Loop and scan through infile to print statments.
    while(fscanf(in, "%d %d", &u, &v) != EOF && (u != 0 && v != 0)) { //Scan until EOF and reached last two 0s.
        BFS(G, u); //Call BFS on scanned vertex.
        d = getDist(G, v); //Get distance.

        //If distance is infinite, print statments.
        if(d == INF) {
            fprintf(out, "The distance from %d to %d is infinity\n", u, v);
            fprintf(out, "No %d-%d path exists\n", u, v);
            fprintf(out, "\n");
        }
        else {
            //Print out distance
            fprintf(out, "The distance from %d to %d is %d\n", u, v, d);

            //Get shortest path of parent to source vertex and print statement.
            getPath(L, G, v);
            fprintf(out, "A shortest %d-%d path is: ", u, v);
            printList(out, L);
            fprintf(out, "\n");
            clear(L); //Clear List for the next print path.
            fprintf(out, "\n");
        }
    }

    //Free memory allocated.
    makeNull(G); //Null out Graph G.
    freeGraph(&G); //Free Graph G.
    freeList(&L); //Free List L.

    //Close infile and outfile.
    fclose(in);
    fclose(out);

    return 0;
}

