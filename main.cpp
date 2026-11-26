#include "modul1.h"
#include "modul2.h"
#include "modul3.h"
#include "modul4.h"
#include "ortak.h"
#include <iostream>

namespace {
void ornekVerileriYukle(KitapKatalogu& katalog,
                        DuyuruPanosu& pano,
                        IslemYigini& yigin,
                        OduncKuyrugu& kuyruk,
                        KampusGraf& graf) {
    // Modul 1: Karisik ID ve sayfa sayilariyla ornek kitaplar
    katalog.sonaEkle({105, "Veri Yapilari ve Algoritmalar", "Ahmet Yilmaz", 420});
    katalog.sonaEkle({102, "C++ Programlama Sanati", "Mehmet Demir", 560});
    katalog.sonaEkle({108, "Isletim Sistemleri", "Ayse Kaya", 310});
    katalog.sonaEkle({101, "Algoritma Analizi", "Can Ozturk", 245});
    katalog.sonaEkle({104, "Veritabani Yonetimi", "Zeynep Ak", 380});
    katalog.sonaEkle({103, "Bilgisayar Aglari", "Emre Sahin", 490});

    // Modul 1: Dairesel liste ornek duyurular
    pano.ekle("Kutuphane vize haftasinda 24 saat acik kalacaktir.");
    pano.ekle("Yeni Veri Yapilari kaynaklari B blok rafina eklendi.");
    pano.ekle("Odunc kitap iade suresi 15 gun olarak guncellendi.");

    // Modul 2: Yigin (Stack) ve Kuyruk (Queue) ornek kayitlari
    yigin.push("[Sistem] Kutuphane otomasyonu baslatildi.");
    yigin.push("[Modul 1] Ornek kitap katalogu bellege yuklendi.");
    yigin.push("[Modul 2] Ornek odunc kuyrugu hazirlandi.");

    kuyruk.enqueue("20241001", "Ali Veli", "Algoritma Analizi");
    kuyruk.enqueue("20241002", "Elif Yildiz", "C++ Programlama Sanati");
    kuyruk.enqueue("20241003", "Burak Celik", "Veri Yapilari ve Algoritmalar");

    // Modul 4: 6 kampus birimi arasi yurume mesafeleri (metre)
    graf.kenarEkle(0, 1, 120); // Merkez Kutuphane <-> MYO Bilgisayar Lab
    graf.kenarEkle(0, 2, 250); // Merkez Kutuphane <-> Muhendislik Binasi
    graf.kenarEkle(0, 3, 180); // Merkez Kutuphane <-> Ogrenci Isleri
    graf.kenarEkle(1, 2, 100); // MYO Bilgisayar Lab <-> Muhendislik Binasi
    graf.kenarEkle(1, 4, 200); // MYO Bilgisayar Lab <-> Yemekhane
    graf.kenarEkle(2, 4, 160); // Muhendislik Binasi <-> Yemekhane
    graf.kenarEkle(2, 5, 220); // Muhendislik Binasi <-> Konferans Salonu
    graf.kenarEkle(3, 4, 130); // Ogrenci Isleri <-> Yemekhane
    graf.kenarEkle(4, 5, 110); // Yemekhane <-> Konferans Salonu
}

void hizliTamDemo(const KampusGraf& graf) {
    std::cout << "\n=============================================================\n";
    std::cout << "HIZLI TAM DEMO: TUM MODULLER VE SINIR DURUMLARI TEST EDILIYOR\n";
    std::cout << "=============================================================\n";

    // 1. Bos veri yapilari kontrolu (sinir durumu)
    std::cout << "\n[DEMO 0] Bos Veri Yapilari Sinir Durumu Kontrolu:\n";
    KitapKatalogu bosKatalog;
    DuyuruPanosu bosPano;
    IslemYigini bosYigin;
    OduncKuyrugu bosKuyruk;
    bosKatalog.ileriListele();
    bosKatalog.analizEt(300);
    bosPano.tamTurListele();
    bosYigin.listele();
    bosKuyruk.listele();

    // 2. Modul 1 Demo (izole demo katalogu ile mevcut veriyi bozmadan)
    std::cout << "\n[DEMO 1] MODUL 1 - Bagli Listeler ve Dosya Islemleri:\n";
    KitapKatalogu demoKatalog;
    demoKatalog.sonaEkle({202, "Sistem Programlama", "Ali Kaya", 350});
    demoKatalog.basaEkle({201, "C++ Temelleri", "Veli Can", 220});
    demoKatalog.sonaEkle({204, "Yapay Zeka Giris", "Ayse Nur", 510});

    std::string hata;
    demoKatalog.hedefOnuneEkle(204, {203, "Veri Tabani", "Deniz Ak", 410}, hata);
    demoKatalog.ileriListele();
    demoKatalog.geriListele();

    Kitap silinen;
    if (demoKatalog.idIleSil(203, silinen)) {
        std::cout << "[-] Demo silinen kitap: ID " << silinen.kitapID << " - " << silinen.kitapAdi << "\n";
    }
    demoKatalog.analizEt(300);

    DuyuruPanosu demoPano;
    demoPano.ekle("Demo Duyuru 1: Sinav takvimi aciklandi.");
    demoPano.ekle("Demo Duyuru 2: Kutuphane saatleri guncellendi.");
    demoPano.tamTurListele();

    demoKatalog.dosyayaYaz("demo_katalog.txt");
    demoKatalog.dosyadanOkuVeGoster("demo_katalog.txt");

    // 3. Modul 2 Demo
    std::cout << "\n[DEMO 2] MODUL 2 - Yigin (Stack) ve Kuyruk (Queue):\n";
    OduncKuyrugu demoKuyruk;
    demoKuyruk.enqueue("20249001", "Selin Demir", "C++ Temelleri");
    demoKuyruk.enqueue("20249002", "Mert Yilmaz", "Yapay Zeka Giris");
    demoKuyruk.listele();

    std::string ogrNo, adSoyad, kitap;
    if (demoKuyruk.dequeue(ogrNo, adSoyad, kitap)) {
        std::cout << "[+] FIFO hizmet verildi -> " << ogrNo << " | " << adSoyad << "\n";
    }
    demoKuyruk.listele();

    IslemYigini demoYigin;
    demoYigin.push("Demo Islem 1: Katalog olusturuldu");
    demoYigin.push("Demo Islem 2: Kuyruga ogrenci eklendi");
    demoYigin.listele();
    std::string ust;
    if (demoYigin.peek(ust)) {
        std::cout << "[PEEK] En ustteki islem: " << ust << "\n";
    }
    std::string cikan;
    if (demoYigin.pop(cikan)) {
        std::cout << "[POP] Yigindan cikarildi: " << cikan << "\n";
    }

    // 4. Modul 3 Demo
    std::cout << "\n[DEMO 3] MODUL 3 - Siralama ve Ikili Arama:\n";
    Kitap* dizi = nullptr;
    int boyut = 0;
    if (demoKatalog.diziyeAktar(dizi, boyut)) {
        Kitap* bDizi = diziKopyala(dizi, boyut);
        Kitap* iDizi = diziKopyala(dizi, boyut);

        SiralamaIstatistik bSonuc = bubbleSortSayfa(bDizi, boyut);
        SiralamaIstatistik iSonuc = insertionSortSayfa(iDizi, boyut);
        std::cout << "[Bubble Sort]    Karsilastirma: " << bSonuc.karsilastirmaSayisi
                  << " | Takas: " << bSonuc.islemSayisi << "\n";
        std::cout << "[Insertion Sort] Karsilastirma: " << iSonuc.karsilastirmaSayisi
                  << " | Kaydirma: " << iSonuc.islemSayisi << "\n";

        long long qKarsilastirma = 0;
        long long qTakas = 0;
        quickSortID(dizi, 0, boyut - 1, qKarsilastirma, qTakas);
        kitapDizisiYazdir(dizi, boyut, "DEMO QUICK SORT (ID'YE GORE)");
        std::cout << "[Quick Sort] Karsilastirma: " << qKarsilastirma << " | Takas: " << qTakas << "\n";

        int adim = 0;
        int idxVar = binarySearchID(dizi, boyut, 204, adim);
        std::cout << "[Binary Search - Mevcut ID 204] Indeks: " << idxVar << " | Adim: " << adim << "\n";

        int idxYok = binarySearchID(dizi, boyut, 999, adim);
        std::cout << "[Binary Search - Olmayan ID 999] Indeks: " << idxYok << " | Adim: " << adim << "\n";

        delete[] bDizi;
        delete[] iDizi;
        delete[] dizi;
    }

    // 5. Modul 4 Demo
    std::cout << "\n[DEMO 4] MODUL 4 - Graf, BFS, DFS ve Dijkstra:\n";
    graf.matrisiYazdir();
    graf.bfs(0);
    graf.dfs(0);
    graf.dijkstra(0, 5);

    std::cout << "\n[OK] Hizli Tam Demo basariyla tamamlandi ve demo bellegi temizlendi.\n";
}
} // namespace

