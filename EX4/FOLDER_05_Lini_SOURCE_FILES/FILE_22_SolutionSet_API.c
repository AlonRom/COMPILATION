/*****************************/
/* FILE_22_SolutionSet_API.c */
/*****************************/

/*************************/
/* GENERAL INCLUDE FILES */
/*************************/
#include <stdio.h>

/*************************/
/* PROJECT INCLUDE FILES */
/*************************/
#include "FILE_01_util.h"
#include "FILE_14_SolutionSet_ErrorMsg.h"
#include "FILE_17_SolutionSet_AST.h"
#include "FILE_18_SolutionSet_API.h"

/**********************/
/* Parse Solution Set */
/**********************/
int Parse_SolutionSet(string SolutionSet_Filename, string Output_Filename)
{
	/*************************/
	/* Open file for parsing */
	/*************************/
	SolutionSet_ErrorMsg_Reset(SolutionSet_Filename);
	FILE * fp;
	/*******************************/
	/* 3 ... 2 ... 1 ... parse !!! */
	/*******************************/
	fp = fopen (Output_Filename,"w+");
	fprintf(fp,"%s", "Fail\n");
	fclose(fp);
	if (ccparse() == 0)
	{	
		 fp = fopen (Output_Filename, "w+");
		 fprintf(fp, "%s", "OK\n");
		 fclose(fp);
		//SolutionSet_ErrorMsg_Log("OK\n");
		/******************/
		/* parsing worked */
		/******************/
		return SolutionSet_AST_ROOT;
	}
	else
	{
		 fp = fopen (Output_Filename, "w+");
		 fprintf(fp, "%s", "FAIL\n");
		 fclose(fp);
		//SolutionSet_ErrorMsg_Log("FAIL\n");
		/******************/
		/* parsing failed */
		/******************/
		return NULL;
	}
}

