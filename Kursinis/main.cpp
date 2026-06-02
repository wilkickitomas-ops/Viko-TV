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

int main() {

    vector<int> data = generateRandomData(20);

    Stats stats;

    insertionSort(data, stats);

    cout << "Iterpimo algoritmas" << endl;

    cout << "pries sortiravima: ";

    for (int num : data) {
        cout << num << " ";
    }

    cout << endl;

    insertionSort(data, stats);

    cout << "po sortiravimo: ";

    for (int num : data) {
        cout << num << " ";
    }

    cout << endl;

    cout << "paliginimai: " << stats.comparisons << endl;
    cout << "apkeitimai: " << stats.swaps << endl;

    return 0;
}