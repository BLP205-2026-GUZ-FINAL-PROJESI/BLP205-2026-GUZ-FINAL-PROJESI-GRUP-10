#include "modul3.h"
#include <iomanip>
#include <iostream>

using namespace std;

namespace {
void kitapTakas(Kitap& a, Kitap& b) {
    Kitap gecici = a;
    a = b;
    b = gecici;
}

int partitionID(Kitap* dizi, int sol, int sag, long long& karsilastirma, long long& takas) {
    int pivotID = dizi[sag].kitapID;
    int i = sol - 1;

    for (int j = sol; j < sag; ++j) {
        ++karsilastirma;
        if (dizi[j].kitapID <= pivotID) {
            ++i;
            if (i != j) {
                kitapTakas(dizi[i], dizi[j]);
                ++takas;
            }
        }
    }
    if (i + 1 != sag) {
        kitapTakas(dizi[i + 1], dizi[sag]);
        ++takas;
    }
    return i + 1;
}
} // namespace

Kitap* diziKopyala(const Kitap* kaynak, int n) {
    if (kaynak == nullptr || n <= 0) {
        return nullptr;
    }
    Kitap* kopya = new Kitap[n];
    for (int i = 0; i < n; ++i) {
        kopya[i] = kaynak[i];
    }
    return kopya;
}

void kitapDizisiYazdir(const Kitap* dizi, int n, const string& baslik) {
    cout << "\n--- " << baslik << " (Toplam: " << n << ") ---\n";
    for (int i = 0; i < n; ++i) {
        cout << " [" << setw(2) << (i + 1) << "] ID: " << setw(4) << dizi[i].kitapID
                  << " | Kitap: " << left << setw(26) << dizi[i].kitapAdi
                  << " | Yazar: " << setw(18) << dizi[i].yazarAdi
                  << " | Sayfa: " << right << setw(4) << dizi[i].sayfaSayisi << "\n";
    }
}

SiralamaIstatistik bubbleSortSayfa(Kitap* dizi, int n) {
    SiralamaIstatistik istatistik = {0, 0};
    for (int i = 0; i < n - 1; ++i) {
        bool takasOldu = false;
        for (int j = 0; j < n - 1 - i; ++j) {
            ++istatistik.karsilastirmaSayisi;
            if (dizi[j].sayfaSayisi > dizi[j + 1].sayfaSayisi) {
                kitapTakas(dizi[j], dizi[j + 1]);
                ++istatistik.islemSayisi;
                takasOldu = true;
            }
        }
        if (!takasOldu) {
            break;
        }
    }
    return istatistik;
}

SiralamaIstatistik insertionSortSayfa(Kitap* dizi, int n) {
    SiralamaIstatistik istatistik = {0, 0};
    for (int i = 1; i < n; ++i) {
        Kitap anahtar = dizi[i];
        int j = i - 1;
        while (j >= 0) {
            ++istatistik.karsilastirmaSayisi;
            if (dizi[j].sayfaSayisi > anahtar.sayfaSayisi) {
                dizi[j + 1] = dizi[j];
                ++istatistik.islemSayisi;
                --j;
            } else {
                break;
            }
        }
        dizi[j + 1] = anahtar;
    }
    return istatistik;
}

void quickSortID(Kitap* dizi, int sol, int sag, long long& karsilastirma, long long& takas) {
    if (sol < sag) {
        int pivotIndeks = partitionID(dizi, sol, sag, karsilastirma, takas);
        quickSortID(dizi, sol, pivotIndeks - 1, karsilastirma, takas);
        quickSortID(dizi, pivotIndeks + 1, sag, karsilastirma, takas);
    }
}

int binarySearchID(const Kitap* dizi, int n, int arananID, int& adimSayisi) {
    adimSayisi = 0;
    int sol = 0;
    int sag = n - 1;

    while (sol <= sag) {
        ++adimSayisi;
        int orta = sol + (sag - sol) / 2;
        if (dizi[orta].kitapID == arananID) {
            return orta;
        } else if (dizi[orta].kitapID < arananID) {
            sol = orta + 1;
        } else {
            sag = orta - 1;
        }
    }
    return -1;
}

