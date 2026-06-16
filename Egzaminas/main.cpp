#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

// Struktūra vieno filmo duomenims saugoti
struct Filmas {
    int id;
    string pavadinimas;
    string zanras;
    int metai;
    double ivertinimas;
    int trukme;
};

// Funkcijų prototipai
void nuskaitytiIsFailo(vector<Filmas>& filmai, const string& failoPavadinimas);
void issaugotiIFaila(const vector<Filmas>& filmai, const string& failoPavadinimas);
void rodytiMeniu();
void rodytiVisusFilmus(const vector<Filmas>& filmai);
void rodytiVienaFilma(const Filmas& filmas);
void pridetiFilma(vector<Filmas>& filmai);
void redaguotiFilma(vector<Filmas>& filmai);
void istrintiFilma(vector<Filmas>& filmai);
void ieskotiPagalPavadinima(const vector<Filmas>& filmai);
void filtruotiPagalZanra(const vector<Filmas>& filmai);
void rikiuotiPagalIvertinima(vector<Filmas>& filmai);
void rodytiStatistika(const vector<Filmas>& filmai);
int gautiNaujaId(const vector<Filmas>& filmai);
int rastiFilmoIndeksaPagalId(const vector<Filmas>& filmai, int id);
int ivestiSveikaSkaiciu(const string& tekstas);
double ivestiSkaiciuSuKableliu(const string& tekstas);

int main() {
    vector<Filmas> filmai;
    string failoPavadinimas = "filmai.txt";
    int pasirinkimas;

    nuskaitytiIsFailo(filmai, failoPavadinimas);

    do {
        rodytiMeniu();
        pasirinkimas = ivestiSveikaSkaiciu("Pasirinkite veiksma: ");

        switch (pasirinkimas) {
            case 1:
                rodytiVisusFilmus(filmai);
                break;
            case 2:
                pridetiFilma(filmai);
                break;
            case 3:
                redaguotiFilma(filmai);
                break;
            case 4:
                istrintiFilma(filmai);
                break;
            case 5:
                ieskotiPagalPavadinima(filmai);
                break;
            case 6:
                filtruotiPagalZanra(filmai);
                break;
            case 7:
                rikiuotiPagalIvertinima(filmai);
                rodytiVisusFilmus(filmai);
                break;
            case 8:
                rodytiStatistika(filmai);
                break;
            case 9:
                issaugotiIFaila(filmai, failoPavadinimas);
                cout << "Duomenys issaugoti. Programa baigta." << endl;
                break;
            default:
                cout << "Neteisingas pasirinkimas. Bandykite dar karta." << endl;
        }

        cout << endl;
    } while (pasirinkimas != 9);

    return 0;
}

// Duomenų nuskaitymas iš tekstinio failo
void nuskaitytiIsFailo(vector<Filmas>& filmai, const string& failoPavadinimas) {
    ifstream failas(failoPavadinimas);

    if (!failas.is_open()) {
        cout << "Nepavyko atidaryti failo: " << failoPavadinimas << endl;
        cout << "Programa prades darba su tusciu sarasu." << endl;
        return;
    }

    string eilute;

    while (getline(failas, eilute)) {
        if (eilute.empty()) {
            continue;
        }

        stringstream ss(eilute);
        string dalis;
        Filmas filmas;

        getline(ss, dalis, ';');
        filmas.id = stoi(dalis);

        getline(ss, filmas.pavadinimas, ';');
        getline(ss, filmas.zanras, ';');

        getline(ss, dalis, ';');
        filmas.metai = stoi(dalis);

        getline(ss, dalis, ';');
        filmas.ivertinimas = stod(dalis);

        getline(ss, dalis, ';');
        filmas.trukme = stoi(dalis);

        filmai.push_back(filmas);
    }

    failas.close();
}

// Duomenų įrašymas į tekstinį failą
void issaugotiIFaila(const vector<Filmas>& filmai, const string& failoPavadinimas) {
    ofstream failas(failoPavadinimas);

    if (!failas.is_open()) {
        cout << "Nepavyko issaugoti duomenu i faila." << endl;
        return;
    }

    for (const Filmas& filmas : filmai) {
        failas << filmas.id << ";"
               << filmas.pavadinimas << ";"
               << filmas.zanras << ";"
               << filmas.metai << ";"
               << filmas.ivertinimas << ";"
               << filmas.trukme << endl;
    }

    failas.close();
}

