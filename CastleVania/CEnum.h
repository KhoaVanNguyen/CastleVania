
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
	Zombie_ID,
	Brick_ID,
	Candle_ID,
	LargeCandle_ID,
	MorningStar_ID,

	StairUpLeft_ID,
	StairUpRight_ID,
	StairDownLeft_ID,
	StairDownRight_ID,




	HP_ID,
	GameUI_ID,
};
enum EKindStair
{
	UpRight,
	UpLeft,
	DownRight,
	DownLeft,
	None_Kind
};
enum ObjectType {
	None,
	Item,
	Enemy_Type,
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
enum ECameraState
{
	Update,
	NoUpdate
};
#endif