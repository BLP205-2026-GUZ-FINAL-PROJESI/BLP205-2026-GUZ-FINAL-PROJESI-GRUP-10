#ifndef ORTAK_H
#define ORTAK_H

#include <string>

// Kitap kaydi icin temel veri yapisi (Modul 1 ve Modul 3 tarafindan ortak kullanilir)
struct Kitap {
    int kitapID;
    std::string kitapAdi;
    std::string yazarAdi;
    int sayfaSayisi;
};

// Kullanicidan guvenli sekilde tam sayi okur (minDeger - maxDeger araliginda)
int tamSayiOku(const std::string& mesaj, int minDeger, int maxDeger);

// Kullanicidan bos olmayan ve '|' ayiracini icermeyen metin okur
std::string metinOku(const std::string& mesaj);

// Dosya ayiraci olan '|' karakterini guvenli sekilde temizler
std::string ayiracTemizle(const std::string& metin);

#endif
