#include "Button.h"

Button::Button(Rectangle bounds, const std::string& label, Color normalColor, Color hoverColor, Color textColor)
    : bounds(bounds), label(label), normalColor(normalColor), hoverColor(hoverColor), textColor(textColor) {
}

bool Button::IsMouseOver(Vector2 mousePos) const {
    return CheckCollisionPointRec(mousePos, bounds);
}

bool Button::IsClicked(Vector2 mousePos) const {
    return IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && IsMouseOver(mousePos);
}

void Button::Draw() const {
    Color drawColor = IsMouseOver(GetMousePosition()) ? hoverColor : normalColor;
    DrawRectangleRounded(bounds, 0.3f, 5, drawColor);
    DrawText(label.c_str(), bounds.x + 20, bounds.y + 15, 20, textColor);
}
