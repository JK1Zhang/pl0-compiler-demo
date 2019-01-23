#ifndef __PL0_TAX_H__
#define __PL0_TAX_H__
#include "stack.h"
#define TXMAX				500 		// max length of token table
#define MAXADDRESS 	32767		// max address
#define MAX_ID_LEN 10
#define Max_Parser_Len 6
#define Max_First_Len 10
#define Max_Synch_Len 25
#define TerminalNum 31
#define NonterminalNum 20
#define Width 4
#define Max_Ins_len 99999
#define CXMAX 1000
#define STACKSIZE 500
#define PROCEDURE_NUM 10
/*variables for token table*/

int table_index = 0;
/*struct for token table*/

typedef struct {
	char name[MAX_ID_LEN + 1];
	int kind;
	int value;
	int level;
	int address;
	int local;
    int procedureaddress;
    int procedureendaddress;
    int size;
    int dimenssion; //dimenssion of array
    int Enum[3];    //size of each dimenssion
	BOOL  Return;//增加符号表成员项Return(函数是否有返回)
} Table;
/*definition for token table*/

int local_ornot;
Table token_table[TXMAX];
/*identifier type*/

enum idtype {
	ID_CONSTANT,
	ID_VARIABLE,
	ID_PROCEDURE
};

enum opcode{
    PUT,/* 将value放入栈顶 */
    LD,/*从栈顶取一个值（address），将memory中address位置的值放入栈顶 *//* 将memory中address位置的值放入栈顶 */
    ST,/*从栈顶取一个值（address），再取一个值（v），将值v存入memory中address位置 *//*从栈顶取一个值（v），将值v存入memory中address位置 */
    JMP,/*从栈顶取一个值（address），跳转到代码段的address位置 *//*跳转到代码段的address位置 */
    JPC,/*从栈顶取布尔值，根据这个值是否为真来决定是否跳转到代码段的address位置 */
    INT,/* flag = 0 打印栈顶值（不取出）； flag = 1程序终止 */
    ADD,/*从栈顶取一个值（l），再取一个值（r），执行l+r运算，将算得的值放入栈顶 */
    SUB,/*从栈顶取一个值（l），再取一个值（r），执行l-r运算，将算得的值放入栈顶 */
    MUL,/*从栈顶取一个值（l），再取一个值（r），执行l*r运算，将算得的值放入栈顶 */
    DIV,/*从栈顶取一个值（l），再取一个值（r），执行l/r运算，将算得的值放入栈顶 */
    EQ,/*从栈顶取一个值（l），再取一个值（r），判断l是否等于r，将算得的布尔值放入栈顶 */
    LE,/*从栈顶取一个值（l），再取一个值（r），判断l是否小于等于r，将算得的布尔值放入栈顶 */
    LT,/*从栈顶取一个值（l），再取一个值（r），判断l是否小于r，将算得的布尔值放入栈顶 */
    GE,/*从栈顶取一个值（l），再取一个值（r），判断l是否大于等于r，将算得的布尔值放入栈顶 */
    GT,/*从栈顶取一个值（l），再取一个值（r），判断l是否大于r，将算得的布尔值放入栈顶 */
    AND,/*从栈顶取一个布尔值（l），再取一个布尔值（r），执行l && r运算，将算得的布尔值放入栈顶 */
    OR, /*从栈顶取一个布尔值（l），再取一个布尔值（r），执行l || r运算，将算得的布尔值放入栈顶 */
    NOT  /*从栈顶取一个布尔值（l），做非运算，将算得的布尔值放入栈顶 */
};
enum InsKind{
    NoAdressOrNum,
    AdressOrNum
};
char *Print_code[] = {"PUT","LD","ST","JMP","JPC"};
char *Instruction[]={"PUT","LD","ST","JMP","JPC","INT","ADD","SUB","MUL","DIV","EQ",
                    "LE","LT","GE","GT","AND","OR","NOT"};

