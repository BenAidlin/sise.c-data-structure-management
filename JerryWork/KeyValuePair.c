#include "KeyValuePair.h"
struct t_keyValuePair{
	Element key;
	Element val;
	PrintFunction printK;
	CopyFunction cpK;
	FreeFunction freeK;
	EqualFunction eqK;
	PrintFunction printV;
	CopyFunction cpV;
	FreeFunction freeV;

};
keyValuePair createKeyValuePair(Element k,Element v,PrintFunction printK,PrintFunction printV,CopyFunction cpK,CopyFunction cpV,FreeFunction freeK,FreeFunction freeV,EqualFunction eqK){
	if(k==NULL ||v==NULL ||printK==NULL ||printV==NULL ||cpK==NULL ||cpV==NULL ||freeK==NULL ||freeV==NULL ||eqK==NULL)
		return NULL;
	keyValuePair p=NULL;
	p = (keyValuePair)malloc(sizeof(struct t_keyValuePair));
	if(p==NULL)
		return NULL;
	p->cpK=cpK;
	p->key=p->cpK(k);//has to be a shallow copy
	if(p->key==NULL){
		p->cpK=NULL;//has to be a shallow copy
		free(p);
		p=NULL;
		return p;
	}
	p->freeK=freeK;
	p->cpV=cpV;
	p->val=p->cpV(v);
	if(p->val==NULL){
		p->cpV=NULL;
		p->freeK(p->key);
		p->freeK=NULL;
		p->cpK=NULL;
		free(p);
		p=NULL;
		return p;
	}
	p->freeV=freeV;
	p->eqK=eqK;
	p->printK=printK;
	p->printV=printV;
	return p;
}

status destroyKeyValuePair(keyValuePair p){
	if(p==NULL)
		return failure;
	if(p->freeK(p->key)==failure)
		return failure;
	if(p->freeV(p->val)==failure)
		return failure;
	p->cpK=NULL;
	p->cpV=NULL;
	p->eqK=NULL;
	p->freeK=NULL;
	p->freeV=NULL;
	p->printK=NULL;
	p->printV=NULL;
	free(p);
	p=NULL;
	return success;
}

status displayValue(keyValuePair p){
	if(p==NULL || p->val==NULL || p->printV==NULL)
		return failure;
	return p->printV(p->val);
}

status displayKey(keyValuePair p){
	if(p==NULL || p->key==NULL || p->printK==NULL)
		return failure;
	return p->printK(p->key);
}

Element getValue(keyValuePair p){
	if(p==NULL || p->val==NULL)
		return NULL;
	return p->val;
}
Element getKey(keyValuePair p){
	if(p==NULL || p->key==NULL)
		return NULL;
	return p->key;
}
bool isEqualKey(keyValuePair p, Element key){
	if(p==NULL || key==NULL)
		return false;
	return p->eqK(p->key,key);//the compare will be between 2 key, not between pair and key
}
PrintFunction getPrintK(keyValuePair p){
	if(p==NULL)return NULL;
	return p->printK;
}
PrintFunction getPrintV(keyValuePair p){
	if(p==NULL)return NULL;
	return p->printV;
}
CopyFunction getCopyK(keyValuePair p){
	if(p==NULL)return NULL;
	return p->cpK;
}
CopyFunction getCopyV(keyValuePair p){
	if(p==NULL)return NULL;
	return p->cpV;
}
FreeFunction getFreeK(keyValuePair p){
	if(p==NULL)return NULL;
	return p->freeK;
}
FreeFunction getFreeV(keyValuePair p){
	if(p==NULL)return NULL;
	return p->freeV;
}
EqualFunction getEqK(keyValuePair p){
	if(p==NULL)return NULL;
	return p->eqK;
}
