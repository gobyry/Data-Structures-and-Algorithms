/****************************************************************************************
 * *  pa5 - By: Ryan Hui, rhui1
 * *  List.cpp
 * *  List ADT File
 * *****************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sstream>
#include "List.h"

using namespace std;

//Private part:
List::Node::Node(ListElement x) { // Constructor for Node.
    //Intialize pointers.
    data = x;
    next = nullptr;
    prev = nullptr;
}

List::List() { // Creates new List.
    //Create new node with front and back dummmies.
    frontDummy = new Node(-1);
    backDummy = new Node(-1);

    //Intialize pointers.
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    num_elements = 0;
    pos_cursor = 0;
}

List::List(const List& L) { // Copy constructor for List.
    // Copy Nodes.
    frontDummy = new Node(-1);
    backDummy = new Node(-1);

    // Copy pointers.
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    num_elements = 0;
    pos_cursor = 0;

    // Loop through elements and copy over.
    Node* copy = L.frontDummy->next; // Create copy node.
    while(copy != L.backDummy) { // While copy isn't done with list.
        insertBefore(copy->data); // Insert copy to data.
        copy = copy->next; // Move next on copy.
    }
}

List::~List() { // Destructor for List.
    clear(); // Clear list.
    delete(frontDummy); // Delete frontDummy node.
    delete(backDummy); // Delete backDummy node.
}

//*** Access functions ***//
int List::length() const { // Returns length of the List.
    return(num_elements);
}

ListElement List::front() const { // Returns front element of the List.
    if(length() == 0) { // pre: length()>0
        throw std::length_error("Front length error.");
    }
    return(frontDummy->next->data);
}

ListElement List::back() const { // Returns back element of the List.
    if(length() == 0 ) { // pre: length()>0
        throw std::length_error("Back length error.");
    }
    return(backDummy->prev->data);
}

int List::position() const { // Returns the cursor position.
    if(pos_cursor < 0 || pos_cursor > length()) { // pre: 0 <= position() <= length().
        throw std::range_error("Position not in range.");
    }
    return(pos_cursor);
}

ListElement List::peekNext() const { // Returns the element after the cursor.
    if(position() > length()) { // pre: position()<length()
        throw std::length_error("Peek next length error.");
    }
    return(afterCursor->data);
}

ListElement List::peekPrev() const { // Returns the element before the cursor.
    if(position() < 0) { // pre: position()>0
        throw std::range_error("Peek prev range error.");
    }
    return(beforeCursor->data);
}

//*** Manipulation procedures ***//
void List::clear() { // Deletes all elements in the List and sets List to empty state.
    while(length() > 0) { // While list is not empty.
        moveFront(); // Move to front.
        eraseAfter(); // Erase eleemnts.
    }
    // Clear pointers.
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    pos_cursor = 0;
    num_elements = 0;
}

void List::moveFront() { // Moves cursor to the front.
    beforeCursor = frontDummy; // Set cursor to the front.
    afterCursor = frontDummy->next;

    pos_cursor = 0; // Set cursor position to the front.
}

void List::moveBack() { // Moves cursor to the back.
    beforeCursor = backDummy->prev; // Set cursor to the back.
    afterCursor = backDummy;

    pos_cursor = length(); // Set cursor position to the back.
}

ListElement List::moveNext() { // Moves cursor to next position.
    if(position() > length()) { // pre: position()<length()
        throw std::length_error("Move next length error.");
    }
    // Moves cursor position to next position.
    beforeCursor = afterCursor;
    afterCursor = afterCursor->next;

    // Increment cursor position.
    pos_cursor += 1;

    return(beforeCursor->data);
}

ListElement List::movePrev() { // Moves cursor to previous position.
    if(position() <= 0) { // pre: position()>0
        throw std::range_error("Move prev range error.");
    }
    // Moves cursor position to previous position.
    afterCursor = beforeCursor;
    beforeCursor = beforeCursor->prev;
    //afterCursor = beforeCursor->next;

    // Decrement cursor position.
    pos_cursor -= 1;

    return(afterCursor->data);
}

void List::insertAfter(ListElement x) { // Inserts x after cursor.
    //Create new node N.
    Node* N = new Node(x);

    //Set previous and next nodes
    N->prev = beforeCursor;
    N->next = afterCursor;

    //Set before and after cursors so element can be inserted after.
    beforeCursor->next = N;
    afterCursor->prev = N;

    // Set node inserted to be after the cursor.
    afterCursor = N;

    // Increment cursor and elements length
    num_elements += 1;
}

void List::insertBefore(ListElement x) { // Inserts x before cursor.
    //Create new node N.
    Node* N = new Node(x);

    //Set previous and next nodes
    N->next = afterCursor;
    N->prev = beforeCursor;

    //Set before and after cursors so element can be inserted before.
    beforeCursor->next = N;
    afterCursor->prev = N;

    // Set node inserted to be before the cursor.
    beforeCursor = N;

    // Increment cursor and elements length.
    pos_cursor += 1;
    num_elements += 1;
}

void List::setAfter(ListElement x) { // Sets element after cursor to x.
    if(position() >= length()) { // pre: position()<length()
        throw std::length_error("Set after length error.");
    }
    afterCursor->data = x; // Set the element after the cursor to x.
}

void List::setBefore(ListElement x) { // Sets element before cursor to x.
    if(position() <= 0) { // pre: position()>0
        throw std::range_error("Set before range error.");
    }
    beforeCursor->data = x; // Set element before the cursor to x.
}

