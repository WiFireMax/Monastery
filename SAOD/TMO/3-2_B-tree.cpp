#include <iostream>
#include <stdlib.h>
using namespace std;
#define M 3 //Порядок дерева


typedef struct _node {
    int    n; //n < M Количество ключей в узле всегда будет меньше порядка дерева
    int    keys[M - 1]; //Массив ключей
    struct _node* p[M]; //Будет использовано (n+1) = M указателей
} node;
node* root = NULL;

typedef enum KeyStatus {
    Duplicate,
    SearchFailure,
    Success,
    InsertIt,
    LessKeys,
} KeyStatus;

void insert(int key);
void display(node* root, int);
void DelNode(int x);
KeyStatus ins(node* r, int x, int* y, node** u);
int searchPos(int x, int* key_arr, int n);
KeyStatus del(node* r, int x);
void eatline(void);

int main() {
    setlocale(LC_ALL, "rus");
    int key;
    int choice;
    cout << "Создание Би-дерева для M=" << M << endl;
    while (1) {
        cout << "1.Вставка" << endl;
        cout << "2.Удаление" << endl;
        cout << "3.Вывести" << endl;
        cin >> choice; eatline();

        switch (choice) {
        case 1:
            cout << "Введите ключ : ";
            cin >> key; eatline();
            insert(key);
            break;
        case 2:
            cout << "Введите ключ : ";
            cin >> key; eatline();
            DelNode(key);
            break;
        case 3:
            cout << "Дерево :" << endl;
            display(root, 0);
            break;
        default:
            cout << "Неправильный выбор\n";
            break;
        }
    }
    return 0;
}

void insert(int key) {
    node* newnode;
    int upKey;
    KeyStatus value;
    value = ins(root, key, &upKey, &newnode);
    if (value == Duplicate)
        cout << "Ключ уже имеется" << endl;
    if (value == InsertIt) {
        node* uproot = root;
        root = new node;
        root->n = 1;
        root->keys[0] = upKey;
        root->p[0] = uproot;
        root->p[1] = newnode;
    }
}

KeyStatus ins(node* ptr, int key, int* upKey, node** newnode) {
    node* newPtr, * lastPtr;
    int pos, i, n, splitPos;
    int newKey, lastKey;
    KeyStatus value;
    if (ptr == NULL) {
        *newnode = NULL;
        *upKey = key;
        return InsertIt;
    }
    n = ptr->n;
    pos = searchPos(key, ptr->keys, n);
    if (pos < n && key == ptr->keys[pos])
        return Duplicate;
    value = ins(ptr->p[pos], key, &newKey, &newPtr);
    if (value != InsertIt)
        return value;
    //Если ключей в узле меньше, чем М-1, где М порядок Би-дерева
    if (n < M - 1) {
        pos = searchPos(newKey, ptr->keys, n);
        //Смещение указателя вправо для вставки нового ключа
        for (i = n; i > pos; i--) {
            ptr->keys[i] = ptr->keys[i - 1];
            ptr->p[i + 1] = ptr->p[i];
        }
        //Установка ключа в нынешнее место
        ptr->keys[pos] = newKey;
        ptr->p[pos + 1] = newPtr;
        ++ptr->n; //Увеличиваем количество ключей в узле
        return Success;
    }
     //Если в узле максимальное количество ключей и указатель стоит на последнем
    if (pos == M - 1) {
        lastKey = newKey;
        lastPtr = newPtr;
    }
    else { //Если в узле максимальное количество ключей и указатель стоит не на последнем
        lastKey = ptr->keys[M - 2];
        lastPtr = ptr->p[M - 1];
        for (i = M - 2; i > pos; i--) {
            ptr->keys[i] = ptr->keys[i - 1];
            ptr->p[i + 1] = ptr->p[i];
        }
        ptr->keys[pos] = newKey;
        ptr->p[pos + 1] = newPtr;
    }
    splitPos = (M - 1) / 2;
    (*upKey) = ptr->keys[splitPos];

    (*newnode) = new node; //Правый узел после разделения
    ptr->n = splitPos; //Количество ключей для левого разделенного узла
    (*newnode)->n = M - 1 - splitPos; //Количество ключей для правого разделенного узла
    for (i = 0; i < (*newnode)->n; i++) {
        (*newnode)->p[i] = ptr->p[i + splitPos + 1];
        if (i < (*newnode)->n - 1)
            (*newnode)->keys[i] = ptr->keys[i + splitPos + 1];
        else
            (*newnode)->keys[i] = lastKey;
    }
    (*newnode)->p[(*newnode)->n] = lastPtr;
    return InsertIt;
}

