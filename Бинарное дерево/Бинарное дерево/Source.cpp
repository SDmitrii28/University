#include <iostream>
#include "BinTree.h"
#include <cstdlib>
#include <ctime>
using namespace std;
int main() {
	setlocale(LC_ALL, "rus");
	srand(time(NULL));
	int* a;
	a = new int[10];
	for (int i = 0; i < 7; i++) {
		a[i] = rand() % 50;
	}
	cout << " - Построение дерева b при помощи конструктора с одним аргументом:" << endl;
	BinTree s(a, 7), b(10), c;
	cout << " - Вывод дерева b:" << endl;
	b.Print();

	cout << " - Построение дерева s при помощи конструктора с двумя аргументами:" << endl;
	cout << " - Вывод дерева s:" << endl;
	s.Print();
	Node* q;

	cout << " - Поиск узла с ключом k1 в дереве s с корнем p :";
	int k1;
	cout<<endl << "Введите k1: ";
	cin >> k1;
	q = s.FindKey(k1, s.GetRoot());
	if (q != NULL) {
		cout << "Данный ключ k1 есть в дереве s" << endl;
	}
	else
		cout << "Данного ключа k1 нет в дереве s" << endl;
	cout << " - Поиск узла с min ключом в дереве s с корнем p: ";
	q = s.FindMin(s.GetRoot());
	cout << q->GetKey() << endl;

	cout << " - Поиск узла с max ключом в дереве s с корнем p: ";
	q = s.FindMax(s.GetRoot());
	cout << q->GetKey() << endl;

	cout << " - Обход дерева s с корнем p, в глубину по принципу лево-корень-право, ключи выводятся на консоль" << endl;
	s.TreeTraversal_LCR(s.GetRoot());
	cout << endl;
	cout << endl;

	cout << " - Обход дерева s с корнем p, в глубину по принципу лево-право-корень, ключи выводятся на консоль" << endl;
	s.TreeTraversal_LRC(s.GetRoot());
	cout << endl;
	cout << endl;

	cout << " - Обход дерева s с корнем p, в глубину по принципу право-лево-корень, ключи выводятся на консоль" << endl;
	s.TreeTraversal_RLC(s.GetRoot());
	cout << endl;
	cout << endl;

	cout << " - Обход дерева s с корнем p, в ширину" << endl;
	s.WidthTraversal(s.GetRoot());
	cout << endl;
	cout << endl;

	cout << " - Добавление узла с ключом k в дерево s: ";
	int k;
	cout << "Введите k: ";
	cin >> k;
	s.Add(k, s.GetRoot());
	cout << " - Вывод дерева s:" << endl;
	s.Print();

	cout << endl << " - Удаление максимального узла p в дереве s";
	s.Del(s.FindMax(s.GetRoot()));
	cout << " - Вывод дерева s:" << endl;
	s.Print();

		cout << " - Оператор присвоения: c = s:" << endl;
		c = s;
		c.Print();

		cout << " - Нахождение высоты в s: ";
		cout << s.FindHight(s.GetRoot()) << endl;

		cout << " - Нахождение количество узлов в s: ";
		cout << s.Count(s.GetRoot()) << endl;

		cout << "Копирования: d(s):" << endl;
		BinTree d(s);
		d.Print();
		delete[]a;
}