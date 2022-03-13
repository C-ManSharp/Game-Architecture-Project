/*
Author: Connor Tall
Used to play sounds.
*/
#ifndef SOUNDFX
#define SOUNDFX
#include "mysoundengine.h"

class SoundFX
{
private:
	SoundIndex explosionSounds[5];
	SoundIndex thrustSounds[5];
	SoundIndex plasmaShootingSounds[5];
	SoundIndex machineGunShootingSounds[5];
	unsigned int currentExplosionIndex;
	unsigned int currentThrustIndex;
	unsigned int currentPlasmaShootingIndex;
	unsigned int currentMachineGunShootingIndex;
	unsigned int numberOfTimesSoundsHaveBeenLoaded;
	const unsigned int MAX_NUMBER_OF_SOUNDS;
	SoundFX();
public:
	static SoundFX instance;
	void loadSounds();
	void playExplosionSound();
	void playEngineSound();
	void stopEngineSound();
	void playPlasmaShootingSound();
	void playMachineGunShootingSound();
	~SoundFX();
};

#endif