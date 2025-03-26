#include "AVLTree.h"

AVLTree::AVLTree(int width, int height) : root(nullptr), screenWidth(width), screenHeight(height) {}

AVLTree::~AVLTree() {
    Clear();
}

int AVLTree::Height(Node* node) {
    if (node == nullptr) return 0;
    return node->height;
}

int AVLTree::GetBalance(Node* node) {
    if (node == nullptr) return 0;
    return Height(node->left) - Height(node->right);
}

Node* AVLTree::RotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = std::max(Height(y->left), Height(y->right)) + 1;
    x->height = std::max(Height(x->left), Height(x->right)) + 1;

    return x;
}

Node* AVLTree::RotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = std::max(Height(x->left), Height(x->right)) + 1;
    y->height = std::max(Height(y->left), Height(y->right)) + 1;

    return y;
}

Node* AVLTree::FindMin(Node* node) {
    while (node->left != nullptr) node = node->left;
    return node;
}

Node* AVLTree::Delete(Node* node, int key) {
    if (node == nullptr) return node;

    if (key < node->key) {
        node->left = Delete(node->left, key);
    }
    else if (key > node->key) {
        node->right = Delete(node->right, key);
    }
    else {
        if (node->left == nullptr || node->right == nullptr) {
            Node* temp = node->left ? node->left : node->right;
            delete node;
            return temp;
        }
        Node* temp = FindMin(node->right);
        node->key = temp->key;
        node->right = Delete(node->right, temp->key);
    }

    if (node == nullptr) return node;

    node->height = 1 + std::max(Height(node->left), Height(node->right));
    int balance = GetBalance(node);

    if (balance > 1 && GetBalance(node->left) >= 0)
        return RotateRight(node);
    if (balance > 1 && GetBalance(node->left) < 0) {
        node->left = RotateLeft(node->left);
        return RotateRight(node);
    }
    if (balance < -1 && GetBalance(node->right) <= 0)
        return RotateLeft(node);
    if (balance < -1 && GetBalance(node->right) > 0) {
        node->right = RotateRight(node->right);
        return RotateLeft(node);
    }

    return node;
}

void AVLTree::Delete(int key) {
    root = Delete(root, key);
}

Node* AVLTree::Insert(Node* node, int key) {
    if (node == nullptr) return new Node(key);

    if (key < node->key)
        node->left = Insert(node->left, key);
    else if (key > node->key)
        node->right = Insert(node->right, key);
    else
        return node;

    node->height = 1 + std::max(Height(node->left), Height(node->right));

    int balance = GetBalance(node);

    if (balance > 1 && key < node->left->key)
        return RotateRight(node);
    if (balance < -1 && key > node->right->key)
        return RotateLeft(node);
    if (balance > 1 && key > node->left->key) {
        node->left = RotateLeft(node->left);
        return RotateRight(node);
    }
    if (balance < -1 && key < node->right->key) {
        node->right = RotateRight(node->right);
        return RotateLeft(node);
    }

    return node;
}

void AVLTree::Add(int key) {
    root = Insert(root, key);
    positionTree(root, screenWidth, screenHeight);
}

Node* AVLTree::Search(Node* node, int key) {
    if (node == nullptr || node->key == key) return node;
    if (key < node->key) return Search(node->left, key);
    return Search(node->right, key);
}

bool AVLTree::Search(int key) {
    return Search(root, key) != nullptr;
}

void AVLTree::Arrange() {
    positionTree(root, screenWidth, screenHeight);
}

void AVLTree::DrawTree(Node* node) {
    if (node == nullptr) return;
    if (node->position.x >= 0 && node->position.x <= screenWidth &&
        node->position.y >= 100 && node->position.y <= screenHeight) {
        if (node->left) {
            DrawLine(node->position.x, node->position.y, node->left->position.x, node->left->position.y, DARKGRAY);
        }
        if (node->right) {
            DrawLine(node->position.x, node->position.y, node->right->position.x, node->right->position.y, DARKGRAY);
        }
        node->DrawNode();
    }
    DrawTree(node->left);
    DrawTree(node->right);
}

void AVLTree::Draw() {
    DrawTree(root);
}

void AVLTree::ClearTree(Node* node) {
    if (node == nullptr) return;
    ClearTree(node->left);
    ClearTree(node->right);
    delete node;
}

void AVLTree::Clear() {
    ClearTree(root);
    root = nullptr;
}
