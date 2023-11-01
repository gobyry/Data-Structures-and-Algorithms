/****************************************************************************************
 * *  pa6 - By: Ryan Hui, rhui1
 * *  ListTest.cpp
 * *  List Test File
 * *****************************************************************************************/

#include<iostream>
#include<string>
#include<stdexcept>
#include <sstream>
#include"List.h"

using namespace std;

int main(){

    // Populate Lists.
    int i, n=10;
    List A, B, C, D;

    for(i=1; i<=n; i++){
      A.insertAfter(i);
      B.insertAfter(11-i);
      C.insertBefore(i);
      D.insertBefore(11-i);
    }

   cout << endl;

   std::cout << "***** List Tests. *****\n";

   std::cout << "List A: " << A.to_string() << " \n";
   std::cout << "List B: " << B.to_string() << " \n";
   std::cout << "List C: " << C.to_string() << " \n";
   std::cout << "List D: " << D.to_string() << " \n";

   std::cout << "Lists are cleared if only printing front and back dummy elements.\n";

   std::cout << "List insertion tests\n";
   cout << endl;

   n = 16;

   for(i=1; i<=n; i++){
      A.insertBefore(i);
      B.insertBefore(17-i);
      C.insertAfter(i);
      D.insertAfter(17-i);
   }

   std::cout << "List position and length tests.\n";

   cout << "A = " << A << endl;
   cout << "A.position() = " << A.position() << endl;
   cout << "A.length() = " << A.length() << endl;

   cout << "B = " << B << endl;
   cout << "B.position() = " << B.position() << endl;
   cout << "B.length() = " << B.length() << endl;

   cout << "C = " << C << endl;
   cout << "C.position() = " << C.position() << endl;
   cout << "C.length() = " << C.length() << endl;

   cout << "D = " << D << endl;
   cout << "D.position() = " << D.position() << endl;
   cout << "D.length() = " << D.length() << endl;
   cout << endl;

   cout << "A position move prev: " << A.movePrev() << "\n";
   cout << "B position move prev: " << B.movePrev() << "\n";

   cout << "C position move next: " << C.moveNext() << "\n";
   cout << "D position move next: " << D.moveNext() << "\n";

   std::cout << "List move front and back tests.\n";

   A.moveFront();
   B.moveFront();
   C.moveBack();
   D.moveBack();

   std::cout << "Peek next and prev tests.\n";

   cout << "A peek next: " << A.peekNext() << "\n";
   cout << "B peek next: " << B.peekNext() << "\n";

   cout << "C peek prev: " << D.peekPrev() << "\n";
   cout << "D peek prev: " << D.peekPrev() << "\n";

   std::cout << "List erase before and after tests.\n";

   A.eraseAfter();
   B.eraseAfter();
   C.eraseBefore();
   D.eraseBefore();

   cout << "A = " << A << endl;
   cout << "B = " << B << endl;
   cout << "C = " << C << endl;
   cout << "D = " << D << endl;

   std::cout << "List concat and cleanup tests.\n";

   cout << "A concat B: " << A.concat(B) << "\n";
   cout << "C concat D: " << C.concat(D) << "\n";

   List G, H;
   G =  A.concat(B);
   H =  D.concat(D);

   G.cleanup();
   H.cleanup();

   cout << "Cleanup A concat B (List G): " << G << "\n";
   cout << "Cleanup A concat B (List H): " << H << "\n";

   std::cout << "List equal tests.\n";

   cout << "List G and H equals: " << G.equals(H) << "\n";

   std::cout << "List find next and prev tests.\n";

   cout << "List A find next 5: " << A.findNext(5) << "\n";
   cout << "List B find next 10 : " << B.findNext(10) << "\n";
   cout << "List C find prev 7 : " << C.findPrev(7) << "\n";
   cout << "List D find prev 3 : " << D.findPrev(3) << "\n";

   std::cout << "List set before and after tests.\n";
   A.setAfter(3);
   B.setAfter(5);
   C.setBefore(8);
   D.setBefore(6);

   cout << "List A with 3 set after cursor: " << A << "\n";
   cout << "List B with 5 set after cursor: " << B << "\n";
   cout << "List C with 8 set before cursor: " << C << "\n";
   cout << "List D with 6 set before cusor: " << D << "\n";

   return 0;
}

/* OUTPUT:
***** List Tests. *****
List A: (10, 9, 8, 7, 6, 5, 4, 3, 2, 1)
List B: (1, 2, 3, 4, 5, 6, 7, 8, 9, 10)
List C: (1, 2, 3, 4, 5, 6, 7, 8, 9, 10)
List D: (10, 9, 8, 7, 6, 5, 4, 3, 2, 1)
Lists are cleared if only printing front and back dummy elements.
List insertion tests

List position and length tests.
A = (1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1)
A.position() = 16
A.length() = 26
B = (16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10)
B.position() = 16
B.length() = 26
C = (1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1)
C.position() = 10
C.length() = 26
D = (10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16)
D.position() = 10
D.length() = 26

A position move prev: 16
B position move prev: 1
C position move next: 16
D position move next: 1
List move front and back tests.
Peek next and prev tests.
A peek next: 1
B peek next: 16
C peek prev: 16
D peek prev: 16
List erase before and after tests.
A = (2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1)
B = (15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10)
C = (1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2)
D = (10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15)
List concat and cleanup tests.
A concat B: (2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10)
C concat D: (1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15)
Cleanup A concat B (List G): (2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 1)
Cleanup A concat B (List H): (10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 11, 12, 13, 14, 15)
List equal tests.
List G and H equals: 0
List find next and prev tests.
List A find next 5: 4
List B find next 10 : 6
List C find prev 7 : 19
List D find prev 3 : 12
List set before and after tests.
List A with 3 set after cursor: (2, 3, 4, 5, 3, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1)
List B with 5 set after cursor: (15, 14, 13, 12, 11, 10, 5, 8, 7, 6, 5, 4, 3, 2, 1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10)
List C with 8 set before cursor: (1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2)
List D with 6 set before cusor: (10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 1, 6, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15)
*/
