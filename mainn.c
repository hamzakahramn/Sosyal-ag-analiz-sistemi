#include <stdio.h>
#include <stdlib.h>

// Agac dugum yapisi
typedef struct AgacDugum {
    int kullanici_id;
    struct AgacDugum** cocuklar;
    int cocuk_sayisi;
    int renk; // Kirmizi-siyah agac icin renk bilgisi (0: Siyah, 1: Kirmizi)
    struct AgacDugum* ebeveyn;
    struct AgacDugum* sol;
    struct AgacDugum* sag;
} AgacDugum;

// Sosyal ag agaci yapisi
typedef struct SosyalAgAgaci {
    AgacDugum** dugumler;
    int dugum_sayisi;
    AgacDugum* kok; // Kirmizi-siyah agacin koku
} SosyalAgAgaci;

// Yeni dugum olusturma
AgacDugum* yeniDugum(int kullanici_id) {
    AgacDugum* dugum = (AgacDugum*)malloc(sizeof(AgacDugum));
    dugum->kullanici_id = kullanici_id;
    dugum->cocuklar = NULL;
    dugum->cocuk_sayisi = 0;
    dugum->renk = 1; // Yeni dugum kirmizi olarak baslar
    dugum->ebeveyn = NULL;
    dugum->sol = NULL;
    dugum->sag = NULL;
    return dugum;
}

// Yeni sosyal ag agaci olusturma
SosyalAgAgaci* yeniSosyalAg() {
    SosyalAgAgaci* ag = (SosyalAgAgaci*)malloc(sizeof(SosyalAgAgaci));
    ag->dugumler = NULL;
    ag->dugum_sayisi = 0;
    ag->kok = NULL;
    return ag;
}

// Kullanici ekleme
void kullaniciEkle(SosyalAgAgaci* ag, int kullanici_id) {
    AgacDugum* yeni = yeniDugum(kullanici_id);
    ag->dugum_sayisi++;
    ag->dugumler = (AgacDugum**)realloc(ag->dugumler, ag->dugum_sayisi * sizeof(AgacDugum*));
    ag->dugumler[ag->dugum_sayisi - 1] = yeni;
}

// Iliski ekleme
void iliskiEkleAgac(SosyalAgAgaci* ag, int kullanici_id1, int kullanici_id2) {
    AgacDugum* dugum1 = NULL;
    AgacDugum* dugum2 = NULL;
    int i;
    for (i = 0; i < ag->dugum_sayisi; i++) {
        if (ag->dugumler[i]->kullanici_id == kullanici_id1) {
            dugum1 = ag->dugumler[i];
        }
        if (ag->dugumler[i]->kullanici_id == kullanici_id2) {
            dugum2 = ag->dugumler[i];
        }
    }
    if (dugum1 && dugum2) {
        dugum1->cocuk_sayisi++;
        dugum1->cocuklar = (AgacDugum**)realloc(dugum1->cocuklar, dugum1->cocuk_sayisi * sizeof(AgacDugum*));
        dugum1->cocuklar[dugum1->cocuk_sayisi - 1] = dugum2;
    }
}

// Derinlik ilk arama (DFS)
void derinlikIlkAramaYardimci(AgacDugum* dugum, int derinlik, int hedef_derinlik) {
    if (derinlik == hedef_derinlik) {
        printf("%d ", dugum->kullanici_id);
        return;
    }
    int i;
    for (i = 0; i < dugum->cocuk_sayisi; i++) {
        derinlikIlkAramaYardimci(dugum->cocuklar[i], derinlik + 1, hedef_derinlik);
    }
}

void derinlikIlkArama(SosyalAgAgaci* ag, int baslangic_id, int hedef_derinlik) {
    AgacDugum* baslangic_dugum = NULL;
    int i;
    for (i = 0; i < ag->dugum_sayisi; i++) {
        if (ag->dugumler[i]->kullanici_id == baslangic_id) {
            baslangic_dugum = ag->dugumler[i];
            break;
        }
    }
    if (baslangic_dugum) {
        derinlikIlkAramaYardimci(baslangic_dugum, 0, hedef_derinlik);
    }
}

