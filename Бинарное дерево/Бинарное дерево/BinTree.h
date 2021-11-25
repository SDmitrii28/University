#pragma once
#pragma once
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
        key = k;
        left = L;
        right = R;
        parent = P;
    }
    int GetKey() {
        return key;
    }

    friend class BinTree;
};
class BinTree
{
    Node* root;

    Node* Tree(int n, Node* p);//------------------------
    //построение идеально сбалансированного дерева
//с n вершинами, p - предок вершины дерева
    void Copy(Node* q, Node* p, int f);//-------------------
    //копирование дерева с корнем q, p - узел, к которому
    //присоединяется копия
    //f=0 - копируемое дерево будет левым потомком для p;
    //f=1 - копируемое дерево будет правым потомком для p.

public:
    BinTree() { //-------------------------
        root = NULL;
    }
    BinTree(int n);//------------- 		//n - количество ключей, ключи случайны
    BinTree(int* a, int n);	//a - массив ключей,  n - количество ключей
                       //потребуется вспомогательная ф-я
    BinTree(const BinTree&);//--------------------------
    BinTree& operator=(const BinTree&);
    ~BinTree();

    void Add(int k, Node* p); //-------------------	//добавление узла с ключом k в дерево 
                           //с корнем p
    void Del(Node* p); 		//удаление узла p
    void DelRoot() {// удаление корня 
        delete root;
    }
    void TreeTraversal_LCR(Node* p);
    //обход дерева с корнем p, в глубину по принципу
    //лево-корень-право, ключи выводятся на консоль

//возможен другой вариант этой функции:
//void TreeTraversal_LCR (Node *p, int *a, int *n);	
       //обход дерева с корнем p, в глубину по принципу
       //лево-корень-право, ключи сохраняются в массиве a, 
       //n - размер массива a 

    void TreeTraversal_LRC(Node* p);
    //обход дерева с корнем p, в глубину по принципу
    //лево-право-корень, ключи выводятся на консоль
    void TreeTraversal_RLC(Node* p);
    //обход дерева с корнем p, в глубину по принципу
    //право-лево-корень, ключи выводятся на консоль
    void WidthTraversal(Node* p);
    //обход дерева с корнем p, в ширину

    Node* FindKey(int k, Node* p);
    //поиск узла с ключом k в дереве с корнем p
    Node* FindMax(Node* p);
    //поиск узла с max ключом в дереве с корнем p
    Node* FindMin(Node* p);
    //поиск узла с min ключом в дереве с корнем p
    int FindHight(Node* p);
    //поиск высоты дерева с корнем p
    int Count(Node* p);
    //нахождение количества узлов в дереве с корнем p

    Node* GetRoot() {
        return root;
    }
    void Clear(Node* p); 	//уничтожает все дерево, кроме корня

    void PrintTree(Node* p, int k);//----------------------
        //вывод дерева на консоль, 
        //k - отступ от левой границы консоли
    void Print();

};
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

BinTree::BinTree(int n)			//n - количество ключей, ключи случайны
{
    root = Tree(n, NULL);
}
BinTree::BinTree(int* a, int n)
{
    if (n == 0) root = NULL;//проверка не пустое ли дерево, иначе просто добавляем элементы массива в конец
    else
    {
        root = new Node(a[0]);
        for (int i = 1; i < n; i++)	Add(a[i], root);
    }

}
BinTree::~BinTree()//диструктор очишаем дерево
{
    Clear(root);
}
void BinTree::Clear(Node* p)
{
    if (p)
    {
        Clear(p->left);//идем по левой,
        Clear(p->right);//потом по правой

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
    Copy(q->left, t, 0);//копируем левую ветвь
    Copy(q->right, t, 1);//копируем правую ветвь
}


//конструктор копирования
BinTree::BinTree(const BinTree& T)
{
    if (T.root == NULL) root = NULL;
    else
    {
        //вначале по левой, потом по правой
        root = new Node(T.root->key);
        Copy(T.root->left, root, 0);
        Copy(T.root->right, root, 1);
    }
}
//оператор присвоения, проверяем на равенство двух деревьем, если не равны то очишаем, и копируем
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
            Copy(T.root->left, root, 0);//копируем левую
            Copy(T.root->right, root, 1);//копируем правую
        }
    }

    return *this;
}
//нахождения минимума
Node* BinTree::FindMin(Node* p)
{
    Node* min = p;
    //проверяем лувую границу
    if (p->left)
    {
        Node* q = FindMin(p->left);
        //сравниваем ключи
        if (min->key > q->key)
        {
            //записываем минимум
            min = q;
        }
    }
    //проверяем правую границу
    if (p->right)
    {
        Node* q1 = FindMin(p->right);
        //сравниваем ключи
        if (min->key > q1->key)
        {
            //записываем минимум
            min = q1;
        }
    }

    return min;
}
//нахождение максимума
Node* BinTree::FindMax(Node* p)
{

    Node* max = p;
    //проверяем лувую границу
    if (p->left)
    {
        Node* q = FindMax(p->left);
        //сравниваем ключи
        if (max->key < q->key)
        {
            //записываем максимум
            max = q;
        }
    }
    //проверяем правую границу
    if (p->right)
    {
        Node* q1 = FindMax(p->right);
        //сравниваем ключи
        if (max->key < q1->key)
        {
            //записываем максимум
            max = q1;
        }
    }

    return max;
}
//нахождение ключа
Node* BinTree::FindKey(int key, Node* p)
{
    if (p && p->key != key)
    {
        Node* t = FindKey(key, p->left);
        //проверяем на существование
        if (t)
        {
            return t;
        }
        //выводим указатель ключа
        return FindKey(key, p->right);
    }

    return p;
}
void BinTree::PrintTree(Node* p, int k)
//вывод дерева на консоль, 
//k - отступ от левой границы консоли
{
    if (p == NULL) return;
    //рукурсивно выводим дерево
    PrintTree(p->right, k + 5);
    for (int i = 0; i < k; i++) cout << ' ';
    cout << p->key << endl;
    PrintTree(p->left, k + 5);
}
void BinTree::Print()
{
    //вывод на консоль дерева
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
///нахождение высоты дерева
int BinTree::FindHight(Node* p)
{
    if (p)
    {
        int l = FindHight(p->left);
        int r = FindHight(p->right);
        //сравниваем левую и правую
        if (l > r)
        {
            return l + 1;//+1 - корень дерева
        }
        else
        {
            return r + 1;//+1 - корень дерева
        }
    }

    return 0;
}
//нахождение количества узлов в дереве с корнем p
int BinTree::Count(Node* p) {
    //проверяем левую и правую границу
    if (p->left == NULL && p->right == NULL)
        return 1;
    int l, r;
    if (p->left != NULL)
        l = Count(p->left);//считаем левую, рекурсивно
    else
        l = 0;
    if (p->right != NULL)
        r = Count(p->right);//считаем правую рекурсивно
    else
        r = 0;

    return l + r + 1;//вывод суммы левой и правой + 1 (корень)
}
//обход дерева с корнем p, в ширину
//используя очередь обойдм дерево в ширину
void  BinTree::WidthTraversal(Node* p) {
    if (p == NULL)
    {
        return;
    }
    queue<Node*> q;
    q.push(p);

    while (!q.empty())//проверка на пустоту
    {
        Node* t = q.front();//извлекаем
        q.pop();//удаляем
        cout << t->key << " "; // Печатаем значение первого элемента в очереди

        if (t->left != NULL)
            q.push(t->left);  // Вставляем  в очередь левого потомка

        if (t->right != NULL)
            q.push(t->right);  // Вставляем  в очередь правого потомка
    }
}
