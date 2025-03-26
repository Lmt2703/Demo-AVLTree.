#pragma once
#ifndef MENU_H
#define MENU_H

#include "Button.h"
#include <vector>

class Menu {
public:
    std::vector<Button> buttons;
    bool visible;

    Menu();

    void AddButton(const Button& btn);
    int ProcessClick();
    void Draw();
};

#endif // MENU_H
