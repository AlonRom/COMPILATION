/******************************/
/* FILE NAME: Calc_ErrorMsg.c */
/******************************/

/****************************************/
/* WARNING DISABLE: sprintf - I love it */
/****************************************/
#pragma warning (disable: 4996)

/*************************/
/* GENERAL INCLUDE FILES */
/*************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

/*************************/
/* PROJECT INCLUDE FILES */
/*************************/
#include "util.h"
#include "Calc_ErrorMsg.h"

/***************/
/* DEFINITIONS */
/***************/
#define MAX_FILENAME_LENGTH 100

/****************/
/* LOG FILENAME */
/****************/
char Calc_ErrorMsg_Log_Filename[MAX_FILENAME_LENGTH];

/********************/
/* GLOBAL VARIABLES */
/********************/
static bool anyErrors= FALSE;
static string fileName = "";
static int lineNum = 1;

/********************/
/* GLOBAL VARIABLES */
/********************/
int Calc_ErrorMsg_tokPos=0;

/********************/
/* GLOBAL VARIABLES */
/********************/
int numVars=0;

/**********************/
/* EXTERNAL VARIABLES */
/**********************/
extern FILE *zzin;

/*********/
/* TYPES */
/*********/
typedef struct intList {int i; struct intList *rest;} *IntList;

/*********/
/* CTORS */
/*********/
static IntList intList(int i, IntList rest) 
{
	IntList l= (IntList) checked_malloc(sizeof *l);
	l->i=i; l->rest=rest;
	
	return l;
}

/********************/
/* GLOBAL VARIABLES */
/********************/
static IntList linePos=NULL;

/********************/
/* GLOBAL VARIABLES */
/********************/
FILE *Calc_ErrorMsg_Log_fl;

/****************/
/* LOG FUNCTION */
/****************/
void Calc_ErrorMsg_Log(char *message,...)
{
	/***********/
	/* va_list */
	/***********/
	va_list ap;

	/*********************************************/
	/* Reset the file content from previous runs */
	/*********************************************/
	static int first_time=1;

	if (first_time == 1) {
		first_time  = 0;
		Calc_ErrorMsg_Log_fl = fopen(Calc_ErrorMsg_Log_Filename,"w+t");
		if (Calc_ErrorMsg_Log_fl == NULL) return;
		fclose(Calc_ErrorMsg_Log_fl);
	}

	/*************************/
	/* For each LEXED token: */
	/* [1] open the log file */
	/* [2] write the token   */
	/* [3] close the file    */
	/*************************/
	/*************************/
	/* [1] Open the log file */
	/*************************/
	Calc_ErrorMsg_Log_fl = fopen(Calc_ErrorMsg_Log_Filename,"a+t");
	if (Calc_ErrorMsg_Log_fl == NULL) return;
		
	/*************************/
	/* [2] Write LEXED token */
	/*************************/
	va_start(ap,message);
	vfprintf(Calc_ErrorMsg_Log_fl, message, ap);
	va_end(ap);

	/**********************/
	/* [3] Close the file */
	/**********************/
	fclose(Calc_ErrorMsg_Log_fl);
}

/***********/
/* NEWLINE */
/***********/
void Calc_ErrorMsg_Newline(void)
{
	lineNum++;
	linePos = intList(Calc_ErrorMsg_tokPos, linePos);
}

/*********/
/* ERROR */
/*********/
void Calc_ErrorMsg_Error(int pos, char *message,...)
{
	va_list ap;
	IntList lines = linePos;
	int num=lineNum;

	anyErrors=TRUE;
	while (lines && lines->i >= pos) 
	{
		lines=lines->rest;
		num--;
	}

	if (fileName)
	{
		fprintf(stderr,"%s:",fileName);
	}
	
	if (lines)
	{
		fprintf(stderr,"%d.%d: ", num, pos-lines->i);
	}
	
	va_start(ap,message);
	vfprintf(stderr, message, ap);
	va_end(ap);
	fprintf(stderr,"\n");

	/*********************************/
	/* [0] exit at the first mistake */
	/*********************************/
	exit(0);
}

/****************/
/* LOG FILENAME */
/****************/
void Calc_ErrorMsg_Set_Log_Filename(string log_Filename)
{
	strcpy(Calc_ErrorMsg_Log_Filename,log_Filename);
}

/*********/
/* RESET */
/*********/
void Calc_ErrorMsg_Reset(string fname)
{
	anyErrors=FALSE;
	fileName=fname;
	lineNum=1;
	linePos=intList(0,NULL);
	zzin = fopen(fname,"r");
	if (!zzin)
	{
		Calc_ErrorMsg_Error(0,"cannot open");
		exit(1);
	}
}