typedef struct{
    int function_code;
    int level;
    int address;
    int kind;//0不带地址，1带地址
}instruction;
instruction code[CXMAX];
instruction temp_code[PROCEDURE_NUM][CXMAX];//保存临时过程的指令
int code_index = 0;
int code_index_main = 0;
int code_index_pro=0;//the position of the start of procedure
int code_index_endpro=0;//the end position
int code_index_call = 0;
int code_index_if[6] ={ 0,0,0,0,0,0};
int code_index_if_count=0;


int code_index_and=0;
int code_index_or=0;


BOOL code_index_if_flag=FALSE;
int code_index_endif[6] ={ 0,0,0,0,0,0};
int code_index_endif_count=0;
BOOL code_index_endif_flag=FALSE;
int code_index_while[6] ={ 0,0,0,0,0,0};
int code_index_while_count=0;
int code_index_return=0;
BOOL code_index_while_flag=FALSE;//used as a flag for filling the adress of while
BOOL return_flag = FALSE;
int level = 0;
int procedure_level = 0;


Stack *S;
/*First */



const char *BF[Max_First_Len]={"CONST","VAR","PROCEDURE","e","ident","CALL","IF","BEGIN","WHILE","\0"};

const char *SF[Max_First_Len]={"CONST","VAR","PROCEDURE","\0"};

const char *CF[Max_First_Len]={"CONST","\0"};

const char *VF[Max_First_Len]={"ident","\0"};

const char *WF[Max_First_Len]={"ident","\0"};

const char *EF[Max_First_Len]={"COMMA","e","\0"};

const char *FF[Max_First_Len]={"COMMA","e","\0"};

const char *GF[Max_First_Len]={"LSBRACKET","e","\0"};

const char *MF[Max_First_Len]={"VAR","\0"};

const char *NF[Max_First_Len]={"PROCEDURE","\0"};

const char *XF[Max_First_Len]={"CONST","VAR","PROCEDURE","e","ident","CALL","IF","BEGIN","WHILE","\0"};

const char *STF[Max_First_Len]={"ident","CALL","BEGIN","IF","WHILE","RETURN","DO","PRINT","\0"};

const char *ELF[Max_First_Len]={"ELSE","ELIF","e","\0"};

const char *ESIF[Max_First_Len]={"ELSE","ELIF","\0"};

const char *IDNUF[Max_First_Len]={"ident","number","MINUS","\0"};

const char *STQF[Max_First_Len]={"ident","CALL","BEGIN","IF","WHILE","DO","RETURN","PRINT","e","\0"};

const char *COF[Max_First_Len]={"NOT","ODD","ident","number","MINUS","LPAREN","\0"};


const char *COZF[Max_First_Len]={"AND","OR","e","\0"};

const char *LF[Max_First_Len]={"AND","OR","\0"};

/*
ST → IF CO THEN ST EL
EL →  ESI|e
ESI → ELSE THEN ST
ESI → ELIF CO THEN ST EL
*/

const char *RF[Max_First_Len]={"EQU", "NEQ","LES","LEQ","GTR","GEQ","\0"};

const char *EXF[Max_First_Len]={"ident","number","MINUS","LPAREN","\0"};

const char *TEF[Max_First_Len]={"ident","number","MINUS","LPAREN","\0"};

const char *HF[Max_First_Len]={"PLUS","MINUS","e","\0"};

const char *IF[Max_First_Len]={"PLUS","MINUS","\0"};

const char *JF[Max_First_Len]={"TIMES","SLASH","e","\0"};

const char *KF[Max_First_Len]={"TIMES","SLASH","\0"};

const char *FAF[Max_First_Len]={"ident","number","MINUS","LPAREN","\0"};

const char *AF[Max_First_Len]={"LSBRACKET","e","\0"};

const char *IAF[Max_First_Len]={"ident","\0"};

const char *NUF[Max_First_Len]={"MINUS","number","\0"};
/*Synch for error recovery*/

const char *BS[Max_Synch_Len]={"PERIOD","SEMICOLON","\0"};

const char *SS[Max_Synch_Len]={"CONST","VAR","PROCEDURE","e","ident","CALL","IF","BEGIN","WHILE","\0"};

