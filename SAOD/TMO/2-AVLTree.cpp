#include <iostream>
//Создание узла
typedef struct AVL {
	int key;
	int height;
	struct AVL* lchild;
	struct AVL* rchild;
}AVL;
//Высота по умолчанию равна 0
AVL* New_Node(int key, AVL* lchild, AVL* rchild, int height = 0)
{
	AVL* p_avl = new AVL;
	p_avl->key = key;
	p_avl->lchild = lchild;
	p_avl->rchild = rchild;
	p_avl->height = height;
	return p_avl;
}

int getHeight(AVL* node)
{
	return (node == NULL) ? -1 : node->height;
}

int max(int a, int b)
{
	return a > b ? a : b;
}

/* RR(Y rotates to the right):
	    k2                   k1
	   /  \                 /  \
	  k1   Z     ==>       X   k2
	 / \                      /  \
	X   Y                    Y    Z
*/
/*
 Return which the root pointer(at a higher level) should point to
 */
AVL* RR_Rotate(AVL* k2)
{
	AVL* k1 = k2->lchild;
	k2->lchild = k1->rchild;
	k1->rchild = k2;
	k2->height = max(getHeight(k2->lchild), getHeight(k2->rchild)) + 1;
	k1->height = max(getHeight(k1->lchild), k2->height) + 1;
	return k1;
}

/* LL(Y rotates to the left):
		k2                       k1
	   /  \                     /  \
	  X    k1         ==>      k2   Z
		  /  \                /  \
		 Y    Z              X    Y
 */
AVL* LL_Rotate(AVL* k2)
{
	AVL* k1 = k2->rchild;
	k2->rchild = k1->lchild;
	k1->lchild = k2;
	k2->height = max(getHeight(k2->lchild), getHeight(k2->rchild)) + 1;
	k1->height = max(getHeight(k1->rchild), k2->height) + 1;
	return k1;
}



/* LR(B rotates to the left, then C rotates to the right):
	  k3                         k3                       k2
	 /  \                       /  \                     /  \
	k1   D                     k2   D                   k1   k3
   /  \         ==>           /  \        ==>          / \   / \
  A    k2                    k1   C                   A  B  C   D
	  /  \                  /  \
	 B    C                A    B
*/
/*
 Return which the root pointer should point to
 */
AVL* LR_Rotate(AVL* k3)
{
	k3->lchild = LL_Rotate(k3->lchild);
	return RR_Rotate(k3);
}


/* RL(D rotates to the right, then C rotates to the left):
	   k3                         k3                          k2
	  /  \                       /  \                        /  \
	 A    k1                    A    k2                     k3   k1
		 /  \       ==>             /  \         ==>       /  \  / \
		k2   B                     C    k1                A   C D   B
	   /  \                            /  \
	  C    D                          D    B
 */
AVL* RL_Rotate(AVL* k3)
{
	k3->rchild = RR_Rotate(k3->rchild);
	return LL_Rotate(k3);
}

/* return which the root pointer(at an outer/higher level) should point to,
   the root_node of AVL tree may change frequently during delete/insert,
   so the Root pointer should point to the REAL root node.
 */
AVL* Insert(AVL* root, int key)
{
	if (root == NULL)
		return (root = New_Node(key, NULL, NULL));
	else if (key < root->key)
		root->lchild = Insert(root->lchild, key);
	else //key >= root->key
		root->rchild = Insert(root->rchild, key);

	root->height = max(getHeight(root->lchild), getHeight(root->rchild)) + 1;
	if (getHeight(root->lchild) - getHeight(root->rchild) == 2)
	{
		if (key < root->lchild->key)
			root = RR_Rotate(root);
		else
			root = LR_Rotate(root);
	}
	else if (getHeight(root->rchild) - getHeight(root->lchild) == 2)
	{
		if (key < root->rchild->key)
			root = RL_Rotate(root);
		else
			root = LL_Rotate(root);
	}
	return root;
}


/* return which the root pointer(at an outer/higher level) should pointer to,
   cause the root_node of AVL tree may change frequently during delete/insert,
   so the Root pointer should point to the REAL root node.
 */
AVL* Delete(AVL* root, int key)
{
	if (!root)
		return NULL;
	if (key == root->key)
	{
		if (root->rchild == NULL)
		{
			AVL* temp = root;
			root = root->lchild;
			delete(temp);
			return root;
		}
		else
		{
			AVL* temp = root->rchild;
			while (temp->lchild)
				temp = temp->lchild;
			/* replace the value */
			root->key = temp->key;
			/* Delete the node (successor node) that should be really deleted */
			root->rchild = Delete(root->rchild, temp->key);
		}
	}
	else if (key < root->key)
		root->lchild = Delete(root->lchild, key);
	else
		root->rchild = Delete(root->rchild, key);

	root->height = max(getHeight(root->lchild), getHeight(root->rchild)) + 1;
	if (getHeight(root->rchild) - getHeight(root->lchild) == 2)
	{
		if (getHeight(root->rchild->rchild) >= getHeight(root->rchild->lchild))
			root = LL_Rotate(root);
		else
			root = RL_Rotate(root);
	}
	else if (getHeight(root->lchild) - getHeight(root->rchild) == 2)
	{
		if (getHeight(root->lchild->lchild) >= getHeight(root->lchild->rchild))
			root = RR_Rotate(root);
		else
			root = LR_Rotate(root);
	}
	return root;
}

void InOrder(AVL* root)
{
	if (root)
	{
		InOrder(root->lchild);
		std::cout << "key: " << root->key << " height: " << root->height;
		if (root->lchild)
			std::cout << " left child: " << root->lchild->key;
		if (root->rchild)
			std::cout << " right child: " << root->rchild->key;
		std::cout << std::endl;
		InOrder(root->rchild);
	}
}

int main()
{
	AVL* root = NULL;
	int vector[] = { 3, 2, 1, 10 };
	const int length = sizeof(vector) / sizeof(int);
	for (int i = 0; i < length; i++)
		root = Insert(root, vector[i]);
	std::cout << "\nInOrder: " << std::endl;
	InOrder(root);
	int input;
	while (root)
	{
		std::cout << "\nplease input value you want to delete: ";
		std::cin >> input;
		//scanf("%u", &input);
		root = Delete(root, input);
		std::cout << "\nAfter delete " << input << ":" << std::endl;
		//printf("\nAfter delete %u:\n", input);
		InOrder(root);
	}
	std::cout << std::endl;
	return 0;
}
