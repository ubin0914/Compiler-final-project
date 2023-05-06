#include "Variable.h"

#include <map>

using namespace std;

/*
struct cmp_str {
	bool operator() (char const *l, char const *r) const {
		if (l == r)
			return false;
		else
			return strcmp(l, r) < 0;
		//return strcmp(l, r) < 0;
	}
};

static map<char*, Variable*, cmp_str> symtab;
*/

static map<string, Variable*> symtab;

Variable* createVariable(char* name) {
	Variable *variable;
	string s(name);

	if (symtab.find(s) != symtab.end()) // Existed
		variable = symtab[s];
	else {
		variable = new Variable;
		variable->name = name;
		variable->constant = new Constant();
		symtab[s] = variable;
	}

	return variable;
}