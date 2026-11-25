#ifndef LISTE_H
#define LISTE_H

#include "kitap.h"

// Çift yönlü bağlı liste düğümü
struct KitapDugumu {
    Kitap veri;
    KitapDugumu* onceki;
    KitapDugumu* sonraki;
};

// Çift yönlü bağlı liste sınıfı
class KitapListesi {
public:
    KitapListesi();
    ~KitapListesi();

    void basaEkle(const Kitap& k);
    void sonaEkle(const Kitap& k);
    void ileriListele() const;
    void geriListele() const;

private:
    KitapDugumu* bas;
    KitapDugumu* son;
};

#endif