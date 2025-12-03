#pragma once

class Object;
struct SpawnObject
{
	Object* obj;
	Layer type;
};
class Scene
{
public:
	Scene();
	virtual ~Scene();
public:
	virtual void Init() abstract;
	virtual void AfterInit();
	virtual void Update();
	virtual void FixedUpdate(float _fixedDT);
	virtual void LateUpdate();
	virtual void Render(HDC hdc);
	virtual void Release();
public:
	const vector<Object*>& GetLayerObjects(Layer _type) const
	{
		return _vecObj[(UINT)_type];
	}
	void AddObject(Object* obj, Layer type)
	{
		_vecObj[(UINT)type].push_back(obj);
	}
	template<typename T>
	T* Spawn(Layer type, Vec2 pos, Vec2 size)
	{
		// 실행도 못하게 막아버림
		static_assert(std::is_base_of<Object, T>::value, "오브젝트를 상속안받음");
		T* obj = new T;
		obj->SetPos(pos);
		obj->SetSize(size);
		AddObject(obj, type);

		return obj;
	}
	void RequestDestroy(Object* obj);
	void RequestSpawn(Object* obj, Layer _type);
	void FlushEvent();
private:
	void RemoveObject(Object* _obj);
private:
	vector<Object*> m_killObject;
	vector<SpawnObject> m_spawnObject;
	vector<Object*> _vecObj[(UINT)Layer::END];
};

