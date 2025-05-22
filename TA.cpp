#include <iostream>
#include <iomanip>
#include <cstdio>  //ini mirip stdio.h yang sering dipake pak hersof
#include <cstring> //ini buat library strlen
using namespace std;

// ini struct buku nya
struct buku
{
    int id, tahun;
    char judul[300], pengarang[100], penerbit[100], kategori[100];
    buku *next;
    buku *prev;
};

// fungsi validasi id buku, jadi kalo misal id kurang  atau lebih dari yang tertera, maka bakal balik false
// jadi id buku itu harus 5 digit, misal 12345
bool validasi_id(int id)
{
    return (id >= 10000 && id <= 99999);
}

// fungsi validasi tahun, jadi kalo misal tahun kurang dari yang tertera, maka bakal balik false
// jadi tahun buku itu harus 4 digit, misal 2023
bool validasi_tahun(int tahun)
{
    return (tahun >= 1000 && tahun <= 9999);
}

// fungsi validasi judul buku, jadi kalo misal judul kurang dari yang tertera, maka bakal balik false
bool validasi_judul(const char *judul)
{
    // strlen secara singkat, dia menghitung panjang karakter stringnya(termasuk spasi)
    int len = strlen(judul); // ini buat ngitung panjang judul, panjang judul itu harus antara 1-300 karakter
    return (len >= 1 && len <= 300);
}

// fungsi buat input data buku
void input_data()
{
    FILE *fp = fopen("data_buku.dat", "ab"); // buka file buat nulis
    if (!fp)
    {
        cout << "Gagal membuka file!" << endl;
        return;
    }

    // input jumlah buku yang mau ditambah
    int jumlah;
    cout << "Masukkan jumlah buku yang ingin ditambahkan: ";
    cin >> jumlah;
    cin.ignore();

    buku b;
    for (int i = 0; i < jumlah; ++i)
    {
        // ID
        do
        {
            cout << "Masukkan ID Buku (5 digit): ";
            cin >> b.id;
            cin.ignore();
            // peringatan kalo id < atau > dari 5 digit
            if (!validasi_id(b.id))
            {
                cout << endl;
                cout << "ID harus terdiri dari 5 digit. " << endl;
                cout << endl;
            }
        } while (!validasi_id(b.id));

        // Judul
        do
        {
            cout << "Masukkan Judul Buku (1-300 karakter): ";
            cin.getline(b.judul, 300);
            // peringatan kalo panjang judul < atau > dari 300
            if (!validasi_judul(b.judul))
            {
                cout << endl;
                cout << "Judul harus antara 1 sampai 300 karakter." << endl;
                cout << endl;
            }
        } while (!validasi_judul(b.judul));

        // Pengarang
        cout << "Masukkan Pengarang Buku: ";
        cin.getline(b.pengarang, 100);

        // Penerbit
        cout << "Masukkan Penerbit Buku: ";
        cin.getline(b.penerbit, 100);

        // Tahun
        do
        {
            cout << "Masukkan Tahun Terbit Buku (4 digit): ";
            cin >> b.tahun;
            cin.ignore();
            // peringatan kalo tahun < atau > dari 4 digit
            if (!validasi_tahun(b.tahun))
            {
                cout << endl;
                cout << "Tahun harus terdiri dari 4 digit." << endl;
                cout << endl;
            }
        } while (!validasi_tahun(b.tahun));

        // Kategori
        cout << "Masukkan Kategori Buku: ";
        cin.getline(b.kategori, 100);

        fwrite(&b, sizeof(buku), 1, fp); // nulis data buku ke file
        cout << "Buku ke-" << (i + 1) << " berhasil ditambahkan." << endl
             << endl;
    }

    fclose(fp);
}

