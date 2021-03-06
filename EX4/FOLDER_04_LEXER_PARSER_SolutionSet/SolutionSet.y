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
%type <gval> RowVecListSize2
%type <gval> RowVecListSize3
%type <gval> RowVecListSize4
%type <gval> RowVecSize2
%type <gval> RowVecSize3
%type <gval> RowVecSize4
%type <gval> Number
%type <gval> Op

/**************/
/* START HERE */
/**************/
%start program

%%

program:		solutionSet		{printf("program --> solutionSet \n");}

solutionSet: 		LBRACE RowVecSize2 RBRACE Op SPAN LPAREN LBRACE RowVecListSize2 RBRACE RPAREN	{printf("solutionSet --> LBRACE RowVecSize2 RBRACE Op SPAN LPAREN LBRACE RowVecListSize2 RBRACE RPAREN \n");}
			| SPAN LPAREN LBRACE RowVecListSize2 RBRACE RPAREN		{printf("solutionSet --> SPAN LPAREN LBRACE RowVecListSize2 RBRACE RPAREN \n");}
			| LBRACE RowVecSize2 RBRACE		{printf("solutionSet --> LBRACE  RowVecSize2 RBRACE \n");}
			| LBRACE RowVecSize3 RBRACE Op SPAN LPAREN LBRACE RowVecListSize3 RBRACE RPAREN	{printf("solutionSet --> LBRACE RowVecSize3 RBRACE Op SPAN LPAREN LBRACE RowVecListSize3 RBRACE RPAREN \n");}
			| SPAN LPAREN LBRACE RowVecListSize3 RBRACE RPAREN		{printf("solutionSet --> SPAN LPAREN LBRACE RowVecListSize3 RBRACE RPAREN \n");}
			| LBRACE RowVecSize3 RBRACE		{printf("solutionSet --> LBRACE  RowVecSize3 RBRACE \n");}
			| LBRACE RowVecSize4 RBRACE Op SPAN LPAREN LBRACE RowVecListSize4 RBRACE RPAREN	{printf("solutionSet --> LBRACE RowVecSize4 RBRACE Op SPAN LPAREN LBRACE RowVecListSize4 RBRACE RPAREN \n");}
			| SPAN LPAREN LBRACE RowVecListSize4 RBRACE RPAREN		{printf("solutionSet --> SPAN LPAREN LBRACE RowVecListSize4 RBRACE RPAREN \n");}
			| LBRACE RowVecSize4 RBRACE		{printf("solutionSet --> LBRACE  RowVecSize4 RBRACE \n");}

RowVecListSize2:	RowVecSize2 COMMA RowVecListSize2 	{printf("RowVecListSize2 --> RowVecSize2 COMMA RowVecListSize2 \n");}
			| RowVecSize2		{printf("RowVecListSize2 --> RowVecSize2 \n");}
			
RowVecListSize3:	RowVecSize3 COMMA RowVecListSize3 	{printf("RowVecListSize3 --> RowVecSize3 COMMA RowVecListSize3 \n");}
			| RowVecSize3		{printf("RowVecListSize3 --> RowVecSize3 \n");}
			
RowVecListSize4:	RowVecSize4 COMMA RowVecListSize4 	{printf("RowVecListSize4 --> RowVecSize4 COMMA RowVecListSize4 \n");}
			| RowVecSize4		{printf("RowVecListSize4 --> RowVecSize4 \n");}

RowVecSize2:  		LPAREN Number COMMA Number RPAREN		{printf("RowVecSize2 --> LPAREN Number COMMA Number RPAREN \n");}

RowVecSize3:  		LPAREN Number COMMA Number COMMA Number RPAREN		{printf("RowVecSize3 --> LPAREN Number COMMA Number COMMA Number RPAREN \n");}

RowVecSize4:  	        LPAREN Number COMMA Number COMMA Number COMMA Number RPAREN	{printf("RowVecSize4 --> LPAREN Number COMMA Number COMMA Number COMMA Number RPAREN \n");}

Number: 		INT DIVIDE INT		{
							if($3.ival == 0)
							{
								printf("ERROR !!!\n");
								exit(0);
							}
							else
							{
								printf("Number --> INT DEVIDE INT \n");
							}
						}
		        | Op INT DIVIDE INT	{
							if($4.ival == 0)
							{
								printf("ERROR !!!\n");
								exit(0);
							}
							else
							{
								printf("Number --> Op INT DEVIDE INT \n");
							}
						}
			| INT 			{printf("Number --> INT \n");}
			| Op INT 		{printf("Number --> Op INT \n");}
		

Op:			PLUS            {printf("Op --> PLUS \n");}
			| MINUS		{printf("Op --> MINUS \n");}

%%
