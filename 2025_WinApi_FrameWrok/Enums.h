#pragma once
// 게임에 따라 변경
enum class Layer
{
	DEFAULT,
	BACKGROUND,
	PLAYER,
	ENEMY,
	PROJECTILE,
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