const char *CS[Max_Synch_Len]={"CONST","VAR","PROCEDURE","ident","CALL","IF","BEGIN","WHILE","\0"};

const char *VS[Max_Synch_Len]={"SEMICOLON","CONST","\0"};

const char *WS[Max_Synch_Len]={"SEMICOLON","VAR","\0"};

const char *ES[Max_Synch_Len]={"SEMICOLON","CONST","VAR","PROCEDURE","\0"};

const char *FS[Max_Synch_Len]={"SEMICOLON","CONST","VAR","PROCEDURE","\0"};

const char *GS[Max_Synch_Len]={"SEMICOLON","CONST","VAR","PROCEDURE","COMMA","\0"};

const char *MS[Max_Synch_Len]={"CONST","VAR","PROCEDURE","ident","CALL","IF","BEGIN","WHILE","\0"};

const char *NS[Max_Synch_Len]={"CONST","VAR","PROCEDURE","ident","CALL","IF","BEGIN","WHILE","\0"};

const char *XS[Max_Synch_Len]={"CONST","VAR","PROCEDURE","ident","CALL","IF","BEGIN","WHILE","\0"};

const char *STS[Max_Synch_Len]={"CONST","VAR","PROCEDURE","ident","CALL","IF","BEGIN","WHILE","PERIOD","SEMICOLON","END","RETURN","PRINT","\0"};

const char *ELS[Max_Synch_Len]={"SEMICOLON","\0"};
const char *ESIS[Max_Synch_Len]={"\0"};
/*
ST → IF CO THEN ST EL
EL → ES|EI|e
ES → ELSE THEN ST
EI → ELIF CO THEN ST EL
*/

const char *IDNUS[Max_Synch_Len]={"ident","number","MINUS","SEMICOLON","\0"};

const char *STQS[Max_Synch_Len]={"CONST","VAR","PROCEDURE","ident","CALL","IF","BEGIN","WHILE","PERIOD","END","RETURN","ELSE","\0"};

const char *COS[Max_Synch_Len]={"THEN","DO","\0"};


const char *COZS[Max_Synch_Len]={"THEN","DO","SEMICOLON","ELSE","\0"};



const char *LS[Max_Synch_Len]={"\0"};

const char *RS[Max_Synch_Len]={"\0"};

const char *EXS[Max_Synch_Len]={"EQU", "NEQ","LES","LEQ","GTR","GEQ","SEMICOLON","RPAREN",
									"THEN","DO","\0"};

const char *TES[Max_Synch_Len]={"EQU", "NEQ","LES","LEQ","GTR","GEQ","SEMICOLON","RPAREN",
									"THEN","DO","PLUS","MINUS","\0"};

const char *HS[Max_Synch_Len]={"CONST","VAR","PROCEDURE","ident","CALL","IF","BEGIN","WHILE","EQU", "NEQ","LES","LEQ","GTR","GEQ","SEMICOLON","RPAREN",
									"ELSE","ELIF","AND","OR","THEN","DO","PLUS","MINUS","ident","\0"};

const char *IS[Max_Synch_Len]={"ident","number","MINUS","LPAREN","\0"};

const char *JS[Max_Synch_Len]={"CONST","VAR","PROCEDURE","ident","CALL","IF","BEGIN","WHILE","EQU", "NEQ","LES","LEQ","GTR","GEQ","SEMICOLON","RPAREN","AND","OR",
									"ELSE","ELIF","THEN","DO","PLUS","MINUS","TIMES","SLASH","ident","\0"};

const char *KS[Max_Synch_Len]={"ident","number","MINUS","LPAREN","\0"};

const char *FAS[Max_Synch_Len]={"EQU", "NEQ","LES","LEQ","GTR","GEQ","SEMICOLON","RPAREN",
									"THEN","DO","PLUS","MINUS","SLASH","TIMES","\0"};

const char *AS[Max_Synch_Len]={"EQU", "NEQ","LES","LEQ","GTR","GEQ","SEMICOLON","RPAREN",
									"THEN","DO","PLUS","MINUS","SLASH","TIMES","BECOMES","BEGIN","ident","LSBRACKET","RSBRACKET","\0"};

