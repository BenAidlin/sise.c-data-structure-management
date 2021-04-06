prog: JerryBoreeMain.o MultiValueHashTable.o LinkedList.o HashTable.o KeyValuePair.o Jerry.o
	gcc JerryBoreeMain.o MultiValueHashTable.o LinkedList.o HashTable.o KeyValuePair.o Jerry.o -o prog
Jerry.o: Jerry.c Jerry.h Defs.h
	gcc -c Jerry.c
KeyValuePair.o: KeyValuePair.c KeyValuePair.h Defs.h
	gcc -c KeyValuePair.c 
LinkedList.o: LinkedList.c LinkedList.h Defs.h
	gcc -c LinkedList.c 
HashTable.o: HashTable.c HashTable.h Defs.h LinkedList.h KeyValuePair.h
	gcc -c HashTable.c
MultiValueHashTable.o: MultiValueHashTable.c LinkedList.h Defs.h MultiValueHashTable.h HashTable.h
	gcc -c MultiValueHashTable.c
JerryBoreeMain.o: JerryBoreeMain.c Defs.h LinkedList.h KeyValuePair.h MultiValueHashTable.h HashTable.h Jerry.h
	gcc -c JerryBoreeMain.c
