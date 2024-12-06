#include <iostream>
using namespace std;

struct File {
    string name;       
    int size;          
    int year;    
    File* next;        
};

class Folder {
private:
    File* head;

public:
    Folder() : head(nullptr) {}

    Folder& themFile(const string& name, int size, int year) {
        File* newFile = new File{name, size, year, nullptr};
        if (head == nullptr) {
            head = newFile;
        } else {
            File* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newFile;
        }
        return *this;
    }

    void hienthi() const {
        File* temp = head;
        while (temp != nullptr) {
            cout << " FileName: " << temp->name
                 << ", Dung luong: " << temp->size << " KB"
                 << ", year: " << temp->year << endl;
            temp = temp->next;
        }
    }

    Folder& sortfile() {
        if (head == nullptr || head->next == nullptr) return *this;

        bool swap;
        do {
            swap = false;
            File* current = head;
            File* prev = nullptr;

            while (current->next != nullptr) {
                if (current->size > current->next->size) {
                    File* nextNode = current->next;
                    current->next = nextNode->next;
                    nextNode->next = current;

                    if (prev == nullptr) {
                        head = nextNode;
                    } else {
                        prev->next = nextNode;
                    }
                    swap = true;
                }
                prev = (prev == nullptr) ? head : prev->next;
                current = (prev == nullptr) ? head->next : prev->next;
            }
        } while (swap);

        return *this;
    }

    Folder& xoaFile() {
    if (head == nullptr) return *this;

    int minSize = head->size;
    File* temp = head;
    while (temp != nullptr) {
        if (temp->size < minSize) {
            minSize = temp->size;
        }
        temp = temp->next;
    }

    File* xoa = nullptr;
    File* pxoa = nullptr;
    File* prev = nullptr;
    temp = head;

    int minyear; 
    while (temp != nullptr) {
        if (temp->size == minSize && temp->year < minyear) {
            minyear = temp->year;
            xoa = temp;
            pxoa = prev;
        }
        prev = temp;
        temp = temp->next;
    }

    if (xoa != nullptr) {
        if (xoa == head) {
            head = head->next;
        } else {
            pxoa->next = xoa->next;
        }
        delete xoa;
    }

    return *this;
}
};
int main() {
    Folder folder;

    folder.themFile("MinhDuc", 1024, 2022)
          .themFile("BachKhoa", 1, 2004)
          .themFile("Hust", 256, 2010)
          .themFile("HaNoi", 64, 2018)
          .themFile("SEEE", 1, 2010)
          .themFile("hihi", 2, 2006)
          .themFile("haha", 4, 2019)
          .themFile("IoT", 128, 2020);

    cout << "List File ban dau:" << endl;
    folder.hienthi();

    folder.sortfile();
    cout << endl <<"List sau khi sap xep:" << endl;
    folder.hienthi();

    folder.xoaFile();
    cout << endl << "Danh sach sau khi xoa:" << endl;
    folder.hienthi();

    return 0;
}

