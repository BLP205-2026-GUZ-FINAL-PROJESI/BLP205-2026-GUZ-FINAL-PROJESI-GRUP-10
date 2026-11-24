// test_modul2_3.cpp
// Modul 2 ve Modul 3 icin birim testleri.
// Derleme: g++ -std=c++11 -Wall -Wextra test_modul2_3.cpp -o test_modul2_3

#include <cassert>
#include <iostream>
#include <string>
#include "ortak.h"
#include "modul2.h"
#include "modul3.h"

// -------------------- Yigin testleri --------------------
void testYigin() {
    std::cout << "--- Yigin testi ---\n";
    IslemYigini yigin;
    std::string deger;

    // Bos yigin: pop ve peek basarisiz olmali
    assert(yigin.bos());
    assert(!yigin.pop(deger));
    assert(!yigin.peek(deger));

    yigin.push("Kitap ekle");
    yigin.push("Kitap sil");
    yigin.listele();

    assert(yigin.peek(deger) && deger == "Kitap sil");   // peek en ustu gosterir
    assert(yigin.elemanSayisi() == 2);                   // peek cikarmaz

    assert(yigin.pop(deger) && deger == "Kitap sil");    // LIFO
    assert(yigin.pop(deger) && deger == "Kitap ekle");
    assert(yigin.bos());
    std::cout << "[OK] Yigin testleri gecti\n\n";
}

// -------------------- Kuyruk testleri --------------------
void testKuyruk() {
    std::cout << "--- Kuyruk testi ---\n";
    OduncKuyrugu kuyruk;
    OgrenciKaydi cikan;

    // Bos kuyruk: dequeue basarisiz olmali
    assert(!kuyruk.dequeue(cikan));
    kuyruk.listele();

    OgrenciKaydi a = {1001, "Ali Yilmaz", 102, "Sefiller"};
    OgrenciKaydi b = {1002, "Ayse Demir", 105, "Suc ve Ceza"};
    OgrenciKaydi c = {1003, "Mehmet Kaya", 110, "Kurk Mantolu Madonna"};
    kuyruk.enqueue(a);
    kuyruk.enqueue(b);
    kuyruk.enqueue(c);
    kuyruk.listele();

    // FIFO: ilk giren ilk cikar
    assert(kuyruk.dequeue(cikan) && cikan.ogrenciNo == 1001);
    assert(kuyruk.dequeue(cikan) && cikan.ogrenciNo == 1002);
    assert(kuyruk.elemanSayisi() == 1);

    // Son dugum silindiginde son da sifirlanmali; yeni eklemeler dogru calismali
    assert(kuyruk.dequeue(cikan) && cikan.ogrenciNo == 1003);
    assert(kuyruk.bos());
    kuyruk.enqueue(a);
    assert(kuyruk.dequeue(cikan) && cikan.ogrenciNo == 1001);
    std::cout << "[OK] Kuyruk testleri gecti\n\n";
}

// -------------------- Siralama ve arama testleri --------------------
void testSiralamaVeArama() {
    std::cout << "--- Siralama ve arama testi ---\n";

    // Ayni veri uc farkli siralama icin kopyalanir
    Kitap ornek[] = {
        {105, "Suc ve Ceza", "Dostoyevski", 671},
        {101, "Kucuk Prens", "Saint-Exupery", 96},
        {110, "Madonna", "Ahmet", 320},
        {102, "Sefiller", "Hugo", 1463},
        {120, "Simyaci", "Coelho", 208}
    };
    const int n = sizeof(ornek) / sizeof(ornek[0]);

    // Bubble Sort (sayfa)
    Kitap bubble[n];
    for (int i = 0; i < n; i++) bubble[i] = ornek[i];
    SiralamaSayaci sBubble;
    bubbleSortSayfa(bubble, n, sBubble);
    assert(sayfayaGoreSirali(bubble, n));
    sBubble.raporYazdir("Bubble Sort (sayfa)");

    // Insertion Sort (sayfa)
    Kitap insertion[n];
    for (int i = 0; i < n; i++) insertion[i] = ornek[i];
    SiralamaSayaci sInsertion;
    insertionSortSayfa(insertion, n, sInsertion);
    assert(sayfayaGoreSirali(insertion, n));
    sInsertion.raporYazdir("Insertion Sort (sayfa)");

    // Quick Sort (ID)
    Kitap quick[n];
    for (int i = 0; i < n; i++) quick[i] = ornek[i];
    SiralamaSayaci sQuick;
    quickSortId(quick, n, sQuick);
    assert(idYeGoreSirali(quick, n));
    sQuick.raporYazdir("Quick Sort (ID)");

    std::cout << "\nID'ye gore sirali liste:\n";
    kitapDizisiYazdir(quick, n);

    // Binary Search: bulunan ID
    int adim = 0;
    int idx = binarySearchId(quick, n, 105, adim);
    assert(idx != -1 && quick[idx].id == 105);
    std::cout << "\n[OK] ID 105 bulundu, indeks " << idx << ", adim " << adim << "\n";

    // Binary Search: bulunamayan ID
    idx = binarySearchId(quick, n, 999, adim);
    assert(idx == -1);
    std::cout << "[OK] ID 999 bulunamadi, adim " << adim << "\n";

    // Bos dizi
    idx = binarySearchId(quick, 0, 105, adim);
    assert(idx == -1);
    std::cout << "[OK] Bos dizide arama dogru calisti\n\n";

    std::cout << "[OK] Siralama ve arama testleri gecti\n\n";
}

int main() {
    testYigin();
    testKuyruk();
    testSiralamaVeArama();
    std::cout << "=== Tum Modul 2 ve Modul 3 testleri basarili ===\n";
    return 0;
}