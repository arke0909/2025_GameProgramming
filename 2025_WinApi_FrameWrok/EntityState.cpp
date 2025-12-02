#include "pch.h"
#include "EntityState.h"

EntityState::EntityState(Entity* owner, std::wstring animetionName)
{
	_animetionName = animetionName;
	_animator = _owner->GetComponent<Animator>();
}

EntityState::~EntityState()
{

}

void EntityState::Enter()
{
	Vec2 animSize;

	switch (_owner->_eTex->GetHeight())
	{
		break;
	case 32:
		animSize = { 32.f,32.f };
		break;
	case 64:
		animSize = { 64.f,64.f };
		break;
	case 96:
		animSize = { 96.f,96.f };
		break;
	}

	auto* animator = AddComponent<Animator>();
	animator->CreateAnimation
	(
		_animetionName,
		_owner->_eTex,
		{ 0.f,0.f },
		animSize,
		{ 0.f,0.f },
		1, 1
	);
}

void EntityState::Update()
{

}

void EntityState::Exit()
{

}
