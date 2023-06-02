#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int id;
    int nomor;
    bool terisi;
    bool sudahBayar; // Field baru untuk status pembayaran
    char namaPenghuni[50];
    int biaya;
    int pembayaran;   // Menyimpan data pembayaran
    int kembalian;    // Menyimpan data kembalian
} kamar;

typedef struct elmt* alamatelmt;

typedef struct elmt {
    kamar kontainer;
    alamatelmt next;
} penghuni;

typedef struct {
    penghuni* first;
} list;

void createList (list* L) {
    (*L).first = NULL;
}

int countElement (list L) {
    int hasil = 0;

    if (L.first != NULL) {
       penghuni* bantu;
       bantu = L.first;

       while (bantu != NULL) {
            hasil = hasil + 1;
            bantu = bantu->next;
       }
    }
    return hasil;
}

void cariKamar (int jumlahKamar, list* L) {
    printf("\n=====DATA KAMAR KOSONG=====\n");
    printf("\n =============");
    int awal = 1;
    penghuni* cari = (*L).first;
    int* hash = (int*)calloc((jumlahKamar - awal + 1), sizeof(int));

    while (cari != NULL) {
        if (cari->kontainer.nomor >= awal && cari->kontainer.nomor <= jumlahKamar) {
            hash[cari->kontainer.nomor - awal] = 1;
        }
        cari = cari->next;
    }

    for (int i = 0; i < jumlahKamar; i++) {
        if (hash[i] == 0) {
            printf("\n || Kamar %d ||", awal + i);
        }
    }
    printf("\n =============");
    free(hash);
}

int isTerisi (int nomor, list L) {
    penghuni* cari = L.first;
    int hasil = 0;
    while (cari != NULL) {
        if (cari->kontainer.nomor == nomor) {
            hasil = 1;
            return hasil;
        }
        cari = cari->next;
    }
    return hasil;
}

void firstPenghuni (int id, int nomor, char namaPenghuni[], int biaya, list* L) {
    penghuni* baru;
    baru = (penghuni*)malloc(sizeof(penghuni));

    baru->kontainer.id = id;
    baru->kontainer.nomor = nomor;
    baru->kontainer.terisi = true;
    strcpy(baru->kontainer.namaPenghuni, namaPenghuni);
    baru->kontainer.biaya = biaya;
    baru->kontainer.sudahBayar = false;

    if ((*L).first == NULL) {
        baru->next = NULL;
    } else {
        baru->next = (*L).first;
    }
    (*L).first = baru;
    baru = NULL;
    printf("Pesanan kamar berhasil ditambahkan.\n");
}

void afterPenghuni (penghuni* prev, int id, int nomor, char namaPenghuni[], int biaya) {
    if (prev != NULL) {
        penghuni* baru;
        baru = (penghuni*)malloc(sizeof(penghuni));

        baru->kontainer.id = id;
        baru->kontainer.nomor = nomor;
        baru->kontainer.terisi = true;
        strcpy(baru->kontainer.namaPenghuni, namaPenghuni);
        baru->kontainer.biaya = biaya;
        baru->kontainer.sudahBayar = false;

        if (prev->next = NULL) {
            baru->next = NULL;
        } else {
            baru->next = prev->next;
        }

        prev->next = baru;
        baru = NULL;
        printf("Pesanan kamar berhasil ditambahkan.\n");
    }
}

void addPenghuni (int id, int nomor, char namaPenghuni[], int biaya, list* L) {
    if ((*L).first == NULL) {
       firstPenghuni(id, nomor, namaPenghuni, biaya, L);
    } else {
        penghuni* last = (*L).first;
        while (last->next != NULL) {
            last = last->next;
        }
        afterPenghuni(last, id, nomor, namaPenghuni, biaya);
    }
}

void delFirstPenghuni (list* L) {
    if ((*L).first != NULL) {
       penghuni* hapus = (*L).first;
       if (countElement(*L) == 1) {
            (*L).first = NULL;
       } else {
           (*L).first = (*L).first->next;
       }
       hapus->next = NULL;
       free(hapus);
    } else {
        printf("\nTidak ada penghuni\n");
    }
}

