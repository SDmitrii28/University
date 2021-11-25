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
    //���������� �������� ����������������� ������
//� n ���������, p - ������ ������� ������
    void Copy(Node* q, Node* p, int f);//-------------------
    //����������� ������ � ������ q, p - ����, � ��������
    //�������������� �����
    //f=0 - ���������� ������ ����� ����� �������� ��� p;
    //f=1 - ���������� ������ ����� ������ �������� ��� p.

public:
    BinTree() { //-------------------------
        root = NULL;
    }
    BinTree(int n);//------------- 		//n - ���������� ������, ����� ��������
    BinTree(int* a, int n);	//a - ������ ������,  n - ���������� ������
                       //����������� ��������������� �-�
    BinTree(const BinTree&);//--------------------------
    BinTree& operator=(const BinTree&);
    ~BinTree();

    void Add(int k, Node* p); //-------------------	//���������� ���� � ������ k � ������ 
                           //� ������ p
    void Del(Node* p); 		//�������� ���� p
    void DelRoot() {// �������� ����� 
        delete root;
    }
    void TreeTraversal_LCR(Node* p);
    //����� ������ � ������ p, � ������� �� ��������
    //����-������-�����, ����� ��������� �� �������

//�������� ������ ������� ���� �������:
//void TreeTraversal_LCR (Node *p, int *a, int *n);	
       //����� ������ � ������ p, � ������� �� ��������
       //����-������-�����, ����� ����������� � ������� a, 
       //n - ������ ������� a 

    void TreeTraversal_LRC(Node* p);
    //����� ������ � ������ p, � ������� �� ��������
    //����-�����-������, ����� ��������� �� �������
    void TreeTraversal_RLC(Node* p);
    //����� ������ � ������ p, � ������� �� ��������
    //�����-����-������, ����� ��������� �� �������
    void WidthTraversal(Node* p);
    //����� ������ � ������ p, � ������

    Node* FindKey(int k, Node* p);
    //����� ���� � ������ k � ������ � ������ p
    Node* FindMax(Node* p);
    //����� ���� � max ������ � ������ � ������ p
    Node* FindMin(Node* p);
    //����� ���� � min ������ � ������ � ������ p
    int FindHight(Node* p);
    //����� ������ ������ � ������ p
    int Count(Node* p);
    //���������� ���������� ����� � ������ � ������ p

    Node* GetRoot() {
        return root;
    }
    void Clear(Node* p); 	//���������� ��� ������, ����� �����

    void PrintTree(Node* p, int k);//----------------------
        //����� ������ �� �������, 
        //k - ������ �� ����� ������� �������
    void Print();

};
Node* BinTree::Tree(int n, Node* p)
//���������� �������� ����������������� ������
//� n ���������, p - ������ ������� ������
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

BinTree::BinTree(int n)			//n - ���������� ������, ����� ��������
{
    root = Tree(n, NULL);
}
BinTree::BinTree(int* a, int n)
{
    if (n == 0) root = NULL;//�������� �� ������ �� ������, ����� ������ ��������� �������� ������� � �����
    else
    {
        root = new Node(a[0]);
        for (int i = 1; i < n; i++)	Add(a[i], root);
    }

}
BinTree::~BinTree()//���������� ������� ������
{
    Clear(root);
}
void BinTree::Clear(Node* p)
{
    if (p)
    {
        Clear(p->left);//���� �� �����,
        Clear(p->right);//����� �� ������

        delete p;
    }
}
void BinTree::Copy(Node* q, Node* p, int f)
//����������� ������ � ������ q, p - ����, � �������� 
//�������������� �����
//f=0 - ���������� ������ ����� ����� �������� ��� p;
//f=1 - ���������� ������ ����� ������ �������� ��� p.
{
    if (q == NULL) return;
    Node* t = new Node(q->key);
    t->parent = p;
    if (f == 0) p->left = t;
    else p->right = t;
    Copy(q->left, t, 0);//�������� ����� �����
    Copy(q->right, t, 1);//�������� ������ �����
}


