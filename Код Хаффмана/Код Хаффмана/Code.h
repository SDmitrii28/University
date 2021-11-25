#pragma once
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <iostream>
using namespace std;
//класс узел
class Node
{
	char* str;//информационное поле, хранить будет букву
	int freq;//частота
	Node* next, * left, * right;//поля связей, следующий, левый и правый потомок

public:
	Node() {
		str = new char[1]; str[0] = '\0';
		freq = 0; next = left = right = NULL;
	}
	Node(char s[], int fr = 0, Node* N = NULL, Node* L = NULL, Node* R = NULL)
	{
		int n = strlen(s);
		str = new char[n + 1]; strcpy_s(str, n + 1, s);
		freq = fr; next = N; left = L; right = R;
	}
	~Node() { delete[]str; }

	friend class Code;
};

class Code
{
	Node* head;
	int type; 		//type==0 -- линейный список, type==1 -- дерево

	//вспомогательные функции
	bool Find(char ch, char p[]); //поиск символа ch в строке p;
	void Copy(Node* q, Node* p, int f);
	//копирование дерева с корнем q, 
	//p - узел, к которому присоединяется копия
	//f=0 - копируемое дерево будет левым потомком для p;
	//f=1 - копируемое дерево будет правым потомком для p.
	void CopyList(Node* q, Node* p); // вспомогательная
public:
	void f() { 
		cout << head->str[0];
	}
	Code() { head = NULL; type = 0; }
	Code(char p[]);		//создает список из символов строки
	~Code() { Clear(head, type); };//деструктор
	Code(const Code&);//копирование
	Code& operator= (const Code&);//оператор присвоения

	void AddToTail(char s[], int k);//добавление в хвост
	void AddToTail(Node* p);

	void AddToHead(char s[], int k);
	void AddToHead(Node* p);

	void AddAfter(Node* pr, char s[], int k);
	void AddAfter(Node* pr, Node* p);	//размещение узла p после узла pr

	void DelHead();
	void Clear(Node* p, int f);
	void Clear(Node* pr, Node* t, int f);
	//t-- удаляемый узел, pr -- его родитель
	bool Empty();

	void PrintList();
	void PrintTree(int k, Node* p);

	Node* GetHead() { return head; }

	void FormTree();		//преобразование списка в дерево
	void CodeText(char s[], char code[], int n);
	//кодирование строки s, n -- размер строки code
	void DecodeText(char code[], char s[], int n);
	//декодирование строки code, n -- размер строки s

};
Code::Code(char p[])
{
	type = 0;
	//создание массива букв и их частот
	int i, TAB[256] = { 0 };
	for (i = 0; p[i]; i++)
		TAB[p[i]]++;

	//поиск 1-го (по ASCII) символа из p и создание головы списка
	char s[2]; s[1] = '\0';
	for (i = 0; i < 256 && TAB[i] == 0; i++);

	if (i == 256) { puts("string is empty"); head = NULL; return; }
	s[0] = i;
	head = new Node(s, TAB[i]);
	i++;

	//формирование упорядоченного по частоте линейного 
	//списка символов строки p
	for (; i < 256; i++)
		if (TAB[i] != 0)
		{
			//cout << '*'; cout << TAB[i];
			s[0] = i;
			if (TAB[i] < head->freq) AddToHead(s, TAB[i]);
			else {
				//cout << '%';
				Node* t = head;
				while (t->next && t->next->freq < TAB[i])
					t = t->next;
				if (t->next == NULL) AddToTail(s, TAB[i]);
				else AddAfter(t, s, TAB[i]);
			}
		}
}


void Code::FormTree()	//преобразование списка в дерево
{
	if (head == NULL)
	{
		puts("list is empty"); return;
	}

	type = 1;
	Node* q, * p1, * p2, * t;
	int n1, n2, fr;
	char* s;

	while (head->next != 0)
	{//создание нового узла
		p1 = head;  p2 = head->next;
		n1 = strlen(p1->str); n2 = strlen(p2->str);
		s = new char[n1 + n2 + 1];
		strcpy_s(s, n1 + n2 + 1, p1->str);
		strcat_s(s, n1 + n2 + 1, p2->str);
		fr = p1->freq + p2->freq;
		q = new Node(s, fr, NULL, p1, p2);
		head = p2->next;
		delete[]s;

		//размещение q в списке;
		t = head;
		if (t == NULL) head = q;
		else {
			while (t->next && t->next->freq < fr)
				t = t->next;
			if (t->next == NULL) AddToTail(q);
			else AddAfter(t, q);
		}
	}
}

void Code::CodeText(char s[], char code[], int n)      //кодирование строки s
{
	if (type == 0) { puts("coding is impossibile"); return; }

	//создание массива букв и их частот
	int i, TAB[256] = { 0 };
	for (i = 0; s[i]; i++)
		TAB[s[i]]++;

	//создание кодовой таблицы
	char CodeTAB[256][10];
	Node* t;
	for (i = 0; i < 256; i++)
		CodeTAB[i][0] = '\0';

	for (i = 0; i < 256; i++)
		if (TAB[i] != 0)
		{
			t = head;
			while (t->left || t->right)
				if (t->left && Find(i, t->left->str))
				{
					strcat_s(CodeTAB[i], 10, "0"); t = t->left;
				}
				else { strcat_s(CodeTAB[i], 10, "1"); t = t->right; }
		}

	//формирование закодированного текста:
	code[0] = '\0';
	for (i = 0; s[i]; i++)
		strcat_s(code, n, CodeTAB[s[i]]);
}

