/***********************/
/* FILE NAME: driver.c */
/***********************/

/*************************/
/* GENERAL INCLUDE FILES */
/*************************/
#include <stdio.h>
#include <stdlib.h>

/*************************/
/* PROJECT INCLUDE FILES */
/*************************/
#include "util.h"
#include "MatReader_ErrorMsg.h"
#include "RowOperations_ErrorMsg.h"
#include "RowOperations_Tokens.h"
#include "SolutionSet_ErrorMsg.h"

#define EOF 0

int aalex(void);
int bblex(void);
int cclex(void);

/*************************/
/* ROW OPERATION METHODS */
/*************************/
void RowOperationList();
void RowOperation();
void Operation();
void MulRow(); 
void MathOperation();
void Binop();
void AddRow();
void SubtractRow();
void AfterMul();
void AfterSubtract();
void Eat(int expectedToken);

/***************************/
/* ROW OPERATION VARIABLES */
/***************************/
int tok;
bool hasError;
int currentRow;

/*****************/
/* START OF CODE */
/*****************/
void usage(int argc, char **argv)
{
	if (argc != 5)
	{
		printf("%d",argc);
		fprintf(stderr,"usage: a.out filename\n");
	}
}

int main(int argc, char **argv)
{
	string RowOperations_Filename=argv[1];
	string SolutionSet_Filename  =argv[2];
	string RowOperationsOutput   =argv[3];
	string SolutionSetOutput     =argv[4];
	
	usage(argc,argv);
	
	RowOperations_ErrorMsg_Set_Log_Filename(RowOperationsOutput);
	SolutionSet_ErrorMsg_Set_Log_Filename(SolutionSetOutput);
	
	RowOperations_ErrorMsg_Reset(RowOperations_Filename);
	SolutionSet_ErrorMsg_Reset(SolutionSet_Filename);

	printf("\n\n");
	
	hasError = 0;	
	currentRow++;	
    	tok = bblex();	
	RowOperationList();
	if(hasError == 0)
		RowOperations_ErrorMsg_Log("OK\n");
	tok = bblex(); //make sure its EOF	



	
	while(bblex());
	while(cclex());
	
	return 0;
}

void Eat(int expectedToken)
{
	if (tok == expectedToken)
	{
		tok = bblex();
	}
	else
	{
		RowOperations_ErrorMsg_Log("Error(%d)\n\n", currentRow);
		hasError = 1;
	}
}

void RowOperationList()
{
	if (hasError)
		return;

	switch (tok)
	{
		// rowOperationList ---> rowOperation rowOperationList
		case(ROW):
			RowOperation();
			break;
		case(LINE_TERMINATOR):
			currentRow++;
			Eat(LINE_TERMINATOR);
			RowOperation();
			break;
		case(EOF):
			break;
		default:
			if (!hasError)
			{
				RowOperations_ErrorMsg_Log("Error(%d)\n\n", currentRow);
				hasError = 1;
			}
			break;
	}
}

void RowOperation()
{
	if (hasError)
		return;
	switch (tok)
	{	
		// R ---> <- | <->
		case(ROW):
			Eat(ROW);
			Operation();
			break;
		case(LINE_TERMINATOR):
			currentRow++;
			Eat(LINE_TERMINATOR);
			RowOperation();
			break;
		case(ERROR):
			RowOperations_ErrorMsg_Log("Error(%d)\n\n", currentRow);
			hasError = 1;
			break;
		case(EOF):
			break;
		default:
			if (!hasError)
			{
				RowOperations_ErrorMsg_Log("Error(%d)\n\n", currentRow);
				hasError = 1;
			}
			break;
	}
}

void Operation()
{
	switch (tok)
	{
		// R ---> <-
		case(LEFT_ARROW):
			Eat(LEFT_ARROW);
			MathOperation();
			RowOperation();
			break;
		// R ---> <->
		case(LEFT_RIGHT_ARROW):
			Eat(LEFT_RIGHT_ARROW);
			Eat(ROW);
			RowOperation();
			break;
		case(LINE_TERMINATOR):
			Eat(LINE_TERMINATOR);
			RowOperations_ErrorMsg_Log("Error(%d)\n\n", currentRow);
			hasError = 1;
			break;
		case(ERROR):
			RowOperations_ErrorMsg_Log("Error(%d)\n\n", currentRow);
			hasError = 1;
			break;
		case(EOF):
			break;
		default:
			if (!hasError)
			{
				RowOperations_ErrorMsg_Log("Error(%d)\n\n", currentRow);
				hasError = 1;
			}
			break;
	}
}

