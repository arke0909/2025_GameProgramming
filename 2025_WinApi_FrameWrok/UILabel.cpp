#include "pch.h"
#include "UILabel.h"

UILabel::UILabel(const wstring& text, RECT rect) : UIElement(rect), _text(text) {
}