#pragma once
#define DECLARE_SINGLE(className)\
private:						 \
className() {}					 \
public:							 \
	static className* GetInst()  \
	{							 \
		static className inst;	 \
		return &inst;			 \
	}

#define GET_SINGLE(className) className::GetInst()
#define fDT GET_SINGLE(TimeManager)->GetDeltaTime()
#define SAFE_DELETE(ptr) if(ptr !=nullptr){    delete ptr;     ptr = nullptr; }                    
#define GET_LT(size, pos) {pos.x - size.x / 2, pos.y - size.y / 2}

#define GET_KEYUP(key) GET_SINGLE(InputManager)->IsUp(key)
#define GET_KEYDOWN(key) GET_SINGLE(InputManager)->IsDown(key)
#define GET_KEY(key) GET_SINGLE(InputManager)->IsPress(key)
#define GET_KEYWITH(main,mod) GET_SINGLE(InputManager)->IsPressWith(main,mod)
#define GET_MOUSEPOS GET_SINGLE(InputManager)->GetMousePos();

// GDI 헬퍼
#define RECT_RENDER(hdc, posx, posy, sizex, sizey) Rectangle(hdc, (int)(posx-sizex/2),(int)(posy-sizey/2),(int)(posx+sizex/2),(int)(posy+sizey/2))
#define ELLIPSE_RENDER(hdc, posx, posy, sizex, sizey) Ellipse(hdc, (int)(posx-sizex/2),(int)(posy-sizey/2),(int)(posx+sizex/2),(int)(posy+sizey/2))
#define RECT_MAKE(posx, posy, sizex, sizey) {posx-sizex/2,posy-sizey/2,posx+sizex/2,posy+sizey/2}

// Stat 관련
// 최대 체력
const std::wstring STAT_HP = L"MaxHP";
// 이속
const std::wstring STAT_SPEED = L"MoveSpeed";
// 무기 이속
const std::wstring STAT_WEAPONSPEED = L"WeaponSpeed";
// 윈도우를 미는 힘
const std::wstring STAT_WALLFORCE = L"WallForce";
// 돈 배율
const std::wstring STAT_GOLDMULTI = L"GoldMultiplier";
// 멀티샷
const std::wstring STAT_WEAPON_SIZE = L"WeaponSize";
// 스플래쉬
const std::wstring STAT_SPLASH = L"Splash";

const std::wstring HEAL = L"HealHP";
