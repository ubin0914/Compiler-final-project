// %language "c++"

%defines "parser.h"

%{
	#pragma warning (disable: 4005)

	#include <bits/stdc++.h>
	#include "Constant.h"
	#include "Variable.h"

	using namespace std;

	// extern int yylex(yy::parser::semantic_type *yylval);
	extern int yylex(); 
	extern void yyerror(const char*);
%}

// % define api.value.type variant

%union {
	int	integerVal;
	double doubleVal;
	bool boolVal;
	char* stringVal;

	struct Constant *constant;
	struct Variable *variable;
}

%token T_INTEGER T_DOUBLE T_BOOL
%token LT LE GT GE EQ NE
%token FUNC_TYPE FUNC_ABS FUNC_POW FUNC_LOG FUNC_SIGMA

%token <integerVal> INTEGER_VAL 
%token <doubleVal> DOUBLE_VAL
%token <boolVal> BOOL_VAL

%token <variable> IDENTIFIER

%nterm <constant> stmt
%nterm <constant> assign_stmt
%nterm <constant> func_stmt
%nterm <constant> arr
%nterm <constant> expr
%nterm <constant> factor

%right '='
%left LT LE GT GE EQ NE 
%left '-' '+'
%left '*' '/'

%start program

%%

program:
	program stmt '\n'				{ printf(">> "); }
	|
	;

stmt:
	assign_stmt						{ $$ = $1; cout << $$ << "\n"; }
	| func_stmt						{ }
	|								{ /* Do Nothing */ }
	;

func_stmt:
	FUNC_TYPE '(' IDENTIFIER ')'	{ cout << "<type '" << $3->constant->type << "'>\n"; }
	/*
	| FUNC_ABS '(' expr ')'			{ cout << absConstant($3) << "\n"; }
	*/
	;

assign_stmt:
	IDENTIFIER '=' assign_stmt			{ $1->constant = $3; $$ = $1->constant; }
	| expr								{ $$ = $1; }
	//| IDENTIFIER '=' '{' arr '}'		{ $$ = $1->constant; }
	;

	/*
arr:
    expr ',' arr						{ $1->size += $3->size }
    | expr
	;
	*/

expr:
	IDENTIFIER							{ $$ = $1->constant; /*printf("expr: [%s]\n", $1->name);*/ }
	| factor							{ $$ = $1; }
	| FUNC_POW '(' expr ',' expr ')'	{ $$ = powConstant($3, $5); }
	| FUNC_LOG '(' expr ')'				{ $$ = logConstant($3); }	//好像不會左因子欸
	| FUNC_LOG '(' expr ',' expr ')'	{ $$ = logConstant($3, $5); }
	| FUNC_SIGMA '(' IDENTIFIER '=' expr ',' expr ')' '{' expr '}'		{
		double sum = 0;
		int from = $5->value.integerVal, to = $7->value.integerVal;
		for($3->constant = createConstantFromInteger(from); $3->constant->value.integerVal <= to; $3->constant->value.integerVal += 1)
			sum += $3->constant->value.integerVal;
		$$ = createConstantFromInteger(sum);
		cout << $$ << "!\n";
	}
	| expr '+' expr						{ $$ = addConstant($1, $3); }
	| expr '-' expr						{ $$ = subConstant($1, $3); }
	| expr '*' expr						{ $$ = mulConstant($1, $3); }
	| expr '/' expr						{ $$ = divConstant($1, $3); }
	| '(' expr ')'						{ $$ = $2; }
	| expr LT expr						{ $$ = lessthanConstant($1, $3); }
	| expr LE expr						{ $$ = lessequalConstant($1, $3); }
	| expr GT expr						{ $$ = greaterthanConstant($1, $3); }
	| expr GE expr						{ $$ = greaterequalConstant($1, $3); }
	| expr EQ expr						{ $$ = equalConstant($1, $3); }
	| expr NE expr						{ $$ = notequalConstant($1, $3); }
	;

factor:
	INTEGER_VAL						{ $$ = createConstantFromInteger($1); }
	| DOUBLE_VAL					{ $$ = createConstantFromDouble($1); }
	| BOOL_VAL						{ $$ = createConstantFromBool($1);}
	;

%%