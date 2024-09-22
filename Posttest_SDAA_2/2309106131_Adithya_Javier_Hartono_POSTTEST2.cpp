#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

const int MAX_NIKKE = 100;
const int MAX_TIM = 20;
const int MAX_ANGGOTA = 5;

struct Nikke {
    string nama;
    string manufacturer;
    string burst;
    string element;
    string kelas;
};

struct Tim {
    string namaTim;
    Nikke* anggota[MAX_ANGGOTA]; 
    int jumlahAnggota = 0;
};

Nikke daftarNikke[MAX_NIKKE];
Tim daftarTim[MAX_TIM];
int jumlahNikke = 0;
int jumlahTim = 0;

void cetakHeaderNikke() {
    system("cls");
    cout << left << setw(10) << "No" << setw(20) << "Nama" << setw(20) << "Manufacturer" 
         << setw(15) << "Burst" << setw(15) << "Element" << setw(15) << "Class" << endl;
    cout << "------------------------------------------------------------------------------" << endl;
}

void cetakHeaderTim() {
    system("cls");
    cout << left << setw(10) << "No" << setw(20) << "Nama Tim" << setw(60) << "Anggota" << endl;
    cout << "------------------------------------------------------------------------------" << endl;
}

void tambahNikke() {
    system("cls");
    if (jumlahNikke >= MAX_NIKKE) {
        cout << "Data Nikke penuh!" << endl;
        return;
    }
    
    Nikke nikkeBaru;
    cout << "Masukkan Nama Nikke: ";
    getline(cin, nikkeBaru.nama);
    cout << "Masukkan Manufacturer: ";
    getline(cin, nikkeBaru.manufacturer);
    cout << "Masukkan Burst: ";
    getline(cin, nikkeBaru.burst);
    cout << "Masukkan Element: ";
    getline(cin, nikkeBaru.element);
    cout << "Masukkan Class: ";
    getline(cin, nikkeBaru.kelas);
    
    daftarNikke[jumlahNikke++] = nikkeBaru;
    cout << "Nikke berhasil ditambahkan!" << endl;
}

void tampilkanSemuaNikke() {
    system("cls");
    if (jumlahNikke == 0) {
        cout << "Belum ada Nikke yang ditambahkan." << endl;
        return;
    }

    cetakHeaderNikke();
    for (int i = 0; i < jumlahNikke; i++) {
        cout << left << setw(10) << (i + 1) << setw(20) << daftarNikke[i].nama 
             << setw(20) << daftarNikke[i].manufacturer << setw(15) << daftarNikke[i].burst 
             << setw(15) << daftarNikke[i].element << setw(15) << daftarNikke[i].kelas << endl;
    }
}

void tambahTim() {
    system("cls");
    if (jumlahTim >= MAX_TIM) {
        cout << "Data Tim penuh!" << endl;
        return;
    }
    
    if (jumlahNikke < MAX_ANGGOTA) {
        cout << "Tambahkan minimal " << MAX_ANGGOTA << " Nikke terlebih dahulu." << endl;
        return;
    }
    
    Tim timBaru;
    cout << "Masukkan Nama Tim: ";
    getline(cin, timBaru.namaTim);
    
    tampilkanSemuaNikke();
    
    
    cout << "Pilih 5 Nikke untuk anggota tim (input nomor Nikke):" << endl;
    for (int i = 0; i < MAX_ANGGOTA; i++) {
        int pilihan;
        cout << "Pilih Nikke ke-" << (i + 1) << ": ";
        cin >> pilihan;
        cin.ignore();
        if (pilihan < 1 || pilihan > jumlahNikke) {
            cout << "Pilihan tidak valid." << endl;
            i--;
        } else {
            timBaru.anggota[i] = &daftarNikke[pilihan - 1];
            timBaru.jumlahAnggota++;
        }
    }
    
    daftarTim[jumlahTim++] = timBaru;
    cout << "Tim berhasil ditambahkan!" << endl;
}

