#pragma once

typedef void(*FP)(void);	//function pointers

extern int current, previous, next;

extern FP fpLoad, fpInitialize, fpUpdate, fpDraw, fpFree, fpUnload;


/*
	Initializes GSM, sets all the states to the same.
*/
void GSM_Initialize(int startingState);


/*
	Updates GSM, contains the different states and their respective functions. (Levels, restart, quit)
*/
void GSM_Update();