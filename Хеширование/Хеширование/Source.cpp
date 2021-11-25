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
	cout << "Массив случайных чисел" << endl;
	for (i = 0; i < 50; i++)
	{
		a[i] = (rand() % 99);
	}
	for (i = 0; i < 50; i++)
	{
		cout << a[i] << ' ';
	}
	cout << endl << endl << endl;
	cout << "Cоздали хеш-таблицу" << endl;
	List H[7];
	for (i = 0; i < 50; i++) 
	{
		H[(a[i] % 7)].AddToTail(a[i]);
	}
	cout << endl << endl;
	cout << "Выводим данную хеш-таблицу" << endl;
	cout << endl;
	for (i = 0; i < 7; i++)
	{
		H[i].PrintList(); 
		cout << endl;
	}

	int x, y;
	cout << endl << "Введите x и y: " << endl;
	//////////////////
	cin >> x >> y;
	Node* X, * Y;
	cout << endl;
	cout << "Если x нету, то добавляем, иначе удаляем" << endl;
	X = H[x % 7].FindKey(x);
	if (X != NULL)
	{
		int temp = X->GetKey();
		if (temp == x) 
		{
			H[x % 7].DelHead();//удаляем голову
		}
		else 
			H[x % 7].DelAfter(X);//добавляем х в список
	}
	else 
		H[(x % 7)].AddToTail(x);//добавляем в хвост списка x

	cout << "Если y нету, то добавляем, иначе удаляем" << endl;
	Y = H[y % 7].FindKey(y);//находим у в списке
	if (Y != NULL)
	{
		int temp = Y->GetKey();//получаем ключ списка
		if (temp == y) 
		{ 
			cout << '&'; 
			H[y % 7].DelHead();//удаляем голову
		}
		else 
		{
			cout << '#'; 
			H[y % 7].DelAfter(Y); //добавляем у в список
		}
	}
	else 
		H[(y % 7)].AddToTail(y);//добавляем в хвост списка у
	/////////////////
	cout << endl << "Новая таблица: " << endl << endl;
	for (i = 0; i < 7; i++)
	{
		H[i].PrintList(); cout << endl << endl;
	}



	cout << " МЕТОД ВНУТРЕННИХ ЦЕПОЧЕК " << endl;
	cout << endl << endl << "Массив: " << endl;
	for (i = 0; i < 50; i++) 
	{
		cout << a[i] << ' ';
	}
	cout << endl << endl << endl;
	Hash B(a, 50, 7);

	cout << "Таблица: " << endl;
	B.Print();//вывод таблицы

	cout << endl << endl << "Введите  x и y: " << endl;
	cin >> x >> y;
	cout << endl;
	cout << "Если x нету, то добавляем, иначе удаляем" << endl;
	int c = B.Find(x);//нахдим x
	if (c == -1) 
		B.Add(x);//добаваляем x
	else
		B.Del(x);//удаляем х
	cout << "Если y нету, то добавляем, иначе удаляем" << endl;
	int d = B.Find(y);
	if (d == -1) 
		B.Add(y);//добаваляем у
	else 
		B.Del(y);//удаляем у


	cout << endl << "Новая таблица: " << endl << endl;
	B.Print();//вывод таблицы
	cout << endl << endl;
	Hash C(B);//проверка конструктора копирования
	cout << "Проверка конструктора копирования: " << endl;
	C.Print();//вывод таблицы

	Hash D; 
	D = C;//проверка оператора присвоения
	cout << "Проверка оператора присвоения: " << endl;
	D.Print();
	return 0;
}