// fungsi buat nampilin data buku
void tampil_data()
{
    FILE *fp = fopen("data_buku.dat", "rb"); // buka file buat baca
    if (!fp)
    {
        cout << "Tidak dapat membuka file untuk membaca!" << endl;
        return;
    }

    buku b;
    int i = 1;

    cout << setfill('=') << setw(100) << " " << endl;
    cout << setfill(' ') << setw(55) << "Data Buku" << endl;
    cout << setfill('=') << setw(100) << " " << endl;

    cout << setfill(' ') << setw(10) << "No" << setw(1) << "|"
         << setw(8) << "ID" << setw(1) << "|"
         << setw(30) << "Judul" << setw(1) << "|"
         << setw(15) << "Pengarang" << setw(1) << "|"
         << setw(15) << "Penerbit" << setw(1) << "|"
         << setw(8) << "Tahun" << setw(1) << "|"
         << setw(15) << "Kategori" << setw(1) << "|" << endl;
    cout << setfill('-') << setw(125) << "-" << setfill(' ') << endl;

    // baca data buku dari file
    while (fread(&b, sizeof(buku), 1, fp))
    {
        cout << setfill(' ') << setw(10) << i++ << setw(1) << "|"
             << setw(8) << b.id << setw(1) << "|"
             << setw(30) << b.judul << setw(1) << "|"
             << setw(15) << b.pengarang << setw(1) << "|"
             << setw(15) << b.penerbit << setw(1) << "|"
             << setw(8) << b.tahun << setw(1) << "|"
             << setw(15) << b.kategori << setw(1) << "|" << endl;
    }
    cout << setfill('-') << setw(125) << "-" << setfill(' ') << endl;

    fclose(fp); // tutup file
    cout << setfill('=') << setw(100) << " " << endl;
}

void searching_data()
{
    char cari[300];
    bool found = false;
    cout << "Masukkan Judul Buku yang dicari: ";
    cin.ignore();
    cin.getline(cari, 300);

    FILE *fp = fopen("data_buku.dat", "rb");
    if (!fp)
    {
        cout << "Tidak dapat membuka file untuk membaca!" << endl;
        return;
    }

    buku b;
    while (fread(&b, sizeof(buku), 1, fp))
    {
        if (strcmp(b.judul, cari) == 0)
        {
            found = true;
            cout << "\nData ditemukan sebagai berikut:\n";
            cout << "ID: " << b.id << endl;
            cout << "Judul: " << b.judul << endl;
            cout << "Pengarang: " << b.pengarang << endl;
            cout << "Penerbit: " << b.penerbit << endl;
            cout << "Tahun: " << b.tahun << endl;
            cout << "Kategori: " << b.kategori << endl;
            break; // berhenti setelah ketemu
        }
    }

    if (!found)
    {
        cout << "\nData tidak ditemukan.\n";
    }

    fclose(fp);
}

void sorting_data()
{
    int i, j;
    FILE *fp = fopen("data_buku.dat", "rb");
    if (!fp)
    {
        cout << "Tidak dapat membuka file!" << endl;
        return;
    }

    buku arr[1000]; // maksimal 1000 data buku
    int n = 0;

    // baca semua data ke array(menggunakan array karena bisa bebas sorting di RAM, yang cepat dan fleksibel)
    while (fread(&arr[n], sizeof(buku), 1, fp))
    {
        n++;
    }
    fclose(fp);

    if (n == 0)
    {
        cout << "Tidak ada data buku untuk disorting!" << endl;
        return;
    }

    int pilihan;
    cout << "Sorting berdasarkan ID Buku:\n";
    cout << "1. Ascending (kecil ke besar)\n";
    cout << "2. Descending (besar ke kecil)\n";
    cout << "Pilih jenis sorting (1/2): ";
    cin >> pilihan;
    cin.ignore();

    // Bubble Sort berdasarkan ID
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if ((pilihan == 1 && arr[j].id > arr[j + 1].id) ||
                (pilihan == 2 && arr[j].id < arr[j + 1].id))
            {
                swap(arr[j], arr[j + 1]);
            }
        }
    }

    // Tampilkan hasil sorting
    cout << "\nData Buku Setelah Sorting Berdasarkan ID:\n";
    cout << setfill('=') << setw(100) << " " << endl;
    cout << setfill(' ') << setw(55) << "Data Buku (Sorted by ID)" << endl;
    cout << setfill('=') << setw(100) << " " << endl;

    cout << setfill(' ') << setw(10) << "No" << setw(1) << "|"
         << setw(8) << "ID" << setw(1) << "|"
         << setw(30) << "Judul" << setw(1) << "|"
         << setw(15) << "Pengarang" << setw(1) << "|"
         << setw(15) << "Penerbit" << setw(1) << "|"
         << setw(8) << "Tahun" << setw(1) << "|"
         << setw(15) << "Kategori" << setw(1) << "|" << endl;
    cout << setfill('-') << setw(125) << "-" << setfill(' ') << endl;

    for (int i = 0; i < n; ++i)
    {
        cout << setfill(' ') << setw(10) << i + 1 << setw(1) << "|"
             << setw(8) << arr[i].id << setw(1) << "|"
             << setw(30) << arr[i].judul << setw(1) << "|"
             << setw(15) << arr[i].pengarang << setw(1) << "|"
             << setw(15) << arr[i].penerbit << setw(1) << "|"
             << setw(8) << arr[i].tahun << setw(1) << "|"
             << setw(15) << arr[i].kategori << setw(1) << "|" << endl;
    }

    cout << setfill('=') << setw(100) << " " << endl;
}

