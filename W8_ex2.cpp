#include <iostream>
using namespace std;

struct Node {
    int id;
    Node* next;
};


Node* vongTron(int N) {
    Node* head = new Node();
    head->id = 1;
    Node* current = head;

    for (int i = 2; i <= N; i++) {
        Node* newNode = new Node();
        newNode->id = i;
        current->next = newNode;
        current = newNode;
    }
    current->next = head;
    return head;
}

int Josephus(Node* head, int M) {
    Node* current = head;
    Node* prev = nullptr;

    while (current->next != current) {
        for (int count = 1; count < M; count++) {
            prev = current;
            current = current->next;
        }
        prev->next = current->next;
        cout << "Nguoi " << current->id << " bi loai." << endl;
        
        delete current; 
        current = prev->next; 
    }

    int winner = current->id;
    delete current; 
    return winner;
}

int main() {
    int N, M;
    cout << "Nhap so nguoi choi N: ";
    cin >> N;
    cout << "Nhap M (so luot chuyen qua bong truoc khi loai): ";
    cin >> M;

    Node* head = vongTron(N);
    int winner = Josephus(head, M);

    cout << "Nguoi chien thang la: " << winner << endl;
    return 0;
}
