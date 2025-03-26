#include "InputBox.h"

InputBox::InputBox(Rectangle bounds, Color boxColor, Color borderColor, Color textColor)
    : bounds(bounds), text(""), active(false), cursorVisible(true),
    cursorBlinkTime(0.0f), boxColor(boxColor), borderColor(borderColor), textColor(textColor) {
}

void InputBox::Update() {
    Vector2 mousePos = GetMousePosition();
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePos, bounds)) {
        active = true;
    }
    else if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        active = false;
    }

    if (active) {
        int key = GetCharPressed();
        while (key > 0) {
            if (key >= 32 && key <= 125 && text.size() < 255)
                text.push_back(static_cast<char>(key));
            key = GetCharPressed();
        }
        if (IsKeyPressed(KEY_BACKSPACE) && !text.empty()) text.pop_back();
    }

    if (active) {
        cursorBlinkTime += GetFrameTime();
        if (cursorBlinkTime >= 0.5f) {
            cursorVisible = !cursorVisible;
            cursorBlinkTime = 0.0f;
        }
    }
    else {
        cursorVisible = false;
    }
}

void InputBox::Draw() const {
    DrawRectangle(bounds.x, bounds.y, bounds.width, bounds.height, boxColor);
    DrawRectangleLines(bounds.x, bounds.y, bounds.width, bounds.height, borderColor);
    DrawText(text.c_str(), bounds.x + 10, bounds.y + 10, 20, textColor);
    if (active && cursorVisible) {
        float textWidth = MeasureText(text.c_str(), 20);
        DrawText("|", bounds.x + 10 + textWidth, bounds.y + 10, 20, textColor);
    }
}
