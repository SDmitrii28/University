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
	cout << " - ���������� ������ ��� ������ ������������ � ����� ����������:" << endl;
	cout << " - ����� ������ a:" << endl;
	a.Print();

	cout << " - ���������� ������ ��� ������ ������������ � ����� �����������:" << endl;
	cout << " - ����� ������ b:" << endl;
	b.Print();
	Node* q;

	cout << " - ����� ���� � ������ k1 � ������ a � ������ p :";
	int k1;
	cout << "������� k1: ";
	cin >> k1;
	q = a.FindKey(k1, a.GetRoot());
	cout << q << endl;

	cout << " - ����� ���� � min ������ � ������ a � ������ p: ";
	q = a.FindMin(a.GetRoot());
	cout << q->GetKey() << endl;

	cout << " - ����� ���� � max ������ � ������ a � ������ p: ";
	q = a.FindMax(a.GetRoot());
	cout << q->GetKey() << endl;

	cout << endl;
	cout << endl;

	cout << " - ���������� ���� � ������ k � ������ a: ";
	int k;
	cout << "������� k: ";
	cin >> k;
	a.Add(k, a.GetRoot());
	cout << " - ����� ������ a:" << endl;
	a.Print();

	cout << endl << " - �������� ���� p � ������ a";
	a.Del(a.FindMax(a.GetRoot()));
	cout << " - ����� ������ a:" << endl;
	a.Print();

	cout << " - �������� ����������: c = a:" << endl;
	c = a;
	c.Print();

	cout << "�����������: d(c):" << endl;
	BinTree d(c);
	d.Print();
}