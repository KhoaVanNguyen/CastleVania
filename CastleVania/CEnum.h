
#ifndef _CENUM_H_
#define _CENUM_H_

static enum ESceneState
{
	Scene_Menu,
	Scene_Intro,
	Scene_Game,
	Scene_End
} EnumSceneState;
enum EnumID
{
	None_ID,

	Simon_ID,
	SimonDeath_ID,

	Brick_ID,
	Candle_ID,
	LargeCandle_ID,
};

enum ObjectType {
	None,
	Item,
	Enemy,
	Other
};
#endif