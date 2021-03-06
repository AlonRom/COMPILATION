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
#include "MatReader_ErrorMsg.h"
#include "MatReader_Tokens.h"
#include "util.h"

/**************************/
/* CONTROL ERROR MESSAGES */
/**************************/
static int charPos=1;

/******************/
/* PROVIDE aaWRAP */
/******************/
int aawrap(void)
{
	charPos=1;
	return 1;
}

/**************************/
/* CONTROL ERROR MESSAGES */
/**************************/
static void adjust(void)
{
	MatReader_ErrorMsg_tokPos = charPos;
	charPos += aaleng;
}

/***********/
/* YYSTYPE */
/***********/
YYSTYPE aalval;

%}

/*****************/
/* UNIQUE PREFIX */
/*****************/
%option prefix="aa"

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
LBRACK	"["
RBRACK	"]"

/**************/
/* SEPARATORS */
/**************/
SEMICOLON	";"

/**********/
/* BINOPS */
/**********/
DIVIDE	 	"/"|"\\"

/*******/
/* INT */
/*******/
INT			[0-9]+|-[0-9]+
	  
		
/*********/
/* RULES */
/*********/
%%
{WHITE_SPACE}		{adjust(); continue;}
{LINE_TERMINATOR}	{adjust(); MatReader_ErrorMsg_Newline(); continue;}
{LBRACK}			{adjust(); MatReader_ErrorMsg_Log("[ "); return LBRACK;}
{RBRACK}			{adjust(); MatReader_ErrorMsg_Log("]"); return RBRACK;}
{DIVIDE}			{adjust(); MatReader_ErrorMsg_Log("/ "); return DIVIDE;}
{SEMICOLON}			{adjust(); MatReader_ErrorMsg_Log("; "); return SEMICOLON;}
{INT}				{
					adjust();
					aalval.gval.ival=atoi(aatext);
					MatReader_ErrorMsg_Log("INT(%d) ",aalval.gval.ival);
					return INT;
				}

