#include "Jerry.h"

//constructor for planet, returns pointer to planet build
Planet* initplanet(char name[], float x, float y, float z){
	Planet* plnt=NULL;
	plnt=(Planet*)malloc(sizeof(Planet));
	if (plnt!=NULL){
		plnt->x = x;
		plnt->y = y;
		plnt->z = z;
		plnt->p_name=(char*)malloc((strlen(name)+1)*sizeof(char));
		if (plnt->p_name!=NULL){strcpy(plnt->p_name,name);}
		return plnt;
	}
	printf("Memory Problem \n");
	return plnt;
}
//constructor for origin, returns pointer to origin build
Origin* initorigin( char dim[], Planet* planet){
	Origin* orig=NULL;
	orig=(Origin*)malloc(sizeof(Origin));
	if (orig!=NULL){
		orig->p_origin=planet;
		orig->dim=(char*)malloc((strlen(dim)+1)*sizeof(char));
		if (orig->dim!=NULL){strcpy(orig->dim,dim);}
		return orig;
	}
	printf("Memory Problem \n");
	return orig;
}

//constructor for jerry, returns pointer to jerry build
Jerry* initjerry( char name[], int happy, Origin* org){
	Jerry* jerry=NULL;
	jerry=(Jerry*)malloc(sizeof(Jerry));
	if (jerry!=NULL){
		jerry->ID=(char*)malloc((strlen(name)+1)*sizeof(char));
		if (jerry->ID!=NULL){strcpy(jerry->ID,name);}
		jerry->happy=happy;
		jerry->o_jer=org;
		jerry->num_of_charact=0;
		jerry->pc_arr=(PhysicalCharacteristic**)malloc(jerry->num_of_charact*sizeof(PhysicalCharacteristic*));
		return jerry;
	}
	printf("Memory Problem \n");
	return jerry;
}

PhysicalCharacteristic* initpc(char name[], float val){
	PhysicalCharacteristic* pc=NULL;
	pc=(PhysicalCharacteristic*)malloc(sizeof(PhysicalCharacteristic));
	if (pc!=NULL){
		pc->pc_name=(char*)malloc((strlen(name)+1)*sizeof(char));
		if(pc->pc_name!=NULL){strcpy(pc->pc_name,name);}
		pc->val=val;
		return pc;
	}
	printf("Memory Problem \n");
	return pc;
}

bool chek_pc(Jerry* jerry, char name[]){
	int i=0;
	for (i=0; i<jerry->num_of_charact ;i++){
		if (strcmp(jerry->pc_arr[i]->pc_name,name)==0){
			return true;
		}
	}
	return false;
}

bool add_pc(Jerry* jerry, PhysicalCharacteristic* pc){
	jerry->num_of_charact++;
	jerry->pc_arr=(PhysicalCharacteristic**)realloc(jerry->pc_arr, jerry->num_of_charact*sizeof(PhysicalCharacteristic*));
	if (jerry->pc_arr!=NULL){
		jerry->pc_arr[jerry->num_of_charact-1]=pc;
		return true;
	}
	else{
		jerry->num_of_charact--;
		printf("Memory Problem \n");
		return false;
	}
}

status del_pc(Jerry* jerry, char name[]){
	int i;
	for (i=0; i<jerry->num_of_charact; i++){
		if (strcmp(jerry->pc_arr[i]->pc_name,name)==0){
			if (jerry->pc_arr[i]!=NULL){
				if(jerry->pc_arr[i]->pc_name!=NULL){free(jerry->pc_arr[i]->pc_name);} // free the place of the name
				jerry->pc_arr[i]->pc_name=NULL;
				free(jerry->pc_arr[i]); // free the place of the pc
				jerry->pc_arr[i]=NULL;

				int j;
				for (j=i; j<jerry->num_of_charact-1; j++){
					jerry->pc_arr[j]=jerry->pc_arr[j+1];
					}
				jerry->pc_arr[jerry->num_of_charact-1]=NULL;
				jerry->num_of_charact--;
				jerry->pc_arr=(PhysicalCharacteristic**)realloc(jerry->pc_arr, jerry->num_of_charact*sizeof(PhysicalCharacteristic*));
				if (jerry->pc_arr!=NULL || jerry->num_of_charact==0){
					return success;
					}
				else{
					jerry->num_of_charact++;
					printf("Memory Problem \n");
					break;
					}
			}
		}//end if
	}//end for
	return failure;
}

status printplanet(Planet* plnt){
	if (plnt!=NULL){
		printf("Planet : %s (%.2f,%.2f,%.2f) \n",plnt->p_name, plnt->x, plnt->y, plnt->z);
		return success;
	}
	return failure;
}

status printjerry(Jerry* jerry){
	if (jerry!=NULL){
		printf("Jerry , ID - %s : \n", jerry->ID);
		printf("Happiness level : %d \n", jerry->happy);
		printf("Origin : %s \n", jerry->o_jer->dim);
		printplanet(jerry->o_jer->p_origin);
		if (jerry->num_of_charact!=0){
				printf("Jerry's physical Characteristics available : \n");
				printf("\t");
				int i;
				for(i=0;i<jerry->num_of_charact-1;i++){
					printf("%s : %.2f , ", jerry->pc_arr[i]->pc_name, jerry->pc_arr[i]->val);
				}
				printf("%s : %.2f \n", jerry->pc_arr[jerry->num_of_charact-1]->pc_name, jerry->pc_arr[jerry->num_of_charact-1]->val);
			}
		return success;
	}
	return failure;
}
void deletepc(PhysicalCharacteristic* pc){
	if (pc!=NULL){
		if (pc->pc_name!=NULL){free(pc->pc_name);}
		pc->pc_name=NULL;
		free(pc);
		pc=NULL;
	}
}

void deleteplanet(Planet* p){
	if (p!=NULL){
		if (p->p_name!=NULL){free(p->p_name);}
		p->p_name=NULL;
		free(p);
		p=NULL;
	}

}
void deleteor(Origin* or){
	if (or!=NULL){
		if(or->dim!=NULL){free(or->dim);}
		or->dim=NULL;
		free(or);
		or = NULL;
	}
}
void deletejerry(Jerry* jer){
	if (jer!=NULL){
		if(jer->ID!=NULL){free(jer->ID);}
		jer->ID = NULL;
		deleteor(jer->o_jer);
		int i;
		if(jer->pc_arr!=NULL){
			for (i=0; i<jer->num_of_charact; i++){
				deletepc(jer->pc_arr[i]);
			}
			free(jer->pc_arr);
		}
		jer->pc_arr=NULL;
		free(jer);
		jer = NULL;
	}
}

void changeHappinessJerry(Jerry* jer, int addHappy){
	if(jer->happy + addHappy > 100)
		jer->happy=100;
	else if(jer->happy + addHappy < 0)
		jer->happy=0;
	else jer->happy = jer->happy+addHappy;
}
int getJerryHappiness(Jerry* jer){
	return jer->happy;
}