// buat baca data buku dari file dengan menggunakan linked list, nanti dipake buat peminjaman
buku *baca_data_buku()
{
    FILE *fp = fopen("data_buku.dat", "rb"); // baca data buku
    if (!fp)
    {
        cout << "File tidak ditemukan!" << endl;
        return nullptr;
    }

    buku *head = nullptr, *tail = nullptr, *baru; // deklarasi pointer biar bisa jadi linked list

    buku temp;
    while (fread(&temp, sizeof(buku), 1, fp)) // ini nulis linked list nya
    {
        baru = new buku;
        *baru = temp;
        baru->next = nullptr;
        baru->prev = tail;

        if (!head)
            head = baru;
        else
            tail->next = baru;

        tail = baru;
    }

    fclose(fp);
    return head;
}

// fungsi buat cari buku berdasarkan id buku yang mau dipinjam
buku *cari_buku_by_id(buku *head, int id)
{
    while (head)
    {
        if (head->id == id)
            return head;
        head = head->next;
    }
    return nullptr;
}

// fungsi buat pinjam buku
void pinjam_buku()
{
    buku *head = baca_data_buku(); // baca data buku dari file
    if (!head)
        return;

    cout << "Daftar Buku yang Tersedia:" << endl;
    cout << setfill('-') << setw(125) << "-" << setfill(' ') << endl;
    buku *temp = head;
    int i = 1;
    while (temp)
    {
        cout << setfill(' ') << setw(10) << i++ << setw(1) << "|"
             << setw(8) << temp->id << setw(1) << "|"
             << setw(30) << temp->judul << setw(1) << "|"
             << setw(15) << temp->pengarang << setw(1) << "|"
             << setw(15) << temp->penerbit << setw(1) << "|"
             << setw(8) << temp->tahun << setw(1) << "|"
             << setw(15) << temp->kategori << setw(1) << "|" << endl;
        temp = temp->next;
    }
    cout << setfill('-') << setw(125) << "-" << setfill(' ') << endl;

    int idCari;
    cout << "Masukkan ID buku yang ingin dipinjam: ";
    cin >> idCari;

    buku *b = cari_buku_by_id(head, idCari);
    if (b)
    {
        cout << "\nData Buku yang Akan Dipinjam:" << endl;
        cout << "ID Buku    : " << b->id << endl;
        cout << "Judul      : " << b->judul << endl;
        cout << "Pengarang  : " << b->pengarang << endl;
        cout << "Penerbit   : " << b->penerbit << endl;
        cout << "Tahun      : " << b->tahun << endl;
        cout << "Kategori   : " << b->kategori << endl;

        cout << "\nBuku berhasil dipinjam." << endl;
    }
    else
    {
        cout << "Buku dengan ID tersebut tidak ditemukan!" << endl;
    }

    // Bebaskan memori
    while (head)
    {
        buku *hapus = head;
        head = head->next;
        delete hapus;
    }

    // Simpan data peminjaman ke file
    // Menyimpan histori peminjaman
    char tanggal[20];
    cout << "Masukkan tanggal peminjaman (YYYY-MM-DD): ";
    cin >> tanggal;

    char namaFile[100];
    sprintf(namaFile, "histori_pinjam_%s.txt", tanggal);
    FILE *fpinjam = fopen(namaFile, "a");
    if (fpinjam)
    {
        fprintf(fpinjam, "ID: %d | Judul: %s | Pengarang: %s | Penerbit: %s | Tahun: %d | Kategori: %s\n",
                b->id, b->judul, b->pengarang, b->penerbit, b->tahun, b->kategori);
        fclose(fpinjam);
    }
}
void pengembalian_buku()
{
    buku *head = baca_data_buku(); // baca semua data buku dari file
    if (!head)
        return;

    cout << "Daftar Buku yang Terdaftar:" << endl;
    cout << setfill('-') << setw(125) << "-" << setfill(' ') << endl;
    buku *temp = head;
    int i = 1;
    while (temp)
    {
        cout << setfill(' ') << setw(10) << i++ << setw(1) << "|"
             << setw(8) << temp->id << setw(1) << "|"
             << setw(30) << temp->judul << setw(1) << "|"
             << setw(15) << temp->pengarang << setw(1) << "|"
             << setw(15) << temp->penerbit << setw(1) << "|"
             << setw(8) << temp->tahun << setw(1) << "|"
             << setw(15) << temp->kategori << setw(1) << "|" << endl;
        temp = temp->next;
    }
    cout << setfill('-') << setw(125) << "-" << setfill(' ') << endl;

    int idCari;
    cout << "Masukkan ID buku yang ingin dikembalikan: ";
    cin >> idCari;

    buku *b = cari_buku_by_id(head, idCari);
    if (b)
    {
        cout << "\nData Buku yang Akan Dikembalikan:" << endl;
        cout << "ID Buku    : " << b->id << endl;
        cout << "Judul      : " << b->judul << endl;
        cout << "Pengarang  : " << b->pengarang << endl;
        cout << "Penerbit   : " << b->penerbit << endl;
        cout << "Tahun      : " << b->tahun << endl;
        cout << "Kategori   : " << b->kategori << endl;

        cout << "\nBuku berhasil dikembalikan." << endl;
    }
    else
    {
        cout << "Buku dengan ID tersebut tidak ditemukan!" << endl;
    }

    // Bebaskan memori
    while (head)
    {
        buku *hapus = head;
        head = head->next;
        delete hapus;
    }
    // Simpan data pengembalian ke file
    // Menyimpan histori pengembalian
    char tanggal[20];
    cout << "Masukkan tanggal pengembalian (YYYY-MM-DD): ";
    cin >> tanggal;

    char namaFile[100];
    sprintf(namaFile, "histori_kembali_%s.txt", tanggal);
    FILE *fkembali = fopen(namaFile, "a");
    if (fkembali)
    {
        fprintf(fkembali, "ID: %d | Judul: %s | Pengarang: %s | Penerbit: %s | Tahun: %d | Kategori: %s\n",
                b->id, b->judul, b->pengarang, b->penerbit, b->tahun, b->kategori);
        fclose(fkembali);
    }
}

