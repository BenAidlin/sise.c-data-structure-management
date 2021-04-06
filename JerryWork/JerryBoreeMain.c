#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Defs.h"
#include "LinkedList.h"
#include "MultiValueHashTable.h"
#include "Jerry.h"
status helper1(hashTable , int , Planet** , linkedList );
status helper2(hashTable, multiHash);
status helper3(hashTable, multiHash);
status helper4(hashTable , multiHash ,linkedList );
status helper5(multiHash ,hashTable , linkedList);
status helper6(linkedList  , multiHash , hashTable );
status helper7(linkedList , multiHash , hashTable ,Planet**, int);
status helper8(linkedList list_of_jerries);
/*clear planets from the heap*/
void clear_planets(int num_of_planets, Planet** arr_of_plnt) { for(int i=0; i<num_of_planets; i++) { deleteplanet(arr_of_plnt[i]); } }
//functions for main linked list of jerries.
Element main_cpPoinetOfJerry(Element e){
	if(e==NULL)return e;
	Jerry* new_pointer = (Jerry*)e;
	return (Element)new_pointer;
}

status main_freePoinetOfJerry(Element e){
	if(e==NULL)return failure;
	Jerry* temp_pointer = (Jerry*)e;
	deletejerry(temp_pointer);
	return success;
}
status main_printPointerofJerry(Element e){
	if(e==NULL)return failure;
	Jerry* temp_pointer = (Jerry*)e;
	return printjerry(temp_pointer);
}
bool main_equalPointersOfJerries(Element e1, Element e2){
	if(e1==NULL || e2==NULL)return false;
	Jerry* temp_pointer1 = (Jerry*)e1;
	Jerry* temp_pointer2 = (Jerry*)e2;
	return (bool)(strcmp(temp_pointer1->ID,temp_pointer2->ID)==0);
}

bool main_equalInfoPointerOfJerries(Element e, Element id){
	if(e==NULL || id==NULL)return false;
	Jerry* temp_pointer = (Jerry*)e;
	char* ID=(char*)id;
	return (bool)(strcmp(temp_pointer->ID,ID)==0);
}
//functions for mht keys(pc.name)
int mht_transPcName(Element e){
	if(e==NULL)return -1;
	char *name = (char*)e;
	int i=0,sum=0;
	for(i=0;i<strlen(name);i++){
		sum+=(int)name[i];
	}
	return sum;
}

Element mht_copyPcName(Element e){
	if(e==NULL)return e;
	char* pcName=(char*)e;
	char* ret;
	ret = (char*)malloc(sizeof(char)*(strlen(pcName)+1));
	strcpy(ret,pcName);
	return (Element)ret;
}
status mht_freePcName(Element e){
	if(e==NULL)return failure;
	free((char*)e);
	e=NULL;
	return success;
}
bool mht_eqPcName(Element e1, Element e2){
	if(e1==NULL || e2==NULL)return false;
	return(strcmp((char*)e1,(char*)e2)==0);
}
status mht_printPcName(Element e){
	if(e==NULL)return failure;
	printf("%s ",(char*)e);
	return success;
}
//functions for mht values(jerries pointers)
Element mht_copyPointerJer(Element e){
	if(e==NULL)return e;
	Jerry* jer = (Jerry*)e;
	return (Element)jer;
}
status mht_freePointerJer(Element e){
	if(e==NULL)return failure;
	e=NULL;
	return success;
}

status mht_printPointerJer(Element e){return main_printPointerofJerry(e);}

bool mht_eqPointerJer(Element e1,Element e2){return main_equalPointersOfJerries(e1,e2);}

bool mht_eqPointerInfoJer(Element e1, Element e2){return main_equalInfoPointerOfJerries(e1,e2);}

int thrBigestPrimeNumer(int num){
	int i,j;
	for(i=num;i>-1;i++){
		for(j=2;j<num;j++){
			if(j==num-1 && i%j!=0){return i;}
			else if (i%j==0){break;}
		}
	}
	return 13;
}



