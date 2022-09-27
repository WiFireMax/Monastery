#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<locale.h>

/* Узел АВЛ - дерева */
struct Node
{
    int key;
    struct Node* left;
    struct Node* right;
    int height;
};


/* Высота дерева */
int height(struct Node* N)
{
    if (N == NULL)
        return 0;
    return 1 + maximum(height(N->left), height(N->right));
}


int maximum(int a, int b)
{
    return (a > b) ? a : b;
}

/* Выделяет новый узел с заданным ключом и нулевыми левыми и правыми указателями. */
struct Node* newNode(int key)
{
    struct Node* node = (struct Node*)
        malloc(sizeof(struct Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 0; // Новый узел в конец
    return(node);
}

/* Правый поворот */
struct Node* rightRotate(struct Node* y)
{
    struct Node* x = y->left;
    struct Node* T2 = x->right;

    // поворот
    x->right = y;
    y->left = T2;

    // изменение высот
    y->height = height(y);
    x->height = height(x);

    return x;
}

/* Левый поворот */
struct Node* leftRotate(struct Node* x)
{
    struct Node* y = x->right;
    struct Node* T2 = y->left;

    // поворот
    y->left = x;
    x->right = T2;

    // изменение высот
    x->height = height(x);
    y->height = height(y);

    return y;
}

// Баланс
int getBalance(struct Node* N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}
/* Добавление узла */
struct Node* insert(struct Node* node, int key)
{
    /* Бинарный поиск */
    if (node == NULL)
        return(newNode(key));

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else 
        return node;

    /* Изменение высоты */
    node->height = height(node);

    /* Получение баланса */
    int balance = getBalance(node);

    /* Если не сбалансированно */

    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    if (balance > 1 && key > node->left->key)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

/* Вывод узлов с высотой */
void preOrder(struct Node* root)
{
    if (root != NULL)
    {
        int output = getBalance(root);
        printf("%d = %d\n", root->key, output);
        preOrder(root->left);
        preOrder(root->right);
    }
}

/* Удаление ключа */

/* поиск узла с минимальным ключом в дереве p */

struct Node* findmin(struct Node* p)  
{
    return p->left ? findmin(p->left) : p;
}

/* удаление узла с минимальным ключом из дерева p */

struct Node* removemin(struct Node* p) 
{
    if (p->left == 0)
        return p->right;
    p->left = removemin(p->left);
    return getBalance(p);
}

struct Node* remove_node(struct Node* root, int k) // удаление ключа k из дерева
{
    if (!root) return 0;
    if (k < root->key)
        root->left = remove_node(root->left, k);
    else if (k > root->key)
        root->right = remove_node(root->right, k);
    else //  k == p->key 
    {
        struct Node* q = root->left;
        struct Node* r = root->right;
        free (root);
        if (!r) return q;
        struct Node* min = findmin(r);
        min->right = removemin(r);
        min->left = q;
        return getBalance(min);
    }
    return getBalance(root);
}


int main()
{
    setlocale(LC_ALL, "RU");
    struct Node* root = NULL;
    printf("Введите кол-во узлов: ");
    int count;
    float buf;
    scanf("%d", &count);
    printf("Введите значения узлов\n");
    for (int i = 0; i < count; i++)
    {
        scanf("\n%f", &buf);
        root = insert(root, buf);
    }

    printf("Предварительный обход: \n");
    preOrder(root);

    printf("\n\n");

    printf("Введите номер ключа для удаления: ");
    int k;
    scanf("%d", &k);
    remove_node(root, k);
    preOrder(root);
    getchar();
    return 0;
}
