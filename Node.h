#pragma once
#ifndef NODE_H
#define NODE_H

#include "raylib.h"
#include <iostream>
#include <string>

class Node {
public:
    int key, height;
    Node* left;
    Node* right;
    Vector2 position;

    Node(int key);

    int GetBalanceFactor();
    void DrawNode();
};

// Hàm hỗ trợ điều chỉnh vị trí node trên màn hình
void adjustNodePositions(Node* root, int level, int index, int totalNodesAtLevel, float screenWidth, float screenHeight);
void positionTree(Node* root, float screenWidth, float screenHeight);

#endif // NODE_H