int main(int argc, char *argv[]){
    FILE *fp;
    char str[1000];
    char* filename = argv[2];
    int num_of_planets = atoi(argv[1]);
    Planet* arr_of_plnts[num_of_planets];
    linkedList list_of_jerries= createLinkedList(main_cpPoinetOfJerry, main_freePoinetOfJerry, main_printPointerofJerry, main_equalPointersOfJerries, main_equalInfoPointerOfJerries);
    int num_of_pc=0;
    fp = fopen(filename, "r");
    fgets(str, 1000, fp); //now str is "Planets"

    int i=0;
    //making garbage NULL
    for (i=0; i<num_of_planets;i++){arr_of_plnts[i]=NULL;}
    //make planets
    for (i=1; i<num_of_planets+1; i++){
    	fgets(str, 1000, fp); //now str is kind of planet
    	char line[strlen(str)+1];
    	strcpy(line,str);

    	char *pt;
		pt = strtok (line,",");
    	char* pname= pt;

    	pt = strtok (NULL,",");
    	float x = atof(pt);

    	pt = strtok (NULL,",");
    	float y= atof(pt);

    	pt = strtok (NULL,",");
    	float z = atof(pt);

    	arr_of_plnts[i-1]=initplanet(pname,x,y,z);
    	if (arr_of_plnts[i-1]==NULL){
			clear_planets(num_of_planets, arr_of_plnts);
			return 0;
    	}
    }
	/*int j;
	for(j=0;j<num_of_planets;j++){
		printplanet(arr_of_plnts[j]);
	}*/
    fgets(str, 1000, fp); //now str is "Jerry"
    char prev_line[strlen(str)+1];
	strcpy(prev_line,str);

    fgets(str, 1000, fp); // now is kind of jerry
	char curr_line[strlen(str)+1];
	strcpy(curr_line,str);
	int flag=0;
	//make jerries
	while(flag==0){
		char *pt;
		pt = strtok (curr_line,",");
		char* ID= pt;

		pt = strtok (NULL,",");
		char* dim_name=pt;

		pt = strtok (NULL,",");
		char* pname=pt;

		pt = strtok (NULL,",");
		int happy = atoi(pt);

		int k;
		for (k=0; k<num_of_planets;k++){
			if (strcmp(pname,arr_of_plnts[k]->p_name)==0){
				Origin *orig = initorigin(dim_name,arr_of_plnts[k]);
				if (orig==NULL){
					deleteor(orig);
					destroyList(list_of_jerries);
					clear_planets(num_of_planets, arr_of_plnts);
					return 0;
					}
				Jerry* temp_jerry = initjerry(ID, happy, orig);
				status s=appendNode(list_of_jerries,(Element)temp_jerry);
				temp_jerry=NULL;
				if (s==failure){
					destroyList(list_of_jerries);
					clear_planets(num_of_planets, arr_of_plnts);
					return 0;
					}
				break;
				}
			}

		//add jerries pc
		while(true){
			char prev_line[strlen(curr_line)+1];
			strcpy(prev_line,str);
			fgets(str, 1000, fp); // now is kind of jerry
			char curr_line[strlen(str)+1];
			strcpy(curr_line,str);
			if(strcmp(curr_line,prev_line)==0){
				flag++;
				break;
			}//end of config file
			if (curr_line[0]!='\t'){break;}
			//printf("%s\n",line);
			pt = strtok (curr_line,":");
			char* pcname = pt;

			//printf("height? %s\n", pcname);
			pt = strtok (NULL,"\n");
			//printf("%s what is pt\n",pt);
			float pcval = atof(pt)+0.001;
			//printf("%f what is pcval\n",pcval);
			PhysicalCharacteristic* new_pc = initpc(pcname+1,pcval);
			num_of_pc++;
			if (new_pc==NULL){
				deletepc(new_pc);
				destroyList(list_of_jerries);
				clear_planets(num_of_planets, arr_of_plnts);
				return 0;
				}
			Jerry* last_jerry = (Jerry*)getDataByIndex(list_of_jerries,getLengthList(list_of_jerries)-1);
			bool b = add_pc(last_jerry,new_pc);
			if(b==false){
				deletepc(new_pc);
				destroyList(list_of_jerries);
				clear_planets(num_of_planets, arr_of_plnts);
				return 0;
				}

			}//end pc while loop
		strcpy(curr_line,str);
	}//end jerris while loop
	//all jerries are in a linked list and all pc's are in an array
	fclose(fp);

	//creat multi hash table: key->pcname, val->list of pointers of jerris
	multiHash mht = createMultiValueHashTable(mht_eqPointerJer,mht_eqPointerInfoJer,mht_copyPcName, mht_freePcName, mht_printPcName, mht_copyPointerJer, mht_freePointerJer, mht_printPointerJer, mht_eqPcName,mht_transPcName, thrBigestPrimeNumer(num_of_pc));
	if(mht==NULL){
		destroyList(list_of_jerries);
		clear_planets(num_of_planets, arr_of_plnts);
		return 0;
	}
	int j;
	for(i=0;i<getLengthList(list_of_jerries);i++){
		Jerry* jer = (Jerry*)getDataByIndex(list_of_jerries, i);
		for(j=0;j<jer->num_of_charact;j++){
			char *name = jer->pc_arr[j]->pc_name;
			status s=addToMultiValueHashTable(mht,name,jer);
			if(s==failure){
				destroyMultiValueHashTable(mht);
				destroyList(list_of_jerries);
				clear_planets(num_of_planets, arr_of_plnts);
				return 0;
			}
		}
	}
	/*printf("PRINT MULTI HASH \n");
	displayMulti(mht);*/

	//create hash table: key->jerry ID, val->pointer of jerry
	hashTable ht = createHashTable(mht_copyPcName, mht_freePcName, mht_printPcName, mht_copyPointerJer, mht_freePointerJer, mht_printPointerJer, mht_eqPcName, mht_transPcName, thrBigestPrimeNumer(getLengthList(list_of_jerries)));
	if(ht==NULL){
		destroyMultiValueHashTable(mht);
		destroyList(list_of_jerries);
		clear_planets(num_of_planets, arr_of_plnts);
		return 0;
	}
	for(i=0;i<getLengthList(list_of_jerries);i++){
		Jerry* jer = (Jerry*)getDataByIndex(list_of_jerries, i);
		char *name = jer->ID;
		status s=addToHashTable(ht,name,jer);
		if(s==failure){
			destroyMultiValueHashTable(mht);
			destroyHashTable(ht);
			destroyList(list_of_jerries);
			clear_planets(num_of_planets, arr_of_plnts);
			return 0;
		}
	}
	/*printf("PRINT HASH \n");
	displayHashElements(ht);*/


    int ch = 1;
    char inp[300];
    while( ch != 9 ) {
    	printf("Welcome Rick, what are your Jerry's needs today ? \n");
    	printf("1 : Take this Jerry away from me \n");
    	printf("2 : I think I remember something about my Jerry \n");
    	printf("3 : Oh wait. That can't be right \n");
    	printf("4 : I guess I will take back my Jerry now \n");
    	printf("5 : I can't find my Jerry. Just give me a similar one \n");
    	printf("6 : I lost a bet. Give me your saddest Jerry \n");
    	printf("7 : Show me what you got \n");
    	printf("8 : Let the Jerries play \n");
		printf("9 : I had enough. Close this place \n");

    	scanf("%s", inp);
    	if (strlen(inp)>1 || '1'>inp[0] || inp[0]>'9'){ch=-1;}
    	else{ch=atoi(inp);}
    	switch( ch ){
    	case 1:
    		helper1(ht, num_of_planets, arr_of_plnts, list_of_jerries);
    		break;
    	case 2:
    		helper2(ht, mht);
    		break;
    	case 3:
    		helper3(ht,mht);
    		break;

    	case 4:
    		helper4(ht, mht,list_of_jerries);
    		break;

    	case 5:
    		helper5(mht, ht, list_of_jerries);
    		break;

    	case 6:
    		helper6(list_of_jerries ,mht, ht);
    		break;

    	case 7:
	 	 	helper7(list_of_jerries , mht, ht,arr_of_plnts, num_of_planets);
			break;
    	case 8:
    		helper8(list_of_jerries);
			break;
    	default:
    		if (ch==9){break;}
    		printf("Rick this option is not known to the daycare ! \n");
    		break;
      }//end cases

    }//end while loop

	destroyMultiValueHashTable(mht);
	destroyHashTable(ht);
	destroyList(list_of_jerries);
	clear_planets(num_of_planets, arr_of_plnts);
	printf("The daycare is now clean and close ! \n");
    return 0;
}

