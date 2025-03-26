#include "Application.h"
#include <fstream>
#include <sstream>
#include <ctime>

Application::Application(int width, int height)
    : w(width), h(height), leftWidth(width * 0.3f),
    showCreateMenu(false), showInitOptions(false),
    selectedOption("Create"), selectedInitOption(""),
    animationProgress(0.0f),
    createButton({ leftWidth * 0.05f, h * 0.05f, leftWidth * 0.4f, 50 }, "Create", ORANGE, GOLD, WHITE),
    startButton({ leftWidth * 0.55f, h * 0.05f, leftWidth * 0.4f, 50 }, "Start", GREEN, LIME, WHITE),
    inputBox({ leftWidth * 0.05f, h * 0.45f, leftWidth * 0.9f, 40 }, Color{ 255, 255, 204, 255 }, DARKBLUE, BLACK),
    tree(width, height),
    statusMessage(""),
    statusColor(DARKGRAY),
    statusTimer(0.0f) {

    float btnY = createButton.bounds.y;
    float btnWidth = createButton.bounds.width;
    Rectangle btnRect;
    const char* options[] = { "Init", "Add", "Del", "Search" };
    for (int i = 0; i < 4; i++) {
        btnRect = { createButton.bounds.x, btnY + (i + 1) * 55, btnWidth, 50 };
        createMenu.AddButton(Button(btnRect, options[i], SKYBLUE, GOLD, WHITE));
    }

    float initX = createButton.bounds.x + createButton.bounds.width + 10;
    float initY = createButton.bounds.y;
    Rectangle initRect;
    const char* initOptions[] = { "Random", "File", "Input" };
    for (int i = 0; i < 3; i++) {
        initRect = { initX, initY + i * 55, btnWidth, 50 };
        initMenu.AddButton(Button(initRect, initOptions[i], SKYBLUE, GOLD, WHITE));
    }
}

void Application::ShowStatus(const std::string& message, Color color) {
    statusMessage = message;
    statusColor = color;
    statusTimer = 3.0f;
}

void Application::Update() {
    Vector2 mousePos = GetMousePosition();
    animationProgress += 0.02f;
    if (animationProgress > 1.0f)
        animationProgress = 1.0f;

    if (statusTimer > 0) {
        statusTimer -= GetFrameTime();
    }

    if (createButton.IsClicked(mousePos)) {
        showCreateMenu = !showCreateMenu;
        createMenu.visible = showCreateMenu;
    }

    if (startButton.IsClicked(mousePos)) {
        if (selectedOption == "Init") {
            HandleInit();
        }
        else {
            HandleOperation();
        }
        inputBox.text = "";
    }

    if (showCreateMenu) {
        int idx = createMenu.ProcessClick();
        if (idx != -1) {
            selectedOption = createMenu.buttons[idx].label;
            showCreateMenu = false;
            createMenu.visible = false;

            if (selectedOption == "Init") {
                showInitOptions = true;
                initMenu.visible = true;
            }
            else {
                showInitOptions = false;
                initMenu.visible = false;
                selectedInitOption = "";
                createButton.label = selectedOption;
            }
        }
    }

    if (showInitOptions) {
        int idx = initMenu.ProcessClick();
        if (idx != -1) {
            selectedInitOption = initMenu.buttons[idx].label;
            selectedOption = "Init";
            showInitOptions = false;
            initMenu.visible = false;
            createButton.label = selectedInitOption;
        }
    }

    inputBox.Update();
}


