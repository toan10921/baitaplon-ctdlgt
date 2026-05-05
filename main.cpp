#include <cctype>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <utility>

using namespace std;

#include "./models/HoaDon.h"
#include "./models/KhachHang.h"
#include "./models/SanPham.h"

ListKH listKH{nullptr};
ListHD listHD{nullptr};
ListSP listSP{nullptr};

const string SAN_PHAM_FILE = "./data/SanPham.txt";
const string KHACH_HANG_FILE = "./data/KhachHang.txt";
const string HOA_DON_FILE = "./data/HoaDon.txt";

void themNodeSanPham(ListSP &list, const SanPham &sp)
{
    NodeSP *newNode = new NodeSP{sp, nullptr};
    if (list.head == nullptr)
    {
        list.head = newNode;
        return;
    }

    NodeSP *temp = list.head;
    while (temp->next != nullptr)
    {
        temp = temp->next;
    }
    temp->next = newNode;
}

void themNodeKhachHang(ListKH &list, const KhachHang &kh)
{
    NodeKH *newNode = new NodeKH{kh, nullptr};
    if (list.head == nullptr)
    {
        list.head = newNode;
        return;
    }

    NodeKH *temp = list.head;
    while (temp->next != nullptr)
    {
        temp = temp->next;
    }
    temp->next = newNode;
}

void themNodeHoaDon(ListHD &list, const HoaDon &hd)
{
    NodeHD *newNode = new NodeHD{hd, nullptr};
    if (list.head == nullptr)
    {
        list.head = newNode;
        return;
    }

    NodeHD *temp = list.head;
    while (temp->next != nullptr)
    {
        temp = temp->next;
    }
    temp->next = newNode;
}

void xoaDanhSachSanPham(ListSP &list)
{
    while (list.head != nullptr)
    {
        NodeSP *nodeCanXoa = list.head;
        list.head = list.head->next;
        delete nodeCanXoa;
    }
}

void xoaDanhSachKhachHang(ListKH &list)
{
    while (list.head != nullptr)
    {
        NodeKH *nodeCanXoa = list.head;
        list.head = list.head->next;
        delete nodeCanXoa;
    }
}

void xoaDanhSachHoaDon(ListHD &list)
{
    while (list.head != nullptr)
    {
        NodeHD *nodeCanXoa = list.head;
        list.head = list.head->next;
        delete nodeCanXoa;
    }
}

