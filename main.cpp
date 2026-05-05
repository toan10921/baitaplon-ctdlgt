#include<iostream>
#include <string>
// đọc ghi file
#include <fstream>
// căn bảng in dữ liệu
#include <iomanip>

// setup namespace
using namespace std;

// include các file header cấu trúc dữ liệu
#include "./models/HoaDon.h"
#include "./models/KhachHang.h"
#include "./models/SanPham.h"

// khởi tạo các danh sách toàn cục 
ListKH listKH;
ListHD listHD;
ListSP listSP;

void loadSanPhamTuFile(ListSP &list, const string &filename){
    ifstream file(filename);
    if(!file.is_open()){
        cout << "Khong the mo file: " << filename << endl;
        return;
    }
    // load binary file
    while(file.peek() != EOF){
        SanPham sp;
        file.read((char*)&sp, sizeof(sp));
        // tạo node mới và thêm vào danh sách
        NodeSP *newNode = new NodeSP{sp, nullptr};
        // nếu là node đầu tiên thì gán head, ngược lại thêm vào cuối danh sách
        if(list.head == nullptr){
            list.head = newNode;
        } else {
            NodeSP *temp = list.head;
            while(temp->next != nullptr){
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }
    file.close();
}


void menu(){
    // dung tieng vet ko dau tranh bug
    cout << "1. Nhap danh sach san pham" << endl;
    cout << "2. In danh sach san pham" << endl;
    cout << "3. Sua san pham theo ma" << endl;
    cout << "4. Xoa san pham theo ma" << endl;
    cout << "5. Tim kiem san pham" << endl;
    cout << "6. Sap xep san pham" << endl;
    cout << "7. Them don hang" << endl;
    cout << "8. Tim san pham co luong ban lon nhat/nho nhat" << endl;
    cout << "9. Tinh tong ton kho" << endl;
    cout << "10. Tim kiem theo loai" << endl;
    cout << "11. Thong ke theo dieu kien" << endl;
    cout << "12. Thoat" << endl;
    cout << "Chon chuc nang: ";
}

void nhapDanhSachSanPham(ListSP &list){
    // code nhập danh sách sản phẩm
    cout << "Nhap so luong san pham: ";
    int n;
    cin >> n;
    cin.ignore(); // xóa phần còn lại của dòng
    for(int i = 0; i < n; i++){
        SanPham sp;
        cout << "Nhap thong tin san pham thu " << i+1 << ":" << endl;   
        cout << "Nhap ma san pham: ";
        getline(cin, sp.maSP);
        cout << "Nhap ten san pham: ";
        getline(cin, sp.tenSP);
        cout << "Nhap loai san pham: ";
        getline(cin, sp.loaiSP);
        cout << "Nhap don gia: ";
        cin >> sp.donGia;
        cout << "Nhap so luong: ";
        cin >> sp.soLuong;
        cin.ignore(); // xóa phần còn lại của dòng
        cout << "Nhap nha san xuat: ";
        getline(cin, sp.nhasanXuat);
        
        // tạo node mới và thêm vào danh sách
        NodeSP *newNode = new NodeSP{sp, nullptr};
        // nếu là node đầu tiên thì gán head, ngược lại thêm vào cuối danh sách
        if(list.head == nullptr){
            list.head = newNode;
        } else {
            NodeSP *temp = list.head;
            while(temp->next != nullptr){
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }
    // lưu lại danh sách sản phẩm vào file sau khi nhập xong
    ofstream file("./data/SanPham.txt", ios::binary);
    if(!file.is_open()){
        cout << "Khong the mo file de luu: " << "./data/SanPham.txt" << endl;
        return;
    }
    NodeSP *temp = list.head;
    while(temp != nullptr){
        file.write((char*)&temp->data, sizeof(temp->data));
        temp = temp->next;
    }
    file.close();
    return;
}


int main(int argc, char* argv[]){
    // load dữ liệu sản phẩm từ file khi chương trình bắt đầu
    loadSanPhamTuFile(listSP, "./data/SanPham.txt");
    while(true){
        menu();
        int choice;
        // fix lỗi nhập chữ thay vì số, tránh crash chương trình
        if(!(cin >> choice)){
            cin.clear(); // xóa trạng thái lỗi
            cin.ignore(1000, '\n'); // bỏ qua input rác trong buffer
            cout << "Lua chon khong hop le. Vui long nhap so." << endl;
            continue;
        }
        cin.ignore(1000, '\n'); // xóa phần còn lại của dòng
        switch(choice){
            case 1:
                cout << "Nhap danh sach san pham." << endl;
                nhapDanhSachSanPham(listSP);
                break;
            case 2:
                // code in danh sách sản phẩm
                break;
            case 3:
                // code sửa sản phẩm theo mã
                break;
            case 4:
                // code xóa sản phẩm theo mã
                break;
            case 5:
                // code tim kiem san pham
                break;
            case 6:
                // code sap xep san pham
                break;
            case 7:
                // code thêm đơn hàng
                break;
            case 8:
                // code tìm sản phẩm có lượng bán lớn nhất/nhỏ nhất
                break;
            case 9:
                // code tính tổng tồn kho
                break;
            case 10:
                // code tìm kiếm theo loại
                break;
            case 11:
                // code thống kê theo điều kiện
                break;
            case 12:
                cout << "Thoat chuong trinh." << endl;
                return 0; // thoat chuong trinh
            default:
                cout << "LLua chon khong hop le. Vui long chon lai." << endl;
        }
    }
    
}
