#include <iostream>
#include <string>

using namespace std;

template <typename T>
class Vector
{
public:
	class Iterator;
	friend class Iterator;

	class Iterator
	{
		friend class Vector<T>;

	public:
		Iterator() : _index(-1) {};
		Iterator(Vector* v) {
			_vec = v;
			_index = -1;
		};
		Iterator(Vector* v, int index) {
			_vec = v;
			_index = index;
		};

		Iterator& operator++()
		{
			_index++;
			return *this;
		}

		Iterator & operator--()
		{
			_index--;
			return *this;
		}

		T& operator*() const
		{
			if (_index == -1)
				throw "tried to dereference an empty iterator";

			try {
				return _vec->_vector[_index].val;
			}
			catch (const std::exception& e) {
				throw "Index in iterator was incorrect";
			}

		}

	private:
		int _index;
		Vector* _vec;
	};

	class PrintIterator;
	friend class PrintIterator;

	class PrintIterator
	{
		friend class Vector<T>;
	public:
		PrintIterator() {};
		PrintIterator(Vector<T>* v, string delemiter) : _delemiter(delemiter), _v(v) {};

		PrintIterator& operator = (const Iterator &it)
		{
			_delemiter = it._delemiter;
			_v = it._v;
			return *this;
		}

		void Print()
		{
			for (int index = 0; index < _v->_size; index++)
			{
				cout << _v->_vector[index].val << _delemiter;
			}
		}

	private:
		string _delemiter;
		Vector* _v;
	};

private:
	class Node;
	friend class Node;

	class Node
	{
	public:
		friend class Vector<T>;
		friend class Iterator;
		friend class PrintIterator;

		Node(T node_val) : val(node_val) {}
		Node() {}
		~Node() {}

		T val;
	};

private:
	Node* _vector;
	int _size;
	Iterator tail_iterator;
	PrintIterator iterator;

public:
	Vector()
	{
		_size = 0;
		_vector = new Node[_size];
		tail_iterator = Iterator(this);
	}

	Vector(T node_val)
	{
		_size = 0;
		tail_iterator = Iterator(this);
		Add(node_val);
	}

	~Vector()
	{
	}

	Iterator rbegin() { return tail_iterator; }

	Node operator [](int index)
	{
		return _vector[index];
	}

	void Add(T node_val)
	{
		Node* _res = new Node[++_size];
		
		for (int index = 0; index < _size; index++)
		{
			if (index != _size - 1)
			{
				_res[index] = _vector[index];
			}
			else
			{
				_res[index] = Node(node_val);
				break;
			}
		}

		delete[] _vector;
		_vector = _res;
		++tail_iterator;
	}

	T Remove()
	{
		if (_size == 0)
			throw "tried to remove from an empty list";

		Node* _res = new Node[--_size];
		Node resItem;
		int resIndex = 0;

		for (int index = 0; index < _size + 1; index++)
		{
			Node item = _vector[index];

			if (index == _size)
			{
				resItem = item;
				continue;
			}
			_res[resIndex++] = _vector[index];
		}
		delete[] _vector;
		_vector = _res;
		--tail_iterator;
		return resItem.val;
	}

	int size()
	{
		return _size;
	}

	Node* getArray()
	{
		return _vector;
	}

	void Sort(Node* vec, int L, int R)
	{
			int i, j, mid;
			T piv;
			i = L;
			j = R;
			mid = L + (R - L) / 2;
			piv = vec[mid].val;

			while (i<R || j>L) {
				while (vec[i].val < piv)
					i++;
				while (vec[j].val > piv)
					j--;

				if (i <= j) {
					Node temp = vec[i];
					vec[i] = vec[j];
					vec[j] = temp;
					i++;
					j--;
				}
				else {
					if (i < R)
						Sort(vec, i, R);
					if (j > L)
						Sort(vec, L, j);
					return;
				}
			}
	};

	void Print()
	{
		iterator = PrintIterator(this, ", ");
		iterator.Print();
	}
};