#pragma once
#include "Object.h"
#include "Entity.h"
#include "Animator.h"

class EntityState
	: public Object
{
public:
	EntityState(Entity* owner, std::wstring animetionName);
	virtual ~EntityState();
public:
	virtual void Enter();
	virtual void Update();
	virtual void Exit();
protected:
	Entity* _owner;
	Animator* _animator;
	std::wstring _animetionName;
};