void rodytiMeniu() {
    cout << "==============================" << endl;
    cout << "      FILMU KATALOGAS" << endl;
    cout << "==============================" << endl;
    cout << "1. Rodyti visus filmus" << endl;
    cout << "2. Prideti nauja filma" << endl;
    cout << "3. Redaguoti filma" << endl;
    cout << "4. Istrinti filma" << endl;
    cout << "5. Ieskoti pagal pavadinima" << endl;
    cout << "6. Filtruoti pagal zanra" << endl;
    cout << "7. Rikiuoti pagal ivertinima" << endl;
    cout << "8. Rodyti statistika" << endl;
    cout << "9. Issaugoti ir baigti" << endl;
    cout << "==============================" << endl;
}

void rodytiVisusFilmus(const vector<Filmas>& filmai) {
    if (filmai.empty()) {
        cout << "Filmu sarasas tuscias." << endl;
        return;
    }

    cout << left << setw(5) << "ID"
         << setw(28) << "Pavadinimas"
         << setw(15) << "Zanras"
         << setw(8) << "Metai"
         << setw(13) << "Ivertinimas"
         << setw(10) << "Trukme" << endl;

    cout << string(79, '-') << endl;

    for (const Filmas& filmas : filmai) {
        rodytiVienaFilma(filmas);
    }
}

void rodytiVienaFilma(const Filmas& filmas) {
    cout << left << setw(5) << filmas.id
         << setw(28) << filmas.pavadinimas
         << setw(15) << filmas.zanras
         << setw(8) << filmas.metai
         << setw(13) << filmas.ivertinimas
         << setw(10) << filmas.trukme << endl;
}

void pridetiFilma(vector<Filmas>& filmai) {
    Filmas naujas;
    naujas.id = gautiNaujaId(filmai);

    cin.ignore();
    cout << "Iveskite filmo pavadinima: ";
    getline(cin, naujas.pavadinimas);

    cout << "Iveskite zanra: ";
    getline(cin, naujas.zanras);

    naujas.metai = ivestiSveikaSkaiciu("Iveskite metus: ");
    naujas.ivertinimas = ivestiSkaiciuSuKableliu("Iveskite ivertinima nuo 0 iki 10: ");
    naujas.trukme = ivestiSveikaSkaiciu("Iveskite trukme minutemis: ");

    filmai.push_back(naujas);
    cout << "Filmas sekmingai pridetas." << endl;
}

void redaguotiFilma(vector<Filmas>& filmai) {
    int id = ivestiSveikaSkaiciu("Iveskite redaguojamo filmo ID: ");
    int indeksas = rastiFilmoIndeksaPagalId(filmai, id);

    if (indeksas == -1) {
        cout << "Filmas su tokiu ID nerastas." << endl;
        return;
    }

    cin.ignore();
    cout << "Naujas pavadinimas: ";
    getline(cin, filmai[indeksas].pavadinimas);

    cout << "Naujas zanras: ";
    getline(cin, filmai[indeksas].zanras);

    filmai[indeksas].metai = ivestiSveikaSkaiciu("Nauji metai: ");
    filmai[indeksas].ivertinimas = ivestiSkaiciuSuKableliu("Naujas ivertinimas: ");
    filmai[indeksas].trukme = ivestiSveikaSkaiciu("Nauja trukme minutemis: ");

    cout << "Filmo duomenys atnaujinti." << endl;
}

void istrintiFilma(vector<Filmas>& filmai) {
    int id = ivestiSveikaSkaiciu("Iveskite trinamo filmo ID: ");
    int indeksas = rastiFilmoIndeksaPagalId(filmai, id);

    if (indeksas == -1) {
        cout << "Filmas su tokiu ID nerastas." << endl;
        return;
    }

    filmai.erase(filmai.begin() + indeksas);
    cout << "Filmas istrintas." << endl;
}

