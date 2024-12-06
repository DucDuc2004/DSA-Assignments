#include <iostream>
#include <string>

using namespace std;

struct Node {
    string value;
    Node* left;
    Node* right;

    Node(string val) : value(val), left(nullptr), right(nullptr) {}
};

struct Stack {
    Node* nodes[100]; 
    int top;

    Stack() : top(-1) {}

    void push(Node* node) {
        if (top < 99) {
            nodes[++top] = node;
        }
    }

    Node* pop() {
        if (top >= 0) {
            return nodes[top--];
        }
        return nullptr;
    }

    Node* peek() {
        if (top >= 0) {
            return nodes[top];
        }
        return nullptr;
    }

    bool Empty() {
        return top == -1;
    }
};

bool checkToanTu(const string& toantu) {
    return toantu == "+" || toantu == "-" || toantu == "*" || toantu == "/" || toantu == "^";
}

int phepToan(const string& toantu) {
    if (toantu == "+" || toantu == "-") return 1;
    if (toantu == "*" || toantu == "/") return 2;
    if (toantu == "^") return 3;
    return 0;
}

Node* Tree(const string& duyet) {
    Stack StackToanTu, StackToanHang;
    string kitu = "";

    for (int i = 0; i < duyet.size(); ++i) {
        char ch = duyet[i];

        if (ch == ' ') continue;

        if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9') || ch == '.') {
            kitu += ch; 
        } else { 
            if (!kitu.empty()) { 
                StackToanHang.push(new Node(kitu)); 
                kitu = "";
            }

            string toantu(1, ch); 
            while (!StackToanTu.Empty() && phepToan(StackToanTu.peek()->value) >= phepToan(toantu)) {
                Node* nodeToanTu = StackToanTu.pop();
                nodeToanTu->right = StackToanHang.pop();
                nodeToanTu->left = StackToanHang.pop();
                StackToanHang.push(nodeToanTu);
            }
            StackToanTu.push(new Node(toantu)); 
        }
    }

    if (!kitu.empty()) {
        StackToanHang.push(new Node(kitu));
    }

    while (!StackToanTu.Empty()) {
        Node* nodeToanTu = StackToanTu.pop();
        nodeToanTu->right = StackToanHang.pop();
        nodeToanTu->left = StackToanHang.pop();
        StackToanHang.push(nodeToanTu);
    }

    return StackToanHang.pop(); 
}

void treeTienTo(Node* root) {
    if (root == nullptr) return;
    cout << root->value << " "; 
    treeTienTo(root->left);
    treeTienTo(root->right);
}

void treeHauTo(Node* root) {
    if (root == nullptr) return;
    treeHauTo(root->left);
    treeHauTo(root->right);
    cout << root->value << " "; 
}

int main() {
    cout << "Nhap bieu thuc: ";
    string bieuthuc;
    getline(cin, bieuthuc);

    Node* root = Tree(bieuthuc);

    cout << "Bieu thuc tien to: ";
    treeTienTo(root);
    cout << endl;

    cout << "Bieu thuc hau to: ";
    treeHauTo(root);
    cout << endl;

    return 0;
}
