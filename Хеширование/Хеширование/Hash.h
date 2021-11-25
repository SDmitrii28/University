#pragma once
#include <iostream>
using namespace std;

class Usel
{
	int key, next;
public:
	Usel(int k = -1, int N = -1)
	{
		key = k; next = N;
	}
	void PrintUsel()
	{
		cout << key << "  " << next << endl;
	}
	friend class Hash;
};

class Hash
{
	int dim;  		//размер хеш-таблицы
	int p;			//хеш-функци€: h=x%p
	Usel* TAB;

public:
	Hash()
	{
		dim = 2;
		p = 2; 
		TAB = new Usel[dim];
	}
	Hash(int a[], int n, int P) 	//n--размер массива a
	{
		dim = n + 5; p = P;
		TAB = new Usel[dim];
		for (int i = 0; i < n; i++)
			Add(a[i]);
	}							   //p=P
	~Hash()
	{
		delete TAB;
	}
	Hash(const Hash& T)
	{
		dim = T.dim; p = T.p; TAB = new Usel[dim];
		for (int i = 0; i < dim; i++)
		{
			TAB[i].key = T.TAB[i].key;
			TAB[i].next = T.TAB[i].next;
		}
	}
	Hash& operator= (const Hash& T)
	{
		delete[] TAB;
		p = T.p; dim = T.dim;
		TAB = new Usel[T.dim];
		for (int i = 0; i < dim; i++)
		{
			TAB[i].key = T.TAB[i].key;
			TAB[i].next = T.TAB[i].next;
		}
		return *this;
	}
	void Add(int k)
	{
		int h = k % p;
		if (TAB[h].key == -1) TAB[h].key = k;
		else	//возникла коллизи€
		{
			int j;
			//размещаем k  в массиве TAB
			for (j = dim - 1; j >= 0; j--)
				if (TAB[j].key == -1)
				{
					TAB[j].key = k; break;
				}
			//поиск последнего эл-та данной коллизии
			int t = h;
			while (TAB[t].next != -1) t = TAB[t].next;
			TAB[t].next = j;
		}
	}//добавление эл-та в хеш-таблицу
	int Find(int k)
	{
		int h = k % p;
		if (TAB[h].key == k) return h;
		else while (h != -1)
		{
			h = TAB[h].next;
			if (TAB[h].key == k) return h;
		}
		cout << "Ёлемента " << k << " в массиве нет. ";
		return -1;
	}
	void Del(int k)
	{
		int h = k % p; 
		int q;
		while (TAB[h].key != k && h != -1)
		{
			//cout << '&';
			q = h;
			h = TAB[h].next;
		}
		if (h == -1) cout << "Ёлемента в массиве нет. ";
		else // если элемент найден
		{
			if ((TAB[h].key == k) && (TAB[h].next == -1))
			{
				TAB[q].next = -1;
				TAB[h].key = -1;
			}
			else
			{
				int e = TAB[TAB[h].next].next;
				int b = TAB[TAB[h].next].key;
				TAB[TAB[h].next].next = -1;
				TAB[TAB[h].next].key = -1;
				TAB[h].key = b;
				TAB[h].next = e;
			}
		}
	}
	void Print()
	{
		int i;
		for (i = 0; i < dim; i++)
		{
			cout << i << ") ";
			TAB[i].PrintUsel();
		}
	}
};
