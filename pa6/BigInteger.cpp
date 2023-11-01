/****************************************************************************************
 * *  pa6 - By: Ryan Hui, rhui1
 * *  BigInteger.cpp
 * *  Big Integer ADT File
 * *****************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sstream>
#include "List.h"
#include "BigInteger.h"

using namespace std;

// Set base and power constants.
const long base = 1000000000; //1000000000
const int power = 9; // 9

//*** BigInteger Functions ***//

BigInteger::BigInteger() { // Creates new BigInteger in zero state.
    signum = 0; // Set signum.
    List digits; // Set digits.
}

BigInteger::BigInteger(long x) { // Creates new BigInteger from x.
    // Help from tutor Sid.
    // Check x's type.
    if(x < 0) { // If x is negative.
        signum = -1; // Sign is negative.
    }
    else if(x > 0) { // Else if x is positive.
        signum = 1; // Sign is positive.
    }

    if(x == 0) { // If x is equal to 0.
        digits.insertBefore(0); // Insert 0 to digits list.
    }
    else { // Else x isn't equal to 0.
        if(signum == -1) { // If sign is negative.
            x *= (-1); // Change x to positive.
        }
        while(x > 0) { // While x is positive.
            digits.insertBefore(x % base); // Insert digits into digits list.
            x /= base; // Updates x by removing inserted digits.
        }
    }
}

BigInteger::BigInteger(std::string s) { // Create new BigInteger from string s.
    // Help from tutor Sid.
    // If string is negative, remove the sign.
    if(s[0] == '-') { // If string has a negative sign.
        signum = -1; // Sign is negative.
        s = s.erase(0, 1); // Remove first element of string.
    }
    else if (s[0] == '+') {// Else if string is not negative.
        signum = 1; // Sign is positive.
        s = s.erase(0, 1); // Remove first element of string.
    }
    else {
        signum = 1;
    }

    int zeroes = 0; // Intialize zeroes counter.
    while(s[zeroes] == '0') { // While string has leading zeroes.
        zeroes += 1; // Increment zeroes counter.
    }

    if(zeroes > 1) { // Don't delete a single 0.
        s = s.erase(0, zeroes); // Remove number of leading zeroes.
    }

    // Insert string digits into digits list.
    for(int i = s.length(); i > 0; i -= power) { // Loop through length of string.
        if(i - power > 0) { // If power is in range.
            long ls = stol(s.substr(i - power, power)); // Store ith element powers as a long.
            digits.insertAfter(ls); // Insert long into digits.
        }
        else { // Else at index is less than power and final group at front less than power.
            long ls = stol(s.substr(0, i)); // Store ith element powers as a long.
            digits.insertAfter(ls); // Insert long into digits.
        }
    }
}

BigInteger::BigInteger(const BigInteger& N) { // Creates a copy of N.
    // Copy over pointers.
    signum = N.sign(); // Set signum to N's sign.
    digits = N.digits; // Set digits.
}

//*** Optional Destuctor ***//
// ~BigInteger();

//*** Access functions ***//
int BigInteger::sign() const { // Returns sign of the BigInteger.
    return signum;
}

int BigInteger::compare(const BigInteger& N) const { // Compares BigIntegers.
    // Intialize lists.
    List L;
    List NL;

    // Fill lists only if both BigIntegers aren't empty to avoid segfaults.
    if(digits.length() > 0 && N.digits.length() > 0) { //If this and N digits are greater than 0.
        // Initialize list for digits.
        L = digits;
        NL = N.digits;
    }
    else { // Else they are empty.
        return 0;
    }

    // Initial checker for BigInteger signs.
    if(sign() < N.sign()) { // If less than N's digit length or sign.
        return -1; // this is less than N.
    }
    else if(sign() > N.sign()) { // If greater than N's digit length or sign.
        return 1; // this is greater than N.
    }
    else if(sign() == 0 && N.sign() == 0) {
        return 0;
    }
    else { // Else digit length or sign is equal, compare the individual digits.
        L.moveFront();
        NL.moveFront();

        if(digits.length() < N.digits.length()) { // If this has less digits than N.
            if(signum == -1) { // If sign of this is positive.
                return 1; // this is smaller than N.
            }
            else { // Else sign is negative.
                return -1; // this is bigger than N as a negative with less digits.
            }
        }
        else if(digits.length() > N.digits.length()) {
            if(sign() == -1) { // If sign of this is positive.
                return -1; // this is greater than N.
            }
            else {
                return 1;
            }
        }
        else { // Else sign is negative.

            // Intiallize list elements.
            ListElement d = 0;
            ListElement dd = 0;

            // Move front on lists.
            L.moveFront();
            NL.moveFront();

            while((L.position() < L.length()) && (d == dd)) { // Loop through digits length.
                // Set digit values for that iteration.
                d = L.moveNext();
                dd = NL.moveNext();

                if(d < dd) { // If digit is less than N digit.
                    if(sign() == -1) { // If sign is positive.
                            return 1; // d is less than dd.
                        }
                        else { // Else sign is negative.
                            return -1; // d is greater than dd/
                        }
                }
                else if(d > dd) { // If digit is greater than N digit.
                    if(sign() == -1) { // If sign is positive.
                        return -1; // d is greater than dd.
                    }
                    else { // Else sign is negative.
                        return 1; // d is less than dd.
                    }
                }
            }
        }
    }
    // Return comparison result.
    return 0;
}

