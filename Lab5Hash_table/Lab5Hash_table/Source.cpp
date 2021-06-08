#include "HashTable.h"
#include <ctime>

using namespace std;

int main() {
	srand(time(NULL));

	HashTable<int, char> htable;

	for (int i = 0; i < 1000; i++) {
		htable.Insert(rand() % 1000, rand() % ('z'-'a') + 'a');
	}

	cout << htable << endl;
	cout << htable.Contains(0) << endl;
	cout << htable.Contains(13) << endl;
	cout << htable.Contains(26) << endl;
	cout << htable.Contains(4) << endl;

	htable.Show();

	htable.Erase(0);
	htable.Erase(40);
	htable.Erase(34);

	cout <<"[] "<< htable[41] << endl;
	cout << "[] " << htable[1] << endl;
	cout << "[] " << htable[1] << endl;
	cout << "[] " << htable[23] << endl;

	htable.Show();
	htable.Clear();

	htable.Show();

	HashTable<int, char> htable2 = htable;
	cout << htable2 << '\n';

	return 0;
}