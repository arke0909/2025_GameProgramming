#pragma once
#include "Object.h"
class BoxCollider;
class Window;

struct WallSet
{
    bool isVertical;
    bool isStart;
};

class Wall :
    public Object
{
public:
    Wall(Window* inGameWindow);
    ~Wall();
public:
    // Object을(를) 통해 상속됨
    void Update() override;
    void Render(HDC hdc) override;

    void EnterCollision(Collider* _other) override;
    void StayCollision(Collider* _other) override;
    void ExitCollision(Collider* _other) override;

    void SetWall(WallSet wallSet)
    {
        _wallSet = wallSet;
    }
    WallSet GetWall()
    {
        return _wallSet;
    }
private:
    WallSet _wallSet;
    BoxCollider* boxCol;
    Window* _inGameWindow;
};

