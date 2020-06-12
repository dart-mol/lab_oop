#include <iostream>
#define _CRT_SECURE_NO_WARNINGS // для корректной работы scanf()
#include <stdio.h>
using namespace std;
class Exeptoin
{

};
struct list
{
	int field; // поле данных
	struct list* ptr; // указатель на следующий элемент
};

struct list* init(int a) // а- значение первого узла
{
	struct list* lst;
	try
	{
		lst = (struct list*)malloc(sizeof(struct list));
		if (lst == NULL || lst == nullptr)
			throw Exeptoin();
		lst->field = a;
		lst->ptr = NULL; // это последний узел списка
		return(lst);
	}
	catch (Exeptoin)
	{
		cout << "Невозможнго выделить память" << endl;
	}

	// выделение памяти под корень списка

}
struct list* addelem(list* lst, int number)
{
	struct list* temp, * p;
	temp = (struct list*)malloc(sizeof(list));
	p = lst->ptr; // сохранение указателя на следующий узел
	lst->ptr = temp; // предыдущий узел указывает на создаваемый
	temp->field = number; // сохранение поля данных добавляемого узла
	temp->ptr = p; // созданный узел указывает на следующий элемент
	return(temp);
}
struct list* deletelem(list* lst, list* root)
{
	struct list* temp;
	temp = root;
	while (temp->ptr != lst) // просматриваем список начиная с корня
	{ // пока не найдем узел, предшествующий lst
		temp = temp->ptr;
	}
	temp->ptr = lst->ptr; // переставляем указатель
	free(lst); // освобождаем память удаляемого узла
	return(temp);
}
void listprint(list* lst)
{
	struct list* p;
	try
	{
		p = lst;
		do {
			printf("%d ", p->field); // вывод значения элемента p
			p = p->ptr; // переход к следующему узлу
		} while (p != NULL);
		if (p = NULL)
			throw Exeptoin();
	}
	catch (Exeptoin)
	{
		cout << "Попытка просмотра пустого множества" << endl;
	}


}

void shellSort(list* lst)
{
	int count = 0;

	struct list* p;
	p = lst;
	do {
		count++;
		p = p->ptr;
	} while (p != NULL);
	int* mas = new int[count];
	count = 0;
	p = lst;
	do {
		mas[count++] = p->field;
		p = p->ptr;
	} while (p != NULL);

	int increment = 3; // начальное приращение сортировки
	while (increment > 0) // пока существует приращение
	{
		for (int i = 0; i < count; i++) // для всех элементов массива
		{
			int j = i; // сохраняем индекс и элемент
			int temp = mas[i];
			// просматриваем остальные элементы массива, отстоящие от j-ого
			// на величину приращения
			while ((j >= increment) && (mas[j - increment] > temp))
			{ // пока отстоящий элемент больше текущего
				mas[j] = mas[j - increment]; // перемещаем его на текущую позицию
				j = j - increment; // переходим к следующему отстоящему элементу
			}
			mas[j] = temp; // на выявленное место помещаем сохранённый элемент
		}
		if (increment > 1) // делим приращение на 2
			increment = increment / 2;
		else if (increment == 1)
		{
			p = lst;
			count = 0;
			do {
				p->field = mas[count++];
				p = p->ptr;
			} while (p != NULL);
			delete[] mas;
			break;
		} // последний проход завершён,
		// выходим из цикла
	}
}


int main()
{
	setlocale(LC_ALL, "ru");
	list* a = NULL;
	int n, item;

	while (true)
	{
		try
		{
			cin >> n;
			if (cin.fail())
				throw Exeptoin();
			else break;
		}

		catch (Exeptoin)
		{
			cout << "Неверный тип данных" << endl;
			std::cin.clear();
			cin.ignore(32767, '\n');


		}
	};



	for (int i = 0; i < n; i++)
	{
		try
		{
			cin >> item;
			if (a == NULL)
				a = init(item);
			else addelem(a, item);
			if (!cin)
				throw Exeptoin();
		}
		catch (Exeptoin)
		{
			cout << "Неверный тип данных" << endl;
		}

	}
	listprint(a);
	cout << endl;
	shellSort(a);
	listprint(a);

}