void delPenghuni (int nomor, list* L) {
    penghuni* before = (*L).first;
    penghuni* bantu;
    while (before != NULL && before->kontainer.nomor != nomor) {
        before = before->next;
    }

    if (before == (*L).first) {
        delFirstPenghuni(&L);
    }

    else if (before != NULL && before->next != NULL) {
        penghuni *kamar = before->next;
        if (kamar->next == NULL) {
            before->next = NULL;
        } else {
            before->next = kamar->next;
        }
        kamar->next = NULL;
        free(kamar);
    } else {
        printf("\nKamar tersebut belum dihuni.\n");
    }
}
/*
void delLastPenghuni (list* L) {
    if ((*L).first != NULL) {
       if (countElement(*L) == 1) {
            delFirstPenghuni(L);
       } else {
           penghuni* last = (*L).first;
           penghuni* prev;

           while (last->next != NULL) {
                prev = last;
                last = last->next;
           }
           delAfterPenghuni(prev);
       }
    }
}*/

int idPertama (list L) {
    penghuni* bantu = L.first;
    penghuni* after = bantu->next;

    while (after != NULL) {
        if (after->kontainer.id < bantu->kontainer.id) {
            bantu = after;
        }
        after = after->next;
    }
    return bantu;
}

void selectionSortId (list* L) {
    penghuni* sorted = NULL;
    penghuni* bantu = (*L).first;

    while (bantu != NULL) {
        penghuni* pertama = idPertama(*L);
        if (pertama == bantu) {
            bantu = bantu->next;
            (*L).first = bantu;
        } else {
            penghuni* prev = bantu;
            while (prev->next != pertama) {
                prev = prev->next;
            }
            prev->next = pertama->next;
        }
        pertama->next = NULL;
        if (sorted == NULL) {
            sorted = pertama;
        } else {
            penghuni* terakhir = sorted;
            while (terakhir->next != NULL) {
                terakhir = terakhir->next;
            }
            terakhir->next = pertama;
        }
    }
    (*L).first = sorted;
}

int kamarPertama (list L) {
    penghuni* bantu = L.first;
    penghuni* after = bantu->next;

    while (after != NULL) {
        if (after->kontainer.nomor < bantu->kontainer.nomor) {
            bantu = after;
        }
        after = after->next;
    }
    return bantu;
}

void selectionSortKamar (list* L) {
    penghuni* sorted = NULL;
    penghuni* bantu = (*L).first;

    while (bantu != NULL) {
        penghuni* pertama = kamarPertama(*L);
        if (pertama == bantu) {
            bantu = bantu->next;
            (*L).first = bantu;
        } else {
            penghuni* prev = bantu;
            while (prev->next != pertama) {
                prev = prev->next;
            }
            prev->next = pertama->next;
        }
        pertama->next = NULL;
        if (sorted == NULL) {
            sorted = pertama;
        } else {
            penghuni* terakhir = sorted;
            while (terakhir->next != NULL) {
                terakhir = terakhir->next;
            }
            terakhir->next = pertama;
        }
    }
    (*L).first = sorted;
}

void dataPenghuni (list L) {
    printf("\n=======DATA PENGHUNI=======\n");
    if (L.first != NULL) {
        penghuni* bantu = L.first;
        while (bantu != NULL) {
            printf("\n===========================");
            printf("\nKamar %d || Penghuni: %s", bantu->kontainer.nomor, bantu->kontainer.namaPenghuni);
            printf("\n\t|| Biaya: Rp %d", bantu->kontainer.biaya);
            bantu = bantu->next;
        }
    } else {
        printf("\nBelum ada penghuni\n");
    }
    printf("\n===========================\n");
}

void konfirmasiPembayaran(list* L) {
    penghuni* cari = (*L).first;
    int nomor, bayar;
    printf("\nMasukkan nomor kamar: ");
    scanf("%d", &nomor);

    while (cari != NULL) {
        if (cari->kontainer.nomor == nomor) {
            printf("Masukkan jumlah pembayaran: ");
            scanf("%d", &cari->kontainer.pembayaran);   // Menyimpan data pembayaran
            while (cari->kontainer.pembayaran < cari->kontainer.biaya) {
                printf("Pembayaran kurang Rp %d", cari->kontainer.biaya - cari->kontainer.pembayaran);
                printf("\n\nMasukkan sisa pembayaran: ");
                scanf("%d", &bayar);
                cari->kontainer.pembayaran = cari->kontainer.pembayaran + bayar;
            }

            // Menghitung kembalian
            cari->kontainer.kembalian = cari->kontainer.pembayaran - cari->kontainer.biaya;
            cari->kontainer.sudahBayar = true;
            printf("Konfirmasi pembayaran berhasil.\n");
            return;
        }
        cari = cari->next;
    }
    printf("Nomor kamar tidak ditemukan.\n");
}

