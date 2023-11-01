/****************************************************************************************
 * *  pa7 - By: Ryan Hui, rhui1
 * *  Order.cpp
 * *  Order Program file
 * *****************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sstream>
#include <string.h>
#include <iostream>
#include <fstream>
#include <string>
#include "Dictionary.h"

using namespace std;

int main(int argc, char * argv[]) {

    // Initialize file pointers.
	ifstream in;
   	ofstream out;

    // Check if 3 arguments are inputted.
	if(argc != 3) {
      cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
      return(EXIT_FAILURE);
   	}

	// Open infile for reading.
   	in.open(argv[1]);
   	if(!in.is_open()) {
      cerr << "Unable to open file " << argv[1] << " for reading" << endl;
      return(EXIT_FAILURE);
   	}

	// Open outfile for writing.
   	out.open(argv[2]);
   	if(!out.is_open()) {
      cerr << "Unable to open file " << argv[2] << " for writing" << endl;
      return(EXIT_FAILURE);
   	}

    // Intialize dictionary, string variables, and counter.
    Dictionary D;
    string lines;
    string lines1;
    string lines2;
    int counter = 1;

    // Loop to set dictionary values.
    while(getline(in, lines)) {
        D.setValue(lines, counter);
        counter += 1;
    }

    // Set string outputs.
    lines1 = D.to_string();
    lines2 = D.pre_string();

    // Output dictionary string values to outfile.
    out << lines1 << "\n";
    out << lines2 << "\n";

    // Close infile and outfile.
    in.close();
    out.close();

    return 0;
}

