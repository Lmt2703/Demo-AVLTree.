#include "AVLTree.h"

AVLTree::AVLTree(int width, int height) : root(nullptr), screenWidth(width), screenHeight(height), highlight(NULL) {}

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

Node* AVLTree::Delete(Node* node, int key, bool skipDeleteStep = false) {
    if (node == nullptr) return node;

    if (key < node->key) {
        if (!isInitializing) {
            algorithmSteps.push_back("Go left from " + std::to_string(node->key));
        }
        node->left = Delete(node->left, key,false);
    }
    else if (key > node->key) {
        if (!isInitializing) {
            algorithmSteps.push_back("Go right from " + std::to_string(node->key));
        }
        node->right = Delete(node->right, key,false);
    }
    else
    {
        if (!isInitializing && !skipDeleteStep)
        {
            algorithmSteps.push_back("Find node " + std::to_string(node->key));
            algorithmSteps.push_back("Delete node " + std::to_string(node->key));
        }
           

        if (node->left == nullptr || node->right == nullptr) {
            Node* temp = (node->left) ? node->left : node->right;
            delete node;
            return temp;
        }
        else
        {
            // Tìm node min của cây con phải
            Node* temp = FindMin(node->right);
            node->key = temp->key;

            // Xóa node min nhưng **bỏ qua ghi thuật toán**
            node->right = Delete(node->right, temp->key, true);
        }
    }

    if (node == nullptr) return node;

    node->height = 1 + std::max(Height(node->left), Height(node->right));
    int balance = GetBalance(node);

    // Kiểm tra và cân bằng lại cây
    if (balance > 1 && GetBalance(node->left) >= 0) { // Left-Left Case
        if (!isInitializing) algorithmSteps.push_back("Right Rotation at " + std::to_string(node->key));
        return RotateRight(node);
    }
    if (balance > 1 && GetBalance(node->left) < 0) { // Left-Right Case
        if (!isInitializing) algorithmSteps.push_back("Left Rotation at " + std::to_string(node->left->key));
        node->left = RotateLeft(node->left);
        if (!isInitializing) algorithmSteps.push_back("Right Rotation at " + std::to_string(node->key));
        return RotateRight(node);
    }
    if (balance < -1 && GetBalance(node->right) <= 0) { // Right-Right Case
        if (!isInitializing) algorithmSteps.push_back("Left Rotation at " + std::to_string(node->key));
        return RotateLeft(node);
    }
    if (balance < -1 && GetBalance(node->right) > 0) { // Right-Left Case
        if (!isInitializing) algorithmSteps.push_back("Right Rotation at " + std::to_string(node->right->key));
        node->right = RotateRight(node->right);
        if (!isInitializing) algorithmSteps.push_back("Left Rotation at " + std::to_string(node->key));
        return RotateLeft(node);
    }

    return node;
}

void AVLTree::Delete(int key) {
    if (!isInitializing) {
        algorithmSteps.push_back("Step by step to delete " + std::to_string(key)+": ");
    }
    root = Delete(root, key);
    positionTree(root, screenWidth, screenHeight);
}

Node* AVLTree::Insert(Node* node, int key) {
    if (node == nullptr) {
        if (!isInitializing) {
            algorithmSteps.push_back("Create new node " + std::to_string(key));
        }
        Node* newNode = new Node(key);
        if (!isInitializing) {
            highlight = newNode;  // Đánh dấu node mới
        }
        return newNode;
    }

    if (key < node->key) {
        if (!isInitializing) {
            algorithmSteps.push_back("Go left from " + std::to_string(node->key));
        }
        node->left = Insert(node->left, key);
    }
    else if (key > node->key) {
        if (!isInitializing) {
            algorithmSteps.push_back("Go right from " + std::to_string(node->key));
        }
        node->right = Insert(node->right, key);
    }
    else {
        return node;
    }

    // Cập nhật chiều cao
    node->height = 1 + std::max(Height(node->left), Height(node->right));

    // Kiểm tra cân bằng
    int balance = GetBalance(node);

    // Xử lý các trường hợp mất cân bằng
    if (balance > 1 && key < node->left->key) {
        if (!isInitializing) algorithmSteps.push_back("Right Rotation at " + std::to_string(node->key));
        return RotateRight(node);
    }
    if (balance < -1 && key > node->right->key) {
        if (!isInitializing) algorithmSteps.push_back("Left Rotation at " + std::to_string(node->key));
        return RotateLeft(node);
    }
    if (balance > 1 && key > node->left->key) {
        if (!isInitializing) algorithmSteps.push_back("Left Rotation at " + std::to_string(node->left->key));
        node->left = RotateLeft(node->left);
        if (!isInitializing) algorithmSteps.push_back("Right Rotation at " + std::to_string(node->key));
        return RotateRight(node);
    }
    if (balance < -1 && key < node->right->key) {
        if (!isInitializing) algorithmSteps.push_back("Right Rotation at " + std::to_string(node->right->key));
        node->right = RotateRight(node->right);
        if (!isInitializing) algorithmSteps.push_back("Left Rotation at " + std::to_string(node->key));
        return RotateLeft(node);
    }

    return node;
}

void AVLTree::Add(int key) 
{
    if (!isInitializing) 
    {
        algorithmSteps.push_back("Step by step to insert " + std::to_string(key)+": ");
    }
    root = Insert(root, key);
    positionTree(root, screenWidth, screenHeight);
}

bool AVLTree::SearchWithEffect(Node* root, int key) {
    highlight = root;
    algorithmSteps.clear(); // Xóa các bước cũ
    algorithmSteps.push_back("Step by step to find " + std::to_string(key) + ": ");
    while (highlight != nullptr) {
        // Ghi lại bước thuật toán
        algorithmSteps.push_back("Checking node: " + std::to_string(highlight->key));

        // Vẽ lại cây với node highlight
        BeginDrawing();
        Draw(root);
        EndDrawing();

        // Tạm dừng để tạo hiệu ứng highlight
        WaitTime(0.5f);

        if (key == highlight->key) {
            algorithmSteps.push_back("Found " + std::to_string(key) + " at this node.");
            return true;  // Tìm thấy node
        }
        else if (key < highlight->key) {
            algorithmSteps.push_back("  "+std::to_string(key) + " < " + std::to_string(highlight->key) + " so node = node->left ");
            highlight = highlight->left;
        }
        else {
            algorithmSteps.push_back("  "+std::to_string(key) + " > " + std::to_string(highlight->key) + " so node = node->left ");
            highlight = highlight->right;
        }
    }

    algorithmSteps.push_back("Key " + std::to_string(key) + " not found in tree.");
    return false; // Không tìm thấy node
}

void AVLTree::Arrange() 
{
    positionTree(root, screenWidth, screenHeight);
}

void AVLTree::DrawTree(Node* node, Node* highlightNode) {
    if (node == nullptr) return;
    
    if (node->left)
    {
        DrawLine(node->position.x, node->position.y, node->left->position.x, node->left->position.y, DARKGRAY);
    }
    if (node->right)
    {
        DrawLine(node->position.x, node->position.y, node->right->position.x, node->right->position.y, DARKGRAY);
    }
     Color nodeColor = (node == highlightNode) ? YELLOW : SKYBLUE;
     node->DrawNode(nodeColor);
    DrawTree(node->left, highlightNode);
    DrawTree(node->right, highlightNode);
}

void AVLTree::Draw(Node* root)
{
    Node* highlightNode = highlight;
    DrawTree(root, highlightNode);
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