void cetakStruk(list* L) {
    printf("\n=======STRUK PEMBAYARAN=======\n");
    if ((*L).first != NULL) {
        penghuni* bantu = (*L).first;
        while (bantu != NULL) {
            if (bantu->kontainer.sudahBayar) {
                printf("\n=====================================");
                printf("\nNomor Struk : KOST/%02d/2023", bantu->kontainer.id);
                printf("\nKamar %d || Penghuni\t: %s", bantu->kontainer.nomor, bantu->kontainer.namaPenghuni);
                printf("\n\t|| Biaya\t: Rp %d", bantu->kontainer.biaya);
                printf("\n\t|| Pembayaran\t: Rp %d", bantu->kontainer.pembayaran);   // Menampilkan data pembayaran
                printf("\n\t|| Kembalian\t: Rp %d", bantu->kontainer.kembalian);     // Menampilkan data kembalian
            }
            bantu = bantu->next;
        }
    } else {
        printf("\nBelum ada penghuni\n");
    }
    printf("\n=====================================\n");
}

int main () {
    list L;
    int jumlahKamar, i, pilihan, id = 0;
    createList(&L);

    printf("======SELAMAT DATANG======\n");
    printf("==Di Program Sistem Kost==\n");
    printf("\nMasukkan jumlah kamar: ");
    scanf("%d", &jumlahKamar);

    while (jumlahKamar < 1) {
        printf("Tidak memiliki kamar.\n");
        printf("\nMasukkan kembali jumlah kamar: ");
        scanf("%d", &jumlahKamar);
    }
    do {
        printf("\n\nMenu Pengelolaan Kost:\n");
        printf("1. Mencari kamar kosong\n");
        printf("2. Menambahkan pesanan kamar\n");
        printf("3. Menghapus pesanan kamar\n");
        printf("4. Penagihan untuk penghuni kost\n");
        printf("5. Konfirmasi pembayaran\n");
        printf("6. Cetak struk\n");
        printf("7. Data penghuni\n");
        printf("0. Keluar\n");
        printf("Pilihan Anda: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                cariKamar(jumlahKamar, &L);
                break;
            case 2: {
                int nomor, biaya;
                char namaPenghuni[50];
                printf("\nMasukkan nomor kamar: ");
                scanf("%d", &nomor);
                while (isTerisi(nomor, L)) {
                    printf("Kamar telah terisi.\n");
                    printf("\nMasukkan nomor kamar: ");
                    scanf("%d", &nomor);
                }
                printf("Masukkan nama penghuni: ");
                fflush(stdin);
                fgets(namaPenghuni, 50, stdin);
                namaPenghuni[strcspn(namaPenghuni, "\n")] = '\0';
                if (nomor > 0 && nomor <= jumlahKamar/2) {
                    biaya = 1000000;
                } else if (nomor > jumlahKamar/2 && nomor <= jumlahKamar) {
                    biaya = 1500000;
                }
                printf("Biaya: Rp %d\n", biaya);
                id = id + 1;
                addPenghuni(id, nomor, namaPenghuni, biaya, &L);
                break;
            }
            case 3: {
                int nomor;
                printf("\nMasukkan nomor kamar: ");
                scanf("%d", &nomor);
                delPenghuni(nomor, &L);
                break;
            }
            case 4:
                selectionSortId(&L);
                dataPenghuni(L);
                break;
            case 5:
                konfirmasiPembayaran(&L);
                break;
            case 6:
                cetakStruk(&L);
                break;
            case 7:
                selectionSortKamar(&L);
                dataPenghuni(L);
                break;
            case 0:
                printf("Terima kasih. Program berakhir.\n");
                break;
            default:
                printf("Pilihan tidak valid. Silakan pilih menu yang tersedia.\n");
                break;
        }
    } while (pilihan != 0);

    return 0;
}
