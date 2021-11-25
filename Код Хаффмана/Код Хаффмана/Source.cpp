#include "Code.h"
#include <iostream>
#include <stdio.h>
using namespace std;

int main()
{
	setlocale(LC_ALL, "RUS");
	char s[80];
	cout << "Введите строку: " << endl;
	cin >> s;
	cout << "Строка: " << endl << s << endl << endl;
	Code T1(s);
	cout << "Упорядоченный список: " << endl;
	T1.PrintList();
	cout << endl;

	cout << endl << "Дерево Т1: " << endl;
	T1.FormTree(); 
	T1.PrintTree(3, T1.GetHead());


	char* s1 = new char[100];
	T1.CodeText(s, s1, 100);
	int l = strlen(s1);
	cout << endl << "Код Хаффмана: " << endl;
	for (int i = 0; i < l; i++)
		cout << s1[i];
	cout << endl << endl;

	char* s2 = new char[23];
	T1.DecodeText(s1, s2, 23);
	int n = strlen(s2);
	for (int i = 0; i < n; i++)
		cout << s2[i];
	cout << endl;

}