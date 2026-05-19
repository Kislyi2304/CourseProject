#include "children.h"
#include "database.h"

#include <iostream>
#include <iomanip>

using namespace std;
//функция вывода данных о воспитанниках
void showChildren(const vector<Child>& db) {

    if (db.empty()) {
        cout << "База пуста.\n";
        return;
    }

    cout << "\nНОМЕР | ИМЯ | ФАМИЛИЯ | ГРУППА | ДАТА\n";
    cout << "--------------------------------------------------\n";

    for (const auto& s : db) {
        string date =
            (s.birthDate.day < 10 ? "0" : "") +
            to_string(s.birthDate.day) + "." +
            (s.birthDate.month < 10 ? "0" : "") +
            to_string(s.birthDate.month) + "." +
            to_string(s.birthDate.year);

        cout << s.number << " | "
             << s.firstName << " | "
             << s.lastName << " | "
             << s.groupName << " | "
             << date << endl;
    }
}
//функция добавления данных о новом ребенке
void addChild(vector<Child>& db) {

    Child s;

    cout << "\n--- Добавление ребенка ---\n";

    cout << "Номер: ";
    cin >> s.number;

    cout << "Имя: ";
    cin >> s.firstName;

    cout << "Фамилия: ";
    cin >> s.lastName;

    cout << "Группа: ";
    cin >> s.groupName;

    cout << "Дата рождения (день месяц год): ";

    cin >> s.birthDate.day
        >> s.birthDate.month
        >> s.birthDate.year;

    string sql =
        "INSERT INTO children "
        "(number, firstName, lastName, groupName, day, month, year) VALUES (" +

        to_string(s.number) + ", '" +
        s.firstName + "', '" +
        s.lastName + "', '" +
        s.groupName + "', " +

        to_string(s.birthDate.day) + ", " +
        to_string(s.birthDate.month) + ", " +
        to_string(s.birthDate.year) + ");";

    char* errMsg = 0;
    int rc = sqlite3_exec(DB,
                          sql.c_str(),
                          0,
                          0,
                          &errMsg);

    if (rc != SQLITE_OK) {
        cout << "Ошибка SQL: "
             << errMsg << endl;

        sqlite3_free(errMsg);
    }
    else {
        db.push_back(s);

        cout << "Данные о ребенке успешно добавлены.\n";
    }
}
//функция поиска данных о ребенке
void searchChild(const vector<Child>& db) {

    if (db.empty()) {

        cout << "База пуста.\n";
        return;
    }

    int number;

    cout << "Введите номер: ";
    cin >> number;

    for (const auto& s : db) {

        if (s.number == number) {
            cout << "\nНайден:\n";
            cout << s.firstName
                 << " "
                 << s.lastName
                 << endl;

            return;
        }
    }

    cout << "Данные о ребенке не найдены.\n";
}
//функция удаления данных о ребенке
void deleteChild(vector<Child>& db) {

    int number;

    cout << "Введите номер для удаления: ";
    cin >> number;

    string sql =
        "DELETE FROM children WHERE number = " +
        to_string(number) + ";";

    char* errMsg = 0;

    int rc = sqlite3_exec(DB,
                          sql.c_str(),
                          0,
                          0,
                          &errMsg);

    if (rc != SQLITE_OK) {

        cout << "Ошибка SQL: "
             << errMsg << endl;

        sqlite3_free(errMsg);
    }
    else {

        for (size_t i = 0; i < db.size(); ++i) {

            if (db[i].number == number) {

                db.erase(db.begin() + i);
                break;
            }
        }

        cout << "Данные о ребенке удалены.\n";
    }
}
//функция редактирования данных о ребенке
void editChild(vector<Child>& db) {

    int number;

    cout << "Введите номер для редактирования: ";
    cin >> number;

    for (auto& s : db) {

        if (s.number == number) {

            cout << "Новое имя: ";
            cin >> s.firstName;

            cout << "Новая фамилия: ";
            cin >> s.lastName;

            cout << "Новая группа: ";
            cin >> s.groupName;

            cout << "Новая дата рождения: ";

            cin >> s.birthDate.day
                >> s.birthDate.month
                >> s.birthDate.year;

            string sql =
                "UPDATE children SET "
                "firstName = '" + s.firstName +
                "', lastName = '" + s.lastName +
                "', groupName = '" + s.groupName +
                "', day = " + to_string(s.birthDate.day) +
                ", month = " + to_string(s.birthDate.month) +
                ", year = " + to_string(s.birthDate.year) +
                " WHERE number = " + to_string(number) + ";";

            char* errMsg = 0;

            int rc = sqlite3_exec(DB,
                                  sql.c_str(),
                                  0,
                                  0,
                                  &errMsg);

            if (rc != SQLITE_OK) {

                cout << "Ошибка SQL: "
                     << errMsg << endl;

                sqlite3_free(errMsg);
            }
            else {

                cout << "Данные обновлены.\n";
            }

            return;
        }
    }

    cout << "Данные о ребенке не найдены.\n";
}
//сортировка по фамилии с помощью метода пузырьковой сортировки
void sortLastNameBubble(vector<Child>& db) {

    for (size_t i = 0; i < db.size() - 1; ++i) {

        for (size_t j = 0;
             j < db.size() - i - 1;
             ++j) {

            if (db[j].lastName >
                db[j + 1].lastName) {

                swap(db[j], db[j + 1]);
            }
        }
    }

    cout << "Сортировка выполнена.\n";
}
//функция сортировки по дате рождения методом вставки
void sortBirthSelection(vector<Child>& db) {

    size_t n = db.size();

    for (size_t i = 0; i < n - 1; ++i) {

        size_t minIndex = i;

        for (size_t j = i + 1; j < n; ++j) {

            bool earlier = false;

            if (db[j].birthDate.year <
                db[minIndex].birthDate.year)

                earlier = true;

            else if (db[j].birthDate.year ==
                     db[minIndex].birthDate.year) {

                if (db[j].birthDate.month <
                    db[minIndex].birthDate.month)

                    earlier = true;

                else if (db[j].birthDate.month ==
                         db[minIndex].birthDate.month) {

                    if (db[j].birthDate.day <
                        db[minIndex].birthDate.day)

                        earlier = true;
                }
            }

            if (earlier)
                minIndex = j;
        }

        if (minIndex != i) {

            swap(db[i], db[minIndex]);
        }
    }

    cout << "Сортировка выполнена.\n";
}
int partitionGroups(vector<Child>& db, int low, int high) {

    string pivot = db[high].groupName;

    int i = low - 1;

    for (int j = low; j < high; ++j) {

        if (db[j].groupName < pivot) {

            i++;

            swap(db[i], db[j]);
        }
    }

    swap(db[i + 1], db[high]);

    return i + 1;
}
//функция quicksort по группам
void quickSortGroups(vector<Child>& db, int low, int high) {
    if (low < high) {

        int pi = partitionGroups(db, low, high);

        quickSortGroups(db, low, pi - 1);

        quickSortGroups(db, pi + 1, high);
    }
}

void sortGroupsQuick(vector<Child>& db) {

    if (db.empty()) {

        cout << "База пуста.\n";
        return;
    }

    quickSortGroups(db, 0, db.size() - 1);

    cout << "Сортировка выполнена.\n";
}
//общая функция сортировки с выбором конкретной сортировки
void sortChild(vector<Child>& db) {

    int choice;

    cout << "\n1. По фамилии\n";
    cout << "2. По дате рождения\n";
    cout << "3. По номеру группы\n";
    cout << "Выберите: ";
    cin >> choice;
    switch (choice) {

        case 1:
            sortLastNameBubble(db);
            break;

        case 2:
            sortBirthSelection(db);
            break;

        case 3:
            sortGroupsQuick(db);
                break;
        default:
            cout << "Ошибка выбора.\n";
    }
}

