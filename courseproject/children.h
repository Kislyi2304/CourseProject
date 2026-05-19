#ifndef CHILDREN_H
#define CHILDREN_H

#include <vector>
#include "models.h"

void showChildren(const vector<Child>& db);

void addChild(vector<Child>& db);

void searchChild(const vector<Child>& db);

void deleteChild(vector<Child>& db);

void editChild(vector<Child>& db);

void sortChild(vector<Child>& db);

#endif