void Code::DecodeText(char code[], char s[], int n)
{
	if (type == 0) { puts("coding is impossibile"); return; }
	int l = strlen(code);
	Node* t = head; int j = 0; int i = 0;
	while (i < l)
	{
		t = head;
		while (t->left || t->right)
		{
			if (code[i] == '0')
			{
				t = t->left;
				if (t->left == NULL && t->right == NULL && j < n)
				{
					s[j] = t->str[0]; j++;
				}
			}
			else
			{
				t = t->right;
				if (t->left == NULL && t->right == NULL && j < n)
				{
					s[j] = t->str[0]; j++;
				}
			}
			i++;
		}
	}
	s[j] = '\0';
}

void Code::PrintTree(int k, Node* p)
//вывод дерева на консоль, 
//k - отступ от левой границы консоли
{
	cout << endl;
	if (p == NULL) return;
	PrintTree(k + 8, p->right);
	for (int i = 0; i < k; i++) cout << ' ';

	for (int j = 0; p->str[j]; j++)
	{
		cout << p->str[j];
	}

	PrintTree(k + 8, p->left);
}

bool Code::Find(char ch, char p[])
{
	int m = strlen(p);
	for (int i = 0; i < m; i++)
		if (p[i] == ch) return true;
	return false;
}

void Code::AddToTail(char s[], int k)
{
	Node* B = new Node(s, k);
	Node* t = head;
	while (t->next != NULL)  t = t->next;
	t->next = B;
}

void Code::AddToTail(Node* p)
{
	Node* t = head;
	while (t->next != NULL)  t = t->next;
	t->next = p;
}

void Code::AddToHead(char s[], int k)
{

	Node* B = new Node(s, k);
	Node* t = head;
	B->next = head;
	head = B;
}

void Code::AddToHead(Node* p)
{
	Node* t = head;
	p->next = t;
	head = p;
}

void Code::AddAfter(Node* pr, char s[], int k)
{
	Node* B = new Node(s, k);
	Node* t = pr->next;
	pr->next = B; B->next = t;
}

void Code::AddAfter(Node* pr, Node* p)
{
	Node* t = pr->next;
	pr->next = p;
	p->next = t;
}


void Code::PrintList()
{
	Node* u = head;
	if (u == NULL) { cout << '&'; exit; }
	while (u)
	{
		//cout << '*';
		cout << u->str[0];
		u = u->next;
	}
}

void Code::Copy(Node* q, Node* p, int f)
{
	if (q == NULL) return;
	Node* t = new Node(q->str, f);
	//t->parent = p;
	if (f == 0) p->left = t;
	else p->right = t;
	Copy(q->left, t, 0);
	Copy(q->right, t, 1);
}

void Code::CopyList(Node* q, Node* p)
{
	if (q == NULL) return;
	Node* t = new Node(q->str, q->freq);
	p->next = t;
	CopyList(q->next, t);
}

Code::Code(const Code& T)
{
	type = T.type;
	if (T.head == NULL) head = NULL;
	else {
		if (type == 0)
		{
			head = new Node(T.head->str, T.head->freq);
			CopyList(T.head->next, head);
		}
		else
		{
			head = new Node(T.head->str, T.head->freq);
			Copy(T.head->left, head, 0);
			Copy(T.head->right, head, 1);
		}
	}
}

Code& Code::operator=(const Code& T)
{
	type = T.type;
	if (T.head == NULL) { head = NULL; }
	else {
		if (type == 0)
		{
			delete head;
			head = new Node(T.head->str, T.head->freq);
			CopyList(T.head->next, head);
			/*Clear(T.head);
			Node* q = T.head->next;
			while (q != NULL)
			{
				AddToTail(q);
				q = q->next; // перешли к следующему узлу
			}*/
		}
		else
		{
			if (this != &T)
			{
				head = new Node(T.head->str, T.head->freq);
				Copy(T.head->left, head, 0);
				Copy(T.head->right, head, 1);
			}
		}
	}
	return *this;
}

void Code::Clear(Node* p, int f)
{
	if (f == 0)
	{
		Node* w = head; Node* q;
		while (w)
		{
			q = w;
			w = q->next;
			delete q;
		}
	}
	else
	{
		if (p != NULL)
		{
			Clear(p->left, 1);
			Clear(p->right, 1);
			{p = NULL; }
		}
	}
}

void Code::Clear(Node* pr, Node* t, int f)
{
	if (f == 0)
	{
		pr->next = t->next;
		delete t;
	}
	else
	{
		Node* q = pr;
		//удаление листа
		if (t->left == NULL && t->right == NULL)
		{
			//cout << '&';
			if (q->left == t) q->left = NULL;
			else q->right = NULL;
			delete t;
			return;
		}
		//у p нет левой ветви
		if (t->left == NULL && t->right != NULL)
		{
			if (q->left == t) q->left = t->right;
			else q->right = t->right;
			//p->right->parent = q;
			delete t;
			return;
		}
		//у p нет правой ветви
		if (t->left != NULL && t->right == NULL)
		{
			if (q->left == t) q->left = t->left;
			else q->right = t->left;
			//p->left->parent = q;
			delete t;
			return;
		}

		//у p есть оба поддерева
		Node* w = t;
		while (w->left != NULL) w = w->left;//

		//вырезаем t из дерева
		/*if (w->right == NULL)
			w->parent->left = NULL;
		else {
			t->parent->left = t->right;
			t->right->parent = t->parent;
		}*/
		//заменяем p узлом t
		w->left = t->left;
		w->right = t->right;
		//w->parent = q;

		if (q->left == t) q->left = w;
		else q->right = w;

		if (t->left != NULL)
			//t->left->parent = w;

		//t->right->parent = w;
			delete t;
		return;
	}
}

bool Code::Empty()
{
	if (head == NULL) return true;
	else return false;
}
