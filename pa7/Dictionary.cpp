/****************************************************************************************
 * *  pa7 - By: Ryan Hui, rhui1
 * *  Dictionary.cpp
 * *  Dictionary ADT File
 * *****************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sstream>
#include <string.h>
#include <iostream>
#include <string>
#include "Dictionary.h"

using namespace std;

Dictionary::Node::Node(keyType x, valType y) { // Constructor for Node.
    // Set Node pointers.
    key = x; // keyType.
    val = y; // valType.
    parent = nullptr; // Node*
    left = nullptr; // Node*
    right = nullptr; // Node*
}

// Helper Functions (Optional) ---------------------------------------------

void Dictionary::inOrderString(std::string& s, Node* R) const { // Appends string in order.
    if(R != nil) { // If R is not nil.
        // Call in order string.
        inOrderString(s, R->left);
        // Appends key and value to string.
        s += R->key;
        s += " : ";
        s += std::to_string(R->val);
        s += "\n";
        inOrderString(s, R->right); // Recusively call in order string.
    }
}

void Dictionary::preOrderString(std::string& s, Node* R) const { // Appends string pre order.
    if(R != nil) { // If R is not nil.
        s += R->key;
        s += "\n"; // Insert key and newline.
        preOrderString(s, R->left); // Recursively call pre order string.
        preOrderString(s, R->right);
    }
}

void Dictionary::preOrderCopy(Node* R, Node* N) { // Pre order copy nodes in R.
    if(R != N) { // If R is not eqaul to N.
        setValue(R->key, R->val); // Set value.

        // Recursively insert subtree.
        preOrderCopy(R->left, N);
        preOrderCopy(R->right, N);
    }
}

void Dictionary::postOrderDelete(Node* R) { // Deletes post order nodes in R.
    if(R != nil) { // If R is not nil.
        postOrderDelete(R->left);   // Delete left subtree
        postOrderDelete(R->right);  // Delete right subtree
        delete R;
    }
}

Dictionary::Node* Dictionary::search(Node* R, keyType k) const { // Search and return node for node key == k, else return nil.
    // Sourced from binary search tree pseudocode and tutor Sarah.
    if(R->key == k || R == nil) { // If R key is eqaul to k or R is nil.
        return R; // Return R.
    }
    else if(k < R->key) { // Else if k is less than R key.
        return search(R->left, k); // Return search on left value and k.
    }
    else if(k > R->key) { // Else if k is greater than R key.
        return search(R->right, k); // Return search on right value and k.
    }
    return nil; // Else return nil.
}

Dictionary::Node* Dictionary::findMin(Node* R) { // Finds left most node, else return nil.
    // Sourced from binary search tree pseudocode and tutor Sarah.
    if(R->left == nil) { // If R left equals nil.
        return R; // Return R.
    }
    Node* N; // Create Node N.
    for(N = R; N->left != nil; N = N->left) { // Loop through N until left value is nil.
    }
    return N; // Returns left most node.
}

Dictionary::Node* Dictionary::findMax(Node* R) { // Finds right most node, else return nil.
    // Sourced from binary search tree pseudocode and tutor Sarah.
    if(R->right == nil) { // If R right equals nil.
        return R; // Return R.
    }
    Node* N; // Create Node N.
    for(N = R; N->right != nil; N = N->right) { // Loop through N until right value is nil.
    }
    return N; // Returns right most node.
}

Dictionary::Node* Dictionary::findNext(Node* N) { // Finds next node after N if N doesn't point to rightmost node, else return nil.
    // Sourced from binary search tree pseudocode and tutor Sarah.
    if(N->right != nil) { // If N right value isn't nil.
        return findMin(N->right); // Return find min on N right.
    }
    Node* M; // Create Node M.
    for(M = N->parent; M != nil && N == M->right; M = M->parent) { // Loop through M's parents.
        N = M; // Set N to M.
    }
    return M; // Return M.
}

Dictionary::Node* Dictionary::findPrev(Node* N) { // Finds previous node before N if N doesn't point to leftmost node, else return nil.
    // Sourced from binary search tree pseudocode and tutor Sarah.
    if(N->left != nil) { // If N left value isn't nil.
        return findMax(N->left); // Return find max on N left.
    }
    Node* M; // Create Node M.
    for(M = N->parent; M != nil && N == M->left; M = M->parent) { // Loop through M's parents.
        N = M; // Set N to M.
    }
    return M; // Return M.
}

//public:

//*** Class Constructors & Destructors ***//

