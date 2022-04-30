/**************************************************************************
 * 	File name	:	AudioManager.hpp
 * 	Project name:	Project D.U.C.K
 * 	Author(s)	:	Hu Jun Ning (PRIMARY AUTHOR - 100%)
 *
 * All content © 2022 DigiPen Institute of Technology Singapore. All rights reserved.
**************************************************************************/

//Initialise audio
void Audio_Init(); //put at init

//Update audio
void Audio_Update(); //put at update

//Unload audio
void Audio_Unload(); //put at unload

//seperate audio functions
void maze_background_Audio(); //put at init (play once)

// background audio for the winscreen
void win_screen_background_Audio();

// background audio for the lose screen
void lose_screen_background_Audio();

// background audio for the menu
void menu_background_Audio();

// background audio for the combat
void combat_background_Audio();

// SFX audio for hitting the wall
void wall_hit_Audio(); //put at update

// SFX audio #1 for flipping the pages
void page_flip1_Audio();

// SFX audio #2 for flipping the pages
void page_flip2_Audio();

// SFX audio #1 for slashing audio
void slashing1_Audio();

// SFX audio #2 slashing audio
void slashing2_Audio();

// SFX audio for swimming movement in the maze
void swimming_Audio();

// SFX audio for drinking potions in combat
void portion_Audio();

// SFX audio for opening chests in the maze
void chest_open_Audio();

// SFX audio for clicking any buttons
void click_Audio();

// SFX audio for our game name logo intro page
void coin_drop_Audio();

// stops the audio for both BGM and SFX
void stop_Audio();

// increases bgm audio level
void increase_bgm_fader();

// decreases bgm audio level
void decrease_bgm_fader();

// increases sfx audio level
void increase_sfx_fader();

// decreases sfq audio level
void decrease_sfx_fader();

// mute all sounds
void mute_master_fader();

// unmute all sounds
void unmute_master_fader();