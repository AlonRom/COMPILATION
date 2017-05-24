%{
/*************************/
/* GENERAL INCLUDE FILES */
/*************************/
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

/*************************/
/* PROJECT INCLUDE FILES */
/*************************/
#include "FILE_01_util.h"
#include "FILE_14_SolutionSet_ErrorMsg.h"
#include "FILE_17_SolutionSet_AST.h"

/**********/
/* ALLOCA */
/**********/
#define alloca malloc

/*******************/
/* LEXING FUNCTION */
/*******************/
int cclex(void);

/******************/
/* ERROR FUNCTION */
/******************/
void ccerror(char *s)
{
	SolutionSet_ErrorMsg_Error(SolutionSet_ErrorMsg_tokPos,"%s",s);
}

/************/
/* AST ROOT */
/************/
int SolutionSet_AST_ROOT;

%}

/********************************************************************************/
/* This union is a C replacement for an abstract class representing an AST node */
/********************************************************************************/
%union
{
	union
	{
		int			ival;
		float		fval;
		string		sval;
	}
	gval;
}

/*************/
/* TERMINALS */
/*************/
%token <gval> INT
%token <gval> LPAREN
%token <gval> RPAREN
%token <gval> LBRACE
%token <gval> RBRACE
%token <gval> COMMA
%token <gval> PLUS
%token <gval> MINUS
%token <gval> DIVIDE
%token <gval> SPAN
%token <gval> COMMA


/*****************/
/* NON TERMINALS */
/*****************/
%type <gval> program
%type <gval> solutionSet
%type <gval> RowVecList
%type <gval> RowVec
%type <gval> Number
%type <gval> Op


/**************/
/* START HERE */
/**************/
%start program

%%

program:		solutionSet		{printf("program --> solutionSet \n");}

solutionSet: 		LBRACE RowVec RBRACE Op SPAN LPAREN LBRACE RowVecList RBRACE RPAREN	{printf("solutionSet --> LBRACE RowVec RBRACE Op SPAN LPAREN LBRACE RowVecList RBRACE RPAREN \n");}
			| SPAN LPAREN LBRACE RowVecList RBRACE RPAREN		{printf("solutionSet --> SPAN LPAREN LBRACE RowVecList RBRACE RPAREN \n");}
			| LBRACE  RowVec RBRACE		{printf("solutionSet --> LBRACE  RowVec RBRACE \n");}

RowVecList:		RowVec COMMA RowVecList 	{printf("RowVecList --> RowVec COMMA RowVecList \n");}
			| RowVec		{printf("solutionSet --> RowVec \n");}

RowVec:  		LPAREN Number COMMA Number RPAREN			{printf("RowVec --> LPAREN Number COMMA Number RPAREN \n");}
			| LPAREN Number COMMA Number COMMA Number RPAREN		{printf("RowVec --> LPAREN Number COMMA Number COMMA Number RPAREN \n");}
			| LPAREN Number COMMA Number COMMA Number COMMA Number RPAREN	{printf("RowVec --> LPAREN Number COMMA Number COMMA Number COMMA Number RPAREN \n");}


Number: 		INT DIVIDE INT		{printf("Number --> INT DEVIDE INT \n");}
			| INT 			{printf("Number --> INT \n");}
			| Op INT DIVIDE INT	{printf("Number --> OP INT DEVIDE INT \n");}
			| Op INT		{printf("Number --> OP INT \n");}
			| Op INT DIVIDE Op INT	{printf("Number --> OP INT DEVIDE OP INT \n");}
			| INT DIVIDE Op INT	{printf("Number --> INT DIVIDE OP INT \n");}

Op:			PLUS            {printf("Op --> PLUS \n");}
			| MINUS		{printf("Op --> MINUS \n");}


%%
