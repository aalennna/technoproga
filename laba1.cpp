#include<iostream>
using namespace std;

class Building{
public:
	int year;
	string type;
	double height;
	Building* next;

	Building(int y, string t, double h) {
		year = y;
		type = t;
		height = h;
		next = nullptr;
	}
	static void AddF(Building* &object, int year, string type, double height) {
		Building* newbuild = new Building(year, type, height);
		newbuild->next = object;//(newbuild->next=(*nesbuild).next))
		object = newbuild;

	}
	static void AddL(Building*& object, int year, string type, double height) {
		Building* newbuild=new Building(year, type, height);
		if (object == nullptr) {
			object = newbuild;
		}
		else {
			Building* tmp = object;
			while (tmp->next != nullptr)
				tmp = tmp->next;
			tmp->next = newbuild;
		}
	}
	static void AddA(Building* object,string existingType, int year, string type, double height) {
		if (object == nullptr) {
			cout << "Пусто" << endl;
			return;
		}
		Building* tmp = object;
		while (tmp != nullptr && tmp->type!=existingType) {
			tmp = tmp->next;
		}
		if (tmp == nullptr) {
			cout << "Нет такого объекта!" << endl;
			return;
		}
		Building* newbuild = new Building(year, type, height);
		newbuild->next = tmp->next;
		tmp->next = newbuild;
	}
	static void AddB(Building* &object, string existingType, int year, string type, double height) {
		if (object == nullptr) {
			cout << "Пусто!" << endl;
			return;
		}
		if (object->type == existingType) {
			AddF(object, year, type, height);
			return;
		}
		Building* prev = object, * tmp = object->next;
		while (tmp->next != nullptr and tmp->type != existingType) {
			tmp = tmp->next;
			prev = prev->next;
		}
		if (tmp->next == nullptr and tmp->type != existingType) {
			cout << "Нет такого объекта"<<endl;
			return;
		}
		Building* newbuild = new Building(year, type, height);
		newbuild->type = type;
		newbuild->year = year;
		newbuild->height = height;
		newbuild->next = tmp;
		prev->next = newbuild;


	}
	static void Delete(Building*& object, string type) {
		if (object == nullptr) {
			cout << "Пусто!" << endl;
			return;
		}
		if (object->type == type) {
			Building* tmp = object;
			object = object->next;
			delete tmp;
			return;
		}
		Building* prev = object;
		Building* tmp = object;
		while (tmp != nullptr && tmp->type != type) {
			prev = tmp;
			tmp = tmp->next;
		}
		if (tmp == nullptr) {
			cout << "Нет такого объекта" << endl;
			return;
		}
		prev->next = tmp->next;
		delete tmp;
	}
	static void List(Building* object) {
		if (object == nullptr) {
			cout << "Пусто";
			return;
		}
		Building* tmp = object;
		while (tmp != nullptr) {
			cout << "Год: " << tmp->year << "\nТип здания: " << tmp->type << "\nВысота здания: " << tmp->height << endl<<endl;
			tmp = tmp->next;
		}

	}
};

int main() {
	setlocale(LC_ALL, "RU");
	Building* list1 = nullptr;
	Building::AddF(list1, 1996, "Школа", 40.3);
	Building::List(list1);
	

	Building::AddF(list1, 2005, "Больница", 30.86);
	Building::List(list1);
	

	Building::AddA(list1, "Больница", 2023, "Торговый центр", 23.15);
	Building::List(list1);
	

	Building::AddB(list1, "Больница", 1987, "Университет", 240.15);
	Building::List(list1);
	

	Building::Delete(list1, "Школа");
	Building::List(list1);
	

	Building::AddL(list1, 2007, "Кинотеатр", 29.7);
	Building::List(list1);

	return 0;
}