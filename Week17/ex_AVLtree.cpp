#include <iostream>
using namespace std;

struct Node {
    int key;
    int height;
    Node* left;
    Node* right;

    Node(int value) : key(value), height(1), left(nullptr), right(nullptr) {}
};

int getHeight(Node* node) {
    return node == nullptr ? 0 : node->height;
}

int getBalance(Node* node) {
    return node == nullptr ? 0 : getHeight(node->left) - getHeight(node->right);
}

void updateHeight(Node* node) {
    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);
    node->height = 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}

Node* balance(Node* node) {
    updateHeight(node);

    int balanceFactor = getBalance(node);

    if (balanceFactor > 1) {
        if (getBalance(node->left) < 0) {
            node->left = rotateLeft(node->left);
        }
        return rotateRight(node);
    }

    if (balanceFactor < -1) {
        if (getBalance(node->right) > 0) {
            node->right = rotateRight(node->right);
        }
        return rotateLeft(node);
    }

    return node;
}

Node* insert(Node* root, int key) {
    if (root == nullptr)
        return new Node(key);

    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);
    else
        return root; 

    return balance(root);
}

void printTree(Node* root, int space = 0, int level = 0) {
    if (root == nullptr) return;

    space += 5;

    printTree(root->right, space, level + 1);

    cout << endl;
    for (int i = 5; i < space; i++) cout << " ";
    cout << root->key << "\n";

    printTree(root->left, space, level + 1);
}

int main() {
    Node* root = nullptr;

    int input[] = {240, 73, 101, 21, 13, 25, 11, 37, 89, 30, 15, 51};
    int size = sizeof(input) / sizeof(input[0]);

    for (int i = 0; i < size; ++i) {
        root = insert(root, input[i]);
    }

    printTree(root);

    return 0;
}
