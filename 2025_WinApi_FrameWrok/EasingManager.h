#pragma once
class EasingManager
{
	DECLARE_SINGLE(EasingManager);

public :
	float Linear(float t);
	float InQuad(float t);
	float OutQuad(float t);
	float InOutQuad(float t);
	float InCubic(float t);
	float OutCubic(float t);
	float InOutCubic(float t);
	float InQuart(float t);
	float OutQuart(float t);
	float InOutQuart(float t);
	float InQuint(float t);
	float OutQuint(float t);
	float InOutQuint(float t);
	float InSine(float t);
	float OutSine(float t);
	float InOutSine(float t);
	float InExpo(float t);
	float OutExpo(float t);
	float InOutExpo(float t);
	float InCirc(float t);
	float OutCirc(float t);
	float InOutCirc(float t);
	float InBack(float t, float s = 1.70158f);
	float OutBack(float t, float s = 1.70158f);
	float InOutBack(float t, float s = 1.70158f);
	float InElastic(float t);
	float OutElastic(float t);
	float InOutElastic(float t);
	float OutBounce(float t);
	float InBounce(float t);
	float InOutBounce(float t);
};

