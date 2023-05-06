#include "Constant.h"

using namespace std;

Constant* createConstantFromInteger(int val) {
	Constant *constant = new Constant;
	constant->type = Constant::IS_INTEGER;
	constant->value.integerVal = val;
	return constant;
}

Constant* createConstantFromDouble(double val) {
	Constant *constant = new Constant;
	constant->type = Constant::IS_DOUBLE;
	constant->value.doubleVal = val;
	return constant;
}

Constant* createConstantFromBool(bool val) {
	Constant *constant = new Constant;
	constant->type = Constant::IS_BOOL;
	constant->value.boolVal = val;
	return constant;
}

Constant* createConstantFromArray(double* vec) {
	Constant* constant = new Constant;
	constant->size = 1;
	return constant;
}

ostream& operator<<(ostream& s, Constant* constant) {
	switch (constant->type) {
		case Constant::UNDEFINED:
			s << "(null)";
			break;
		case Constant::IS_INTEGER:
			s << constant->value.integerVal;
			break;
		case Constant::IS_DOUBLE:
			s << constant->value.doubleVal;
			break;
		case Constant::IS_BOOL:
			s << (constant->value.boolVal ? "true" : "false");
			break;
	}
	return s; 
}

ostream& operator<<(ostream& s, Constant::Type type) {
	switch (type) {
		case Constant::UNDEFINED:
			s << "undefined";
			break;
		case Constant::IS_INTEGER:
			s << "integer";
			break;
		case Constant::IS_DOUBLE:
			s << "double";
			break;
		case Constant::IS_BOOL:
			s << "bool";
			break;
	}
	return s; 
}

double doubleVal(Constant* c) {
	if (c->type == Constant::IS_INTEGER) return(double(c->value.integerVal));
	else if (c->type == Constant::IS_DOUBLE) return(c->value.doubleVal);
	return 0;
}

Constant* calcConstant(Constant* l, Constant* r, double (*calc)(double, double)) {
	Constant *constant = new Constant;

	if (l->type == Constant::UNDEFINED || r->type == Constant::UNDEFINED ||
		l->type == Constant::IS_BOOL || r->type == Constant::IS_BOOL)
		constant->type = Constant::UNDEFINED;
	else if (l->type == Constant::IS_INTEGER && r->type == Constant::IS_INTEGER) {
		constant->type = Constant::IS_INTEGER;
		constant->value.integerVal = calc(l->value.integerVal, r->value.integerVal);
	}
	else {
		constant->type = Constant::IS_DOUBLE;

		if (l->type == Constant::IS_INTEGER)
			constant->value.doubleVal = calc(l->value.integerVal, r->value.doubleVal);
		else if (r->type == Constant::IS_INTEGER)
			constant->value.doubleVal = calc(l->value.doubleVal, r->value.integerVal);
		else
			constant->value.doubleVal = calc(l->value.doubleVal, r->value.doubleVal);
	}

	return constant;
}

Constant* calcConstant_f(Constant* l, double (*calc)(double)) {
	Constant* constant = new Constant;

	if (l->type == Constant::UNDEFINED || l->type == Constant::IS_BOOL)
		constant->type = Constant::UNDEFINED;
	else {
		constant->type = Constant::IS_DOUBLE;
		constant->value.doubleVal = calc(doubleVal(l));
	}

	return constant;
}

Constant* calcConstant_f(Constant* l, Constant* r, double (*calc)(double, double)) {
	Constant* constant = new Constant;

	if (l->type == Constant::UNDEFINED || r->type == Constant::UNDEFINED ||
		l->type == Constant::IS_BOOL || r->type == Constant::IS_BOOL)
		constant->type = Constant::UNDEFINED;
	else {
		constant->type = Constant::IS_DOUBLE;
		constant->value.doubleVal = calc(doubleVal(l), doubleVal(r));
	}

	return constant;
}

Constant* addConstant(Constant* l, Constant* r) {
	auto calc = [] (double l, double r) { return l + r; };
	return calcConstant(l, r, calc);
}

Constant* subConstant(Constant* l, Constant* r) {
	auto calc = [] (double l, double r) { return l - r; };
	return calcConstant(l, r, calc);
}

Constant* mulConstant(Constant* l, Constant* r) {
	auto calc = [] (double l, double r) { return l * r; };
	return calcConstant(l, r, calc);
}

Constant* divConstant(Constant* l, Constant* r) {
	auto calc = [] (double l, double r) { return l / r; };
	return calcConstant(l, r, calc);
}

Constant* powConstant(Constant* a, Constant* b) {
	auto calc = [] (double a, double b) { return pow(a, b); };
	return calcConstant(a, b, calc);
}

