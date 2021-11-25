#pragma once
#include "SBinTree.h"

class OSBinTree : public SBinTree
{
private:
	void CreateMatrix(int* p, int* q, int n, int** W, int** C, int** R);
	Node* OTree(int* d, int i, int j, int** R);

public:
	OSBinTree() : SBinTree() {};//конструктор по умолчанию
	OSBinTree(int* d, int* p, int* q, int n);//d - массив ключей, p - массив частот, q - массив частот ловушек, n- размер массивов
	OSBinTree(const OSBinTree&);//конструктор копирования
	OSBinTree& operator= (const OSBinTree &);//оператор присвоения
	virtual ~OSBinTree() {};//деструктор
};
Node* OSBinTree::OTree(int *d,int i, int j, int **R)
{
	if (i >= j)return NULL;
	int k = R[i][j];
	Node* q = new Node(d[k]);
	q->left = OTree(d,i, k - 1, R);
	q->right = OTree(d,k, j, R);
	return q;
}
OSBinTree::OSBinTree(int* d, int* p, int* q, int n)
{
	int** w = new int* [n + 1];
	int** r = new int* [n + 1];
	int** c = new int* [n + 1];
	for (int i = 0; i < n + 1; i++)
	{
		w[i] = new int[n + 1];
		c[i] = new int[n + 1];
		r[i] = new int[n + 1];
	}
	CreateMatrix(p, q, n, w, c, r);
	root = OTree(d, 0, n, r);
}
OSBinTree::OSBinTree(const OSBinTree& T)
{
	if (T.root == NULL) root = NULL;
	else
	{
		root = new Node(T.root->key);
		Copy(T.root->left, root, 0);
		Copy(T.root->right, root, 1);
	}
}
OSBinTree& OSBinTree::operator=(const OSBinTree& T)
{
	if (T.root != root)
	{
		delete root;
		root = new Node(T.root->key);
		Copy(T.root->left, root, 0);
		Copy(T.root->right, root, 1);
	}
	return *this;
}
void OSBinTree::CreateMatrix(int* p, int* q, int n, int** W, int** C, int** R)
//n -- количество ключей -> размер массивов n+1			
{
	int i, j, t;
	for (i = 0; i < n + 1; i++)
		for (j = 0; j < n + 1; j++)
			W[i][j] = C[i][j] = R[i][j] = -1;

	//заполнение главной (t=0) диагонали в W и C
	for (i = 0; i < n + 1; i++)
		W[i][i] = C[i][i] = q[i];

	//заполнение первой (t=1) диагонали в W, C и R
	for (i = 0; i < n; i++)
	{
		j = i + 1;
		W[i][j] = W[i][i] + p[j] + q[j];
		C[i][j] = W[i][j] + C[i][i] + C[j][j];
		R[i][j] = j;
	}

	int min, k, k_min;
	//заполнение остальных (t=2,3,...,n) диагонали в W, C и R
	for (t = 2; t < n + 1; t++)
		for (i = 0; i < n + 1 - t; i++)
		{
			j = i + t;
			W[i][j] = W[i][j - 1] + p[j] + q[j];

			min = C[i][i] + C[i + 1][j]; k_min = i + 1;
			for (k = i + 2; k <= j; k++)
				if (C[i][k - 1] + C[k][j] < min)
				{
					min = C[i][k - 1] + C[k][j]; k_min = k;
				}

			C[i][j] = W[i][j] + min;
			R[i][j] = k_min;

		}
}
