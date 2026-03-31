#include <iostream>
#include <string>
using namespace std;

int main() {
    const int MAX_MOK = 100;
    const int MAX_PAZ = 10;

    string vardai[MAX_MOK];
    int pazymiai[MAX_MOK][MAX_PAZ];
    int kiekPaz[MAX_MOK];

    int mokKiekis = 0;
    int pasirinkimas;

    do {
        cout << "\n===== PAZYMIU PROGRAMA =====\n";
        cout << "1 - Naujas mokinys\n";
        cout << "2 - Rodyti visus\n";
        cout << "3 - Rodyti viena\n";
        cout << "0 - Iseiti\n";
        cout << ">>> ";
        cin >> pasirinkimas;

        switch (pasirinkimas) {

        case 1: {
            if (mokKiekis >= MAX_MOK) {
                cout << "Sarasas pilnas!\n";
                break;
            }

            cout << "Ivesk varda: ";
            cin >> vardai[mokKiekis];

            cout << "Kiek pazymiu: ";
            cin >> kiekPaz[mokKiekis];

            for (int j = 0; j < kiekPaz[mokKiekis]; j++) {
                cout << "Pazymys " << j + 1 << ": ";
                cin >> pazymiai[mokKiekis][j];
            }

            mokKiekis++;
            cout << "Prideta!\n";
            break;
        }

        case 2: {
            if (mokKiekis == 0) {
                cout << "Tuscia.\n";
                break;
            }

            for (int i = 0; i < mokKiekis; i++) {
                cout << vardai[i] << ": ";
                for (int j = 0; j < kiekPaz[i]; j++) {
                    cout << pazymiai[i][j] << " ";
                }
                cout << endl;
            }
            break;
        }

        case 3: {
            string v;
            bool rasta = false;

            cout << "Vardas: ";
            cin >> v;

            for (int i = 0; i < mokKiekis; i++) {
                if (vardai[i] == v) {
                    cout << vardai[i] << ": ";
                    for (int j = 0; j < kiekPaz[i]; j++) {
                        cout << pazymiai[i][j] << " ";
                    }
                    cout << endl;
                    rasta = true;
                }
            }

            if (!rasta) {
                cout << "Nerasta.\n";
            }
            break;
        }

        case 0:
            cout << "Baigta.\n";
            break;

        default:
            cout << "Blogas pasirinkimas.\n";
        }

    } while (pasirinkimas != 0);

    return 0;
}