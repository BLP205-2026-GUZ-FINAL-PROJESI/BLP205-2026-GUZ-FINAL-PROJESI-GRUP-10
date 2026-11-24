// ortak.h
// Tum modullerin ortak kullandigi Kitap yapisi ve yardimci fonksiyonlar.
// NOT: Bu dosya Kaan (Modul 1) ile birlikte kesinlestirilmelidir.

#ifndef ORTAK_H
#define ORTAK_H

#include <iostream>
#include <string>

// Bir kitap kaydi: ID, ad, yazar ve sayfa sayisi
struct Kitap {
    int id;
    std::string ad;
    std::string yazar;
    int sayfa;
};

// Tek bir kitap bilgisini ekrana yazdirir
inline void kitapYazdir(const Kitap& k) {
    std::cout << "ID: " << k.id
              << " | Ad: " << k.ad
              << " | Yazar: " << k.yazar
              << " | Sayfa: " << k.sayfa << "\n";
}

// Bir kitap dizisini ekrana yazdirir
inline void kitapDizisiYazdir(const Kitap dizi[], int n) {
    if (n == 0) {
        std::cout << "[BILGI] Listelenecek kitap yok.\n";
        return;
    }
    for (int i = 0; i < n; i++) {
        kitapYazdir(dizi[i]);
    }
}

#endif