Dictionary::Dictionary() { // Constructor for Dictionary.
    // Set Dictionary pointers.
    nil = new Node("\000", 0);
    nil->left = nil;
    nil->right = nil;
    nil->parent = nil;

    // Copy over rest of pointers.
    root = nil;
    current = nil;
    num_pairs = 0;
}

Dictionary::Dictionary(const Dictionary& D) { // Copy constructor for Dictionary.
    // Sourced from tutor Sarah.

    // Copy Dictionary pointers.
    nil = new Node("\000", 0);
    nil->left = nil;
    nil->right = nil;
    nil->parent = nil;

    // Copy over rest of pointers.
    root = nil;
    current = nil;
    num_pairs = 0;

    // Call pre order copy on root and nil.
    preOrderCopy(D.root, D.nil);
}

Dictionary::~Dictionary() { // Destructor for Dictionary.
    // Sourced from tutor Sarah.
    postOrderDelete(root); // Call pre order delete.

    // Set Dictionary pointers to nil and 0.

    root = nil;
    current = nil;
    num_pairs = 0;

    // Delete nil node.
    delete nil;
}

//*** Access functions ***//

int Dictionary::size() const { // Returns Dictionary size.
    return num_pairs;
}

bool Dictionary::contains(keyType k) const { // Returns true if key == k, else return false.
    Node* N = search(root, k); // Set N to search on root and k.
    if(N == nil) { // If N is nill.
        return false; // Return false.
    }
    else { // Else return true.
        return true;
    }
}

valType& Dictionary::getValue(keyType k) const { // Returns a reference to key k.
    if(!contains(k)) { // If k isn't contained.
        throw std::logic_error("Get value error.");
    }
    Node* N = search(root, k); // Set Node N to search root k.
    return N->val; // Return N value.
}

bool Dictionary::hasCurrent() const { // Returns true if current iterator is defined, else return false.
    if(current == nil) { // If current is nil.
        return false; // Return false.
    }
    else { // Else return true.
        return true;
    }
}

keyType Dictionary::currentKey() const { // Returns current key,
    if(hasCurrent() == true) { // If has current is true.
        return current->key; // Return current key.
    }
    else { // Else throw error.
        throw std::logic_error("Current key error.");
    }
}

valType& Dictionary::currentVal() const { // Returns reference to current value.
    if(hasCurrent() == true) { // If has current is true.
        return current->val; // Return current value.
    }
    else {  // Else throw error.
        throw std::logic_error("Current value error.");
    }
}

//*** Manipulation procedures ***//

void Dictionary::clear() { // Resets Dictionary to empty state.
    postOrderDelete(root); // Call pre order delete on root.

    // Clear Dictionary pointers.
    root = nil;
    current = nil;
    num_pairs = 0;
}

void Dictionary::transplant(Node* u, Node* v) {
    // Sourced from binary search tree pseudocode and tutor Sarah.
    if(u->parent == nil) { // If node u parent is nil.
        root = v; // Set root to v.
    }
    else if(u == u->parent->left) { // Else if u equals u parent left.
        u->parent->left = v; // Set u parent left to v.
    }
    else { // Else u doesn't equal u parent left.
        u->parent->right = v; // Set u parent right to v.
    }
    if(v != nil) { // If v is not nil.
        v->parent = u->parent; // Set v parent to u parent.
    }
}

void Dictionary::setValue(keyType k, valType v) { // If key == k, overwrite value with v, else insert new pair.
    // Sourced from binary search tree pseudocode and tutor Sarah.

    // Set Node x and y.
    Node* x = root;
    Node* y = nil;

    while(x != nil) { // While x is not nil.
        y = x; // Set y equal to x.
        if(k < x->key) { // If k is less than x key.
            x = x->left; // x equals x left.
        }
        else if(x->key == k) { // Else if x key equals k.
            x->val = v; // x value equals v.
            return; // Return.
        }
        else { // Else x key is left than k.
            x = x->right; // x equals x right.
        }
    }
    // Create Node z equal to new Node (k, v).
    Node* z = new Node(k, v);
    // Set Node z values.
    z->left = nil;
    z->right = nil;
    z->parent = y;

    if(y == nil) { // If y is nil.
        root = z; // Set root to z.
    }
    else if(z->key < y->key) { // Else if z key is less than y key.
        y->left = z; // y left equals. z.
    }
    else { // Else z key is greater than y key.
        y->right = z; // y right equals z.
    }
    num_pairs += 1; // Increment num pairs by 1.
    //delete(z);
}

