#include <iostream>
#include "SSBinTree.h"
using namespace std;
int main() {
	int a[10] = { 6,8,69,95,4,20,75,46,27,50 };
	SSBinTree tree(a, 10);
	tree.Print();

	tree.Add(500, tree.GetRoot());
	tree.Print();

	Node* q = tree.FindKey(50, tree.GetRoot());
	tree.Del(q);
	tree.Print();
	cout << endl;
}