//����������� �����������
BinTree::BinTree(const BinTree& T)
{
    if (T.root == NULL) root = NULL;
    else
    {
        //������� �� �����, ����� �� ������
        root = new Node(T.root->key);
        Copy(T.root->left, root, 0);
        Copy(T.root->right, root, 1);
    }
}
//�������� ����������, ��������� �� ��������� ���� ��������, ���� �� ����� �� �������, � ��������
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
            Copy(T.root->left, root, 0);//�������� �����
            Copy(T.root->right, root, 1);//�������� ������
        }
    }

    return *this;
}
//���������� ��������
Node* BinTree::FindMin(Node* p)
{
    Node* min = p;
    //��������� ����� �������
    if (p->left)
    {
        Node* q = FindMin(p->left);
        //���������� �����
        if (min->key > q->key)
        {
            //���������� �������
            min = q;
        }
    }
    //��������� ������ �������
    if (p->right)
    {
        Node* q1 = FindMin(p->right);
        //���������� �����
        if (min->key > q1->key)
        {
            //���������� �������
            min = q1;
        }
    }

    return min;
}
//���������� ���������
Node* BinTree::FindMax(Node* p)
{

    Node* max = p;
    //��������� ����� �������
    if (p->left)
    {
        Node* q = FindMax(p->left);
        //���������� �����
        if (max->key < q->key)
        {
            //���������� ��������
            max = q;
        }
    }
    //��������� ������ �������
    if (p->right)
    {
        Node* q1 = FindMax(p->right);
        //���������� �����
        if (max->key < q1->key)
        {
            //���������� ��������
            max = q1;
        }
    }

    return max;
}
//���������� �����
Node* BinTree::FindKey(int key, Node* p)
{
    if (p && p->key != key)
    {
        Node* t = FindKey(key, p->left);
        //��������� �� �������������
        if (t)
        {
            return t;
        }
        //������� ��������� �����
        return FindKey(key, p->right);
    }

    return p;
}
void BinTree::PrintTree(Node* p, int k)
//����� ������ �� �������, 
//k - ������ �� ����� ������� �������
{
    if (p == NULL) return;
    //���������� ������� ������
    PrintTree(p->right, k + 5);
    for (int i = 0; i < k; i++) cout << ' ';
    cout << p->key << endl;
    PrintTree(p->left, k + 5);
}
void BinTree::Print()
{
    //����� �� ������� ������
    PrintTree(root, 0);
}
void BinTree::Del(Node* p) 		//�������� ���� p
{
    Node* q = p->parent;
    //�������� �����
    if (p->left == NULL && p->right == NULL)
    {
        if (q->left == p) q->left = NULL;
        else q->right = NULL;
        delete p;
        p = NULL;
        return;
    }
    //� p ��� ����� �����
    if (p->left == NULL && p->right != NULL)
    {
        if (q->left == p) q->left = p->right;
        else q->right = p->right;
        p->right->parent = q;
        delete p;
        p = NULL;
        return;
    }
    //� p ��� ������ �����
    if (p->left != NULL && p->right == NULL)
    {
        if (q->left == p) q->left = p->left;
        else q->right = p->left;
        p->left->parent = q;
        delete p;
        p = NULL;
        return;
    }

    //� p ���� ��� ���������
    Node* t = p;
    while (t->left != NULL) t = t->left;

    //�������� t �� ������
    if (t->right == NULL)
        t->parent->left = NULL;
    else {
        t->parent->left = t->right;
        t->right->parent = t->parent;
    }
    //�������� p ����� t
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
//����� ������ � ������ p, � ������� �� ��������
//����-������-�����, ����� ��������� �� �������

{
    if (p == NULL) return;
    TreeTraversal_LCR(p->left);
    cout << p->key << ' ';
    TreeTraversal_LCR(p->right);
}
void BinTree::TreeTraversal_LRC(Node* p)
//����� ������ � ������ p, � ������� �� ��������
//����-������-�����, ����� ��������� �� �������

{
    if (p == NULL) return;
    TreeTraversal_LRC(p->left);

    TreeTraversal_LRC(p->right);

    cout << p->key << " ";
}
void BinTree::TreeTraversal_RLC(Node* p)
//����� ������ � ������ p, � ������� �� ��������
//����-������-�����, ����� ��������� �� �������

{
    if (p == NULL) return;
    TreeTraversal_LRC(p->right);

    TreeTraversal_LRC(p->left);


    cout << p->key << " ";
}
//����� ������ � ������ p, � ������� �� ��������
//����-������-�����, ����� ��������� �� �������
void BinTree::Add(int k, Node* p) // p-������
            //���������� ���� � ������ k � ������ � ������ p
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
        //������ �������:
         //Node *q=new Node (k, NULL, NULL, p);
         //p->right=q;
        return;
    }
    if (rand() % 2) Add(k, p->left);
    else Add(k, p->right);
}
///���������� ������ ������
int BinTree::FindHight(Node* p)
{
    if (p)
    {
        int l = FindHight(p->left);
        int r = FindHight(p->right);
        //���������� ����� � ������
        if (l > r)
        {
            return l + 1;//+1 - ������ ������
        }
        else
        {
            return r + 1;//+1 - ������ ������
        }
    }

    return 0;
}
//���������� ���������� ����� � ������ � ������ p
int BinTree::Count(Node* p) {
    //��������� ����� � ������ �������
    if (p->left == NULL && p->right == NULL)
        return 1;
    int l, r;
    if (p->left != NULL)
        l = Count(p->left);//������� �����, ����������
    else
        l = 0;
    if (p->right != NULL)
        r = Count(p->right);//������� ������ ����������
    else
        r = 0;

    return l + r + 1;//����� ����� ����� � ������ + 1 (������)
}
//����� ������ � ������ p, � ������
//��������� ������� ������ ������ � ������
void  BinTree::WidthTraversal(Node* p) {
    if (p == NULL)
    {
        return;
    }
    queue<Node*> q;
    q.push(p);

    while (!q.empty())//�������� �� �������
    {
        Node* t = q.front();//���������
        q.pop();//�������
        cout << t->key << " "; // �������� �������� ������� �������� � �������

        if (t->left != NULL)
            q.push(t->left);  // ���������  � ������� ������ �������

        if (t->right != NULL)
            q.push(t->right);  // ���������  � ������� ������� �������
    }
}
