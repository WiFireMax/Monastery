#include <iostream>
#include <math.h>
using namespace std;
/*
arr - основной массив со значениями
n - размер массивов
curr_elements - логический массив, в котором с помощью 0 и 1 идет разделение массива arr
no_of_selected_elements - кол-во 1 в curr_elements для прерывания функции
soln - логический массив, в который записывается лучшее решение
min_diff - разность полусуммы arr от суммы curr_sum
sum - сумма массива arr
curr_sum - сумма элементов со значением 1 в curr_elements
curr_position - текущий индекс в массиве
*/
void func(int* arr, int n, bool* curr_elements, int no_of_selected_elements,
    bool* soln, int* min_diff, int sum, int curr_sum, int curr_position)
{
    // Проверка выхода за границу
    if (curr_position == n)
        return;

    // Если кол-во оставшихся эл-ов меньше половины
    if ((n / 2 - no_of_selected_elements) > (n - curr_position))
        return;

    // Если текущий элемент не добавлен
    func(arr, n, curr_elements, no_of_selected_elements,
        soln, min_diff, sum, curr_sum, curr_position + 1);

    // Добавить элемент в массив 
    no_of_selected_elements++;
    curr_sum = curr_sum + arr[curr_position];
    curr_elements[curr_position] = true;

    // Если кол-во элементов достаточно
    if (no_of_selected_elements == n / 2)
    {
        // Проверка на схожесть сумм
        if (abs(sum / 2 - curr_sum) < *min_diff)
        {
            *min_diff = abs(sum / 2 - curr_sum);
            for (int i = 0; i < n; i++)
                soln[i] = curr_elements[i];
        }
    }
    else
    {
        // Если текущий элемент добавлен
        func(arr, n, curr_elements, no_of_selected_elements, soln,
            min_diff, sum, curr_sum, curr_position + 1);
    }

    // Убирает current element 
    curr_elements[curr_position] = false;
}

// Создание вспомогательных массивов
void tugOfWar(int* arr, int n)
{
    bool* curr_elements = new bool[n];

    bool* soln = new bool[n];

    int min_diff = INT_MAX;

    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += arr[i];
        curr_elements[i] = soln[i] = false;
    }

    func(arr, n, curr_elements, 0, soln, &min_diff, sum, 0, 0);

    // Вывод
    cout << "Первое множество: ";
    int new_sum=0;
    for (int i = 0; i < n; i++)
    {
        if (soln[i] == true)
        {
            cout << arr[i] << " ";
            new_sum += arr[i];
        }
    }
    cout << "= " << new_sum;
    cout << "\nВторое множество: ";
    new_sum = 0;
    for (int i = 0; i < n; i++)
    {
        if (soln[i] == false)
        {
            cout << arr[i] << " ";
            new_sum += arr[i];
        }
    }
    cout << "= " << new_sum;
}

int main()
{
    setlocale(LC_ALL, "rus");
    int n;
    while (true)
    {

        cout << "Введите размер массива кратный двум: ";
        cin >> n;
        if (n % 2 != 0)
        {
            cout << "Ошибка при вводе" << endl;
        }
        else
        {
            break;
        }
    }
    int *arr = new int[n];
    srand(time(NULL));
    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % 100 + 1;
        cout << "[" << arr[i] << "] ";
    }
    cout << endl;
    tugOfWar(arr, n);
    return 0;
}
