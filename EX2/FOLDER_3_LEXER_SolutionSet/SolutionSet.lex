%{
/*************************/
/* GENERAL INCLUDE FILES */
/*************************/
#include <math.h>
#include <string.h>
#include <stdlib.h>

/*************************/
/* PROJECT INCLUDE FILES */
/*************************/
#include "SolutionSet_ErrorMsg.h"
#include "SolutionSet_Tokens.h"
#include "util.h"

/**************************/
/* CONTROL ERROR MESSAGES */
/**************************/
static int charPos=1;

/******************/
/* PROVIDE ccWRAP */
/******************/
int ccwrap(void)
{
	charPos=1;
	return 1;
}

/**************************/
/* CONTROL ERROR MESSAGES */
/**************************/
static void adjust(void)
{
	SolutionSet_ErrorMsg_tokPos = charPos;
	charPos += ccleng;
}



%}

/*****************/
/* UNIQUE PREFIX */
/*****************/
%option prefix="cc"

/********************/
/* COMMON REGEXP(s) */
/********************/

/**********/
/* SPACES */
/**********/
WHITE_SPACE		" "|\t
LINE_TERMINATOR	\n

/***************/
/* PARENTHESES */
/***************/
LPAREN	"("
RPAREN	")"
LBRACE	"{"
RBRACE	"}"

/**********/
/* BINOPS */
/**********/
PLUS	"+"
DIVIDE	"/"
MINUS "-"

/*******/
/* INT */
/*******/
INT				[0-9]+
SPAN			"SP"
COMMA			","
		
/*********/
/* RULES */
/*********/
%%
{WHITE_SPACE}		        {adjust(); continue;}
{LINE_TERMINATOR}	        {adjust(); SolutionSet_ErrorMsg_Newline(); continue;}
{LPAREN}			{adjust(); /*SolutionSet_ErrorMsg_Log("(");*/  return LPAREN;}
{RPAREN}			{adjust(); /*SolutionSet_ErrorMsg_Log(")");*/  return RPAREN;}
{LBRACE}			{adjust(); /*SolutionSet_ErrorMsg_Log("{");*/  return LBRACE;}
{RBRACE}			{adjust(); /*SolutionSet_ErrorMsg_Log("}");*/  return RBRACE;}
{SPAN}			        {adjust(); /*SolutionSet_ErrorMsg_Log("SP");*/  return SPAN;}
{COMMA}			        {adjust(); /*SolutionSet_ErrorMsg_Log(",");*/  return COMMA;}
{PLUS}                          {adjust(); /* RowOperations_ErrorMsg_Log("+ ");  */ return PLUS;}
{MINUS}                         {adjust(); /* RowOperations_ErrorMsg_Log("- "); */  return MINUS;}
{DIVIDE}                        {adjust(); /*  RowOperations_ErrorMsg_Log("/ "); */  return DIVIDE;}
{INT}                           {
                                                adjust();
                                                //bblval.gval.ival=atoi(bbtext);
                                                //RowOperations_ErrorMsg_Log("INT(%d) ",bblval.gval.ival);
                                                return INT;
                                }
.                               {adjust(); /* RowOperations_ErrorMsg_Log("ERROR ");*/   return ERROR;}

				

