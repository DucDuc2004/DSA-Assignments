#include <iostream>

const int MAX_MUCCON = 10; // Số mục con tối đa cho mỗi node

struct Node {
    char title[50];         // Tên Chapter hoặc mục
    int pages;              // Số trang của mục
    int totalPages;         // Tổng số trang (gồm mục con)
    int soMucCon;         // Số mục con
    Node* muccon[MAX_MUCCON]; // Mảng con trỏ đến các mục con

    Node(const char* t, int p) {
        // Sao chép tên mục vào title
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

// Hàm so sánh hai chuỗi ký tự (tự triển khai thay vì dùng strcmp)
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

// Hàm tính tổng số trang cho một node (bao gồm các mục con)
int totalPages(Node* node) {
    if (node == nullptr) return 0;
    int total = node->pages;
    for (int i = 0; i < node->soMucCon; i++) {
        total += totalPages(node->muccon[i]);
    }
    node->totalPages = total;
    return total;
} 

// Đếm số Chapter của cuốn sách (các node con trực tiếp của gốc)
int soChapter(Node* root) {
    if (root == nullptr) return 0;
    return root->soMucCon;
}

// Tìm Chapter dài nhất trong cuốn sách
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

// Tìm và xóa một mục khỏi cây dựa trên tên mục
bool deleteSection(Node* parent, const char* targetTitle) {
    if (parent == nullptr) return false;

    for (int i = 0; i < parent->soMucCon; i++) {
        if (ssString(parent->muccon[i]->title, targetTitle)) {
            // Xóa node
            delete parent->muccon[i];
            for (int j = i; j < parent->soMucCon - 1; j++) {
                parent->muccon[j] = parent->muccon[j + 1];
            }
            parent->muccon[parent->soMucCon - 1] = nullptr;
            parent->soMucCon--;
            totalPages(parent); // Cập nhật lại tổng số trang
            return true;
        }
        // Đệ quy tìm và xóa trong các mục con
        if (deleteSection(parent->muccon[i], targetTitle)) {
            totalPages(parent);
            return true;
        }
    }
    return false;
}

// In cây sách theo dạng cây có thụt lề
void printBook(Node* root, int level = 0) {
    if (root == nullptr) return;

    for (int i = 0; i < level; i++) std::cout << "  "; // Thụt lề
    std::cout << root->title << " (" << root->pages << " pages, Total: " << root->totalPages << " pages)\n";

    for (int i = 0; i < root->soMucCon; i++) {
        printBook(root->muccon[i], level + 1);
    }
}

int main() {
   
    Node* book = new Node("Artificial Intelligence", 0);

    // Thêm các Chapter
    book->muccon[0] = new Node("Chapter 1: AI Introduction", 10);
    book->muccon[1] = new Node("Chapter 2: Machine Learning", 20);
    book->muccon[2] = new Node("Chapter 3: Deep Learning", 25);
    book->soMucCon = 3;

    // Thêm mục con cho Chapter 2
    book->muccon[1]->muccon[0] = new Node("Section 2.1: ML Introduction", 5);
    book->muccon[1]->muccon[1] = new Node("Section 2.2: ML Algorithm", 8);
    book->muccon[1]->soMucCon = 2;

    // Tính tổng số trang
    totalPages(book);

    // In cây sách
    std::cout << "Cấu trúc cuốn sách:\n";
    printBook(book);

    // Đếm Chapter
    std::cout << "\nSố Chapter của cuốn sách: " << soChapter(book) << "\n";

    // Tìm Chapter dài nhất
    Node* longest = longChapter(book);
    if (longest) {
        std::cout << "Chapter dài nhất: " << longest->title << " với " << longest->totalPages << " trang\n";
    }

    // Xóa một mục
    std::cout << "\nXóa mục 'Section 2.2: Các thuật toán ML':\n";
    deleteSection(book, "Section 2.2: Các thuật toán ML");
    printBook(book);

    // Dọn dẹp bộ nhớ
    delete book;

    return 0;
}
