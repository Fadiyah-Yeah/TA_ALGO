#include <iostream>
#include <iomanip>
#include <cstdio>//ini mirip stdio.h yang sering dipake pak hersof
#include <cstring>//ini buat library strlen
using namespace std;

// ini struct buku nya
struct buku
{
    int id, tahun;
    char judul[300], pengarang[100], penerbit[100], kategori[100];
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
    //strlen secara singkat, dia menghitung panjang karakter stringnya(termasuk spasi) 
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
                cout << "ID harus terdiri dari 5 digit. << endl";
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
                cout << "Judul harus antara 1 sampai 300 karakter. << endl";
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
                cout << "Tahun harus terdiri dari 4 digit. << endl";
                cout << endl;
            }
        } while (!validasi_tahun(b.tahun));

        // Kategori
        cout << "Masukkan Kategori Buku: ";
        cin.getline(b.kategori, 100);

        fwrite(&b, sizeof(buku), 1, fp); // nulis data buku ke file
        cout << "Buku ke-" << (i + 1) << " berhasil ditambahkan. << endl << endl";
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
             << setw(15) << b.kategori.nama << setw(1) << "|" << endl;
    }
    cout << setfill('-') << setw(125) << "-" << setfill(' ') << endl;

    fclose(fp); // tutup file
    cout << setfill('=') << setw(100) << " " << endl;
}

void searching_data() {
    char cari[300];
    bool found = false;
    cout << "Masukkan Judul Buku yang dicari: ";
    cin.ignore();
    cin.getline(cari, 300);

    FILE *fp = fopen("data_buku.dat", "rb");
    if (!fp) {
        cout << "Tidak dapat membuka file untuk membaca!" << endl;
        return;
    }

    buku b;
    while (fread(&b, sizeof(buku), 1, fp)) {
        if (strcmp(b.judul, cari) == 0) {
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

    if (!found) {
        cout << "\nData tidak ditemukan.\n";
    }

    fclose(fp);
}

void sorting_data() {
     int i, j;
    FILE *fp = fopen("data_buku.dat", "rb");
    if (!fp) {
        cout << "Tidak dapat membuka file!" << endl;
        return;
    }

    buku arr[1000]; // maksimal 1000 data buku
    int n = 0;

    // baca semua data ke array(menggunakan array karena bisa bebas sorting di RAM, yang cepat dan fleksibel)
    while (fread(&arr[n], sizeof(buku), 1, fp)) {
        n++;
    }
    fclose(fp);

    if (n == 0) {
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
   for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - i - 1; j++) {
        if ((pilihan == 1 && arr[j].id > arr[j + 1].id) ||
            (pilihan == 2 && arr[j].id < arr[j + 1].id)) {
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

    for (int i = 0; i < n; ++i) {
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

//buat baca data buku dari file dengan menggunakan linked list, nanti dipake buat peminjaman
buku* baca_data_buku()
{
    FILE *fp = fopen("data_buku.dat", "rb");
    if (!fp)
    {
        cout << "File tidak ditemukan!" << endl;
        return nullptr;
    }

    buku *head = nullptr, *tail = nullptr, *baru;

    buku temp;
    while (fread(&temp, sizeof(buku), 1, fp))
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

        cout << "1. Input Data Buku" << endl;
        cout << "2. Tampilkan Data Buku" << endl;
        cout << "3. Searching Data Buku" << endl;
        cout << "4. Sorting Data Buku" << endl;
        cout << "5. Peminjaman Buku" << endl;
        cout << "6. Keluar" << endl;
        cout << setfill('=') << setw(50) << " " << endl;

        cout << "Masukkan Pilihan : ";
        cin >> pilih;
        cin.ignore();
        system("CLS");

        switch (pilih)
        {
        case 1:
            input_data();
            break;
        case 2:
            tampil_data();
            break;
        case 3:
            // searching_data();
            break;
        case 4:
            // sorting_data();
            break;
        case 5:
            // peminjaman_data();
            break;
        case 6:
            keluar();
            break;
        default:
            cout << "Pilihan tidak valid!" << endl;
            break;
        }
    } while (true);

    return 0;
}
