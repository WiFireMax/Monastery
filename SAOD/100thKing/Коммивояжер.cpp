#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <string>

using namespace std;

int fill_matrix(double** matrix, int* x, int* y, int size)
{
	//float* matrix = new float[size];


	for (int i = 0; i < size; i++)
	{
		for (int k = 0; k < size; k++)
		{
			matrix[i][k] = ceil	(sqrt( abs (x[i] - x[k]) + abs (y[i] - y[k])) * 100) / 100;
		}
	}
	return **matrix;
}
 


double salesman(double** matrix, int size) 
{
	double best = INT_MAX;
	double summ = 0;
	int* way = new int[size];
	vector <int> d(size);
	iota(d.begin(), d.end(), 0);
	int res = 0;
	do {
		if (d[0] != 0)
		{
			continue;
		}

		for (int k = 0; k < (size - 1); k++)
		{
			//cout << d[k] << ' ';
			if (matrix[d[k]][d[k + 1]] == 0)
			{
				summ = INT_MAX;
				continue;
			}
			summ += matrix[d[k]][d[k + 1]];
		}

		if (summ < best)
		{
			best = summ;
			for (int z = 0; z < size; z++)
			{
				way[z] = d[z];
			}
		}
		summ = 0;
		reverse(d.begin() + size, d.end());
	} while (next_permutation(d.begin(), d.end()));

	cout << endl;
	cout << "Way: ";
	for (int i = 0; i < size; i++)
	{
		cout << way[i]+1 << ' ';
	}
	cout << endl << endl;
	cout << "Cost: " << best;
	cout << endl << endl;
	return 0;
}



int main()
{
	ifstream txt("D:/Исходники/САОД/Коммивояжер/Текст.txt", ios_base::in);
	setlocale(LC_ALL, "rus");

	while (!txt.is_open())
	{
		cout << "Файл не может быть открыт\n";
	}
		int size;
		txt >> size;
		int* x = new int[size];
		int* y = new int[size];
		double** matrix = new double* [size];
		for (int i = 0; i < size; i++)
		{
			matrix[i] = new double[size];
		}

		while (!txt.eof())
		{

			for (int k = 0; k < size; k++)
			{
				txt >> x[k] >> y[k];
			}
		}
		fill_matrix(matrix, x, y, size);

	txt.close();
	//cout << p << '\n';

	for (int i = 0; i < size; i++)
	{
		for (int k = 0; k < size; k++)
		{
			cout << "{" << matrix[i][k] << "} ";
		}
		cout << endl;
	}
	salesman(matrix, size);
}
