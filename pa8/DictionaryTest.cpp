/****************************************************************************************
 * *  pa8 - By: Ryan Hui, rhui1
 * *  DictionaryTest.cpp
 * *  Dictionary Test File
 * *****************************************************************************************/

#include<iostream>
#include<string>
#include<stdexcept>
#include"Dictionary.h"

using namespace std;

int main(){
   string s;
   int x;
   string S[] =   {
                     "plaices",
                     "ambusher",
                     "crosby",
                     "wattles",
                     "pardoner",
                     "pythons",
                     "second",
                     "forms",
                     "impales",
                     "pic",
                     "verticals",
                     "recriminator",
                     "depressants",
                     "cul",
                     "potables",
                     "norm",
                     "reinsurer",
                     "deschooler",
                     "recoining",
                     "dissocialised",
                     "cohabit",
                     "hemiolia",
                     "cantling",
                     "glamorized",
                     "millesimal",
                     "glagolitic"
                  };
   string T[] =   {
                     "second",
                     "forms",
                     "impales",
                     "pic",
                     "verticals",
                     "recriminator",
                     "depressants",
                     "cul",
                     "potables",
                     "norm",
                     "reinsurer",
                     "deschooler",
                     "recoining",
                  };

   Dictionary A;
   Dictionary B;

   cout << endl;

   // insert some pairs into A
   for(int i=0; i<26; i++){
      A.setValue(S[i], i+2);
   }

   // call operator=()
   B = A;

   cout << "Testing Dictionary print.\n";

   cout << "A.size() = " << A.size() << endl  << A << endl;
   cout << "B.size() = " << B.size() << endl  << B << endl;

   cout << "Testing Set value.\n";

   B.setValue("norm", 101);
   B.setValue("cohabitr", 102);
   B.setValue("forms", 103);
   B.setValue("pythons", 104);
   B.setValue("glagolitic", 105);

   cout << "Dictionary B: .\n";

   cout << B;

   // call copy constructor
   Dictionary C = B;

   cout << "Testing size.\n";

   cout << "B.size() = " << B.size() << endl  << B << endl;
   cout << "C.size() = " << C.size() << endl  << C << endl;

   cout << "Testing equals.\n";

   // check operator==()
   cout << "A == B is " << (A==B?"true":"false") << endl;
   cout << "B == C is " << (B==C?"true":"false") << endl;
   cout << "C == A is " << (C==A?"true":"false") << endl << endl;

   cout << "A == A is " << (A==A?"true":"false") << endl;
   cout << "B == B is " << (B==B?"true":"false") << endl;
   cout << "C == C is " << (C==C?"true":"false") << endl;

   cout << "Testing state of Dictionary A.\n";
   // perform alterations on A
   cout << A.getValue("norm") << endl;
   A.getValue("norm") *= 10; // change the value associated with "hemiolia"
   cout << A.getValue("norm") << endl << endl;

   // check state of A
   cout << "A.size() = " << A.size() << endl  << A << endl;
   cout << A.pre_string() << endl;

   cout << "Testing state of Dictionary B.\n";
   // perform alterations on A
   cout << B.getValue("norm") << endl;
   B.getValue("norm") *= 10; // change the value associated with "hemiolia"
   cout << B.getValue("norm") << endl << endl;

   // check state of A
   cout << "B.size() = " << B.size() << endl  << B << endl;
   cout << B.pre_string() << endl;

   cout << "Testing state of Dictionary C.\n";
   // perform alterations on A
   cout << C.getValue("norm") << endl;
   C.getValue("norm") *= 10; // change the value associated with "hemiolia"
   cout << C.getValue("norm") << endl << endl;

   // check state of A
   cout << "C.size() = " << C.size() << endl  << C << endl;
   cout << C.pre_string() << endl;

   cout << "Testing removing on all Dictionaries.\n";

   // remove some pairs from A
   for(int i=0; i<14; i++){
      cout << "removing " << T[i] << " from Dictionary A" << endl;
      A.remove(T[i]);
   }

    // remove some pairs from B.
   for(int i=0; i<5; i++){
      cout << "removing " << T[i] << " from Dictionary B" << endl;
      B.remove(T[i+1]);
   }

   for(int i=0; i<10; i++){
      cout << "removing " << T[i] << " from Dictionary C" << endl;
      C.remove(T[i+1]);
   }

   cout << "\n";

   cout << "Testing Dictionary A.\n";

   // check state of A
   cout << "A.size() = " << A.size() << endl  << A << endl;
   cout << A.pre_string() << endl;

   cout << "Regular printinf o A.\n";
   // do forward iteration on A
   for(A.begin(); A.hasCurrent(); A.next()){
      s = A.currentKey();
      x = A.currentVal();
      cout << "("+s+", " << x << ") ";
   }

   cout << endl << endl;

   cout << "Reverse printing of A.\n";

   // do reverse iteration on A
   for(A.end(); A.hasCurrent(); A.prev()){
      s = A.currentKey();
      x = A.currentVal();
      cout << "("+s+", " << x << ") ";
   }

   return( EXIT_SUCCESS );
}

