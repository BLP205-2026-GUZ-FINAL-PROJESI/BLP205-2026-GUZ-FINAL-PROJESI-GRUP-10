#ifndef MODUL3_H
#define MODUL3_H

#include "modul1.h"
#include "ortak.h"
#include <string>

// Siralama algoritmalarinin performans metrikleri
struct SiralamaIstatistik {
    long long karsilastirmaSayisi;
    long long islemSayisi; // Bubble ve Quick Sort icin takas, Insertion Sort icin kaydirma
};

// Sayfa sayisina gore kucukten buyuge Bubble Sort
SiralamaIstatistik bubbleSortSayfa(Kitap* dizi, int n);

// Sayfa sayisina gore kucukten buyuge Insertion Sort
SiralamaIstatistik insertionSortSayfa(Kitap* dizi, int n);

// Kitap ID degerine gore kucukten buyuge Quick Sort
void quickSortID(Kitap* dizi, int sol, int sag, long long& karsilastirma, long long& takas);

// ID'ye gore sirali dizide Ikili Arama (Binary Search)
int binarySearchID(const Kitap* dizi, int n, int arananID, int& adimSayisi);

// Dizi kopyalama yardimcisi
Kitap* diziKopyala(const Kitap* kaynak, int n);

// Dizi yazdirma yardimcisi
void kitapDizisiYazdir(const Kitap* dizi, int n, const std::string& baslik);

// Modul 3 alt menusu
void modul3Menu(const KitapKatalogu& katalog);

#endif