void MulRow()
{
	switch (tok)
	{
		case(ROW):
			Eat(ROW);
			AfterMul();
			break;
		case(DIVIDE):
			Eat(DIVIDE);
			Eat(INT);
			AfterMul();
			break;
		case(LINE_TERMINATOR):
			Eat(LINE_TERMINATOR);
			RowOperations_ErrorMsg_Log("Error(%d)\n\n", currentRow);
			hasError = 1;
			break;
		case(ERROR):
			RowOperations_ErrorMsg_Log("Error(%d)\n\n", currentRow);
			hasError = 1;
			break;
		case(EOF):
			break;
		default:
			if (!hasError)
			{
				RowOperations_ErrorMsg_Log("Error(%d)\n\n", currentRow);
				hasError = 1;
			}
			break;
	}
}



void MathOperation()
{
	switch (tok)
	{
		// R ---> R + | R -
		case(ROW):
			Eat(ROW);
			Binop();
			break;
		// R ---> INT MULROW
		case(INT):
			Eat(INT);
			MulRow();
			break;
		// R ---> - SUBROW
		case(MINUS):
			Eat(MINUS);
			SubtractRow();
			break;
		case(EOF):
			break;
		default:
			if (!hasError)
			{
				RowOperations_ErrorMsg_Log("Error(%d)\n\n", currentRow);
				hasError = 1;
			}
			break;
	}
}

void Binop()
{
	switch (tok)
	{
		// R ---> R + R | R + INT R
		case(PLUS):
			Eat(PLUS);
			AddRow();
			break;
		// R ---> R - R | R - INT R | R - INT / INT R
		case(MINUS):
			Eat(MINUS);
			SubtractRow();
			break;
	}
}

void AddRow()
{
	switch (tok)
	{
	// R ---> + R
	case(ROW):
		Eat(ROW);
		Eat(LINE_TERMINATOR);
		currentRow++;
		break;
	// R ---> + INT R
	case(INT):
		Eat(INT);
		Eat(ROW);
		Eat(LINE_TERMINATOR);
		currentRow++;
		break;
	case(LINE_TERMINATOR):
		Eat(LINE_TERMINATOR);
		RowOperations_ErrorMsg_Log("Error(%d)\n\n", currentRow);
		hasError = 1;
		break;
	case(ERROR):
		RowOperations_ErrorMsg_Log("Error(%d)\n\n", currentRow);
		hasError = 1;
		break;
	case(EOF):
		break;
	default:
		if (!hasError)
		{
			RowOperations_ErrorMsg_Log("Error(%d)\n\n", currentRow);
			hasError = 1;
		}
		break;
	}
}

void SubtractRow()
{
	switch (tok)
	{
	// R ---> - R
	case(ROW):
		Eat(ROW);
		Eat(LINE_TERMINATOR);
		currentRow++;
		break;
	// R ---> - INT R | - INT/INT R
	case(INT):
		Eat(INT);
		AfterSubtract();
		break;
	case(LINE_TERMINATOR):
		Eat(LINE_TERMINATOR);
		RowOperations_ErrorMsg_Log("Error(%d)\n\n", currentRow);
		hasError = 1;
		break;
	case(ERROR):
		RowOperations_ErrorMsg_Log("Error(%d)\n\n", currentRow);
		hasError = 1;
		break;
	case(EOF):
		break;
	default:
		if (!hasError)
		{
			RowOperations_ErrorMsg_Log("Error(%d)\n\n", currentRow);
			hasError = 1;
		}
		break;
	}
}

void AfterMul()
{
	switch (tok)
	{
		case(ROW):
			Eat(ROW);
			Eat(LINE_TERMINATOR);
			currentRow++;
			break;	
		case(PLUS):
			Eat(PLUS);
			AddRow();
			break;
		case(MINUS):
			Eat(MINUS);
			SubtractRow();
			break;
		case(LINE_TERMINATOR):
			currentRow++;
			Eat(LINE_TERMINATOR);
			RowOperation();
			break;
		case(ERROR):
			RowOperations_ErrorMsg_Log("Error(%d)\n\n", currentRow);
			hasError = 1;
			break;
		case(EOF):
			break;
		default:
			if (!hasError)
			{
				RowOperations_ErrorMsg_Log("Error(%d)\n\n", currentRow);
				hasError = 1;
			}
			break;
	}
}

void AfterSubtract()
{
	switch (tok)
	{
	// R ---> - INT R
	case(ROW):
		Eat(ROW);
		Eat(LINE_TERMINATOR);
		currentRow++;
		break;
	// R ---> - INT/INT R
	case(DIVIDE):
		Eat(DIVIDE);
		Eat(INT);
		Eat(ROW);
		Eat(LINE_TERMINATOR);
		currentRow++;
		break;
	case(LINE_TERMINATOR):
		Eat(LINE_TERMINATOR);
		RowOperations_ErrorMsg_Log("Error(%d)\n\n", currentRow);
		hasError = 1;
		break;
	case(ERROR):
		RowOperations_ErrorMsg_Log("Error(%d)\n\n", currentRow);
		hasError = 1;
		break;
	case(EOF):
		break;
	default:
		if (!hasError)
		{
			RowOperations_ErrorMsg_Log("Error(%d)\n\n", currentRow);
			hasError = 1;
		}
		break;
	}
}
