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
#include "SolutionSet_Tokens.h"



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

/***************************/
/* SOLUTION SET VARIABLES  */
/***************************/

int size = 0;
int commaCounter = 0;
int commaDefCounter = 0;
int coloum = 0;
//-- to enable debug set to 1
int debugEnabled = 1;


/***************************/
/* SOLUTION SET METHODS    */
/***************************/

void SolutionOperationList();
void Lbrace();
void Operation();

void StartVector();
void AfterRparen();
void AfterInt();
void AfterComma();
void AfterRbrace();
void AfterPlus();
void AfterSpan();
void AfterLparen();
void AfterDivide();
void AfterMinus();

void Logging(int debug,char* string,int row, int coloum,int token)
{
	if (debug == 1)
	{
		if(debugEnabled)
			SolutionSet_ErrorMsg_Log("DEBUG: MESSAGE %s, ROW %d, COLOUM %d, TOKEN %d \n",string,row,coloum,token);
	}
	else
	{
		if (debug == 2)
		{
			SolutionSet_ErrorMsg_Log("INFO: MESSAGE %s \n",string);
		}
		else
		{
			SolutionSet_ErrorMsg_Log("ERROR: MESSAGE %s, ROW %d, COLOUM %d, TOKEN %d \n",string,row,coloum,token);
		}
	}

}

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

	//-- solution set

	hasError = 0;
	currentRow = 0;
	tok = cclex();

	SolutionOperationList();

	tok = cclex();





	
	while(bblex());
	while(cclex());
	
	return 0;
}


void SolutionOperationList()
{
	currentRow++;
	switch (tok)
	{
		// rowOperationList ---> rowOperation rowOperationList
	case(LBRACE):
		coloum++;
		EatS(LBRACE);
		coloum++;
		Lbrace();
		SolutionOperationList();
		break;

	case(EOF):
		Logging(1,"EOF",0,0,0);
		break;

	default:
		if (hasError)
			//Logging("Error(%d)\n\n", currentRow);
			Logging(0,"Error", currentRow, coloum,tok);
		break;
	}
}

void Lbrace()
{
	switch (tok)
	{
	case(LPAREN):
		coloum++;
		EatS(LPAREN);
		AfterLparen();
		break;

	default:
		//Logging("Error(%d)\n\n", currentRow);
		Logging(0,"Error", currentRow, coloum,tok);
		break;
		//exit(0);
	}
}

void AfterLparen()
{
	//--If there were any commase left from vector seperation {(),()} make the counter zero
	if (commaCounter > 0)
	{
		commaCounter = 0;
	}
	switch (tok)
	{
	case(INT):
		coloum++;
		EatS(INT);
		AfterInt();
		break;
	case(LBRACE):
		coloum++;
		EatS(LBRACE);
		Lbrace();
		break;
	case(MINUS):
		coloum++;
		EatS(MINUS);
		AfterMinus();
		break;
	default:
		Logging(0, "Error", currentRow, coloum, tok);
		break;
	}
}


void OperationS()
{
	switch (tok)
	{
	case(LPAREN):
		coloum++;
		EatS(LPAREN);
		StartVector();
		break;
	default:
		SolutionSet_ErrorMsg_Log("Error(%d) (%d)\n\n", currentRow, coloum);
		break;
	}
}

void StartVector()
{
	commaCounter = 0;
	switch (tok)
	{
	case(INT):
		coloum++;
		EatS(INT);
		AfterInt();
		break;
	case(RPAREN):
		coloum++;
		EatS(RPAREN);
		AfterRparen();
		break;
	default:
		Logging(0, "Error", currentRow, coloum, tok);
		break;
	}
}

void AfterInt()
{
	switch (tok)
	{
	case(RPAREN):
		coloum++;
		EatS(RPAREN);
		AfterRparen();
		break;
	case(COMMA):
		coloum++;
		EatS(COMMA);
		AfterComma();
		break;
	case(DIVIDE):
		coloum++;
		EatS(DIVIDE);
		AfterDivide();
		break;
	default:
		Logging(0, "Error", currentRow, coloum, tok);
		break;
	}
}