// Topluluk tespiti icin DFS
void toplulukBulDFS(AgacDugum* dugum, int* ziyaret_edilenler, int* topluluk, int* indeks) {
    ziyaret_edilenler[dugum->kullanici_id] = 1;
    topluluk[*indeks] = dugum->kullanici_id;
    (*indeks)++;

    int i;
    for (i = 0; i < dugum->cocuk_sayisi; i++) {
        if (!ziyaret_edilenler[dugum->cocuklar[i]->kullanici_id]) {
            toplulukBulDFS(dugum->cocuklar[i], ziyaret_edilenler, topluluk, indeks);
        }
    }
}

void toplulukTespit(SosyalAgAgaci* ag) {
    int* ziyaret_edilenler = (int*)calloc(1000, sizeof(int));
    int* topluluk = (int*)malloc(1000 * sizeof(int));
    int indeks;

    printf("Topluluklar:\n");
    int i;
    for (i = 0; i < ag->dugum_sayisi; i++) {
        if (!ziyaret_edilenler[ag->dugumler[i]->kullanici_id]) {
            indeks = 0;
            toplulukBulDFS(ag->dugumler[i], ziyaret_edilenler, topluluk, &indeks);
            printf("Topluluk: ");
            int j;
            for (j = 0; j < indeks; j++) {
                printf("%d ", topluluk[j]);
            }
            printf("\n");
        }
    }

    free(ziyaret_edilenler);
    free(topluluk);
}

void etkialaniHesapla(AgacDugum* dugum, int* ziyaret_edilenler, int* etki) {
    ziyaret_edilenler[dugum->kullanici_id] = 1;
    (*etki)++;

    int i;
    for (i = 0; i < dugum->cocuk_sayisi; i++) {
        if (!ziyaret_edilenler[dugum->cocuklar[i]->kullanici_id]) {
            etkialaniHesapla(dugum->cocuklar[i], ziyaret_edilenler, etki);
        }
    }
}

int kullaniciEtkisi(SosyalAgAgaci* ag, int kullanici_id) {
    int* ziyaret_edilenler = (int*)calloc(1000, sizeof(int));
    int etki = 0;

    AgacDugum* baslangic_dugum = NULL;
    int i;
    for (i = 0; i < ag->dugum_sayisi; i++) {
        if (ag->dugumler[i]->kullanici_id == kullanici_id) {
            baslangic_dugum = ag->dugumler[i];
            break;
        }
    }

    if (baslangic_dugum) {
        etkialaniHesapla(baslangic_dugum, ziyaret_edilenler, &etki);
    }

    free(ziyaret_edilenler);
    return etki;
}

int main() {
    SosyalAgAgaci* sosyalAg = yeniSosyalAg();

    // Ornek veriler ekleniyor
    kullaniciEkle(sosyalAg, 101);
    kullaniciEkle(sosyalAg, 102);
    kullaniciEkle(sosyalAg, 103);
    kullaniciEkle(sosyalAg, 104);
    kullaniciEkle(sosyalAg, 105);

    iliskiEkleAgac(sosyalAg, 101, 102);
    iliskiEkleAgac(sosyalAg, 101, 103);
    iliskiEkleAgac(sosyalAg, 102, 104);
    iliskiEkleAgac(sosyalAg, 103, 104);
    iliskiEkleAgac(sosyalAg, 104, 105);

    printf("Derinlikteki arkadaslar:\n");
    derinlikIlkArama(sosyalAg, 101, 2);
    printf("\n\n");

    toplulukTespit(sosyalAg);

    int etkisi = kullaniciEtkisi(sosyalAg, 101);
    printf("\nKullanici 101 etkisi: %d\n", etkisi);

    return 0;
}
