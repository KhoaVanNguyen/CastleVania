
#ifndef _SOUNDGAME_H_
#define _SOUNDGAME_H_
#include "GAudio.h"
#include <vector>
#include "Global.h"
#include "dsutil.h"
using namespace std;

enum EBGSound
{
	EMenuSound,
	EStage1Sound,
	EStage2Sound,
	EBoss,
	EIntroSound,
	EEndGameSound
};

enum ESoundEffect
{
	ES_LifeLost,
	ES_CollectItem,
	ES_CollectWeapon,
	ES_UsingMorningStar,
	ES_SplashWater,
	ES_HitByWeapon,
	ES_HolyCross,
	ES_Select,
	ES_OpenDoor,
	ES_HolyWater,
	ES_StageClear,
	ES_FallingCastle,
	ES_GetScoreTimer,
	ES_GetScoreWeaponCount,
	ES_StopTimer,
	ES_FallInLake
};
class Sound
{
private:
	GAudio* _audio;
	//List of effect sound
	vector<GSound*> _listSoundEffect;
	//List of background sound (looped play sound)
	vector<GSound*> _listBgm;

	//BackGround Music
	GSound *bgmMenu;
	GSound *bgmStage1;
	GSound *bgmStage2;
	GSound *bgmBoss;
	GSound *bgmIntro;
	GSound *bgmEndGame;
	//Sound Effect
	GSound *lifeLost;
	GSound *stageClear;
	GSound* collectItem;
	GSound* collectWeapon;
	GSound* usingMorningStar;
	GSound* splashWater;
	GSound* hitByWeapon;
	GSound* holyCross;
	GSound* select;
	GSound* openDoor;
	GSound* holyWater;
	GSound* fallCastle;
	GSound* getScoreTimer;
	GSound* getScoreWeaponCount;
	GSound* stopTimer;
	GSound* fallInLake;
	Sound();
	static Sound* _instance;
public:
	static Sound* GetInst();
	static bool isBGM_On;
	static bool isSoundEffect_On;
	~Sound();

	void PlayBGSound(EBGSound);
	void PlaySoundEffect(ESoundEffect);
	void StopAllBGSound();
	void RemoveAllBGM();
	void ResumeBGM();
};

#endif