const char *IAS[Max_Synch_Len]={"EQU", "NEQ","LES","LEQ","GTR","GEQ","SEMICOLON","RPAREN",
									"THEN","DO","PLUS","MINUS","SLASH","TIMES","BECOMES","BEGIN","\0"};																		

const char *NUS[Max_Synch_Len]={"EQU", "NEQ","LES","LEQ","GTR","GEQ","SEMICOLON","RPAREN",
									"THEN","DO","PLUS","MINUS","SLASH","TIMES","BECOMES","BEGIN","IF",
									"WHILE","DO","COMMA","\0"};																		
/*Terminal*/

const char *Terminal[TerminalNum+3]={"CONST","VAR","PROCEDURE","ident","COMMA","SEMICOLON","e","number","PLUS",
"MINUS","TIMES","SLASH","EQU", "NEQ","LES","LEQ","GTR","GEQ","LPAREN","RPAREN","PERIOD","BECOMES",
"BEGIN","END","IF","THEN","DO","WHILE","CALL","ODD","RETURN","AND","OR","NOT"};//增加终结符RETURN     增加and，not，or
/*Nonterminal*/

const char *Nonterminal[NonterminalNum]={"B","S","C","V","W","E","F","M","N","X"};
/*parser*/

const char ParserB1[Max_Parser_Len][MAX_ID_LEN]={"B","S","\0","\0","\0"};

const char ParserB2[Max_Parser_Len][MAX_ID_LEN]={"e","\0","\0","\0","\0"};

const char ParserB3[Max_Parser_Len][MAX_ID_LEN]={"ST","\0","\0","\0","\0"};

const char ParserS1[Max_Parser_Len][MAX_ID_LEN]={"C","\0","\0","\0","\0"};

const char ParserS2[Max_Parser_Len][MAX_ID_LEN]={"M","\0","\0","\0","\0"};

const char ParserS3[Max_Parser_Len][MAX_ID_LEN]={"N","\0","\0","\0","\0"};

const char ParserC[Max_Parser_Len][MAX_ID_LEN]={"SEMICOLON","V","CONST","\0","\0"};

const char ParserV[Max_Parser_Len][MAX_ID_LEN]={"E","NU","EQU","ident","\0"};

const char ParserE1[Max_Parser_Len][MAX_ID_LEN]={"V","COMMA","\0","\0","\0"};

const char ParserE2[Max_Parser_Len][MAX_ID_LEN]={"e","\0","\0","\0","\0"};

const char ParserM[Max_Parser_Len][MAX_ID_LEN]={"SEMICOLON","W","VAR","\0","\0"};

const char ParserW[Max_Parser_Len][MAX_ID_LEN]={"F","G","ident","\0","\0"};

const char ParserF1[Max_Parser_Len][MAX_ID_LEN]={"W","COMMA","\0","\0","\0"};

const char ParserF2[Max_Parser_Len][MAX_ID_LEN]={"e","\0","\0","\0","\0"};

const char ParserG1[Max_Parser_Len][MAX_ID_LEN]={"G","RSBRACKET","IDNU","LSBRACKET","\0"};

const char ParserG2[Max_Parser_Len][MAX_ID_LEN]={"e","\0","\0","\0","\0"};

const char ParserN[Max_Parser_Len][MAX_ID_LEN]={"X","SEMICOLON","ident","PROCEDURE","\0"};

const char ParserX[Max_Parser_Len][MAX_ID_LEN]={"SEMICOLON","B","\0","\0","\0"};

const char ParserST1[Max_Parser_Len][MAX_ID_LEN]={"EX","BECOMES","IA","\0","\0"};

const char ParserST2[Max_Parser_Len][MAX_ID_LEN]={"ident","CALL","\0","\0","\0"};

const char ParserST3[Max_Parser_Len][MAX_ID_LEN]={"END","STQ","BEGIN","\0","\0"};

