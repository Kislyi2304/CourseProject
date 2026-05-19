#include <iostream>
#include <vector>
#include "models.h"
#include "database.h"
#include "menus.h"
#include "auth.h"
using namespace std;

int main() {
    setlocale(LC_ALL, "rus");
    
    if (!openDatabase()) {
        return 1;
    }
    
    createTable();
    
    vector<User> users = {
        {"admin", get_hash("123"), 1},
        {"teacher", get_hash("123"), 2}
    };
    
    vector<Child> database;
    loadFromDatabase(database);
    int mainChoice;
    
    do {
        
        cout << "\n=== ДЕТСКИЙ САД ===\n";
        
        cout << "1. Войти как сотрудник\n";
        cout << "2. Войти как родитель\n";
        cout << "0. Выход\n";
        cout << "Выберите: ";
        
        cin >> mainChoice;
        
        if (mainChoice == 1) {
            int role = authorize(users);
            
            if (role == 1)
                adminPanel(database);
            
            else if (role == 2)
                teacherPanel(database);
        }
        
        else if (mainChoice == 2) {
            parentPanel(database);
        }
    } while (mainChoice != 0);
    
    sqlite3_close(DB);
    
    return 0;
}
