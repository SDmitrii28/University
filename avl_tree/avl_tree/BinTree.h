#pragma once
#pragma once
#pragma once
//подключение необходимых библиотек
#include <iostream>
#include <cstdlib>
#include <queue>
using namespace std;
class Node
{
    int key;
    Node* left, * right, * parent;

public:
    Node(int k = 0, Node* L = NULL, Node* R = NULL, Node* P = NULL)
    {
        key = k; left = L; right = R; parent = P;
    }
    int GetKey() { return key; }

    friend class BinTree;
    friend class SSBinTree;
};



class BinTree
{
protected:					//!!!!!!!!!!!!!!!!!!!!!
    Node* root;

    Node* Tree(int n, Node* p);
    //построение идеально сбалансированного дерева
    //с n вершинами, p - предок вершины дерева

    void Copy(Node* q, Node* p, int f);
    //копирование дерева с корнем q, p - узел, 
    //к которому присоединяется копия
    //f=0 - копируемое дерево будет левым потомком для p;
    //f=1 - копируемое дерево будет правым потомком для p.

public:
    BinTree() { root = NULL; }
    BinTree(int n); 	//n - количество ключей, ключи случайны
    BinTree(int* a, int n);	//a - массив ключей,  n - количество ключей
                       //потребуется вспомогательная ф-я
    BinTree(const BinTree&);
    BinTree& operator=(const BinTree&);
    ~BinTree();					//!!!!!!!!!!!!!!!!!!!!!

    virtual void Add(int k, Node* p); 	//!!!!!!!!!!!!!!!!!!!!!	
           //добавление узла с ключом k в дерево с корнем p
    virtual void Del(Node* p); 			//!!!!!!!!!!!!!!!!!!!!!	
           //удаление узла p
    void DelRoot(); 				//!!!!!!!!!!!!!!!!!!!!!					//удаление корня

    void TreeTraversal_LCR(Node* p);
    //обход дерева с корнем p, в глубину по принципу
    //лево-корень-право, ключи выводятся на консоль
//возможен другой вариант этой функции:
//void TreeTraversal_LCR (Node *p, int *a, int *n);	
       //обход дерева с корнем p, в глубину по принципу
       //лево-корень-право, ключи сохраняются в 
       //массиве a, n - размер массива a 

    void TreeTraversal_LRC(Node* p);
    //обход дерева с корнем p, в глубину по принципу
    //лево-право-корень, ключи выводятся на консоль
    void TreeTraversal_RLC(Node* p);
    //обход дерева с корнем p, в глубину по принципу
    //право-лево-корень, ключи выводятся на консоль
    void WidthTraversal(Node* p);
    //обход дерева с корнем p, в ширину

    virtual Node* FindKey(int k, Node* p); 	//!!!!!!!!!!!!!!!!!!
           //поиск узла с ключом k в дереве с корнем p
    Node* FindMax(Node* p);		//!!!!!!!!!!!!!!!!!!				//поиск узла с max ключом в дереве с корнем p
    Node* FindMin(Node* p);		//!!!!!!!!!!!!!!!!!!				//поиск узла с min ключом в дереве с корнем p
    int FindHight(Node* p);
    //поиск высоты дерева с корнем p
    int Count(Node* p);
    //нахождение количества узлов в дереве с корнем p

    Node* GetRoot() { return root; }
    void Clear(Node* p); 	//уничтожает все дерево, кроме корня

    void PrintTree(Node* p, int k);
    //вывод дерева на консоль, 
    //k - отступ от левой границы консоли
    void Print();
    int FindHeight(Node* p);
};
int BinTree::FindHeight(Node* p)
{
    if (p == NULL)
        return 0;
    else
    {
        int lheight = FindHeight(p->left);
        int rheight = FindHeight(p->right);
        if (lheight > rheight)
            return (lheight + 1);
        return (rheight + 1);
    }
}
Node* BinTree::Tree(int n, Node* p)
//построение идеально сбалансированного дерева
//с n вершинами, p - предок вершины дерева
{
    if (n == 0) return NULL;
    Node* q = new Node(rand() % 50);
    int nL, nR;
    nL = (n - 1) / 2;
    nR = n - 1 - nL;
    q->left = Tree(nL, q);
    q->right = Tree(nR, q);
    q->parent = p;
    return q;
}
void BinTree::DelRoot() {
    delete root;
}
BinTree::BinTree(int n)			//n - количество ключей, ключи случайны
{
    root = Tree(n, NULL);
}
BinTree::BinTree(int* a, int n)
{
    if (n == 0) root = NULL;
    else
    {
        root = new Node(a[0]);
        for (int i = 1; i < n; i++)	Add(a[i], root);
    }

}
BinTree::~BinTree()
{
    Clear(root);
}
void BinTree::Clear(Node* p)
{
    if (p)
    {
        Clear(p->left);
        Clear(p->right);

        delete p;
    }
}
void BinTree::Copy(Node* q, Node* p, int f)
//копирование дерева с корнем q, p - узел, к которому 
//присоединяется копия
//f=0 - копируемое дерево будет левым потомком для p;
//f=1 - копируемое дерево будет правым потомком для p.
{
    if (q == NULL) return;
    Node* t = new Node(q->key);
    t->parent = p;
    if (f == 0) p->left = t;
    else p->right = t;
    Copy(q->left, t, 0);
    Copy(q->right, t, 1);
}



