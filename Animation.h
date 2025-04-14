#pragma once
#ifndef ANIMATION_H
#define ANIMATION_H

#include "Node.h"  // Đảm bảo Node đã được định nghĩa

// Hàm nội suy tuyến tính (Lerp)
float Lerp(float start, float end, float t);

// Cập nhật vị trí hiện tại của các node theo targetPosition
void updateAnimation(Node* node, float factor);

// Thiết lập targetPosition cho các node dựa trên cấu trúc cây
void setNodesTargetPosition(Node* root, int level, int index, int totalNodesAtLevel, float screenWidth, float screenHeight);

// Hàm vẽ cây với hiệu ứng animation (non-blocking)
// Lưu ý: hàm này sẽ cập nhật vị trí các node rồi vẽ toàn bộ cây.
void drawWithAnimation(Node* root, Node* highlightNode, float screenWidth, float screenHeight, float animSpeed);

#endif  // ANIMATION_H
