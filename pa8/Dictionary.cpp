/****************************************************************************************
 * *  pa8 - By: Ryan Hui, rhui1
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

Dictionary::Node::Node(keyType k, valType v) { // Constructor for Node.
    // Set Node pointers.
    key = k; // keyType.
    val = v; // valType.
    parent = nullptr; // Node*
    left = nullptr; // Node*
    right = nullptr; // Node*
    color = 1; // Color starts as black.
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
    // Sourced from tutor sid.
    if(R != nil) { // If R is not nil.
        s += R->key;
        if(R->color == 0) { // If the color is red.
            s += " (RED)"; // Add RED to end of string.
        }
        s += "\n"; // Insert key and newline.
        preOrderString(s, R->left); // Recursively call pre order string.
        preOrderString(s, R->right);

    }
}

/*
void Dictionary::BST_insert(Node* M) { // Inserts copy of Node M into dictionary.



}
*/

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
    if(N == nil) {
        return nil;
    }

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

void Dictionary::LeftRotate(Node* N) { // Left rotate function.
    // Sourced from binary search tree pseudocode.
    Node* x = N;
    Node* y = x->right;

    x->right = y->left;

    if(y->left != nil) {
        y->left->parent = x;
    }

    y->parent = x->parent;
    if(x->parent == nil) {
        root = y;
    }
    else if(x == x->parent->left) {
        x->parent->left = y;
    }
    else {
        x->parent->right = y;
    }

    y->left = x;
    x->parent = y;
}

void Dictionary::RightRotate(Node* N) { // Right rotate function.
    // Sourced from binary search tree pseudocode.
    Node* x = N;
    Node* y = x->left;

    x->left = y->right;
    if(y->right != nil) {
        y->right->parent = x;
    }

    y->parent = x->parent;
    if(x->parent == nil) {
        root = y;
    }
    else if(x == x->parent->right) {
        x->parent->right = y;
    }
    else {
        x->parent->left = y;
    }

    y->right = x;
    x->parent = y;
}

void Dictionary::RB_Insert(Node* N) { // Rb insert function.
    // Sourced from binary search tree pseudocode.
    Node* y = nil;
    Node* x = root;
    Node* z = N;

    while(x != nil) {
        y = x;
        if(z->key < x->key) {
            x = x->left;
        }
        else {
            x = x->right;
        }
    }
    z->parent = y;
    if(y == nil) {
        root = z;
    }
    else if(z->key < y->key) {
        y->left = z;
    }
    else {
        y->right = z;
    }
    z->left = nil;
    z->right = nil;
    z->color = 0;
    RB_InsertFixUp(z);
}

void Dictionary::RB_InsertFixUp(Node* N) { // RB insert fix up function.
    // Sourced from binary search tree pseudocode.
    Node* y;
    Node* z = N;

    while(z->parent->color == 0) {
        if(z->parent == z->parent->parent->left) {
            y = z->parent->parent->right;
            if(y->color == 0) {
                z->parent->color = 1;
                y->color = 1;
                z->parent->parent->color = 0;
                z = z->parent->parent;
            }
            else {
                if(z == z->parent->right) {
                    z = z->parent;
                    LeftRotate(z);
                }
                z->parent->color = 1;
                z->parent->parent->color = 0;
                RightRotate(z->parent->parent);
            }
        }
        else {
            y = z->parent->parent->left;
            if(y->color == 0) {
                z->parent->color = 1;
                y->color = 1;
                z->parent->parent->color = 0;
                z = z->parent->parent;
            }
            else {
                if(z == z->parent->left) {
                    z = z->parent;
                    RightRotate(z);
                }
                z->parent->color = 1;
                z->parent->parent->color = 0;
                LeftRotate(z->parent->parent);
            }

        }
    }
    root->color = 1;
}

void Dictionary::RB_Transplant(Node* u, Node* v) { // RB transplant function.
    // Sourced from binary search tree pseudocode.
    if(u->parent == nil) {
        root = v;
    }
    else if(u == u->parent->left) {
        u->parent->left = v;
    }
    else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

void Dictionary::RB_DeleteFixUp(Node* N) { // RB delete fix up function
    // Sourced from binary search tree pseudocode.
    Node* x = N;
    Node* w;

    while(x != root && x->color == 1) { // Black color.
        if(x == x->parent->left) {
            w = x->parent->right;
            if(w->color == 0) { // Red color.
                w->color = 1; // Black color.
                x->parent->color = 0; // Red color.
                LeftRotate(x->parent);
                w = x->parent->right;
            }
            if(w->left->color == 1 && w->right->color == 1) { // Black color.
                w->color = 0; // Red color.
                x = x->parent;
            }
            else {
                if(w->right->color == 1) { // Black color.
                    w->left->color = 1; // Black color.
                    w->color = 0; // Red color.
                    RightRotate(w);
                }
                w->color = x->parent->color;
                x->parent->color = 1; // Black color.
                w->right->color = 1; // Black color.
                LeftRotate(x->parent);
                x = root;
            }
        }
        else {
            w = x->parent->left;
            if(w->color == 0) { // Red color.
                w->color = 1; // Black color
                x->parent->color = 0; // Red color.
                RightRotate(x->parent);
                w = x->parent->left;
            }
            if(w->right->color == 1 && w->left->color == 1) { // Black color.
                w->color = 0; // Red color.
                x = x->parent;
            }
            else {
                if(w->left->color == 1) { // Black color.
                    w->right->color = 1; // Black color.
                    w->color = 0; // Red color.
                    LeftRotate(w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = 1; // Black color.
                w->left->color = 1; // Black color.
                RightRotate(x->parent);
                x = root;
            }
        }
    }
    x->color = 1;
}

void Dictionary::RB_Delete(Node* N) { // RB delete function.
    // Sourced from binary search tree pseudocode.
    Node* z = N;
    Node* y = z;
    int y_color = y->color;
    Node* x;

    if(z->left == nil) {
        x = z->right;
        RB_Transplant(z, z->right);
    }
    else if(z->right == nil) {
        x = z->left;
        RB_Transplant(z, z->left);
    }
    else {
        y = findMin(z->right);
        y_color = y->color;
        x = y->right;
        if(y->parent == z) {
            x->parent = y;
        }
        else {
            RB_Transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        RB_Transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    if(y_color == 1) { // Color is black.
        RB_DeleteFixUp(x);
    }
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
    // Sourced from tutor Sid.
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
    z->color = 0;
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
    RB_InsertFixUp(z); // Insert fix up node z.
}

void Dictionary::remove(keyType k) { // Removes key == k pair. If pair is current, current becomes undefined.
    // Sourced from tutor Sid.
    Node* z = search(root, k);

    if(z == nil) { // If k is not contained.
        throw std::logic_error("Remove error.");
    }
    if(k == current->key) {  // If k equals current key.
        current = nil; // Set current to nil.
    }
    RB_Delete(z); // RB delete node z.
    num_pairs -=1; // Decrement num pairs by 1.
    delete z;
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

