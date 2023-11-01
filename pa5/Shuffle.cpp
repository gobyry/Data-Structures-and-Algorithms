/****************************************************************************************
 * *  pa5 - By: Ryan Hui, rhui1
 * *  Shuffle.cpp
 * *  Shuffle Program File
 * *****************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <iostream>
#include <string>
#include "List.h"

using namespace std;

void shuffle(List& D) { // Shuffle function.
    // Create lists.
    List L = D; // Copy over List D to L.
    List LL; // Initialize left list.
    List LR; // Initialize right list.

    // Move front of every list.
    L.moveFront();
    LL.moveFront();
    LR.moveFront();

    // Intialize variables.
    int i = 0;
    int half = (L.length() / 2); // Set half equal to length of list divided by 2.

    // Fill left list with numbers.
    for(i = 0; i < half; i += 1) { // Loop through first half of list L.
        LL.insertBefore(L.peekNext()); // Insert first half numbers into the left list.
        L.moveNext(); // Move next on list L.
    }

    // Fill right lists with numbers.
    for(i = half; i < L.length(); i += 1) { // Loop through second half of list L.
        LR.insertBefore(L.peekNext()); // Insert second half numbers into the right list.
        L.moveNext(); // Move next on list L.
    }

    // Move front of both lists.
    LL.moveFront();
    LR.moveFront();

    // Clear list D and move to the front.
    D.clear();
    D.moveFront();

    // Insert left and right lists into deck in shuffled order.
    for(i = 0; i < half; i += 1) { // Loop through left and right lists for half the deck size.
        D.insertBefore(LR.peekNext()); // Insert right element into list D.
        LR.moveNext(); // Move next on right list.

        D.insertBefore(LL.peekNext()); // Insert left element into list D.
        LL.moveNext(); // Move next on left list.
    }

    if(L.length() % 2 != 0) { // If deck is odd.
        D.insertBefore(LR.peekNext()); // Insert right element into list D.
        LR.moveNext(); // Move next on right list.
    }
}

int main(int argc, char * argv[]) {

    // Check if 3 arguments are inputted.
    if(argc != 2){
      cerr << "Usage: " << argv[0] << " number." << endl;
      return(EXIT_FAILURE);
    }

    // Store argument number.
    int num = stoi(argv[1]);

    // Intialize original list and shuffle list.
    List OL; // Original list.
    List SL; // Shuffle list.

    // Print title.
    std::cout << "deck size        shuffle count\n";
    std::cout << "------------------------------\n";

    // Intialize varaibles.
    int shuffle_count = 1;
    int i = 0;

    for(i = 1; i <= num; i += 1) { // Loop through argument size.

        // Insert deck size number into original list.
        OL.insertAfter(i);

        // Copy over original list to shuffle list.
        SL = OL;

        // Call shuffle on shuffle list.
        shuffle(SL);

        // Intialize shuffle count.
        shuffle_count = 1;

        // Loop until shuffled list matches original list.
        while(!(SL.equals(OL))) {
            shuffle(SL);
            shuffle_count += 1;
        }

        // Print deck size and shuffle count for each size.
        std::cout << (i) << "\t\t" << shuffle_count << std::endl;
    }
}