//*** Manipulation procedures ***//

void BigInteger::makeZero() { // Resets BigInteger to zero state.
    // Reset sign and digits.
    signum = 0;
    digits.clear();
}

void BigInteger::negate() { // Reverses sign of BigInteger if not 0.
    if(digits.length() == 0 || sign() == 0 ) { // If BigInteger is 0 or sign is 0.
        signum = 0; // Do nothing
    }
    else { // Else is not 0.
        signum = -signum; // Reverse sign.
    }
}

//*** Optional Functions ***/
void negateList(List& L) { // Changes sign of each element of List L.
    List CL = L; // Intialize list copy.

    //Move front on list.
    L.moveFront();
    CL.moveFront();

    // Clear list to change signs.
    L.clear();

    // Loop through copy list.
    for(int i = 0; i < CL.length(); i += 1) { // Loop through size of list L.
        ListElement rev = CL.moveNext() * -1; // Get value of copy list and change sign.
        L.insertAfter(rev); // Insert negated value to list.
        L.moveNext(); // Move next on list L.
    }
}

void sumList(List& S, List A, List B, int sgn) { // Overwrites List S with List A and B vectors.
    // Sourced from tutors Mike/Stanley.
    S.clear(); // Overwrite state of S.

    // Move front on lists.
    A.moveBack();
    B.moveBack();

    while((A.position() > 0) && (B.position() > 0)) { // Loop through size of list A and list B.
        S.insertAfter(A.movePrev() + (sgn * B.movePrev())); // Perform sum list operation.
    }

    while(A.position() > 0) { // Loop through list A.
        S.insertAfter(A.movePrev()); // Insert A to S.

    }
    while(B.position() > 0) { // Loop through list B.
        S.insertAfter(B.movePrev() * sgn); // Insert operation into list S.
    }
}

int normalizeList(List& L) { // Returns integer after performing carries from right to left.
    // Pseudo sourced from tutor Sebastion.
    // Move front on list L.
    L.moveBack();

    // Intialize varaibles.
    ListElement q = 0; // Quotient.
    ListElement r = 0; // Remainder.
    ListElement u = 0; // u.
    ListElement carryIn = 0; // Carry in.
    ListElement carryOut = 0; // Carry out.
    ListElement col = 0; // Column.

    while (L.position() > 0) { // While list is not empty.
        // Calculate the normalized value by carrying from right to left.
        carryIn = carryOut; // Set carryIn to carryOut.

        // Get list position and store it in position. Add carryIn value to col value.
        col = L.movePrev();
        col += carryIn;

        // Calculate carry value.
        q = col / base; // Obtain quotient.
        r = col % base; // Obtain remainder.

        // Handle negative numbers.
        if(r < 0) { // If remainder is negative.
            u = 1; // Set u to 1.
        }
        else { // Else remainder is positive.
            u = 0; // Set u to 0.
        }

        // Update col value.
        col = (r + u * base);

        // Update carry out value.
        carryOut = q - u;

        // Erase previous digit and insert col valumn in place of it.
        L.setAfter(col);

        // Checker for additional carrys.
        if (L.position() == 0) { // If moved all the way to the front of the list.
            if (carryOut > 0) { // If carry is positive.
                L.insertBefore(0); // Insert a 0 since there is still a carry.
            }
            else if(carryOut < 0) { // If carry is negative.
                L.insertBefore(carryOut); // Insert carry after cursor.
                break;
            }
        }
    }
    // Remove trailing zeros.
    L.moveFront();
    while(L.position() < L.length() && L.peekNext() == 0) { // While number of digits are more than 1 and front equals 0.
        L.eraseAfter(); // Erase the 0.
        if(L.length() == 0) { // If list empty.
            L.insertBefore(0); // Insert a 0.
            return 0; // Sign is 0.
        }
    }
    // If leftmost digit is positive.
    if(L.length() > 0) {
        L.moveFront();
        if(L.peekNext() > 0) { // If value is positive.
            return 1; // Set sign to positive.
        }
        // If leftmost digit is negative, recurisvely call normalize.
        else if(L.peekNext() < 0) {
            negateList(L); // Reverse sign of all digits.
            normalizeList(L); // Recursively normalize digits.
            return -1; // Set sign to negative.
        }
    }
    return 0;
}

