/***********************/
/* FILE NAME: driver.c */
/***********************/

/*************************/
/* GENERAL INCLUDE FILES */
/*************************/
#include <stdio.h>

/*************************/
/* PROJECT INCLUDE FILES */
/*************************/
#include "util.h"
#include "Parser.h"
#include "Calc_ErrorMsg.h"

/*****************/
/* START OF CODE */
/*****************/
int main(int argc, char **argv)
{
	string fname;

	if (argc != 3)
	{
		fprintf(stderr,"usage: a.out filename\n");
		return 0;
	}
	
	fname=argv[1];
	
	Calc_ErrorMsg_Reset(fname);

	printf("\n\n");

	if (Parse())
	{
		printf("\n\nLegal Expression\n\n");
	}
	else
	{
		printf("\n\nIllegal Expression\n\n");
	}
	
	return 0;
}

