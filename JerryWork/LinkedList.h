#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Defs.h"

typedef struct linkedList_t *linkedList;

linkedList createLinkedList(CopyFunction , FreeFunction , PrintFunction , EqualFunction,EqualFunction );
status destroyList(linkedList );
status appendNode(linkedList , Element );
status deleteNode(linkedList , Element );
status displayList(linkedList );
Element getDataByIndex(linkedList , int );
int getLengthList(linkedList );
Element searchByKeyInList(linkedList , Element );
CopyFunction getCopy(linkedList);
FreeFunction getFree(linkedList);
PrintFunction getPrint(linkedList);
EqualFunction getEqNodes(linkedList);
EqualFunction getEqInfo(linkedList);
#endif /* LINKEDLIST_H_ */