void display(node* ptr, int blanks) {
    if (ptr) {
        int i;
        for (i = 1; i <= blanks; i++)
            cout << " ";
        for (i = 0; i < ptr->n; i++)
            cout << " " << ptr->keys[i];
        cout << "\n";
        for (i = 0; i <= ptr->n; i++)
            display(ptr->p[i], blanks + 10);
    }
}

int searchPos(int key, int* key_arr, int n) {
    int pos = 0;
    while (pos < n && key > key_arr[pos])
        pos++;
    return pos;
}

void DelNode(int key) {
    node* uproot;
    KeyStatus value;
    value = del(root, key);
    switch (value) {
    case SearchFailure:
        cout << "Ключ " << key << " недоступен" << endl;
        break;
    case LessKeys:
        uproot = root;
        root = root->p[0];
        free(uproot);
        break;
    default:
        return;
    }
}

KeyStatus del(node* ptr, int key) {
    int pos, i, pivot, n, min;
    int* key_arr;
    KeyStatus value;
    node** p, * lptr, * rptr;

    if (ptr == NULL)
        return SearchFailure;
    //Назначение значений узла
    n = ptr->n;
    key_arr = ptr->keys;
    p = ptr->p;
    min = (M - 1) / 2; //Минимальное количество ключей

    //Поиск ключа для удаления
    pos = searchPos(key, key_arr, n);
    //Если р листок
    if (p[0] == NULL) {
        if (pos == n || key < key_arr[pos])
            return SearchFailure;
        /*Shift keys and pointers left*/
        for (i = pos + 1; i < n; i++)
        {
            key_arr[i - 1] = key_arr[i];
            p[i] = p[i + 1];
        }
        return --ptr->n >= (ptr == root ? 1 : min) ? Success : LessKeys;
    }

     //Если ключ найден, но p не является листком
    if (pos < n && key == key_arr[pos]) {
        node* qp = p[pos], * qp1;
        int nkey;
        while (1) {
            nkey = qp->n;
            qp1 = qp->p[nkey];
            if (qp1 == NULL)
                break;
            qp = qp1;
        }
        key_arr[pos] = qp->keys[nkey - 1];
        qp->keys[nkey - 1] = key;
    }
    value = del(p[pos], key);
    if (value != LessKeys)
        return value;

    if (pos > 0 && p[pos - 1]->n > min) {
        pivot = pos - 1; //Вращение для левого и правого узла
        lptr = p[pivot];
        rptr = p[pos];
        //Назначение значений для правого узла
        rptr->p[rptr->n + 1] = rptr->p[rptr->n];
        for (i = rptr->n; i > 0; i--) {
            rptr->keys[i] = rptr->keys[i - 1];
            rptr->p[i] = rptr->p[i - 1];
        }
        rptr->n++;
        rptr->keys[0] = key_arr[pivot];
        rptr->p[0] = lptr->p[lptr->n];
        key_arr[pivot] = lptr->keys[--lptr->n];
        return Success;
    }
     //if (posn > min)
    if (pos < n && p[pos + 1]->n > min) {
        pivot = pos; //Вращение для левого и правого узла
        lptr = p[pivot];
        rptr = p[pivot + 1];
        //Назначение значений для левого узла
        lptr->keys[lptr->n] = key_arr[pivot];
        lptr->p[lptr->n + 1] = rptr->p[0];
        key_arr[pivot] = rptr->keys[0];
        lptr->n++;
        rptr->n--;
        for (i = 0; i < rptr->n; i++) {
            rptr->keys[i] = rptr->keys[i + 1];
            rptr->p[i] = rptr->p[i + 1];
        }
        rptr->p[rptr->n] = rptr->p[rptr->n + 1];
        return Success;
    }

    if (pos == n)
        pivot = pos - 1;
    else
        pivot = pos;

    lptr = p[pivot];
    rptr = p[pivot + 1];
    //Объединение правого и левого узлов
    lptr->keys[lptr->n] = key_arr[pivot];
    lptr->p[lptr->n + 1] = rptr->p[0];
    for (i = 0; i < rptr->n; i++) {
        lptr->keys[lptr->n + 1 + i] = rptr->keys[i];
        lptr->p[lptr->n + 2 + i] = rptr->p[i + 1];
    }
    lptr->n = lptr->n + rptr->n + 1;
    free(rptr); //Удаление правого узла
    for (i = pos + 1; i < n; i++) {
        key_arr[i - 1] = key_arr[i];
        p[i] = p[i + 1];
    }
    return --ptr->n >= (ptr == root ? 1 : min) ? Success : LessKeys;
}

void eatline(void) {
    char c;
    while ((c = getchar()) != '\n');
}
