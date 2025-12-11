#pragma once
#include "UIElement.h"

class UISlider : public UIElement
{
public:
    UISlider(const Vec2& pos, const Vec2& size);
    ~UISlider() override = default;
    void SetValue(float value);
    float GetValue() const { return _value; }

    void SetOnValueChanged(std::function<void(float)> callback);

    void Render(HDC hdc) override;
    void Update() override;

private:
    float _value = 0.0f;
    bool _dragging = false;

    RECT _barRect;
    RECT _fillRect;
    RECT _handleRect;

    std::function<void(float)> _onValueChanged;
};
