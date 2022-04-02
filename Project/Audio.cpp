//JN: new code (the entire file)

#include "pch.hpp"

constexpr auto MAX_CHANNELS = 64;
FMOD::System* audio_system;
FMOD_RESULT result;
FMOD::Sound* maze_bgm = nullptr;
FMOD::Sound* wall_sound = nullptr;
FMOD::Sound* page_flip_sound1 = nullptr;
FMOD::Sound* page_flip_sound2 = nullptr;
FMOD::Sound* slashing_sound1 = nullptr;
FMOD::Sound* slashing_sound2 = nullptr;
FMOD::Sound* win_screen_bgm = nullptr;
FMOD::Sound* lose_screen_bgm = nullptr;
FMOD::Sound* swimming_sound = nullptr;
FMOD::Sound* portion_sound = nullptr;
FMOD::Sound* menu_bgm = nullptr;
FMOD::Sound* combat_bgm = nullptr;
extern FMOD::Channel* channel;
float volume = 0.5;

//Initialise audio
void Audio_Init()
{
	result = FMOD::System_Create(&audio_system);
	result = audio_system->init(MAX_CHANNELS, FMOD_INIT_NORMAL, nullptr);
	
	//maze background
	audio_system->createSound("Music/VIETNAM-COUNTRY_GEN-HDF-25318.wav", FMOD_LOOP_NORMAL, nullptr, &maze_bgm);
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
	//win screen background
	audio_system->createSound("Music/PRIDE OF OWNERSHIP - Corporate MSCCRP1_35.wav", FMOD_DEFAULT, nullptr, &win_screen_bgm);
	//lose screen background
	audio_system->createSound("Music/TubaComedy CTE09_40.2.wav", FMOD_DEFAULT, nullptr, &lose_screen_bgm);
	//swimming sound
	audio_system->createSound("Music/WATER-SPLASH_GEN-HDF-25630-short.wav", FMOD_DEFAULT, nullptr, &swimming_sound);
	//portion drinking
	audio_system->createSound("Music/ICE-GLASS_GEN-HDF-15591.wav", FMOD_DEFAULT, nullptr, &portion_sound);
	//menu background
	audio_system->createSound("Music/menu.wav", FMOD_LOOP_NORMAL, nullptr, &menu_bgm);
	//menu background
	audio_system->createSound("Music/gameplay.wav", FMOD_LOOP_NORMAL, nullptr, &combat_bgm);
}

//Update audio
void Audio_Update()
{
	result = audio_system->update();
}

//Unload audio
void Audio_Unload()
{
	maze_bgm->release();
	wall_sound->release();
	page_flip_sound1->release();
	page_flip_sound2->release();
	slashing_sound1->release();
	slashing_sound2->release();
	win_screen_bgm->release();
	lose_screen_bgm->release();
	swimming_sound->release();
	portion_sound->release();
	menu_bgm->release();
	combat_bgm->release();
}

//seperate audio function
void maze_background_Audio()
{
	// Play the sound.
	result = audio_system->playSound(maze_bgm, nullptr, false, &channel);
	std::cout << "maze background sound audio\n\n";

	//channel->getVolume(&volume);
	channel->setVolume(0.1f);
	increase_master_fader();
	decrease_master_fader();

	//adjusting_master_fader();
	//bool isPlaying = false;
	////check if sound is playing or not
	//channel->isPlaying(&isPlaying);
	//channel->stop();
	//channel->setMute(1);
}

void menu_background_Audio()
{
	// Play the sound.
	result = audio_system->playSound(menu_bgm, nullptr, false, &channel);
	std::cout << "menu background sound audio\n\n";

	//channel->getVolume(&volume);
	increase_master_fader();
	decrease_master_fader();

	//adjusting_master_fader();
	//bool isPlaying = false;
	////check if sound is playing or not
	//channel->isPlaying(&isPlaying);
	//channel->stop();
	//channel->setMute(1);
}

void combat_background_Audio()
{
	// Play the sound.
	result = audio_system->playSound(combat_bgm, nullptr, false, &channel);
	std::cout << "menu background sound audio\n\n";

	//channel->getVolume(&volume);
	increase_master_fader();
	decrease_master_fader();

	//adjusting_master_fader();
	//bool isPlaying = false;
	////check if sound is playing or not
	//channel->isPlaying(&isPlaying);
	//channel->stop();
	//channel->setMute(1);
}

void wall_hit_Audio()
{
	// Play the sound.
	result = audio_system->playSound(wall_sound, nullptr, false, &channel);
	std::cout << "Hit wall audio\n\n";

	//channel->getVolume(&volume);
	//increase_master_fader();
	//decrease_master_fader();

	//adjusting_master_fader();
	//bool isPlaying = false;
	////check if sound is playing or not
	//channel->isPlaying(&isPlaying);
	//channel->setVolume(1);
}

