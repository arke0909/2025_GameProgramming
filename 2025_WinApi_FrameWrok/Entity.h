#pragma once
#include "Object.h"
#include "Texture.h"
class Entity :
    public Object
{
protected:
    Entity();
	virtual ~Entity();
public:
    virtual void Update() override abstract;
	virtual void Render(HDC hdc) override abstract;
public:
	Texture* _eTex;

};

