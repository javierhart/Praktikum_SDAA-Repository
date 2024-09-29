#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

struct Nikke {
    string nama;
    string manufacturer;
    string burst;
    string element;
    string kelas;
    Nikke* next = nullptr;  
};

struct AnggotaTim {
    Nikke* nikke;  
    AnggotaTim* next = nullptr;  
};

struct Tim {
    string namaTim;
    AnggotaTim* anggotaTim = nullptr;  
    Tim* next = nullptr;  
};

Nikke* headNikke = nullptr;  
Tim* headTim = nullptr;  
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
    Nikke* nikkeBaru = new Nikke;

    cout << "Masukkan Nama Nikke: ";
    getline(cin, nikkeBaru->nama);
    cout << "Masukkan Manufacturer: ";
    getline(cin, nikkeBaru->manufacturer);
    cout << "Masukkan Burst: ";
    getline(cin, nikkeBaru->burst);
    cout << "Masukkan Element: ";
    getline(cin, nikkeBaru->element);
    cout << "Masukkan Class: ";
    getline(cin, nikkeBaru->kelas);
    
    nikkeBaru->next = headNikke;
    headNikke = nikkeBaru;
    jumlahNikke++;
    cout << "Nikke berhasil ditambahkan!" << endl;
}

void tampilkanSemuaNikke() {
    system("cls");
    if (jumlahNikke == 0) {
        cout << "Belum ada Nikke yang ditambahkan." << endl;
        return;
    }

    cetakHeaderNikke();
    Nikke* temp = headNikke;
    int no = 1;
    while (temp != nullptr) {
        cout << left << setw(10) << no++ << setw(20) << temp->nama
             << setw(20) << temp->manufacturer << setw(15) << temp->burst
             << setw(15) << temp->element << setw(15) << temp->kelas << endl;
        temp = temp->next;
    }
}

void tambahTim() {
    system("cls");
    if (jumlahNikke < 5) {
        cout << "Tambahkan minimal 5 Nikke terlebih dahulu." << endl;
        return;
    }

    Tim* timBaru = new Tim;
    cout << "Masukkan Nama Tim: ";
    getline(cin, timBaru->namaTim);

    tampilkanSemuaNikke();

    cout << "Pilih 5 Nikke untuk anggota tim (input nomor Nikke):" << endl;
    for (int i = 0; i < 5; i++) {
        int pilihan;
        cout << "Pilih Nikke ke-" << (i + 1) << ": ";
        cin >> pilihan;
        cin.ignore();

        if (pilihan < 1 || pilihan > jumlahNikke) {
            cout << "Pilihan tidak valid." << endl;
            i--;
        } else {
            Nikke* temp = headNikke;
            for (int j = 1; j < pilihan; j++) {
                temp = temp->next;
            }

            AnggotaTim* anggotaBaru = new AnggotaTim;
            anggotaBaru->nikke = temp;
            anggotaBaru->next = timBaru->anggotaTim;
            timBaru->anggotaTim = anggotaBaru;
        }
    }

    timBaru->next = headTim;
    headTim = timBaru;
    jumlahTim++;
    cout << "Tim berhasil ditambahkan!" << endl;
}

void tampilkanSemuaTim() {
    system("cls");
    if (jumlahTim == 0) {
        cout << "Belum ada Tim yang ditambahkan." << endl;
        return;
    }

    cetakHeaderTim();
    Tim* tempTim = headTim;
    int no = 1;
    while (tempTim != nullptr) {
        cout << left << setw(10) << no++ << setw(20) << tempTim->namaTim;

        AnggotaTim* tempAnggota = tempTim->anggotaTim;
        while (tempAnggota != nullptr) {
            cout << tempAnggota->nikke->nama;
            if (tempAnggota->next != nullptr)
                cout << ", ";
            tempAnggota = tempAnggota->next;
        }

        cout << endl;
        tempTim = tempTim->next;
    }
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
        cout << "5. Keluar" << endl;
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
                tambahTim();
                break;
            case 4:
                tampilkanSemuaTim();
                break;
            case 5:
                cout << "Keluar dari program." << endl;
                break;
            default:
                cout << "Pilihan tidak valid." << endl;
        }
    } while (pilihan != 5);
}

int main() {
    menuUtama();
    return 0;
}
