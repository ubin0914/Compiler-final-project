%option noyywrap

%{ 
	#pragma warning (disable: 4005)

	#include <bits/stdc++.h>

	#include "parser.h"

	#include "Variable.h"

	using namespace std;
%}

%%

	/* Built-In Function */
"type"					{ return FUNC_TYPE; }
"abs"					{ return FUNC_ABS; }
"pow"					{ return FUNC_POW; }
"log"					{ return FUNC_LOG; }
"sig"					{ return FUNC_SIGMA; }

	/* Type */ /* Unused */
int						{ return T_INTEGER; }
double					{ return T_DOUBLE; }
bool					{ return T_BOOL; }

	/* Constant */
[+-]?[0-9]+				{ yylval.integerVal = atoi(yytext); return INTEGER_VAL; }
[+-]?[0-9]*\.[0-9]+		{ yylval.doubleVal = atof(yytext); return DOUBLE_VAL; }
"true"|"false"			{ yylval.boolVal = (yytext[0] == 't'); return BOOL_VAL; }

	/* Variable */
[a-zA-Z_][a-zA-Z_0-9]*  {
	//if (yytext[0] == 't' && yytext[1] == 'o') return '~';	else {}
	yylval.variable = createVariable(yytext); return IDENTIFIER;
}

	/* Operator */
[=+*/()\[\]\{\}-]		{ return yytext[0]; }
"<"						{ return LT; }
"<="					{ return LE; }
">"						{ return GT; }
">="					{ return GE; }
"=="					{ return EQ; }
"!="					{ return NE; }

	/* Delimiter */
[;]						{ return ';'; }
[\n]					{ return '\n'; }
[ \t]					{ /* Ignore */ }
[,]						{ return ','; }

	/* End Of File */
<<EOF>>					{ cout << "End Of File.\n"; yyterminate(); }
.						{ cout << "Invaild character: " << *yytext << " \n"; }