void shiftList(List& L, int p) { // Prepends p number of zero digits to List L.
    // Move to back of list L.
    L.moveBack();

    for(int i = 0; i < p; i += 1) { // Loop through length of p.
        L.insertBefore(0); // Prepend 0.
    }
}

void scalarMultList(List& L, ListElement m) { // Multiplies List L by vector m.
    List CL = L; // Intialize list copy.

    //Move front on list.
    L.moveFront();
    CL.moveFront();

    // Clear list to change signs.
    L.clear();

    for(int i = 0; i < CL.length(); i += 1) { // Loop through length of list L.
        ListElement mult = CL.moveNext() * m; // Set scalar multiple value equal to list L index * m.
        L.insertAfter(mult); // Insert scalar multiple value into list L.
        L.moveNext(); // Move next on list L.
    }
}

//*** BigInteger Arithmetic operations ***//

BigInteger BigInteger::add(const BigInteger& N) const { // Returns the sum of BigInteger and N.
    // Pseudocode from tutors Norton/Brian.

    // Intialize list of digits, N list of digits, and sum list
    List L = digits;
    List NL = N.digits;
    List SL;

    // Intialize BigIntegers and set digits.
    BigInteger BS;
    BigInteger B;

    BS.digits = L;
    B.digits = NL;

    // If both have same signs.
    if(sign() == N.sign()) {
        sumList(SL, L, NL, 1); // Sum list using a sgn of 1.
        normalizeList(SL); // Normalize list SL.
        BS.digits = SL; // Set BS to SL digits.
    }
    // Else if signs doesn't eqaul.
    else if(sign() != N.sign()) {
        sumList(SL, L, NL, -1); // Sum list using sgn of -1.
        BS.digits = SL; // Normalize list SL.
    }

    // Set signum of BS.
    int sgn; // Initialize sgn.

    sgn = normalizeList(BS.digits);

    // Basic sign checkers.
    if(sign() == N.sign()) { // If signs are equal.
        sgn = sign(); // Set sgn to sign.
    }
    if(sign() == 0) { // If this is 0.
        sgn = N.sign(); // Set sgn to N's sign.
    }
    if(N.sign() == 0) { // If N is 0.
        sgn = sign(); // Set sgn to this's sign.
    }

    // Negative sign checkers.
    if(sign() == -1 && N.sign() == -1) { // If both signs are negative.
        negateList(L); // Negate list to be added.
        sumList(SL, L, NL, -1); // Sum list with negative sign.
        BS.digits = SL; // Set digits.
    }
    else if(sign() == -1 && N.sign() == 1) { // If this is negative and N is positive.
        sumList(SL, NL, L, -1); // Sum list with negative sign.
        BS.digits = SL; // Set digits.
    }
    else if(N.sign() == -1 && sign() == 1) { // If N is negative and this is positive.
        sumList(SL, L, NL, -1); // Sum list with negative sign.
        BS.digits = SL; // Set digits.
    }
    else { // Else positive.
        sumList(SL, L, NL, 1); // Sum list with positive sign.
        BS.digits = SL; // Set digits.
    }

    // Set sgn to normalized digits.
    sgn = normalizeList(BS.digits);

    // Set signum to sgn.
    BS.signum = sgn;

    // Return digits of sum list as BigInteger.
    return(BS);
}

BigInteger BigInteger::sub(const BigInteger& N) const { // Returns the subtraction of BigInteger and N.
    // Sourced from tutor Norton.
    BigInteger BS = BigInteger(N); // Create BigInteger sub from N.
    BS.negate(); // Negate BigInteger sub to be added.
    return add(BS); // Add negated BigInteger sub to N.
}

