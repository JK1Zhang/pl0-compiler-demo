#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include "../common/common.h"
#include "pl0_lex.h"
#define MaxFileLen 99999

const char * TOKEN_RESERVED_WORDS[NRW] = {"var", "const", "procedure", "begin", "end", "if", "then", "do", "while", "call", "odd","else","elif","return","print"};
const char * TOKEN_SYMBOLS[NSYM+3] = { "+", "-", "*", "/", "=", "!=", "<", "<=", ">", ">=", "(", ")", ",", ";", ".", ":=", "[", "]","&&","||","!" };
const char TOKEN_DELIMITER[23] = {"\t \n\r,.;+-()*&^<>:!=/[]|"};
const char TOKEN_Symbol[20]={",.;()*^<>:!=+-/[]"};
PL0Lex * PL0Lex_create(PL0Compiler * parent)
{
	PL0Lex * lex = (PL0Lex *) calloc(1, sizeof(PL0Lex));
	lex->compiler = parent;
	lex->position=0;
	lex->PositionFlag=0;
	lex->line=1;
	lex->begin=0; lex->end=0;
	long FileLen;
	fseek(fin,0,SEEK_END);
	FileLen=ftell(fin);
	rewind(fin);
	fread(lex->FileContent,sizeof(char),FileLen,fin);
	return lex;
}

void LexInit(PL0Lex *lex){							//init the lex
	lex->position=0;
	lex->PositionFlag=0;
	lex->line=0;
}

void PL0Lex_get_token_valid(Stack *S, PL0Lex *lex){			//get token until we get a valid one
	if(lex->FileContent[lex->position]=='\0'){
		printf("We've been at the end of the file\n");
		return;
	}
	PL0Lex_get_token(lex);
	while(lex->last_token_type==TOKEN_NULL&&lex->FileContent[lex->position]!='\0')
		PL0Lex_get_token(lex);
		if(lex->last_token_type==TOKEN_NULL){}
		if (lex->last_token_type == TOKEN_IDENTIFIER)
		{
			printf("Identifier: %12s\n", lex->last_id);
		}
		else if (lex->last_token_type == TOKEN_NUMBER)
		{
			printf("Number: %12d\n", lex->last_num);
		}
		else if (lex->last_token_type > TOKEN_RESWORDS)
		{
			printf("Reserved word: %12s\n", TOKEN_RESERVED_WORDS[lex->last_token_type - TOKEN_RESWORDS - 1]);
		}
		else if(lex->last_token_type>TOKEN_SYMBOL&&lex->last_token_type<TOKEN_RESWORDS)
		{
			printf("Symbol: %12s\n", TOKEN_SYMBOLS[lex->last_token_type - TOKEN_SYMBOL - 1]);
		}
		else{}
	if(lex->last_token_type!=TOKEN_NULL){
		char TokenStr[MAX_ID_LEN];
		Transfer(lex,TokenStr);
		Shift(S,TokenStr);
	}
}
void ShiftForward(PL0Lex *lex, int Length){			//move forward
		lex->position+=Length;
		lex->begin=lex->PositionFlag;
		lex->end=lex->begin+Length-1;
		lex->PositionFlag=lex->end+1;
	}

