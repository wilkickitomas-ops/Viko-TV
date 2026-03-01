#include <iostream>

using namespace std;

int main() {

    int pasirinkimas;
    float skaicius1, skaicius2;
//Kursas už 1 Eurą
    //GBP
    const float GBP_Bendras   = 0.8729;
    const float GBP_Pirkti    = 0.8600;
    const float GBP_Parduoti  = 0.9220;
    //USD
    const float USD_Bendras   = 1.1793;
    const float USD_Pirkti    = 1.1460;
    const float USD_Parduoti  = 1.2340;
    //Rupi
    const float INR_Bendras   = 104.6918;
    const float INR_Pirkti    = 101.3862;
    const float INR_Parduoti  = 107.8546;


    cout << "===Valiutos keityklos===" << endl;
    cout << "1 - Valiutos kurso palyginimas su kita valiuta" << endl;
    cout << "2 - Isigyti valiuta" << endl;
    cout << "3 - Parduoti valiuta" << endl;
    cin >> pasirinkimas;

    cout << "===Pasirinkit valiuta===" << endl;



    cout << "iveskite euro kieki" << endl;
    cin >> skaicius1;

    switch (pasirinkimas) {
        case 1:
            cout << skaicius1 << endl;
    }
    //test
}