//add new jerry to the daycare
status helper1(hashTable ht, int num_of_planets, Planet** arrP, linkedList list_of_jerries){
	char tempID[300];
	char plntName[300];
	char dim[300];
	int happy;
	Jerry* jer;

	printf("What is your Jerry's ID ? \n");
	scanf("%s", tempID);
	char* ID = (char*)malloc(sizeof(char)*(strlen(tempID)+1));
	if(ID==NULL)
		return failure;
	strcpy(ID,tempID);
	Element e=lookupInHashTable(ht,(Element)ID);
	if (e!=NULL){
		free(ID);
		ID=NULL;
		printf("Rick did you forgot ? you already left him here ! \n");
		return failure;
	}
	printf("What planet is your Jerry from ? \n");
	scanf("%s",plntName);
	int i;
	for(i=0;i<num_of_planets;i++){
		if(strcmp(arrP[i]->p_name,plntName)==0)
			break;
	}
	if(i==num_of_planets)
	{
		printf("%s is not a known planet ! \n",plntName);
		free(ID);
		ID=NULL;
		return failure;
	}
	printf("What is your Jerry's dimension ? \n");
	scanf("%s",dim);
	printf("How happy is your Jerry now ? \n");
	scanf("%d",&happy);
	Origin* O = initorigin(dim,arrP[i]);
	jer = initjerry(tempID,happy,O);
	appendNode(list_of_jerries,(Element)jer);
	addToHashTable(ht, ID, (Element)jer);
	printjerry(jer);
	jer=NULL;
	free(ID);
	ID=NULL;
	return success;
}