/* Output:
Testing Dictionary print.
A.size() = 26
ambusher : 3
cantling : 24
cohabit : 22
crosby : 4
cul : 15
depressants : 14
deschooler : 19
dissocialised : 21
forms : 9
glagolitic : 27
glamorized : 25
hemiolia : 23
impales : 10
millesimal : 26
norm : 17
pardoner : 6
pic : 11
plaices : 2
potables : 16
pythons : 7
recoining : 20
recriminator : 13
reinsurer : 18
second : 8
verticals : 12
wattles : 5

B.size() = 26
ambusher : 3
cantling : 24
cohabit : 22
crosby : 4
cul : 15
depressants : 14
deschooler : 19
dissocialised : 21
forms : 9
glagolitic : 27
glamorized : 25
hemiolia : 23
impales : 10
millesimal : 26
norm : 17
pardoner : 6
pic : 11
plaices : 2
potables : 16
pythons : 7
recoining : 20
recriminator : 13
reinsurer : 18
second : 8
verticals : 12
wattles : 5

Testing Set value.
Dictionary B: .
ambusher : 3
cantling : 24
cohabit : 22
cohabitr : 102
crosby : 4
cul : 15
depressants : 14
deschooler : 19
dissocialised : 21
forms : 103
glagolitic : 105
glamorized : 25
hemiolia : 23
impales : 10
millesimal : 26
norm : 101
pardoner : 6
pic : 11
plaices : 2
potables : 16
pythons : 104
recoining : 20
recriminator : 13
reinsurer : 18
second : 8
verticals : 12
wattles : 5
Testing size.
B.size() = 27
ambusher : 3
cantling : 24
cohabit : 22
cohabitr : 102
crosby : 4
cul : 15
depressants : 14
deschooler : 19
dissocialised : 21
forms : 103
glagolitic : 105
glamorized : 25
hemiolia : 23
impales : 10
millesimal : 26
norm : 101
pardoner : 6
pic : 11
plaices : 2
potables : 16
pythons : 104
recoining : 20
recriminator : 13
reinsurer : 18
second : 8
verticals : 12
wattles : 5

C.size() = 27
ambusher : 3
cantling : 24
cohabit : 22
cohabitr : 102
crosby : 4
cul : 15
depressants : 14
deschooler : 19
dissocialised : 21
forms : 103
glagolitic : 105
glamorized : 25
hemiolia : 23
impales : 10
millesimal : 26
norm : 101
pardoner : 6
pic : 11
plaices : 2
potables : 16
pythons : 104
recoining : 20
recriminator : 13
reinsurer : 18
second : 8
verticals : 12
wattles : 5

Testing equals.
A == B is false
B == C is true
C == A is false

A == A is true
B == B is true
C == C is true
Testing state of Dictionary A.
17
170

A.size() = 26
ambusher : 3
cantling : 24
cohabit : 22
crosby : 4
cul : 15
depressants : 14
deschooler : 19
dissocialised : 21
forms : 9
glagolitic : 27
glamorized : 25
hemiolia : 23
impales : 10
millesimal : 26
norm : 170
pardoner : 6
pic : 11
plaices : 2
potables : 16
pythons : 7
recoining : 20
recriminator : 13
reinsurer : 18
second : 8
verticals : 12
wattles : 5

impales
depressants (RED)
crosby
cantling
ambusher (RED)
cohabit (RED)
cul
dissocialised
deschooler
glamorized (RED)
forms
glagolitic (RED)
hemiolia
pythons (RED)
plaices
pardoner (RED)
norm
millesimal (RED)
pic
potables
second
recriminator
recoining (RED)
reinsurer (RED)
wattles
verticals (RED)

Testing state of Dictionary B.
101
1010

B.size() = 27
ambusher : 3
cantling : 24
cohabit : 22
cohabitr : 102
crosby : 4
cul : 15
depressants : 14
deschooler : 19
dissocialised : 21
forms : 103
glagolitic : 105
glamorized : 25
hemiolia : 23
impales : 10
millesimal : 26
norm : 1010
pardoner : 6
pic : 11
plaices : 2
potables : 16
pythons : 104
recoining : 20
recriminator : 13
reinsurer : 18
second : 8
verticals : 12
wattles : 5

glamorized
depressants
cantling
ambusher
crosby (RED)
cohabit
cohabitr (RED)
cul
dissocialised
deschooler
forms
glagolitic (RED)
norm
impales
hemiolia
millesimal
pythons (RED)
plaices
pardoner
pic (RED)
potables
recriminator
recoining
second (RED)
reinsurer
wattles
verticals (RED)

Testing state of Dictionary C.
101
1010

C.size() = 27
ambusher : 3
cantling : 24
cohabit : 22
cohabitr : 102
crosby : 4
cul : 15
depressants : 14
deschooler : 19
dissocialised : 21
forms : 103
glagolitic : 105
glamorized : 25
hemiolia : 23
impales : 10
millesimal : 26
norm : 1010
pardoner : 6
pic : 11
plaices : 2
potables : 16
pythons : 104
recoining : 20
recriminator : 13
reinsurer : 18
second : 8
verticals : 12
wattles : 5

dissocialised
cohabitr
cantling
ambusher
cohabit
depressants
crosby
cul (RED)
deschooler
impales
glagolitic
forms
glamorized
hemiolia (RED)
plaices (RED)
norm
millesimal
pardoner
pic (RED)
recriminator
pythons (RED)
potables
recoining
second (RED)
reinsurer
wattles
verticals (RED)

Testing removing on all Dictionaries.
removing second from Dictionary A
removing forms from Dictionary A
removing impales from Dictionary A
removing pic from Dictionary A
removing verticals from Dictionary A
removing recriminator from Dictionary A
removing depressants from Dictionary A
removing cul from Dictionary A
removing potables from Dictionary A
removing norm from Dictionary A
removing reinsurer from Dictionary A
removing deschooler from Dictionary A
removing recoining from Dictionary A
removing plaices from Dictionary A
removing second from Dictionary B
removing forms from Dictionary B
removing impales from Dictionary B
removing pic from Dictionary B
removing verticals from Dictionary B
removing second from Dictionary C
removing forms from Dictionary C
removing impales from Dictionary C
removing pic from Dictionary C
removing verticals from Dictionary C
removing recriminator from Dictionary C
removing depressants from Dictionary C
removing cul from Dictionary C
removing potables from Dictionary C
removing norm from Dictionary C

Testing Dictionary A.
A.size() = 12
ambusher : 3
cantling : 24
cohabit : 22
crosby : 4
dissocialised : 21
glagolitic : 27
glamorized : 25
hemiolia : 23
millesimal : 26
pardoner : 6
pythons : 7
wattles : 5

millesimal
dissocialised (RED)
cantling
ambusher
crosby
cohabit (RED)
glamorized
glagolitic
hemiolia
pythons
pardoner
wattles

Regular printinf o A.
(ambusher, 3) (cantling, 24) (cohabit, 22) (crosby, 4) (dissocialised, 21) (glagolitic, 27) (glamorized, 25) (hemiolia, 23) (millesimal, 26) (pardoner, 6) (pythons, 7) (wattles, 5)

Reverse printing of A.
(wattles, 5) (pythons, 7) (pardoner, 6) (millesimal, 26) (hemiolia, 23) (glamorized, 25) (glagolitic, 27) (dissocialised, 21) (crosby, 4) (cohabit, 22) (cantling, 24) (ambusher, 3)
*/
