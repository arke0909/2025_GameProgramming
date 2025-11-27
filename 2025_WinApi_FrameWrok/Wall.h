#pragma once
#include "Object.h"
class BoxCollider;

struct WallSet
{
    bool isVertical;
    bool isStart;
};

class Wall :
    public Object
{
public:
    Wall();
    ~Wall();
public:
    // Object을(를) 통해 상속됨
    void Update() override;
    void Render(HDC hdc) override;
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
};

