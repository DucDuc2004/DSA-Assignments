#include <iostream>
using namespace std;

struct Go {
    string loaiGo;
    int kichThuoc;
    int tuoiGo;
};

class KhoGo {
private:
    int soluongGo;           
    int sizeKho;         
    Go* array;         

public:
    KhoGo(int size) {
        sizeKho = size;
        soluongGo = 0;
        array = new Go[sizeKho];
    }

    bool Full() {
        return soluongGo == sizeKho ;
    }

    bool Rong() {
        return soluongGo == 0;
    }

    void themGo(Go thanhGo) {
        if (Full()) {
            cout << "Kho go day" << endl;
            return;
        }
        array[++soluongGo] = thanhGo;
    }

    int demTuoi(int tuoi) {
        int dem = 0;
        for (int i = 1; i <= soluongGo; i++) {
            if (array[i].tuoiGo == tuoi) {
                dem++;
            }
        }
        return dem;
    }

    void hienthi() {
        if (Rong()) {
            cout << "Kho go rong" << endl;
            return;
        }
        cout << "Danh sach cac thanh go: " << endl;
        for (int i = 1; i <= soluongGo; i++) {
            cout << "Loai go: " << array[i].loaiGo 
                 << ", Kich thuoc: " << array[i].kichThuoc 
                 << ", Tuoi tho: " << array[i].tuoiGo << endl;
        }
    }

    KhoGo() {
        delete[] array;
    }
};

int main() {
    KhoGo khoGo(10);

    khoGo.themGo({"Go thong", 10, 5});
    khoGo.themGo({"Go soi", 12, 10});
    khoGo.themGo({"Go lim", 30, 5});
    khoGo.themGo({"Go bach dan", 22, 8});
    khoGo.themGo({"Go vang", 92, 24});
    khoGo.themGo({"Go xa cu", 84, 21});
    khoGo.themGo({"Go phuong", 49, 8});
    khoGo.themGo({"Go bang", 93, 5});
    khoGo.themGo({"Go xua", 2, 10});

    khoGo.hienthi();

    int tuoiCanDem;
    cout << "Nhap so tuoi: ";
    cin >> tuoiCanDem;
    cout <<"So luong thanh go cung tuoi " << tuoiCanDem << " la: " 
         << khoGo.demTuoi(tuoiCanDem) << endl;
    return 0;
}