BinTree::BinTree(const BinTree& T)
{
    if (T.root == NULL) root = NULL;
    else
    {
        root = new Node(T.root->key);
        Copy(T.root->left, root, 0);
        Copy(T.root->right, root, 1);
    }
}
BinTree& BinTree::operator=(const BinTree& T)
{
    if (this != &T)
    {
        Clear(root);
        delete root;
        if (T.root == NULL) {
            root = NULL;
        }
        else
        {
            root = new Node(T.root->key);
            Copy(T.root->left, root, 0);
            Copy(T.root->right, root, 1);
        }
    }

    return *this;
}
Node* BinTree::FindMin(Node* p)
{
    Node* min = p;

    if (p->left)
    {
        Node* q = FindMin(p->left);

        if (min->key > q->key)
        {
            min = q;
        }
    }

    if (p->right)
    {
        Node* q1 = FindMin(p->right);

        if (min->key > q1->key)
        {
            min = q1;
        }
    }

    return min;
}

Node* BinTree::FindMax(Node* p)
{

    Node* max = p;

    if (p->left)
    {
        Node* q = FindMax(p->left);

        if (max->key < q->key)
        {
            max = q;
        }
    }

    if (p->right)
    {
        Node* q1 = FindMax(p->right);

        if (max->key < q1->key)
        {
            max = q1;
        }
    }

    return max;
}

Node* BinTree::FindKey(int key, Node* p)
{
    if (p && p->key != key)
    {
        Node* t = FindKey(key, p->left);

        if (t)
        {
            return t;
        }

        return FindKey(key, p->right);
    }

    return p;
}
void BinTree::PrintTree(Node* p, int k)
//вывод дерева на консоль, 
//k - отступ от левой границы консоли
{
    if (p == NULL) return;
    PrintTree(p->right, k + 5);
    for (int i = 0; i < k; i++) cout << ' ';
    cout << p->key << endl;
    PrintTree(p->left, k + 5);
}
void BinTree::Print()
{
    PrintTree(root, 0);
}
void BinTree::Del(Node* p) 		//удаление узла p
{
    Node* q = p->parent;
    //удаление листа
    if (p->left == NULL && p->right == NULL)
    {
        if (q->left == p) q->left = NULL;
        else q->right = NULL;
        delete p;
        p = NULL;
        return;
    }
    //у p нет левой ветви
    if (p->left == NULL && p->right != NULL)
    {
        if (q->left == p) q->left = p->right;
        else q->right = p->right;
        p->right->parent = q;
        delete p;
        p = NULL;
        return;
    }
    //у p нет правой ветви
    if (p->left != NULL && p->right == NULL)
    {
        if (q->left == p) q->left = p->left;
        else q->right = p->left;
        p->left->parent = q;
        delete p;
        p = NULL;
        return;
    }

    //у p есть оба поддерева
    Node* t = p;
    while (t->left != NULL) t = t->left;

    //вырезаем t из дерева
    if (t->right == NULL)
        t->parent->left = NULL;
    else {
        t->parent->left = t->right;
        t->right->parent = t->parent;
    }
    //заменяем p узлом t
    t->left = p->left;
    t->right = p->right;
    t->parent = q;

    if (q->left == p) q->left = t;
    else q->right = t;

    if (p->left != NULL)
        p->left->parent = t;

    p->right->parent = t;
    delete p;
    p = NULL;
    return;
}

void BinTree::TreeTraversal_LCR(Node* p)
//обход дерева с корнем p, в глубину по принципу
//лево-корень-право, ключи выводятся на консоль

{
    if (p == NULL) return;
    TreeTraversal_LCR(p->left);
    cout << p->key << ' ';
    TreeTraversal_LCR(p->right);
}
void BinTree::TreeTraversal_LRC(Node* p)
//обход дерева с корнем p, в глубину по принципу
//лево-корень-право, ключи выводятся на консоль

{
    if (p == NULL) return;
    TreeTraversal_LRC(p->left);

    TreeTraversal_LRC(p->right);

    cout << p->key << " ";
}
void BinTree::TreeTraversal_RLC(Node* p)
//обход дерева с корнем p, в глубину по принципу
//лево-корень-право, ключи выводятся на консоль

{
    if (p == NULL) return;
    TreeTraversal_LRC(p->right);

    TreeTraversal_LRC(p->left);


    cout << p->key << " ";
}
//обход дерева с корнем p, в глубину по принципу
//лево-корень-право, ключи выводятся на консоль
void BinTree::Add(int k, Node* p) // p-предок
            //добавление узла с ключом k в дерево с корнем p
{
    if (p->left == NULL)
    {
        Node* q = new Node(k);
        p->left = q;  q->parent = p;
        return;
    }
    if (p->right == NULL)
    {
        Node* q = new Node(k);
        p->right = q;  q->parent = p;
        //другой вариант:
         //Node *q=new Node (k, NULL, NULL, p);
         //p->right=q;
        return;
    }
    if (rand() % 2) Add(k, p->left);
    else Add(k, p->right);
}

int BinTree::FindHight(Node* p)
{
    if (p)
    {
        int l = FindHight(p->left);
        int r = FindHight(p->right);

        if (l > r)
        {
            return l + 1;
        }
        else
        {
            return r + 1;
        }
    }

    return 0;
}
int BinTree::Count(Node* p) {
    if (p->left == NULL && p->right == NULL)
        return 1;
    int l, r;
    if (p->left != NULL)
        l = Count(p->left);
    else
        l = 0;
    if (p->right != NULL)
        r = Count(p->right);
    else
        r = 0;

    return l + r + 1;
}
void  BinTree::WidthTraversal(Node* p) {
    if (p == NULL)
    {
        return;
    }
    queue<Node*> q;
    q.push(p);

    while (!q.empty())
    {
        Node* t = q.front();
        q.pop();
        cout << t->key << " "; //значение первого элемента в очереди

        if (t->left != NULL)
            q.push(t->left);  // Вставляем  в очередь левого потомка

        if (t->right != NULL)
            q.push(t->right);  // Вставляем  в очередь правого потомка
    }
}



