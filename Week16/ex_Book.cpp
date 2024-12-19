#include <iostream>

const int MAX_MUCCON = 10; 

struct Node {
    char title[50];     
    int pages;              
    int totalPages;     
    int soMucCon;         
    Node* muccon[MAX_MUCCON]; 

    Node(const char* t, int p) {
        int i = 0;
        while (t[i] != '\0' && i < 49) {
            title[i] = t[i];
            i++;
        }
        title[i] = '\0';

        pages = p;
        totalPages = p;
        soMucCon = 0;
        for (int j = 0; j < MAX_MUCCON; j++) {
            muccon[j] = nullptr;
        }
    }
};

bool ssString(const char* str1, const char* str2) {
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) {
            return false;
        }
        i++;
    }
    return str1[i] == '\0' && str2[i] == '\0';
}

int totalPages(Node* node) {
    if (node == nullptr) return 0;

    int total = 0;
    for (int i = 0; i < node->soMucCon; i++) {
        total += totalPages(node->muccon[i]); 
    }

    node->totalPages = (node->soMucCon > 0) ? total : node->pages;
    return node->totalPages;
}


int soChapter(Node* root) {
    if (root == nullptr) return 0;
    return root->soMucCon;
}

Node* longChapter(Node* root) {
    if (root == nullptr || root->soMucCon == 0) return nullptr;

    Node* longestChapter = root->muccon[0];
    for (int i = 1; i < root->soMucCon; i++) {
        if (root->muccon[i]->totalPages > longestChapter->totalPages) {
            longestChapter = root->muccon[i];
        }
    }
    return longestChapter;
}

bool deleteSection(Node* Node, const char* targetTitle) {
    if (Node == nullptr) return false;

    for (int i = 0; i < Node->soMucCon; i++) {
        if (ssString(Node->muccon[i]->title, targetTitle)) {
            delete Node->muccon[i];
            for (int j = i; j < Node->soMucCon - 1; j++) {
                Node->muccon[j] = Node->muccon[j + 1];
            }
            Node->muccon[Node->soMucCon - 1] = nullptr;
            Node->soMucCon--;
            totalPages(Node); 
            return true;
        }
       
        if (deleteSection(Node->muccon[i], targetTitle)) {
            totalPages(Node);
            return true;
        }
    }
    return false;
}

void printBook(Node* root, int level = 0) {
    if (root == nullptr) return;

    for (int i = 0; i < level; i++) std::cout << "  "; 
    if (root->soMucCon > 0) {
        std::cout << root->title << " (Total: " << root->totalPages << " pages)\n";
    } else {
        std::cout << root->title << " (" << root->totalPages << " pages)\n";
    }

    for (int i = 0; i < root->soMucCon; i++) {
        printBook(root->muccon[i], level + 1);
    }
}

int main() {
   
    Node* book = new Node("Artificial Intelligence", 0);

    book->muccon[0] = new Node("Chapter 1: AI Introduction", 10);
    book->muccon[1] = new Node("Chapter 2: Machine Learning", 20);
    book->muccon[2] = new Node("Chapter 3: Deep Learning", 25);
    book->soMucCon = 3;

    book->muccon[0]->muccon[0] = new Node("Section 1.1: Definition of AI", 3);
    book->muccon[0]->muccon[1] = new Node("Section 1.2: Applications of AI", 4);
    book->muccon[0]->muccon[2] = new Node("Section 1.3: History of AI", 3);
    book->muccon[0]->soMucCon = 3;

    book->muccon[1]->muccon[0] = new Node("Section 2.1: Linear Regression", 5);
    book->muccon[1]->muccon[1] = new Node("Section 2.2: Support Vector Machines", 8);
    book->muccon[1]->muccon[2] = new Node("Section 2.3: Decision Trees", 7);
    book->muccon[1]->soMucCon = 3;

    book->muccon[2]->muccon[0] = new Node("Section 3.1: Neural Networks", 10);
    book->muccon[2]->muccon[1] = new Node("Section 3.2: Convolutional Neural Networks", 12);
    book->muccon[2]->muccon[2] = new Node("Section 3.3: Recurrent Neural Networks", 8);
    book->muccon[2]->soMucCon = 3;

    totalPages(book);

    std::cout << "Book Structure\n";
    printBook(book);

    std::cout << "\nNumber of Chapters in the Book: " << soChapter(book) << "\n";

    Node* longest = longChapter(book);
    if (longest) {
        std::cout << "Longest Chapter: " << longest->title << " (Total: " << longest->totalPages << " pages)\n";
    }

    std::cout << "\nDelete 'Section 2.2: Support Vector Machines':\n";
    deleteSection(book, "Section 2.2: Support Vector Machines");
    printBook(book);

    delete book;

    return 0;
}
