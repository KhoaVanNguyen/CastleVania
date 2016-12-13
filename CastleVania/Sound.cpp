#include "Sound.h"

Sound* Sound::_instance = NULL;
bool Sound::isBGM_On = true;
bool Sound::isSoundEffect_On = true;
Sound* Sound::GetInst()
{
	if (Sound::_instance == NULL)
	{
		_instance = new Sound();
	}
	return _instance;
}

Sound::Sound()
{
	_audio = new GAudio();
	_audio->Init_DirectSound(G_hWnd);

	bgmMenu = _audio->LoadSound("Sounds\\music\\Title_Theme_Prelude.wav");
	bgmStage1 = _audio->LoadSound("Sounds\\music\\Stage_01_Vampire_Killer.wav");
	bgmStage2 = _audio->LoadSound("Sounds\\music\\Stage_04_Stalker.wav");
	bgmBoss = _audio->LoadSound("Sounds\\music\\Boss_Battle_Poison_Mind.wav");
	bgmIntro = _audio->LoadSound("Sounds\\music\\Game_Start_Prologue.wav");
	bgmEndGame = _audio->LoadSound("Sounds\\music\\Stage_Clear.wav");

	stageClear = _audio->LoadSound("Sounds\\music\\Stage_Clear.wav");
	lifeLost = _audio->LoadSound("Sounds\\music\\Life_Lost.wav");
	collectItem = _audio->LoadSound("Sounds\\sound\\collectitem.wav");
	collectWeapon = _audio->LoadSound("Sounds\\sound\\collectweapon.wav");
	usingMorningStar = _audio->LoadSound("Sounds\\sound\\usingwhip.wav");
	splashWater = _audio->LoadSound("Sounds\\sound\\splashwater.wav");
	hitByWeapon = _audio->LoadSound("Sounds\\sound\\hit.wav");
	holyCross = _audio->LoadSound("Sounds\\sound\\holycross.wav");
	select = _audio->LoadSound("Sounds\\sound\\select.wav");
	openDoor = _audio->LoadSound("Sounds\\sound\\opendoor.wav");
	holyWater = _audio->LoadSound("Sounds\\sound\\holywater.wav");
	fallCastle = _audio->LoadSound("Sounds\\sound\\fallcastle.wav");
	getScoreTimer = _audio->LoadSound("Sounds\\sound\\getscoretimer.wav");
	getScoreWeaponCount = _audio->LoadSound("Sounds\\sound\\getscoreweapon.wav");
	stopTimer = _audio->LoadSound("Sounds\\sound\\stoptimer.wav");
	fallInLake = _audio->LoadSound("Sounds\\sound\\fallingdownwatersurface.wav");
}

Sound::~Sound()
{

}

void Sound::PlayBGSound(EBGSound id)
{

	switch (id)
	{
	case EBGSound::EMenuSound:

		_listBgm.push_back(bgmMenu);
		if (isBGM_On == true)
		{
			bgmMenu->Reset();
			_audio->LoopSound(bgmMenu);
		}
		break;
	case EBGSound::EStage1Sound:
		_listBgm.push_back(bgmStage1);
		if (isBGM_On == true)
		{
			bgmStage1->Reset();
			_audio->LoopSound(bgmStage1);
		}

		break;
	case EBGSound::EStage2Sound:
		_listBgm.push_back(bgmStage2);
		if (isBGM_On == true)
		{
			bgmStage2->Reset();
			_audio->LoopSound(bgmStage2);
		}

		break;
	case EBGSound::EBoss:
		_listBgm.push_back(bgmBoss);
		if (isBGM_On == true)
		{
			bgmBoss->Reset();
			_audio->LoopSound(bgmBoss);
		}

		break;
	case EBGSound::EIntroSound:
		_listBgm.push_back(bgmIntro);
		if (isBGM_On == true)
		{
			bgmIntro->Reset();
			_audio->LoopSound(bgmIntro);
		}
		break;
	case EBGSound::EEndGameSound:
		_listBgm.push_back(bgmEndGame);
		if (isBGM_On == true)
		{
			bgmIntro->Reset();
			_audio->LoopSound(bgmEndGame);
		}
		break;
	}
}

void Sound::PlaySoundEffect(ESoundEffect id)
{
	if (isSoundEffect_On == false)
		return;
	switch (id)
	{
	case ESoundEffect::ES_CollectItem:
		collectItem->Play();
		break;
	case ESoundEffect::ES_CollectWeapon:
		collectWeapon->Play();
		break;
	case ESoundEffect::ES_UsingMorningStar:
		usingMorningStar->Play();
		break;
	case ESoundEffect::ES_SplashWater:
		splashWater->Play();
		break;
	case ESoundEffect::ES_HitByWeapon:
		hitByWeapon->Play();
		break;
	case ESoundEffect::ES_HolyCross:
		holyCross->Play();
		break;
	case ESoundEffect::ES_OpenDoor:
		openDoor->Play();
		break;
	case ESoundEffect::ES_Select:
		select->Play();
		break;
	case ESoundEffect::ES_LifeLost:
		lifeLost->Play();
		break;
	case ESoundEffect::ES_StageClear:
		stageClear->Play();
		break;
	case ESoundEffect::ES_FallingCastle:
		fallCastle->Play();
		break;
	case ESoundEffect::ES_GetScoreTimer:
		getScoreTimer->Play();
		break;
	case ESoundEffect::ES_GetScoreWeaponCount:
		getScoreWeaponCount->Play();
		break;
	case ESoundEffect::ES_StopTimer:
		stopTimer->Play();
		break;
	case ESoundEffect::ES_FallInLake:
		fallInLake->Play();
		break;
	case ESoundEffect::ES_HolyWater:
		holyWater->Play();
		break;
	}
}

void Sound::StopAllBGSound()
{
	for (int i = 0; i<_listBgm.size(); i++)
	{
		_listBgm[i]->Stop();
	}
}

void Sound::RemoveAllBGM()
{
	StopAllBGSound();
	_listBgm.clear();
}
void Sound::ResumeBGM()
{
	for (int i = 0; i<_listBgm.size(); i++)
	{
		_audio->PlaySoundA(_listBgm[i]);
	}
}