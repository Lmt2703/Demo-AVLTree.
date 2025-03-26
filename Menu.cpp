#include "Menu.h"

Menu::Menu() : visible(false) {}

void Menu::AddButton(const Button& btn) {
    buttons.push_back(btn);
}

int Menu::ProcessClick() {
    Vector2 mousePos = GetMousePosition();
    for (size_t i = 0; i < buttons.size(); i++) {
        if (buttons[i].IsClicked(mousePos))
            return static_cast<int>(i);
    }
    return -1;
}

void Menu::Draw() {
    if (!visible) return;
    for (auto& btn : buttons)
        btn.Draw();
}