PL0TokenType MatchToken(char *ch){
	int i;
	for(i=0;i<NRW;i++)
		if(strcmp(ch,TOKEN_RESERVED_WORDS[i])==0)
			break;
	if(i<NRW){
		switch(i){
			case 0: return TOKEN_VAR;
			case 1: return TOKEN_CONST;
			case 2: return TOKEN_PROCEDURE;
			case 3: return TOKEN_BEGIN;
			case 4: return TOKEN_END;
			case 5: return TOKEN_IF;
			case 6: return TOKEN_THEN;
			case 7: return TOKEN_DO;
			case 8: return TOKEN_WHILE;
			case 9: return TOKEN_CALL;
			case 10:return TOKEN_ODD;
			case 11:return TOKEN_ELSE;
			case 12:return TOKEN_ELIF;
			case 13:return TOKEN_RETURN;
			case 14:return TOKEN_PRINT;
		}
	}
	for(i=0;i<NSYM+3;i++)
		if(strcmp(ch,TOKEN_SYMBOLS[i])==0)
			break;
	if(i<NSYM+3){
		switch(i){
			case 0: return TOKEN_PLUS;	/* + */
			case 1: return TOKEN_MINUS;	/* - */
			case 2: return TOKEN_TIMES;	/* * */
			case 3: return TOKEN_SLASH;	/* / */
			case 4: return TOKEN_EQU;  	/* = */
			case 5: return TOKEN_NEQ;  	/* != */
			case 6: return TOKEN_LES;  	/* < */
			case 7: return TOKEN_LEQ;  	/* <= */
			case 8: return TOKEN_GTR;  	/* > */
			case 9: return TOKEN_GEQ;  	/* >= */
			case 10: return TOKEN_LPAREN;	/* ( */
			case 11: return TOKEN_RPAREN;	/* ) */
			case 12: return TOKEN_COMMA;	/* , */
			case 13: return TOKEN_SEMICOLON;/* ; */
			case 14: return TOKEN_PERIOD;	/* . */
			case 15: return TOKEN_BECOMES;	/* := */

            
            case 16: return TOKEN_AND;	/* & */
			case 17: return TOKEN_OR;	/* | */
            case 18: return TOKEN_NOT;	/* ! */
		}
	}
	if(ch[0]=='-'){
		if(ch[1]=='\0') return TOKEN_MINUS;
		else{
			for(i=1;ch[i]!='\0';i++)
				if(ch[i]<'0'||ch[i]>'9')
					break;
			if(ch[i]=='\0') return TOKEN_NUMBER;
			return TOKEN_IDENTIFIER;
		}
	}
	for(i=0;ch[i]!='\0';i++)
		if(ch[i]<'0'||ch[i]>'9')
			break;
	if(ch[i]=='\0') return TOKEN_NUMBER;
	if(sizeof(ch)==1&&ch[0]=='_'){
		("Wrong identifier format: identifier cannot start with a number.");
		return TOKEN_NULL;
	}
	else return TOKEN_IDENTIFIER;

}
BOOL MatchDelimiter(char ch){
	int i;
	for(i=0;TOKEN_DELIMITER[i]!='\0';i++ )
		if(ch==TOKEN_DELIMITER[i])
			break;
	if(TOKEN_DELIMITER[i]=='\0') return FALSE;
	return TRUE;
}

int StrtoNum(char *ch){
	int i,sum=0;
	if(ch[0]!='-'){
		sum=ch[0]-'0';
		for(i=1;ch[i]!='\0';i++)
			sum=sum*10+(ch[i]-'0');
	}
	else{
		sum=ch[1]-'0';
		for(i=2;ch[i]!='\0';i++)
			sum=sum*10+(ch[i]-'0');
		sum=-sum;
	}
	return sum;
}

void NumtoStr(int num, char *str){

}
BOOL PL0Lex_destroy(PL0Lex * lex){
    free(lex);
    return TRUE;
}

