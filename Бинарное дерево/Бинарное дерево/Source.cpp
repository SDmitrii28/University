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
	cout << " - ���������� ������ b ��� ������ ������������ � ����� ����������:" << endl;
	BinTree s(a, 7), b(10), c;
	cout << " - ����� ������ b:" << endl;
	b.Print();

	cout << " - ���������� ������ s ��� ������ ������������ � ����� �����������:" << endl;
	cout << " - ����� ������ s:" << endl;
	s.Print();
	Node* q;

	cout << " - ����� ���� � ������ k1 � ������ s � ������ p :";
	int k1;
	cout<<endl << "������� k1: ";
	cin >> k1;
	q = s.FindKey(k1, s.GetRoot());
	if (q != NULL) {
		cout << "������ ���� k1 ���� � ������ s" << endl;
	}
	else
		cout << "������� ����� k1 ��� � ������ s" << endl;
	cout << " - ����� ���� � min ������ � ������ s � ������ p: ";
	q = s.FindMin(s.GetRoot());
	cout << q->GetKey() << endl;

	cout << " - ����� ���� � max ������ � ������ s � ������ p: ";
	q = s.FindMax(s.GetRoot());
	cout << q->GetKey() << endl;

	cout << " - ����� ������ s � ������ p, � ������� �� �������� ����-������-�����, ����� ��������� �� �������" << endl;
	s.TreeTraversal_LCR(s.GetRoot());
	cout << endl;
	cout << endl;

	cout << " - ����� ������ s � ������ p, � ������� �� �������� ����-�����-������, ����� ��������� �� �������" << endl;
	s.TreeTraversal_LRC(s.GetRoot());
	cout << endl;
	cout << endl;

	cout << " - ����� ������ s � ������ p, � ������� �� �������� �����-����-������, ����� ��������� �� �������" << endl;
	s.TreeTraversal_RLC(s.GetRoot());
	cout << endl;
	cout << endl;

	cout << " - ����� ������ s � ������ p, � ������" << endl;
	s.WidthTraversal(s.GetRoot());
	cout << endl;
	cout << endl;

	cout << " - ���������� ���� � ������ k � ������ s: ";
	int k;
	cout << "������� k: ";
	cin >> k;
	s.Add(k, s.GetRoot());
	cout << " - ����� ������ s:" << endl;
	s.Print();

	cout << endl << " - �������� ������������� ���� p � ������ s";
	s.Del(s.FindMax(s.GetRoot()));
	cout << " - ����� ������ s:" << endl;
	s.Print();

		cout << " - �������� ����������: c = s:" << endl;
		c = s;
		c.Print();

		cout << " - ���������� ������ � s: ";
		cout << s.FindHight(s.GetRoot()) << endl;

		cout << " - ���������� ���������� ����� � s: ";
		cout << s.Count(s.GetRoot()) << endl;

		cout << "�����������: d(s):" << endl;
		BinTree d(s);
		d.Print();
		delete[]a;
}