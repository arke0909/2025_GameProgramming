#pragma once
// 게임에 따라 변경
enum class Layer
{
	DEFAULT,
	BACKGROUND,
	UI,
	PLAYER,
	ENEMY,
	WALL,
	PROJECTILE,
	BULLET,
	END
};

enum class PenType
{
	RED, GREEN, END
};

enum class BrushType
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
	BulletSpeed,
	AttackSpeed,
	WallPunch,
	MoneyDrop,
	MaxHealth,
	Heal20HP,
	MultiShot,
	SplashDamage,
	Pierce,

	COUNT
};