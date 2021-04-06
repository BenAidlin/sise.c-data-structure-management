#ifndef MULTIVALUEHASHTABLE_H_
#define MULTIVALUEHASHTABLE_H_
#include "HashTable.h"

typedef struct t_multihash *multiHash;
multiHash createMultiValueHashTable(EqualFunction eqValListInPair,EqualFunction eqInfoListInPair,CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey, CopyFunction copyValue, FreeFunction freeValue, PrintFunction printValue, EqualFunction equalKey, TransformIntoNumberFunction transformIntoNumber, int hashNumber);
status destroyMultiValueHashTable(multiHash mht);
status addToMultiValueHashTable(multiHash mht, Element k, Element v);
Element lookupInMultiValueHashTable(multiHash mht, Element k);
status removeFromMultiValueHashTable(multiHash mht, Element k, Element lst);
status displayMultiValueHashTable(multiHash mht, Element k);
#endif /* MULTIVALUEHASHTABLE_H_ */
