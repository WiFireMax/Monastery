#include <iostream>

using namespace std;
enum type { RED, BLACK };

struct Node
{
    int data;
    struct Node* left;
    struct Node* right;
    struct Node* parent;
    enum type color;
};
//Очередь для работы с узлами поэлементно
struct Queue
{
    struct Node* data;
    struct Queue* next;
};

struct Queue* front = NULL;
struct Queue* tail = NULL;
//Функция для сопоставления бита цвета (см. enum) и самого цвета
string what_color(struct Node* root) {
    if (root->color == BLACK) return "BLACK";
    if (root->color == RED) return "RED";
}
//Установка указателя на первый элемент дерева (очереди)
struct Node* pfront()
{
    struct Node* data;
    data = front->data;
    return data;
}

int isempty()
{
    if (front == NULL)
        return 1;

    else
        return 0;
}
//Удаление очереди
void dequeue()
{
    if (isempty())
        return;

    struct Queue* temp = front;
    front = front->next;
    free(temp);
}

//Вставка в очередь
void enqueue(struct Node* data)
{
    struct Queue* temp = new Queue;
    temp->data = data;
    temp->next = NULL;

    if (front == NULL && tail == NULL)
    {
        front = tail = temp;
        return;
    }

    tail->next = temp;
    tail = temp;
}
//Вывод дерева в порядке убывания высот
void levelorder(struct Node* root)
{
    if (root == NULL)
        return;

    enqueue(root);

    while (!isempty())
    {
        struct Node* current = pfront();
        cout << "key: " << current->data << " color: " << what_color(current) << endl;
        if (current->left) cout << "      --left child: " << current->left->data << "; color: " << what_color(current->left) << endl;
        if (current->right) cout << "      --right child: " << current->right->data << "; color: " << what_color(current->right) << endl;

        if (current->left != NULL)
            enqueue(current->left);

        if (current->right != NULL)
            enqueue(current->right);

        dequeue();
    }
}

void LeftRotate(struct Node** Tree, struct Node** x)
{
    struct Node* y = (*x)->right;
    (*x)->right = y->left;

    if (y->left != NULL)
        y->left->parent = *x;

    y->parent = (*x)->parent;

    if ((*x)->parent == NULL)
        *Tree = y;

    else if (*x == (*x)->parent->left)
        (*x)->parent->left = y;

    else
        (*x)->parent->right = y;

    y->left = *x;

    (*x)->parent = y;

}
void RightRotate(struct Node** Tree, struct Node** x)
{
    struct Node* y = (*x)->left;
    (*x)->left = y->right;

    if (y->right != NULL)
        y->right->parent = *x;

    y->parent = (*x)->parent;

    if ((*x)->parent == NULL)
        *Tree = y;

    else if ((*x) == (*x)->parent->left)
        (*x)->parent->left = y;

    else
        (*x)->parent->right = y;

    y->right = *x;
    (*x)->parent = y;

}
//Перекрашивание дерева после вставки
void RB_insert_fixup(struct Node** Tree, struct Node** z)
{
    struct Node* grandparent = NULL;
    struct Node* parentpt = NULL;

    while (((*z) != *Tree) && ((*z)->color != BLACK) && ((*z)->parent->color == RED))
    {
        parentpt = (*z)->parent;
        grandparent = (*z)->parent->parent;

        if (parentpt == grandparent->left)
        {
            struct Node* uncle = grandparent->right;

            if (uncle != NULL && uncle->color == RED)
            {
                grandparent->color = RED;
                parentpt->color = BLACK;
                uncle->color = BLACK;
                *z = grandparent;
            }

            else
            {
                if ((*z) == parentpt->right)
                {
                    LeftRotate(Tree, &parentpt);
                    (*z) = parentpt;
                    parentpt = (*z)->parent;
                }

                RightRotate(Tree, &grandparent);
                parentpt->color = BLACK;
                grandparent->color = RED;
                (*z) = parentpt;
            }
        }

        else
        {
            struct Node* uncle = grandparent->left;

            if (uncle != NULL && uncle->color == RED)
            {
                grandparent->color = RED;
                parentpt->color = BLACK;
                uncle->color = BLACK;
                (*z) = grandparent;
            }

            else
            {
                if ((*z) == parentpt->left)
                {
                    RightRotate(Tree, &parentpt);
                    (*z) = parentpt;
                    parentpt = (*z)->parent;
                }

                LeftRotate(Tree, &grandparent);
                parentpt->color = BLACK;
                grandparent->color = RED;
                (*z) = parentpt;
            }
        }
    }
    (*Tree)->color = BLACK;

}
//Вставка
struct Node* RB_insert(struct Node* Tree, int data)
{
    struct Node* z = new Node;
    z->data = data;
    z->left = NULL;
    z->right = NULL;
    z->parent = NULL;
    z->color = RED;

    struct Node* y = NULL;
    struct Node* x = Tree;//root

