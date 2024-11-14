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
    string mostFrequent;
    int maxCount = 0;
    while (temp != nullptr) {
        if (temp->solan > maxCount) {
            maxCount = temp->solan;
            mostFrequent = temp->word;
        }
        temp = temp->next;
    }
    return mostFrequent;
}

void removeReduplicative(Node*& head) {
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

int countUniqueWords(Node* head) {
    int solan = 0;
    Node* temp = head;
    while (temp != nullptr) {
        solan++;
        temp = temp->next;
    }
    return solan;
}

void freeList(Node*& head) {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

void processSentence(Node*& head, const string& sentence) {
    size_t pos = 0, found;
    while ((found = sentence.find_first_of(" ", pos)) != string::npos) {
        string word = sentence.substr(pos, found - pos);
        addWord(head, word);
        pos = found + 1;
    }
    addWord(head, sentence.substr(pos));
}

int main() {
    Node* head = nullptr;
    string sentence;
    
    cout << "Nhap cau: ";
    getline(cin, sentence);

    processSentence(head, sentence);

    string mostFrequentWord = timWordnhieunhat(head);
    cout << "Tu xuat hien nhieu nhat: " << mostFrequentWord << endl;

    removeReduplicative(head);

    int uniqueWordCount = countUniqueWords(head);
    cout << "So tu vung trong cau: " << uniqueWordCount << endl;

    freeList(head);
    
    return 0;
}
