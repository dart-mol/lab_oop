#include <iostream>
#include "Vector.h";
#include "windows.h";

int main()
{
	Vector<int> vector;
	
	vector.Add(1);
	vector.Add(5);
	vector.Add(-4);
	vector.Add(10);

	int last_value = *vector.rbegin();
	cout << last_value << "\n";

	vector.Remove();
	last_value = *vector.rbegin();
	cout << last_value << "\n";

	cout << *--vector.rbegin() << "\n";

	vector.Print();
	std::cout << "\n";

	vector.Sort(vector.getArray(), 0, vector.size() - 1);
	vector.Print();
	Sleep(10000);
}

