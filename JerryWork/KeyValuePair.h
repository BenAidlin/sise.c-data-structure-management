#ifndef KEYVALUEPAIR_H_
#define KEYVALUEPAIR_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Defs.h"

typedef struct t_keyValuePair* keyValuePair;

keyValuePair createKeyValuePair(Element,Element,PrintFunction,PrintFunction,CopyFunction,CopyFunction,FreeFunction,FreeFunction,EqualFunction);
status destroyKeyValuePair(keyValuePair);
status displayValue(keyValuePair);
status displayKey(keyValuePair);
Element getValue(keyValuePair);
Element getKey(keyValuePair);
bool isEqualKey(keyValuePair, Element);
PrintFunction getPrintK(keyValuePair);
PrintFunction getPrintV(keyValuePair);
CopyFunction getCopyK(keyValuePair);
CopyFunction getCopyV(keyValuePair);
FreeFunction getFreeK(keyValuePair);
FreeFunction getFreeV(keyValuePair);
EqualFunction getEqK(keyValuePair);
#endif /* KEYVALUEPAIR_H_ */