void page_flip1_Audio()
{
	// Play the sound.
	result = audio_system->playSound(page_flip_sound1, nullptr, false, &channel);
	std::cout << "Page flip 1 audio\n\n";

	//channel->getVolume(&volume);
	//increase_master_fader();
	//decrease_master_fader();

	//adjusting_master_fader();
	//bool isPlaying = false;
	////check if sound is playing or not
	//channel->isPlaying(&isPlaying);
	//channel->setVolume(1);
}

void page_flip2_Audio()
{
	// Play the sound.
	result = audio_system->playSound(page_flip_sound2, nullptr, false, &channel);
	std::cout << "Page flip 2 audio\n\n";

	//channel->getVolume(&volume);
	//increase_master_fader();
	//decrease_master_fader();

	//adjusting_master_fader();
	//bool isPlaying = false;
	////check if sound is playing or not
	//channel->isPlaying(&isPlaying);
	//channel->setVolume(1);
}

void slashing1_Audio()
{
	// Play the sound.
	result = audio_system->playSound(slashing_sound1, nullptr, false, &channel);
	std::cout << "Slashing 1 audio\n\n";

	//channel->getVolume(&volume);
	//increase_master_fader();
	//decrease_master_fader();

	//adjusting_master_fader();
	//bool isPlaying = false;
	////check if sound is playing or not
	//channel->isPlaying(&isPlaying);
	//channel->setVolume(1);
}

void slashing2_Audio()
{
	// Play the sound.
	result = audio_system->playSound(slashing_sound2, nullptr, false, &channel);
	std::cout << "Slashing 2 audio\n\n";

	//channel->getVolume(&volume);
	//increase_master_fader();
	//decrease_master_fader();

	//adjusting_master_fader();
	//bool isPlaying = false;
	////check if sound is playing or not
	//channel->isPlaying(&isPlaying);
	//channel->setVolume(1);
}

void win_screen_background_Audio()
{
	// Play the sound.
	result = audio_system->playSound(win_screen_bgm, nullptr, false, &channel);
	std::cout << "Win screen audio\n\n";

	//channel->getVolume(&volume);
	//increase_master_fader();
	//decrease_master_fader();

	//adjusting_master_fader();
	//bool isPlaying = false;
	////check if sound is playing or not
	//channel->isPlaying(&isPlaying);
	//channel->setVolume(1);
}

void lose_screen_background_Audio()
{
	// Play the sound.
	result = audio_system->playSound(lose_screen_bgm, nullptr, false, &channel);
	std::cout << "Lose screen audio\n\n";

	//channel->getVolume(&volume);
	//increase_master_fader();
	//decrease_master_fader();

	//adjusting_master_fader();
	//bool isPlaying = false;
	////check if sound is playing or not
	//channel->isPlaying(&isPlaying);
	//channel->setVolume(1);
}

void swimming_Audio()
{
	// Play the sound.
	result = audio_system->playSound(swimming_sound, nullptr, false, &channel);
	std::cout << "swim audio\n\n";

	//channel->getVolume(&volume);
	//increase_master_fader();
	//decrease_master_fader();

	//adjusting_master_fader();
	//bool isPlaying = false;
	////check if sound is playing or not
	//channel->isPlaying(&isPlaying);
	//channel->setVolume(1);
}

void portion_Audio()
{
	// Play the sound.
	result = audio_system->playSound(portion_sound, nullptr, false, &channel);
	std::cout << "drinking portion audio\n\n";

	//channel->getVolume(&volume);
	//increase_master_fader();
	//decrease_master_fader();

	//adjusting_master_fader();
	//bool isPlaying = false;
	////check if sound is playing or not
	//channel->isPlaying(&isPlaying);
	//channel->setVolume(1);
}

void increase_master_fader()
{
	if (AEInputCheckTriggered(AEVK_UP))
	{
		volume += 0.1f;

		if (volume >= 1) volume = 1.f;
	}

	channel->setVolume(volume);
}

void decrease_master_fader()
{
	if (AEInputCheckTriggered(AEVK_DOWN))
	{
		volume -= 0.1f;

		if (volume <= 0) volume = 0.f;
	}

	channel->setVolume(volume);
}

void get_current_volume()
{
	channel->getVolume(&volume);
}

//void main_menu_background_Audio()
//{
//	// Play the sound.
//	result = audio_system->playSound(sound1, nullptr, false, &channel);
//	std::cout << "main menu background sound";
//
//	channel->setVolume(0.5);
//	//bool isPlaying = false;
//	////check if sound is playing or not
//	//channel->isPlaying(&isPlaying);
//	//channel->stop();
//	//channel->setMute(1);
//}