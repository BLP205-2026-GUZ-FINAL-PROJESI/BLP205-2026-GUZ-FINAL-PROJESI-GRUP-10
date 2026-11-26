#ifndef MODUL1_H
#define MODUL1_H

#include "ortak.h"
#include "modul2.h"
#include <string>

// Cift yonlu dogrusal bagli liste dugumu (Kitap Katalogu)
struct KitapDugum {
    Kitap veri;
    KitapDugum* prev;
    KitapDugum* next;
};

// Kitap katalogunu yoneten cift yonlu dogrusal bagli liste sinifi
class KitapKatalogu {
private:
    KitapDugum* head;
    KitapDugum* tail;
    int elemanSayisi;

public:
    KitapKatalogu();
    ~KitapKatalogu();

    bool bosMu() const;
    int boyut() const;
    bool idVarMi(int id) const;

    bool basaEkle(const Kitap& kitap);
    bool sonaEkle(const Kitap& kitap);
    bool hedefOnuneEkle(int hedefID, const Kitap& kitap, std::string& hataMesaji);
    bool idIleSil(int id, Kitap& silinen);

    void ileriListele() const;
    void geriListele() const;
    void analizEt(int sayfaEsigi) const;

    bool dosyayaYaz(const std::string& dosyaAdi) const;
    bool dosyadanOkuVeGoster(const std::string& dosyaAdi) const;

    // Modul 3 icin bagli listedeki kitaplari dinamik diziye aktarir
    bool diziyeAktar(Kitap*& dizi, int& boyut) const;

    int temizle();
};

// Tek yonlu dairesel bagli liste dugumu (Duyuru Panosu)
struct DuyuruDugum {
    int duyuruID;
    std::string metin;
    DuyuruDugum* next;
};

// Duyuru panosunu yoneten tek yonlu dairesel bagli liste sinifi
class DuyuruPanosu {
private:
    DuyuruDugum* head;
    int elemanSayisi;
    int sonrakiID;

public:
    DuyuruPanosu();
    ~DuyuruPanosu();

    bool bosMu() const;
    int boyut() const;
    void ekle(const std::string& metin);
    void tamTurListele() const;
    int temizle();
};

// Modul 1 alt menusu
void modul1Menu(KitapKatalogu& katalog, DuyuruPanosu& pano, IslemYigini& yigin);

#endif
