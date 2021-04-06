#ifndef JERRY_H_
#define JERRY_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Defs.h"

typedef struct p_Planet{
	float x;
	float y;
	float z;
	char* p_name;
}Planet;

typedef struct o_Origin{
	char* dim;
	Planet* p_origin;
}Origin;

typedef struct p_PhysicalCharacteristic{
	char* pc_name;
	float val;
}PhysicalCharacteristic;

typedef struct j_Jerry{
	char* ID;
	int happy;
	Origin* o_jer;
	int num_of_charact;
	PhysicalCharacteristic** pc_arr;
}Jerry;


Planet* initplanet( char[], float , float , float );
Origin* initorigin( char[], Planet*);
Jerry* initjerry( char[], int, Origin*);
PhysicalCharacteristic* initpc(char[], float);
bool chek_pc(Jerry*, char[]);
bool add_pc(Jerry*, PhysicalCharacteristic*);
status del_pc(Jerry*, char[]);
status printplanet(Planet*);
status printjerry(Jerry*);
void deletejerry(Jerry*);
void deletepc(PhysicalCharacteristic*);
void deleteplanet(Planet*);
void deleteor(Origin*);
void changeHappinessJerry(Jerry* , int );
int getJerryHappiness(Jerry*);
#endif
