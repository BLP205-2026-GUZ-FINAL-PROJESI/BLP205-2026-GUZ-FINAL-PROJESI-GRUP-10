// modul3.h
// Modul 3 - Siralama ve Arama Algoritmalari (dizi uzerinde)
// Sorumlu: Umut (2. ogrenci)
//
// Kullanim notu: Bagli listedeki kitaplar once bir diziye aktarilmalidir.
// Binary Search, dizinin ID'ye gore sirali olmasini gerektirir.

#ifndef MODUL3_H
#define MODUL3_H

#include <iostream>
#include <string>
#include "ortak.h"

// Siralama islemlerinin sayaclari (raporlama icin)
struct SiralamaSayaci {
    long long karsilastirma;  // iki eleman karsilastirma sayisi
    long long takas;          // Bubble ve Quick Sort icin takas sayisi
    long long kaydirma;       // Insertion Sort icin kaydirma sayisi

    SiralamaSayaci() : karsilastirma(0), takas(0), kaydirma(0) {}

    void sifirla() {
        karsilastirma = 0;
        takas = 0;
        kaydirma = 0;
    }

    void raporYazdir(const std::string& algoritmaAdi) const {
        std::cout << "[RAPOR] " << algoritmaAdi << "\n"
                  << "  Karsilastirma: " << karsilastirma << "\n"
                  << "  Takas:         " << takas << "\n"
                  << "  Kaydirma:      " << kaydirma << "\n";
    }
};

// Iki kitap kaydinin yerini degistirir
inline void kitapTakasYap(Kitap& a, Kitap& b) {
    Kitap gecici = a;
    a = b;
    b = gecici;
}

// Dizinin sayfa sayisina gore kucukten buyuge sirali olup olmadigini kontrol eder
inline bool sayfayaGoreSirali(const Kitap dizi[], int n) {
    for (int i = 0; i + 1 < n; i++) {
        if (dizi[i].sayfa > dizi[i + 1].sayfa) {
            return false;
        }
    }
    return true;
}

// Dizinin ID'ye gore kucukten buyuge sirali olup olmadigini kontrol eder
inline bool idYeGoreSirali(const Kitap dizi[], int n) {
    for (int i = 0; i + 1 < n; i++) {
        if (dizi[i].id > dizi[i + 1].id) {
            return false;
        }
    }
    return true;
}

// -------------------------------------------------------------------
// Bubble Sort: kitaplari sayfa sayisina gore siralar
// Her gecislde en buyuk eleman sona tasinir. Hic takas olmazsa erken durur.
// Zaman karmasikligi: en kotu O(n^2), en iyi O(n)
// -------------------------------------------------------------------
inline void bubbleSortSayfa(Kitap dizi[], int n, SiralamaSayaci& s) {
    for (int i = 0; i < n - 1; i++) {
        bool takasYapildi = false;
        for (int j = 0; j < n - 1 - i; j++) {
            s.karsilastirma++;
            if (dizi[j].sayfa > dizi[j + 1].sayfa) {
                kitapTakasYap(dizi[j], dizi[j + 1]);
                s.takas++;
                takasYapildi = true;
            }
        }
        if (!takasYapildi) {
            break;  // dizi zaten sirali
        }
    }
}

// -------------------------------------------------------------------
// Insertion Sort: kitaplari sayfa sayisina gore siralar
// Her elemani, solundaki sirali bolumde dogru yere kaydirarak yerlestirir.
// Zaman karmasikligi: en kotu O(n^2), en iyi O(n)
// -------------------------------------------------------------------
inline void insertionSortSayfa(Kitap dizi[], int n, SiralamaSayaci& s) {
    for (int i = 1; i < n; i++) {
        Kitap anahtar = dizi[i];
        int j = i - 1;

        while (j >= 0) {
            s.karsilastirma++;
            if (dizi[j].sayfa <= anahtar.sayfa) {
                break;  // anahtarin yeri bulundu
            }
            dizi[j + 1] = dizi[j];  // elemani saga kaydir
            s.kaydirma++;
            j--;
        }
        dizi[j + 1] = anahtar;
    }
}

// -------------------------------------------------------------------
// Quick Sort (ID'ye gore). Lomuto bolumleme semasi: son eleman pivot.
// Zaman karmasikligi: ortalama O(n log n), en kotu O(n^2)
// -------------------------------------------------------------------

// Dizinin [sol, sag] araligini pivota gore boler, pivotun son yerini dondurur
inline int bolumle(Kitap dizi[], int sol, int sag, SiralamaSayaci& s) {
    int pivot = dizi[sag].id;
    int i = sol - 1;  // pivottan kucuk elemanlarin son indeksi

    for (int j = sol; j < sag; j++) {
        s.karsilastirma++;
        if (dizi[j].id < pivot) {
            i++;
            if (i != j) {
                kitapTakasYap(dizi[i], dizi[j]);
                s.takas++;
            }
        }
    }

    // Pivotu dogru yerine koy
    if (i + 1 != sag) {
        kitapTakasYap(dizi[i + 1], dizi[sag]);
        s.takas++;
    }
    return i + 1;
}

// Quick Sort'un ozyinelemeli kismi
inline void hizliSiralaOzyineli(Kitap dizi[], int sol, int sag, SiralamaSayaci& s) {
    if (sol < sag) {
        int pivotIndeksi = bolumle(dizi, sol, sag, s);
        hizliSiralaOzyineli(dizi, sol, pivotIndeksi - 1, s);
        hizliSiralaOzyineli(dizi, pivotIndeksi + 1, sag, s);
    }
}

// Disariya acik Quick Sort fonksiyonu
inline void quickSortId(Kitap dizi[], int n, SiralamaSayaci& s) {
    if (n > 1) {
        hizliSiralaOzyineli(dizi, 0, n - 1, s);
    }
}

// -------------------------------------------------------------------
// Binary Search (ID'ye gore). Dizi ID'ye gore sirali olmalidir.
// Bulunursa dizideki indeksi, bulunamazsa -1 dondurur.
// adimSayisi: kac adimda karar verildigini raporlar.
// Zaman karmasikligi: O(log n)
// -------------------------------------------------------------------
inline int binarySearchId(const Kitap dizi[], int n, int aranan, int& adimSayisi) {
    adimSayisi = 0;
    int sol = 0;
    int sag = n - 1;

    while (sol <= sag) {
        adimSayisi++;
        int orta = sol + (sag - sol) / 2;

        if (dizi[orta].id == aranan) {
            return orta;
        }
        if (dizi[orta].id < aranan) {
            sol = orta + 1;   // aranan sag yarida
        } else {
            sag = orta - 1;   // aranan sol yarida
        }
    }
    return -1;  // bulunamadi
}

#endif