void ieskotiPagalPavadinima(const vector<Filmas>& filmai) {
    cin.ignore();
    string tekstas;
    bool rasta = false;

    cout << "Iveskite pavadinimo dali: ";
    getline(cin, tekstas);

    transform(tekstas.begin(), tekstas.end(), tekstas.begin(), ::tolower);

    cout << "Paieskos rezultatai:" << endl;

    for (const Filmas& filmas : filmai) {
        string pavadinimas = filmas.pavadinimas;
        transform(pavadinimas.begin(), pavadinimas.end(), pavadinimas.begin(), ::tolower);

        if (pavadinimas.find(tekstas) != string::npos) {
            rodytiVienaFilma(filmas);
            rasta = true;
        }
    }

    if (!rasta) {
        cout << "Pagal nurodyta teksta filmu nerasta." << endl;
    }
}

void filtruotiPagalZanra(const vector<Filmas>& filmai) {
    cin.ignore();
    string zanras;
    bool rasta = false;

    cout << "Iveskite zanra: ";
    getline(cin, zanras);

    transform(zanras.begin(), zanras.end(), zanras.begin(), ::tolower);

    cout << "Filmai pagal pasirinkta zanra:" << endl;

    for (const Filmas& filmas : filmai) {
        string filmoZanras = filmas.zanras;
        transform(filmoZanras.begin(), filmoZanras.end(), filmoZanras.begin(), ::tolower);

        if (filmoZanras == zanras) {
            rodytiVienaFilma(filmas);
            rasta = true;
        }
    }

    if (!rasta) {
        cout << "Tokio zanro filmu nerasta." << endl;
    }
}

void rikiuotiPagalIvertinima(vector<Filmas>& filmai) {
    sort(filmai.begin(), filmai.end(), [](const Filmas& a, const Filmas& b) {
        return a.ivertinimas > b.ivertinimas;
    });

    cout << "Filmai surikiuoti pagal ivertinima mazejimo tvarka." << endl;
}

void rodytiStatistika(const vector<Filmas>& filmai) {
    if (filmai.empty()) {
        cout << "Nera filmu statistikai skaiciuoti." << endl;
        return;
    }

    double suma = 0;
    int bendraTrukme = 0;
    Filmas geriausias = filmai[0];
    Filmas ilgiausias = filmai[0];

    for (const Filmas& filmas : filmai) {
        suma += filmas.ivertinimas;
        bendraTrukme += filmas.trukme;

        if (filmas.ivertinimas > geriausias.ivertinimas) {
            geriausias = filmas;
        }

        if (filmas.trukme > ilgiausias.trukme) {
            ilgiausias = filmas;
        }
    }

    cout << fixed << setprecision(2);
    cout << "Filmu kiekis: " << filmai.size() << endl;
    cout << "Vidutinis ivertinimas: " << suma / filmai.size() << endl;
    cout << "Bendra filmu trukme: " << bendraTrukme << " min." << endl;
    cout << "Geriausiai ivertintas filmas: " << geriausias.pavadinimas
         << " (" << geriausias.ivertinimas << ")" << endl;
    cout << "Ilgiausias filmas: " << ilgiausias.pavadinimas
         << " (" << ilgiausias.trukme << " min.)" << endl;
}

int gautiNaujaId(const vector<Filmas>& filmai) {
    int didziausiasId = 0;

    for (const Filmas& filmas : filmai) {
        if (filmas.id > didziausiasId) {
            didziausiasId = filmas.id;
        }
    }

    return didziausiasId + 1;
}

int rastiFilmoIndeksaPagalId(const vector<Filmas>& filmai, int id) {
    for (int i = 0; i < (int)filmai.size(); i++) {
        if (filmai[i].id == id) {
            return i;
        }
    }

    return -1;
}

int ivestiSveikaSkaiciu(const string& tekstas) {
    int skaicius;

    while (true) {
        cout << tekstas;
        cin >> skaicius;

        if (!cin.fail()) {
            return skaicius;
        }

        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Klaida. Iveskite sveikaji skaiciu." << endl;
    }
}

double ivestiSkaiciuSuKableliu(const string& tekstas) {
    double skaicius;

    while (true) {
        cout << tekstas;
        cin >> skaicius;

        if (!cin.fail()) {
            return skaicius;
        }

        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Klaida. Iveskite skaiciu." << endl;
    }
}
