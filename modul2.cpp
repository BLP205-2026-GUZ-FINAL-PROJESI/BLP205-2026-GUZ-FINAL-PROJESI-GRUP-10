#include "modul2.h"
#include "ortak.h"
#include <iostream>

using namespace std;

// ===================== ISLEM YIGINI (STACK) =====================

IslemYigini::IslemYigini() : top(nullptr), elemanSayisi(0) {}

IslemYigini::~IslemYigini() {
    temizle();
}

bool IslemYigini::bosMu() const {
    return top == nullptr;
}

int IslemYigini::boyut() const {
    return elemanSayisi;
}

void IslemYigini::push(const string& aciklama) {
    YiginDugum* yeni = new YiginDugum;
    yeni->islemAciklamasi = aciklama;
    yeni->next = top;
    top = yeni;
    ++elemanSayisi;
}

bool IslemYigini::pop(string& cikarilan) {
    if (bosMu()) {
        return false;
    }
    YiginDugum* silinecek = top;
    cikarilan = silinecek->islemAciklamasi;
    top = top->next;
    delete silinecek;
    --elemanSayisi;
    return true;
}

bool IslemYigini::peek(string& enUstteki) const {
    if (bosMu()) {
        return false;
    }
    enUstteki = top->islemAciklamasi;
    return true;
}

void IslemYigini::listele() const {
    if (bosMu()) {
        cout << "[BILGI] Islem gecmisi yigini su anda bos.\n";
        return;
    }
    cout << "\n--- ISLEM GECMISI YIGINI (STACK - LIFO, Toplam: " << elemanSayisi << ") ---\n";
    YiginDugum* gezgin = top;
    int sira = 1;
    while (gezgin != nullptr) {
        if (sira == 1) {
            cout << " [TOP] " << sira << ". " << gezgin->islemAciklamasi << "\n";
        } else {
            cout << "       " << sira << ". " << gezgin->islemAciklamasi << "\n";
        }
        gezgin = gezgin->next;
        ++sira;
    }
}

int IslemYigini::temizle() {
    int silinenSayisi = 0;
    while (top != nullptr) {
        YiginDugum* silinecek = top;
        top = top->next;
        delete silinecek;
        ++silinenSayisi;
    }
    elemanSayisi = 0;
    return silinenSayisi;
}

// ===================== ODUNC KUYRUGU (QUEUE) =====================

OduncKuyrugu::OduncKuyrugu() : front(nullptr), rear(nullptr), elemanSayisi(0) {}

OduncKuyrugu::~OduncKuyrugu() {
    temizle();
}

bool OduncKuyrugu::bosMu() const {
    return front == nullptr;
}

int OduncKuyrugu::boyut() const {
    return elemanSayisi;
}

void OduncKuyrugu::enqueue(const string& ogrenciNo,
                           const string& adSoyad,
                           const string& kitap) {
    KuyrukDugum* yeni = new KuyrukDugum;
    yeni->ogrenciNo = ogrenciNo;
    yeni->adSoyad = adSoyad;
    yeni->talepEdilenKitap = kitap;
    yeni->next = nullptr;

    if (bosMu()) {
        front = yeni;
        rear = yeni;
    } else {
        rear->next = yeni;
        rear = yeni;
    }
    ++elemanSayisi;
}

bool OduncKuyrugu::dequeue(string& ogrenciNo,
                           string& adSoyad,
                           string& kitap) {
    if (bosMu()) {
        return false;
    }
    KuyrukDugum* silinecek = front;
    ogrenciNo = silinecek->ogrenciNo;
    adSoyad = silinecek->adSoyad;
    kitap = silinecek->talepEdilenKitap;

    front = front->next;
    if (front == nullptr) {
        rear = nullptr;
    }
    delete silinecek;
    --elemanSayisi;
    return true;
}