//add pc to jerry
status helper2(hashTable ht, multiHash mht){
	char tempID[300];
	char pcName[300];
	char val[300];
	Jerry* jer;

	printf("What is your Jerry's ID ? \n");
	scanf("%s", tempID);
	char* ID = (char*)malloc(sizeof(char)*(strlen(tempID)+1));
	if(ID==NULL)
		return failure;
	strcpy(ID,tempID);
	Element e=lookupInHashTable(ht,(Element)ID);
	if (e==NULL){
		free(ID);
		ID=NULL;
		printf("Rick this Jerry is not in the daycare ! \n");
		return failure;
	}
	printf("What physical characteristic can you add to Jerry - %s ? \n",tempID);
	scanf("%s",pcName);
	jer = (Jerry*)e;
	int i=0;
	for(i=0;i<jer->num_of_charact;i++){
		if(strcmp(jer->pc_arr[i]->pc_name,pcName)==0){
			printf("The information about his %s already available to the daycare ! \n", pcName);
			free(ID);
			ID=NULL;
			return failure;
		}
	}
	printf("What is the value of his %s ? \n",pcName);
	scanf("%s",val);
	float num = atof(val)+0.001;
	PhysicalCharacteristic* newPc = initpc(pcName, num);
	add_pc(jer,newPc);
	status s= addToMultiValueHashTable(mht, (Element)pcName, (Element)jer);
	displayMultiValueHashTable(mht, (Element)pcName);
	free(ID);
	ID=NULL;
	jer=NULL;
	return s;
}

//delete pc from jerry
status helper3(hashTable ht, multiHash mht){
	char tempID[300];
	char pcName[300];
	Jerry* jer;

	printf("What is your Jerry's ID ? \n");
	scanf("%s", tempID);
	char* ID = (char*)malloc(sizeof(char)*(strlen(tempID)+1));
	if(ID==NULL)
		return failure;
	strcpy(ID,tempID);
	Element e=lookupInHashTable(ht,(Element)ID);
	if (e==NULL){
		free(ID);
		ID=NULL;
		printf("Rick this Jerry is not in the daycare ! \n");
		return failure;
	}
	printf("What physical characteristic do you want to remove from Jerry - %s ? \n",tempID);
	scanf("%s",pcName);
	jer = (Jerry*)e;
	int i;
	for(i=0;i<jer->num_of_charact;i++){
		if(strcmp(jer->pc_arr[i]->pc_name,pcName)==0){
			del_pc(jer, pcName);
			char* temp = (char*)malloc(sizeof(char)*(strlen(pcName)+1));
			strcpy(temp,pcName);
			removeFromMultiValueHashTable(mht,(Element)temp,(Element)jer);
			printjerry(jer);
			free(ID);
			free(temp);
			jer=NULL;
			ID=NULL;
			temp=NULL;
			return success;
		}
	}
	printf("The information about his %s not available to the daycare ! \n", pcName);
	free(ID);
	ID=NULL;
	return failure;
}

