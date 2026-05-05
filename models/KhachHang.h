struct KhachHang{
    string maKH;
    string tenKH;
    string diaChi;
    string soDienThoai;
};

struct NodeKH{
    KhachHang data;
    NodeKH *next;
};

struct ListKH{
    NodeKH *head;
};