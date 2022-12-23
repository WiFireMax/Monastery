#include <iostream>
#include <locale>
using namespace std;

//Веса ребер
struct Edge {
	int src, dest, weight;
};

//Взвешенный направленный граф
struct Graph {
	int V, E;

	struct Edge* edge;
};

struct Graph* createGraph(int V, int E)
{
	struct Graph* graph = new Graph;
	graph->V = V;
	graph->E = E;
	graph->edge = new Edge[E];
	return graph;
}

void printArr(int dist[], int n)
{
	printf("Дистанция от первой вершины до любой другой: \n");
	for (int i = 0; i < n; ++i)
		printf("%d \t\t %d\n", i+1, dist[i]);
}

// Алгоритм находит кратчайшие пути из src в остальные вершины
void BellmanFord(struct Graph* graph, int src)
{
	int V = graph->V;
	int E = graph->E;
	int *dist = new int[V];

	//Шаг 1: установить расстояния до всех вершин равное бесконечности
	for (int i = 0; i < V; i++)
		dist[i] = INT_MAX;
	dist[src] = 0;

	// Шаг 2: Обработать все ребра V - 1 раз
	for (int i = 1; i <= V - 1; i++) {
		for (int j = 0; j < E; j++) {
			int u = graph->edge[j].src;
			int v = graph->edge[j].dest;
			int weight = graph->edge[j].weight;
			if (dist[u] != INT_MAX
				&& dist[u] + weight < dist[v])
				dist[v] = dist[u] + weight;
		}
	}

	// Шаг 3: поиск циклов отрицательного веса
	for (int i = 0; i < E; i++) {
		int u = graph->edge[i].src;
		int v = graph->edge[i].dest;
		int weight = graph->edge[i].weight;
		if (dist[u] != INT_MAX
			&& dist[u] + weight < dist[v]) {
			printf("Граф содержит отрицательный цикл");
			return;
		}
	}

	printArr(dist, V);

	return;
}

int main()
{
	setlocale(LC_ALL, "rus");
	int V, E, source, destination, weight;
	cout << "Введите количество вершин и граней графа: ";
	cin >> V >> E;
	struct Graph* graph = createGraph(V, E);
	for (int i = 0; i < E; i++) {
		cout << "Создание грани " << i + 1 << endl << "Введите начальную вершину, конечную вершину и вес грани через пробел: ";
		cin >> source >> destination >> weight;
		graph->edge[i].src = source - 1;
		graph->edge[i].dest = destination - 1;
		graph->edge[i].weight = weight;
	}
	
	BellmanFord(graph, 0);

	return 0;
}
