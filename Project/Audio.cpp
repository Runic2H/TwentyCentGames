/**************************************************************************
 * 	File name	:	Audio.cpp
 * 	Project name:	Project D.U.C.K
 * 	Author(s)	:	Hu Jun Ning (PRIMARY AUTHOR - 100%)
 *
 * All content © 2022 DigiPen Institute of Technology Singapore. All rights reserved.
**************************************************************************/

#include "pch.hpp"

constexpr auto MAX_CHANNELS = 64;
FMOD::System* audio_system;
FMOD_RESULT result;

//**		BGM		**//
FMOD::Sound* maze_bgm = nullptr;
FMOD::Sound* win_screen_bgm = nullptr;
FMOD::Sound* lose_screen_bgm = nullptr;
FMOD::Sound* menu_bgm = nullptr;
FMOD::Sound* combat_bgm = nullptr;

//**		effects		**//
FMOD::Sound* wall_sound = nullptr;
FMOD::Sound* page_flip_sound1 = nullptr;
FMOD::Sound* page_flip_sound2 = nullptr;
FMOD::Sound* slashing_sound1 = nullptr;
FMOD::Sound* slashing_sound2 = nullptr;
FMOD::Sound* swimming_sound = nullptr;
FMOD::Sound* portion_sound = nullptr;
FMOD::Sound* chest_open_sound = nullptr;
FMOD::Sound* click_sound = nullptr;
FMOD::Sound* coin_drop_sound = nullptr;

extern FMOD::Channel* bgm_channel;			//individual channels for bgm
extern FMOD::Channel* sfx_channel;			//individual channels for effects
extern FMOD::ChannelGroup* bgm_group;		//group for bgm
extern FMOD::ChannelGroup* sfx_group;		//group for effects
extern FMOD::ChannelGroup* master_fader;	//controls all volume


//Initialise audio
void Audio_Init()
{
	//create audio system
	result = FMOD::System_Create(&audio_system);
	//initialise the audio system with number of channels
	result = audio_system->init(MAX_CHANNELS, FMOD_INIT_NORMAL, nullptr);
	
	//create 3 channel groups
	audio_system->createChannelGroup("master_fader", &master_fader);
	audio_system->createChannelGroup("Music", &bgm_group);
	audio_system->createChannelGroup("SFX", &sfx_group);
	//add the 2 groups into Master_Fader (controls all volumes)
	master_fader->addGroup(bgm_group);
	master_fader->addGroup(sfx_group);

	//**		BGM		**//
	//maze background
	audio_system->createSound("Music/VIETNAM-COUNTRY_GEN-HDF-25318.wav", FMOD_LOOP_NORMAL, nullptr, &maze_bgm);
	//win screen background
	audio_system->createSound("Music/PRIDE OF OWNERSHIP - Corporate MSCCRP1_35.wav", FMOD_LOOP_NORMAL, nullptr, &win_screen_bgm);
	//lose screen background
	audio_system->createSound("Music/TubaComedy CTE09_40.2.wav", FMOD_DEFAULT, nullptr, &lose_screen_bgm);
	//menu background
	audio_system->createSound("Music/DAYLIGHT STROLL - EasyListeningMid MSCEZL4_09.wav", FMOD_LOOP_NORMAL, nullptr, &menu_bgm);
	//combat background
	audio_system->createSound("Music/PUNCH DRUNK - DanceTechno MSCDNT2_37.wav", FMOD_LOOP_NORMAL, nullptr, &combat_bgm);
	
	//**		effects		**//
	//hit on wall
	audio_system->createSound("Music/HIT-WHOOSH_GEN-HDF-14186.wav", FMOD_DEFAULT, nullptr, &wall_sound);
	//page flip sound 1
	audio_system->createSound("Music/BOOK-BIBLE_GEN-HDF-04344.wav", FMOD_DEFAULT, nullptr, &page_flip_sound1);
	//page flip sound 2
	audio_system->createSound("Music/BOOK-PAPERBACK_GEN-HDF-04515.wav", FMOD_DEFAULT, nullptr, &page_flip_sound2);
	//slashing sound 1
	audio_system->createSound("Music/HORROR_GEN-HDF-14514.wav", FMOD_DEFAULT, nullptr, &slashing_sound1);
	//slashing sound 2
	audio_system->createSound("Music/HORROR_GEN-HDF-14515.wav", FMOD_DEFAULT, nullptr, &slashing_sound2);
	//swimming sound
	audio_system->createSound("Music/WATER-SPLASH_GEN-HDF-25630-short.wav", FMOD_DEFAULT, nullptr, &swimming_sound);
	//portion drinking
	audio_system->createSound("Music/ICE-GLASS_GEN-HDF-15591.wav", FMOD_DEFAULT, nullptr, &portion_sound);
	//chest open
	audio_system->createSound("Music/DOOR-COMPARTMENT_GEN-HDF-09514.wav", FMOD_LOOP_OFF, nullptr, &chest_open_sound);
	//click
	audio_system->createSound("Music/THERMOSTAT_GEN-HDF-23295.wav", FMOD_LOOP_OFF, nullptr, &click_sound);
	//coin drop
	audio_system->createSound("Music/CoinDrop_CTE01_46.1.ogg", FMOD_LOOP_OFF, nullptr, &coin_drop_sound);

	if (systemsettings.mute == 1)
	{
		mute_master_fader();
	}
	else
	{
		unmute_master_fader();
	}

	bgm_group->setVolume(bgm_volume);
	sfx_group->setVolume(sfx_volume);

}