//delete jerry
status helper4(hashTable ht, multiHash mht,linkedList list_of_jerries){
	char tempID[300];
	Jerry* jer;
	printf("What is your Jerry's ID ? \n");
	scanf("%s", tempID);
	char* ID = (char*)malloc(sizeof(char)*(strlen(tempID)+1));
	if(ID==NULL)
		return failure;
	strcpy(ID,tempID);
	Element e=lookupInHashTable(ht,(Element)ID);
	if (e==NULL){
		free(ID);
		ID=NULL;
		printf("Rick this Jerry is not in the daycare ! \n");
		return failure;
	}
	jer = (Jerry*)e;
	removeFromHashTable(ht, (Element)jer->ID);
	int i;
	for(i=0;i<jer->num_of_charact;i++){
		removeFromMultiValueHashTable(mht,(Element)jer->pc_arr[i]->pc_name,(Element)jer);
	}
	deleteNode(list_of_jerries,(Element)jer);
	printf("Rick thank you for using our daycare service ! Your Jerry awaits ! \n");
	free(ID);
	ID=NULL;
	return success;

}

//takes similar jerry
status helper5(multiHash mht,hashTable ht, linkedList list_of_jerries){
	char tempPC[300];
	char tempval[300];

	printf("What do you remember about your Jerry ? \n");
	scanf("%s", tempPC);
	char* PC = (char*)malloc(sizeof(char)*(strlen(tempPC)+1));
	if(PC==NULL)
		return failure;
	strcpy(PC,tempPC);
	linkedList tempList = (linkedList)lookupInMultiValueHashTable(mht,(Element)PC);
	if (tempList==NULL){
		printf("Rick we can not help you - we do not know any Jerry's %s ! \n",PC);
		free(PC);
		return failure;
	}
	printf("What do you remember about the value of his %s ? \n",PC);
	scanf("%s",tempval);
	float similar = atof(tempval)+0.001;
	int i,j,index;
	float minDiff;
	Jerry* jer=NULL;
	for(i=0;i<getLengthList(tempList);i++){
		jer=(Jerry*)getDataByIndex(tempList,i);
		for(j=0;j<jer->num_of_charact;j++){
			if(strcmp(jer->pc_arr[j]->pc_name,PC)==0){
				float num = (similar-jer->pc_arr[j]->val);
				if(num<0){num*=-1;}
				if(i==0){
					minDiff=num;
					index=i;
					break;
					}
				if(minDiff>num){
					minDiff=num;
					index=i;
					}
				break;
				}
		}//end inner loop
	}//end out loop
	printf("Rick this is the most suitable Jerry we found : \n");
	jer = (Jerry*)getDataByIndex(tempList,index);
	printjerry(jer);
	removeFromHashTable(ht, (Element)jer->ID);
	for(i=0;i<jer->num_of_charact;i++){
		removeFromMultiValueHashTable(mht,(Element)jer->pc_arr[i]->pc_name,(Element)jer);
	}
	deleteNode(list_of_jerries,(Element)jer);
	printf("Rick thank you for using our daycare service ! Your Jerry awaits ! \n");
	free(PC);
	PC=NULL;
	return success;
}
status helper6(linkedList list_of_jerries , multiHash mht, hashTable ht){
	if(getLengthList(list_of_jerries)==0){
		printf("Rick we can not help you - we currently have no Jerries in the daycare ! \n");
		return failure;
	}
	int i;
	Jerry* jerToRet, *jer;

	for(i=0;i<getLengthList(list_of_jerries);i++){
		if(i==0){
			jerToRet = (Jerry*)getDataByIndex(list_of_jerries,i);
		}
		else{
			jer =(Jerry*)getDataByIndex(list_of_jerries,i);
			if(jerToRet->happy > jer->happy)
				jerToRet=jer;
		}
	}
	printf("Rick this is the most suitable Jerry we found : \n");
	printjerry(jerToRet);
	removeFromHashTable(ht, (Element)jerToRet->ID);
	for(i=0;i<jerToRet->num_of_charact;i++){
		removeFromMultiValueHashTable(mht,(Element)jerToRet->pc_arr[i]->pc_name,(Element)jerToRet);
	}
	deleteNode(list_of_jerries,(Element)jerToRet);
	printf("Rick thank you for using our daycare service ! Your Jerry awaits ! \n");
	jer=NULL;
	jerToRet=NULL;
	return success;
}
status helper7(linkedList list_of_jerries , multiHash mht, hashTable ht,Planet** arr_of_plnts, int num_of_planets){
    int ch = 1;
    char inp[300];
    int flag=0, i;
	printf("What information do you want to know ? \n");
	printf("1 : All Jerries \n");
	printf("2 : All Jerries by physical characteristics \n");
	printf("3 : All known planets \n");
	scanf("%s", inp);
	if (strlen(inp)>1 || '1'>inp[0] || inp[0]>'3'){ch=-1;}
	else{ch=atoi(inp);}
	switch ( ch ){
    case 1:
    	if(getLengthList(list_of_jerries)==0){
    		printf("Rick we can not help you - we currently have no Jerries in the daycare ! \n");
    	}
    	else{
    		displayList(list_of_jerries);
    		flag++;
    	}
    	break;
    case 2:
    	printf("What physical characteristics ? \n");
		char tempPC[300];
		scanf("%s", tempPC);
		char* PC = (char*)malloc(sizeof(char)*(strlen(tempPC)+1));
		if(PC==NULL)
			return failure;
		strcpy(PC,tempPC);
		linkedList tempList = (linkedList)lookupInMultiValueHashTable(mht,(Element)PC);
		if (tempList==NULL){
			printf("Rick we can not help you - we do not know any Jerry's %s ! \n",PC);
			free(PC);
			return failure;
		}
		//displayMultiValueHashTable(mht, (Element)PC);
		printf("%s : \n",tempPC);
		displayList(tempList);
		free(PC);
		PC=NULL;
		flag++;
    	break;
    case 3:

    	for(i=0;i<num_of_planets;i++){
    		printplanet(arr_of_plnts[i]);
    	}
    	flag++;
    	break;
    default:
    	printf("Rick this option is not known to the daycare ! \n");//check the space after the-!
    	break;
    }
	if(flag==0){return failure;}
	return success;
}

