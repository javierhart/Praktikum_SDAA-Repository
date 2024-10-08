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

struct Stack {
    Nikke* top = nullptr;

    bool isEmpty() {
        return top == nullptr;
    }

    void push(Nikke* nikke) {
        nikke->next = top;
        top = nikke;
    }

    Nikke* pop() {
        if (isEmpty()) {
            cout << "Stack kosong oii!" << endl;
            return nullptr;
        }
        Nikke* temp = top;
        top = top->next;
        return temp;
    }

    void printStack() {
        Nikke* temp = top;
        int no = 1;
        while (temp != nullptr) {
            cout << left << setw(10) << no++ << setw(20) << temp->nama
                 << setw(20) << temp->manufacturer << setw(15) << temp->burst
                 << setw(15) << temp->element << setw(15) << temp->kelas << endl;
            temp = temp->next;
        }
    }
};


struct Queue {
    Tim* front = nullptr;
    Tim* rear = nullptr;

    bool isEmpty() {
        return front == nullptr;
    }

    void enqueue(Tim* tim) {
        if (isEmpty()) {
            front = rear = tim;
        } else {
            rear->next = tim;
            rear = tim;
        }
    }

    Tim* dequeue() {
        if (isEmpty()) {
            cout << "Queue kosong oii!" << endl;
            return nullptr;
        }
        Tim* temp = front;
        front = front->next;
        if (front == nullptr) {
            rear = nullptr;
        }
        return temp;
    }

    void printQueue() {
        Tim* temp = front;
        int no = 1;
        while (temp != nullptr) {
            cout << left << setw(10) << no++ << setw(20) << temp->namaTim;

            AnggotaTim* tempAnggota = temp->anggotaTim;
            while (tempAnggota != nullptr) {
                cout << tempAnggota->nikke->nama;
                if (tempAnggota->next != nullptr)
                    cout << ", ";
                tempAnggota = tempAnggota->next;
            }

            cout << endl;
            temp = temp->next;
        }
    }
};

Stack stackNikke; 
Queue queueTim;    

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
    stackNikke.push(nikkeBaru); 
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
    stackNikke.printStack();  
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
    queueTim.enqueue(timBaru);  
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
    queueTim.printQueue();  
}


void hapusTim() {
    system("cls");
    if (jumlahTim == 0) {
        cout << "Belum ada Tim yang ditambahkan." << endl;
        return;
    }

    string namaTimDihapus;
    cout << "Masukkan nama tim yang ingin dihapus: ";
    getline(cin, namaTimDihapus);

    Tim* temp = headTim;
    Tim* prev = nullptr;

    while (temp != nullptr && temp->namaTim != namaTimDihapus) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == nullptr) {
        cout << "Tim tidak ditemukan." << endl;
        return;
    }

    if (prev == nullptr) {
        headTim = temp->next;
    } else {
        prev->next = temp->next;
    }

    delete temp;
    jumlahTim--;

    cout << "Tim berhasil dihapus." << endl;
}

void updateTim() {
    system("cls");
    if (jumlahTim == 0) {
        cout << "Belum ada Tim yang ditambahkan." << endl;
        return;
    }

    string namaTimDiupdate;
    cout << "Masukkan nama tim yang ingin diupdate: ";
    getline(cin, namaTimDiupdate);

    Tim* tempTim = headTim;

    while (tempTim != nullptr && tempTim->namaTim != namaTimDiupdate) {
        tempTim = tempTim->next;
    }

    if (tempTim == nullptr) {
        cout << "Tim tidak ditemukan." << endl;
        return;
    }

    cout << "Update anggota tim: " << tempTim->namaTim << endl;
    tampilkanSemuaNikke();

    cout << "Pilih 5 Nikke untuk anggota tim (input nomor Nikke):" << endl;
    
    AnggotaTim* newAnggotaTim = nullptr;
    
    for (int i = 0; i < 5; i++) {
        int pilihan;
        cout << "Pilih Nikke ke-" << (i + 1) << ": ";
        cin >> pilihan;
        cin.ignore();

        if (pilihan < 1 || pilihan > jumlahNikke) {
            cout << "Pilihan tidak valid." << endl;
            i--;
        } else {
            Nikke* tempNikke = headNikke;
            for (int j = 1; j < pilihan; j++) {
                tempNikke = tempNikke->next;
            }

            AnggotaTim* anggotaBaru = new AnggotaTim;
            anggotaBaru->nikke = tempNikke;
            anggotaBaru->next = newAnggotaTim;
            newAnggotaTim = anggotaBaru;
        }
    }

    
    tempTim->anggotaTim = newAnggotaTim;
    cout << "Anggota tim berhasil diupdate!" << endl;
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
        cout << "5. Hapus Tim" << endl;
        cout << "6. Update Tim" << endl;
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
                tambahTim();
                break;
            case 4:
                tampilkanSemuaTim();
                break;
            case 5:
                hapusTim();
                break;
            case 6:
                updateTim();
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
