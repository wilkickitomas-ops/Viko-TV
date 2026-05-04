#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

const int MAX_ITEMS = 100;
const double VAT_RATE = 0.21;

struct menuItemType {
    string menuItem;   // patiekalo pavadinimas
    double menuPrice;  // patiekalo kaina
};

void getData(menuItemType menuList[], int& itemCount);
void showMenu(const menuItemType menuList[], int itemCount);
void printCheck(const menuItemType menuList[], int itemCount);

int main() {
    menuItemType menuList[MAX_ITEMS];
    int itemCount = 0;

    getData(menuList, itemCount);

    if (itemCount == 0) {
        cout << "Nepavyko nuskaityti meniu duomenu is failo menu.txt" << endl;
        return 1;
    }

    showMenu(menuList, itemCount);
    printCheck(menuList, itemCount);

    return 0;
}

void getData(menuItemType menuList[], int& itemCount) {
    ifstream fin("menu.txt");
    itemCount = 0;

    if (!fin) {
        return;
    }

    while (itemCount < MAX_ITEMS && getline(fin, menuList[itemCount].menuItem)) {
        fin >> menuList[itemCount].menuPrice;
        fin.ignore(1000, '\n');
        itemCount++;
    }

    fin.close();
}

void showMenu(const menuItemType menuList[], int itemCount) {
    cout << endl << "Sveiki atvyke i restorana Barbora piceria!!!" << endl;
    cout << "\nPusryciu meniu:\n";

    for (int i = 0; i < itemCount; i++) {
        cout << "  " << i + 1 << ". "
             << left << setw(35) << menuList[i].menuItem
             << right << fixed << setprecision(2) << menuList[i].menuPrice << " EUR" << endl;
    }

    cout << "\nKaip uzsakyti:" << endl;
    cout << "- Iveskite patiekalo numeri ir kieki." << endl;
    cout << "- Pvz.: 1 2 (reiskia 2 porcijos pirmo patiekalo)" << endl;
    cout << "- Baige uzsakyma iveskite 0 0" << endl;
}

void printCheck(const menuItemType menuList[], int itemCount) {
    ofstream fout("receipt.txt");

    if (!fout) {
        cout << "Nepavyko sukurti receipt.txt failo." << endl;
        return;
    }

    int choice, quantity;
    double subtotal = 0.0;

    int orderedItem[MAX_ITEMS];
    int orderedQty[MAX_ITEMS];
    int orderCount = 0;

    cout << endl;

    while (true) {
        cout << "Iveskite patiekalo numeri ir kieki: ";
        cin >> choice >> quantity;

        if (choice == 0 && quantity == 0) {
            break;
        }

        if (choice < 1 || choice > itemCount || quantity <= 0) {
            cout << "Neteisingas pasirinkimas. Bandykite dar karta." << endl;
            continue;
        }

        orderedItem[orderCount] = choice - 1;
        orderedQty[orderCount] = quantity;
        orderCount++;

        double itemTotal = menuList[choice - 1].menuPrice * quantity;
        subtotal += itemTotal;

        cout << quantity << "  "
             << left << setw(35) << menuList[choice - 1].menuItem
             << right << fixed << setprecision(2) << itemTotal << " EUR" << endl;
    }

    double vat = subtotal * VAT_RATE;
    double total = subtotal + vat;

    cout << endl << "Sveiki atvyke i restorana Barbora piceria" << endl;
    fout << "Sveiki atvyke i restorana Barbora piceria" << endl << endl;

    for (int i = 0; i < orderCount; i++) {
        int index = orderedItem[i];
        double itemTotal = menuList[index].menuPrice * orderedQty[i];

        cout << orderedQty[i] << "  "
             << left << setw(35) << menuList[index].menuItem
             << right << fixed << setprecision(2) << itemTotal << " EUR" << endl;

        fout << orderedQty[i] << "  "
             << left << setw(35) << menuList[index].menuItem
             << right << fixed << setprecision(2) << itemTotal << " EUR" << endl;
    }

    cout << endl;
    cout << "Suma be PVM:     " << fixed << setprecision(2) << subtotal << " EUR" << endl;
    cout << "Mokesciai (21%): " << fixed << setprecision(2) << vat << " EUR" << endl;
    cout << "Galutine suma:   " << fixed << setprecision(2) << total << " EUR" << endl;

    fout << endl;
    fout << "Suma be PVM:     " << fixed << setprecision(2) << subtotal << " EUR" << endl;
    fout << "Mokesciai (21%): " << fixed << setprecision(2) << vat << " EUR" << endl;
    fout << "Galutine suma:   " << fixed << setprecision(2) << total << " EUR" << endl;

    fout.close();

    cout << "\nSaskaita issaugota faile receipt.txt" << endl;
}