void OduncKuyrugu::listele() const {
    if (bosMu()) {
        cout << "[BILGI] Odunc kitap bekleyen ogrenci kuyrugu su anda bos.\n";
        return;
    }
    cout << "\n--- BEKLEYEN OGRENCI KUYRUGU (QUEUE - FIFO, Toplam: " << elemanSayisi << ") ---\n";
    KuyrukDugum* gezgin = front;
    int sira = 1;
    while (gezgin != nullptr) {
        cout << " " << sira << ". Ogrenci No: " << gezgin->ogrenciNo
                  << " | Ad Soyad: " << gezgin->adSoyad
                  << " | Talep Edilen Kitap: " << gezgin->talepEdilenKitap << "\n";
        gezgin = gezgin->next;
        ++sira;
    }
}

int OduncKuyrugu::temizle() {
    int silinenSayisi = 0;
    while (front != nullptr) {
        KuyrukDugum* silinecek = front;
        front = front->next;
        delete silinecek;
        ++silinenSayisi;
    }
    rear = nullptr;
    elemanSayisi = 0;
    return silinenSayisi;
}

// ===================== MODUL 2 MENU =====================

void modul2Menu(IslemYigini& yigin, OduncKuyrugu& kuyruk) {
    int secim;
    do {
        cout << "\n--- [MODUL 2: YIGIN (STACK) & KUYRUK (QUEUE)] ---\n";
        cout << "1. Odunc Sirasina Ogrenci Ekle (Queue - Enqueue)\n";
        cout << "2. Siradaki Ogrenciye Kitap Ver ve Cikar (Queue - Dequeue)\n";
        cout << "3. Bekleyen Ogrenci Kuyrugunu Listele (FIFO)\n";
        cout << "4. Islem Gecmisi Yiginini Goruntule (Stack - LIFO)\n";
        cout << "5. En Son Yapilan Islemi Gor (Stack - Peek/Top)\n";
        cout << "6. Son Islemi Geri Al / Yigindan Cikar (Stack - Pop/Undo)\n";
        cout << "0. Ana Menuye Don\n";

        secim = tamSayiOku("Alt Seciminiz: ", 0, 6);

        if (secim == 1) {
            string ogrNo = metinOku("Ogrenci Numarasi: ");
            string adSoyad = metinOku("Ogrenci Ad Soyad: ");
            string kitap = metinOku("Talep Edilen Kitap Adi: ");
            kuyruk.enqueue(ogrNo, adSoyad, kitap);
            yigin.push("[Modul 2] Kuyruga eklendi -> " + ogrNo + " (" + adSoyad + ") - " + kitap);
            cout << "[+] Ogrenci odunc kuyruguna basariyla eklendi.\n";
        } else if (secim == 2) {
            string ogrNo, adSoyad, kitap;
            if (kuyruk.dequeue(ogrNo, adSoyad, kitap)) {
                cout << "[+] Hizmet verildi ve kuyruktan cikarildi: "
                          << ogrNo << " - " << adSoyad << " (Kitap: " << kitap << ")\n";
                yigin.push("[Modul 2] Kitap odunc verildi (Dequeue) -> " + ogrNo + " - " + kitap);
            } else {
                cout << "[UYARI] Kuyruk bos! Hizmet verilecek ogrenci yok.\n";
            }
        } else if (secim == 3) {
            kuyruk.listele();
        } else if (secim == 4) {
            yigin.listele();
        } else if (secim == 5) {
            string enUstteki;
            if (yigin.peek(enUstteki)) {
                cout << "[TOP] En son yapilan islem: " << enUstteki << "\n";
            } else {
                cout << "[UYARI] Islem gecmisi yigini bos.\n";
            }
        } else if (secim == 6) {
            string cikarilan;
            if (yigin.pop(cikarilan)) {
                cout << "[-] Yigindan cikarilan (geri alinan) islem: " << cikarilan << "\n";
            } else {
                cout << "[UYARI] Yigin bos! Cikarilacak islem yok.\n";
            }
        }
    } while (secim != 0);
}
