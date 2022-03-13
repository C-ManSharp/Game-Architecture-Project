#include "../header/SoundFX.h"
#include "..\header\SoundFX.h"

SoundFX SoundFX::instance;

SoundFX::SoundFX() : explosionSounds{}, thrustSounds{}, plasmaShootingSounds{}, 
currentExplosionIndex{0}, currentThrustIndex{ 0 }, currentPlasmaShootingIndex{ 0 },
currentMachineGunShootingIndex{ 0 }, MAX_NUMBER_OF_SOUNDS{ 5 }, numberOfTimesSoundsHaveBeenLoaded{ 0 },
machineGunShootingSounds{  }
{
}

void SoundFX::loadSounds()
{
	//Check to stop the sounds from loading mid game if someone accidently calls load sounds.
	if (numberOfTimesSoundsHaveBeenLoaded == 0)
	{
		explosionSounds[0] = MySoundEngine::GetInstance()->LoadWav(L"assets/explosion.wav");
		explosionSounds[1] = MySoundEngine::GetInstance()->LoadWav(L"assets/explosion1.wav");
		explosionSounds[2] = MySoundEngine::GetInstance()->LoadWav(L"assets/explosion2.wav");
		explosionSounds[3] = MySoundEngine::GetInstance()->LoadWav(L"assets/explosion3.wav");
		explosionSounds[4] = MySoundEngine::GetInstance()->LoadWav(L"assets/explosion4.wav");

		for (int i = 0; i < 5; i++)
		{
			thrustSounds[i] = MySoundEngine::GetInstance()->LoadWav(L"assets/thrustloop2.wav");
			plasmaShootingSounds[i] = MySoundEngine::GetInstance()->LoadWav(L"assets/shoot.wav");
			machineGunShootingSounds[i] = MySoundEngine::GetInstance()->LoadWav(L"assets/servo.wav");
		}
		numberOfTimesSoundsHaveBeenLoaded++;
	}
}

void SoundFX::playExplosionSound()
{
	const unsigned int RANDOM_NUMBER = rand() % 4;
	MySoundEngine::GetInstance()->Play(explosionSounds[RANDOM_NUMBER]);
}

void SoundFX::playEngineSound()
{
	MySoundEngine::GetInstance()->Play(thrustSounds[0], true);
}

void SoundFX::stopEngineSound()
{
	MySoundEngine::GetInstance()->Stop(thrustSounds[0]);
}

void SoundFX::playPlasmaShootingSound()
{
	MySoundEngine::GetInstance()->Play(plasmaShootingSounds[currentPlasmaShootingIndex]);
	currentPlasmaShootingIndex++;
	if (currentPlasmaShootingIndex >= MAX_NUMBER_OF_SOUNDS)
		currentPlasmaShootingIndex = 0;
}

void SoundFX::playMachineGunShootingSound()
{
	MySoundEngine::GetInstance()->Play(machineGunShootingSounds[currentMachineGunShootingIndex]);
	currentMachineGunShootingIndex++;
	if (currentMachineGunShootingIndex >= MAX_NUMBER_OF_SOUNDS)
		currentMachineGunShootingIndex = 0;
}

SoundFX::~SoundFX()
{
}