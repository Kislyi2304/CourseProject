#include "menus.h"
#include "children.h"

#include <iostream>

using namespace std;
//панель родителя
void parentPanel(const vector<Child>& db) {

    int choice;

    do {

        cout << "\n--- ПАНЕЛЬ РОДИТЕЛЯ ---\n";

        cout << "1. Просмотр данных детей\n";
        cout << "2. Поиск данных о ребенке\n";
        cout << "0. Выход\n";
        cout << "Выберите: ";

        cin >> choice;

        if (choice == 1)
            showChildren(db);

        else if (choice == 2)
            searchChild(db);
        else if (choice != 1 || choice != 2)
            cout <<"\nВведите корректный выбор!\n";
    } while (choice != 0);
}
//панель воспитателя
void teacherPanel(vector<Child>& db) {

    int choice;

    do {

        cout << "\n--- ПАНЕЛЬ ВОСПИТАТЕЛЯ ---\n";

        cout << "1. Просмотр данных детей\n";
        cout << "2. Поиск данных о ребенке\n";
        cout << "3. Сортировка\n";
        cout << "4. Редактировать данные о ребенке\n";
        cout << "0. Выход\n";
        cout << "Выберите: ";

        cin >> choice;

        switch (choice) {

            case 1:
                showChildren(db);
                break;

            case 2:
                searchChild(db);
                break;

            case 3:
                sortChild(db);
                break;

            case 4:
                editChild(db);
                break;
                
            default:
                cout<<"\nВыберите корректный вариант!\n";
                break;
        }

    } while (choice != 0);
}
//панель заведующей
void adminPanel(vector<Child>& db) {

    int choice;

    do {

        cout << "\n--- ПАНЕЛЬ ЗАВЕДУЮЩЕЙ ---\n";

        cout << "1. Просмотр данных детей\n";
        cout << "2. Поиск данных о ребенке\n";
        cout << "3. Сортировка\n";
        cout << "4. Добавить данные о ребенке\n";
        cout << "5. Удалить данные о ребенке\n";
        cout << "6. Редактировать данные о ребенке\n";
        cout << "0. Выход\n";
        cout << "Выберите: ";

        cin >> choice;

        switch (choice) {
            case 1:
                showChildren(db);
                break;

            case 2:
                searchChild(db);
                break;

            case 3:
                sortChild(db);
                break;

            case 4:
                addChild(db);
                break;

            case 5:
                deleteChild(db);
                break;

            case 6:
                editChild(db);
                break;

            default:
                cout<<"\nВыберите корректный вариант!\n";
                break;
        }
    } while (choice != 0);
}

