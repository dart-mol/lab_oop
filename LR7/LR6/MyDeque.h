#include <deque>
#include <functional>
#include <algorithm>
#include "iostream"

using namespace std;

template <typename T>
class MyDeque
{
	void quicksort(deque<T> &deq, int L, int R) {
		int i, j, mid;
		i = L;
		j = R;
		mid = L + (R - L) / 2;
		T piv = deq[mid];

		while (i<R || j>L) {
			while (deq[i] < piv)
				i++;
			while (deq[j] > piv)
				j--;

			if (i <= j) {
				swap(deq, i, j);
				i++;
				j--;
			}
			else {
				if (i < R)
					quicksort(deq, i, R);
				if (j > L)
					quicksort(deq, L, j);
				return;
			}
		}
	}

	void swap(deque<T>& d, int x, int y) {
		T temp = d[x];
		d[x] = d[y];
		d[y] = temp;
	}
public:
	deque<T> _deque;
	MyDeque() {};
	void Sort()
	{
		quicksort(_deque, 0, _deque.size() - 1);
	};
	T FindIf(function<bool(int)> lambda)
	{
		typedef deque<T>::iterator iterator;
		iterator it = std::find_if(_deque.begin(), _deque.end(), lambda);
		return *it;
	};
	void RemoveIf(function<bool(int)> lambda)
	{
		_deque.erase(remove_if(_deque.begin(), _deque.end(), lambda), _deque.end());
	};
	void Print()
	{
		cout << "Content: " << endl;

		if (_deque.empty())
		{
			cout << "Empty" << endl;
		}
		else
		{
			for (auto it : this->_deque)
			{
				cout << it << " ";
			}

			cout << endl;
		}
	};
};
