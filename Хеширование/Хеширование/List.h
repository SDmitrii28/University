#pragma once
#pragma once
#include <iostream>
using namespace std;

class Node
{
	int key;
	Node* next;
public:
	Node(int k = -1, Node* N = nullptr)
	{
		key = k; next = N;
	}
	int GetKey() { return key; }
	friend class List;
};

class List
{
	Node* head;

public:
	List() {
		head = NULL;
	}
	List(int a[], int n)
	{
		head = new Node(a[0]);
		head->next = nullptr;
		for (int i = 1; i < n; i++)
			AddToTail(a[i]);
	}
	List(int n)
	{
		int i, x;
		x = rand() % 100;
		head = new Node(x);
		head->next = nullptr;

		for (i = 0; i < n; i++)
		{
			x = rand() % 100;
			AddToTail(x);
		}
	}
	~List()
	{
		this->Clear();
	}
	List(const List& X)
	{
		head = new Node;
		head->next = nullptr;
		head = X.head;
		Node* q = X.head->next;
		while (q != nullptr)
		{
			AddToTail(q->key);
			q = q->next; // перешли к следующему узлу
		}
	}
	List& operator= (const List& X)
	{
		Clear();
		head = X.head;
		Node* q = X.head->next;
		while (q != nullptr)
		{
			AddToTail(q->key);
			q = q->next; // перешли к следующему узлу
		}
		return *this;
	}

	void AddToHead(int k)
	{
		Node* q = new Node;
		q->key = k;
		q->next = head;
		head = q;
	}
	void AddToTail(int k)
	{
		Node* t = head;
		if (t == NULL) { AddToHead(k); }
		else {
			Node* q = head;
			while (q->next) q = q->next;
			AddAfter(k, q);
		}
	}
	void AddAfter(int k, Node* pr)
	{
		Node* q = new Node;
		q->key = k;
		q->next = pr->next;
		pr->next = q;
	}

	void DelHead()
	{
		if (head->next == nullptr) return;
		Node* t = head;
		head = head->next;
		delete t;
	}
	void DelTail()
	{
		if (head == nullptr) return;
		if (head->next == nullptr)
		{
			DelHead(); return;
		}
		Node* q = new Node;
		while (q->next != nullptr) q = q->next;
		Del(q);
	}
	void DelAfter(Node* p)
	{
		Node* q = head;
		while (q != p) { q = q->next; }
		Node* t = q->next->next;
		delete q->next;
		q->next = t;
	}

	void Del(Node* p)
	{
		if (head == nullptr) return;
		if (head == p) DelHead();

		Node* q = head; Node* t = head->next;
		while (t != p && t)
		{
			t = t->next;
			q = q->next;
		}
		if (!t) return;
		q->next = t->next;
		delete t;
	}

	Node* FindKey(int k)
	{
		Node* M = NULL;
		Node* q = head;
		if (q == NULL)
		{
			cout << "—писок пустой." << endl;
			return M;
		}
		else
		{
			if (q->key == k || q->next->key == k) return head;
			//  огда искомый узел - 2-ый в списке
			q = q->next;
			while (q->next != NULL)
			{
				if (q->next->key == k)
				{
					//cout << '&' << q->key << '&';
					return q;
				}
				q = q->next;
			}
			cout << "Ёлемент " << k << " отсутствует в списке. "
				<< endl; return M;
		}
	}


	Node* Findpos(int pos)
	{
		Node* M = NULL; int count = 0;
		Node* q = head;
		if (q == NULL)
		{
			cout << "—писок пустой." << endl;
			return M;
		}
		else
		{
			for (; count < pos && q != NULL; count++)
				q = q->next;
			if (count == pos) return q;
			else
			{
				cout << "Ёлемента под таким номером нет в списке. " << endl; return M;
			}
		}
	}
	bool Empty()
	{
		Node* q = head;
		if (q == NULL) return true;
		else return false;
	}
	void Clear()
	{
		Node* t = head;
		while (t->next != NULL)
		{
			DelAfter(t);
		}
		DelHead();
	}
	void PrintList()
	{
		Node* q = head;
		if (q == nullptr)
			cout << "—писок пустой." << endl;
		else {
			while (q != NULL)
			{
				cout << q->key << ' ';
				q = q->next;
			}
		}
	}
};