void List::eraseAfter() { // Deletes element after cursor.
    if (position() >= length() ) { // pre: position()<length()
        throw std::length_error("Erase after length error.");
    }
    //Set node N.
    Node* N = afterCursor;

    //Cursors before
    afterCursor = N->next;
    afterCursor->prev = beforeCursor;
    beforeCursor->next = afterCursor;

    delete(N); // Delete node N.

    // Decrement number of elements by 1.
    num_elements -= 1;
}

void List::eraseBefore() { // Deletes element before cursor.
    if (position() <= 0) { // pre: position()>0
        throw std::range_error("Erase before range error.");
    }

    //Set node N.
    Node* N = beforeCursor;

    beforeCursor = N->prev; // Set element to previous.
    beforeCursor->next = afterCursor; // Set next element before cursor to after cursor's element.
    afterCursor->prev = beforeCursor; // Set previous element for after cursor to before cursor's element.

    delete(N); // Delete node N.

    // Decrement number of elements and cursor position by 1.
    num_elements-=1;
    pos_cursor-=1;
}

//*** Other Functions ***//

int List::findNext(ListElement x) { // Returns first occurence of x going front to back.
    int pos = -1; // Set default cursor position.

    while(afterCursor != backDummy) { // Loop through list front to back.
        if(moveNext() == x) { // If x is found.
            pos = pos_cursor; // Set position variable to position.
            break;
        }
    }
    return(pos); // Return found position, else, -1.
}

int List::findPrev(ListElement x) { // Returns first occurence of x going back to front.
    int pos = -1; // Set default cursor position.

    while(beforeCursor != frontDummy) { // Loop through list back to front.
        if(movePrev() == x) { // If x is found.
            pos = pos_cursor; // Set position variable to position.
            break;
        }
    }
    return(pos); // Return found position, else, -1.
}

void List::cleanup() { // Cleans up list leaving only unique elements.
    // Clean up function pseudocode provided by tutor Brian.
    Node* curr = frontDummy->next;
    int pos = 0;

    while(curr != backDummy) { // While current node isn't at the back.
        Node* prev = curr; // Set prev node.
        Node* next = curr->next; // Set next node.

        while (next != backDummy) { // While next node isn't at the back.
            if (curr->data == next->data) { // If current node data equals next node data.
                Node* next_next = next->next; // Set the next next node.
                prev->next = next_next; // Next value of previous node equals next next node.
                next_next->prev = prev; // Next next node's previous value equals previos.

                if (beforeCursor == next) { // If before cursor equals next node.
                    beforeCursor = next->prev; // Set before cursor to previous value.
                    pos += 1; // Increment position by 1.
                } else if (afterCursor == next) { // Else if after cursor equals next node.
                    afterCursor = next_next; // Set after cursor to next next node.
                    pos += 1; // Incremenet position by 1.
                }
                if(pos < pos_cursor) { // If position variable less than position.
                    pos_cursor -= 1; // Decrement position by 1.
                }
                delete(next); // Delete next node.
                next = next_next; // Set next node equal to next next node.
                num_elements -= 1; // Decrement number of elements by 1.
            }
            else { // Else current data doesn't equal next data.
                prev = next; // Set previous node to next.
                next = next->next; // Set next node to next next value.
            }
        }
        curr = curr->next; // Set current node equal to current next value.
        pos += 1; // Increment position by 1.
    }
}

List List::concat(const List& L) const { // Returns a new list NL followed by elements of the list.
    // Function sourced from Queue.cpp.

    List NL; // Initialize new list NL.

    for(Node* N = this->frontDummy->next; N != this->backDummy; N = N->next) { // Loop through elements in list.
        NL.insertBefore(N->data); // Insert looped elements into new list NL.
    }

    for(Node* M = L.frontDummy->next; M != L.backDummy; M = M->next) { // Loop through elements in list L.
        NL.insertBefore(M->data); // Insert looped elements into new list NL.
    }
    NL.moveFront(); // Reset cursor position for NL.

    return NL;
}

std::string List::to_string() const { // Returns string representation of the List.
    // Function sourced from Queue.cpp.
    Node* N = nullptr; // Intialize node N.
    std::string s = ""; // Set string s.

    for(N = frontDummy; N !=nullptr ; N = N->next) { // Loop through list starting at front.
       s += std::to_string(N->data)+" "; // Increment string s with node data.
    }
    return s;
}

bool List::equals(const List& R) const { // Returns true only if List is the same integer sequence of R.
    // Function sourced from Queue.cpp.
    if(length() != R.length()) { // Check if length of lists are equal.
        return false;
    }

    Node* N = frontDummy->next; // Intialize node N to list front dummmy.
    Node* M = R.frontDummy->next; // Intialize node M to List R front dummy.

    while(N != backDummy) { // While node N isn't at the back.
        if(N->data != M->data) { // If nodes N and M values aren't equal.
            return false;
        }
        //Move next on Nodes N and M.
        N = N->next;
        M = M->next;
    }
    return true;
}

//*** Overriden Operators ***//

std::ostream& operator<<( std::ostream& stream, const List& L ) { // Inserts string representation L into stream.
    // Function sourced from Queue.cpp.
    return stream << L.List::to_string();
}

bool operator==( const List& A, const List& B ) { // Returns true if A and B are the same integer sequence.
    // Function sourced from Queue.cpp.
    return A.List::equals(B);
}

List& List::operator=( const List& L ) { // Overwrites state of the List with state of L.
    // Function sourced from Queue.cpp.
    if( this != &L ){ // If not a self assignment of List.
      // Make a temp of list L.
      List temp = L;

      // Swap list with list L fields.
      std::swap(frontDummy, temp.frontDummy);
      std::swap(backDummy, temp.backDummy);
      std::swap(num_elements, temp.num_elements);
    }
    return *this; // Return equaled list.
}
