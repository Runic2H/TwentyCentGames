/**************************************************************************
 * 	File name	:	GameStateManager.hpp
 * 	Project name:	Project D.U.C.K
 * 	Author(s)	:	Elton Teo Zhe Wei		(PRIMARY CONTRIBUTOR - 20%)
 *					Louis Mineo				(PRIMARY CONTRIBUTOR - 20%)
 *					Richmond Choo Tze Yong	(PRIMARY CONTRIBUTOR - 20%)
 *					Hu Jun Ning				(PRIMARY CONTRIBUTOR - 20%)
 *					Matthew Cheung Jun Yin	(PRIMARY CONTRIBUTOR - 20%)
 *
 * All content © 2022 DigiPen Institute of Technology Singapore. All rights reserved.
**************************************************************************/

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