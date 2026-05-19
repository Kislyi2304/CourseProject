#ifndef DATABASE_H
#define DATABASE_H

#include <vector>
#include "models.h"
#include <sqlite3.h>

extern sqlite3* DB;

bool openDatabase();

void createTable();

void loadFromDatabase(vector<Child>& db);

#endif

