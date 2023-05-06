#include <bits/stdc++.h>

#include "parser.h"

using namespace std;

extern int yyparse();

int main() {
	cout << ">> ";
	yyparse();
	return 0;
}

void yyerror(const char* msg) {
	cout << "Error: " << msg << "\n";
}