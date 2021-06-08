#include "vector.h"
#include "list.h"

int main() {
	List<int> l0{1,2,3,4,5};
	List<int> l1 = l0;
	cout << l1 << endl;
	cout << l0.Empty() << endl;
	l0.PushFront(4);
	l0.PushFront(44);
	l0.PushBack(13);
	l0.PushBack(14);
	l0.PushBack(15);
	l0.PushBack(0);
	l0.PushBack(10);
	l0.PushBack(1230);
	l0.Show();
	l0.ReverseShow();
	cout << l0.PopBack() << " " << l0.PopBack() << endl;
	l0.Show();
	cout << l0.PopFront() << " " << l0.PopFront() << endl;
	l0.Show();
	l0.PopBack();
	l0.Show();
	l0 = { 0,11,1,12,2,13 };
	cout << l0 << endl;
	auto iter = l0.begin();
	auto iter23 = ++l0.begin();
	cout << "list[0] " <<*(iter[0]) << endl;
	cout << "list[1] " << *(iter[1]) << endl;
	cout << "list[2] " << *(iter[2]) << endl;
	cout << "list[3] " << *(iter[3]) << endl;
	cout << "list[5] " << *(iter23[4]) << endl << endl;
	cout << *(iter23) << " " << *(iter23 + 3) << " " << *(iter23 - 1) << endl;
	cout << *(iter23) << " " << *(3 + iter23) << " " << *(1 - iter23) << endl; 
	auto iterIt = ++l0.begin();
	auto iterIt1 = --l0.end();
	cout <<"Dif: "<< iterIt1 - iter << endl;
	auto iter234 = iter23 + 3;
	cout << *(iter23) << " "<<*(2 + iter23)<<" ";
	cout << *(iter234) << endl;

	cout << *(3 + iter23) << endl;
	if (iter <= iter23) {
		cout << "true" << endl;
	}

	Vector<int> v0{1,2,3,4,5,6,5,4,3,2,1};
	cout << v0 << endl;
	cout << v0.Empty() << endl;
	v0 = { 1,2,3,4,5,6,7 };
	cout << v0.Empty() << endl;
	cout << v0 << endl;
	cout << v0 << endl;
	v0.PushBack(13);
	v0.PushBack(14);
	v0.PushBack(15);
	cout << v0 << endl;
	cout << v0 << endl << endl << endl;
	cout << *v0.begin() << endl;
	cout << *(3 + v0.begin()) << endl << endl;
	cout << *(v0.begin()+3) << endl;
	auto iter1 = v0.begin();
	cout <<"Iter iter[4]"<< *(iter1[4]) << endl;
	cout << "Iter iter[3]" << *(iter1[3]) << endl;
	cout << "Iter iter[0]" << *(iter1[0]) << endl;
	cout << "Iter iter[7]" << *(iter1[7]) << endl;
	iter1 += 5;
	cout << "Result: " << *(iter1) << endl;
	iter1 -= 4;
	cout << "Result: " << *(iter1) << endl;
	auto iter2 = v0.begin();
	if (iter2 <= ++iter1) {
		cout << iter1 - iter2 << endl;
	} 
	iter2 = v0.end();
	cout << "end()--" << *(--iter2) << endl;
	cout << *(iter2 - 3) << endl;
	cout << *(3 - iter2) << endl;
	cout << v0[9] << endl;
	for (int i = 1; i < 10; i++) {
		v0.PushBack(i);
	}
	cout << v0 << endl;
	v0.Resize(15);
	cout << v0 << endl;
	v0.Resize(17);
	cout << v0 << endl;
	cout << v0.Size();
	return 0;
}