void AfterDivide()
{
	switch (tok)
	{
	case(INT):
		coloum++;
		EatS(INT);
		AfterInt();
		break;
	case(MINUS):
		coloum++;
		EatS(MINUS);
		AfterMinus();
		break;
	default:
		Logging(0, "Error", currentRow, coloum, tok);
		break;
	}
}

void AfterMinus()
{
	switch (tok)
	{
	case(INT):
		coloum++;
		EatS(INT);
		AfterInt();
		break;
	default:
		Logging(0, "Error", currentRow, coloum, tok);
		break;
	}
}


void AfterRparen()
{
	//-- Case it's first vector ending
	if (commaDefCounter == 0)
	{
		//-- Set definite counter to comma current counter
		commaDefCounter = commaCounter;
		//-- Make current counter aero
		commaCounter = 0;
	}
	//-- Case it's not first vector
	else
	{
		//-- If amount commas different then definite amount commase throw exception and it's not the start of a new vector
		if (commaCounter != commaDefCounter && tok != 0)
		{
			Logging(0,"Error --> Vectors dimensions are not matching \n \n", currentRow, coloum,tok);
			getchar();
			exit(0);
		}
	}
	commaCounter = 0;
	switch (tok)
	{
	case(RBRACE):
		coloum++;
		EatS(RBRACE);
		AfterRbrace();
		break;
	case (PLUS):
		coloum++;
		EatS(PLUS);
		AfterPlus();
		break;
	case(COMMA):
		coloum++;
		EatS(COMMA);
		AfterComma();
		break;
	default:
		if (tok != 0)
		{
			Logging(0, "Error", currentRow, coloum, tok);
		}
		else
		{
			Logging(2, " === NO ERRORS IN FILE === ", 0, 0, 0);
		}
		break;
	}

}

void AfterRbrace()
{
	switch (tok)
	{
	case(RBRACE):
		coloum++;
		EatS(RBRACE);
		AfterRbrace();
		break;
	case(PLUS):
		coloum++;
		EatS(PLUS);
		AfterPlus();
		break;
	case(RPAREN):
		coloum++;
		EatS(RPAREN);
		AfterRparen();
		break;
	default:
		Logging(0, "Error", currentRow, coloum, tok);
		break;
	}
}

void AfterPlus()
{
	switch (tok)
	{
	case(SPAN):
		coloum++;
		EatS(SPAN);
		AfterSpan();
		break;
	default:
		Logging(0, "Error", currentRow, coloum, tok);
		break;
	}
}


void AfterComma()
{
	commaCounter++;
	switch (tok)
	{
	case(INT):
		coloum++;
		EatS(INT);
		AfterInt();
		break;
	case(LPAREN):
		coloum++;
		EatS(LPAREN);
		StartVector();
		break;
	case(MINUS):
		coloum++;
		EatS(MINUS);
		AfterMinus();
		break;
	default:
		Logging(0, "Error", currentRow, coloum, tok);
		break;
	}
}

void AfterSpan()
{
	switch (tok)
	{
	case(LPAREN):
		coloum++;
		EatS(LPAREN);
		AfterLparen();
		break;
	default:
		Logging(0, "Error", currentRow, coloum, tok);
		break;
	}
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

void EatS(int expectedToken)
{
	if (tok == expectedToken)
	{
		//Logging("EatS: (%d)\n", tok);
		Logging(1,"EatS:",currentRow,coloum, tok);
		tok = cclex();
		if (tok == ERROR)
		{
			Logging(0, "Wrong Char", currentRow, coloum, tok);
		}
	}
	else
	{
		Logging(0,"Error",currentRow,coloum,tok);
		hasError = 1;
		//exit(0);
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
