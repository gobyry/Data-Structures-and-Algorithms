/****************************************************************************************
 * *  pa8 - By: Ryan Hui, rhui1
 * *  WordFrequency.cpp
 * *  Word Frequency file
 * *****************************************************************************************/

#include<iostream>
#include<fstream>
#include<string>
#include <cctype>
#include "Dictionary.h"

using namespace std;

#define MAX_LEN 300

int main(int argc, char * argv[]){
    ifstream in;
    ofstream out;

    // Check command line for correct number of arguments
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
        return(EXIT_FAILURE);
    }

    // Open files for reading and writing
    in.open(argv[1]);
    if (!in.is_open()) {
        cerr << "Unable to open file " << argv[1] << " for reading" << endl;
        return(EXIT_FAILURE);
    }

    out.open(argv[2]);
    if (!out.is_open()) {
        cerr << "Unable to open file " << argv[2] << " for writing" << endl;
        return(EXIT_FAILURE);
    }

    // Intialize dictioanry D.
    Dictionary D;

    // Intialize int and string variables.
    int line_count = 0;
    int val = 0;

    string lines;
    string token;
    string tokenBuffer;
    string delim = " \t\\\"\',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789"; // String delimn.

    // Read each line from infile.
    while(getline(in, lines)) {
        line_count += 1; // Increment line count by 1.
        size_t len = lines.length(); // Set length equal to lines length.
        tokenBuffer = ""; // Set token buffer to empty string.

        // Obtain first token.
        size_t begin = min(lines.find_first_not_of(delim, 0), len);
        size_t end   = min(lines.find_first_of(delim, begin), len);
        token = lines.substr(begin, end-begin);

        while(token != "") {  // While token exists.

            // Update token buffer.
            tokenBuffer += "   " + token + "\n";

            // Intialize lowercase string and set equal to token.
            string lowercase = token;

            // Set every token to lowercase format.
            for(size_t i = 0; i < lowercase.length(); i += 1) {
                lowercase[i] = tolower(lowercase[i]);
            }

            if(D.contains(lowercase)) { // If word is in dictionary.
                val = D.getValue(lowercase) + 1; // Set value incremented by 1.
                D.setValue(lowercase, val); // Set dictionary value with lowercased token string and incremented value.
            }

            if(D.contains(lowercase) == false) { // Else word not in dictionary.
                D.setValue(lowercase, 1); // Set non existent value to 1.
            }

            // Obtain next token.
            begin = min(lines.find_first_not_of(delim, end+1), len);
            end   = min(lines.find_first_of(delim, begin), len);
            token = lines.substr(begin, end-begin);
        }
    }
    // Print out dictionary.
    out << D << "\n";

   // Close infile and outfile.
   in.close();
   out.close();

   return(EXIT_SUCCESS);
}
