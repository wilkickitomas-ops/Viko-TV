#include <iostream>

using namespace std;

int main() {

    int pasirinkimas, valiuta;
    string PavValuta;
    float bendras, pirkti, parduoti, kiekis, rezultatas;

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

//Pasirinkimo patikrinimas
    if (pasirinkimas >= 1, pasirinkimas <=3 ) {
    }
    else {
        cout << "tokio pasirinkimo nera" << endl;
        return 0;
    }

    cout << "===Pasirinkit valiuta===" << endl;
    cout << "1 - GBP (Svaras)" << endl;
    cout << "2 - USD (Doleris)" << endl;
    cout << "3 - INR (Rupija)" << endl;
    cin >> valiuta;

    switch (valiuta) {
        case 1:
            PavValuta = "GBP";
            bendras = GBP_Bendras;
            pirkti = GBP_Pirkti;
            parduoti = GBP_Parduoti;
            break;
        case 2:
            PavValuta = "USD";
            bendras = USD_Bendras;
            pirkti = USD_Pirkti;
            parduoti = USD_Parduoti;
            break;
        case 3:
            PavValuta = "INR";
            bendras = INR_Bendras;
            pirkti = INR_Pirkti;
            parduoti = INR_Parduoti;
            break;
        default:
            cout << "tokio pasirinkimo nera...";
            return 0;
    }
//Kurso palyginimas
    if (pasirinkimas == 1) {
        cout << "Valiutos " << PavValuta << " kursai:\n";
        cout << "Bendras kursas: " << bendras << endl;
        cout << "Pirkimo kursas: " << pirkti << endl;
        cout << "Pardavimo kursas: " << parduoti << endl;
    }
//valiutos pirkimas (EUR > valiuta)
    else if (pasirinkimas == 2) {
        cout << "kiek (EUR) norite apkeist:" << endl;

        cin >> kiekis;

        rezultatas =  pirkti * kiekis;

        cout << kiekis << " Eur = " << rezultatas << " " << PavValuta << endl;
        cout << "jusu galusit " << rezultatas << " " << PavValuta;
    }
//valiutos pardavimas (valiuta > EUR)
    else if (pasirinkimas == 3) {
        cout << "koki kieki norite parduot? \n" << PavValuta <<endl;

        cin >> kiekis;

        rezultatas = kiekis * parduoti;
        cout << kiekis << " " << PavValuta << " = " << rezultatas << " EUR";
    }
    else {
        cout << "nera tokio pasirinkimo";
    }
    return 0;
}
