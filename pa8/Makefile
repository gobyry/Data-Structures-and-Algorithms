#------------------------------------------------------------------------------
#  Makefile for CSE 101 Programming Assignment 8
#
#  make                     makes WordFrequency
#  make DictionaryClient    makes DictionaryClient
#  make clean               removes all binaries
#  make WordFrequencyCheck  runs WordFrequency under valgrind on Gutenberg
#  make DictionaryCheck     runs DictionaryClient under valgrind
#------------------------------------------------------------------------------

MAIN           = WordFrequency
MAIN_2		   = Order
ADT            = Dictionary
SOURCE         = $(MAIN).cpp
SOURCE_2       = $(MAIN_2).cpp
OBJECT         = $(MAIN).o
OBJECT_2       = $(MAIN_2).o
ADT_TEST       = $(ADT)Test
ADT_SOURCE     = $(ADT).cpp
ADT_OBJECT     = $(ADT).o
ADT_OBJECT_2   = $(ADT).o
ADT_HEADER     = $(ADT).h
COMPILE        = g++ -std=c++17 -Wall -c
LINK           = g++ -std=c++17 -Wall -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full

$(MAIN): $(OBJECT) $(ADT_OBJECT)
	$(LINK) $(MAIN) $(OBJECT) $(ADT_OBJECT)

$(MAIN_2): $(OBJECT_2) $(ADT_OBJECT_2)
	$(LINK) $(MAIN_2) $(OBJECT_2) $(ADT_OBJECT_2)

$(ADT_TEST): $(ADT_TEST).o $(ADT_OBJECT)
	$(LINK) $(ADT_TEST) $(ADT_TEST).o $(ADT_OBJECT)

$(OBJECT): $(SOURCE) $(ADT_HEADER)
	$(COMPILE) $(SOURCE)

$(OBJECT_2): $(SOURCE_2) $(ADT_HEADER)
	$(COMPILE) $(SOURCE_2)

$(ADT_TEST).o: $(ADT_TEST).cpp $(ADT_HEADER)
	$(COMPILE) $(ADT_TEST).cpp

$(ADT_OBJECT): $(ADT_SOURCE) $(ADT_HEADER)
	$(COMPILE) $(ADT_SOURCE)

clean:
	$(REMOVE) $(MAIN) $(MAIN_2) $(ADT_TEST) $(OBJECT) $(OBJECT_2) $(ADT_TEST).o $(ADT_OBJECT) $(ADT_OBJECT_2)

$(MAIN)Check: $(MAIN)
	$(MEMCHECK) $(MAIN) Gutenberg myGutenberg-out

$(ADT)Check: $(ADT_TEST)
	$(MEMCHECK) $(ADT_TEST)