BigInteger BigInteger::mult(const BigInteger& N) const { // Returns the multiplication of BigInteger and N.
    // Sourced from tutor Norton.
    // Intialize BigInteger mult.
    BigInteger BM;

    // Intialize lists and variables.
    List L = digits;
    List NL = N.digits;
    List SL;
    int sgn = 0;
    int y = 0;

    NL.moveBack();

    // Checker if one of the BigIntegers are 0.
    if(sign() == 0) { // If this is 0.
        BM.digits.insertBefore(0); // Insert 0 into list.
        BM.signum = 0; // Set sign to 0.
        return BM;
    }
    else if(N.sign() == 0) { // If N is 0.
        BM.digits.insertBefore(0); // Insert 0 into list.
        BM.signum = 0; // Set sign to 0.
        return BM;
    }

    // Negative checker for negating digitis.
    if(sign() == -1 && N.sign() == 1) { // If this is negative and N is positive.
        negateList(L); // Make this digits negative.
    }
    else if(N.sign() == -1 && sign() == 1) { // If N is negative and this is positive.
        negateList(L); // Make N digits negative.
    }

    for (int i = NL.length(); i > 0; i-= 1) { // Loop through list B.
        ListElement x = NL.movePrev(); // Get the current digit from B
        List L = digits;

        scalarMultList(L, x); // Multiply A elements by b.

        shiftList(L, y); // Shift list by y counter.

        sumList(BM.digits, BM.digits, L, 1); // Sum digits with list L.

        y += 1; // Increment y counter by 1.
        sgn = normalizeList(BM.digits);
    }
    // Set sgn equal to normalized digits.

    // Rechange sng according to the starting BigIntegers.
    if(sign() == 1 && N.sign() == 1) { // If both signs are positive.
        sgn = 1;
    }
    else if(sign() == -1 && N.sign() == -1) { // If both signs are negative.
        sgn = 1;
    }
    else if(sign() == -1 && N.sign() == 1) { // If this is negative and N is positive.
        sgn = -1;
    }
    else if(N.sign() == -1 && sign() == 1) { // If N is negative and this is positive.
        sgn = -1;
    }

    // Set BigInteger mult signum.
    BM.signum = sgn;

    return BM;
}

//*** Other Functions ***//

std::string BigInteger::to_string() { // Prints out BigInteger digits.
    // Sourced from tutor pseudocode.
    std::string s = ""; // Set string s.

    if(signum == 0) { // If digits is empty.
        s += "0"; // Print a 0.
    }

    if(signum < 0) { // If BigInteger is negative.
        s += "-"; // Print a negative sign in front.
    }

    // Start from the beginning of the digits.
    digits.moveFront();

    // Loop through length of digits and add each digit value to the string to be printed.
    for(int i = 0; i < digits.length(); i += 1) { // Loop through digits.
        std::string d = std::to_string(digits.moveNext()); // Add digit value to string d.
        long l = d.length(); // Set l to d length.
        if(digits.position() > 1 && power > l) { // Loop through digits according to power.
            for(long i = 0; i < power - l; i += 1) { // Loop through powers.
                s += "0"; // Add a 0 for each power.
            }
            s += d; // Add d to the s.
        }
        else {
            s += d; // Add d to string s.
        }
    }

    // If first element is 0.
    if(s[0] == '0') {
        s.erase(0, 1); // Erase leading 0.
    }

    // Return digit string.
    return s;
}

//*** Overriden Operators ***//

std::ostream& operator<<( std::ostream& stream, BigInteger N ) { // Returns string operation.
    return stream << N.BigInteger::to_string();
}

bool operator==( const BigInteger& A, const BigInteger& B ) { // Returns equal to operation.
    return A.BigInteger::compare(B) == 0;
}

bool operator<( const BigInteger& A, const BigInteger& B ) { // Returns less than operation.
    return A.BigInteger::compare(B) < 0;
}

bool operator<=( const BigInteger& A, const BigInteger& B ) { // Returns less than or equal to operation.
    return A.BigInteger::compare(B) <= 0;
}

bool operator>( const BigInteger& A, const BigInteger& B ) { // Returns greater than operation.
    return A.BigInteger::compare(B) > 0;
}

bool operator>=( const BigInteger& A, const BigInteger& B ) { // Returns greater than or equal to operation.
    return A.BigInteger::compare(B) >= 0;
}

BigInteger operator+( const BigInteger& A, const BigInteger& B ) { // Returns sum operation.
    return A.BigInteger::add(B);
}

BigInteger operator+=( BigInteger& A, const BigInteger& B ) { // Returns sum equals to operation.
    A = A + B;
    return A;
}

BigInteger operator-( const BigInteger& A, const BigInteger& B ) { // Returns sub operation.
    return A.BigInteger::sub(B);
}

BigInteger operator-=( BigInteger& A, const BigInteger& B ) { // Returns sub equals to operation.
    A = A - B;
    return A;
}

BigInteger operator*( const BigInteger& A, const BigInteger& B ) { // Returns mult operation
    return A.BigInteger::mult(B);
}

BigInteger operator*=( BigInteger& A, const BigInteger& B ) { // Returns mult equals to operation
    A = A * B;
    return A;
}


