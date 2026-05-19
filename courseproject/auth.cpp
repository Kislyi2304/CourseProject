#include <string>
#include <vector>
#include <iostream>
#include "auth.h"
using namespace std;
//функция хэширования
unsigned long get_hash(string str) {

    unsigned long hash = 5381;

    for (char c : str) {
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}
//функция авторизации пользователей
int authorize(const vector<User>& users) {
    
    string login;
    string pass;
    
    cout << "\n--- АВТОРИЗАЦИЯ ---\n";
    
    cout << "Логин: ";
    cin >> login;
    
    cout << "Пароль: ";
    cin >> pass;
    
    unsigned long inputHash =
    get_hash(pass);
    
    for (const auto& user : users) {
        
        if (user.login == login &&
            user.passwordHash == inputHash) {
            
            cout << "Вход выполнен.\n";
            
            return user.role;
        }
    }
    
    cout << "Неверные данные.\n";
    
    return 0;
}
