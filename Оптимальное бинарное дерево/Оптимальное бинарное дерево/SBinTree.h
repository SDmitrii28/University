#pragma once
#include "BinTree.h"
#include <cstdlib>
#include <iostream>

class SBinTree : public BinTree
{
public:
	SBinTree() : BinTree() {};
	SBinTree(int n);
	//n - ���������� ������, ����� ��������
	SBinTree(int* a, int n);
	//a - ������ ������, n - ���������� ������
	SBinTree(const SBinTree&);
	SBinTree& operator= (const SBinTree&);
	virtual ~SBinTree() {};

	virtual void Add(int k, Node* p) override;
	//���������� ���� � ������ k � ������ � ������ p
	virtual void Del(Node* p) override; 		//�������� ���� p
	virtual void DelRoot() override; 			//�������� �����

	virtual Node* FindKey(int k, Node* p) override;
	//����� ���� � ������ k � ������ � ������ p
	virtual Node* FindMax(Node* p) override;
	//����� ���� � max ������ � ������ � ������ p
	virtual Node* FindMin(Node* p) override;
	//����� ���� � min ������ � ������ � ������ p

};

SBinTree::SBinTree(int n)		//n - ���������� ������, ����� ��������
{
	if (n == 0) root = NULL;
	else {
		root = new Node(rand() % 50);
		for (int i = 1; i < n; i++)	Add(rand() % 50, root);
	}
}
void SBinTree::DelRoot() {
	delete root;
}
SBinTree::SBinTree(int* a, int n)		//n - ���������� ������, ����� ��������
{
	if (n == 0) root = NULL;
	else {
		root = new Node(rand() % 50);
		for (int i = 1; i < n; i++)	Add(a[i], root);
	}
}

SBinTree::SBinTree(const SBinTree& T)
{
	if (T.root == NULL) root = NULL;
	else {
		root = new Node(T.root->key);
		Copy(T.root->left, root, 0);
		Copy(T.root->right, root, 1);
	}
}

SBinTree& SBinTree::operator= (const SBinTree& T)
{
	if (this != &T)
	{
		Clear(root);
		DelRoot();
		if (T.root == NULL)
		{
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
void SBinTree::Add(int k, Node* p)
//���������� ���� � ������ k � ������ � ������ p
{
	Node* q;
	if (k < p->key)
		if (p->left == NULL)
		{
			q = new Node(k);
			p->left = q;
			q->parent = p;
		}
		else Add(k, p->left);
	else if (p->right == NULL)
	{
		q = new Node(k);
		p->right = q;
		q->parent = p;
	}
	else Add(k, p->right);
}

void SBinTree::Del(Node* p)  		//�������� ���� p
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
	Node* t = p->left;
	if (t->right == NULL)
	{
		t->parent = q;
		if (q->left == p) q->left = t;
		else q->right = t;
		t->right = p->right;
		p->right->parent = t;
	}
	else {
		while (t->right != NULL) t = t->right;
		t->parent->right = t->left;
		if (t->left != NULL)
			t->left->parent = t->parent;

		t->left = p->left;
		t->right = p->right;
		p->left->parent = t;
		p->right->parent = t;

		t->parent = q;
		if (q->left == p) q->left = t;
		else q->right = t;
	}

	delete p;
	p = NULL;
	return;
}

Node* SBinTree::FindKey(int key, Node* p) {
	if (p)
	{
		if (p->key > key)
		{
			return FindKey(key, p->left);
		}
		else
			if (p->key < key)
			{
				return FindKey(key, p->right);
			}
	}

	return p;
}
Node* SBinTree::FindMax(Node* p) {
	if (p->right)
	{
		return FindMax(p->right);
	}

	return p;
}

Node* SBinTree::FindMin(Node* p) {
	if (p->left)
	{
		return FindMin(p->left);
	}

	return p;
}

