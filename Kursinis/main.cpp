#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace chrono;

// Struktūra palyginimų ir perkėlimų statistikai saugoti
struct Stats {
    long long comparisons = 0;
    long long swaps = 0;
};

// Įterpimo rikiavimo algoritmas
void insertionSort(vector<int>& arr, Stats& stats) {
    int n = arr.size();

    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0) {
            stats.comparisons++;

            if (arr[j] > key) {
                arr[j + 1] = arr[j];
                stats.swaps++;
                j--;
            } else {
                break;
            }
        }

        arr[j + 1] = key;
    }
}

// Suliejimo funkcija sujungia dvi surikiuotas masyvo dalis
void merge(vector<int>& arr, int left, int mid, int right, Stats& stats) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1);
    vector<int> R(n2);

    // Kairės ir dešinės dalių kopijavimas
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];

    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    // Dviejų dalių suliejimas
    while (i < n1 && j < n2) {
        stats.comparisons++;

        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }

        stats.swaps++;
        k++;
    }

    // Likusių elementų kopijavimas iš kairės dalies
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
        stats.swaps++;
    }

    // Likusių elementų kopijavimas iš dešinės dalies
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
        stats.swaps++;
    }
}

// Rekursyvus Merge Sort algoritmas
void mergeSort(vector<int>& arr, int left, int right, Stats& stats) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid, stats);
        mergeSort(arr, mid + 1, right, stats);

        merge(arr, left, mid, right, stats);
    }
}

// Atsitiktinių duomenų generavimas
vector<int> generateRandomData(int size) {
    vector<int> data(size);

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, 1000000);

    for (int i = 0; i < size; i++) {
        data[i] = dist(gen);
    }

    return data;
}

// Jau surikiuotų duomenų generavimas
vector<int> generateSortedData(int size) {
    vector<int> data(size);

    for (int i = 0; i < size; i++) {
        data[i] = i + 1;
    }

    return data;
}

// Atvirkščiai surikiuotų duomenų generavimas
vector<int> generateReverseSortedData(int size) {
    vector<int> data(size);

    for (int i = 0; i < size; i++) {
        data[i] = size - i;
    }

    return data;
}

// Funkcija atlieka algoritmo testavimą ir apskaičiuoja vidurkius
void testAlgorithm(const vector<int>& originalData, const string& dataType, int size) {
    const int repetitions = 5;

    long long insertionTimeSum = 0;
    long long mergeTimeSum = 0;

    long long insertionComparisonsSum = 0;
    long long mergeComparisonsSum = 0;

    long long insertionSwapsSum = 0;
    long long mergeSwapsSum = 0;

    // Testas kartojamas 5 kartus
    for (int i = 0; i < repetitions; i++) {

        vector<int> data1 = originalData;
        vector<int> data2 = originalData;

        Stats insertionStats;
        Stats mergeStats;

        // Insertion Sort vykdymo laiko matavimas
        auto start1 = high_resolution_clock::now();
        insertionSort(data1, insertionStats);
        auto end1 = high_resolution_clock::now();

        // Merge Sort vykdymo laiko matavimas
        auto start2 = high_resolution_clock::now();
        mergeSort(data2, 0, data2.size() - 1, mergeStats);
        auto end2 = high_resolution_clock::now();

        insertionTimeSum += duration_cast<microseconds>(end1 - start1).count();
        mergeTimeSum += duration_cast<microseconds>(end2 - start2).count();

        insertionComparisonsSum += insertionStats.comparisons;
        mergeComparisonsSum += mergeStats.comparisons;

        insertionSwapsSum += insertionStats.swaps;
        mergeSwapsSum += mergeStats.swaps;
    }

    // Vidutinių rezultatų išvedimas
    cout << "Duomenu tipas: " << dataType << endl;
    cout << "Elementu kiekis: " << size << endl;

    cout << left << setw(18) << ""
         << setw(18) << "Laikas (us)"
         << setw(18) << "Palyginimas"
         << setw(18) << "Sukeitimai" << endl;

    cout << left << setw(18) << "Iterpimo sort"
         << setw(18) << insertionTimeSum / repetitions
         << setw(18) << insertionComparisonsSum / repetitions
         << setw(18) << insertionSwapsSum / repetitions << endl;

    cout << left << setw(18) << "Suliejimo sort"
         << setw(18) << mergeTimeSum / repetitions
         << setw(18) << mergeComparisonsSum / repetitions
         << setw(18) << mergeSwapsSum / repetitions << endl;

    cout << "------------------------------------------------------------" << endl;
}

int main() {

    // Testuojami trys duomenų dydžiai
    vector<int> sizes = {5000, 10000, 50000};

    for (int size : sizes) {

        // Sugeneruojami skirtingų tipų duomenys
        vector<int> randomData = generateRandomData(size);
        vector<int> sortedData = generateSortedData(size);
        vector<int> reverseData = generateReverseSortedData(size);

        // Atliekami visi eksperimentai
        testAlgorithm(randomData, "Nesurikiuoti duomenys", size);
        testAlgorithm(reverseData, "Atvirksciai surikiuoti duomenys", size);
        testAlgorithm(sortedData, "Jau surikiuoti duomenys", size);
    }

    return 0;
}