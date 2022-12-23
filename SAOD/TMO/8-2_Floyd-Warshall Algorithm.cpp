#include <iostream>
#include <locale>
using namespace std;

//Бесконечность
#define INF 999

void printMatrix(int **matrix, int V);

void floydWarshall(int **graph, int V, int E) {
    int** grph = new int* [V]; //Строки
    for (int count = 0; count < V; count++)
        grph[count] = new int[V]; //Столбцы
        
        int i, j, k;

    for (i = 0; i < V; i++)
        for (j = 0; j < V; j++)
            grph[i][j] = graph[i][j];
    bool flag = true;
    // Обработка ребер
    for (k = 0; k < V; k++) {
        for (i = 0; i < V; i++) {
            for (j = 0; j < V; j++) {
                if (grph[i][k] + grph[k][j] < grph[i][j])
                    grph[i][j] = grph[i][k] + grph[k][j];
            }
        }
    }
    for (k = 0; k < V; k++) {
        for (i = 0; i < V; i++) {
            for (j = 0; j < V; j++) {
                if (grph[i][k] + grph[k][j] < grph[i][j]) {
                    flag = false;
                }
            }
        }
    }
    if (flag == true) {
        printMatrix(grph, V);
    }
    else { cout << "Граф содержит отрицательный цикл"; return; }
}

void printMatrix(int **matrix, int V) {
    cout << "Матрица путей: " << endl;
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (matrix[i][j] == INF)
                printf("%4s", "INF");
            else
                printf("%4d", matrix[i][j]);
        }
        printf("\n");
    }
}
//Матрица
// [] [1] [2] [3] [4]
// [1] 0   3  INF  5
// [2] 2   0  INF  4
// [3] INF 3   0  INF
// [4] INF INF 2   0
//Соответствует графу
//  [1]--5-->[4]
// /\|      /\ |
// | |     /   |
// | |    4    2
// 2 4   /     |
// | |  /      |
// |\/ /      \/
// [2]<---1---[3]
//


int main() {
    setlocale(LC_ALL, "rus");
    int V, E, tmp_src, tmp_dest, tmp_val;
    cout << "Введите количество вершин и ребер через пробел: " << endl;  cin >> V >> E;
    int** grph = new int* [V]; //Строки
    for (int count = 0; count < V; count++)
        grph[count] = new int[V]; //Столбцы
    for (int i = 0; i < V; i++) for (int j = 0; j < V; j++) grph[i][j] = INF;
    for (int i = 0; i < V; i++) {
        grph[i][i] = 0;
    }
    for (int i = 0; i < E; i++) {
        cout << "Введите ребро " << i + 1 << endl;
        cin >> tmp_src >> tmp_dest >> tmp_val;
        tmp_src--; tmp_dest--;
        grph[tmp_src][tmp_dest] = tmp_val;
    }
    floydWarshall(grph, V, E);
}
