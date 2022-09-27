#include <iostream>
#include <cstdlib>
#include <locale>

using namespace std;

struct node // ñòðóêòóðà äëÿ ïðåäñòàâëåíèÿ óçëîâ äåðåâà
{
	int key;
	unsigned char height;
	node* left;
	node* right;
	node(int k) { key = k; left = right = nullptr; height = 1; }
};

unsigned char height(node* p)
{
	return p ? p->height : 0;
}

int bfactor(node* p)
{
	return height(p->right) - height(p->left);
}

void fixheight(node* p)
{
	unsigned char hl = height(p->left);
	unsigned char hr = height(p->right);
	p->height = (hl > hr ? hl : hr) + 1;
}

node* rotateright(node* p) // ïðàâûé ïîâîðîò âîêðóã p
{
	node* q = p->left;
	p->left = q->right;
	q->right = p;
	fixheight(p);
	fixheight(q);
	return q;
}

node* rotateleft(node* q) // ëåâûé ïîâîðîò âîêðóã q
{
	node* p = q->right;
	q->right = p->left;
	p->left = q;
	fixheight(q);
	fixheight(p);
	return p;
}

node* balance(node* p) // áàëàíñèðîâêà óçëà p
{
	fixheight(p);
	if (bfactor(p) == 2)
	{
		if (bfactor(p->right) < 0)
			p->right = rotateright(p->right);
		return rotateleft(p);
	}
	if (bfactor(p) == -2)
	{
		if (bfactor(p->left) > 0)
			p->left = rotateleft(p->left);
		return rotateright(p);
	}
	return p; // áàëàíñèðîâêà íå íóæíà
}

node* insert(node* p, int k) // âñòàâêà êëþ÷à k â äåðåâî ñ êîðíåì p
{
	if (!p) return new node(k);
	if (k < p->key)
		p->left = insert(p->left, k);
	else
		p->right = insert(p->right, k);
	return balance(p);
}

node* findmin(node* p) // ïîèñê óçëà ñ ìèíèìàëüíûì êëþ÷îì â äåðåâå p 
{
	return p->left ? findmin(p->left) : p;
}

node* removemin(node* p) // óäàëåíèå óçëà ñ ìèíèìàëüíûì êëþ÷îì èç äåðåâà p
{
	if (p->left == 0)
		return p->right;
	p->left = removemin(p->left);
	return balance(p);
}

node* remove(node* p, int k) // óäàëåíèå êëþ÷à k èç äåðåâà p
{
	if (!p) return 0;
	if (k < p->key)
		p->left = remove(p->left, k);
	else if (k > p->key)
		p->right = remove(p->right, k);
	else //  k == p->key 
	{
		node* q = p->left;
		node* r = p->right;
		delete p;
		if (!r) return q;
		node* min = findmin(r);
		min->right = removemin(r);
		min->left = q;
		return balance(min);
	}
	return balance(p);
}

void preOrder(node* root)
{
	if (root != NULL)
	{
		int output = height(root);
		cout << "Êëþ÷ äåðåâà: " << root->key << " Âûñîòà äåðåâà: " << output << endl;
		//printf("%d = %d\n", root->key, output);
		preOrder(root->left);
		preOrder(root->right);
	}
}

int main() 
{
	int x, count;
	setlocale(LC_ALL, "RU");
	cout << "Ââåäèòå êîëè÷åñòâî óçëîâ: " << endl;
	cin >> count;
	if (count == 0)
	{
		cout << "Error";
	}
	else
	{
		cout << "Ââåäèòå êëþ÷ êîðíÿ äåðåâà: " << endl;
		cin >> x;
		node* root = new node(x);
		count--;
		while (count)
		{
			cout << "Ââåäèòå êëþ÷: " << endl;
			cin >> x;
			root = insert(root, x);
			count--;
		}
		preOrder(root);
		cout << "Êàêîé êëþ÷ óäàëèòü?" << endl;
		cin >> x;
		remove(root, x);
		if (root->key < 0) cout << "Âû óäàëèëè êîðåíü äåðåâà." << endl;
		else preOrder(root);
	}
}
