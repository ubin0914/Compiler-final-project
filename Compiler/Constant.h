#ifndef CONSTANT_H
#define CONSTANT_H

#include <iostream>
#include <vector>

using namespace std;

struct Constant {

	enum Type { UNDEFINED, IS_INTEGER, IS_DOUBLE, IS_BOOL, IS_VECTOR } type;
	union {
		int integerVal;
		double doubleVal;
		bool boolVal;
	} value;
	int size;

};

Constant* createConstantFromInteger(int val);
Constant* createConstantFromDouble(double val);
Constant* createConstantFromBool(bool val);
Constant* createConstantFromDoubleVec(double* vec, int size);

ostream& operator<<(ostream& s, Constant* constant);
ostream& operator<<(ostream& s, Constant::Type type);

Constant* calcConstant(Constant* l, Constant* r, double (*calc)(double, double));
Constant* addConstant(Constant* l, Constant *r);
Constant* subConstant(Constant* l, Constant* r);
Constant* mulConstant(Constant* l, Constant* r);
Constant* divConstant(Constant* l, Constant* r);
Constant* powConstant(Constant* a, Constant* b);
Constant* logConstant(Constant*);
Constant* logConstant(Constant* a, Constant* b);

Constant* compareConstant(Constant* l, Constant* r, bool (*compare)(double, double));
Constant* lessthanConstant(Constant* l, Constant *r);
Constant* lessequalConstant(Constant* l, Constant *r);
Constant* greaterthanConstant(Constant* l, Constant *r);
Constant* greaterequalConstant(Constant* l, Constant *r);
Constant* equalConstant(Constant* l, Constant *r);
Constant* notequalConstant(Constant* l, Constant *r);

Constant* absConstant(Constant* constant);

#endif