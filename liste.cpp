#include "liste.h"
#include <iostream>

KitapListesi::KitapListesi() : bas(nullptr), son(nullptr) {}

KitapListesi::~KitapListesi() {
    // Tüm düğümleri delete et
    KitapDugumu* aktif = bas;
    while (aktif != nullptr) {
        KitapDugumu* sonrakiDugum = aktif->sonraki;
        delete aktif;
        aktif = sonrakiDugum;
    }
}

void KitapListesi::basaEkle(const Kitap& k) {
    KitapDugumu* yeni = new KitapDugumu{k, nullptr, bas};
    if (bas != nullptr) {
        bas->onceki = yeni;
    } else {
        son = yeni;
    }
    bas = yeni;
}

void KitapListesi::sonaEkle(const Kitap& k) {
    KitapDugumu* yeni = new KitapDugumu{k, son, nullptr};
    if (son != nullptr) {
        son->sonraki = yeni;
    } else {
        bas = yeni;
    }
    son = yeni;
}

void KitapListesi::ileriListele() const {
    if (bas == nullptr) {
        std::cout << "Kitap listesi bos.\n";
        return;
    }
    for (KitapDugumu* p = bas; p != nullptr; p = p->sonraki) {
        std::cout << p->veri.kitapId << " - " << p->veri.kitapAdi
                  << " (" << p->veri.yazarAdi << ", " << p->veri.sayfaSayisi << " sayfa)\n";
    }
}

void KitapListesi::geriListele() const {
    if (son == nullptr) {
        std::cout << "Kitap listesi bos.\n";
        return;
    }
    for (KitapDugumu* p = son; p != nullptr; p = p->onceki) {
        std::cout << p->veri.kitapId << " - " << p->veri.kitapAdi
                  << " (" << p->veri.yazarAdi << ", " << p->veri.sayfaSayisi << " sayfa)\n";
    }
}