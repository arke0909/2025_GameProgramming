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

// GDI ����
#define RECT_RENDER(hdc, posx, posy, sizex, sizey) Rectangle(hdc, (int)(posx-sizex/2),(int)(posy-sizey/2),(int)(posx+sizex/2),(int)(posy+sizey/2))
#define ELLIPSE_RENDER(hdc, posx, posy, sizex, sizey) Ellipse(hdc, (int)(posx-sizex/2),(int)(posy-sizey/2),(int)(posx+sizex/2),(int)(posy+sizey/2))
// Stat ����
// �ִ� ü��
const std::wstring STAT_HP = L"MaxHP";
// �����
const std::wstring STAT_ATTACK = L"Attack";
// ź��
const std::wstring STAT_BULLETSPEED = L"BulletSpeed";
// ���� �ӵ�
const std::wstring STAT_ATTACKSPEED = L"AttackSpeed";
// �����츦 �̴� ��
const std::wstring STAT_WALLFORCE = L"WallForce";
// �� ����
const std::wstring STAT_GOLDMULTI = L"GoldMultiplier";
// ��Ƽ��
const std::wstring STAT_MULTISHOT = L"MultiShot";
// ���÷���
const std::wstring STAT_SPLASH = L"Splash";
// źȯ ����
const std::wstring STAT_PENET = L"Penetration";
#define RECT_MAKE(posx, posy, sizex, sizey) {posx-sizex/2,posy-sizey/2,posx+sizex/2,posy+sizey/2}