#include <iostream>
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
void insertSampleSanPhamData(const string &filename)
{
    ofstream file(filename);
    if (!file.is_open())
    {
        cout << "Khong the mo file de ghi du lieu mau: " << filename << endl;
        return;
    }
    SanPham ds[] = {
        {"SP01", "Gao ST25", "Thuc pham", 32000, 80, "Vinaseed"},
        {"SP02", "Sua tuoi", "Do uong", 12000, 150, "Vinamilk"},
        {"SP03", "Nuoc rua chen", "Gia dung", 28000, 45, "Sunlight"},
        {"SP04", "Banh quy", "Thuc pham", 45000, 60, "Kinh Do"},
        {"SP05", "Dau an", "Thuc pham", 52000, 35, "Tuong An"}};
    int n = sizeof(ds) / sizeof(ds[0]);
    for (int i = 0; i < n; ++i)
    {
        if (i == n)
        {
            file << ds[i].maSP << '\t'
                 << ds[i].tenSP << '\t'
                 << ds[i].loaiSP << '\t'
                 << ds[i].donGia << '\t'
                 << ds[i].soLuong;
            break;
        }
        file << ds[i].maSP << '\t'
             << ds[i].tenSP << '\t'
             << ds[i].loaiSP << '\t'
             << ds[i].donGia << '\t'
             << ds[i].soLuong << '\t'
             << ds[i].nhasanXuat << '\n';
    }
    file.close();
    cout << "Da ghi du lieu mau vao " << filename << endl;
}

