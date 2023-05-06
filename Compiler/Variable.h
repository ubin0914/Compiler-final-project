#ifndef VARIABLE_H
#define VARIABLE_H

#include "Constant.h"

using namespace std;

struct Variable {

	char* name;

	struct Constant* constant;

};

Variable* createVariable(char* name);

#endif