#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

class LinkedList {
private:
    Node* head;

public:
    LinkedList() : head(nullptr) {}

    LinkedList& themNodedau(int value) {
        Node* newNode = new Node();
        newNode->data = value;
        newNode->next = head;
        head = newNode;
        return *this;
    }

    LinkedList& themNodecuoi(int value) {
        Node* newNode = new Node();
        newNode->data = value;
        newNode->next = nullptr;
        if (head == nullptr) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
        return *this;
    }

    LinkedList& xoaNodedau() {
        if (head == nullptr) {
            cout << "Rong" << endl;
        } else {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        return *this;
    }

    LinkedList& xoaNodecuoi() {
        if (head->next == nullptr) { 
            delete head;
            head = nullptr;
        } else {
            Node* temp = head;
            while (temp->next->next != nullptr) {
                temp = temp->next;
            }
            delete temp->next;
            temp->next = nullptr;
        }
        return *this;
    }

    LinkedList& xoaNodechotruoc(int value) {
        Node* temp = head;
        while (temp != nullptr && temp->data != value) {
            temp = temp->next;
        }
            Node* nodeToDelete = temp->next;
            temp->next = temp->next->next;
            delete nodeToDelete;     
        return *this;
    }

    void hienthi() {
        Node* temp = head;
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

int main() {
    LinkedList list;

    list.themNodedau(1)
        .themNodedau(2)
        .themNodecuoi(3)
        .themNodecuoi(4);

    cout << "List ban dau: ";
    list.hienthi();

    cout << "Xoa node dau" << endl;
    list.xoaNodedau().hienthi();

    cout << "Xoa node cuoi" << endl;
    list.xoaNodecuoi().hienthi();

    cout << "Xoa node cho truoc" << endl;
    list.xoaNodechotruoc(1).hienthi();

    return 0;
}