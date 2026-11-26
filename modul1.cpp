#include "modul1.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

namespace {
void kitapSatiriYazdir(const Kitap& k) {
    std::cout << "  ID: " << std::setw(4) << k.kitapID
              << " | Kitap: " << std::left << std::setw(28) << k.kitapAdi
              << " | Yazar: " << std::setw(20) << k.yazarAdi
              << " | Sayfa: " << std::right << std::setw(4) << k.sayfaSayisi << "\n";
}
} // namespace

// ===================== KITAP KATALOGU (DOUBLY LINKED LIST) =====================

KitapKatalogu::KitapKatalogu() : head(nullptr), tail(nullptr), elemanSayisi(0) {}

KitapKatalogu::~KitapKatalogu() {
    temizle();
}

bool KitapKatalogu::bosMu() const {
    return head == nullptr;
}

int KitapKatalogu::boyut() const {
    return elemanSayisi;
}

bool KitapKatalogu::idVarMi(int id) const {
    KitapDugum* gezgin = head;
    while (gezgin != nullptr) {
        if (gezgin->veri.kitapID == id) {
            return true;
        }
        gezgin = gezgin->next;
    }
    return false;
}

bool KitapKatalogu::basaEkle(const Kitap& kitap) {
    if (idVarMi(kitap.kitapID)) {
        return false;
    }
    KitapDugum* yeni = new KitapDugum;
    yeni->veri = kitap;
    yeni->prev = nullptr;
    yeni->next = head;

    if (bosMu()) {
        head = yeni;
        tail = yeni;
    } else {
        head->prev = yeni;
        head = yeni;
    }
    ++elemanSayisi;
    return true;
}

bool KitapKatalogu::sonaEkle(const Kitap& kitap) {
    if (idVarMi(kitap.kitapID)) {
        return false;
    }
    KitapDugum* yeni = new KitapDugum;
    yeni->veri = kitap;
    yeni->next = nullptr;
    yeni->prev = tail;

    if (bosMu()) {
        head = yeni;
        tail = yeni;
    } else {
        tail->next = yeni;
        tail = yeni;
    }
    ++elemanSayisi;
    return true;
}

bool KitapKatalogu::hedefOnuneEkle(int hedefID, const Kitap& kitap, std::string& hataMesaji) {
    if (bosMu()) {
        hataMesaji = "Katalog bos oldugu icin hedef ID bulunamadi.";
        return false;
    }
    if (idVarMi(kitap.kitapID)) {
        hataMesaji = "Bu kitap ID zaten katalogda mevcut.";
        return false;
    }

    KitapDugum* hedef = head;
    while (hedef != nullptr && hedef->veri.kitapID != hedefID) {
        hedef = hedef->next;
    }
    if (hedef == nullptr) {
        hataMesaji = "Hedef kitap ID katalogda bulunamadi.";
        return false;
    }

    if (hedef == head) {
        return basaEkle(kitap);
    }

    KitapDugum* yeni = new KitapDugum;
    yeni->veri = kitap;
    yeni->prev = hedef->prev;
    yeni->next = hedef;
    hedef->prev->next = yeni;
    hedef->prev = yeni;
    ++elemanSayisi;
    return true;
}

bool KitapKatalogu::idIleSil(int id, Kitap& silinen) {
    if (bosMu()) {
        return false;
    }
    KitapDugum* gezgin = head;
    while (gezgin != nullptr && gezgin->veri.kitapID != id) {
        gezgin = gezgin->next;
    }
    if (gezgin == nullptr) {
        return false;
    }

    silinen = gezgin->veri;

    // Tek dugumlu liste durumu
    if (gezgin == head && gezgin == tail) {
        head = nullptr;
        tail = nullptr;
    } else if (gezgin == head) {
        head = head->next;
        head->prev = nullptr;
    } else if (gezgin == tail) {
        tail = tail->prev;
        tail->next = nullptr;
    } else {
        gezgin->prev->next = gezgin->next;
        gezgin->next->prev = gezgin->prev;
    }

    delete gezgin;
    --elemanSayisi;
    return true;
}

void KitapKatalogu::ileriListele() const {
    if (bosMu()) {
        std::cout << "[BILGI] Kitap katalogu su anda bos.\n";
        return;
    }
    std::cout << "\n--- KITAP KATALOGU (BASTAN SONA / NEXT, Toplam: " << elemanSayisi << ") ---\n";
    KitapDugum* gezgin = head;
    while (gezgin != nullptr) {
        kitapSatiriYazdir(gezgin->veri);
        gezgin = gezgin->next;
    }
}