void Dictionary::remove(keyType k) { // Removes key == k pair. If pair is current, current becomes undefined.
    // Sourced from binary search tree pseudocode and tutor Sarah.

    if(!contains(k)) { // If k is not contained.
        throw std::logic_error("Remove error.");
    }
    if(k == current->key) {  // If k equals current key.
        current = nil; // Set current to nil.
    }
    // Create Nodes y and z.
    Node* y = root;
    Node* z = search(root, k);

    if(z->left == nil) { // If z left equals nil.
        transplant(z, z->right); // Transplant z with z right.
    }
    else if(z->right == nil) { // Else if z right equals nil.
        transplant(z, z->left); // Transplant z with z left.
    }
    else { // Else z doesn't equal nil.
        y = findMin(z->right); // Set y to find min for z right.
        if(y->parent != z) { // If y parent doesn't equal z.
            transplant(y, y->right); // Transplant y with y right.
            y->right = z->right; // Set y right equal to z right.
            y->right->parent = y; // Set y right parent to y.
        }
        transplant(z, y); // Transplant z with y.
        y->left = z->left; // Set y left equal z left.
        y->left->parent = y; // Set y left parent to y.
    }
    num_pairs -= 1; // Decrement y pairs by 1.
    delete(z); // Delete Node z.
}

void Dictionary::begin() { // Places iterator at first key pair if non empty, else do nothing.
    if(num_pairs != 0) { // If num pairs doesn't equal 0.
        current = findMin(root); // Current equals find min root.
    }
}

void Dictionary::end() { // Places iterator at last key pair if non empty, else do nothing.
    if(num_pairs != 0) { // If num pairs doesn't equal 0.
        current = findMax(root); // Current equals find max root.
    }
}

void Dictionary::next() { // Advance current to next pair if current iterator is not at the last pair. If current iterator is at the last pair, make current undefined.
    if(!hasCurrent()) {
        throw std::logic_error("Next error.");
    }
    if(findNext(current) == nil) { // If find next current equals nil.
        current = nil; // Current equals nil.
    }
    else { // Else find next current is not nil.
        current = findNext(current); // Current equals find next current.
    }
}

void Dictionary::prev() { // Move current to previous pair if current iterator not at first pair. If current iterator is at the first pair, make current undefined.
    if(!hasCurrent()) {
        throw std::logic_error("Prev error.");
    }
    if(findPrev(current) == nil) { // If find prev current equals nil.
        current = nil; // Current equals nil.
    }
    else { // Else find prev current is not nil.
        current = findPrev(current); // Current equals find prev current.
    }
}

//*** Other Functions ***//

std::string Dictionary::to_string() const { // Returns string representation of the Dictionary.
    string s = ""; // Create string s.
    inOrderString(s, root); // In order string and root.
    return s; // Return string.
}

std::string Dictionary::pre_string() const { // Returns string representation of all Dictionary keys.
    string s = ""; // Creates string s.
    preOrderString(s, root); // Pre order string and root.
    return s; // Return string.
}

bool Dictionary::equals(const Dictionary& D) const { // Returns true if Dictionaries contain same key values and pairs.
    if(num_pairs != D.num_pairs) { // If pair numbers aren't the same.
        return false; // Return false.
    }
    if(this->to_string() == D.to_string()) { // If strings are the same.
        return true; // Return true.
    }
    else { // Else Dictionaries aren't the same.
        return false; // Return false.
    }
}

//*** Overloaded Operators ***//

std::ostream& operator<<( std::ostream& stream, Dictionary& D ) { // Returns string representation of Dictionary.
    return stream << D.Dictionary::to_string();
}

bool operator==( const Dictionary& A, const Dictionary& B ) { // Returns Dictionary compare operation.
    return A.Dictionary::equals(B);
}

Dictionary& Dictionary::operator=( const Dictionary& D ) { // Overwrites Dictionary with equal operation.
    // Set temp dictionary equal to D.
    Dictionary temp = D;

    // Copy over dictionary D alues.
    std::swap(nil, temp.nil);
    std::swap(root, temp.root);
    std::swap(current, temp.current);
    std::swap(num_pairs, temp.num_pairs);

    // Return overwritten dictionary.
    return *this;
}