void tampilkanSemuaTim() {
    system("cls");
    if (jumlahTim == 0) {
        cout << "Belum ada Tim yang ditambahkan." << endl;
        return;
    }

    cetakHeaderTim();
    for (int i = 0; i < jumlahTim; i++) {
        cout << left << setw(10) << (i + 1) << setw(20) << daftarTim[i].namaTim;
        for (int j = 0; j < daftarTim[i].jumlahAnggota; j++) {
            cout << daftarTim[i].anggota[j]->nama;
            if (j < daftarTim[i].jumlahAnggota - 1)
                cout << ", ";
        }
        cout << endl;
    }
}

void updateTim() {
    system("cls");
    if (jumlahTim == 0) {
        cout << "Belum ada Tim yang ditambahkan." << endl;
        return;
    }
    
    tampilkanSemuaTim();
    int pilihan;
    cout << "Pilih nomor tim yang akan diubah: ";
    cin >> pilihan;
    cin.ignore();
    
    if (pilihan < 1 || pilihan > jumlahTim) {
        cout << "Pilihan tidak valid." << endl;
        return;
    }
    
    Tim* timDipilih = &daftarTim[pilihan - 1];
    
    cout << "Anggota tim saat ini: ";
    for (int i = 0; i < timDipilih->jumlahAnggota; i++) {
        cout << timDipilih->anggota[i]->nama;
        if (i < timDipilih->jumlahAnggota - 1)
            cout << ", ";
    }
    cout << endl;
    
    tampilkanSemuaNikke();
    
    cout << "Pilih 5 Nikke baru untuk anggota tim (input nomor Nikke):" << endl;
    for (int i = 0; i < MAX_ANGGOTA; i++) {
        int pilihanNikke;
        cout << "Pilih Nikke ke-" << (i + 1) << ": ";
        cin >> pilihanNikke;
        cin.ignore();
        if (pilihanNikke < 1 || pilihanNikke > jumlahNikke) {
            cout << "Pilihan tidak valid." << endl;
            i--;
        } else {
            timDipilih->anggota[i] = &daftarNikke[pilihanNikke - 1];
        }
    }
    cout << "Tim berhasil diupdate!" << endl;
}

void hapusTim() {
    system("cls");
    if (jumlahTim == 0) {
        cout << "Belum ada Tim yang ditambahkan." << endl;
        return;
    }
    
    tampilkanSemuaTim();
    int pilihan;
    cout << "Pilih nomor tim yang akan dihapus: ";
    cin >> pilihan;
    cin.ignore();
    
    if (pilihan < 1 || pilihan > jumlahTim) {
        cout << "Pilihan tidak valid." << endl;
        return;
    }
    
    for (int i = pilihan - 1; i < jumlahTim - 1; i++) {
        daftarTim[i] = daftarTim[i + 1];
    }
    jumlahTim--;
    cout << "Tim berhasil dihapus!" << endl;
}

void menuUtama() {  
    system("cls");
    int pilihan;
    do {
        cout << "\n===== Menu Utama =====" << endl;
        cout << "1. Tambah Nikke" << endl;
        cout << "2. Lihat Semua Nikke" << endl;
        cout << "3. Tambah Tim" << endl;
        cout << "4. Lihat Semua Tim" << endl;
        cout << "5. Ubah Tim" << endl;
        cout << "6. Hapus Tim" << endl;
        cout << "7. Keluar" << endl;
        cout << "Pilih menu: ";
        cin >> pilihan;
        cin.ignore();
        
        switch (pilihan) {
            case 1:
                tambahNikke();
                break;
            case 2:
                tampilkanSemuaNikke();
                break;
            case 3:
                tampilkanSemuaTim();
                break;
            case 4:
                tambahTim();
                break;
            case 5:
                updateTim();
                break;
            case 6:
                hapusTim();
                break;
            case 7:
                cout << "Keluar dari program." << endl;
                break;
            default:
                cout << "Pilihan tidak valid." << endl;
        }
    } while (pilihan != 7);
}

int main() {
    menuUtama();
    return 0;
}