int main() {
    KitapKatalogu katalog;
    DuyuruPanosu pano;
    IslemYigini yigin;
    OduncKuyrugu kuyruk;
    KampusGraf graf;

    ornekVerileriYukle(katalog, pano, yigin, kuyruk, graf);
    std::cout << "[OK] Tum moduller icin ornek veriler basariyla bellege yuklendi!\n";

    int secim;
    do {
        std::cout << "\n=============================================================\n";
        std::cout << "DOGUS UNIVERSITESI MYO - BLP 205 VERI YAPILARI FINAL PROJESI\n";
        std::cout << "KAMPUS KUTUPHANESI VE OGRENCI HIZMETLERI OTOMASYONU (C++)\n";
        std::cout << "=============================================================\n";
        std::cout << "[1] MODUL 1 (1. Ogrenci): Bagli Listeler (Cift Yonlu & Dairesel) ve Dosya\n";
        std::cout << "[2] MODUL 2 (2. Ogrenci): Yigin (Stack - Undo) ve Kuyruk (Queue - Sira)\n";
        std::cout << "[3] MODUL 3 (3. Ogrenci): Siralama ve Arama Algoritmalari\n";
        std::cout << "[4] MODUL 4 (4. Ogrenci): Graf (Graph - Matris, BFS, DFS, En Kisa Yol)\n";
        std::cout << "[5] HIZLI TAM DEMO: 4 Modulun Tum Fonksiyonlarini Sirayla Calistir\n";
        std::cout << "[0] Bellegi Temizle (delete) ve Cikis\n";

        secim = tamSayiOku("\nSeciminiz: ", 0, 5);

        if (secim == 1) {
            modul1Menu(katalog, pano, yigin);
        } else if (secim == 2) {
            modul2Menu(yigin, kuyruk);
        } else if (secim == 3) {
            modul3Menu(katalog);
        } else if (secim == 4) {
            modul4Menu(graf);
        } else if (secim == 5) {
            hizliTamDemo(graf);
        }
    } while (secim != 0);

    int silinenKitap = katalog.temizle();
    int silinenDuyuru = pano.temizle();
    int silinenYigin = yigin.temizle();
    int silinenKuyruk = kuyruk.temizle();

    std::cout << "\n[BELLEK TEMIZLIGI] Tum dinamik dugumler delete edildi:\n";
    std::cout << " - Kitap dugumleri  : " << silinenKitap << "\n";
    std::cout << " - Duyuru dugumleri : " << silinenDuyuru << "\n";
    std::cout << " - Yigin dugumleri  : " << silinenYigin << "\n";
    std::cout << " - Kuyruk dugumleri : " << silinenKuyruk << "\n";
    std::cout << "Program sonlandirildi. Iyi gunler!\n";

    return 0;
}
