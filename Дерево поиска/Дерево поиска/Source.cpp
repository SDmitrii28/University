#include <iostream>
#include "SBinTree.h"
using namespace std;
int main() {
	setlocale(LC_ALL, "rus");
	srand(time(NULL));
	int* mas;
	mas = new int[10];
	for (int i = 0; i < 10; i++) {
		mas[i] = rand() % 50;
	}
	SBinTree a(10), b(mas,10), c;
	cout << " - Построение дерева при помощи конструктора с одним аргументом:" << endl;
	cout << " - Вывод дерева a:" << endl;
	a.Print();

	cout << " - Построение дерева при помощи конструктора с двумя аргументами:" << endl;
	cout << " - Вывод дерева b:" << endl;
	b.Print();
	Node* q;

	cout << " - Поиск узла с ключом k1 в дереве a с корнем p :";
	int k1;
	cout << "Введите k1: ";
	cin >> k1;
	q = a.FindKey(k1, a.GetRoot());
	cout << q << endl;

	cout << " - Поиск узла с min ключом в дереве a с корнем p: ";
	q = a.FindMin(a.GetRoot());
	cout << q->GetKey() << endl;

	cout << " - Поиск узла с max ключом в дереве a с корнем p: ";
	q = a.FindMax(a.GetRoot());
	cout << q->GetKey() << endl;

	cout << endl;
	cout << endl;

	cout << " - Добавление узла с ключом k в дерево a: ";
	int k;
	cout << "Введите k: ";
	cin >> k;
	a.Add(k, a.GetRoot());
	cout << " - Вывод дерева a:" << endl;
	a.Print();

	cout << endl << " - Удаление узла p в дереве a";
	a.Del(a.FindMax(a.GetRoot()));
	cout << " - Вывод дерева a:" << endl;
	a.Print();

	cout << " - Оператор присвоения: c = a:" << endl;
	c = a;
	c.Print();

	cout << "Копирования: d(c):" << endl;
	BinTree d(c);
	d.Print();
}