status helper8(linkedList list_of_jerries){
	if(getLengthList(list_of_jerries)==0){
		printf("Rick we can not help you - we currently have no Jerries in the daycare ! \n");
		return failure;
	}
	int ch = 1;
	char inp[300];
	int i;
	printf("What activity do you want the Jerries to partake in ? \n");
	printf("1 : Interact with fake Beth \n");
	printf("2 : Play golf \n");
	printf("3 : Adjust the picture settings on the TV \n");
	scanf("%s", inp);
	if (strlen(inp)>1 || '1'>inp[0] || inp[0]>'3'){ch=-1;}
	else{ch=atoi(inp);}
	switch ( ch ){
	    case 1:
	    	for(i=0;i<getLengthList(list_of_jerries);i++){
	    		Jerry* jer = (Jerry*)getDataByIndex(list_of_jerries, i);
	    		if(getJerryHappiness(jer)>=20)changeHappinessJerry(jer,15);
	    		if(getJerryHappiness(jer)<20)changeHappinessJerry(jer,-5);
	    	}
	    	printf("The activity is now over ! \n");
			displayList(list_of_jerries);
	    	break;
	    case 2:
	    	for(i=0;i<getLengthList(list_of_jerries);i++){
				Jerry* jer = (Jerry*)getDataByIndex(list_of_jerries, i);
				if(getJerryHappiness(jer)>=50)changeHappinessJerry(jer,10);
				if(getJerryHappiness(jer)<50)changeHappinessJerry(jer,-10);
	    	}
	    	printf("The activity is now over ! \n");
			displayList(list_of_jerries);
	    	break;
	    case 3:
	    	for(i=0;i<getLengthList(list_of_jerries);i++){
				Jerry* jer = (Jerry*)getDataByIndex(list_of_jerries, i);
				changeHappinessJerry(jer,20);
	    	}
	    	printf("The activity is now over ! \n");
			displayList(list_of_jerries);
	    	break;
	    default:
	    	printf("Rick this option is not known to the daycare ! \n");//check the space after the-!
	    	break;
	    }
		return success;
}





