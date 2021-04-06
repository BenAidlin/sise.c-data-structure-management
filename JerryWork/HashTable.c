#include "HashTable.h"
#include "LinkedList.h"
#include "KeyValuePair.h"

struct hashTable_s{
	linkedList* arr;
	int n;
	TransformIntoNumberFunction trans;
	EqualFunction eqBtweenKeys;
	CopyFunction cpKofPair;
	PrintFunction printKofPair;
	FreeFunction freeKofPair;
	CopyFunction cpVofPair;
	PrintFunction printVofPair;
	FreeFunction freeVofPair;
};
//helper functions
static Element copyPair(Element p1){
	if(p1==NULL)return NULL;
	keyValuePair p=NULL;
	p = (keyValuePair)p1;
	keyValuePair newP=NULL;
	newP=createKeyValuePair(getKey(p),getValue(p),getPrintK(p),getPrintV(p),getCopyK(p),getCopyV(p),getFreeK(p),getFreeV(p),getEqK(p));
	if(newP==NULL)
		return NULL;
	return (Element)newP;
}

static status destroyPair(Element ptemp){
	if(ptemp==NULL)
		return failure;
	keyValuePair p =NULL;
	p=(keyValuePair)ptemp;
	return destroyKeyValuePair(p);
}

static status displayPair(Element p1){
	if(p1==NULL)return failure;
	keyValuePair p=NULL;
	p = (keyValuePair)p1;
	printf("{ key: ");
	displayKey(p);
	printf(" | value: ");
	displayValue(p);
	printf(" }");
	return success;
}

static bool isEqualPair(Element p1temp,Element p2temp){
	if(p1temp==NULL||p2temp==NULL)return false;
	keyValuePair p1=NULL,p2=NULL;
	p1 = (keyValuePair)p1temp;
	p2 = (keyValuePair)p2temp;
	bool b = isEqualKey(p1,getKey(p2));
	return b;
}

static bool isEqualPairInfo(Element ptemp,Element info){
	if(ptemp==NULL || info==NULL)
		return false;
	keyValuePair p=NULL;
	p=(keyValuePair)ptemp;
	return isEqualKey(p,info);
}

static int hashFunc(hashTable ht, Element key){
	if (ht==NULL || key==NULL)return -1;
	return ht->trans(key)%ht->n;
}
//implement of header file
hashTable createHashTable(CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey, CopyFunction copyValue, FreeFunction freeValue, PrintFunction printValue, EqualFunction equalKey, TransformIntoNumberFunction transformIntoNumber, int hashNumber){
	if(copyKey==NULL || freeKey==NULL || printKey==NULL || copyValue==NULL || freeValue==NULL || printValue==NULL || equalKey==NULL || transformIntoNumber==NULL || hashNumber<=0)
		return NULL;
	hashTable ht=NULL;
	ht = (hashTable)malloc(sizeof(struct hashTable_s));
	if(ht==NULL)
		return NULL;
	ht->n=hashNumber;
	ht->arr=(linkedList*)malloc(sizeof(linkedList)*ht->n);
	if(ht->arr==NULL)
		return NULL;
	int i=0;
	for(i=0;i<ht->n;i++){
		ht->arr[i]=createLinkedList(copyPair, destroyPair, displayPair,isEqualPair,isEqualPairInfo);
		if(ht->arr[i]==NULL)
			return NULL;
	}
	ht->cpKofPair=copyKey;
	ht->cpVofPair=copyValue;
	ht->eqBtweenKeys=equalKey;
	ht->freeKofPair=freeKey;
	ht->freeVofPair=freeValue;
	ht->printKofPair=printKey;
	ht->printVofPair=printValue;
	ht->trans=transformIntoNumber;
	return ht;
}
status destroyHashTable(hashTable ht){
	if(ht==NULL)return failure;
	status s;
	int i;
	for (i=0;i<ht->n;i++){
		s=destroyList(ht->arr[i]);
		ht->arr[i]=NULL;
		if(s==failure)return s;
	}
	free(ht->arr);
	ht->arr=NULL;
	ht->cpKofPair=NULL;
	ht->cpVofPair=NULL;
	ht->eqBtweenKeys=NULL;
	ht->freeKofPair=NULL;
	ht->freeVofPair=NULL;
	ht->printKofPair=NULL;
	ht->printVofPair=NULL;
	ht->trans=NULL;
	free(ht);
	ht=NULL;
	return success;
}

status addToHashTable(hashTable ht, Element key,Element value){
	if (ht==NULL || key==NULL || value==NULL)return failure;
	Element temp =lookupInHashTable(ht,key);
	status s;
	if (temp==NULL){
		keyValuePair newP =createKeyValuePair(key,value,ht->printKofPair, ht->printVofPair,ht->cpKofPair,ht->cpVofPair,ht->freeKofPair,ht->freeVofPair,ht->eqBtweenKeys);
		if (newP==NULL)return failure;
		s=appendNode(ht->arr[hashFunc(ht,key)],newP);
		if(destroyKeyValuePair(newP)==failure || s==failure)return failure;
		return success;
	}
	temp=NULL;
	return failure;
}

Element lookupInHashTable(hashTable ht, Element key){
	if (ht==NULL || key==NULL)return NULL;
	int index=hashFunc(ht,key);
	keyValuePair temp =(keyValuePair)searchByKeyInList(ht->arr[index],key);
	if (temp==NULL)return temp;
	return getValue(temp);
}

status removeFromHashTable(hashTable ht, Element key){
	if (ht==NULL || key==NULL)return failure;
	Element temp =lookupInHashTable(ht,key);
	if(temp==NULL)return failure;
	int index=hashFunc(ht,key);
	keyValuePair newP =(keyValuePair)searchByKeyInList(ht->arr[index],key);
	if(newP==NULL)return failure;
	if (deleteNode(ht->arr[index],newP)==failure){
		newP=NULL;
		return failure;
	}
	temp=NULL;
	return success;

}

status displayHashElements(hashTable ht){
	if(ht==NULL)return failure;
	status s;
	int i;
	for (i=0;i<ht->n;i++){
		printf("arr[%d]= ", i);
		s=displayList(ht->arr[i]);
		printf("\n");
		if(s==failure)return s;
	}
	printf("END OF THE HASH TABLE \n");
	return success;
}
