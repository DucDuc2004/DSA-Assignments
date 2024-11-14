#include <iostream>
using namespace std;

struct Node {
    string fileName;
    int fileSize;
    int timestamp;
    Node* next;
};

Node* taoNode(const string& fileName, int fileSize, int timestamp) {
    Node* newNode = new Node();
    newNode->fileName = fileName;
    newNode->fileSize = fileSize;
    newNode->timestamp = timestamp;
    newNode->next = nullptr;
    return newNode;
}

void insertFile(Node*& head, const string& fileName, int fileSize, int timestamp) {
    Node* newNode = taoNode(fileName, fileSize, timestamp);
    if (head == nullptr || timestamp < head->timestamp) {
        newNode->next = head;
        head = newNode;
    } else {
        Node* current = head;
        while (current->next != nullptr && current->next->timestamp < timestamp) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

int calculateTotalSize(Node* head) {
    int totalSize = 0;
    Node* current = head;
    while (current != nullptr) {
        totalSize += current->fileSize;
        current = current->next;
    }
    return totalSize;
}

void removeSmallestFile(Node*& head) {
    if (head == nullptr) return;

    Node* smallest = head;
    Node* current = head;
    Node* prevSmallest = nullptr;
    Node* prev = nullptr;

    while (current != nullptr) {
        if (current->fileSize < smallest->fileSize) {
            smallest = current;
            prevSmallest = prev;
        }
        prev = current;
        current = current->next;
    }

    if (prevSmallest == nullptr) {
        head = head->next;
    } else {
        prevSmallest->next = smallest->next;
    }
    delete smallest;
}

void backupToUSB(Node*& head) {
    const int USB_SIZE = 32 * 1024;
    while (calculateTotalSize(head) > USB_SIZE) {
        removeSmallestFile(head);
    }
}

void freeList(Node*& head) {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

void displayFiles(Node* head) {
    Node* current = head;
    cout << "Danh sach cac tep trong thu muc D>Document:\n";
    while (current != nullptr) {
        cout << "Tep: " << current->fileName << ", Kich thuoc: " << current->fileSize 
             << "MB, Thoi gian tao: " << current->timestamp << endl;
        current = current->next;
    }
}

int main() {
    Node* head = nullptr;
    return 0;
}
