#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstring>
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
