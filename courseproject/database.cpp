#include "database.h"
#include <iostream>

using namespace std;

sqlite3* DB;
//функция открытия базы данных
bool openDatabase() {

    int rc =
        sqlite3_open(
            "children.db",
            &DB
        );

    if (rc) {

        cout << "Ошибка БД\n";
        return false;
    }

    return true;
}
//функция создания таблицы в базе данных
void createTable() {

    const char* sql =
        "CREATE TABLE IF NOT EXISTS children ("
        "number INTEGER PRIMARY KEY,"
        "firstName TEXT,"
        "lastName TEXT,"
        "groupName TEXT,"
        "day INTEGER,"
        "month INTEGER,"
        "year INTEGER);";

    char* errMsg = 0;

    sqlite3_exec(DB,
                 sql,
                 0,
                 0,
                 &errMsg);
}

static int callback(void* data,
                    int argc,
                    char** argv,
                    char** azColName) {

    vector<Child>* db =
        static_cast<vector<Child>*>(data);

    Child s;

    s.number = stoi(argv[0]);
    s.firstName = argv[1];
    s.lastName = argv[2];
    s.groupName = argv[3];

    s.birthDate.day = stoi(argv[4]);
    s.birthDate.month = stoi(argv[5]);
    s.birthDate.year = stoi(argv[6]);

    db->push_back(s);

    return 0;
}
//функция загрузки данных из базы данных
void loadFromDatabase(vector<Child>& db) {

    db.clear();

    const char* sql =
        "SELECT * FROM children;";

    char* errMsg = 0;

    sqlite3_exec(DB,
                 sql,
                 callback,
                 &db,
                 &errMsg);
}

