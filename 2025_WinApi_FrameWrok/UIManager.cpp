#include "pch.h"
#include "UIManager.h"

void UIManager::Add(UIElement* elem) {
    _elements.push_back(elem);
}

void UIManager::Render(HDC hdc) {
    for (auto elem : _elements)
        if (elem->IsVisible()) elem->Render(hdc);
}
void UIManager::Update() {
    for (auto elem : _elements)
        elem->Update();
}

void UIManager::Clear() {
    for (auto elem : _elements)
        delete elem;
    _elements.clear();
}