void Application::HandleInit() {
    tree.Clear();
    bool success = false;

    if (selectedInitOption == "Random") {
        srand(time(0));
        for (int i = 0; i < 7; i++) {
            tree.Add(rand() % 100);
        }
        success = true;
        ShowStatus("Random AVL tree created", GREEN);
    }
    else if (selectedInitOption == "File") {
        std::ifstream file(inputBox.text);
        if (!file) {
            ShowStatus("Failed to open file: " + inputBox.text, RED);
            return;
        }

        int num, count = 0;
        while (file >> num) {
            tree.Add(num);
            count++;
        }
        file.close();
        success = true;
        ShowStatus("Loaded " + std::to_string(count) + " numbers from file", GREEN);
    }
    else if (selectedInitOption == "Input") {
        std::stringstream ss(inputBox.text);
        int num, count = 0;
        while (ss >> num) {
            tree.Add(num);
            count++;
        }
        success = (count > 0);
        ShowStatus(success ? "Loaded numbers successfully" : "No numbers added", success ? GREEN : ORANGE);
    }

    if (success) {
        tree.Arrange();
    }
}

void Application::HandleOperation() {
    if (inputBox.text.empty()) {
        ShowStatus("Please enter a valid number", ORANGE);
        return;
    }

    try {
        int value = std::stoi(inputBox.text);
        if (selectedOption == "Add") {
            if (!tree.Search(value)) {
                tree.Add(value);
                ShowStatus("Added number " + std::to_string(value), GREEN);
            }
            else {
                ShowStatus("Number already exists", ORANGE);
            }
        }
        else if (selectedOption == "Del") {
            if (tree.Search(value)) {
                tree.Delete(value);
                ShowStatus("Deleted number " + std::to_string(value), GREEN);
            }
            else {
                ShowStatus("Number not found", ORANGE);
            }
        }
        else if (selectedOption == "Search") {
            ShowStatus(tree.Search(value) ? "Number found" : "Number not found", tree.Search(value) ? GREEN : ORANGE);
        }
    }
    catch (...) {
        ShowStatus("Invalid input!", RED);
    }
}

void Application::Draw()
{
    Color leftPanelColor = { 173, 216, 230, 255 }; // Màu nền panel bên trái
    ClearBackground(RAYWHITE);

    // Vẽ phần menu bên trái
    DrawRectangle(0, 0, leftWidth, h, leftPanelColor);
    DrawText("AVL TREE", leftWidth + (w - leftWidth) / 2 - MeasureText("AVL TREE", 50) / 2, 20, 50, RED);

    // Vẽ nút bấm và menu
    createButton.Draw();
    startButton.Draw();
    createMenu.Draw();
    initMenu.Draw();

    // Vẽ input box nếu cần nhập dữ liệu
    if (selectedOption == "Add" || selectedOption == "Del" || selectedOption == "Search" ||
        selectedInitOption == "Input" || selectedInitOption == "File")
    {
        inputBox.Draw();
    }

    // Hiển thị thông báo trạng thái ngay trên input box
    if (statusTimer > 0)
    {
        int statusX = inputBox.bounds.x + (inputBox.bounds.width / 2) - (MeasureText(statusMessage.c_str(), 20) / 2) + 30;
        int statusY = inputBox.bounds.y - 30;
        DrawText(statusMessage.c_str(), statusX, statusY, 20, RED);
    }

    // Hiển thị label cho input box
    if (selectedInitOption == "File")
        DrawText("Input file name:", inputBox.bounds.x, inputBox.bounds.y - 30, 20, DARKBLUE);
    else if (selectedInitOption == "Input")
        DrawText("Input sequence:", inputBox.bounds.x, inputBox.bounds.y - 30, 20, DARKBLUE);
    else if (selectedOption == "Add" || selectedOption == "Del" || selectedOption == "Search")
        DrawText("Input number:", inputBox.bounds.x, inputBox.bounds.y - 30, 20, DARKBLUE);

    // Vẽ cây AVL ở bên phải màn hình
    tree.Draw();

    // Vẽ khu vực hiển thị thuật toán
    DrawRectangle(0, h * 0.5f, leftWidth, h * 0.5f, ColorAlpha(RAYWHITE, 0.9f));
    DrawRectangleLines(0, h * 0.5f, leftWidth, h * 0.5f, DARKBLUE);
    DrawLine(0, h * 0.5f, leftWidth, h * 0.5f, DARKBLUE);
    DrawText("Algorithm Steps:", 20, h * 0.5f + 20, 20, DARKBLUE);
}
