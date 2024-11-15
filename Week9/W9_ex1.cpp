#include <iostream>
#include <string>
#include <cstring>
using namespace std;

struct Node {
    string word;
    int solan;
    Node* next;
};

Node* taoNode(const string& word) {
    Node* newNode = new Node();
    newNode->word = word;
    newNode->solan = 1;
    newNode->next = nullptr;
    return newNode;
}

void addWord(Node*& head, const string& word) {
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->word == word) {
            temp->solan++;
            return;
        }
        temp = temp->next;
    }
    Node* newNode = taoNode(word);
    newNode->next = head;
    head = newNode;
}

string timWordnhieunhat(Node* head) {
    Node* temp = head;
    string wordnhieunhat;
    int max = 0;
    while (temp != nullptr) {
        if (temp->solan > max) {
            max = temp->solan;
            wordnhieunhat = temp->word;
        }
        temp = temp->next;
    }
    return wordnhieunhat;
}

void loaiboTuLay(Node*& head) {
    Node* temp = head;
    while (temp != nullptr && temp->next != nullptr) {
        if (temp->word + " " + temp->word == temp->next->word) {
            Node* duplicate = temp->next;
            temp->next = duplicate->next;
            delete duplicate;
        }
        temp = temp->next;
    }
}

int demsoTuVung(Node* head) {
    int solan = 0;
    Node* temp = head;
    while (temp != nullptr) {
        solan++;
        temp = temp->next;
    }
    return solan;
}

void giaiphong(Node*& head) {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

void tuVung(Node*& head, const string& s) {
    size_t pos = 0, found;
    while ((found = s.find_first_of(" ", pos)) != string::npos) {
        string word = s.substr(pos, found - pos);
        addWord(head, word);
        pos = found + 1;
    }
    addWord(head, s.substr(pos));
}

int main() {
    Node* head = nullptr;
    string s;
    
    cout << "Nhap cau: ";
    getline(cin, s);

    tuVung(head, s);

    string wordnhieunhat = timWordnhieunhat(head);
    cout << "Tu xuat hien nhieu nhat: " << wordnhieunhat << endl;

    loaiboTuLay(head);

    int sotuvung = demsoTuVung(head);
    cout << "So tu vung trong cau: " << sotuvung << endl;

    giaiphong(head);
    
    return 0;
}
