#include "pch.h"
#include "Scene.h"
#include "Object.h"
#include "CollisionManager.h"
#include "Rigidbody.h"
#include "UIManager.h"
#include "IAfterInit.h"

Scene::Scene()
{
}

Scene::~Scene()
{
	Release();
}

void Scene::AfterInit()
{
	for (UINT i = 0; i < (UINT)Layer::END; ++i)
	{
		auto& vec = _vecObj[i];
		for (auto* obj : vec)
		{
			auto afterInit = dynamic_cast<IAfterInit*>(obj);
			if(afterInit)
				afterInit->AfterInit();
		}
	}
}

void Scene::Update()
{
	FlushEvent();
	for (UINT i = 0; i < (UINT)Layer::END; ++i)
	{
		auto& vec = _vecObj[i];
		for (auto* obj : vec)
		{
			if(!obj->GetIsDead())
				obj->Update();
		}
	}

	GET_SINGLE(UIManager)->Update();
}

void Scene::FixedUpdate(float _fixedDT)
{
	for (UINT i = 0; i < (UINT)Layer::END; ++i)
	{
		auto& vec = _vecObj[i];
		for (auto* obj : vec)
		{
			if (auto rb = obj->GetComponent<Rigidbody>())
			{
				if (rb != nullptr)
					rb->FixedUpdate(_fixedDT);
			}
		}
	}
}

void Scene::LateUpdate()
{
	for (UINT i = 0; i < (UINT)Layer::END; ++i)
	{
		auto& vec = _vecObj[i];
		for (auto* obj : vec)
			if(!obj->GetIsDead())
			obj->LateUpdate();
	}
}
void Scene::Render(HDC hdc)
{
	for (UINT i = 0; i < (UINT)Layer::END; ++i)
	{
		auto& vec = _vecObj[i];
		for (auto* obj : vec)
			if(!obj->GetIsDead())
			obj->Render(hdc);
	}

	GET_SINGLE(UIManager)->Render(hdc);
}

void Scene::Release()
{
	for (UINT i = 0; i < (UINT)Layer::END; ++i)
	{
		auto& vec = _vecObj[i];
		for (auto* obj : vec)
			SAFE_DELETE(obj);
		vec.clear();
	}
	GET_SINGLE(CollisionManager)->CheckReset();
	GET_SINGLE(UIManager)->Clear();
}

void Scene::RequestDestroy(Object* obj)
{
	if (obj == nullptr)
		return;

	// 죽지 않으면 넣어라
	if (!obj->GetIsDead())
	{
		obj->SetDead();
		// 실제 delete는 FlushObject에서
		m_killObject.push_back(obj);
	}
}

void Scene::RequestSpawn(Object* obj, Layer _type)
{

}

void Scene::FlushEvent()
{
	for (Object* d : m_killObject)
	{
		RemoveObject(d);
		SAFE_DELETE(d);
	}
	m_killObject.clear();
}

void Scene::RemoveObject(Object* _obj)
{
	for (UINT i = 0; i < (UINT)Layer::END; ++i)
	{
		auto& v = _vecObj[i];
		v.erase(std::remove(v.begin(), v.end(), _obj), v.end());
	}
}
