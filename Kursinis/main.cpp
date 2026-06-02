#include <iostream>
#include <vector>
#include <random>

using namespace std;

struct Stats {
    long long comparisons = 0;
    long long swaps = 0;
};

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

vector<int> generateSortedData(int size) {
    vector<int> data(size);

    for (int i = 0; i < size; i++) {
        data[i] = i + 1;
    }

    return data;
}

vector<int> generateReverseSortedData(int size) {
    vector<int> data(size);

    for (int i = 0; i < size; i++) {
        data[i] = size - i;
    }

    return data;
}

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
            }
            else {
                break;
            }
        }

        arr[j + 1] = key;
    }
}

void merge(vector<int>& arr, int left, int mid, int right, Stats& stats) {

    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1);
    vector<int> R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];

    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2) {

        stats.comparisons++;

        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }

        stats.swaps++;
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
        stats.swaps++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
        stats.swaps++;
    }
}

void mergeSort(vector<int>& arr, int left, int right, Stats& stats) {

    if (left < right) {

        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid, stats);
        mergeSort(arr, mid + 1, right, stats);

        merge(arr, left, mid, right, stats);
    }
}

int main() {

    vector<int> data = generateRandomData(20);

    vector<int> data1 = data;
    vector<int> data2 = data;

    Stats insertionStats;
    Stats mergeStats;

    cout << "Pirmines doumenis:" << endl;

    for (int num : data) {
        cout << num << " ";
    }

    cout << endl << endl;

    insertionSort(data1, insertionStats);

    cout << "Iterpimo sorteravimo rezultatai:" << endl;

    for (int num : data1) {
        cout << num << " ";
    }

    cout << endl;
    cout << "Palyginimai: " << insertionStats.comparisons << endl;
    cout << "Apkeitimai: " << insertionStats.swaps << endl;

    cout << endl;

    mergeSort(data2, 0, data2.size() - 1, mergeStats);

    cout << "Sulejimo sorteravimo rezultatai:" << endl;

    for (int num : data2) {
        cout << num << " ";
    }

    cout << endl;
    cout << "palyginimai: " << mergeStats.comparisons << endl;
    cout << "Apkeitimai: " << mergeStats.swaps << endl;

    return 0;
}