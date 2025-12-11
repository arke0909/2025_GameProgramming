#pragma once
#include "Object.h"
#include "Texture.h"
class Entity :
    public Object
{
protected:
	Entity() {};
	virtual ~Entity() {};
public:
	Texture* _eTex;

};
