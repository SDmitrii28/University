#include <iostream>
#include "Hash.h"
#include "List.h"
using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	int a[50];
	int p = 7;
	int h, i;
	cout << "������ ��������� �����" << endl;
	for (i = 0; i < 50; i++)
	{
		a[i] = (rand() % 99);
	}
	for (i = 0; i < 50; i++)
	{
		cout << a[i] << ' ';
	}
	cout << endl << endl << endl;
	cout << "C������ ���-�������" << endl;
	List H[7];
	for (i = 0; i < 50; i++) 
	{
		H[(a[i] % 7)].AddToTail(a[i]);
	}
	cout << endl << endl;
	cout << "������� ������ ���-�������" << endl;
	cout << endl;
	for (i = 0; i < 7; i++)
	{
		H[i].PrintList(); 
		cout << endl;
	}

	int x, y;
	cout << endl << "������� x � y: " << endl;
	//////////////////
	cin >> x >> y;
	Node* X, * Y;
	cout << endl;
	cout << "���� x ����, �� ���������, ����� �������" << endl;
	X = H[x % 7].FindKey(x);
	if (X != NULL)
	{
		int temp = X->GetKey();
		if (temp == x) 
		{
			H[x % 7].DelHead();//������� ������
		}
		else 
			H[x % 7].DelAfter(X);//��������� � � ������
	}
	else 
		H[(x % 7)].AddToTail(x);//��������� � ����� ������ x

	cout << "���� y ����, �� ���������, ����� �������" << endl;
	Y = H[y % 7].FindKey(y);//������� � � ������
	if (Y != NULL)
	{
		int temp = Y->GetKey();//�������� ���� ������
		if (temp == y) 
		{ 
			cout << '&'; 
			H[y % 7].DelHead();//������� ������
		}
		else 
		{
			cout << '#'; 
			H[y % 7].DelAfter(Y); //��������� � � ������
		}
	}
	else 
		H[(y % 7)].AddToTail(y);//��������� � ����� ������ �
	/////////////////
	cout << endl << "����� �������: " << endl << endl;
	for (i = 0; i < 7; i++)
	{
		H[i].PrintList(); cout << endl << endl;
	}



	cout << " ����� ���������� ������� " << endl;
	cout << endl << endl << "������: " << endl;
	for (i = 0; i < 50; i++) 
	{
		cout << a[i] << ' ';
	}
	cout << endl << endl << endl;
	Hash B(a, 50, 7);

	cout << "�������: " << endl;
	B.Print();//����� �������

	cout << endl << endl << "�������  x � y: " << endl;
	cin >> x >> y;
	cout << endl;
	cout << "���� x ����, �� ���������, ����� �������" << endl;
	int c = B.Find(x);//������ x
	if (c == -1) 
		B.Add(x);//���������� x
	else
		B.Del(x);//������� �
	cout << "���� y ����, �� ���������, ����� �������" << endl;
	int d = B.Find(y);
	if (d == -1) 
		B.Add(y);//���������� �
	else 
		B.Del(y);//������� �


	cout << endl << "����� �������: " << endl << endl;
	B.Print();//����� �������
	cout << endl << endl;
	Hash C(B);//�������� ������������ �����������
	cout << "�������� ������������ �����������: " << endl;
	C.Print();//����� �������

	Hash D; 
	D = C;//�������� ��������� ����������
	cout << "�������� ��������� ����������: " << endl;
	D.Print();
	return 0;
}