void KitapKatalogu::geriListele() const {
    if (bosMu()) {
        std::cout << "[BILGI] Kitap katalogu su anda bos.\n";
        return;
    }
    std::cout << "\n--- KITAP KATALOGU (SONDAN BASA / PREV, Toplam: " << elemanSayisi << ") ---\n";
    KitapDugum* gezgin = tail;
    while (gezgin != nullptr) {
        kitapSatiriYazdir(gezgin->veri);
        gezgin = gezgin->prev;
    }
}

void KitapKatalogu::analizEt(int sayfaEsigi) const {
    if (bosMu()) {
        std::cout << "[BILGI] Katalog bos oldugu icin istatistik analizi yapilamiyor.\n";
        return;
    }

    long long toplamSayfa = 0;
    const Kitap* minKitap = &(head->veri);
    const Kitap* maxKitap = &(head->veri);

    KitapDugum* gezgin = head;
    while (gezgin != nullptr) {
        toplamSayfa += gezgin->veri.sayfaSayisi;
        if (gezgin->veri.sayfaSayisi < minKitap->sayfaSayisi) {
            minKitap = &(gezgin->veri);
        }
        if (gezgin->veri.sayfaSayisi > maxKitap->sayfaSayisi) {
            maxKitap = &(gezgin->veri);
        }
        gezgin = gezgin->next;
    }

    double ortalama = static_cast<double>(toplamSayfa) / elemanSayisi;

    std::cout << "\n--- KATALOG ISTATISTIK ANALIZI ---\n";
    std::cout << "Toplam Kitap Sayisi   : " << elemanSayisi << "\n";
    std::cout << "Toplam Sayfa Sayisi   : " << toplamSayfa << "\n";
    std::cout << "Ortalama Sayfa Sayisi : " << std::fixed << std::setprecision(2) << ortalama << "\n";
    std::cout << "En Az Sayfali Kitap   : " << minKitap->kitapAdi << " (ID: " << minKitap->kitapID
              << ", " << minKitap->sayfaSayisi << " sayfa)\n";
    std::cout << "En Cok Sayfali Kitap  : " << maxKitap->kitapAdi << " (ID: " << maxKitap->kitapID
              << ", " << maxKitap->sayfaSayisi << " sayfa)\n";

    std::cout << "\n" << sayfaEsigi << " sayfa esigini asan kitaplar:\n";
    int esikUstuSayac = 0;
    gezgin = head;
    while (gezgin != nullptr) {
        if (gezgin->veri.sayfaSayisi > sayfaEsigi) {
            kitapSatiriYazdir(gezgin->veri);
            ++esikUstuSayac;
        }
        gezgin = gezgin->next;
    }
    if (esikUstuSayac == 0) {
        std::cout << "  [BILGI] Bu sayfa esigini asan kitap bulunamadi.\n";
    }
}

bool KitapKatalogu::dosyayaYaz(const std::string& dosyaAdi) const {
    std::ofstream dosya(dosyaAdi.c_str());
    if (!dosya.is_open()) {
        return false;
    }

    KitapDugum* gezgin = head;
    while (gezgin != nullptr) {
        dosya << gezgin->veri.kitapID << "|"
              << gezgin->veri.kitapAdi << "|"
              << gezgin->veri.yazarAdi << "|"
              << gezgin->veri.sayfaSayisi << "\n";
        gezgin = gezgin->next;
    }
    dosya.close();
    return true;
}

bool KitapKatalogu::dosyadanOkuVeGoster(const std::string& dosyaAdi) const {
    std::ifstream dosya(dosyaAdi.c_str());
    if (!dosya.is_open()) {
        return false;
    }

    std::cout << "\n--- DOSYADAN OKUNAN KATALOG KAYITLARI (" << dosyaAdi << ") ---\n";
    std::string satir;
    int satirNo = 0;
    while (std::getline(dosya, satir)) {
        if (satir.empty()) {
            continue;
        }
        std::stringstream ss(satir);
        std::string idStr, ad, yazar, sayfaStr;

        if (std::getline(ss, idStr, '|') &&
            std::getline(ss, ad, '|') &&
            std::getline(ss, yazar, '|') &&
            std::getline(ss, sayfaStr, '|')) {
            ++satirNo;
            std::cout << " " << satirNo << ". ID: " << idStr
                      << " | Kitap: " << ad
                      << " | Yazar: " << yazar
                      << " | Sayfa: " << sayfaStr << "\n";
        }
    }
    if (satirNo == 0) {
        std::cout << "  [BILGI] Dosyada gosterilecek kitap kaydi yok (katalog bos).\n";
    }
    dosya.close();
    return true;
}

