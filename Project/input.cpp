/**************************************************************************
 * 	File name	:	input.cpp
 * 	Project name:	Project D.U.C.K
 * 	Author(s)	:	Elton Teo Zhe Wei		(PRIMARY CONTRIBUTOR - 100%)
 *
 * All content © 2022 DigiPen Institute of Technology Singapore. All rights reserved.
**************************************************************************/

#include "pch.hpp"

/**************************************************************
*	for alt tabbing window in fullscreen mode
***************************************************************/
void Input_Handle() {

	is_focused = AESysGetWindowHandle() == GetFocus();
	if (systemsettings.fullscreen == 1 && !is_focused)
	{
		ShowWindow(AESysGetWindowHandle(), SW_MINIMIZE);
	}
	if (AEInputCheckCurr(AEVK_LALT) || AEInputCheckCurr(AEVK_RALT))
	{
		if (AEInputCheckTriggered(AEVK_RETURN))
		{
			systemsettings.fullscreen == 1 ? systemsettings.fullscreen = 0 : systemsettings.fullscreen = 1;
			AEToogleFullScreen(systemsettings.fullscreen);
		}
	}

}