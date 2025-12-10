#pragma once
#include "Component.h"
class SkillComponent : 
	public Component
{
public:
	SkillComponent();
	~SkillComponent();
public:
	// Component을(를) 통해 상속됨
	void Init() override;
	void LateUpdate() override;
	void Render(HDC hDC) override;


};
