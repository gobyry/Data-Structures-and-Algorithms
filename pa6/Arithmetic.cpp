/****************************************************************************************
 * *  pa6 - By: Ryan Hui, rhui1
 * *  Arithmetic.cpp
 * *  Arithmetic Program File
 * *****************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <fstream>
#include "List.h"
#include "BigInteger.h"

using namespace std;

int main(int argc, char * argv[]) {

    // Initialize file pointers.
	ifstream in;
   	ofstream out;

    // Check if 3 arguments are inputted.
	if( argc != 3 ){
      cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
      return(EXIT_FAILURE);
   	}

	// Open infile for reading.
   	in.open(argv[1]);
   	if( !in.is_open() ){
      cerr << "Unable to open file " << argv[1] << " for reading" << endl;
      return(EXIT_FAILURE);
   	}

	// Open outfile for writing.
   	out.open(argv[2]);
   	if( !out.is_open() ){
      cerr << "Unable to open file " << argv[2] << " for writing" << endl;
      return(EXIT_FAILURE);
   	}

	// Intialize strings for get line.
    string line1, line2, line3;

	// Get lines for the BigIntegers and print A and B.
    getline(in, line1); // Get line 1.

    BigInteger A = BigInteger(line1); // Set A to line1.
	out << A << std::endl; // Print A.
	out << std::endl;

	getline(in, line2); // Get line 2 and discard it.

    getline(in, line3); // Get line 3.

    BigInteger B = BigInteger(line3); // Set B to line3.
    out << B << std::endl; // Print B.
	out << std::endl;

	// Print out operations done on BigIntegers A and B into outfile.
	out << (A + B) << std::endl; // Print A + B.
	out << std::endl;

	out << (A - B) << std::endl; // Print A - B.
	out << std::endl;

	out << (A - A)  << std::endl; // Print A - A.
	out << std::endl;

	// Set BigIntegers for 3 and 2.
	BigInteger num1 = BigInteger("+3");
	BigInteger num2 = BigInteger("+2");

	out << ((num1 * A) - (num2 * B)) << std::endl; // Print 3 * A - 2 * B.
	out << std::endl;

	out << (A * B) << std::endl; // Print A * B.
	out << std::endl;

    out << (A * A) << std::endl; // Print A * A.
	out << std::endl;

    out << (B * B) << std::endl; // Print B * B.
	out << std::endl;

	// Set BigIntegers for 9 and 12.
	num1 = BigInteger("+9");
	num2 = BigInteger("+16");

    out << ((num1 * A * A * A * A) + (num2 * B * B * B * B * B)) << std::endl; // Print 9 * A^4 + 16 * B^5.

	// Close infile and outfile.
    in.close();
	out.close();

	return 0;
}