// fungsi untuk menampilkan data histori
void tampilkan_histori(const char *jenis)
{
    char tanggal[20];
    cout << "Masukkan tanggal histori yang ingin ditampilkan (YYYY-MM-DD): ";
    cin >> tanggal;

    char namaFile[100];
    sprintf(namaFile, "histori_%s_%s.txt", jenis, tanggal);
    FILE *f = fopen(namaFile, "r");
    if (!f)
    {
        cout << "Histori tidak ditemukan untuk tanggal tersebut.\n";
        return;
    }

    cout << "\nIsi Histori " << jenis << " pada " << tanggal << ":\n";
    char line[500];
    while (fgets(line, sizeof(line), f))
    {
        cout << line;
    }
    fclose(f);
}

// fungsi untuk edit data buku
void edit_data_buku()
{
    int idEdit;
    cout << "Masukkan ID Buku yang ingin diedit: ";
    cin >> idEdit;
    cin.ignore();

    FILE *fp = fopen("data_buku.dat", "rb");
    if (!fp)
    {
        cout << "File tidak ditemukan!" << endl;
        return;
    }

    buku arr[1000];
    int n = 0;
    while (fread(&arr[n], sizeof(buku), 1, fp))
    {
        n++;
    }
    fclose(fp);

    bool found = false;
    for (int i = 0; i < n; ++i)
    {
        if (arr[i].id == idEdit)
        {
            found = true;
            cout << "\nData lama:\n";
            cout << "Judul: " << arr[i].judul << endl;

            cout << "\nMasukkan data baru:\n";
            cout << "Judul: ";
            cin.getline(arr[i].judul, 300);
            cout << "Pengarang: ";
            cin.getline(arr[i].pengarang, 100);
            cout << "Penerbit: ";
            cin.getline(arr[i].penerbit, 100);
            cout << "Tahun: ";
            cin >> arr[i].tahun;
            cin.ignore();
            cout << "Kategori: ";
            cin.getline(arr[i].kategori, 100);

            break;
        }
    }

    if (!found)
    {
        cout << "Buku dengan ID tersebut tidak ditemukan!" << endl;
        return;
    }

    // Tulis ulang seluruh data ke file setelah diedit
    fp = fopen("data_buku.dat", "wb");
    if (!fp)
    {
        cout << "Gagal membuka file untuk menulis!" << endl;
        return;
    }

    for (int i = 0; i < n; ++i)
    {
        fwrite(&arr[i], sizeof(buku), 1, fp);
    }

    fclose(fp);
    cout << "\nData buku berhasil diperbarui." << endl;
}