//Update audio
void Audio_Update()
{
	result = audio_system->update();
}

//Unload audio
void Audio_Unload()
{
	//**		BGM		**//
	maze_bgm->release();
	win_screen_bgm->release();
	lose_screen_bgm->release();
	menu_bgm->release();
	combat_bgm->release();

	//**		effects		**//
	wall_sound->release();
	page_flip_sound1->release();
	page_flip_sound2->release();
	slashing_sound1->release();
	slashing_sound2->release();
	swimming_sound->release();
	portion_sound->release();
	chest_open_sound->release();
	click_sound->release();
	coin_drop_sound->release();
}

//seperate audio functions
//**		BGM		**//
void maze_background_Audio()
{
	// Play the sound.
	result = audio_system->playSound(maze_bgm, nullptr, false, &bgm_channel);
	bgm_channel->setChannelGroup(bgm_group);

	//adjusting_master_fader();
	//bool isPlaying = false;
	////check if sound is playing or not
	//channel->isPlaying(&isPlaying);
	//channel->stop();
	//channel->setMute(1);
}

// background audio for the winscreen
void win_screen_background_Audio()
{
	result = audio_system->playSound(win_screen_bgm, nullptr, false, &bgm_channel);
	bgm_channel->setChannelGroup(bgm_group);
	//////std::cout << "Win screen audio\n\n";
}

// background audio for the lose screen
void lose_screen_background_Audio()
{
	result = audio_system->playSound(lose_screen_bgm, nullptr, false, &bgm_channel);
	bgm_channel->setChannelGroup(bgm_group);
	//////std::cout << "Lose screen audio\n\n";
}

// background audio for the menu
void menu_background_Audio()
{
	result = audio_system->playSound(menu_bgm, nullptr, false, &bgm_channel);
	bgm_channel->setChannelGroup(bgm_group);
	////std::cout << "menu background sound audio\n\n";
}

// background audio for the combat
void combat_background_Audio()
{
	result = audio_system->playSound(combat_bgm, nullptr, false, &bgm_channel);
	bgm_channel->setChannelGroup(bgm_group);
	////std::cout << "menu background sound audio\n\n";
}


//**		effects		**//

