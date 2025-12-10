#include "pch.h"
#include "SceneManager.h"
#include "Object.h"
#include "Collider.h"
#include "TilteScene.h"
#include "PlayerDevScene.h"
#include "WindowManager.h"
#include "GameScene.h"

void SceneManager::Init()
{
	_curScene = nullptr;
	// 다이나믹 캐스트 : 다운캐스팅할 때 보통 사용함
	// dynamic_cast<>
	// std::dynamic_pointer_cast<>

	RegisterScene(L"TitleScene", std::make_shared<TitleScene>());
	RegisterScene(L"PlayerDevScene", std::make_shared<PlayerDevScene>());
	RegisterScene(L"GameScene", std::make_shared<GameScene>());
	LoadScene(L"TitleScene");
}

void SceneManager::Update()
{
	if (_curScene == nullptr)
		return;
	_curScene->Update();
	_curScene->LateUpdate();
}

void SceneManager::FixedUpdate(float _fixedDT)
{
	if (_curScene == nullptr) return;
	_curScene->FixedUpdate(_fixedDT);
	PhysicsSyncColliders();
}

void SceneManager::Render(HDC hdc)
{
	if (_curScene == nullptr)
		return;
	_curScene->Render(hdc);

}

void SceneManager::PhysicsSyncColliders()
{
	for (UINT i = 0; i < (UINT)Layer::END; ++i)
	{
		const auto& objects = _curScene->GetLayerObjects((Layer)i);
		for (Object* obj : objects)
		{
			if (!obj)
				continue;

			if (auto* col = obj->GetComponent<Collider>())
				col->LateUpdate(); // sync  
		}
	}
}

void SceneManager::RegisterScene(const wstring& name, std::shared_ptr<Scene> scene)
{
	if (name.empty() || scene == nullptr)
		return;

	_mapScene.insert(_mapScene.end(), {name, scene});
}

void SceneManager::LoadScene(const wstring& name)
{
	GET_SINGLE(WindowManager)->Release();
	if (_curScene != nullptr)
	{
		_curScene->Release();
		_curScene = nullptr;
	}

	auto iter = _mapScene.find(name);
	if (iter != _mapScene.end())
	{
		_curScene = iter->second;
		_curScene->Init();
		_curScene->AfterInit();
	}
}
