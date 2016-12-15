
#ifndef _CENUM_H_
#define _CENUM_H_

static enum ESceneState
{
	Scene_Menu,
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
	MorningStar_ID,

	//enemy
	MedusaHeads_ID,
	Bats_ID,
	Panthers_ID,
	Fishmen_ID,
	AxeKnights_ID,
	BoneTowers_ID,
	Ghouls_ID,
	//groud
	MovingPlatform_ID,
	StairUpLeft_ID,
	StairUpRight_ID,
	StairDownLeft_ID,
	StairDownRight_ID,
	
	DoorLeft_ID,
	DoorRight_ID,
	DoorUp_ID,
	DoorDown_ID,
	OpenDoor_ID,
	StupidDoor_ID,
	CastleGate_ID,
	//boss
	PhantomBat_ID,
	Medusa_ID,

	//other
	Water_ID,
	FireBall_ID,
	Reward_ID,
	HP_ID,
	GameUI_ID,


	//Item
	Cross,
	Invisibility_Potion,
	Pork_Chop,
	Double_Shot,
	Triple_Shot,
	Bonuses,
	Crystal_Ball,
	Whip_Upgrade,
	Small_Heart,
	Large_Heart,
	Red_Money_Bag,
	Purple_Money_Bag,
	White_Money_Bag,
	MoneyBagRedItem_ID,
	MoneyBagBlueItem_ID,
	MoneyBagWhiteItem_ID,
	MoneyBagItem_ID,
	WatchItem_ID,
	//weapon
	Dagger_ID,
	Throw_Axe_ID,
	Holy_Watter_ID,
	Boomerang_ID,
	Stop_Watch_ID
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

//enum EMoveDirection
//{
//	MoveUp,
//	MoveDown,
//	MoveRight,
//	MoveLeft,
//	None
//};

enum EDirectDoor
{
	DoorUp,
	DoorDown,
	DoorRight,
	DoorLeft,
	NoneDoor
};
enum EStateCamera
{
	Update_Camera,
	NoUpdate_Camera
};
#endif