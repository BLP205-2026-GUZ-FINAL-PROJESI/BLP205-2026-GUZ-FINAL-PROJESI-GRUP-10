#ifndef MODUL2_H
#define MODUL2_H

#include <string>

// Bagli liste tabanli Yigin (Stack - LIFO) dugumu
struct YiginDugum {
    std::string islemAciklamasi;
    YiginDugum* next;
};

// Islem gecmisini tutan bagli liste tabanli Stack sinifi
class IslemYigini {
private:
    YiginDugum* top;
    int elemanSayisi;

public:
    IslemYigini();
    ~IslemYigini();

    bool bosMu() const;
    int boyut() const;
    void push(const std::string& aciklama);
    bool pop(std::string& cikarilan);
    bool peek(std::string& enUstteki) const;
    void listele() const;
    int temizle();
};

// Bagli liste tabanli Kuyruk (Queue - FIFO) dugumu
struct KuyrukDugum {
    std::string ogrenciNo;
    std::string adSoyad;
    std::string talepEdilenKitap;
    KuyrukDugum* next;
};

// Odunc kitap bekleyen ogrencileri tutan bagli liste tabanli Queue sinifi
class OduncKuyrugu {
private:
    KuyrukDugum* front;
    KuyrukDugum* rear;
    int elemanSayisi;

public:
    OduncKuyrugu();
    ~OduncKuyrugu();

    bool bosMu() const;
    int boyut() const;
    void enqueue(const std::string& ogrenciNo, const std::string& adSoyad, const std::string& kitap);
    bool dequeue(std::string& ogrenciNo, std::string& adSoyad, std::string& kitap);
    void listele() const;
    int temizle();
};

// Modul 2 alt menusu
void modul2Menu(IslemYigini& yigin, OduncKuyrugu& kuyruk);

#endif
