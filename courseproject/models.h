#ifndef MODELS_H
#define MODELS_H

#include <string>
using namespace std;
struct Date {
    int day;
    int month;
    int year;
};

struct Child {
    int number;
    string firstName;
    string lastName;
    string groupName;
    Date birthDate;
};
struct User {
    string login;
    unsigned long passwordHash;
    int role;
};

#endif

