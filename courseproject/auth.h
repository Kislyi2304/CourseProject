#ifndef AUTH_H
#define AUTH_H

#include <vector>
#include "models.h"

unsigned long get_hash(string str);
int authorize(const vector<User>& users);

#endif

