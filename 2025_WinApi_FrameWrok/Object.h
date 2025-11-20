#pragma once
class Component;
class Collider;
class Object
{
public:
    Object();
    virtual ~Object();
public:
	virtual void Update() abstract;
	virtual void LateUpdate();
	virtual void Render(HDC hdc) abstract;
    void ComponentRender(HDC hdc);
    virtual void EnterCollision(Collider* _other) {};
    virtual void StayCollision(Collider* _other) {};
    virtual void ExitCollision(Collider* _other) {};
public:
	void SetPos(Vec2 pos) { _pos = pos; }
	void SetSize(Vec2 size) { _size = size; }
	const Vec2& GetPos() const { return _pos; }
	const Vec2& GetSize()const { return _size;	}
    bool GetIsDead() const { return m_isDie; }
    void SetDead() { m_isDie = true; }
public:
    template<typename T>
    T* AddComponent()
    {
        static_assert(std::is_base_of<Component, T>::value, "Component로부터 상속받아야 합니다.");
        T* compo = new T;
        compo->SetOwner(this); // 주인 찾기
        // 자기 자신의 기본 세팅 완료
        // setowner하고 이 owner로 getcom를 하던지 할 수 있음
        compo->Init();
        m_vecComponents.push_back(compo);
        return compo; // 리턴값을 나중에 setter 등 유연하게 사용
    }
    template<typename T>
    T* GetComponent()
    {
        T* component = nullptr;
        for (Component* com : m_vecComponents)
        {
            component = dynamic_cast<T*>(com);
            if (component)
                break;
        }
        return component;
    }
protected:
	void Translate(Vec2 _delta)
	{
		_pos.y += _delta.y;
		_pos.x += _delta.x;
	}
	void Scale(Vec2 scale)
	{
		_size.x *= scale.x;
		_size.y *= scale.y;
	}
protected:
	Vec2 _pos;
	Vec2 _size;
	vector<Component*> m_vecComponents;
    bool m_isDie;
};