/*
ST → IF CO THEN ST EL
EL → ES|EI|e

ES → ELSE THEN ST

EI → ELIF CO THEN ST EL
*/



const char ParserST4[Max_Parser_Len][MAX_ID_LEN]={"EL","ST","THEN","CO","IF","\0"};
const char ParserEL1[Max_Parser_Len][MAX_ID_LEN]={"ESI","\0","\0","\0","\0"};
const char ParserEL2[Max_Parser_Len][MAX_ID_LEN]={"e","\0","\0","\0","\0"};
const char ParserESI1[Max_Parser_Len][MAX_ID_LEN]={"ST","THEN","ELSE","\0","\0"};
const char ParserESI2[Max_Parser_Len][MAX_ID_LEN]={"EL","ST","THEN","CO","ELIF","\0"};



const char ParserST5[Max_Parser_Len][MAX_ID_LEN]={"ST","DO","CO","WHILE","\0"};

const char ParserST6[Max_Parser_Len][MAX_ID_LEN]={"CO","WHILE","ST","DO","\0"};

const char ParserST7[Max_Parser_Len][MAX_ID_LEN]={"IDNU","RETURN","\0"};

const char ParserST8[Max_Parser_Len][MAX_ID_LEN]={"IDNU","PRINT","\0"};

const char ParserSTQ1[Max_Parser_Len][MAX_ID_LEN]={"STQ","SEMICOLON","ST","\0","\0"};

const char ParserSTQ2[Max_Parser_Len][MAX_ID_LEN]={"e","\0","\0","\0","\0"};

const char ParserCO1[Max_Parser_Len][MAX_ID_LEN]={"COZ","EX","ODD","\0","\0"};

const char ParserCO2[Max_Parser_Len][MAX_ID_LEN]={"COZ","EX","R","EX","\0"};


const char ParserCO3[Max_Parser_Len][MAX_ID_LEN]={"COZ","CO","NOT","\0","\0"};

const char ParserCOZ1[Max_Parser_Len][MAX_ID_LEN]={"COZ","CO","L","\0","\0"};
const char ParserCOZ2[Max_Parser_Len][MAX_ID_LEN]={"e","\0","\0","\0","\0"};

const char ParserL1[Max_Parser_Len][MAX_ID_LEN]={"AND","\0","\0","\0","\0"};

const char ParserL2[Max_Parser_Len][MAX_ID_LEN]={"OR","\0","\0","\0","\0"};




const char ParserR1[Max_Parser_Len][MAX_ID_LEN]={"EQU","\0","\0","\0","\0"};

const char ParserR2[Max_Parser_Len][MAX_ID_LEN]={"NEQ","\0","\0","\0","\0"};

const char ParserR3[Max_Parser_Len][MAX_ID_LEN]={"LES","\0","\0","\0","\0"};

const char ParserR4[Max_Parser_Len][MAX_ID_LEN]={"LEQ","\0","\0","\0","\0"};

const char ParserR5[Max_Parser_Len][MAX_ID_LEN]={"GTR","\0","\0","\0","\0"};

const char ParserR6[Max_Parser_Len][MAX_ID_LEN]={"GEQ","\0","\0","\0","\0"};

const char ParserEX[Max_Parser_Len][MAX_ID_LEN]={"H","TE","\0","\0","\0"};

const char ParserH1[Max_Parser_Len][MAX_ID_LEN]={"H","TE","I","\0","\0"};

const char ParserH2[Max_Parser_Len][MAX_ID_LEN]={"e","\0","\0","\0","\0"};

const char ParserI1[Max_Parser_Len][MAX_ID_LEN]={"PLUS","\0","\0","\0","\0"};

const char ParserI2[Max_Parser_Len][MAX_ID_LEN]={"MINUS","\0","\0","\0","\0"};

const char ParserTE[Max_Parser_Len][MAX_ID_LEN]={"J","FA","\0","\0","\0"};

const char ParserJ1[Max_Parser_Len][MAX_ID_LEN]={"J","FA","K","\0","\0"};

const char ParserJ2[Max_Parser_Len][MAX_ID_LEN]={"e","\0","\0","\0","\0"};

