
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

	Player_ID,
	PlayerDeath_ID,

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
enum Action
{
	Idle,
	Run_Right,
	Run_Left,
	Jump,
	Fight,
	Sit,
	Fall,
	IntoCastle
};
#endif