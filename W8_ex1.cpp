#include <iostream>
using namespace std;

struct Ngay { 
    int ngay, thang, nam; 
}; 

struct SinhVien { 
    char maSV[8]; 
    char hoTen[50]; 
    int gioiTinh;   
    Ngay ngaySinh; 
    char diaChi[100]; 
    char lop[12]; 
    char khoa[7]; 
};

struct Node { 
    SinhVien data; 
    Node *link; 
}; 

struct List {   
    Node *first;
    Node *last; 
};

void initList(List &list) {
    list.first = nullptr;
    list.last = nullptr;
}

Node* taoNode(const SinhVien &sv) {
    Node* newNode = new Node;
    newNode->data = sv;
    newNode->link = nullptr;
    return newNode;
}

int soSanhChuoi(const char* str1, const char* str2) {
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) {
            return (str1[i] < str2[i]) ? -1 : 1;
        }
        i++;
    }
    if (str1[i] == '\0' && str2[i] == '\0') return 0;
    return (str1[i] == '\0') ? -1 : 1;
}

void themSinhVien(List &list, const SinhVien &sv) {
    Node* newNode = taoNode(sv);

    if (list.first == nullptr || soSanhChuoi(sv.maSV, list.first->data.maSV) < 0) {
        newNode->link = list.first;
        list.first = newNode;
        if (list.last == nullptr) list.last = newNode;
    } else {
        Node* p = nullptr;
        Node* duyet = list.first;
        while (duyet != nullptr && soSanhChuoi(duyet->data.maSV, sv.maSV) < 0) {
            p = duyet;
            duyet = duyet->link;
        }
        newNode->link = duyet;
        p->link = newNode;
        if (duyet == nullptr) list.last = newNode;
    }
}

void nhapSinhVien(SinhVien &sv) {
    cout << "Nhap ma sinh vien: ";
    cin >> sv.maSV;
    cin.ignore();
    cout << "Nhap ten: ";
    cin.getline(sv.hoTen, sizeof(sv.hoTen));
    cout << "Nhap gioi tinh (1: Nam , 0: Nu): ";
    cin >> sv.gioiTinh;
    cout << "Nhap ngay sinh: ";
    cin >> sv.ngaySinh.ngay >> sv.ngaySinh.thang >> sv.ngaySinh.nam;
    cin.ignore();
    cout << "Nhap dia chi: ";
    cin.getline(sv.diaChi, sizeof(sv.diaChi));
    cout << "Nhap lop: ";
    cin >> sv.lop;
    cout << "Nhap khoa: ";
    cin >> sv.khoa;
}

void inList(const List &list) {
    Node* duyet = list.first;
    while (duyet != nullptr) {
        cout << "Ma SV: " << duyet->data.maSV
             << ", Ho ten: " << duyet->data.hoTen
             << ", Gioi tinh: " << (duyet->data.gioiTinh ? "Nam" : "Nu")
             << ", Ngay sinh: " << duyet->data.ngaySinh.ngay << "/"
             << duyet->data.ngaySinh.thang << "/" << duyet->data.ngaySinh.nam
             << ", Dia chi: " << duyet->data.diaChi
             << ", Lop: " << duyet->data.lop
             << ", Khoa: " << duyet->data.khoa << "\n";
        duyet = duyet->link;
    }
}

bool soSanhNgay(const Ngay &ng1, const Ngay &ng2) {
    return ng1.ngay == ng2.ngay && ng1.thang == ng2.thang && ng1.nam == ng2.nam;
}

void hienthiSVcungngaysinh(const List &list) {
    bool found = false;
    for (Node* p1 = list.first; p1 != nullptr; p1 = p1->link) {
        for (Node* pss = p1->link; pss != nullptr; pss = pss->link) {
            if (soSanhNgay(p1->data.ngaySinh, pss->data.ngaySinh)) {
                if (!found) {
                    cout << "Danh sach sinh vien co cung ngay sinh:\n";
                    found = true;
                }
                cout << "Ma SV: " << pss->data.maSV << ", Ho ten: " << pss->data.hoTen << "\n";
                break;
            }
        }
    }
    if (!found) cout << "Khong tim thay sinh vien cung ngay sinh.\n";
}

void xoaSVcungngaysinh(List &list) {
    Node* p = nullptr;
    Node* duyet = list.first;
    while (duyet != nullptr) {
        Node* check = duyet->link;
        bool flag = false;
        while (check != nullptr) {
            if (soSanhNgay(duyet->data.ngaySinh, check->data.ngaySinh)) {
                flag = true;
                break;
            }
            check = check->link;
        }
        if (flag) {
            if (p == nullptr) list.first = duyet->link;
            else p->link = duyet->link;

            Node* temp = duyet;
            duyet = duyet->link;
            delete temp;
        } else {
            p = duyet;
            duyet = duyet->link;
        }
    }
}

void hienThiSV(const List &list) {
    cout << "Danh sach sinh vien sau khi loai bo sinh vien co cung ngay sinh:\n";
    inList(list);
}

int main() {
    List listSV;
    initList(listSV);
    
    int n;
    cout << "Nhap so luong sinh vien: ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        SinhVien sv;
        cout << "Nhap thong tin sinh vien thu " << i + 1 << ":\n";
        nhapSinhVien(sv);
        themSinhVien(listSV, sv);
    }
    cout << "Danh sach sap xep theo ma so sinh vien: \n";
    inList(listSV);
    hienthiSVcungngaysinh(listSV);
    xoaSVcungngaysinh(listSV);
    hienThiSV(listSV);

    return 0;
}