bool KitapKatalogu::diziyeAktar(Kitap*& dizi, int& boyut) const {
    dizi = nullptr;
    boyut = 0;
    if (bosMu()) {
        return false;
    }
    boyut = elemanSayisi;
    dizi = new Kitap[boyut];

    KitapDugum* gezgin = head;
    int indeks = 0;
    while (gezgin != nullptr && indeks < boyut) {
        dizi[indeks] = gezgin->veri;
        gezgin = gezgin->next;
        ++indeks;
    }
    return true;
}

int KitapKatalogu::temizle() {
    int silinenSayisi = 0;
    while (head != nullptr) {
        KitapDugum* silinecek = head;
        head = head->next;
        delete silinecek;
        ++silinenSayisi;
    }
    tail = nullptr;
    elemanSayisi = 0;
    return silinenSayisi;
}

// ===================== DUYURU PANOSU (CIRCULAR SINGLY LINKED LIST) =====================

DuyuruPanosu::DuyuruPanosu() : head(nullptr), elemanSayisi(0), sonrakiID(1) {}

DuyuruPanosu::~DuyuruPanosu() {
    temizle();
}

bool DuyuruPanosu::bosMu() const {
    return head == nullptr;
}

int DuyuruPanosu::boyut() const {
    return elemanSayisi;
}

void DuyuruPanosu::ekle(const std::string& metin) {
    DuyuruDugum* yeni = new DuyuruDugum;
    yeni->duyuruID = sonrakiID++;
    yeni->metin = metin;

    if (bosMu()) {
        head = yeni;
        yeni->next = head;
    } else {
        DuyuruDugum* son = head;
        while (son->next != head) {
            son = son->next;
        }
        son->next = yeni;
        yeni->next = head;
    }
    ++elemanSayisi;
}

void DuyuruPanosu::tamTurListele() const {
    if (bosMu()) {
        std::cout << "[BILGI] Duyuru panosu su anda bos.\n";
        return;
    }
    std::cout << "\n--- DUYURU PANOSU (DAIRESEL LISTE - 1 TAM TUR, Toplam: " << elemanSayisi << ") ---\n";
    DuyuruDugum* gezgin = head;
    do {
        std::cout << " [Duyuru #" << gezgin->duyuruID << "] " << gezgin->metin << "\n";
        gezgin = gezgin->next;
    } while (gezgin != head);
    std::cout << " [BILGI] Baslangic dugumune (Duyuru #" << head->duyuruID << ") geri donuldu.\n";
}

int DuyuruPanosu::temizle() {
    if (bosMu()) {
        return 0;
    }
    int silinenSayisi = 0;
    DuyuruDugum* gezgin = head->next;
    while (gezgin != head) {
        DuyuruDugum* silinecek = gezgin;
        gezgin = gezgin->next;
        delete silinecek;
        ++silinenSayisi;
    }
    delete head;
    ++silinenSayisi;
    head = nullptr;
    elemanSayisi = 0;
    return silinenSayisi;
}

// ===================== MODUL 1 MENU =====================

namespace {
Kitap kullanicidanKitapAl() {
    Kitap k;
    k.kitapID = tamSayiOku("Kitap ID (1 - 99999): ", 1, 99999);
    k.kitapAdi = metinOku("Kitap Adi: ");
    k.yazarAdi = metinOku("Yazar Adi: ");
    k.sayfaSayisi = tamSayiOku("Sayfa Sayisi (1 - 10000): ", 1, 10000);
    return k;
}
} // namespace

