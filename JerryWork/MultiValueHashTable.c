#include "LinkedList.h"
#include "MultiValueHashTable.h"

struct t_multihash {
	hashTable ht;
	int size;
	CopyFunction cpVinNode;
	PrintFunction printVinNode;
	FreeFunction freeVinNode;
	EqualFunction eqValListInPair;
	EqualFunction eqInfoListInPair;
	PrintFunction printK;
};
static Element copyList(Element lstTemp){
	if(lstTemp==NULL)return NULL;
	linkedList lst=(linkedList)lstTemp;
	linkedList fin=createLinkedList(getCopy(lst) , getFree(lst) , getPrint(lst) ,  getEqNodes(lst),getEqInfo(lst));
	if(fin==NULL)return NULL;
	Element e=getDataByIndex(lst,0);
	if(e==NULL)return fin;
	appendNode(fin,e);
	return fin;
}
static status freeList(Element lstTemp){
	if(lstTemp==NULL)return failure;
	linkedList lst=(linkedList)lstTemp;
	return destroyList(lst);
}
static status printList(Element lstTemp){
	if(lstTemp==NULL)return failure;
	linkedList lst=(linkedList)lstTemp;
	return displayList(lst);
}

multiHash createMultiValueHashTable(EqualFunction eqValListInPair,EqualFunction eqInfoListInPair ,CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey, CopyFunction copyValue, FreeFunction freeValue, PrintFunction printValue, EqualFunction equalKey, TransformIntoNumberFunction transformIntoNumber, int hashNumber){
	if(eqInfoListInPair==NULL || eqValListInPair==NULL || copyKey==NULL || freeKey==NULL || printKey==NULL || copyValue==NULL || freeValue==NULL || printValue==NULL || equalKey==NULL || transformIntoNumber==NULL || hashNumber<=0)
		return NULL;
	multiHash mht = NULL;
	mht=(multiHash)malloc(sizeof(struct t_multihash));
	if(mht==NULL)return NULL;
	mht->size=hashNumber;
	mht->ht=createHashTable(copyKey,freeKey,printKey,copyList,freeList,printList,equalKey,transformIntoNumber,hashNumber);
	if(mht->ht==NULL){
		free(mht);
		return NULL;
	}
	mht->cpVinNode=copyValue;
	mht->freeVinNode=freeValue;
	mht->printVinNode=printValue;
	mht->eqValListInPair =  eqValListInPair;
	mht->eqInfoListInPair=eqInfoListInPair;
	mht->printK=printKey;
	return mht;
}


Element lookupInMultiValueHashTable(multiHash mht, Element k){
	if(mht==NULL || k==NULL)return NULL;
	linkedList newLst = (linkedList)lookupInHashTable(mht->ht, k);
	return newLst;
}

status addToMultiValueHashTable(multiHash mht, Element k, Element v){
	if(mht==NULL || k==NULL || v==NULL)return failure;
	status s;
	linkedList valInPair = (linkedList)lookupInHashTable(mht->ht,k);
	if(valInPair!=NULL){
		s = appendNode(valInPair, v);
		valInPair=NULL;
		return s;
	}
	valInPair = createLinkedList(mht->cpVinNode , mht->freeVinNode , mht->printVinNode , mht->eqValListInPair,mht->eqInfoListInPair );
	if (valInPair==NULL)return failure;
	s = appendNode(valInPair,v);
	if (s==failure)return s;
	s=addToHashTable(mht->ht,k,valInPair);
	status s2;
	s2=destroyList(valInPair);//maybe we dont need to free the pointer
	if (s2==failure)return s2;
	return s;
}

status destroyMultiValueHashTable(multiHash mht){
	if(mht==NULL)return failure;
	status s;
	s=destroyHashTable(mht->ht);
	if(s==failure)return s;
	mht->ht=NULL;
	mht->cpVinNode=NULL;
	mht->eqInfoListInPair=NULL;
	mht->eqValListInPair=NULL;
	mht->freeVinNode=NULL;
	mht->printVinNode=NULL;
	mht->printK=NULL;
	free(mht);
	mht=NULL;
	return success;
}

status displayMultiValueHashTable(multiHash mht, Element k){
	if(mht==NULL || k==NULL)return failure;
	linkedList temp = NULL;
	temp=(linkedList)lookupInMultiValueHashTable(mht,k);
	if (temp==NULL)return failure;
	status s;
	s=mht->printK(k);
	if (s==failure)return s;
	printf(": \n");
	s=displayList(temp);
	return s;
}

status removeFromMultiValueHashTable(multiHash mht, Element k, Element e){
	if(mht==NULL || k==NULL || e==NULL)return failure;
	linkedList tempList = (linkedList) lookupInMultiValueHashTable(mht,k);
	if(tempList==NULL)return failure;
	status s;
	s=deleteNode(tempList,e);
	if(s==failure)return s;
	if(getLengthList(tempList)==0){
		s=removeFromHashTable(mht->ht,k);
	}
	return s;
}

