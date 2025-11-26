#pragma once
union COLLIDER_ID
{
    struct
    {
        UINT lo_ID;
        UINT hi_ID;
    };
    ULONGLONG ID;
};

class Collider;
class BoxCollider;
class CircleCollider;
class CollisionManager
{
    DECLARE_SINGLE(CollisionManager);
public:
    void Update();
    void CheckLayer(Layer _left, Layer _right);
    void CheckReset();
private:
    void CollisionLayerUpdate(Layer _left, Layer _right);
    bool IsCollision(Collider* _left, Collider* _right);
    bool IsAABBAABB(BoxCollider* _left, BoxCollider* _right);
    bool IsCircleAABB(BoxCollider* aabb, CircleCollider* circle);
    bool IsCircleCircle(CircleCollider* _left, CircleCollider* _right);
    ULONGLONG MakePairKey(UINT a, UINT b);
private:
    // 그룹 간의 충돌체크 배열
    UINT m_objectLayer[(UINT)Layer::END];
    std::unordered_map<ULONGLONG, bool> m_mapCollisionInfo;
};