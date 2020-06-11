#include <iostream>
#include <deque>
#include "MyDeque.h"

using namespace std;

int main()
{
	MyDeque<int> d;
	d._deque.push_back(23);
	d._deque.push_back(12);
	d._deque.push_back(42);
	d._deque.push_back(-67);

	d.Print();

	d.Sort();
	d.Print();

	cout << d.FindIf([](int num) -> bool {
		return num > 20;
		});

	cout << endl;

	d.RemoveIf([](int num) -> bool {
		return num > 20;
		});

	d.Print();
}
