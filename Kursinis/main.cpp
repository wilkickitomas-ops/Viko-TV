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

int main() {
    cout << "Data generation ready." << endl;
    return 0;
}