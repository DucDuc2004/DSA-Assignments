#include <iostream>
using namespace std;

struct Go {
    string loaiGo;   
    int kichThuoc;    
    int tuoiGo;     
    Go* next;         
};

class KhoGo {
private:
    Go* head; 

public:
    KhoGo() {
        head = nullptr;
    }

    void themGo(const string& loaiGo, int kichThuoc, int tuoiGo) {
        Go* thanhGo = new Go{loaiGo, kichThuoc, tuoiGo, nullptr};
        if (!head) {
            head = thanhGo; 
        } else {
            Go* temp = head;
            while (temp->next) { 
                temp = temp->next;
            }
            temp->next = thanhGo; 
        }
    }

    int demTuoi(int tuoi) {
        int dem = 0;
        Go* temp = head;
        while (temp) {
            if (temp->tuoiGo == tuoi) {
                dem++;
            }
            temp = temp->next;
        }
        return dem;
    }

    void hienthi() {
        if (!head) {
            cout << "Kho go rong" << endl;
            return;
        }
        cout << "Danh sach cac thanh go: " << endl;
        Go* temp = head;
        while (temp) {
            cout << "Loai go: " << temp->loaiGo 
                 << ", Kich thuoc: " << temp->kichThuoc 
                 << ", Tuoi tho: " << temp->tuoiGo << endl;
            temp = temp->next;
        }
    }

    ~KhoGo() {
        while (head) {
            Go* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    KhoGo khoGo;

    khoGo.themGo("Go thong", 10, 5);
    khoGo.themGo("Go soi", 12, 10);
    khoGo.themGo("Go lim", 30, 5);
    khoGo.themGo("Go bach dan", 22, 8);
    khoGo.themGo("Go vang", 92, 24);
    khoGo.themGo("Go xa cu", 84, 21);
    khoGo.themGo("Go phuong", 49, 8);
    khoGo.themGo("Go bang", 93, 5);
    khoGo.themGo("Go xua", 2, 10);

    khoGo.hienthi();

    int tuoiCanDem;
    cout << "Nhap so tuoi: ";
    cin >> tuoiCanDem;
    cout << "So luong thanh go cung tuoi " << tuoiCanDem << " la: " 
         << khoGo.demTuoi(tuoiCanDem) << endl;

    return 0;
}
