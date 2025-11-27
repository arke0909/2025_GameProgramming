#pragma once
struct Vec2
{
public:
    //Vec2() {}
    Vec2() = default;
    Vec2(float _x, float _y) : x(_x), y(_y) {}
    Vec2(POINT _pt) : x((float)_pt.x), y((float)_pt.y) {}
    Vec2(int _x, int _y) : x((float)_x), y((float)_y) {}
    Vec2(const Vec2& _other) : x(_other.x), y(_other.y) {}
public:
    Vec2 operator + (const Vec2& _vOther)
    {
        return Vec2(x + _vOther.x, y + _vOther.y);
    }
    Vec2 operator - (const Vec2& _vOther)
    {
        return Vec2(x - _vOther.x, y - _vOther.y);
    }
    Vec2 operator / (float _val)
    {
        return Vec2(x / _val, y / _val);
    }
    Vec2 operator * (const Vec2& _vOther)
    {
        return Vec2(x * _vOther.x, y * _vOther.y);
    }
    Vec2 operator * (float _val)
    {
        return Vec2(x * _val, y * _val);
    } 
    void operator+=(const Vec2& _other)
    {
        x += _other.x;
        y += _other.y;
    }
    void operator-=(const Vec2& _other)
    {
        x -= _other.x;
        y -= _other.y;
    }
    Vec2 operator *= (const Vec2& _vOther)
    {
        x *= _vOther.x;
        y *= _vOther.y;
        return *this;
    }
    Vec2 operator *= (float _val)
    {
        x *= _val;
        y *= _val;
        return *this;
    }
    Vec2 operator - ()
    {
        return Vec2(-x, -y);
    }
    float LengthSquared()
    {
        return x * x + y * y;
    }
    float Length()
    {
        return ::sqrt(LengthSquared());
    }
    void Normalize()
    {
        float len = Length();
        if (len < FLT_EPSILON)
            return;
        x /= len;
        y /= len;
    }
    float Dot(Vec2 other)
    {
        return x * other.x + y * other.y;
    }
    float Cross(Vec2 other)
    {
        return x * other.y - y * other.x;
    }
public:
    float x = 0.f;
    float y = 0.f;
};

using Vector2 = Vec2;