#include <iostream>
#include "OSBinTree.h"
using namespace std;
int main() {
	setlocale(LC_ALL, "RUS");
	int n = 6;
	/*int d[6] = { -1, 10,20,30,40,50 };
	int p[6] = { -1, 2,1,1,5,3 };
	int q[6] = { 1,10,1,4,10,6 };*/
	int d[6] = { -1,10,20,30,40,50 };
	int p[6] = { -1,3,1,5,9,4 };
	int q[6] = { 8, 3,1,5,2,4 };
	OSBinTree A(d,p,q,n-1);
	cout << "Вывод дерева" << endl;
	A.Print();
}