#pragma once
#ifndef AVLTREE_H
#define AVLTREE_H

#include "Node.h"
#include <algorithm>

class AVLTree {
public:
    Node* root;
    int screenWidth, screenHeight;

    AVLTree(int width, int height);
    ~AVLTree();

    int Height(Node* node);
    int GetBalance(Node* node);

    Node* RotateRight(Node* y);
    Node* RotateLeft(Node* x);

    Node* Insert(Node* node, int key);
    void Add(int key);

    Node* Delete(Node* node, int key);
    void Delete(int key);

    Node* FindMin(Node* node);

    Node* Search(Node* node, int key);
    bool Search(int key);

    void Arrange();
    void DrawTree(Node* node);
    void Draw();

    void ClearTree(Node* node);
    void Clear();
};

#endif // AVLTREE_H
