#include <iostream>
using namespace std;

int main()
{
    int a[5];
    int sum = 0;

//skaičiu ivedimas
    for(int i = 0; i < 5; i++)
    {
        cin >> a[i];
    }

    int max = a[0];
    int min = a[0];

//sumos skaičiavimas ir max,min paieįka
    for(int i = 0; i < 5; i++) {
        sum += a[i];

        if(a[i] > max)
            max = a[i];

        if(a[i] < min)
            min = a[i];
    };

//rezultato atvaizdavimas
    cout << "Suma: " << sum << endl;
    cout << "Didziausias: " << max << endl;
    cout << "Maziausias: " << min << endl;

    return 0;
}