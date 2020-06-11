#include <iostream>
#include <list>
#include <fstream>
#include <algorithm>
#include <string>

using namespace std;
/*
	Реализовать класс текстовых файлов, с помощью которого и
	осуществлять взаимодействие с текстовыми файлами. В данном классе
	реализовать операции чтения и записи. К
	тому же реализовать дополнительный функционал сортировки, который
	будет указан в задании по варианту.
	Любую работу с данными реализовывать через обработку
	исключительных ситуаций и реализовать, где возможно, перегрузку
	операторов.
*/

/*
	V9
	Реализовать класс “Продукция”. Поля класса:

	● наименование;
	● количество;
	● номер цеха.
	Для заданного цеха необходимо вывести количество
	выпущенных изделий по каждому наименованию в
	порядке убывания количества.
*/


class File {
public:

	template <typename T>
	static list<T> read() {
		list<T> li;
		try {

			ifstream stream("db.txt", ios::in);

			if (stream.is_open()) {
				T temp;
				while (stream >> temp) {
					// if(!temp.isEmpty())
					li.push_back(temp);
				}
			}
			else {
				cerr << "Error";
			}

			stream.close();

		}
		catch (...) {
			cerr << "Ошибка чтения из файла.\n";
		}

		return li;
	}

	template <typename T>
	static void write(T responser) {
		ofstream stream;

		try {
			stream.open("db.txt", ios::out);

			if (stream.is_open()) {

				for (auto item : responser.get())
					stream << item;

			}
			stream.close();

		}
		catch (...) {
			cerr << "Ошибка записи в файл.\n";
		}

	}

};

class Product {
private:
	char _name[255];
	int _count;
	char _number[12];
public:
	Product() {

	}

	void edit() {
		try {
			cout << "Заполнение продукта\n";
			cout << "Наименование:\n";
			cin >> _name;

			cout << "Количество:\n";
			cin >> _count;

			cout << "Номер цеха:\n";
			cin >> _number;
			cout << endl;
		}
		catch (...) {
			cerr << "Ошибка ввода.\n";
		}
	}


	void print() {
		cout << "Наименование: " << _name << "; Количество: " << _count << "; Номер цеха: " << _number;
	}

	char* number() {
		return _number;
	}

	int count() {
		return _count;
	}


	bool isEmpty() {
		return _count > 0;
	}

	friend ofstream& operator << (ofstream& os, const Product& p);
	friend ifstream& operator >> (ifstream& is, Product& p);

};

class Products {
	list<Product> products;
public:
	void add() {
		Product p;

		p.edit();

		products.push_back(p);
	}

	void add(Product p) {
		products.push_back(p);
	}


	void print() {

		if (products.empty())
			cout << "Пусто.\n";
		else {
			cout << "Список продукции:\n";
			for (auto i : products) {
				i.print();
				cout << endl;
			}
		}
	}

	void save() {
		File::write<Products>(*this);
		cout << "Сохранено.\n";
	}

	void load() {
		products = File::read<Product>();
		cout << "Загружено.\n";
	}


	void findByNumber(char number[12]) {
		try {
			list<Product> temp;
			for (auto item : products)
				if (string(item.number()) == string(number))
					temp.push_back(item);


			if (temp.empty()) {
				cout << "Ничего не найдено\n";
			}
			else {

				temp.sort([](Product& p1, Product& p2) {
					return p1.count() > p2.count();
					});

				cout << "Продукты по указаному цеху:\n";
				for (Product t : temp) {
					t.print();
					cout << endl;
				}


			}
		}
		catch (...) {
			cerr << "Ошибка поиска по номеру цеха.\n";
		}
	}

	void setFindByNumber() {
		char number[12];
		cout << "Введите номер цеха для поиска:\n";
		cin >> number;
		findByNumber(number);
	}


	list<Product>& get() {
		return products;
	}

};


ofstream& operator << (ofstream& os, const Product& p) {
	os << p._name << " " << p._count << " " << p._number << endl;
	return os;
}


ifstream& operator >> (ifstream& is, Product& p) {
	is >> p._name >> p._count >> p._number;
	return is;
}


int main() {
	setlocale(LC_ALL, "");

	Products prod;

	int key;

	do {
		try {
			cout << "1 - Добавить\n";
			cout << "2 - Просмотреть\n";
			cout << "3 - Найти по цеху\n";
			cout << "4 - Загрузить с файла\n";
			cout << "5 - Сохранить в файл\n";
			cout << "0 - Выход\n";
			cin >> key;

			switch (key) {
			case 1:
				prod.add();
				break;
			case 2:
				prod.print();
				break;
			case 3:
				prod.setFindByNumber();

				break;
			case 4:
				prod.load();

				break;
			case 5:
				prod.save();

				break;
			default:
				break;
			}
			cout << endl;
		}
		catch (...) {
			cerr << "Что-то сломалось...\n";
		}
	} while (key != 0);





	cin.get();
	return 0;
}