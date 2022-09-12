#include <iostream>
#include <vector>
#include <locale>
using namespace std;

vector <int> fenwick(200, 0);

void update(int i, int value, int limit) {
    for (int j = i + 1; j <= limit; j += (j & (-j))) {
        fenwick[j] += value;
    }
}

int sum(int i) {
    int result = 0;
    for (int j = i + 1; j >= 1; j -= (j & (-j))) {
        result += fenwick[j];
    }
    return result;
}

int main() {
    setlocale(LC_ALL, "RUS");
    int N, M, num1, num2;
    char ch;
    cout << "Введите количество чисел в массиве:" << endl;
    cin >> N;
    vector<int> arr(N);
    cout << "Введите числа через пробел:" << endl;
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
        update(i, arr[i], arr.size());
    }
    cout << "Введите количество запросов:" << endl;
    cin >> M;
    cout << "Введите запрос:" << endl;
    for (int i = 0; i < M; i++) {
        cin >> ch >> num1 >> num2;
        num1--; num2--;
        switch (ch) {
        case 's':
            cout << sum(num2) - sum(num1 - 1) << endl;
            break;
        case 'u':
            int diff = num2 - arr[num1];
            update(num1, diff, arr.size());
            break;
        }
    }
}