Constant* logConstant(Constant* a) {
	auto calc = [] (double a) { return log(a); };
	return calcConstant_f(a, calc);
}

Constant* logConstant(Constant* a, Constant* b) {
	auto calc = [] (double a, double b) { return log(a) / log(b); };
	return calcConstant_f(a, b, calc);
}

Constant* compareConstant(Constant* l, Constant* r, bool (*compare)(double, double)) {
	Constant *constant = new Constant;

	if (l->type == Constant::UNDEFINED || r->type == Constant::UNDEFINED ||
		l->type == Constant::IS_BOOL || r->type == Constant::IS_BOOL)
		constant->type = Constant::UNDEFINED;
	else {
		constant->type = Constant::IS_BOOL;

		double lval = (l->type == Constant::IS_INTEGER ? l->value.integerVal : l->value.doubleVal);
		double rval = (r->type == Constant::IS_INTEGER ? r->value.integerVal : r->value.doubleVal);

		constant->value.boolVal = compare(lval, rval);
	}

	return constant;
}

Constant* lessthanConstant(Constant* l, Constant *r) {
	auto compare = [] (double l, double r) { return l < r; };
	return compareConstant(l, r, compare);
}

Constant* lessequalConstant(Constant* l, Constant *r) {
	auto compare = [] (double l, double r) { return l <= r; };
	return compareConstant(l, r, compare);
}

Constant* greaterthanConstant(Constant* l, Constant *r) {
	auto compare = [] (double l, double r) { return l > r; };
	return compareConstant(l, r, compare);
}

Constant* greaterequalConstant(Constant* l, Constant *r) {
	auto compare = [] (double l, double r) { return l >= r; };
	return compareConstant(l, r, compare);
}

Constant* equalConstant(Constant* l, Constant *r) {
	Constant *constant = new Constant;

	if (l->type == Constant::UNDEFINED || r->type == Constant::UNDEFINED ||
		l->type == Constant::IS_BOOL && r->type != Constant::IS_BOOL ||
		l->type != Constant::IS_BOOL && r->type == Constant::IS_BOOL)
		constant->type = Constant::UNDEFINED;
	else {
		constant->type = Constant::IS_BOOL;

		if (l->type == Constant::IS_BOOL && r->type == Constant::IS_BOOL)
			constant->value.boolVal = l->value.boolVal == r->value.boolVal;
		else {
			if (l->type == Constant::IS_INTEGER && r->type == Constant::IS_INTEGER)
				constant->value.boolVal = l->value.integerVal == r->value.integerVal;
			else {
				if (l->type == Constant::IS_INTEGER)
					constant->value.boolVal = l->value.integerVal == r->value.doubleVal;
				else if (r->type == Constant::IS_INTEGER)
					constant->value.boolVal = l->value.doubleVal == r->value.integerVal;
				else
					constant->value.boolVal = l->value.doubleVal == r->value.doubleVal;
			}
		}
	}

	return constant;
}

Constant* notequalConstant(Constant* l, Constant *r) {
	Constant *constant = new Constant;

	if (l->type == Constant::UNDEFINED || r->type == Constant::UNDEFINED ||
		l->type == Constant::IS_BOOL && r->type != Constant::IS_BOOL ||
		l->type != Constant::IS_BOOL && r->type == Constant::IS_BOOL)
		constant->type = Constant::UNDEFINED;
	else {
		constant->type = Constant::IS_BOOL;

		if (l->type == Constant::IS_BOOL && r->type == Constant::IS_BOOL)
			constant->value.boolVal = l->value.boolVal != r->value.boolVal;
		else {
			if (l->type == Constant::IS_INTEGER && r->type == Constant::IS_INTEGER)
				constant->value.boolVal = l->value.integerVal != r->value.integerVal;
			else {
				if (l->type == Constant::IS_INTEGER)
					constant->value.boolVal = l->value.integerVal != r->value.doubleVal;
				else if (r->type == Constant::IS_INTEGER)
					constant->value.boolVal = l->value.doubleVal != r->value.integerVal;
				else
					constant->value.boolVal = l->value.doubleVal != r->value.doubleVal;
			}
		}
	}

	return constant;
}

Constant* absConstant(Constant* c) {
	Constant *constant = new Constant;

	if (c->type == Constant::UNDEFINED || c->type == Constant::IS_BOOL)
		constant->type = Constant::UNDEFINED;
	else {
		constant->type = c->type;

		if (c->type == Constant::IS_INTEGER)
			constant->value.integerVal = (c->value.integerVal > 0 ? c->value.integerVal : -c->value.integerVal);
		else if (c->type == Constant::IS_DOUBLE)
			constant->value.doubleVal = (c->value.doubleVal > 0 ? c->value.doubleVal : -c->value.doubleVal);
	}

	return constant;
}