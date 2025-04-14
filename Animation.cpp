#include "Animation.h"
#include "raylib.h"
#include <string>
#include <cmath>   // Dùng cho fabs

// Hàm nội suy tuyến tính: tạo ra giá trị trung gian giữa start và end theo t
float Lerp(float start, float end, float t) {
    return start + (end - start) * t;
}

// Cập nhật vị trí hiện tại của node từ vị trí ban đầu tiến về targetPosition
void updateAnimation(Node* node, float factor) {
    if (node == nullptr) return;

    node->position.x = Lerp(node->position.x, node->targetPosition.x, factor);
    node->position.y = Lerp(node->position.y, node->targetPosition.y, factor);

    updateAnimation(node->left, factor);
    updateAnimation(node->right, factor);
}

// Thiết lập targetPosition cho các node (sắp xếp cây theo vị trí hiển thị)
void setNodesTargetPosition(Node* root, int level, int index, int totalNodesAtLevel, float screenWidth, float screenHeight) {
    if (root == nullptr) return;

    float xMin = screenWidth * 0.3f;
    float xMax = screenWidth;
    float xSpacing = (xMax - xMin) / (totalNodesAtLevel + 1);
    root->targetPosition.x = xMin + xSpacing * (index + 1);

    float yStart = 150;
    float ySpacing = (screenHeight - yStart) / 7;
    root->targetPosition.y = yStart + ySpacing * level;

    setNodesTargetPosition(root->left, level + 1, index * 2, totalNodesAtLevel * 2, screenWidth, screenHeight);
    setNodesTargetPosition(root->right, level + 1, index * 2 + 1, totalNodesAtLevel * 2, screenWidth, screenHeight);
}

// Hàm vẽ cây với hiệu ứng animation
void drawWithAnimation(Node* root, Node* highlightNode, float screenWidth, float screenHeight, float animSpeed) {
    // Cập nhật targetPosition cho toàn bộ cây (nếu có thay đổi cấu trúc)
    setNodesTargetPosition(root, 0, 0, 1, screenWidth, screenHeight);

    // Tính hệ số nội suy dựa trên thời gian của frame hiện tại
    float factor = animSpeed * GetFrameTime();  // Ví dụ: animSpeed ~ 5.0f
    if (factor > 1.0f) factor = 1.0f;

    // Cập nhật vị trí của các node từ position sang targetPosition
    updateAnimation(root, factor);

    // Sau đó, vẽ cây
    if (root != nullptr) {
        // Vẽ các đường nối giữa các node
        if (root->left) {
            DrawLine(root->position.x, root->position.y, root->left->position.x, root->left->position.y, DARKGRAY);
        }
        if (root->right) {
            DrawLine(root->position.x, root->position.y, root->right->position.x, root->right->position.y, DARKGRAY);
        }
        // Nếu node cần được highlight
        Color nodeColor = (root == highlightNode) ? YELLOW : SKYBLUE;
        root->DrawNode(nodeColor);

        // Vẽ đệ quy cho các node con
        drawWithAnimation(root->left, highlightNode, screenWidth, screenHeight, animSpeed);
        drawWithAnimation(root->right, highlightNode, screenWidth, screenHeight, animSpeed);
    }
}