void loadSanPhamTuFile(ListSP &list, const string &filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "Khong the mo file: " << filename << endl;
        return;
    }
    SanPham sp;
    string donGiaStr, soLuongStr;
    while (getline(file, sp.maSP, '\t'))
    {
        getline(file, sp.tenSP, '\t');
        getline(file, sp.loaiSP, '\t');
        getline(file, donGiaStr, '\t');
        getline(file, soLuongStr, '\t');
        getline(file, sp.nhasanXuat);
        if (sp.maSP.empty())
            continue;
        sp.donGia = stoi(donGiaStr);
        sp.soLuong = stoi(soLuongStr);

        NodeSP *newNode = new NodeSP{sp, nullptr};
        if (list.head == nullptr)
        {
            list.head = newNode;
        }
        else
        {
            NodeSP *temp = list.head;
            while (temp->next != nullptr)
            {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }
    file.close();
}

void luuDanhSachSPVaoFile(const ListSP &list, const string &filename)
{
    ofstream file(filename);
    if (!file.is_open())
    {
        cout << "Khong the mo file de luu: " << filename << endl;
        return;
    }
    NodeSP *temp = list.head;
    while (temp != nullptr)
    {
        file << temp->data.maSP << '\t'
             << temp->data.tenSP << '\t'
             << temp->data.loaiSP << '\t'
             << temp->data.donGia << '\t'
             << temp->data.soLuong << '\t'
             << temp->data.nhasanXuat << '\n';
        temp = temp->next;
    }
    file.close();
}

void nhapDanhSachSanPham(ListSP &list)
{
    // code nhập danh sách sản phẩm
    cout << "Nhap so luong san pham: ";
    int n;
    cin >> n;
    cin.ignore(); // xóa phần còn lại của dòng
    for (int i = 0; i < n; i++)
    {
        SanPham sp;
        cout << "Nhap thong tin san pham thu " << i + 1 << ":" << endl;
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
        if (list.head == nullptr)
        {
            list.head = newNode;
        }
        else
        {
            NodeSP *temp = list.head;
            while (temp->next != nullptr)
            {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }
    // lưu lại danh sách sản phẩm vào file sau khi nhập xong
    NodeSP *temp = list.head;
    luuDanhSachSPVaoFile(list, "./data/SanPham.txt");
    return;
}

void inDanhSachSanPham(const ListSP &list)
{
    // code in danh sách sản phẩm
    cout << left << setw(10) << "Ma SP"
         << left << setw(20) << "Ten SP"
         << left << setw(15) << "Loai SP"
         << left << setw(10) << "Don Gia"
         << left << setw(10) << "So Luong"
         << left << setw(20) << "Nha San Xuat"
         << endl;
    cout << string(85, '-') << endl; // in đường kẻ ngang
    NodeSP *temp = list.head;
    while (temp != nullptr)
    {
        cout << left << setw(10) << temp->data.maSP
             << left << setw(20) << temp->data.tenSP
             << left << setw(15) << temp->data.loaiSP
             << left << setw(10) << temp->data.donGia
             << left << setw(10) << temp->data.soLuong
             << left << setw(20) << temp->data.nhasanXuat
             << endl;
        temp = temp->next;
    }
}

void suaSanPhamTheoMa(ListSP &list, const string &maSP)
{
    NodeSP *temp = list.head;
    while (temp != nullptr)
    {
        if (temp->data.maSP == maSP)
        {
            cout << "Nhap thong tin san pham moi:" << endl;
            cout << "Nhap ten san pham: ";
            getline(cin, temp->data.tenSP);
            cout << "Nhap loai san pham: ";
            getline(cin, temp->data.loaiSP);
            cout << "Nhap don gia: ";
            cin >> temp->data.donGia;
            cout << "Nhap so luong: ";
            cin >> temp->data.soLuong;
            cin.ignore(); // xóa phần còn lại của dòng
            cout << "Nhap nha san xuat: ";
            getline(cin, temp->data.nhasanXuat);
            break;
        }
        temp = temp->next;
    }
    temp = list.head;
    // lưu lại danh sách sản phẩm vào file sau khi sửa xong
    luuDanhSachSPVaoFile(list, "./data/SanPham.txt");
}

void xoaSanPhamTheoMa(ListSP &list, const string &maSP)
{
    NodeSP *temp = list.head;
    while (temp != nullptr)
    {
        if (temp->data.maSP == maSP)
        {
            // code xóa node temp khỏi danh sách
            // thuật toán: nếu temp là node đầu tiên thì gán head = temp->next, ngược lại tìm node trước temp rồi gán prev->next = temp->next
            if (temp == list.head)
            {
                list.head = temp->next;
            }
            else
            {
                NodeSP *prev = list.head;
                while (prev->next != temp)
                {
                    prev = prev->next;
                }
                prev->next = temp->next;
            }
            delete temp; // giải phóng bộ nhớ của node bị xóa
            break;
        }
        temp = temp->next;
    }
    // lưu lại danh sách sản phẩm vào file sau khi xóa xong
    luuDanhSachSPVaoFile(list, "./data/SanPham.txt");
}

void timKiemSanPhamGiaCaoNhat(const ListSP &list)
{
    NodeSP *temp = list.head;
    if (temp == nullptr)
    {
        cout << "Danh sach san pham rong." << endl;
        return;
    }
    SanPham spMax = temp->data;
    while (temp != nullptr)
    {
        if (temp->data.donGia > spMax.donGia)
        {
            spMax = temp->data;
        }
        temp = temp->next;
    }
    cout << "San pham co don gia cao nhat:" << endl;
    cout << left << setw(10) << "Ma SP"
         << left << setw(20) << "Ten SP"
         << left << setw(15) << "Loai SP"
         << left << setw(10) << "Don Gia"
         << left << setw(10) << "So Luong"
         << left << setw(20) << "Nha San Xuat"
         << endl;
    cout << string(85, '-') << endl; // in đường kẻ ngang
    cout << left << setw(10) << spMax.maSP
         << left << setw(20) << spMax.tenSP
         << left << setw(15) << spMax.loaiSP
         << left << setw(10) << spMax.donGia
         << left << setw(10) << spMax.soLuong
         << left << setw(20) << spMax.nhasanXuat
         << endl;
}

void sapXepSanPhamTheoDonGiaTangDan(ListSP &list)
{
    // code sắp xếp sản phẩm theo đơn giá tăng dần
    if (list.head == nullptr)
    {
        cout << "Danh sach san pham rong." << endl;
        return;
    }
    // thuật toán sắp xếp: sử dụng thuật toán bubble sort để sắp xếp lại các node trong danh sách liên kết đơn
    bool swapped;
    do
    {
        swapped = false;
        NodeSP *temp = list.head;
        while (temp->next != nullptr)
        {
            if (temp->data.donGia > temp->next->data.donGia)
            {
                swap(temp->data, temp->next->data); // hoán đổi dữ liệu của 2 node
                swapped = true;
            }
            temp = temp->next;
        }
    } while (swapped);
    cout << "Da sap xep san pham theo don gia tang dan." << endl;
}

void menu()
{
    // dung tieng vet ko dau tranh bug
    cout << "1. Nhap danh sach san pham" << endl;
    cout << "2. In danh sach san pham" << endl;
    cout << "3. Sua san pham theo ma" << endl;
    cout << "4. Xoa san pham theo ma" << endl;
    cout << "5. Tim kiem san pham gia cao nhat" << endl;
    cout << "6. Sap xep san pham theo don gia tang dan" << endl;
    cout << "7. Them don hang" << endl;
    cout << "8. Tim san pham co luong ban lon nhat/nho nhat" << endl;
    cout << "9. TTinh tong ton kho" << endl;
    cout << "10. TTim kiem theo loai" << endl;
    cout << "11. Thong ke theo dieu kien" << endl;
    cout << "12. Thoat" << endl;
    cout << "13. Ghi du lieu mau vao file" << endl;
    cout << "Chon chuc nang: ";
}

void themDonHang()
{
    
}

int main(int argc, char *argv[])
{
    // load dữ liệu sản phẩm từ file khi chương trình bắt đầu
    loadSanPhamTuFile(listSP, "./data/SanPham.txt");
    while (true)
    {
        menu();
        int choice;
        // fix lỗi nhập chữ thay vì số, tránh crash chương trình
        if (!(cin >> choice))
        {
            cin.clear();            // xóa trạng thái lỗi
            cin.ignore(1000, '\n'); // bỏ qua input rác trong buffer
            cout << "Lua chon khong hop le. Vui long nhap so." << endl;
            continue;
        }
        cin.ignore(1000, '\n'); // xóa phần còn lại của dòng
        switch (choice)
        {
        case 1:
            nhapDanhSachSanPham(listSP);
            break;
        case 2:
            inDanhSachSanPham(listSP);
            break;
        case 3:
        {
            string maSP;
            cout << "Nhap ma san pham can sua: ";
            getline(cin, maSP);
            suaSanPhamTheoMa(listSP, maSP);
        }
        break;
        case 4:
        {
            string maSP;
            cout << "Nhap ma san pham can xoa: ";
            getline(cin, maSP);
            xoaSanPhamTheoMa(listSP, maSP);
        }
        break;
        case 5:
            timKiemSanPhamGiaCaoNhat(listSP);
            break;
        case 6:
            sapXepSanPhamTheoDonGiaTangDan(listSP);
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
        case 13:
            insertSampleSanPhamData("./data/SanPham.txt");
            break;
        default:
            cout << "Lua chon khong hop le. Vui long chon lai." << endl;
        }
    }
}
