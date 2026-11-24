// modul2.h
// Modul 2 - Bagli liste tabanli Yigin (Stack) ve Kuyruk (Queue)
// Sorumlu: Umut (2. ogrenci)

#ifndef MODUL2_H
#define MODUL2_H

#include <iostream>
#include <string>

// =====================================================================
// YIGIN (STACK) - bagli liste tabanli, islem gecmisi icin
// =====================================================================

struct IslemDugumu {
    std::string aciklama;   // islem aciklamasi
    IslemDugumu* sonraki;   // bir alt dugume isaretci
};

class IslemYigini {
public:
    IslemYigini() : ust(nullptr), boyut(0) {}

    // Yigin destructor'i tum dugumleri delete eder
    ~IslemYigini() { temizle(); }

    // Kopyalamayi engelle: iki nesne ayni dugumleri paylasip cift delete yapmasin
    IslemYigini(const IslemYigini&) = delete;
    IslemYigini& operator=(const IslemYigini&) = delete;

    // Push: yeni islemi yiginin en ustune ekler
    void push(const std::string& aciklama) {
        IslemDugumu* yeni = new IslemDugumu;
        yeni->aciklama = aciklama;
        yeni->sonraki = ust;   // yeni dugum eski ustu gosterir
        ust = yeni;            // yeni dugum artik en ust
        boyut++;
    }

    // Pop: en ustteki islemi cikarir. Basarili ise true doner ve degeri cikan'a yazar.
    bool pop(std::string& cikan) {
        if (bos()) {
            return false;
        }
        IslemDugumu* silinecek = ust;
        cikan = silinecek->aciklama;
        ust = silinecek->sonraki;
        delete silinecek;
        boyut--;
        return true;
    }

    // Peek/Top: en ustteki islemi cikarmadan gosterir
    bool peek(std::string& ustDeger) const {
        if (bos()) {
            return false;
        }
        ustDeger = ust->aciklama;
        return true;
    }

    // Yiginin tum elemanlarini en yeniden en eskiye listeler
    void listele() const {
        if (bos()) {
            std::cout << "[BILGI] Islem yigini bos.\n";
            return;
        }
        std::cout << "Islem gecmisi (en yeniden eskiye):\n";
        int sira = 1;
        for (IslemDugumu* p = ust; p != nullptr; p = p->sonraki) {
            std::cout << "  " << sira << ". " << p->aciklama << "\n";
            sira++;
        }
    }

    bool bos() const { return ust == nullptr; }
    int elemanSayisi() const { return boyut; }

    // Tum dugumleri tek tek delete eder
    void temizle() {
        while (ust != nullptr) {
            IslemDugumu* p = ust;
            ust = ust->sonraki;
            delete p;
        }
        boyut = 0;
    }

private:
    IslemDugumu* ust;   // yiginin en ustundeki dugum
    int boyut;          // eleman sayisi
};

// =====================================================================
// KUYRUK (QUEUE) - bagli liste tabanli, odunc kitap bekleme sirasi icin
// =====================================================================

struct OgrenciKaydi {
    int ogrenciNo;
    std::string adSoyad;
    int kitapId;
    std::string kitapAdi;
};

struct KuyrukDugumu {
    OgrenciKaydi veri;      // bekleyen ogrenci bilgisi
    KuyrukDugumu* sonraki;  // siradaki ogrenciye isaretci
};

class OduncKuyrugu {
public:
    OduncKuyrugu() : bas(nullptr), son(nullptr), boyut(0) {}

    // Kuyruk destructor'i tum dugumleri delete eder
    ~OduncKuyrugu() { temizle(); }

    OduncKuyrugu(const OduncKuyrugu&) = delete;
    OduncKuyrugu& operator=(const OduncKuyrugu&) = delete;

    // Enqueue: ogrenciyi kuyrugun sonuna ekler
    void enqueue(const OgrenciKaydi& kayit) {
        KuyrukDugumu* yeni = new KuyrukDugumu;
        yeni->veri = kayit;
        yeni->sonraki = nullptr;

        if (bos()) {
            bas = yeni;
            son = yeni;
        } else {
            son->sonraki = yeni;
            son = yeni;
        }
        boyut++;
    }

    // Dequeue: siradaki ilk ogrenciyi cikarir (FIFO). Cikan kaydi 'cikan'a yazar.
    bool dequeue(OgrenciKaydi& cikan) {
        if (bos()) {
            return false;
        }
        KuyrukDugumu* p = bas;
        cikan = p->veri;
        bas = bas->sonraki;
        if (bas == nullptr) {
            son = nullptr;   // kuyruk bosaldi, son da sifirlanmali
        }
        delete p;
        boyut--;
        return true;
    }

    // Kuyrugu bastan sona (FIFO sirasiyla) listeler
    void listele() const {
        if (bos()) {
            std::cout << "[BILGI] Bekleyen ogrenci yok.\n";
            return;
        }
        std::cout << "Bekleme sirasi (FIFO):\n";
        int sira = 1;
        for (KuyrukDugumu* p = bas; p != nullptr; p = p->sonraki) {
            std::cout << "  " << sira << ". No: " << p->veri.ogrenciNo
                      << " | " << p->veri.adSoyad
                      << " | Kitap: " << p->veri.kitapAdi
                      << " (ID " << p->veri.kitapId << ")\n";
            sira++;
        }
    }

    bool bos() const { return bas == nullptr; }
    int elemanSayisi() const { return boyut; }

    // Tum dugumleri tek tek delete eder
    void temizle() {
        while (bas != nullptr) {
            KuyrukDugumu* p = bas;
            bas = bas->sonraki;
            delete p;
        }
        son = nullptr;
        boyut = 0;
    }

private:
    KuyrukDugumu* bas;  // kuyrugun basi (ilk giren)
    KuyrukDugumu* son;  // kuyrugun sonu (son giren)
    int boyut;
};

#endif