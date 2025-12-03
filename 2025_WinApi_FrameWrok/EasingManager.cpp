#include "pch.h"
#include "EasingManager.h"

const float Pi = 3.14159265358979323846f;

float EasingManager::Linear(float t) {
	return t;
}

float EasingManager::InQuad(float t) {
	return t * t;
}

float EasingManager::OutQuad(float t) {
	return t * (2 - t);
}

float EasingManager::InOutQuad(float t) {
	if (t < 0.5f) return 2 * t * t;
	return -1 + (4 - 2 * t) * t;
}

float EasingManager::InCubic(float t) {
	return t * t * t;
}

float EasingManager::OutCubic(float t) {
	t -= 1;
	return t * t * t + 1;
}

float EasingManager::InOutCubic(float t) {
	if (t < 0.5f) return 4 * t * t * t;
	t -= 1;
	return 1 + 4 * t * t * t;
}

float EasingManager::InQuart(float t) {
	return t * t * t * t;
}

float EasingManager::OutQuart(float t) {
	t -= 1;
	return 1 - t * t * t * t;
}

float EasingManager::InOutQuart(float t) {
	if (t < 0.5f) return 8 * t * t * t * t;
	t -= 1;
	return 1 - 8 * t * t * t * t;
}

float EasingManager::InQuint(float t) {
	return t * t * t * t * t;
}

float EasingManager::OutQuint(float t) {
	t -= 1;
	return 1 + t * t * t * t * t;
}

float EasingManager::InOutQuint(float t) {
	if (t < 0.5f) return 16 * t * t * t * t * t;
	t -= 1;
	return 1 + 16 * t * t * t * t * t;
}

float EasingManager::InSine(float t) {
	return 1 - cos((t * Pi) / 2);
}

float EasingManager::OutSine(float t) {
	return sin((t * Pi) / 2);
}

float EasingManager::InOutSine(float t) {
	return -(cos(Pi * t) - 1) / 2;
}

float EasingManager::InExpo(float t) {
	return (t == 0) ? 0 : pow(2, 10 * (t - 1));
}

float EasingManager::OutExpo(float t) {
	return (t == 1) ? 1 : 1 - pow(2, -10 * t);
}

float EasingManager::InOutExpo(float t) {
	if (t == 0) return 0;
	if (t == 1) return 1;
	if (t < 0.5f) return pow(2, 20 * t - 10) / 2;
	return (2 - pow(2, -20 * t + 10)) / 2;
}

float EasingManager::InCirc(float t) {
	return 1 - sqrt(1 - t * t);
}

float EasingManager::OutCirc(float t) {
	t -= 1;
	return sqrt(1 - t * t);
}

float EasingManager::InOutCirc(float t) {
	if (t < 0.5f)
		return (1 - sqrt(1 - 4 * t * t)) / 2;
	t = 2 * t - 2;
	return (sqrt(1 - t * t) + 1) / 2;
}

float EasingManager::InBack(float t, float s) {
	return t * t * ((s + 1) * t - s);
}

float EasingManager::OutBack(float t, float s) {
	t -= 1;
	return t * t * ((s + 1) * t + s) + 1;
}

float EasingManager::InOutBack(float t, float s) {
	s *= 1.525f;
	if (t < 0.5f)
		return (t * t * ((s + 1) * (2 * t) - s)) * 2;
	t -= 1;
	return (t * t * ((s + 1) * (2 * t + 2) + s)) / 2 + 1;
}

float EasingManager::InElastic(float t) {
	if (t == 0) return 0;
	if (t == 1) return 1;
	return -pow(2, 10 * (t - 1)) *
		sin((t - 1.1f) * 5 * Pi);
}

float EasingManager::OutElastic(float t) {
	if (t == 0) return 0;
	if (t == 1) return 1;
	return pow(2, -10 * t) *
		sin((t - 0.1f) * 5 * Pi) + 1;
}

float EasingManager::InOutElastic(float t) {
	if (t == 0) return 0;
	if (t == 1) return 1;

	t *= 2;
	if (t < 1)
		return -0.5f * pow(2, 10 * (t - 1)) *
		sin((t - 1.1f) * 5 * Pi);

	t -= 1;
	return 0.5f * pow(2, -10 * t) *
		sin((t - 0.1f) * 5 * Pi) + 1;
}

float EasingManager::OutBounce(float t) {
	if (t < 4 / 11.0f)
		return (121 * t * t) / 16.0f;
	else if (t < 8 / 11.0f)
		return (363 / 40.0f * t * t) - (99 / 10.0f * t) + 17 / 5.0f;
	else if (t < 9 / 10.0f)
		return (4356 / 361.0f * t * t) - (35442 / 1805.0f * t) + 16061 / 1805.0f;
	else
		return (54 / 5.0f * t * t) - (513 / 25.0f * t) + 268 / 25.0f;
}

float EasingManager::InBounce(float t) {
	return 1 - OutBounce(1 - t);
}

float EasingManager::InOutBounce(float t) {
	if (t < 0.5f)
		return 0.5f * InBounce(t * 2);
	return 0.5f * OutBounce(t * 2 - 1) + 0.5f;
}
