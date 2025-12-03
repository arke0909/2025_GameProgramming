#include "pch.h"
#include "EntityState.h"

EntityState::EntityState(Entity* owner, std::wstring animetionName)
    : _owner(owner), _animetionName(animetionName)
{
    if (_owner != nullptr)
        _animator = _owner->GetComponent<Animator>();
}


EntityState::~EntityState()
{

}

void EntityState::Enter()
{
	_animator->Play(_animetionName);
}

void EntityState::Update()
{

}

void EntityState::Exit()
{

}
