#ifndef __SOLUTION_SET_TOKENS_H__
#define __SOLUTION_SET_TOKENS_H__

/***********************************/
/* FLEX uses 0-255 for inner stuff */
/***********************************/
#define SERIAL_NUMBER_START_s	276
#define SERIAL_NUMBER_START 256
/*********************/
/* TOKENS start here */
/*********************/
#define LPAREN	SERIAL_NUMBER_START_s+1
#define RPAREN	SERIAL_NUMBER_START_s+2
#define LBRACE	SERIAL_NUMBER_START_s+3
#define RBRACE	SERIAL_NUMBER_START_s+4
#define SPAN	SERIAL_NUMBER_START_s+5
#define COMMA	SERIAL_NUMBER_START_s+6


#define INT                             SERIAL_NUMBER_START+5
#define PLUS                            SERIAL_NUMBER_START+6
#define MINUS                           SERIAL_NUMBER_START+7
#define DIVIDE                          SERIAL_NUMBER_START+8
#define ERROR                           SERIAL_NUMBER_START+9


/* TYPES */
/*********/

/****************************/
/* EXTERNAL VARIABLE cclval */
/****************************/

#endif
