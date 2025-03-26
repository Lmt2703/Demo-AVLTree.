#pragma once
#ifndef APPLICATION_H
#define APPLICATION_H

#include "raylib.h"
#include "Button.h"
#include "InputBox.h"
#include "Menu.h"
#include "AVLTree.h"
#include <string>
#include <fstream>
#include <sstream>

class Application {
public:
    int w, h;
    float leftWidth;
    bool showCreateMenu;
    bool showInitOptions;
    std::string selectedOption;
    std::string selectedInitOption;
    float animationProgress;
    Button createButton;
    Button startButton;
    Menu createMenu;
    Menu initMenu;
    InputBox inputBox;
    AVLTree tree;
    std::string statusMessage;
    Color statusColor;
    float statusTimer;

    Application(int width, int height);

    void ShowStatus(const std::string& message, Color color);
    void Update();
    void HandleInit();
    void HandleOperation();
    void Draw();
};

#endif // APPLICATION_H