NodeSP *timSanPhamTheoMa(ListSP &list, const string &maSP)
{
    NodeSP *temp = list.head;
    while (temp != nullptr)
    {
        if (temp->data.maSP == maSP)
        {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}

NodeKH *timKhachHangTheoMa(ListKH &list, const string &maKH)
{
    NodeKH *temp = list.head;
    while (temp != nullptr)
    {
        if (temp->data.maKH == maKH)
        {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}

bool tonTaiMaHoaDon(const ListHD &list, const string &maHD)
{
    NodeHD *temp = list.head;
    while (temp != nullptr)
    {
        if (temp->data.maHD == maHD)
        {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

string chuyenVeChuThuong(string chuoi)
{
    for (char &kyTu : chuoi)
    {
        kyTu = static_cast<char>(tolower(static_cast<unsigned char>(kyTu)));
    }
    return chuoi;
}

int nhapSoNguyen(const string &thongBao, int giaTriToiThieu)
{
    while (true)
    {
        cout << thongBao;
        int giaTri;
        if ((cin >> giaTri) && giaTri >= giaTriToiThieu)
        {
            cin.ignore(1000, '\n');
            return giaTri;
        }

        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Gia tri khong hop le. Vui long nhap lai." << endl;
    }
}

void inTieuDeDanhSachSanPham()
{
    cout << left << setw(10) << "Ma SP"
         << left << setw(20) << "Ten SP"
         << left << setw(15) << "Loai SP"
         << left << setw(10) << "Don Gia"
         << left << setw(10) << "So Luong"
         << left << setw(20) << "Nha San Xuat"
         << endl;
    cout << string(85, '-') << endl;
}

void inMotSanPham(const SanPham &sp)
{
    cout << left << setw(10) << sp.maSP
         << left << setw(20) << sp.tenSP
         << left << setw(15) << sp.loaiSP
         << left << setw(10) << sp.donGia
         << left << setw(10) << sp.soLuong
         << left << setw(20) << sp.nhasanXuat
         << endl;
}

void inTieuDeSanPhamKemLuongBan()
{
    cout << left << setw(10) << "Ma SP"
         << left << setw(20) << "Ten SP"
         << left << setw(15) << "Loai SP"
         << left << setw(10) << "Don Gia"
         << left << setw(10) << "Ton Kho"
         << left << setw(15) << "Luong Ban"
         << left << setw(20) << "Nha San Xuat"
         << endl;
    cout << string(100, '-') << endl;
}

void inMotSanPhamKemLuongBan(const SanPham &sp, int luongBan)
{
    cout << left << setw(10) << sp.maSP
         << left << setw(20) << sp.tenSP
         << left << setw(15) << sp.loaiSP
         << left << setw(10) << sp.donGia
         << left << setw(10) << sp.soLuong
         << left << setw(15) << luongBan
         << left << setw(20) << sp.nhasanXuat
         << endl;
}

int tinhTongSoLuongDaBan(const ListHD &list, const string &maSP)
{
    int tongSoLuong = 0;
    NodeHD *temp = list.head;
    while (temp != nullptr)
    {
        if (temp->data.maSP == maSP)
        {
            tongSoLuong += temp->data.soLuongMua;
        }
        temp = temp->next;
    }
    return tongSoLuong;
}

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
        {
            continue;
        }

        sp.donGia = stod(donGiaStr);
        sp.soLuong = stoi(soLuongStr);
        themNodeSanPham(list, sp);
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

void loadKhachHangTuFile(ListKH &list, const string &filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "Khong the mo file: " << filename << endl;
        return;
    }

    KhachHang kh;
    while (getline(file, kh.maKH, '\t'))
    {
        getline(file, kh.tenKH, '\t');
        getline(file, kh.diaChi, '\t');
        getline(file, kh.soDienThoai);
        if (kh.maKH.empty())
        {
            continue;
        }
        themNodeKhachHang(list, kh);
    }
    file.close();
}

void luuDanhSachKHVaoFile(const ListKH &list, const string &filename)
{
    ofstream file(filename);
    if (!file.is_open())
    {
        cout << "Khong the mo file de luu: " << filename << endl;
        return;
    }

    NodeKH *temp = list.head;
    while (temp != nullptr)
    {
        file << temp->data.maKH << '\t'
             << temp->data.tenKH << '\t'
             << temp->data.diaChi << '\t'
             << temp->data.soDienThoai << '\n';
        temp = temp->next;
    }
    file.close();
}

void loadHoaDonTuFile(ListHD &list, const string &filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "Khong the mo file: " << filename << endl;
        return;
    }

    HoaDon hd;
    string soLuongMuaStr, donGiaStr, thanhTienStr;
    while (getline(file, hd.maHD, '\t'))
    {
        getline(file, hd.maKH, '\t');
        getline(file, hd.maSP, '\t');
        getline(file, soLuongMuaStr, '\t');
        getline(file, donGiaStr, '\t');
        getline(file, hd.ngayBan, '\t');
        getline(file, thanhTienStr);
        if (hd.maHD.empty())
        {
            continue;
        }

        hd.soLuongMua = stoi(soLuongMuaStr);
        hd.donGia = stod(donGiaStr);
        hd.thanhTien = stod(thanhTienStr);
        themNodeHoaDon(list, hd);
    }
    file.close();
}

void luuDanhSachHDVaoFile(const ListHD &list, const string &filename)
{
    ofstream file(filename);
    if (!file.is_open())
    {
        cout << "Khong the mo file de luu: " << filename << endl;
        return;
    }

    NodeHD *temp = list.head;
    while (temp != nullptr)
    {
        file << temp->data.maHD << '\t'
             << temp->data.maKH << '\t'
             << temp->data.maSP << '\t'
             << temp->data.soLuongMua << '\t'
             << temp->data.donGia << '\t'
             << temp->data.ngayBan << '\t'
             << temp->data.thanhTien << '\n';
        temp = temp->next;
    }
    file.close();
}

void nhapDanhSachSanPham(ListSP &list)
{
    cout << "Nhap so luong san pham: ";
    int n;
    cin >> n;
    cin.ignore(1000, '\n');

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
        cin.ignore(1000, '\n');
        cout << "Nhap nha san xuat: ";
        getline(cin, sp.nhasanXuat);

        themNodeSanPham(list, sp);
    }

    luuDanhSachSPVaoFile(list, SAN_PHAM_FILE);
}

void inDanhSachSanPham(const ListSP &list)
{
    if (list.head == nullptr)
    {
        cout << "Danh sach san pham rong." << endl;
        return;
    }

    inTieuDeDanhSachSanPham();
    NodeSP *temp = list.head;
    while (temp != nullptr)
    {
        inMotSanPham(temp->data);
        temp = temp->next;
    }
}

void suaSanPhamTheoMa(ListSP &list, const string &maSP)
{
    NodeSP *temp = timSanPhamTheoMa(list, maSP);
    if (temp == nullptr)
    {
        cout << "Khong tim thay san pham co ma " << maSP << endl;
        return;
    }

    cout << "Nhap thong tin san pham moi:" << endl;
    cout << "Nhap ten san pham: ";
    getline(cin, temp->data.tenSP);
    cout << "Nhap loai san pham: ";
    getline(cin, temp->data.loaiSP);
    cout << "Nhap don gia: ";
    cin >> temp->data.donGia;
    cout << "Nhap so luong: ";
    cin >> temp->data.soLuong;
    cin.ignore(1000, '\n');
    cout << "Nhap nha san xuat: ";
    getline(cin, temp->data.nhasanXuat);

    luuDanhSachSPVaoFile(list, SAN_PHAM_FILE);
}

void xoaSanPhamTheoMa(ListSP &list, const string &maSP)
{
    NodeSP *temp = list.head;
    while (temp != nullptr)
    {
        if (temp->data.maSP == maSP)
        {
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
            delete temp;
            luuDanhSachSPVaoFile(list, SAN_PHAM_FILE);
            cout << "Da xoa san pham co ma " << maSP << endl;
            return;
        }
        temp = temp->next;
    }

    cout << "Khong tim thay san pham co ma " << maSP << endl;
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
    inTieuDeDanhSachSanPham();
    inMotSanPham(spMax);
}

void sapXepSanPhamTheoDonGiaTangDan(ListSP &list)
{
    if (list.head == nullptr)
    {
        cout << "Danh sach san pham rong." << endl;
        return;
    }

    bool swapped;
    do
    {
        swapped = false;
        NodeSP *temp = list.head;
        while (temp->next != nullptr)
        {
            if (temp->data.donGia > temp->next->data.donGia)
            {
                swap(temp->data, temp->next->data);
                swapped = true;
            }
            temp = temp->next;
        }
    } while (swapped);

    luuDanhSachSPVaoFile(list, SAN_PHAM_FILE);
    cout << "Da sap xep san pham theo don gia tang dan." << endl;
}

void themDonHang()
{
    if (listSP.head == nullptr)
    {
        cout << "Danh sach san pham rong. Khong the tao don hang." << endl;
        return;
    }

    HoaDon hd;
    cout << "Nhap ma hoa don: ";
    getline(cin, hd.maHD);
    if (hd.maHD.empty())
    {
        cout << "Ma hoa don khong duoc de trong." << endl;
        return;
    }
    if (tonTaiMaHoaDon(listHD, hd.maHD))
    {
        cout << "Ma hoa don da ton tai." << endl;
        return;
    }

    cout << "Nhap ma khach hang: ";
    getline(cin, hd.maKH);
    if (hd.maKH.empty())
    {
        cout << "Ma khach hang khong duoc de trong." << endl;
        return;
    }

    cout << "Nhap ma san pham: ";
    getline(cin, hd.maSP);
    NodeSP *sanPham = timSanPhamTheoMa(listSP, hd.maSP);
    if (sanPham == nullptr)
    {
        cout << "Khong tim thay san pham co ma " << hd.maSP << endl;
        return;
    }

    KhachHang khMoi;
    bool canThemKhachHang = false;
    if (timKhachHangTheoMa(listKH, hd.maKH) == nullptr)
    {
        canThemKhachHang = true;
        khMoi.maKH = hd.maKH;
        cout << "Khach hang chua ton tai. Nhap thong tin khach hang moi." << endl;
        cout << "Nhap ten khach hang: ";
        getline(cin, khMoi.tenKH);
        cout << "Nhap dia chi: ";
        getline(cin, khMoi.diaChi);
        cout << "Nhap so dien thoai: ";
        getline(cin, khMoi.soDienThoai);
    }

    cout << "San pham: " << sanPham->data.tenSP
         << " | Ton kho: " << sanPham->data.soLuong
         << " | Don gia: " << sanPham->data.donGia << endl;

    hd.soLuongMua = nhapSoNguyen("Nhap so luong mua: ", 1);
    if (hd.soLuongMua > sanPham->data.soLuong)
    {
        cout << "So luong mua vuot qua ton kho." << endl;
        return;
    }

    cout << "Nhap ngay ban: ";
    getline(cin, hd.ngayBan);
    if (hd.ngayBan.empty())
    {
        hd.ngayBan = "Khong ro";
    }

    hd.donGia = sanPham->data.donGia;
    hd.thanhTien = hd.donGia * hd.soLuongMua;

    if (canThemKhachHang)
    {
        themNodeKhachHang(listKH, khMoi);
        luuDanhSachKHVaoFile(listKH, KHACH_HANG_FILE);
    }

    themNodeHoaDon(listHD, hd);
    sanPham->data.soLuong -= hd.soLuongMua;
    luuDanhSachHDVaoFile(listHD, HOA_DON_FILE);
    luuDanhSachSPVaoFile(listSP, SAN_PHAM_FILE);

    cout << "Da them don hang thanh cong." << endl;
    cout << "Thanh tien: " << hd.thanhTien << endl;
}

void timSanPhamCoLuongBanLonNhatNhoNhat(const ListSP &danhSachSP, const ListHD &danhSachHD)
{
    if (danhSachHD.head == nullptr)
    {
        cout << "Chua co don hang nao." << endl;
        return;
    }

    NodeSP *tempSP = danhSachSP.head;
    SanPham spMax;
    SanPham spMin;
    int luongBanMax = 0;
    int luongBanMin = 0;
    bool daCoDuLieuBan = false;

    while (tempSP != nullptr)
    {
        int tongBan = tinhTongSoLuongDaBan(danhSachHD, tempSP->data.maSP);
        if (tongBan > 0)
        {
            if (!daCoDuLieuBan || tongBan > luongBanMax)
            {
                spMax = tempSP->data;
                luongBanMax = tongBan;
            }
            if (!daCoDuLieuBan || tongBan < luongBanMin)
            {
                spMin = tempSP->data;
                luongBanMin = tongBan;
            }
            daCoDuLieuBan = true;
        }
        tempSP = tempSP->next;
    }

    if (!daCoDuLieuBan)
    {
        cout << "Chua co san pham nao duoc ban." << endl;
        return;
    }

    cout << "San pham co luong ban lon nhat:" << endl;
    inTieuDeSanPhamKemLuongBan();
    inMotSanPhamKemLuongBan(spMax, luongBanMax);

    cout << "San pham co luong ban nho nhat:" << endl;
    inTieuDeSanPhamKemLuongBan();
    inMotSanPhamKemLuongBan(spMin, luongBanMin);
}

void tinhTongTonKho(const ListSP &list)
{
    int tongTonKho = 0;
    NodeSP *temp = list.head;
    while (temp != nullptr)
    {
        tongTonKho += temp->data.soLuong;
        temp = temp->next;
    }

    cout << "Tong so luong ton kho: " << tongTonKho << endl;
}

void timKiemTheoLoai(const ListSP &list)
{
    if (list.head == nullptr)
    {
        cout << "Danh sach san pham rong." << endl;
        return;
    }

    string loaiCanTim;
    cout << "Nhap loai san pham can tim: ";
    getline(cin, loaiCanTim);
    if (loaiCanTim.empty())
    {
        cout << "Loai san pham khong duoc de trong." << endl;
        return;
    }

    string loaiChuanHoa = chuyenVeChuThuong(loaiCanTim);
    int dem = 0;
    NodeSP *temp = list.head;

    while (temp != nullptr)
    {
        if (chuyenVeChuThuong(temp->data.loaiSP) == loaiChuanHoa)
        {
            if (dem == 0)
            {
                cout << "Danh sach san pham thuoc loai " << loaiCanTim << ":" << endl;
                inTieuDeDanhSachSanPham();
            }
            inMotSanPham(temp->data);
            dem++;
        }
        temp = temp->next;
    }

    if (dem == 0)
    {
        cout << "Khong tim thay san pham thuoc loai " << loaiCanTim << endl;
        return;
    }

    cout << "So san pham thuoc loai " << loaiCanTim << ": " << dem << endl;
}

void thongKeTheoDieuKien(const ListSP &list)
{
    if (list.head == nullptr)
    {
        cout << "Danh sach san pham rong." << endl;
        return;
    }

    int nguong = nhapSoNguyen("Nhap nguong so luong (thong ke san pham co so luong nho hon nguong): ", 0);
    int dem = 0;
    NodeSP *temp = list.head;

    while (temp != nullptr)
    {
        if (temp->data.soLuong < nguong)
        {
            if (dem == 0)
            {
                cout << "Cac san pham co so luong duoi " << nguong << ":" << endl;
                inTieuDeDanhSachSanPham();
            }
            inMotSanPham(temp->data);
            dem++;
        }
        temp = temp->next;
    }

    if (dem == 0)
    {
        cout << "Khong co san pham nao co so luong duoi " << nguong << endl;
        return;
    }

    cout << "Tong so san pham thoa dieu kien: " << dem << endl;
}

void menu()
{
    cout << "1. Nhap danh sach san pham" << endl;
    cout << "2. In danh sach san pham" << endl;
    cout << "3. Sua san pham theo ma" << endl;
    cout << "4. Xoa san pham theo ma" << endl;
    cout << "5. Tim kiem san pham gia cao nhat" << endl;
    cout << "6. Sap xep san pham theo don gia tang dan" << endl;
    cout << "7. Them don hang" << endl;
    cout << "8. Tim san pham co luong ban lon nhat/nho nhat" << endl;
    cout << "9. Tinh tong ton kho" << endl;
    cout << "10. Tim kiem theo loai" << endl;
    cout << "11. Thong ke theo dieu kien" << endl;
    cout << "12. Thoat" << endl;
    cout << "13. Ghi du lieu mau vao file" << endl;
    cout << "Chon chuc nang: ";
}

int main()
{
    loadSanPhamTuFile(listSP, SAN_PHAM_FILE);
    loadKhachHangTuFile(listKH, KHACH_HANG_FILE);
    loadHoaDonTuFile(listHD, HOA_DON_FILE);

    while (true)
    {
        menu();
        int choice;
        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Lua chon khong hop le. Vui long nhap so." << endl;
            continue;
        }
        cin.ignore(1000, '\n');

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
            break;
        }
        case 4:
        {
            string maSP;
            cout << "Nhap ma san pham can xoa: ";
            getline(cin, maSP);
            xoaSanPhamTheoMa(listSP, maSP);
            break;
        }
        case 5:
            timKiemSanPhamGiaCaoNhat(listSP);
            break;
        case 6:
            sapXepSanPhamTheoDonGiaTangDan(listSP);
            break;
        case 7:
            themDonHang();
            break;
        case 8:
            timSanPhamCoLuongBanLonNhatNhoNhat(listSP, listHD);
            break;
        case 9:
            tinhTongTonKho(listSP);
            break;
        case 10:
            timKiemTheoLoai(listSP);
            break;
        case 11:
            thongKeTheoDieuKien(listSP);
            break;
        case 12:
            cout << "Thoat chuong trinh." << endl;
            xoaDanhSachSanPham(listSP);
            xoaDanhSachKhachHang(listKH);
            xoaDanhSachHoaDon(listHD);
            return 0;
        case 13:
            insertSampleSanPhamData(SAN_PHAM_FILE);
            xoaDanhSachSanPham(listSP);
            loadSanPhamTuFile(listSP, SAN_PHAM_FILE);
            break;
        default:
            cout << "Lua chon khong hop le. Vui long chon lai." << endl;
        }
    }
}
