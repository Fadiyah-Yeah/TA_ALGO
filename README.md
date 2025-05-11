# TA_ALGO
#include <iostream>
#include <fstream>
using namespace std;





int main() {
    do {
        cout << setfill(' ') << setw(35) << "Program Data Mahasiswa" << endl;
    cout << "1. Input Data" << endl;
    cout << "2. Tampil Data" << endl;
    cout << "3. Searching" << endl;
    cout << "4. Sorting" << endl;
    cout << "5. Peminjaman" << endl;
    cout << "5. Exit/Keluar" << endl;
    cout << setfill('=') << setw(50) << " " << endl;
    cout << "Pilihan : ";
    cin >> pilihan;
        switch (pilihan) {
            case 1:
                inputData();
                break;
            case 2:
                tampilData();
                break;
            case 3:
                searching();
                break;
            case 4:
                sorting();
                break;
            case 5:
                peminjaman();
                break;
            case 6:
                cout << "Exit" << endl;
                cout << "Terima kasih telah menggunakan program ini" << endl;
                break;
            default:
                cout << "Pilihan tidak valid." << endl;
        }
        cout << "Apakah anda ingin melanjutkan program? (y/t) : ";
        cin >> lanjut;
    } while (lanjut == 'y' || lanjut == 'Y');

    return 0;
}
 