void modul3Menu(const KitapKatalogu& katalog) {
    int secim;
    do {
        cout << "\n--- [MODUL 3: SIRALAMA VE ARAMA ALGORITMALARI] ---\n";
        cout << "1. Bubble Sort vs Insertion Sort (Sayfa Sayisina Gore Karsilastirma)\n";
        cout << "2. Quick Sort (ID'ye Gore) ve Binary Search (Ikili Arama)\n";
        cout << "0. Ana Menuye Don\n";

        secim = tamSayiOku("Alt Seciminiz: ", 0, 2);
        if (secim == 0) {
            break;
        }

        Kitap* anaDizi = nullptr;
        int boyut = 0;
        if (!katalog.diziyeAktar(anaDizi, boyut)) {
            cout << "[UYARI] Kitap katalogu bos! Siralama ve arama icin once Modul 1'den kitap ekleyiniz.\n";
            continue;
        }

        if (secim == 1) {
            Kitap* bubbleDizi = diziKopyala(anaDizi, boyut);
            Kitap* insertionDizi = diziKopyala(anaDizi, boyut);

            SiralamaIstatistik bubbleSonuc = bubbleSortSayfa(bubbleDizi, boyut);
            SiralamaIstatistik insertionSonuc = insertionSortSayfa(insertionDizi, boyut);

            kitapDizisiYazdir(bubbleDizi, boyut, "SAYFA SAYISINA GORE SIRALI KATALOG (Bubble Sort)");
            cout << "\n[RAPOR] Bubble Sort    -> Karsilastirma: " << bubbleSonuc.karsilastirmaSayisi
                      << " | Takas (Swap): " << bubbleSonuc.islemSayisi << "\n";

            kitapDizisiYazdir(insertionDizi, boyut, "SAYFA SAYISINA GORE SIRALI KATALOG (Insertion Sort)");
            cout << "\n[RAPOR] Insertion Sort -> Karsilastirma: " << insertionSonuc.karsilastirmaSayisi
                      << " | Kaydirma (Shift): " << insertionSonuc.islemSayisi << "\n";

            delete[] bubbleDizi;
            delete[] insertionDizi;
        } else if (secim == 2) {
            long long karsilastirma = 0;
            long long takas = 0;
            quickSortID(anaDizi, 0, boyut - 1, karsilastirma, takas);

            kitapDizisiYazdir(anaDizi, boyut, "KITAP ID'YE GORE SIRALI KATALOG (Quick Sort)");
            cout << "\n[RAPOR] Quick Sort -> Karsilastirma: " << karsilastirma
                      << " | Takas (Swap): " << takas << "\n";

            int arananID = tamSayiOku("\nBinary Search ile aranacak Kitap ID: ", 1, 99999);
            int adimSayisi = 0;
            int bulunanIndeks = binarySearchID(anaDizi, boyut, arananID, adimSayisi);

            if (bulunanIndeks != -1) {
                cout << "[BULUNDU] Kitap ID " << arananID
                          << " -> Indeks: " << bulunanIndeks
                          << " | Adim Sayisi: " << adimSayisi << "\n";
                cout << "  Detay -> Kitap: " << anaDizi[bulunanIndeks].kitapAdi
                          << " | Yazar: " << anaDizi[bulunanIndeks].yazarAdi
                          << " | Sayfa: " << anaDizi[bulunanIndeks].sayfaSayisi << "\n";
            } else {
                cout << "[BULUNAMADI] Kitap ID " << arananID
                          << " katalogda mevcut degil. (Toplam Arama Adimi: " << adimSayisi << ")\n";
            }
        }

        delete[] anaDizi;
    } while (secim != 0);
}
