struct HoaDon{
    string maHD;
    string maKH;
    string maSP;
    int soLuongMua;
    double donGia;
    string ngayBan;
    double thanhTien;
};

struct NodeHD{
    HoaDon data;
    NodeHD *next;
};

struct ListHD{
    NodeHD *head;
};