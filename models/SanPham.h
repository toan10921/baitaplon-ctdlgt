struct SanPham{
    string maSP;
    string tenSP;
    string loaiSP;
    double donGia;
    int soLuong;
    string nhasanXuat;
};

struct NodeSP{
    SanPham data;
    NodeSP *next;
};

struct ListSP{
    NodeSP *head;
};