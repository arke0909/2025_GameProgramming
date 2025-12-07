#pragma once
#include<vector>

enum class PatternType {
	CIRCLESHOT, LINEARSHOT, BOUNCESHOT, TRACKINGSHOT
};

struct PatternData {
	PatternType patternType; // 패턴 타입
	float collTime; // 쿨타임
	float weight; // 패턴 선택확률
	float speed; // 공격 속도
};

class PhaseData
{
public:
	float attackInterval; // 공격 간격
	std::vector<PatternData> patterns; // 갖고 있는 패턴들
};