    while (x != NULL)
    {
        y = x;
        if (z->data < x->data)
            x = x->left;

        else
            x = x->right;
    }
    z->parent = y;

    if (y == NULL)
        Tree = z;

    else if (z->data < y->data)
        y->left = z;

    else
        y->right = z;

    RB_insert_fixup(&Tree, &z);

    return Tree;
}
//Неупорядоченный вывод
void preorder(struct Node* root)
{
    if (root)
    {
        preorder(root->left);
        cout << "key: " << root->data << " color: " << what_color(root) << endl;
        if (root->left)
            cout << "      --left child: " << root->left->data << "; color: " << what_color(root->left) << endl;
        if (root->right)
            cout << "      --right child: " << root->right->data << "; color: " << what_color(root->right) << endl;
        preorder(root->right);
    }
}

struct Node* Tree_minimum(struct Node* node)
{
    while (node->left != NULL)
        node = node->left;

    return node;
}
//Перекрашивание дерева после удаления узла
void RB_delete_fixup(struct Node** Tree, struct Node** x)
{
    while ((*x) != *Tree && (*x)->color == BLACK)
    {
        if ((*x) == (*x)->parent->left)
        {
            struct Node* w = (*x)->parent->right;

            if (w->color == RED)
            {
                w->color = BLACK;
                (*x)->parent->color = BLACK;
                LeftRotate(Tree, &((*x)->parent));
                w = (*x)->parent->right;
            }

            if (w->left->color == BLACK && w->right->color == BLACK)
            {
                w->color = RED;
                (*x) = (*x)->parent;
            }

            else
            {
                if (w->right->color == BLACK)
                {
                    w->left->color = BLACK;
                    w->color = RED;
                    RightRotate(Tree, &w);
                    w = (*x)->parent->right;
                }

                w->color = (*x)->parent->color;
                (*x)->parent->color = BLACK;
                w->right->color = BLACK;
                LeftRotate(Tree, &((*x)->parent));
                (*x) = *Tree;
            }
        }

        else
        {
            struct Node* w = (*x)->parent->left;

            if (w->color == RED)
            {
                w->color = BLACK;
                (*x)->parent->color = BLACK;
                RightRotate(Tree, &((*x)->parent));
                w = (*x)->parent->left;
            }

            if (w->right->color == BLACK && w->left->color == BLACK)
            {
                w->color = RED;
                (*x) = (*x)->parent;
            }

            else
            {
                if (w->left->color == BLACK)
                {
                    w->right->color = BLACK;
                    w->color = RED;
                    LeftRotate(Tree, &w);
                    w = (*x)->parent->left;
                }

                w->color = (*x)->parent->color;
                (*x)->parent->color = BLACK;
                w->left->color = BLACK;
                RightRotate(Tree, &((*x)->parent));
                (*x) = *Tree;
            }
        }
    }
    (*x)->color = BLACK;

}
//"Пересаживание" листка
void RB_transplat(struct Node** Tree, struct Node** u, struct Node** v)
{
    if ((*u)->parent == NULL)
        *Tree = *v;

    else if ((*u) == (*u)->parent->left)
        (*u)->parent->left = *v;
    else
        (*u)->parent->right = *v;

    if ((*v) != NULL)
        (*v)->parent = (*u)->parent;
}

struct Node* RB_delete(struct Node* Tree, struct Node* z)
{
    struct Node* y = z;
    enum type yoc;
    yoc = z->color; // y's original color

    struct Node* x;

    if (z->left == NULL)
    {
        x = z->right;
        RB_transplat(&Tree, &z, &(z->right));
    }

    else if (z->right == NULL)
    {
        x = z->left;
        RB_transplat(&Tree, &z, &(z->left));
    }

    else
    {
        y = Tree_minimum(z->right);
        yoc = y->color;
        x = y->right;

        if (y->parent != z) {
            RB_transplat(&Tree, &y, &x);
            y->right = z->right;
            y->right->parent = y;

        }

        RB_transplat(&Tree, &z, &y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    if (yoc == BLACK)
        RB_delete_fixup(&Tree, &x);

    return Tree;
}

struct Node* BST_search(struct Node* root, int x)
{
    if (root == NULL || root->data == x)
        return root;

    if (root->data > x)
        return  BST_search(root->left, x);
    else
        return BST_search(root->right, x);
}

int main()
{
    int n;
    struct Node* RBT = NULL;
    cout << "Enter the count of numbers: ";
    cin >> n;
    cout << "Enter the numbers trough space: ";
    while (n) {
        int q;
        cin >> q;
        RBT = RB_insert(RBT, q);
        n--;
    }

    cout << "\nLevel order: " << endl;
    levelorder(RBT);
    
    int w;
    cout << "Which number you want to delete?" << endl;
    cin >> w;
    struct Node* x = BST_search(RBT, w);
    RBT = RB_delete(RBT, x);

    front = NULL; tail = NULL; //Удаление старой очереди

    cout << "\nLevel order: " << endl;
    levelorder(RBT);
    return 0;
}
