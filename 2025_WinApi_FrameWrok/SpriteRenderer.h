// SpriteRenderer.h

#include "Component.h"
class Sprite;

class SpriteRenderer : public Component
{
public:
	SpriteRenderer(); // 생성자
	~SpriteRenderer(); // 소멸자

public:
	void LateUpdate() override; // 매 프레임의 마지막에 호출되는 업데이트 함수
	void Render(HDC hDC) override; // 실제 화면에 렌더링하는 함수

public:
	// 스프라이트 설정 및 가져오기
	void setSprite(Sprite* sprite) { _sprite = sprite; }
	Sprite* getSprite() { return _sprite; }

	// 스케일 설정 및 가져오기
	void setScale(const Vector2& scale) { _scale = scale; }
	const Vector2& getScale() { return _scale; }

	// 오프셋(위치 보정) 설정
	void setOffset(const Vector2& offset) { _offset = offset; }

	// 흰색 효과(하이라이트) 설정
	void setWhiteness(const bool& whiteness) { _whiteness = whiteness; }

private:
	Sprite* _sprite;         // 렌더링할 스프라이트
	Vector2 _scale;          // 크기 배율
	Vector2 _offset;         // 위치 보정 값
	bool _whiteness = false; // 흰색 효과 활성화 여부
};
