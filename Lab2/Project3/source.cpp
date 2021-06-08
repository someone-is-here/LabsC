#include "Deque.h"
int main() {
	Deque<int> d0 = Deque<int>();

	cout << "Empty()" << d0.Empty() << endl;
	d0.Clear();

	for (int i = 1; i < 21; i++) {
		d0.PushBack(i);
	}
	d0.Show();
	auto iter = d0.end();
	for (int i = 0; i < 20; i++) {
		cout << *(--iter) << " ";
	}
	
	auto iter1 = d0.begin();
	cout <<"10[] " <<*iter1[13] << endl;
	cout << "iter1 " << *(11+iter1) << endl;
	int fDiff = (11 + iter) - iter;
	cout << "iter1 DIFF " << fDiff << endl;
	
	auto iter2 = --d0.end();
	fDiff = iter2 - iter1;
	cout << "iter1 DIFF " << fDiff << endl;
	cout << "iter2 " << *(iter2-10) << endl;
	iter2 -= 4;
	cout << *iter2 << endl;
	bool res = d0.begin() < (--d0.end());
	cout <<"Res"<< res << endl;
	for (int i = 0; i < 20; i++, iter1++) {
		cout << *iter1 << " ";
	}
	cout << *(--d0.end()) << " " << *d0.begin() << endl;

	cout << "Begin: " << *d0.begin() << endl;

	for (int i = 0; i < d0.Size(); i++) {
		if (i % d0.GetK() == 0) {
			cout << endl;
		}
		cout << d0[i] << " ";
	}
	cout << d0 << endl;
	for (int i = 1; i < 11; i++) {
		d0.PushFront(-i);
	}

	d0.Show();

	for (int i = 0; i < d0.Size(); i++) {
		if (i % d0.GetK() == 0) {
			cout << endl;
		}
		cout << d0[i] << " ";
	}

	for (int i = 1; i < 11; i++) {
		d0.PushFront(-i-10);
	}

	d0.Show();
	cout << endl << endl;

	for (int i = 1; i < 21; i++) {
		d0.PushBack(i+20);
	}

	res = (d0.end()-40) < (d0.begin()+19);
	cout << "Res" << res << endl;

	d0.Show();

	cout << *(--d0.end()) << " " << *d0.begin() << endl;

	for (int i = 0; i < d0.Size(); i++) {
		if (i % d0.GetK() == 0) {
			cout << endl;
		}
		cout << d0[i] << " ";
	}
	cout << endl << endl;
	
	
	for (int i = 0; i < 14; i++) {
		cout << d0.PopFront() << " ";
	}

	d0.Show();

	for (int i = 0; i < 4; i++) {
		cout << d0.PopBack() << endl;
	}

	d0.Show();

	cout << endl << endl;

	cout << d0.PopBack() << endl << endl;

	cout << endl << endl;

	for (int i = 0; i < 37; i++) {
		cout << d0.PopBack() << " ";
	}

	cout << endl;

	d0.Show();
	return 0;
}