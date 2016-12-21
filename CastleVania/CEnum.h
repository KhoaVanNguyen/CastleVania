
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
	Ghosts_ID,
	//groud
	MovingPlatform_ID,
	StairUpLeft_ID,
	StairUpRight_ID,
	StairDownLeft_ID,
	StairDownRight_ID,

	DoorLeft_ID,
	DoorRight_ID,
	TeleUp_ID,
	TeleDown_ID,
	OpenDoor_ID,
	TrapDoor_ID,
	CastleGate_ID,
	//boss
	PhantomBat_ID,
	Medusa_ID,
	LittleSnake_ID,

	//other
	Water_ID,
	Fire_ID,
	FireBossDie_ID,
	HP_ID,
	GameUI_ID,


	//Item
	Invisibility_Potion,
	PorkChop_ID,
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
	RedMoneyBag_ID,
	PurpleMoneyBag_ID,
	WhiteMoneyBag_ID,
	MoneyBagItem_ID,
	WatchItem_ID,
	MagicalBall_ID,

	RewardedItem_ID,
	//weapon
	Dagger_ID,
	Throw_Axe_ID,
	HolyWater_ID,
	Boomerang_ID,
	StopWatch_ID,


	CrossItem_ID,

	HolyWaterItem_ID
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

enum ECollisionDirect
{
	Colls_None,
	Colls_Left,
	Colls_Right,
	Colls_Bot,
	Colls_Top
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
	TeleUp,
	TeleDown,
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