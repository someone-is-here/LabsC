#include "BinaryTree.h"
using namespace std;
int main() {
	BinaryTree<int, int> d1 = BinaryTree<int, int>();
	cout << d1 << endl;
	d1.Insert(8, 14);
	cout << d1 << endl;
	d1.Insert(3, 15);
	cout << d1 << endl;
	d1.Insert(10, 13);
	cout << d1 << endl;
	d1.Insert(1, 103);
	cout << d1 << endl;
	d1.Insert(6, 1323);
	d1.Insert(4, 13323);
	d1.Insert(7, 13003);
	d1.Insert(14, 1300);
	d1.Insert(13, 100);
	cout << d1 << endl;
	cout << "Result: " << d1.Find(13) << endl;
	cout << d1[7] << endl;
	cout <<"fing next"<< d1.FindNext(11) << endl;
	cout << "find prev" << d1.FindPrevious(10) << endl;
	d1.Erase(6);
	cout << d1 << endl;
	BinaryTree<int, int> d2 = d1;
	cout << d2 << endl;
	return 0;
}