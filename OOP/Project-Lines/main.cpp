#include "GameController.h"
#include <fmod.h>
#include <fmod.hpp>
#include <windows.h>


//=============================================================================
// main function
int main(int argc, char** argv){

	// create system
	FMOD::System* system;
	FMOD_RESULT result = FMOD::System_Create(&system);

	// load sound
	FMOD::Sound* sound;
	system->setOutput(FMOD_OUTPUTTYPE_DSOUND );
	system->init(32, FMOD_INIT_NORMAL, 0);

	
	
	result = system->createSound("Sounds/appear.mp3", FMOD_LOOP_NORMAL,NULL, 
									&sound); 
	// play sound 
	FMOD::Channel* channel = 0; 
	result = system->playSound(FMOD_CHANNEL_FREE, sound, false, &channel); 
	//system->update(); 
	//if(result == FMOD_OK) 
	//::MessageBox(0, "werwer", "wer", 0); 
	//// release resources 
	//result = sound->release(); 
	//result = system->release();



	GameController::getInst()->LoadGame();

	return 0;
}
//=============================================================================
//=============================================================================
//=============================================================================