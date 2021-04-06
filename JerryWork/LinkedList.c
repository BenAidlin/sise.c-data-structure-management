#include "LinkedList.h"

typedef struct t_Node{
	Element val;
	struct t_Node *next;
	struct t_Node *prev;
}Node;

struct linkedList_t{
	Node *head;
	Node *tail;
	int length;
	CopyFunction copyVal;
	FreeFunction freeVal;
	PrintFunction printVal;
	EqualFunction equalVal;
	EqualFunction equalByInfo;
};

linkedList createLinkedList(CopyFunction copyVal, FreeFunction freeVal, PrintFunction printVal, EqualFunction equalVal, EqualFunction equalByInfo){
	if(copyVal==NULL || freeVal==NULL || printVal==NULL || equalVal==NULL || equalByInfo==NULL)
		return NULL;
	linkedList list=NULL;
	list = (linkedList)malloc(sizeof(struct linkedList_t));
	if(list==NULL)
		return NULL;
	list->head=NULL;
	list->tail=NULL;
	list->length=0;
	list->copyVal=copyVal;
	list->equalVal=equalVal;
	list->freeVal=freeVal;
	list->printVal=printVal;
	list->equalByInfo=equalByInfo;
	return list;
}

status appendNode(linkedList list, Element val){
	if(list==NULL || val ==NULL)
		return failure;
	Node *newNode=NULL;
	newNode=(Node*)malloc(sizeof(Node));
	if(newNode==NULL)
		return failure;
	newNode->val=list->copyVal(val);
	if(newNode->val==NULL)
		return failure;
	newNode->next=NULL;
	if(list->length>0){
		newNode->prev=list->tail;
		list->tail->next=newNode;
		list->length++;
		list->tail=newNode;
		}
	else{
		list->head = newNode;
		list->tail = newNode;
		list->length++;
		newNode->prev=NULL;
		}
	return success;
}

int getLengthList(linkedList list){
	if(list!=NULL)return list->length;
	else return -1;
}

Element searchByKeyInList(linkedList list, Element info){
	if(list==NULL || info==NULL)
		return NULL;
	Node *curr = NULL;
	curr = list->head;
	while (curr!=NULL){
		if(list->equalByInfo(curr->val,info)){  //we need to check if the inputs of copyfunc must get the same types or the can be different
			return curr->val;
			}
		curr=curr->next;
		}
	return NULL;
}

status deleteNode(linkedList list, Element element){
	Node *curr = list->head;
	int i;
	for (i=0;i<list->length;i++){
		if(list->equalVal(curr->val,element)){
			if(i==0){
				if(list->length==1){
					list->head=NULL;
					list->tail=NULL;
					list->freeVal(curr->val);
					curr->next=NULL;
					curr->prev=NULL;
					free(curr);
					list->length--;
					curr=NULL;
					return success;
					}
				else{
					list->head=curr->next;
					list->head->prev=NULL;
					list->freeVal(curr->val);
					curr->next=NULL;
					curr->prev=NULL;
					free(curr);
					list->length--;
					curr=NULL;
					return success;
					}
				}
			else if(i==list->length-1){
				list->tail=curr->prev;
				list->tail->next=NULL;
				list->freeVal(curr->val);
				curr->next=NULL;
				curr->prev=NULL;
				free(curr);
				list->length--;
				curr=NULL;
				return success;
				}
			else{
				curr->prev->next=curr->next;
				curr->next->prev=curr->prev;
				list->freeVal(curr->val);
				curr->next=NULL;
				curr->prev=NULL;
				free(curr);
				curr=NULL;
				list->length--;
				return success;
				}

			}
		curr=curr->next;
	}
	return failure;
}

status displayList(linkedList list){
	if(list==NULL)
		return failure;
	if(list->length==0){
		return success;
	}
	Node *curr = list->head;
	int i;
	for(i=0; i<=list->length;i++){
		if(i==list->length){
			break;
		}
		list->printVal(curr->val);
		curr=curr->next;
	}

	return success;
}

Element getDataByIndex(linkedList list, int index){
	if (index > list->length-1 || index<0 || list->length==0){return NULL;}
	int i=0;
	Node *curr = list->head;
	while (curr!=NULL){
		if(i==index){return curr->val;}
		curr=curr->next;
		i++;
		}
	return NULL;
}

status destroyList(linkedList list){
	if(list==NULL)
		return failure;
	Node *curr = list->head;
	while (curr!=NULL){
		if(list->freeVal(curr->val)==failure)
			return failure;
		Node *temp=curr;
		curr=curr->next;
		temp->next=NULL;
		temp->prev=NULL;
		free(temp);
		temp=NULL;
		}
	list->head=NULL;
	list->tail=NULL;
	list->copyVal=NULL;
	list->equalVal=NULL;
	list->freeVal=NULL;
	list->printVal=NULL;
	list->equalByInfo=NULL;
	free(list);
	list=NULL;
	return success;
}
CopyFunction getCopy(linkedList l){
	if(l==NULL)return NULL;
	return l->copyVal;
}
FreeFunction getFree(linkedList l){
	if(l==NULL)return NULL;
	return l->freeVal;
}
PrintFunction getPrint(linkedList l){
	if(l==NULL)return NULL;
	return l->printVal;
}
EqualFunction getEqNodes(linkedList l){
	if(l==NULL)return NULL;
	return l->equalVal;
}
EqualFunction getEqInfo(linkedList l){
	if(l==NULL)return NULL;
	return l->equalByInfo;
}


