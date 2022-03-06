#include "pch.hpp"



void Input_Handle() {
//	outFile << "Input:Handle" << std::endl;

	if (AEInputCheckTriggered(AEVK_1)) {
		next = MAZE;
	}

	if (AEInputCheckTriggered(AEVK_2)) {
		next = COMBAT;
	}

	//if (AEInputCheckTriggered(AEVK_ESCAPE)) {
	//	next = GS_QUIT;
	//}
}