#pragma once
#pragma once

#include "BinTree.h"

class BalansTree : public BinTree
{
public:
	BalansTree();
	BalansTree(int n);
	BalansTree(int*a,int n);
	virtual void Add(int key, Node* p);
	void Del(Node* p);

private:
	void RotateLeft(Node* p);
	void RotateRight(Node* p);
	void RotateLeft2(Node* p);
	void RotateRight2(Node* p);

	void Balance(Node* p);

	int Height(Node* t);
	int B_factor(Node* t);
	int Max(int a, int b) {
		if (a > b) {
			return a;
		}
		else
			return b;
	}
};

BalansTree::BalansTree()
{

}
BalansTree::BalansTree(int n)		//n - количество ключей, ключи случайны
{
	if (n == 0) root = NULL;
	else {
		root = new Node(rand() % 50);
		for (int i = 1; i < n; i++)	Add(rand() % 50, root);
	}
}
BalansTree::BalansTree(int* a, int n)
{
	if (n == 0) root = NULL;
	else
	{
		root = new Node(a[0]);
		for (int i = 1; i < n; i++)	Add(a[i], root);
	}

}
int BalansTree::Height(Node* t) 
{
	int h = 0;
	if (t != NULL)
	{
		int l = Height(t->left);
		int r = Height(t->right);
		int max = Max(l, r);
		h = max + 1;
	}
	return h;
}

int BalansTree::B_factor(Node* t) {
	return Height(t->left) - Height(t->right);
}
//Левый поворот является симметричной копией правого :
void BalansTree::RotateLeft(Node*q)
{
	Node* p = q->right;

	q->right = p->left;
	p->left = q;

	q = p;
}
// правый поворот вокруг p
void BalansTree::RotateRight(Node *p)
{
	Node* q = p->left;

	p->left = q->right;
	q->right = p;
	p = q;
}
// левый поворот (двухкратный)
void BalansTree::RotateLeft2(Node* s )
{
	Node* p = s->right;
	Node* r = s->left;

	s->right = p->left;
	p->left = s;

	r->left = p->right;
	p->right = r;

}
// правый поворот вокруг p (двухкратный)
void BalansTree::RotateRight2(Node* s)
{
	Node* p = s->left;
	Node* r = s->right;

	s->left = p->right;
	p->right = s;
	r->right = p->left;
	p->left = r;
}
// балансировка узла p
void BalansTree::Balance(Node* p)
{
	if (B_factor(p) == 2)
	{
		if (B_factor(p->right) < 0)
		{
			RotateRight(p->right);
		}

		RotateLeft(p);
	}

	if (B_factor(p) == -2)
	{
		if (B_factor(p->left) > 0)
		{
			RotateLeft(p->left);
		}

		RotateRight(p);
	}
}
void BalansTree::Add(int key, Node* p)
{
	BinTree::Add(key, p);

	Balance(p);
}
void BalansTree::Del(Node* p)
{
	Node* q = p->parent;
	if (p->left == NULL && p->right == NULL)
	{
		if (q->left == p)
			q->left = NULL;
		else
			q->right = NULL;
		delete p;
		Balance(q);
		return;
	}
	if (p->left == NULL && p->right != NULL)
	{
		if (q->left == p)
			q->left = p->right;
		else
			q->right = p->right;
		p->right->parent = q;
		delete p;
		Balance(q);
		return;
	}
	if (p->left != NULL && p->right == NULL)
	{
		if (q->left == p)
			q->left = p->left;
		else
			q->right = p->left;
		p->left->parent = q;
		delete p;
		Balance(q);
		return;
	}
	Node* t = p->left;
	if (t->right == NULL)
	{
		t->parent = q;
		if (q->left == p)
			q->left = t;
		else
			q->right = t;
		t->right = p->right;
		p->right->parent = t;
		Balance(q);
	}
	else
	{
		while (t->right != NULL)
		{
			t = t->right;
		}
		Node* t_parent = t->parent;
		t->parent->right = t->left;
		if (t->left != NULL)
			t->left->parent = t->parent;
		t->left = p->left;
		t->right = p->right;
		p->left->parent = t;
		p->right->parent = t;
		t->parent = q;
		if (q->left == p)
			q->left = t;
		else
			q->right = t;
		Balance(t_parent);
	}
	delete p;
	return;
}