// SFX audio for hitting the wall
void wall_hit_Audio()
{
	result = audio_system->playSound(wall_sound, nullptr, false, &sfx_channel);
	sfx_channel->setChannelGroup(sfx_group);
	////std::cout << "Hit wall audio\n\n";
}

// SFX audio #1 for flipping the pages
void page_flip1_Audio()
{
	result = audio_system->playSound(page_flip_sound1, nullptr, false, &sfx_channel);
	sfx_channel->setChannelGroup(sfx_group);
	////std::cout << "Page flip 1 audio\n\n";
}

// SFX audio #2 for flipping the pages
void page_flip2_Audio()
{
	result = audio_system->playSound(page_flip_sound2, nullptr, false, &sfx_channel);
	sfx_channel->setChannelGroup(sfx_group);
	////std::cout << "Page flip 2 audio\n\n";
}

// SFX audio #1 for slashing audio
void slashing1_Audio()
{
	result = audio_system->playSound(slashing_sound1, nullptr, false, &sfx_channel);
	sfx_channel->setChannelGroup(sfx_group);
	//std::cout << "Slashing 1 audio\n\n";
}

// SFX audio #2 slashing audio
void slashing2_Audio()
{
	result = audio_system->playSound(slashing_sound2, nullptr, false, &sfx_channel);
	sfx_channel->setChannelGroup(sfx_group);
	////std::cout << "Slashing 2 audio\n\n";
}

// SFX audio for swimming movement in the maze
void swimming_Audio()
{
	result = audio_system->playSound(swimming_sound, nullptr, false, &sfx_channel);
	sfx_channel->setChannelGroup(sfx_group);
	////std::cout << "swim audio\n\n";
}

// SFX audio for drinking potions in combat
void portion_Audio()
{
	result = audio_system->playSound(portion_sound, nullptr, false, &sfx_channel);
	sfx_channel->setChannelGroup(sfx_group);
	////std::cout << "drinking portion audio\n\n";
}

// SFX audio for opening chests in the maze
void chest_open_Audio()
{
	result = audio_system->playSound(chest_open_sound, nullptr, false, &sfx_channel);
	sfx_channel->setChannelGroup(sfx_group);
	////std::cout << "chest open audio\n\n";
}

// SFX audio for clicking any buttons
void click_Audio()
{
	result = audio_system->playSound(click_sound, nullptr, false, &sfx_channel);
	sfx_channel->setChannelGroup(sfx_group);
	////std::cout << "click audio\n\n";
}

// SFX audio for our game name logo intro page
void coin_drop_Audio()
{
	result = audio_system->playSound(coin_drop_sound, nullptr, false, &sfx_channel);
	sfx_channel->setChannelGroup(sfx_group);
	////std::cout << "coin audio\n\n";
}

// stops the audio for both BGM and SFX
void stop_Audio()
{
	bgm_channel->stop();
	sfx_channel->stop();
}

// increases bgm audio level
void increase_bgm_fader()
{
	bgm_volume += 0.1f;
	if (bgm_volume >= 0.5f) bgm_volume = 0.5f;
	bgm_group->setVolume(bgm_volume);
}

// decreases bgm audio level
void decrease_bgm_fader()
{
	bgm_volume -= 0.1f;
	if (bgm_volume <= 0) bgm_volume = 0.0f;
	bgm_group->setVolume(bgm_volume);
}

// increases sfx audio level
void increase_sfx_fader()
{
	sfx_volume += 0.1f;
	if (sfx_volume >= 0.5f) sfx_volume = 0.5f;
	sfx_group->setVolume(sfx_volume);
}

// decreases sfq audio level
void decrease_sfx_fader()
{
	sfx_volume -= 0.1f;
	if (sfx_volume <= 0) sfx_volume = 0.0f;
	sfx_group->setVolume(sfx_volume);
}

// mute all sounds
void mute_master_fader()
{
	master_fader->setMute(true);
}

// unmute all sounds
void unmute_master_fader()
{
	master_fader->setMute(false);
}