#include "Node.h"

Node::Node(int key) : key(key), height(1), left(nullptr), right(nullptr), position({ 0, 0 }) {}

int Node::GetBalanceFactor() {
    int leftHeight = (left != nullptr) ? left->height : 0;
    int rightHeight = (right != nullptr) ? right->height : 0;
    return leftHeight - rightHeight;
}

void Node::DrawNode() {
    int radius = 40;
    DrawCircle(position.x, position.y, radius, SKYBLUE);
    DrawCircleLines(position.x, position.y, radius, DARKBLUE);
    DrawText(std::to_string(key).c_str(), position.x - 12, position.y - 12, 22, WHITE);

    std::string balanceStr = "bf:" + std::to_string(GetBalanceFactor());
    DrawText(balanceStr.c_str(), position.x - 15, position.y + 20, 16, RED);
}

void adjustNodePositions(Node* root, int level, int index, int totalNodesAtLevel, float screenWidth, float screenHeight) {
    if (root == nullptr) return;

    float xMin = screenWidth * 0.3f;
    float xMax = screenWidth;
    float xSpacing = (xMax - xMin) / (totalNodesAtLevel + 1);
    root->position.x = xMin + xSpacing * (index + 1);

    float yStart = 150;
    float ySpacing = (screenHeight - yStart) / 7;
    root->position.y = yStart + ySpacing * level;

    adjustNodePositions(root->left, level + 1, index * 2, totalNodesAtLevel * 2, screenWidth, screenHeight);
    adjustNodePositions(root->right, level + 1, index * 2 + 1, totalNodesAtLevel * 2, screenWidth, screenHeight);
}

void positionTree(Node* root, float screenWidth, float screenHeight) {
    if (root == nullptr) return;
    adjustNodePositions(root, 0, 0, 1, screenWidth, screenHeight);
}