// fungsi untuk menghapus data buku
void hapus_data_buku()
{
    int idHapus;
    cout << "Masukkan ID Buku yang ingin dihapus: ";
    cin >> idHapus;
    cin.ignore();

    FILE *fp = fopen("data_buku.dat", "rb");
    if (!fp)
    {
        cout << "File tidak ditemukan!" << endl;
        return;
    }

    buku arr[1000];
    int n = 0;
    while (fread(&arr[n], sizeof(buku), 1, fp))
    {
        n++;
    }
    fclose(fp);

    bool found = false;
    int j = 0;
    for (int i = 0; i < n; ++i)
    {
        if (arr[i].id != idHapus)
        {
            arr[j++] = arr[i];
        }
        else
        {
            found = true;
        }
    }

    if (!found)
    {
        cout << "Data dengan ID tersebut tidak ditemukan!" << endl;
        return;
    }

    fp = fopen("data_buku.dat", "wb");
    fwrite(arr, sizeof(buku), j, fp);
    fclose(fp);

    cout << "Data berhasil dihapus." << endl;
}

// fungsi buat keluar dari program
void keluar()
{
    cout << "Terima kasih telah menggunakan program ini." << endl;
    exit(0);
}

int main()
{
    int pilih;
    do
    {
        cout << setfill('=') << setw(50) << " " << endl;
        cout << setfill(' ') << setw(30) << "MENU PILIHAN" << endl;
        cout << setfill('=') << setw(50) << " " << endl;

        cout << "1. Arsip Buku" << endl;
        cout << "2. Tampilkan Data Buku" << endl;
        cout << "3. Searching Data Buku" << endl;
        cout << "4. Sorting Data Buku" << endl;
        cout << "5. Peminjaman Buku" << endl;
        cout << "6. Pengembalian Buku" << endl;
        cout << "7. Keluar" << endl;
        cout << setfill('=') << setw(50) << " " << endl;

        cout << "Masukkan Pilihan : ";
        cin >> pilih;
        cin.ignore();
        system("CLS");

        switch (pilih)
        {
        case 1:
            cout << "Pilih Fitur Edit Data: " << endl;
            cout << "1. Input Data Buku" << endl;
            cout << "2. Edit Data Buku" << endl;
            cout << "3. Hapus Data Buku" << endl;
            cout << "Masukkan Pilihan: ";
            int editPilihan;
            cin >> editPilihan;
            cin.ignore();
            if (editPilihan == 1)
            {
                input_data();
            }
            else if (editPilihan == 2)
            {
                edit_data_buku();
            }
            else if (editPilihan == 3)
            {
                hapus_data_buku();
            }
            else
            {
                cout << "Pilihan tidak valid!" << endl;
            }
            break;
            input_data();
            break;
        case 2:
            cout << "Tampilkan Data Buku\n";
            cout << "a. Arsip\n";
            cout << "b. Histori Peminjaman\n";
            cout << "c. Histori Pengembalian\n";
            cout << "Pilih submenu (a/b/c): ";
            char subpilih;
            cin >> subpilih;
            cin.ignore();
            switch (subpilih)
            {
            case 'a':
                tampil_data();
                break;
            case 'b':
                tampilkan_histori("pinjam");
                break;
            case 'c':
                tampilkan_histori("kembali");
                break;
            default:
                cout << "Pilihan submenu tidak valid!\n";
                break;
            }
            break;

        case 3:
            searching_data();
            break;
        case 4:
            sorting_data();
            break;
        case 5:
            pinjam_buku();
            break;
        case 6:
            pengembalian_buku();
            break;
        case 7:
            keluar();
            break;
        default:
            cout << "Pilihan tidak valid!" << endl;
            break;
        }
    } while (true);

    return 0;
}
