#include "Map.h"
#include "Set.h"
#include "Set2.h"
#include "Map2.h"
#include <typeInfo>

using namespace std;

int main() {
	Set2<int> set2 = Set2<int>();
	set2.Insert(13);
	set2.Insert(14);
	cout << "Set2: " << endl << set2 << endl;
	auto it = set2.begin();
	cout << "It* " << *it << endl;
	cout << "It2* " << *(++it) << endl;
	cout << typeid(it).name() << endl;

	Map< int, int> d1 = Map<int, int>();
	cout << d1 << endl;
	cout << "Insert: " << endl;
	d1.Insert(8, 14);
	d1.Insert(3, 15);
	d1.Insert(10, 13);
	d1.Insert(1, 103);
	d1.Insert(6, 1323);
	d1.Insert(4, 13323);
	d1.Insert(7, 13003);
	d1.Insert(14, 1300);
	d1.Insert(13, 100);
	cout << "Result: " << d1.Find(13) << endl;
	cout << d1[7] << endl;
	cout << "fing next" << d1.FindNext(11) << endl;
	cout << "find prev" << d1.FindPrevious(10) << endl;
	cout << d1 << endl;
	cout << "Erase" << endl;

	d1.Erase(3);
	cout << d1 << endl;
	d1.showList();
	cout << "NewMap" << endl;
	Map<int,int> d2 = d1;
	cout << d2 << endl;
	cout << "iTER: " << endl;
	auto iterator = d1.begin();
	cout <<endl<< *iterator << endl;
	d1.showList();
	cout << endl << *(iterator--) << endl;
	cout << *iterator << endl;

	auto iterator123 = d1.end();
	cout << *(--iterator123) << endl;

	cout << *(++iterator) << endl;
	cout << "Map2()" << endl;
	cout << typeid(iterator).name() << endl;
	cout << typeid(iterator123).name() << endl;
	Map2<int, int> map2 = Map2<int,int>();

	map2.Insert(8, 14);
	map2.Insert(3, 15);
	map2.Insert(10, 13);
	map2.Insert(1, 103);
	map2.Insert(6, 1323);
	map2.Insert(4, 13323);
    map2.Insert(7, 13003);
	map2.Insert(14, 1300);
	map2.Insert(13, 100);

	cout << map2 << endl;
	cout << endl << endl;
	
	map2.Insert(17, 10320);
	cout << map2 << endl;	
	cout << map2.Find(10) << endl;
	cout << map2.Find(17) << endl;
	map2.Insert(2, 16663003);
	cout << map2 << endl;
	cout <<"[][][]"<< map2[17] << endl;
	map2.Insert(5, 1666909003);
	cout << map2 << endl;

	auto iter = map2.end();
	cout << typeid(iter).name() << endl;
	map2.Erase(17);
	cout << "----" << endl;
	cout << "IterList: " << endl;
	cout << "Iter: " << *iter << endl;
	cout << "Iter2: " << *(iter--) << endl;
	cout << "Iter23: " << *(iter) << endl;
	map2.Erase(1);
	cout << "----" << endl;
	cout << "IterList: " << endl;
	cout << "Iter: " << *(--iter) << endl;
	cout << "Iter2: " << *(iter--) << endl;
	cout << "Iter23: " << *(iter) << endl;

	Set<int> set = Set<int>();
	set.Insert(13);
	set.Insert(14);
	set.Insert(8);
	set.Insert(3);
	set.Insert(10);
	set.Insert(1);
	set.Insert(6);
	set.Insert(4);
	set.Insert(7);

	cout << set << endl;
	cout << endl << endl;

	set.Insert(17);

	cout << "Set: " << endl << set << endl;
	auto iter0 = set.begin();
	cout << typeid(iter0).name() << endl;
	cout << *iter0 << endl;
	cout << *(--iter0) << endl;
	cout << *(--iter0) << endl;
	cout << *(--iter0) << endl;
	cout << *(iter0++) << endl;
	cout << *(iter0++) << endl;
	cout << *(iter0++) << endl;
	cout << *(iter0++) << endl;
	cout << *(iter0++) << endl;
	return 0;
}