BOOL PL0Lex_get_token(PL0Lex * lex)
{
	int i,j,k,EndofAnnotion;
	int WordLen,Begin,End;
	char temp[MAX_ID_LEN];
	PL0TokenType t;
	BOOL MatchDFlag;
	BOOL Special;
	i=lex->position;
	while(lex->FileContent[i]!='\0'){
		if(isalpha(lex->FileContent[i])||lex->FileContent[i]=='_'){	//alpha or '_' for start, identifier or reaserve wods
			WordLen=1;
			Begin=i;
			i++;
			while(!MatchDelimiter(lex->FileContent[i])){			//forward until meet delimiter
				i++;
				WordLen++;
			}
			strncpy(lex->last_id,&lex->FileContent[Begin],WordLen);
			lex->last_id[WordLen]='\0';
			lex->last_token_type= MatchToken(lex->last_id);
			ShiftForward(lex,WordLen);
			return TRUE;
		}
		else if(isalnum (lex->FileContent[i])){						//number 
			int FlagForErrorId=0;									//Id start with number;
			char Temp[MAX_NUM_LEN];
			WordLen=1;
			Begin=i;
			i++;
			while(!MatchDelimiter(lex->FileContent[i])){
				if(isalpha(lex->FileContent[i]))
					FlagForErrorId=1;
				i++;
				WordLen++;
			}
			if(FlagForErrorId)	{
				lex->last_token_type=TOKEN_NULL;
				printf("Wrong identifier format: identifier cannot start with a number.\n");
			}
			else if(WordLen>MAX_NUM_LEN){
				lex->last_token_type=TOKEN_NULL;
				printf("Too long identifier or number.\n");
			}
			else{
				strncpy(Temp,&lex->FileContent[Begin],WordLen);
				Temp[WordLen]='\0';
				lex->last_num=StrtoNum(Temp);
				lex->last_token_type=TOKEN_NUMBER;
			}
			ShiftForward(lex,WordLen);
			return TRUE;
		}
		else if(MatchDelimiter(lex->FileContent[i])){							//Delimeter including symbols
			int SymbolLen;
			if(lex->FileContent[i]==' '||lex->FileContent[i]=='\t'){			//white space
				lex->position++;
				lex->PositionFlag++;
				lex->last_token_type=TOKEN_NULL;
				return TRUE;
			}
			else if(lex->FileContent[i]=='\n'){									//new line
				lex->position++;
				lex->PositionFlag=0;
				lex->line++;
				lex->last_token_type=TOKEN_NULL;
				return TRUE;
			}
			else if(lex->FileContent[i]=='+'){									//+
				SymbolLen=1;
				ShiftForward(lex,SymbolLen);
				lex->last_token_type=TOKEN_PLUS;
				return  TRUE;
			}
			else if(lex->FileContent[i]=='-'){									//-
				SymbolLen=1;
				ShiftForward(lex,SymbolLen);
				lex->last_token_type=TOKEN_MINUS;
				return  TRUE;
			}
			else if(lex->FileContent[i]=='*'){									//*
					SymbolLen=1;
					ShiftForward(lex,SymbolLen);
					lex->last_token_type=TOKEN_TIMES;
					return  TRUE;
			}
			else if(lex->FileContent[i]=='/'){									// '/'
				int CommentsLength=0;
				int CommentsLineLength=lex->PositionFlag+1;
				i++;
				if(lex->FileContent[i]=='/'){									//comments '//'
					i++;
					while(lex->FileContent[i]!='\n'){
						CommentsLength++;
						i++;
					}
					ShiftForward(lex,CommentsLength+2);
					lex->last_token_type=TOKEN_NULL;
					return TRUE;
				}
				else if(lex->FileContent[i]=='*'){								//comments '/* */'
					i++;
					CommentsLineLength+=2;
					while(lex->FileContent[i]!='\0'){
						if(lex->FileContent[i]=='*'){
							i++;
							if(lex->FileContent[i]=='/'){
								ShiftForward(lex,CommentsLength+4);
								lex->PositionFlag=CommentsLineLength+1;
								lex->last_token_type=TOKEN_NULL;
								return TRUE;
							}
						}
						else{
							if(lex->FileContent[i]=='\n'){
								lex->PositionFlag=0;
								CommentsLineLength=0;
								lex->line++;
								CommentsLineLength=0;
							}
							CommentsLength++;
							i++;
						}
						CommentsLineLength++;
					}
					if(lex->FileContent[i]=='\0') {
						printf("\n★  Missing a end for comment: has reached the EOF.\n");
						return FALSE;
					}
				}
				else{
					SymbolLen=1;
					ShiftForward(lex,SymbolLen);
					lex->last_token_type=TOKEN_SLASH;
					return TRUE;
				}								

			}
			else if(lex->FileContent[i]=='='){									//'='
				SymbolLen=1;
				ShiftForward(lex,SymbolLen);
				lex->last_token_type=TOKEN_EQU;
				return TRUE;
			}
			else if(lex->FileContent[i]=='<'){									//'<' or '<='
				i++;
				if(lex->FileContent[i]=='='){
					SymbolLen=2;
					ShiftForward(lex,SymbolLen);
					lex->last_token_type=TOKEN_LEQ;
					return TRUE;
				}
				else{
					SymbolLen=1;
					ShiftForward(lex,SymbolLen);
					lex->last_token_type=TOKEN_LES;
					return TRUE;
				}
			}
			else if(lex->FileContent[i]=='!'){									//'!='
				i++;
				if(lex->FileContent[i]=='='){
					SymbolLen=2;
					ShiftForward(lex,SymbolLen);
					lex->last_token_type=TOKEN_NEQ;
					return TRUE;
				}
				else{
					SymbolLen=1;
					ShiftForward(lex,SymbolLen);
					lex->last_token_type=TOKEN_NOT;
					//printf("Invalid Symbol\n");
					return TRUE;
				}
			}
			else if(lex->FileContent[i]=='>'){									//'>='
				i++;
				if(lex->FileContent[i]=='='){
					SymbolLen=2;
					ShiftForward(lex,SymbolLen);
					lex->last_token_type=TOKEN_GEQ;
					return TRUE;
				}
				else{
					SymbolLen=1;
					ShiftForward(lex,SymbolLen);
					lex->last_token_type=TOKEN_GTR;
					return TRUE;
				}
			}


          		  else if(lex->FileContent[i]=='&'){									//'&'
				i++;
				if(lex->FileContent[i]=='&'){
					SymbolLen=2;
					ShiftForward(lex,SymbolLen);
					lex->last_token_type=TOKEN_AND;
					return TRUE;
				}
			}
           		 else if(lex->FileContent[i]=='|'){				//'|'
				i++;
				if(lex->FileContent[i]=='|'){
					SymbolLen=2;
					ShiftForward(lex,SymbolLen);
					lex->last_token_type=TOKEN_OR;
					return TRUE;
				}
			}


			else if(lex->FileContent[i]=='('){
				SymbolLen=1;
				ShiftForward(lex,SymbolLen);
				lex->last_token_type=TOKEN_LPAREN;
				return TRUE;
			}
			else if(lex->FileContent[i]==')'){
				SymbolLen=1;
				ShiftForward(lex,SymbolLen);
				lex->last_token_type=TOKEN_RPAREN;
				return TRUE;
			}
			else if(lex->FileContent[i]==','){
				SymbolLen=1;
				ShiftForward(lex,SymbolLen);
				lex->last_token_type=TOKEN_COMMA;
				return TRUE;
			}
			else if(lex->FileContent[i]==';'){
				SymbolLen=1;
				ShiftForward(lex,SymbolLen);
				lex->last_token_type=TOKEN_SEMICOLON;
				return TRUE;
			}
			else if(lex->FileContent[i]=='('){
				SymbolLen=1;
				ShiftForward(lex,SymbolLen);
				lex->last_token_type=TOKEN_LPAREN;
				return TRUE;
			}
			else if(lex->FileContent[i]=='.'){
				SymbolLen=1;
				ShiftForward(lex,SymbolLen);
				lex->last_token_type=TOKEN_PERIOD;
				return TRUE;
			}
			else if(lex->FileContent[i]==':'){									
				i++;
				if(lex->FileContent[i]=='='){
					SymbolLen=2;
					ShiftForward(lex,SymbolLen);
					lex->last_token_type=TOKEN_BECOMES;
					return TRUE;
				}
				else{
					SymbolLen=1;
					ShiftForward(lex,SymbolLen);
					lex->last_token_type=TOKEN_NULL;
					printf("Expect an '=' after ':'\n");
					return TRUE;
				}
			}
			else if(lex->FileContent[i]=='['){
				SymbolLen=1;
				ShiftForward(lex,SymbolLen);
				lex->last_token_type=TOKEN_LSBRACKETS;
				return TRUE;
			}
			else if(lex->FileContent[i]==']'){
				SymbolLen=1;
				ShiftForward(lex,SymbolLen);
				lex->last_token_type=TOKEN_RSBRACKETS;
				return TRUE;
			}
			else{
				ShiftForward(lex,1);
				lex->last_token_type=TOKEN_NULL;
				printf("Invalid character\n");
				return TRUE;
			}
			
		}
		else{
			ShiftForward(lex,1);
			lex->last_token_type=TOKEN_NULL;
			printf("Invalid character\n");
			printf("\n\n\n%c\n\n\n\n\n\n",lex->FileContent[i]);
			return TRUE;
		}
	}
	return FALSE;
}
