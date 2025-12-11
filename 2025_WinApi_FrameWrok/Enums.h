#pragma once
// 게임에 따라 변경
enum class Layer
{
	DEFAULT,
	BACKGROUND,
	PLAYER,
	ENEMY,
	WALL,
	PROJECTILE,
	BULLET,
	EFFECT,
	UI,
	END
};

enum class MyPenType
{
	RED, GREEN,WHITE, END
};

enum class MyBrushType
{
	HOLLOW, RED, GREEN, END
};

enum class FontType
{
	UI, TITLE, END
};

enum class PlayMode
{
	Once, Loop, Counted
};

enum class ButtonEvent
{
	Click, Hover, END
};

enum class ItemType
{
	PlayerSpeed,
	WeaponSpeed,
	WallPunch,
	MoneyDrop,
	MaxHealth,
	Heal20HP,
	WeaponSize,
	SplashDamage,
	Pierce,

	COUNT
};