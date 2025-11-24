#pragma once
class TimeManager
{
	DECLARE_SINGLE(TimeManager);

public:
	void Init();
	void Update();
public:
	float GetDeletaTime() const { return _deltaTime; }
	float GetTime() const { return  _time; }
private:
	LARGE_INTEGER _llPrevCnt = {};
	LARGE_INTEGER _llCurCnt = {};
	LARGE_INTEGER _llFrequency = {};

	float _deltaTime = 0.f;
	float _time = 0.f;

	UINT _fps = 0;
	UINT _frameCnt = 0;
	float _frameTime = 0.f;
};