const char ParserK1[Max_Parser_Len][MAX_ID_LEN]={"TIMES","\0","\0","\0","\0"};

const char ParserK2[Max_Parser_Len][MAX_ID_LEN]={"SLASH","\0","\0","\0","\0"};

const char ParserFA1[Max_Parser_Len][MAX_ID_LEN]={"IA","\0","\0","\0"};

const char ParserFA2[Max_Parser_Len][MAX_ID_LEN]={"number","\0","\0","\0","\0"};

const char ParserFA3[Max_Parser_Len][MAX_ID_LEN]={"EX","MINUS","\0","\0"};

const char ParserFA4[Max_Parser_Len][MAX_ID_LEN]={"RPAREN","EX","LPAREN","\0","\0"};

const char ParserIA[Max_Parser_Len][MAX_ID_LEN]={"A","ident","\0","\0","\0"};

const char ParserA1[Max_Parser_Len][MAX_ID_LEN]={"A","RSBRACKET","IDNU","LSBRACKET","\0"};

const char ParserA2[Max_Parser_Len][MAX_ID_LEN]={"e","\0","\0","\0","\0"};

const char ParserNU1[Max_Parser_Len][MAX_ID_LEN]={"number","\0","\0","\0","\0"};

const char ParserNU2[Max_Parser_Len][MAX_ID_LEN]={"number","MINUS","\0","\0","\0"};

const char ParserIDNU1[Max_Parser_Len][MAX_ID_LEN]={"IA","\0","\0","\0","\0"};

const char ParserIDNU2[Max_Parser_Len][MAX_ID_LEN]={"NU","\0","\0","\0","\0"};
/*

B → SB							

B → ST							//statement

B → ε							2

S → C 							3

S → M 							4

S → N							5

C → const V SEMICOLON 			//const	

V → ident EQU NU E				7

E → COMMA V 					8

E → ε							9

M → var W SEMICOLON				//var

W → ident G F					11

F → COMMA W 					12

F → ε							13

G → [IDNU] G | e					//for the process of array

N → procedure ident SEMICOLON X	//procedure

X → B SEMICOLON		15

ST → IA BECOMES EX				//statement, IA represent identifier or array element

ST → CALL ident

ST → BEGIN STQ END

ST → IF CO THEN ST EL

ST → WHILE CO DO ST

ST → DO ST WHILE CO             //增加dowhile语句

ST → RETURN IDNU               //增加return语句

ST → PRINT id

IDNU → IA|NU

STQ → ST SEMICOLON STQ			//statement seq

STQ → e


ST → IF CO THEN ST EL

EL → ES|EI|e

ES → ELSE THEN ST

EI → ELIF CO THEN ST EL







；CO → ODD EX 					//condition

；CO → EX R EX 
//condition,加上运算后  //消除左递归很重要

CO → NOT CO COZ

CO → ODD EX COZ

CO → EX R EX COZn

				

COZ → L CO COZ/e

L → AND|OR





R → EQU|NEQ|LES|LEQ|GTR|GEQ		//relop

EX → TE H						//expression

H → I TE H |ε

I → PLUS | MINUS

TE → FA J						//term

J → K FA J |ε

K → *|/

FA → IA| number | - EX |(EX)			//factor

IA → ident A

A → [IDNU] A|e					//process array

NU → -number|number				//number including negative
*/

char CodeBuffer[Max_Ins_len]={"\0"};	//buffer for code
long Offset=0;
/*operations for token table*/

void table_append(PL0Lex * lex, int kind,int dimenssion,int Enum[3]);
/*functions for syntax analysis*/

void statement(PL0Lex * lex); //analysis the statement

void condition(PL0Lex * lex); //analysis the condition statement

void expression(PL0Lex * lex); //analysis the expression

void term(PL0Lex * lex); //analysis the term

void factor(PL0Lex * lex); //analysis the factor

void program_block(PL0Lex * lex); //analysis the program block

void GenASM();

void Shift(Stack *S , char *c);
#endif //pl0_tax.h
