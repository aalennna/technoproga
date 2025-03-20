#include <iostream>
using namespace std;

struct Building {
    string type;
    int year;
    double height;
    Building* next;
};

void AddF(Building*& head, string type, int year, double height) {
    Building* newBuild = new Building;
    newBuild->type = type;
    newBuild->year = year;
    newBuild->height = height;
    newBuild->next = head;
    head = newBuild;
}


void AddL(Building*& head, string type, int year, double height) {
    Building* newBuild = new Building;
    newBuild->type = type;
    newBuild->year = year;
    newBuild->height = height;
    newBuild->next = head;
    newBuild->next = nullptr;
    if (head == nullptr) {
        head = newBuild;
    }
    else {
        Building* tmp = head;
        while (tmp->next != nullptr)
            tmp = tmp->next;
        tmp->next = newBuild;
    }
}


void AddAfter(Building* head, string your, string type, int year, double height) {
    if (head == nullptr) {
        cout << "Пусто\n";
        return;
    }
    Building* tmp = head;
    while (tmp->next != nullptr and tmp->type != your)
        tmp = tmp->next;
    if (tmp->next == nullptr and tmp->type != your) {
        cout << "Нет такого элемента\n";
        return;
    }
    Building* newBuild = new Building;
    newBuild->type = type;
    newBuild->year = year;
    newBuild->height = height;
    newBuild->next = tmp->next;
    tmp->next = newBuild;
}


void AddBefore(Building* head, string your, string type, int year, double height) {
    if (head == nullptr) {
        cout << "Пусто!\n";
        return;
    }
    if (head->type == your) {
        AddF(head, type, year, height);
        return;
    }
    Building* prev = head, * tmp = head->next;
    while (tmp->next != nullptr and tmp->type != your) {
        tmp = tmp->next;
        prev = prev->next;
    }
    if (tmp->next == nullptr and tmp->type != your) {
        cout << "Нет такого элемента!\n";
        return;
    }
    Building* newBuild = new Building;
    newBuild->type = type;
    newBuild->year = year;
    newBuild->height = height;
    newBuild->next = tmp;
    prev->next = newBuild;
}


void Del(Building*& head, string your) {
    if (head == nullptr) {
        cout << "Пусто!\n";
        return;
    }
    Building* tmp = head;
    if (head->type == your) {
        head = head->next;
        delete tmp;
        return;
    }

    Building* prev = head;
    tmp = head->next;
    while (tmp->next != nullptr and tmp->type != your) {
        tmp = tmp->next;
        prev = prev->next;

    }
    if (tmp->next == nullptr and tmp->type != your) {
        cout << "Нет такого элемента\n";
        return;
    }
    if (tmp->type == your) {
        prev->next = tmp->next;
        delete tmp;
        return;
    }
}


void Print(Building* head) {
    if (head == nullptr) {
        cout << "Пусто!\n";
        return;
    }
    Building* tmp = head;
    while (tmp != nullptr) {
        cout << "Тип: " << tmp->type << "\nГод: " << tmp->year << "\nВысота: " << tmp->height << endl << endl;
        tmp = tmp->next;
    }
}


int main() {
    setlocale(LC_ALL, "RU");
    Building* list1 = nullptr;
    AddF(list1, "Школа", 1996, 23.5);
    Print(list1);

    AddF(list1, "Больница", 2007, 59.64);
    Print(list1);

    AddAfter(list1, "Школа", "Торговый центр", 2022, 100.38);
    Print(list1);

    AddBefore(list1, "Больница", "Кинотеатр", 2005, 56.49);
    Print(list1);

    Del(list1, "Больница");
    Print(list1);

    AddL(list1, "Университет", 1982, 151.26);
    Print(list1);
    delete list1;

    return 0;
}