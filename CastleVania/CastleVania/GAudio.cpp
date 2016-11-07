
#include "GAudio.h"


int GAudio::Init_DirectSound(HWND hwnd)
{
    HRESULT result;

    //create DirectSound manager object
    dsound = new GSoundManager();

    //initialize DirectSound
    result = dsound->Initialize(hwnd, DSSCL_PRIORITY);
    if (result != DS_OK)
    {
		GLTrace("[FAILED] Can not init directx sound");
		return 0;
	}

    //set the primary buffer format
    result = dsound->SetPrimaryBufferFormat(2, 22050, 16);
    if (result != DS_OK)
    {
		GLTrace("[FAILED] Can not set the primary buffer");
		 return 0;
	}
    //return success
	GLTrace("Directx Sound has been success init");
    return 1;
}

GSound* GAudio::LoadSound(char *filename)
{
    HRESULT result;

    //create local reference to wave data
    GSound *wave;

    //attempt to load the wave file
    result = dsound->Create(&wave, filename);
    if (result != DS_OK)
    {
		GLTrace("[Failed] Can not load sound file");
		 return NULL;
	}
	GLTrace("Sound file has been loaded");
    //return the wave
    return wave;
}

void GAudio::PlaySound(GSound *sound)
{
    sound->Play();
	GLTrace("Sound file has been played");
}

void GAudio::LoopSound(GSound *sound)
{
    sound->Play(0, DSBPLAY_LOOPING);
}

void GAudio::StopSound(GSound *sound)
{
    sound->Stop();
}
