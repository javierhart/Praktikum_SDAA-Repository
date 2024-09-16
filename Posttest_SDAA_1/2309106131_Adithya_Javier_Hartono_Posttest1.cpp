#include <iostream>
using namespace std;

void hanoitower(int n, char tiang_pertama, char tiang_kedua, char tiang_ketiga) {
    if (n == 1) {
        cout << "Pindahkan piringan 1 dari tiang " << tiang_pertama << " ke tiang " << tiang_kedua << endl;
        return;
    }
    hanoitower(n - 1, tiang_pertama, tiang_ketiga, tiang_kedua);
    cout << "Pindahkan piringan " << n << " dari tiang " << tiang_pertama << " ke tiang " << tiang_kedua << endl;
    hanoitower(n - 1, tiang_ketiga, tiang_kedua, tiang_pertama);
}

int main() {
    int n;
    cout << "Masukan jumlah piringan pada tiang pertama (Tiang A) = ";
    cin >> n;
    cout << string(50, '=') << endl;
    cout << "Proses:" << endl;
    hanoitower(n, 'A', 'C', 'B');
    return 0;
}
