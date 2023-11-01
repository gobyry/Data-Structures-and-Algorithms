/****************************************************************************************
 * *  pa3 - By: Ryan Hui, rhui1
 * *  FindComponents.c File
 * *  DFS Program File
 * *****************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "List.h"
#include "Graph.h"

int main(int argc, char* argv[]) {

	//Initialize file pointers.
	FILE *in = NULL;
	FILE *out = NULL;

    //Declare variables.
    int n = 0; //Graph size variable.
    int u = 0; //Vertex variable.
    int v = 0; //Edge variable.
    int component = 0; //Component variable.

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
    Graph G = newGraph(n); //Create new Graph G.
    List S = newList(); //Create new List S.

    //Loop through size of Graph.
    for(int i = 1; i <= n; i += 1) {
        append(S, i); //Append and fill List S with i.
    }

     //Loop and scan through infile.
    while(fscanf(in, "%d %d", &u, &v) != EOF && (u != 0 && v != 0)) { //Scan until EOF and reached last two 0s.
        addArc(G, u, v); //Add arc to scanned integers
    }

    //Print Graph G to outfile.
    fprintf(out, "Adjacency list representation of G:\n");
    printGraph(out, G);
    fprintf(out, "\n");

    //Create and transpose Graph GT with Graph G.
    Graph GT = transpose(G);

    //Run DFS on G.
    DFS(G, S);

    //Run DFS on GT.
    DFS(GT, S);

    //Loop through and process vertices in Graph GT
    for(int i = 1; i <= getOrder(GT); i += 1) { //Loop through vertices in Graph GT.
        if(getParent(GT, i) == NIL) { //If GT parent is NIL.
            component += 1;
        }
    }
    int temp = component; //Set temp variable to component.

    //Print components.
    fprintf(out, "G contains %d strongly connected components:\n", component);

    //Create new List allocate memory to length of strong components.
    List *CL = calloc(component, sizeof(List)); //Allocate memory for Graph neighbors.

    //Loop through strong components.
    for(int i = 0; i < component; i += 1) {
        CL[i] = newList(); //Create new List of Lists CL for strong components.
    }

    //Loop through List S.
    for(moveFront(S); index(S) >= 0; moveNext(S)) {
        if(getParent(GT, get(S)) == NIL) { //If List value has no parents.
            component -= 1; //Decrement component by 1.
        }
         //Else List value has parents.
        if(component >= 0) { //If temp is not negative.
            append(CL[component], get(S)); //Append S value for component temp index.
        }
    }

    int num = 1;
    //Loop through components and print statment and List CL.
    for(int i = 0; i < temp; i += 1) { //Loop through stored component value.
        fprintf(out, "Component %d: ", num);
        printList(out, CL[i]); //Print component list.
        fprintf(out, "\n");
        num += 1; //Increment component number by 1.
    }
    fprintf(out, "\n");

    //Free memory allocated.
    freeGraph(&G); //Free Graph G.
    freeGraph(&GT); //Free Graph GT.

    //Loop through List of Lists CL and free each List pointer.
    for(int i = 0; i < temp; i += 1) {
        freeList(&CL[i]);
    }
    freeList(&S); //Free List S.
    freeList(CL); //Free List CL.
    free(CL); //Free List CL again.

    //Close infile and outfile.
    fclose(in);
    fclose(out);

    return 0;
}
