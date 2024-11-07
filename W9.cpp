#include <iostream>
using namespace std;

struct Node {
    int heso;
    int somu;
    Node* next;
};

void addPhantu(Node*& head, int coso, int mu) {
    Node* newNode = new Node();
    newNode->heso = coso;
    newNode->somu = mu;
    newNode->next = head;
    head = newNode;
}

void inDathuc (Node* head){
    Node* t = head;
    while (t != nullptr) {
        if (t->heso > 0 && t != head) {
            cout << " + ";
        }
        if (t->heso < 0) {
            cout << " - ";
        }
        cout << abs(t->heso);
        if (t->somu != 0) {
            cout << "x";
            if (t->somu != 1) {
                cout << "^" << t->somu;
            }
        }
        if (t->heso == 0 && t != head) {
            delete t;
        }
        t = t->next;
    }
    cout << endl;
}

Node* congDathuc(Node* fx, Node* gx) {
    Node* hx = nullptr;
    Node* p1 = fx;
    Node* p2 = gx;

    while(p1 != nullptr && p2 != nullptr) {
        if (p1->somu == p2->somu) {
            addPhantu(hx, p1->heso + p2->heso,p1->somu);
            p1 = p1->next;
            p2 = p2->next;
        }
        else if (p1->somu > p2->somu) {
            addPhantu(hx,p1->heso,p1->somu);
            p1 = p1->next;
        }
        else {
            addPhantu(hx,p2->heso,p2->somu);
            p2 = p2->next;
        }
    }
    while (p1 != nullptr) {
        addPhantu(hx,p1->heso,p1->somu);
        p1 = p1->next;
    }
    while (p2 != nullptr) {
        addPhantu(hx,p2->heso,p2->somu);
        p2 = p2->next;
    }
    return hx;
}

int main() {
    int b1,b2,heso,somu;
    cout << "Da thuc f(x)" << endl << "Nhap so phan tu f(x): ";
    cin >> b1;
    Node* f = nullptr;
    for(int i = 0; i < b1; i++) {
        cout << "Nhap he so: ";
        cin >> heso;
        cout << "Nhap so mu: ";
        cin >> somu;
        addPhantu(f,heso,somu);
    }

    cout << "Da thuc g(x)" << endl << "Nhap so phan tu g(x): ";
    cin >> b2;
    Node* g = nullptr;
    for(int i = 0; i < b2; i++) {
        cout << "Nhap he so: ";
        cin >> heso;
        cout << "Nhap so mu: ";
        cin >> somu;
        addPhantu(g,heso,somu);
    }

    cout << "f(x) = ";
    inDathuc(f);
    cout << "g(x) = ";
    inDathuc(g);

    Node* h = congDathuc(f,g);

    cout << "h(x) = ";
    inDathuc(h);

    return 0;
}