void modul1Menu(KitapKatalogu& katalog, DuyuruPanosu& pano, IslemYigini& yigin) {
    int secim;
    const std::string dosyaAdi = "kutuphane_katalog.txt";

    do {
        std::cout << "\n--- [MODUL 1: BAGLI LISTELER & DOSYA ISLEMLERI] ---\n";
        std::cout << "1. Kitap Basa Ekle (Cift Yonlu Bagli Liste)\n";
        std::cout << "2. Kitap Sona Ekle (Cift Yonlu Bagli Liste)\n";
        std::cout << "3. Kitap Araya Ekle (Hedef ID Oncesine)\n";
        std::cout << "4. Kitap Sil (ID ile)\n";
        std::cout << "5. Kitaplari Bastan Sona Listele (next ile Ileri)\n";
        std::cout << "6. Kitaplari Sondan Basa Listele (prev ile Ters)\n";
        std::cout << "7. Katalog Istatistik Analizi (Toplam, Ortalama, Min, Max, Filtre)\n";
        std::cout << "8. Dairesel Bagli Liste Duyuru Panosunu Goruntule / Ekle\n";
        std::cout << "9. Katalogu Dosyaya Yaz (ofstream) ve Dosyadan Oku (ifstream)\n";
        std::cout << "0. Ana Menuye Don\n";

        secim = tamSayiOku("Alt Seciminiz: ", 0, 9);

        if (secim == 1) {
            Kitap k = kullanicidanKitapAl();
            if (katalog.basaEkle(k)) {
                std::cout << "[+] Kitap basa eklendi: ID " << k.kitapID << " - " << k.kitapAdi << "\n";
                yigin.push("[Modul 1] Basa kitap eklendi -> ID " + std::to_string(k.kitapID) + ": " + k.kitapAdi);
            } else {
                std::cout << "[HATA] ID " << k.kitapID << " zaten katalogda kayitli!\n";
            }
        } else if (secim == 2) {
            Kitap k = kullanicidanKitapAl();
            if (katalog.sonaEkle(k)) {
                std::cout << "[+] Kitap sona eklendi: ID " << k.kitapID << " - " << k.kitapAdi << "\n";
                yigin.push("[Modul 1] Sona kitap eklendi -> ID " + std::to_string(k.kitapID) + ": " + k.kitapAdi);
            } else {
                std::cout << "[HATA] ID " << k.kitapID << " zaten katalogda kayitli!\n";
            }
        } else if (secim == 3) {
            if (katalog.bosMu()) {
                std::cout << "[UYARI] Katalog bos! Once basa veya sona kitap ekleyiniz.\n";
                continue;
            }
            int hedefID = tamSayiOku("Hangi Kitap ID oncesine eklensin?: ", 1, 99999);
            Kitap k = kullanicidanKitapAl();
            std::string hata;
            if (katalog.hedefOnuneEkle(hedefID, k, hata)) {
                std::cout << "[+] Kitap basariyla ID " << hedefID << " oncesine eklendi.\n";
                yigin.push("[Modul 1] ID " + std::to_string(hedefID) + " oncesine eklendi -> ID " +
                           std::to_string(k.kitapID));
            } else {
                std::cout << "[HATA] " << hata << "\n";
            }
        } else if (secim == 4) {
            if (katalog.bosMu()) {
                std::cout << "[UYARI] Katalog zaten bos, silinecek kitap yok.\n";
                continue;
            }
            int silID = tamSayiOku("Silinecek Kitap ID: ", 1, 99999);
            Kitap silinen;
            if (katalog.idIleSil(silID, silinen)) {
                std::cout << "[-] Kitap silindi: ID " << silinen.kitapID << " - " << silinen.kitapAdi << "\n";
                yigin.push("[Modul 1] Kitap silindi -> ID " + std::to_string(silinen.kitapID) + ": " + silinen.kitapAdi);
            } else {
                std::cout << "[HATA] ID " << silID << " katalogda bulunamadi!\n";
            }
        } else if (secim == 5) {
            katalog.ileriListele();
        } else if (secim == 6) {
            katalog.geriListele();
        } else if (secim == 7) {
            if (katalog.bosMu()) {
                katalog.analizEt(0);
            } else {
                int esik = tamSayiOku("Filtrelenecek minimum sayfa esigi (orn. 300): ", 0, 10000);
                katalog.analizEt(esik);
            }
        } else if (secim == 8) {
            std::cout << "\n  1. Duyuru Panosunu Tam Tur Listele\n";
            std::cout << "  2. Yeni Duyuru Ekle\n";
            int alt = tamSayiOku("  Seciminiz (1-2): ", 1, 2);
            if (alt == 1) {
                pano.tamTurListele();
            } else {
                std::string metin = metinOku("Yeni Duyuru Metni: ");
                pano.ekle(metin);
                std::cout << "[+] Duyuru dairesel listeye eklendi.\n";
                yigin.push("[Modul 1] Duyuru eklendi -> " + metin);
                pano.tamTurListele();
            }
        } else if (secim == 9) {
            if (katalog.dosyayaYaz(dosyaAdi)) {
                std::cout << "[+] Katalog '" << dosyaAdi << "' dosyasina ayirac ('|') ile yazildi.\n";
                if (!katalog.dosyadanOkuVeGoster(dosyaAdi)) {
                    std::cout << "[HATA] Dosya okuma sirasinda hata olustu.\n";
                } else {
                    yigin.push("[Modul 1] Katalog dosyaya yazildi ve okundu: " + dosyaAdi);
                }
            } else {
                std::cout << "[HATA] '" << dosyaAdi << "' dosyasi yazilamadi.\n";
            }
        }
    } while (secim != 0);
}
