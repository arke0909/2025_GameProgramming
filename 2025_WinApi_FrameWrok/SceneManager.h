#pragma once
#include "Scene.h"

class SceneManager
{
	DECLARE_SINGLE(SceneManager);

public:
	void Init();
	void Update();
	void FixedUpdate(float _fixedDT);
	void Render(HDC hdc);
	void PhysicsSyncColliders();
public:
	void RegisterScene(const wstring& name, std::shared_ptr<Scene> scene);
	void LoadScene(const wstring& name);
	void RequestDestroy(Object* obj)
	{
		if (_curScene)
		{
			_curScene->RequestDestroy(obj);
		}
	}
public:
	const std::shared_ptr<Scene>& GetCurScene() const
	{
		return _curScene;
	}
private:
	//vector<Scene*> sceneVec;
	std::shared_ptr<Scene> _curScene;
	std::unordered_map<wstring, std::shared_ptr<Scene>> _mapScene;
};

