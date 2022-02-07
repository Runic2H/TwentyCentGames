#include "pch.hpp"

void System_Initialise() {

	fontId = AEGfxCreateFont("Roboto-Regular.ttf", 12);

}



void System_Exit() {

	AEGfxDestroyFont(fontId);
}