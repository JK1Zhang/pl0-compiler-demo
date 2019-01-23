#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../common/common.h"
#include "../lex/pl0_lex.h"
#include "pl0_tax.h"
#include "stack.h"
//Stack *S;
/*operations for token table*/
void table_append(PL0Lex * lex, int kind,int dimension,int Enum[3]) {
	strcpy(token_table[table_index].name, lex->last_id);
	token_table[table_index].kind = kind;
	switch (kind) {
		case ID_CONSTANT:
			if (lex->last_num > MAXADDRESS) {
				printf("\n★  the number is too great!\n");
				lex->last_num = 0;
			}
			token_table[table_index].value = lex->last_num;
			token_table[table_index].size=4;
			token_table[table_index].dimenssion=0;
			if(table_index==0) token_table[table_index].address=8;
			else token_table[table_index].address=token_table[table_index-1].address+Width;
			break;
		case ID_VARIABLE:
			token_table[table_index].local = local_ornot;
			token_table[table_index].level = lex->last_level;
			int size=1,i;
			if(dimension>0){
				for(i=1;i<=dimension;i++){
					size*=Enum[i];
					token_table[table_index].Enum[i]=Enum[i];
				}
			}
			size=size*Width;
			token_table[table_index].size=size;
			token_table[table_index].dimenssion=dimension;
			if(table_index==0) token_table[table_index].address=8;
			else{
				for(i=table_index-1;i>=0;i--){//we should ignore procedure id because it dose not occupy memory in fact
					if(token_table[i].kind!=ID_PROCEDURE)
						break;
				}
				if(i>0||(i==0&&token_table[i].kind!=ID_PROCEDURE))
			 		token_table[table_index].address=token_table[i].address+token_table[i].size;
				else
					token_table[table_index].address=8;
			}
			break;
		case ID_PROCEDURE:
			token_table[table_index].level = lex->last_level;
			token_table[table_index].procedureaddress=code_index;
			break;
	}
	table_index += 1;
} //table_append
/*output operations*/
BOOL IsTerminal(char *c){
	int i;
	for(i=0;i<TerminalNum+3;i++)
		if(strcmp(c,Terminal[i])==0)
			return TRUE;
	return FALSE;
}
BOOL First(char *Stop, char *str){
	int i;
	if(strcmp(Stop,"B")==0){
		for(i=0;strcmp(BF[i],"\0")!=0;i++)
			if(strcmp(BF[i],str)==0)
				return TRUE;
		return FALSE;
	}
	else if(strcmp(Stop,"S")==0){
		for(i=0;strcmp(SF[i],"\0")!=0;i++)
			if(strcmp(SF[i],str)==0)
				return TRUE;
		return FALSE;
	}
	else if(strcmp(Stop,"C")==0){
		for(i=0;strcmp(CF[i],"\0")!=0;i++)
			if(strcmp(CF[i],str)==0)
				return TRUE;
		return FALSE;
	}
	else if(strcmp(Stop,"V")==0){
		for(i=0;strcmp(VF[i],"\0")!=0;i++)
			if(strcmp(VF[i],str)==0)
				return TRUE;
		return FALSE;
	}
	else if(strcmp(Stop,"W")==0){
		for(i=0;strcmp(WF[i],"\0")!=0;i++)
			if(strcmp(WF[i],str)==0)
				return TRUE;
		return FALSE;
	}
	else if(strcmp(Stop,"E")==0){
		for(i=0;strcmp(EF[i],"\0")!=0;i++)
			if(strcmp(EF[i],str)==0)
				return TRUE;
		return FALSE;
	}
	else if(strcmp(Stop,"F")==0){
		for(i=0;strcmp(FF[i],"\0")!=0;i++)
			if(strcmp(FF[i],str)==0)
				return TRUE;
		return FALSE;
	}
	else if(strcmp(Stop,"G")==0){
		for(i=0;strcmp(GF[i],"\0")!=0;i++)
			if(strcmp(GF[i],str)==0)
				return TRUE;
		return FALSE;
	}
	else if(strcmp(Stop,"M")==0){
		if(strcmp(str,"VAR")==0)
			return TRUE;
		else
			return FALSE;
	}
	else if(strcmp(Stop,"N")==0){
		for(i=0;strcmp(NF[i],"\0")!=0;i++)
			if(strcmp(NF[i],str)==0)
				return TRUE;
		return FALSE;
	}
	else if(strcmp(Stop,"X")==0){
		for(i=0;strcmp(XF[i],"\0")!=0;i++)
			if(strcmp(XF[i],str)==0)
				return TRUE;
		return FALSE;
	}
	else if(strcmp(Stop,"ST")==0){
		for(i=0;strcmp(STF[i],"\0")!=0;i++)
			if(strcmp(STF[i],str)==0)
				return TRUE;
		return FALSE;
	}
	else if(strcmp(Stop,"EL")==0){
		for(i=0;strcmp(ELF[i],"\0")!=0;i++)
			if(strcmp(ELF[i],str)==0)
				return TRUE;
		return FALSE;
	}
	else if(strcmp(Stop,"ESI")==0){
		for(i=0;strcmp(ESIF[i],"\0")!=0;i++)
			if(strcmp(ESIF[i],str)==0)
				return TRUE;
		return FALSE;
	}
	else if(strcmp(Stop,"IDNU")==0){
		for(i=0;strcmp(IDNUF[i],"\0")!=0;i++)
			if(strcmp(IDNUF[i],str)==0)
				return TRUE;
		return FALSE;
	}
	else if(strcmp(Stop,"STQ")==0){
		for(i=0;strcmp(STQF[i],"\0")!=0;i++)
			if(strcmp(STQF[i],str)==0)
				return TRUE;
		return FALSE;
	}
	else if(strcmp(Stop,"CO")==0){
		for(i=0;strcmp(COF[i],"\0")!=0;i++)
			if(strcmp(COF[i],str)==0)
				return TRUE;
		return FALSE;
	}
	else if(strcmp(Stop,"COZ")==0){
		for(i=0;strcmp(COZF[i],"\0")!=0;i++)
			if(strcmp(COZF[i],str)==0)
				return TRUE;
		return FALSE;
	}
	else if(strcmp(Stop,"L")==0){
		for(i=0;strcmp(LF[i],"\0")!=0;i++)
			if(strcmp(LF[i],str)==0)
				return TRUE;
		return FALSE;
	}
	else if(strcmp(Stop,"R")==0){
		for(i=0;strcmp(RF[i],"\0")!=0;i++)
			if(strcmp(RF[i],str)==0)
				return TRUE;
		return FALSE;
	}
	else if(strcmp(Stop,"EX")==0){
		for(i=0;strcmp(EXF[i],"\0")!=0;i++)
			if(strcmp(EXF[i],str)==0)
				return TRUE;
		return FALSE;
	}
	else if(strcmp(Stop,"H")==0){
		for(i=0;strcmp(HF[i],"\0")!=0;i++)
			if(strcmp(HF[i],str)==0)
				return TRUE;
		return FALSE;
	}
	else if(strcmp(Stop,"I")==0){
		for(i=0;strcmp(IF[i],"\0")!=0;i++)
			if(strcmp(IF[i],str)==0)
				return TRUE;
		return FALSE;
	}
	else if(strcmp(Stop,"TE")==0){
		for(i=0;strcmp(TEF[i],"\0")!=0;i++)
			if(strcmp(TEF[i],str)==0)
				return TRUE;
		return FALSE;
	}
	else if(strcmp(Stop,"J")==0){
		for(i=0;strcmp(JF[i],"\0")!=0;i++)
			if(strcmp(JF[i],str)==0)
				return TRUE;
		return FALSE;
	}
	else if(strcmp(Stop,"K")==0){
		for(i=0;strcmp(KF[i],"\0")!=0;i++)
			if(strcmp(KF[i],str)==0)
				return TRUE;
		return FALSE;
	}
	else if(strcmp(Stop,"FA")==0){
		for(i=0;strcmp(FAF[i],"\0")!=0;i++)
			if(strcmp(FAF[i],str)==0)
				return TRUE;
		return FALSE;
	}
	else if(strcmp(Stop,"IA")==0){
		for(i=0;strcmp(IAF[i],"\0")!=0;i++)
			if(strcmp(IAF[i],str)==0)
				return TRUE;
		return FALSE;
	}
	else if(strcmp(Stop,"A")==0){
		for(i=0;strcmp(AF[i],"\0")!=0;i++)
			if(strcmp(AF[i],str)==0)
				return TRUE;
		return FALSE;
	}
	else if(strcmp(Stop,"NU")==0){
		for(i=0;strcmp(NUF[i],"\0")!=0;i++)
			if(strcmp(NUF[i],str)==0)
				return TRUE;
		return FALSE;
	}
	else{
		printf("\n★  The Nonterminal is wrong\n");
		return FALSE;
	}
}
BOOL Synch(char *Stop, char *str){			//see if str is in the synch set of Stop, it's for error recovery
	int i;
	if(strcmp(Stop,"B")==0){
		for(i=0;strcmp(BS[i],"\0")!=0;i++)
			if(strcmp(BS[i],str)==0)
				return TRUE;
		return FALSE;
	}
	else if(strcmp(Stop,"S")==0){
		for(i=0;strcmp(SS[i],"\0")!=0;i++)
			if(strcmp(SS[i],str)==0)
				return TRUE;
		return FALSE;
	}
	else if(strcmp(Stop,"C")==0){
		for(i=0;strcmp(CS[i],"\0")!=0;i++)
			if(strcmp(CS[i],str)==0)
				return TRUE;
		return FALSE;
	}
	else if(strcmp(Stop,"V")==0){
		for(i=0;strcmp(VS[i],"\0")!=0;i++)
			if(strcmp(VS[i],str)==0)
				return TRUE;
		return FALSE;
	}
	else if(strcmp(Stop,"W")==0){
		for(i=0;strcmp(WS[i],"\0")!=0;i++)
			if(strcmp(WS[i],str)==0)
				return TRUE;
		return FALSE;
	}
	else if(strcmp(Stop,"E")==0){
		for(i=0;strcmp(ES[i],"\0")!=0;i++)
			if(strcmp(ES[i],str)==0)
				return TRUE;
		return FALSE;
	}
	else if(strcmp(Stop,"F")==0){
		for(i=0;strcmp(FS[i],"\0")!=0;i++)
			if(strcmp(FS[i],str)==0)
				return TRUE;
		return FALSE;
	}
	else if(strcmp(Stop,"G")==0){
		for(i=0;strcmp(GS[i],"\0")!=0;i++)
			if(strcmp(GS[i],str)==0)
				return TRUE;
		return FALSE;
	}
	else if(strcmp(Stop,"M")==0){
		if(strcmp(str,"var")==0)
			return TRUE;
		else
			return FALSE;
	}
	else if(strcmp(Stop,"N")==0){
		for(i=0;strcmp(NS[i],"\0")!=0;i++)
			if(strcmp(NS[i],str)==0)
				return TRUE;
		return FALSE;
	}
	else if(strcmp(Stop,"X")==0){
		for(i=0;strcmp(XS[i],"\0")!=0;i++)
			if(strcmp(XS[i],str)==0)
				return TRUE;
		return FALSE;
	}
	else if(strcmp(Stop,"ST")==0){
		for(i=0;strcmp(STS[i],"\0")!=0;i++)
			if(strcmp(STS[i],str)==0)
				return TRUE;
		return FALSE;
	}
	else if(strcmp(Stop,"EL")==0){
		for(i=0;strcmp(ELS[i],"\0")!=0;i++)
			if(strcmp(ELS[i],str)==0)
				return TRUE;
		return FALSE;
	}
	else if(strcmp(Stop,"ESI")==0){
		for(i=0;strcmp(ESIS[i],"\0")!=0;i++)
			if(strcmp(ESIS[i],str)==0)
				return TRUE;
		return FALSE;
	}
	else if(strcmp(Stop,"IDNU")==0){
		for(i=0;strcmp(IDNUS[i],"\0")!=0;i++)
			if(strcmp(IDNUS[i],str)==0)
				return TRUE;
		return FALSE;
	}
	else if(strcmp(Stop,"STQ")==0){
		for(i=0;strcmp(STQS[i],"\0")!=0;i++)
			if(strcmp(STQS[i],str)==0)
				return TRUE;
		return FALSE;
	}
	else if(strcmp(Stop,"CO")==0){
		for(i=0;strcmp(COS[i],"\0")!=0;i++)
			if(strcmp(COS[i],str)==0)
				return TRUE;
		return FALSE;
	}
	else if(strcmp(Stop,"COZ")==0){
		for(i=0;strcmp(COZS[i],"\0")!=0;i++)
			if(strcmp(COZS[i],str)==0)
				return TRUE;
		return FALSE;
	}
	else if(strcmp(Stop,"L")==0){
		for(i=0;strcmp(LS[i],"\0")!=0;i++)
			if(strcmp(LS[i],str)==0)
				return TRUE;
		return FALSE;
	}	
	else if(strcmp(Stop,"R")==0){
		for(i=0;strcmp(RS[i],"\0")!=0;i++)
			if(strcmp(RS[i],str)==0)
				return TRUE;
		return FALSE;
	}
	else if(strcmp(Stop,"EX")==0){
		for(i=0;strcmp(EXS[i],"\0")!=0;i++)
			if(strcmp(EXS[i],str)==0)
				return TRUE;
		return FALSE;
	}
	else if(strcmp(Stop,"H")==0){
		for(i=0;strcmp(HS[i],"\0")!=0;i++)
			if(strcmp(HS[i],str)==0)
				return TRUE;
		return FALSE;
	}
	else if(strcmp(Stop,"I")==0){
		for(i=0;strcmp(IS[i],"\0")!=0;i++)
			if(strcmp(IS[i],str)==0)
				return TRUE;
		return FALSE;
	}
	else if(strcmp(Stop,"TE")==0){
		for(i=0;strcmp(TES[i],"\0")!=0;i++)
			if(strcmp(TES[i],str)==0)
				return TRUE;
		return FALSE;
	}
	else if(strcmp(Stop,"J")==0){
		for(i=0;strcmp(JS[i],"\0")!=0;i++)
			if(strcmp(JS[i],str)==0)
				return TRUE;
		return FALSE;
	}
	else if(strcmp(Stop,"K")==0){
		for(i=0;strcmp(KS[i],"\0")!=0;i++)
			if(strcmp(KS[i],str)==0)
				return TRUE;
		return FALSE;
	}
	else if(strcmp(Stop,"FA")==0){
		for(i=0;strcmp(FAS[i],"\0")!=0;i++)
			if(strcmp(FAS[i],str)==0)
				return TRUE;
		return FALSE;
	}
	else if(strcmp(Stop,"IA")==0){
		for(i=0;strcmp(IAS[i],"\0")!=0;i++)
			if(strcmp(IAS[i],str)==0)
				return TRUE;
		return FALSE;
	}	
	else if(strcmp(Stop,"A")==0){
		for(i=0;strcmp(AS[i],"\0")!=0;i++)
			if(strcmp(AS[i],str)==0)
				return TRUE;
		return FALSE;
	}
	else if(strcmp(Stop,"NU")==0){
		for(i=0;strcmp(NUS[i],"\0")!=0;i++)
			if(strcmp(NUS[i],str)==0)
				return TRUE;
		return FALSE;
	}
	else{
		printf("\n★  The Nonterminal is wrong\n");
		return FALSE;
	}
}
void CopyParser( char destination[Max_Parser_Len][MAX_ID_LEN],char resource[Max_Parser_Len][MAX_ID_LEN]){
	int i=0;
	for(i=0;i<Max_Parser_Len;i++){
		strcpy(destination[i],resource[i]);
	}
}
BOOL MatchParser(char *Stop, char *c, char result[Max_Parser_Len][MAX_ID_LEN]){// serach the right parser
	if(IsTerminal(Stop)){
		printf("\n★  Expect Nonterminal\n");
		return FALSE;
	}
	if(!First(Stop,c)){
		//printf("not match\n");
		return FALSE;
	}
	if(strcmp(Stop,"B")==0){
		if(strcmp(c,"e")==0)
			CopyParser(result,ParserB2);
		else if(First("S",c))
			CopyParser(result,ParserB1);
		else if(First("ST",c))
			CopyParser(result,ParserB3);
		else
			printf("\n★  B match error\n");
	}
	else if(strcmp(Stop,"S")==0){
		if(First("C",c))
			CopyParser(result,ParserS1);
		else if(First("M",c))
			CopyParser(result,ParserS2);
		else if(First("N",c))
			CopyParser(result,ParserS3);
	}
	else if(strcmp(Stop,"C")==0){
		CopyParser(result,ParserC);
	}
	else if(strcmp(Stop,"V")==0){
		CopyParser(result,ParserV);
	}
	else if(strcmp(Stop,"E")==0){
		if(strcmp(c,"e")==0)
			CopyParser(result,ParserE2);
		else
			CopyParser(result,ParserE1);
	}
	else if(strcmp(Stop,"M")==0){
		CopyParser(result,ParserM);
	}
	else if(strcmp(Stop,"W")==0){
		CopyParser(result,ParserW);
	}
	else if(strcmp(Stop,"F")==0){
		if(strcmp(c,"e")==0)
			CopyParser(result,ParserF2);
		else
			CopyParser(result,ParserF1);
	}
	else if(strcmp(Stop,"G")==0){
		if(strcmp(c,"e")==0)
			CopyParser(result,ParserG2);
		else 
			CopyParser(result,ParserG1);
	}
	else if(strcmp(Stop,"N")==0){
		CopyParser(result,ParserN);
	}
	else if(strcmp(Stop,"X")==0){
		CopyParser(result,ParserX);
	}
	else if(strcmp(Stop,"ST")==0){
		if(strcmp(c,"ident")==0)
			CopyParser(result,ParserST1);
		else if(strcmp(c,"CALL")==0)
			CopyParser(result,ParserST2);
		else if(strcmp(c,"BEGIN")==0)
			CopyParser(result,ParserST3);
		else if(strcmp(c,"IF")==0)
			CopyParser(result,ParserST4);
		else if(strcmp(c,"WHILE")==0)
			CopyParser(result,ParserST5);
		else if(strcmp(c,"DO")==0)
			CopyParser(result,ParserST6);
		else if(strcmp(c,"RETURN")==0)
			CopyParser(result,ParserST7);
		else if(strcmp(c,"PRINT")==0)
			CopyParser(result,ParserST8);
		else
			printf("\n★  ST match error\n");
	}
	else if(strcmp(Stop,"EL")==0){
		if(First("ESI",c))
			CopyParser(result,ParserEL1);
		else if(strcmp(c,"e")==0)
			CopyParser(result,ParserEL2);
		else 
			printf("\n★  EL match error\n");
	}
	else if(strcmp(Stop,"ESI")==0){
		if(strcmp(c,"ELSE")==0)
			CopyParser(result,ParserESI1);
		else if(strcmp(c,"ELIF")==0)
			CopyParser(result,ParserESI2);
		else
			printf("\n★  ESI match error\n");
	}
	else if(strcmp(Stop,"IDNU")==0){
		if(strcmp(c,"ident")==0)
			CopyParser(result,ParserIDNU1);
		else if(strcmp(c,"number")==0||strcmp(c,"MINUS")==0)
			CopyParser(result,ParserIDNU2);
		else
			printf("\n★  IDNU match error\n");
	}
	else if(strcmp(Stop,"STQ")==0){
		if(strcmp(c,"e")==0)
			CopyParser(result,ParserSTQ2);
		else if(First("ST",c))
			CopyParser(result,ParserSTQ1);
		else
			printf("\n★  STQ match error\n");
	}
	else if(strcmp(Stop,"CO")==0){
		if(strcmp(c,"ODD")==0)
			CopyParser(result,ParserCO1);
		else if(First("EX",c))
			CopyParser(result,ParserCO2);
		else if(strcmp(c,"NOT")==0)
			CopyParser(result,ParserCO3);
		else
			printf("\n★  CO match error\n");
	}
	else if(strcmp(Stop,"COZ")==0){
		if(strcmp(c,"e")==0)
			CopyParser(result,ParserCOZ2);
		else if(First("L",c))
			CopyParser(result,ParserCOZ1);
		else
			printf("\n★  CO match error\n");
	}
	else if(strcmp(Stop,"L")==0){
		if(strcmp(c,"AND")==0)
			CopyParser(result,ParserL1);
		else if(strcmp(c,"OR")==0)
			CopyParser(result,ParserL2);
		else
			printf("\n★  CO match error\n");
	}
	else if(strcmp(Stop,"R")==0){
		if(strcmp(c,"EQU")==0)
			CopyParser(result,ParserR1);
		else if(strcmp(c,"NEQ")==0)
			CopyParser(result,ParserR2);
		else if(strcmp(c,"LES")==0)
			CopyParser(result,ParserR3);
		else if(strcmp(c,"LEQ")==0)
			CopyParser(result,ParserR4);
		else if(strcmp(c,"GTR")==0)
			CopyParser(result,ParserR5);
		else if(strcmp(c,"GEQ")==0)
			CopyParser(result,ParserR6);
		else
			printf("\n★  R match error\n");
	}
	else if(strcmp(Stop,"EX")==0){
		CopyParser(result,ParserEX);
	}
	else if(strcmp(Stop,"H")==0){
		if(strcmp(c,"e")==0)
			CopyParser(result,ParserH2);
		else if(First("I",c))
			CopyParser(result,ParserH1);
		else
			printf("\n★  H match error\n");
	}
	else if(strcmp(Stop,"I")==0){
		if(strcmp(c,"PLUS")==0)
			CopyParser(result,ParserI1);
		else if(strcmp("MINUS",c)==0)
			CopyParser(result,ParserI2);
		else
			printf("\n★  I match error\n");
	}
	else if(strcmp(Stop,"TE")==0){
		CopyParser(result,ParserTE);
	}
	else if(strcmp(Stop,"J")==0){
		if(strcmp(c,"e")==0)
			CopyParser(result,ParserJ2);
		else if(First("K",c))
			CopyParser(result,ParserJ1);
		else
			printf("\n★  J match error\n");
	}
	else if(strcmp(Stop,"K")==0){
		if(strcmp(c,"TIMES")==0)
			CopyParser(result,ParserK1);
		else if(strcmp("SLASH",c)==0)
			CopyParser(result,ParserK2);
		else
			printf("\n★  K match error\n");
	}
	else if(strcmp(Stop,"FA")==0){
		if(strcmp(c,"ident")==0)
			CopyParser(result,ParserFA1);
		else if(strcmp(c,"number")==0)
			CopyParser(result,ParserFA2);
		else if(strcmp(c,"MINUS")==0)
			CopyParser(result,ParserFA3);
		else if(strcmp(c,"LPAREN")==0)
			CopyParser(result,ParserFA4);
		else
			printf("\n★  FA match error\n");
	}
	else if(strcmp(Stop,"IA")==0){
		CopyParser(result,ParserIA);
	}
	else if(strcmp(Stop,"A")==0){
		if(strcmp(c,"LSBRACKET")==0)
			CopyParser(result,ParserA1);
		else if(strcmp("e",c)==0)
			CopyParser(result,ParserA2);
		else
			printf("\n★  K match error\n");
	}
	else if(strcmp(Stop,"NU")==0){
		if(strcmp(c,"number")==0)
			CopyParser(result,ParserNU1);
		else if(strcmp("MINUS",c)==0)
			CopyParser(result,ParserNU2);
		else
			printf("\n★  NU match error\n");
	}
	return TRUE;
}
void Transfer(PL0Lex *lex,char *result){	// Transfer token into string we need
	//char result[MAX_ID_LEN];
	if (lex->last_token_type == TOKEN_IDENTIFIER)
		strcpy(result,"ident");
	else if (lex->last_token_type == TOKEN_NUMBER){
		strcpy(result,"number");
	}
	else if (lex->last_token_type > TOKEN_RESWORDS){
		strcpy(result,TOKEN_RESERVED_WORDS[lex->last_token_type - TOKEN_RESWORDS - 1]);
		int i;
		for(i=0;result[i]!='\0';i++)
			result[i]+='A'-'a';
	}
	else{
		switch(lex->last_token_type){
			case TOKEN_PLUS: strcpy(result,"PLUS");break;
			case TOKEN_MINUS: strcpy(result,"MINUS");break;
			case TOKEN_TIMES: strcpy(result,"TIMES");break;
			case TOKEN_SLASH: strcpy(result,"SLASH");break;
			case TOKEN_EQU: strcpy(result,"EQU");break;
			case TOKEN_NEQ: strcpy(result,"NEQ");break;
			case TOKEN_LES: strcpy(result,"LES");break;
			case TOKEN_LEQ: strcpy(result,"LEQ");break;
			case TOKEN_GTR: strcpy(result,"GTR");break;
			case TOKEN_LPAREN: strcpy(result,"LPAREN");break;
			case TOKEN_RPAREN: strcpy(result,"RPAREN");break;
			case TOKEN_COMMA: strcpy(result,"COMMA");break;
			case TOKEN_SEMICOLON: strcpy(result,"SEMICOLON");break;
			case TOKEN_PERIOD: strcpy(result,"PERIOD");break;
			case TOKEN_BECOMES: strcpy(result,"BECOMES");break;
			case TOKEN_LSBRACKETS: strcpy(result,"LSBRACKET");break;
			case TOKEN_RSBRACKETS: strcpy(result,"RSBRACKET");break;
			case TOKEN_AND: strcpy(result,"AND");break;
			case TOKEN_OR: strcpy(result,"OR");break;
			case TOKEN_NOT: strcpy(result,"NOT");break;
		}
	}
	//return result;
}
void Shift(Stack *S,char *c){				//push parser into the stack
	char Stop[MAX_ID_LEN];
	char Parser[Max_Parser_Len][MAX_ID_LEN]={"\0","\0","\0","\0","\0"};
	while(!IsEmpty(S)){
		GetTop(S,Stop);
		if(strcmp(Stop,c)==0){
			Pop(S,Stop);
			Print(S);
			return;
		}
		else if(IsTerminal(Stop)&&strcmp(Stop,c)!=0){
			//printf("\n★  error,the top of the stack doesn't match input, we will pop the terminal\n");
			Pop(S,Stop);
			Print(S);
		}
		else if(MatchParser(Stop,c,Parser)==FALSE){
			if(First(Stop,"e")&&Synch(Stop,c)){
				Pop(S,Stop);
				Push(S,"e");
				Print(S);
				Pop(S,Stop);
				Print(S);
			}
			else if(Synch(Stop,c)){
				//printf("\n★  Match error, we will ignore the nonterminal at the top of the stack\n");
				Pop(S,Stop);
				Print(S);
			}
			else{
				//printf("\n%s",Stop);
				//printf("%s\n",c);
				printf("\n★  error,you miss something,please check your grammar\n");
				return;
			}
		}
		else{
			int i=0;
			MatchParser(Stop,c,Parser);
			Pop(S,Stop);
			while(strcmp(Parser[i],"\0")!=0){
				Push(S,Parser[i]);
				i++;
			}
			Print(S);
		}
	}
	return;
}
void Gen(int x,int y,int z,int k){//生成代码
	code[code_index].function_code = x;
	code[code_index].level = y;
	code[code_index].address = z;
	code[code_index].kind = k;
	code_index++;
}
void printcode(int a,int b){//打印指令
	printf("\n");
	int i;
	for( i = a;i<b;i++)
	{
		if(code[i].kind==0){
			printf("%5d %s\t",i,Print_code[code[i].function_code]);
		}
		else if(code[i].kind == 1){
			printf("%5d %s\t %d\n",i,Print_code[code[i].function_code],code[i].address);
		}
	}
}
int LookupTable(char* c,PL0Lex *lex){					//see if the id is already defined
	int i;
	int j = -1;
	for(i=0;i<table_index;i++)
		if(strcmp(c,token_table[i].name)==0){
			if(token_table[i].local ==local_ornot)
				return i;
			else{
				j = i;
			}
		}		
				
	return j;
}
/*functions for syntax analysis*/
void statementseq(PL0Lex *lex){
	//printf("analysis seq\n");
	if(lex->FileContent[lex->position]=='\0')
		return;
	while(1){
		if(lex->FileContent[lex->position]=='\0')
		return;
		statement(lex);
		if(lex->last_token_type==TOKEN_PERIOD)
			break;
		if(lex->last_token_type==TOKEN_SEMICOLON){
			//printf("seq exit judgement\n");
			PL0Lex_get_token(lex);
			while(lex->last_token_type==TOKEN_NULL&&lex->FileContent[lex->position]!='\0')
				PL0Lex_get_token(lex);
			if(lex->last_token_type==TOKEN_END){
				char str[MAX_ID_LEN];
				Transfer(lex,str);
				Shift(S,str);
				break;
			}	
			else	
				lex->position-=lex->end-lex->begin+1;
		}
		if(lex->last_token_type==TOKEN_END)
			break;
		//printf("you are in seq\n");
	}
}
void statement(PL0Lex * lex)
{
	if(lex->FileContent[lex->position]=='\0'){
		S->top--;
		S->length--;
		return;
	}
	PL0Lex_get_token_valid(S,lex);
		if(lex->last_token_type==TOKEN_IDENTIFIER)
		{
		    int IdTablePosition=LookupTable(lex->last_id,lex);
			PL0Lex_get_token_valid(S,lex);
			if(lex->last_token_type==TOKEN_BECOMES){
				PL0Lex_get_token_valid(S,lex);
                if(lex->last_token_type == TOKEN_CALL)
                {
                    PL0Lex_get_token_valid(S,lex);
                    if(lex->last_token_type == TOKEN_IDENTIFIER){
                        int IdTablePositioncall=LookupTable(lex->last_id,lex);
                        Gen(JMP,0, token_table[IdTablePositioncall].procedureaddress,AdressOrNum);//跳转到过程
                        code[code_index_return].address = code_index;
                    }
                    Gen(ST,token_table[IdTablePosition].level,token_table[IdTablePosition].address,AdressOrNum);
                    PL0Lex_get_token_valid(S,lex);//读掉分号
                }
                else{
                    expression(lex);
                    Gen(ST,token_table[IdTablePosition].level,token_table[IdTablePosition].address,AdressOrNum);
                }
			}
			else if(lex->last_token_type==TOKEN_LSBRACKETS){   //array 
				int ArrayOffset=0;
				BOOL ExpFlag=FALSE;//if the position of array is one expression
				do{
					PL0Lex_get_token_valid(S,lex);
					if(lex->last_token_type==TOKEN_MINUS){
						PL0Lex_get_token_valid(S,lex);
						if(lex->last_token_type==TOKEN_NUMBER){
							printf("\n★  The size of array can't be negative");
						}
						PL0Lex_get_token_valid(S,lex);
					}
					if(lex->last_token_type==TOKEN_NUMBER){
						if(token_table[IdTablePosition].dimenssion==1)
							ArrayOffset=lex->last_num*4;
						else{
						int i,size;
						//for(i=1;i<token_table[IdTablePosition].dimenssion)
						}
						PL0Lex_get_token_valid(S,lex);
					}
					if(lex->last_token_type==TOKEN_IDENTIFIER){
						ExpFlag=TRUE;
						expression(lex);
						Gen(PUT,0,4,AdressOrNum);
						Gen(MUL,0,0,NoAdressOrNum);//the width of element is 4
						Gen(PUT,0,token_table[IdTablePosition].address,AdressOrNum);
						Gen(ADD,0,0,NoAdressOrNum);
						Gen(ST,0,0,AdressOrNum);//store the position into memory
					}
					if(lex->last_token_type!=TOKEN_RSBRACKETS){
						printf("\n★  Missing right square bracket");
					}
					PL0Lex_get_token_valid(S,lex);
				}while(lex->last_token_type==TOKEN_LSBRACKETS);
				if(lex->last_token_type==TOKEN_BECOMES){
					PL0Lex_get_token_valid(S,lex);
					expression(lex);
					if(!ExpFlag)
						Gen(ST,0,token_table[IdTablePosition].address+ArrayOffset,AdressOrNum);
					else{
						Gen(LD,0,0,AdressOrNum);
						Gen(ST,0,0,NoAdressOrNum);
					}
				}
			}
			else{
				printf("\n★  There must be a ':=' following the id\n");
				PL0Lex_get_token_valid(S,lex);
			}
		}
	else if(lex->last_token_type==TOKEN_CALL)
	{
	    PL0Lex_get_token_valid(S,lex);
	    int IdTablePosition=LookupTable(lex->last_id,lex);
	    if(lex->last_token_type!=TOKEN_IDENTIFIER)
	        printf("\n★  There must be an id following 'call'\n");
	    else {
            if(IdTablePosition==-1)
            {
                printf("\n★  Undeclared identifier.\n");
            }
            else if (token_table[IdTablePosition].kind == ID_PROCEDURE)//跳转到procedure指示的地址
            {
				Gen(PUT,0, code_index+2 ,AdressOrNum);

                Gen(JMP,0, token_table[IdTablePosition].procedureaddress,AdressOrNum);//跳转到过程
                code_index_call = code_index;//记录跳转之后的第一条指令地址
				code[token_table[IdTablePosition].procedureendaddress].address=code_index_call;
            }
            else {
                printf("\n★  A constant or variable can not be called.\n");
            }
            PL0Lex_get_token_valid(S, lex);
        }
	}
	else if(lex->last_token_type==TOKEN_BEGIN){
	    statementseq(lex);
	    if(lex->last_token_type!=TOKEN_END)
	        printf("\n★  Missing 'end'\n");
	    PL0Lex_get_token_valid(S,lex);
	}
	else if(lex->last_token_type==TOKEN_IF)
	{
	    PL0Lex_get_token_valid(S,lex);
	    condition(lex);
		Gen(NOT,0,0,NoAdressOrNum);//attention again
	    code_index_if[code_index_if_count++] = code_index;
	    Gen(JPC,0,0,AdressOrNum);//条件不成立跳转到code_index_if,需要回填
        if(lex->last_token_type==TOKEN_THEN){
			code[code_index_or].address = code_index;//回填or短路的JPC
            statement(lex);
        }
        else{
            printf("\n★  Matching error:Expecting 'then'\n");
            lex->position-=lex->end-lex->begin+1;
            S->length++;
            S->top++;
            statement(lex);
        }
        code[code_index_if[0]].address = code_index;//回填if开始的JPC
		code[code_index_and].address = code_index;//回填and短路的JPC
        //PL0Lex_get_token_valid(S,lex);
		if(lex->last_token_type==TOKEN_ELIF){
			code_index_if_flag=TRUE;
			code_index_endif[code_index_endif_count++]=code_index;
			Gen(JMP,0,0,AdressOrNum);
			do{
				code[code_index_if[code_index_if_count-1]].address=code_index;//fill last if/elseif adress
				PL0Lex_get_token_valid(S,lex);
				condition(lex);
				Gen(NOT,0,0,NoAdressOrNum);
				code_index_if[code_index_if_count++] = code_index;
	    		Gen(JPC,0,0,AdressOrNum);//条件不成立跳转到code_index_if,需要回填
				statement(lex);
				code_index_endif[code_index_endif_count++]=code_index;
				Gen(JMP,0,0,AdressOrNum);//We shuold jmp to the end after we finish the excution
			}while(lex->last_token_type==TOKEN_ELIF);
		}
        if(lex->last_token_type==TOKEN_ELSE){
			//code_index_endif[code_index_endif_count++]=code_index;
			//Gen(JMP,0,0,AdressOrNum);
			code_index_if_flag=TRUE;
			code[code_index_if[code_index_if_count-1]].address=code_index;
            statement(lex);
			for(code_index_endif_count--;code_index_endif_count>=0;code_index_endif_count--){
				code[code_index_endif[code_index_endif_count]].address=code_index;
			}
            //code[code_index_endif].address = code_index;//回填跳出if语句的JMP指令
        }
		else if(lex->last_token_type!=TOKEN_END){
			if(code_index_if_flag==FALSE)
				code[code_index_if[0]].address==code_index;
			lex->position-=lex->end-lex->begin+1;
            S->length++;
            S->top++;
		}
		else{
			if(code_index_if_flag==FALSE)
				code[code_index_if[0]].address==code_index;
		}
		for(;code_index_if_count>=0;code_index_if_count--){
			code_index_if[code_index_if_count]=0;
			if(code_index_endif_count>=0)
				code_index_endif[code_index_endif_count--]=0;
		}
		code_index_endif_count=0;
		code_index_if_count=0;
	}
	else if(lex->last_token_type==TOKEN_WHILE)
	{
	    PL0Lex_get_token_valid(S,lex);
	    int code_index_temp = code_index;
	    condition(lex);
		Gen(NOT,0,0,NoAdressOrNum);//attention here
	    code_index_while[code_index_while_count++] = code_index;//记录JPC指令的地址
	    Gen(JPC,0,0,AdressOrNum);//跳出while，需要回填
        if(lex->last_token_type==TOKEN_DO)
        {
            statement(lex);
        }
        else{
            printf("\n★  Matching error:Expecting 'do'\n");
            lex->position-=lex->end-lex->begin+1;
            S->length++;
            S->top++;
            statement(lex);
        }
        Gen(JMP,0,code_index_temp,AdressOrNum);//无条件跳回code_index_temp
		if(!code_index_while_flag){
			code_index_while_count--;
			code_index_while_flag=TRUE;
		}
        code[code_index_while[code_index_while_count--]].address = code_index;//回填while开始的JPC指令跳转的地址
    }
    else if(lex->last_token_type==TOKEN_DO)
    {
        int code_index1 = code_index;
        statement(lex);
        if(lex->last_token_type==TOKEN_WHILE){
            PL0Lex_get_token_valid(S,lex);
            condition(lex);
            Gen(JPC,0,code_index1,AdressOrNum);
        }
        else{
            printf("\n★  Matching error:Expecting 'while'\n");
            lex->position-=lex->end-lex->begin+1;
            S->length++;
            S->top++;
            condition(lex);
            Gen(JPC,0,code_index1,AdressOrNum);//条件跳转
			}
    }
    else if(lex->last_token_type==TOKEN_RETURN){//返回值
	    return_flag = TRUE;
		PL0Lex_get_token_valid(S,lex);
		int Idposition = LookupTable(lex->last_id,lex);
		Gen(LD,0,token_table[Idposition].address,AdressOrNum);//返回值放在栈顶
	    if(lex->last_token_type==TOKEN_SEMICOLON){
	        printf("\n★  Matching error:Expecting return value\n");
	    }
	    code_index_return = code_index;
	    Gen(JMP,0,0,AdressOrNum);//跳回call之后的第一条指令地址
        PL0Lex_get_token_valid(S,lex);//读掉分号
        statement(lex);
			//保留val属性传递
    }
    else if(lex->last_token_type==TOKEN_PRINT){
	    PL0Lex_get_token_valid(S,lex);
	    if(lex->last_token_type!=TOKEN_IDENTIFIER){
	        printf("\n★  There must be an id following print\n");
	    }
	    int IdTablePosition=LookupTable(lex->last_id,lex);
	    if(IdTablePosition==-1){
	        printf("\n★  The id is not defined\n");
	    }
	    else{
			PL0Lex_get_token_valid(S,lex);
			int ArrayOffset=0;
			BOOL ExpFlag=FALSE;
			if(lex->last_token_type==TOKEN_LSBRACKETS){		//process array
			do{
				PL0Lex_get_token_valid(S,lex);
				if(lex->last_token_type==TOKEN_MINUS){
						PL0Lex_get_token_valid(S,lex);
						if(lex->last_token_type==TOKEN_NUMBER){
							printf("\n★  The size of array can't be negative\n");
						}
						PL0Lex_get_token_valid(S,lex);						
				}
				if(lex->last_token_type==TOKEN_NUMBER){
					if(token_table[IdTablePosition].dimenssion==1)
						ArrayOffset=lex->last_num*4;
					else{
						int i,size;
					}
					PL0Lex_get_token_valid(S,lex);
				}
				if(lex->last_token_type==TOKEN_IDENTIFIER){
						ExpFlag=TRUE;
						expression(lex);
						Gen(PUT,0,token_table[IdTablePosition].address,AdressOrNum);
						Gen(ADD,0,0,NoAdressOrNum);
						Gen(ST,0,0,AdressOrNum);//store the position into memory
				}
				if(lex->last_token_type!=TOKEN_RSBRACKETS){
					printf("\n★  Missing right square bracket\n");
				}
				PL0Lex_get_token_valid(S,lex);
			}while(lex->last_token_type==TOKEN_LSBRACKETS);
			}
			if(!ExpFlag){
				Gen(LD,0,token_table[IdTablePosition].address+ArrayOffset,AdressOrNum);
				Gen(INT,0,0,AdressOrNum);
			}
			else{
				Gen(LD,0,token_table[IdTablePosition].address,AdressOrNum);
	        	Gen(INT,0,0,AdressOrNum);
			}


			//出栈
			Gen(PUT,0,0,AdressOrNum);
			Gen(MUL,0,0,NoAdressOrNum);
			Gen(ADD,0,0,NoAdressOrNum);
	    }
	}
	else if(lex->last_token_type==TOKEN_PERIOD){
	    return;
	}
	else{
	    return;
	    printf("\n★  statement error\n");
	}
}
void CONDITION(PL0Lex * lex) {
	//printf("analysis the condition expression\n");
	//逻辑运算!
	int TempType;
	if(lex->last_token_type == TOKEN_LPAREN){
		PL0Lex_get_token_valid(S,lex);
		CONDITION(lex);
		PL0Lex_get_token_valid(S,lex);
	}
	else if(lex->last_token_type==TOKEN_NOT){
		PL0Lex_get_token_valid(S,lex);
		CONDITION(lex);
		Gen(NOT,0,0,NoAdressOrNum);
	}
	else{
		if(lex->last_token_type==TOKEN_ODD){
			PL0Lex_get_token_valid(S,lex);
			expression(lex);
		}
		else{
			expression(lex);
			if(lex->last_token_type==TOKEN_EQU||lex->last_token_type==TOKEN_NEQ||
			   lex->last_token_type==TOKEN_LES||lex->last_token_type==TOKEN_GTR||
			   lex->last_token_type==TOKEN_LEQ||lex->last_token_type==TOKEN_GEQ){
				TempType=lex->last_token_type;
				PL0Lex_get_token_valid(S,lex);
				expression(lex);
				switch(TempType){
					case TOKEN_EQU:
						Gen(EQ,0,0,NoAdressOrNum);
						break;
					case TOKEN_NEQ:
						Gen(EQ,0,0,NoAdressOrNum);
						Gen(NOT,0,0,NoAdressOrNum);
						break;
					case TOKEN_LES:
						Gen(GT,0,0,NoAdressOrNum);
						break;
					case TOKEN_LEQ:
						Gen(GE,0,0,NoAdressOrNum);
						break;
					case TOKEN_GTR:
						Gen(LT,0,0,NoAdressOrNum);
						break;
					case TOKEN_GEQ:
						Gen(LE,0,0,NoAdressOrNum);
						break;
					default:
						break;
				}
			}
			else
				printf("\n★  condition error\n");
		}
	}
}
void condition(PL0Lex *lex){
	int TempType;
	CONDITION(lex);
	while(lex->last_token_type == TOKEN_AND||lex->last_token_type == TOKEN_OR){

		if(TempType==TOKEN_AND){//短路
			Gen(NOT,0,0,NoAdressOrNum);
			code_index_and = code_index;
			Gen(JPC,0,0,AdressOrNum);
		}
			
		else{
			code_index_or = code_index;
			Gen(JPC,0,0,AdressOrNum);
		}
			

		


		TempType = lex->last_token_type;
		PL0Lex_get_token_valid(S,lex);
		CONDITION(lex);
		if(TempType==TOKEN_AND)
			Gen(AND,0,0,NoAdressOrNum);
		else
			Gen(OR,0,0,NoAdressOrNum);
	}
}
void expression(PL0Lex * lex) {
	//printf("analysis the expression\n");
	term(lex);
	int TempType;
	do{
		if(lex->last_token_type==TOKEN_PLUS||lex->last_token_type==TOKEN_MINUS){
			TempType=lex->last_token_type;
			PL0Lex_get_token_valid(S,lex);
			term(lex);
			if(TempType==TOKEN_MINUS){
				Gen(ST,0,0,AdressOrNum);
				Gen(ST,0,4,AdressOrNum);
				Gen(LD,0,0,AdressOrNum);
				Gen(LD,0,4,AdressOrNum);
				Gen(SUB,0,0,NoAdressOrNum);
			}
			else
				Gen(ADD,0,0,NoAdressOrNum);
		}
	}while(lex->last_token_type==TOKEN_PLUS||lex->last_token_type==TOKEN_MINUS);
}
void term(PL0Lex * lex) {
	//printf("analysis the term\n");
	factor(lex);
	int TempType;
	do{
		if(lex->last_token_type==TOKEN_SLASH||lex->last_token_type==TOKEN_TIMES){
			TempType=lex->last_token_type;
			PL0Lex_get_token_valid(S,lex);
			factor(lex);
			if(TempType==TOKEN_SLASH){
				Gen(ST,0,0,AdressOrNum);
				Gen(ST,0,4,AdressOrNum);
				Gen(LD,0,0,AdressOrNum);
				Gen(LD,0,4,AdressOrNum);
				Gen(DIV,0,0,NoAdressOrNum);
			}
			else
				Gen(MUL,0,0,NoAdressOrNum);
		}
	}
	while(lex->last_token_type==TOKEN_SLASH||lex->last_token_type==TOKEN_TIMES);
}
void factor(PL0Lex * lex) {
	//printf("analysis the factor\n");
	if(lex->last_token_type==TOKEN_IDENTIFIER){
		int IdTablePosition=LookupTable(lex->last_id,lex);
		if(IdTablePosition==-1)
			printf("\n★  %s is not defined\n",lex->last_id);
		PL0Lex_get_token_valid(S,lex);
		int ArrayOffset=0;
		BOOL ExpFlag=FALSE;
		if(lex->last_token_type==TOKEN_LSBRACKETS){		//process array
			do{
				PL0Lex_get_token_valid(S,lex);
				if(lex->last_token_type==TOKEN_MINUS){
						PL0Lex_get_token_valid(S,lex);
						if(lex->last_token_type==TOKEN_NUMBER){
							printf("\n★  The size of array can't be negative\n");
						}
						PL0Lex_get_token_valid(S,lex);						
				}
				if(lex->last_token_type==TOKEN_NUMBER){
					if(token_table[IdTablePosition].dimenssion==1)
						ArrayOffset=lex->last_num*4;
					else{
						int i,size;
						//for(i=1;i<token_table[IdTablePosition].dimenssion)
					}
					PL0Lex_get_token_valid(S,lex);
				}
				if(lex->last_token_type==TOKEN_IDENTIFIER){
						ExpFlag=TRUE;
						expression(lex);
						Gen(PUT,0,4,AdressOrNum);
						Gen(MUL,0,0,NoAdressOrNum);//the width of element is 4
						Gen(PUT,0,token_table[IdTablePosition].address,AdressOrNum);
						Gen(ADD,0,0,NoAdressOrNum);
						Gen(ST,0,4,AdressOrNum);//store the position into memory
				}
				if(lex->last_token_type!=TOKEN_RSBRACKETS){
					printf("\n★  Missing right square bracket\n");
				}
				PL0Lex_get_token_valid(S,lex);
			}while(lex->last_token_type==TOKEN_LSBRACKETS);
		}
		if(!ExpFlag)
			Gen(LD,0,token_table[IdTablePosition].address+ArrayOffset,AdressOrNum);
		else{
			Gen(LD,0,4,AdressOrNum);//push the address of the array element
			Gen(LD,0,0,NoAdressOrNum);//push the array element
		}
	}
	else if(lex->last_token_type==TOKEN_NUMBER){
		Gen(PUT,0,lex->last_num,AdressOrNum);
		PL0Lex_get_token_valid(S,lex);
	}
	else if(lex->last_token_type==TOKEN_MINUS){
		PL0Lex_get_token_valid(S,lex);
		expression(lex);
		Gen(PUT,0,0,AdressOrNum);
		Gen(SUB,0,0,0);
	}
	else if(lex->last_token_type==TOKEN_LPAREN){
		PL0Lex_get_token_valid(S,lex);
		expression(lex);
		if(lex->last_token_type==TOKEN_RPAREN){
		}
		else
			printf("\n★  Missing ')'");
		PL0Lex_get_token_valid(S,lex);
	}
	else if(lex->last_token_type==TOKEN_CALL){
		PL0Lex_get_token_valid(S,lex);
		if(lex->last_token_type==TOKEN_IDENTIFIER){
			int IdTablePosition=LookupTable(lex->last_id,lex);
			if(IdTablePosition!=-1)
				Gen(JMP,0,token_table[IdTablePosition].procedureaddress,AdressOrNum);
			code[token_table[IdTablePosition].procedureendaddress].address=code_index;
		}
	}
}
void const_declaration(PL0Lex * lex) {
	char TokenStr[MAX_ID_LEN];
	int IdTablePosition;
	int AddressOfId;
	char *AddressStr,*NumStr;
	if (lex->last_token_type == TOKEN_IDENTIFIER) {
		PL0Lex_get_token_valid(S,lex);
		if (lex->last_token_type == TOKEN_EQU || lex->last_token_type == TOKEN_BECOMES) {
			if (lex->last_token_type == TOKEN_BECOMES)
				printf("\n★  found ':=' when expecting '='\n");
			PL0Lex_get_token_valid(S,lex);
			if (lex->last_token_type==TOKEN_MINUS){
				PL0Lex_get_token_valid(S,lex);
				if (lex->last_token_type == TOKEN_NUMBER) {
					lex->last_num=-lex->last_num;
					table_append(lex, ID_CONSTANT,0,NULL);
					Gen(PUT,0,lex->last_num,AdressOrNum);
					IdTablePosition=LookupTable(lex->last_id,lex);
					AddressOfId=token_table[IdTablePosition].address;
					Gen(ST,0,AddressOfId,AdressOrNum);
					PL0Lex_get_token_valid(S,lex);				
				} else {
					printf("\n★  there must be a number to follow '='\n");
				}
			}			
			else if (lex->last_token_type == TOKEN_NUMBER) {
				table_append(lex, ID_CONSTANT,0,NULL);
				Gen(PUT,0,lex->last_num,AdressOrNum);
				IdTablePosition=LookupTable(lex->last_id,lex);
				AddressOfId=token_table[IdTablePosition].address;
				Gen(ST,0,AddressOfId,AdressOrNum);
				PL0Lex_get_token_valid(S,lex);				
			} else {
				printf("\n★  there must be a number to follow '='\n");
			}
		} else {
			printf("\n★  there must be an '=' to follow the identifier\n");
		}
	} else {
		printf("\n★  There must be an identifier to follow 'const'\n");
	}
} //const_declaration
void var_declaration(PL0Lex * lex){
	char TokenStr[MAX_ID_LEN],ID[MAX_ID_LEN];
	int Dimension=0;														//dimension of the array
	int Enum[3];														    //element number of each dimension
	long position=lex->position;
	if(lex->last_token_type==TOKEN_IDENTIFIER){
		PL0Lex_get_token(lex);
		if(lex->last_token_type==TOKEN_LSBRACKETS){						   	//process array
			lex->position=position;
			PL0Lex_get_token_valid(S,lex);							   		//'['
			do{
				PL0Lex_get_token_valid(S,lex);								//num
				if(lex->last_token_type==TOKEN_MINUS){
						PL0Lex_get_token_valid(S,lex);
						if(lex->last_token_type==TOKEN_NUMBER){
							printf("\n★  The size of array can't be negative\n");
						}
					}//
				else if(!(lex->last_token_type==TOKEN_NUMBER||lex->last_token_type==TOKEN_IDENTIFIER)){
					printf("\n★  There must be a number or declared id in brackets\n");
				}
				else{
					Dimension++;
					if(lex->last_token_type==TOKEN_NUMBER)
						Enum[Dimension]=lex->last_num;
					else{
						int i=LookupTable(lex->last_id,lex);
						if(i==-1){
							printf("\n★ The id is not declared\n");
							Enum[Dimension]=0;
						}
						else{
							if(token_table[i].value<0){
								printf("\n★  The size of array can't be negative\n");
								Enum[Dimension]=0;
							}
							else
								Enum[Dimension]=token_table[i].value;
						}
					}
				}
				PL0Lex_get_token_valid(S,lex);
				if(lex->last_token_type!=TOKEN_RSBRACKETS){
					printf("\n★  Missing right square bracket\n");
				}
				PL0Lex_get_token_valid(S,lex);
			}while(lex->last_token_type==TOKEN_LSBRACKETS);
			//for(i=0;i<tablenum;i++)
			table_append(lex,ID_VARIABLE,Dimension,Enum);
		}
		else{
			lex->position=position;
			table_append(lex,ID_VARIABLE,0,NULL);									//unless we meet another id, or we won't change last_id, so here we can use lex without extra recovery
			PL0Lex_get_token_valid(S,lex);
		}
	}
	else
		printf("\n★  There must be an identifier to follow 'var'\n");
}
void program_block(PL0Lex * lex) {//回填技术，暂时还没有想到
	//printf("analysis the program block\n");
	BOOL PFlag=FALSE;
	char ID[MAX_ID_LEN];
	do {
		if (lex->last_token_type == TOKEN_CONST) {
			PL0Lex_get_token_valid(S,lex);
			do {
				const_declaration(lex);
				while (lex->last_token_type == TOKEN_COMMA) {
					PL0Lex_get_token_valid(S,lex);
					const_declaration(lex);
				}
				if (lex->last_token_type == TOKEN_SEMICOLON) {
					PL0Lex_get_token_valid(S,lex);
				}
				else {
					printf("\n★  missing ',' or ';'\n");
				}
			} while (lex->last_token_type == TOKEN_IDENTIFIER);
		}
		else if(lex->last_token_type==TOKEN_VAR){
			PL0Lex_get_token_valid(S,lex);			
			do{
				var_declaration(lex);
				while(lex->last_token_type==TOKEN_COMMA){
					PL0Lex_get_token_valid(S,lex);					
					var_declaration(lex);
				}
				if(lex->last_token_type==TOKEN_SEMICOLON){
					PL0Lex_get_token_valid(S,lex);					
				}
				else if(lex->last_token_type==TOKEN_IDENTIFIER){//COMMA Missing
					printf("\n★  missing ','\n");
				}
				else
					printf("\n★  missing ';'\n");
			}while (lex->last_token_type == TOKEN_IDENTIFIER);
		}
		else if(lex->last_token_type==TOKEN_PROCEDURE)//分析过程，先跳转到main函数
		{
			local_ornot = table_index + 10;
		    PL0Lex_get_token_valid(S,lex);
			if(!PFlag){//when there are multiple procedure , we just need to gen one;
				code_index_pro = code_index;
				Gen(JMP,0,0,AdressOrNum);//跳转到main函数
			}
			PFlag=TRUE;	//we meet procedure before we begin main function							
			if(lex->last_token_type==TOKEN_IDENTIFIER)
			{
				lex->last_level++;
				strcpy(ID,lex->last_id);
				table_append(lex,ID_PROCEDURE,0,NULL);
				PL0Lex_get_token_valid(S,lex);
				if(lex->last_token_type==TOKEN_SEMICOLON){
					PL0Lex_get_token_valid(S,lex);
					level++;//嵌套深度++
					program_block(lex);//递归调用下一block
					level--;
				}
				else	
					printf("\n★  missing ';'\n");
                int IdTablePosition=LookupTable(ID,lex);
                token_table[IdTablePosition].procedureendaddress=code_index;
				if(!return_flag)//没有return时结束后跳转
					Gen(JMP,0,0,NoAdressOrNum);
                    //Gen(JMP,0,0,AdressOrNum);//at the end of the procedure we should jmp back to the position where we call it.
				if(lex->last_token_type!=TOKEN_SEMICOLON)	
					printf("\n★  missing ';'\n");
				PL0Lex_get_token_valid(S,lex);
			}
			else if(lex->last_token_type==TOKEN_SEMICOLON)
			{
				printf("\n★  There must be an identifier to follow 'procedure'\n");
				lex->last_level++;
				PL0Lex_get_token_valid(S,lex);
				program_block(lex);
				lex->last_level--;
				if(lex->last_token_type!=TOKEN_SEMICOLON)	
					printf("\n★  missing ';'\n");
				PL0Lex_get_token_valid(S,lex);
			}
			else
				printf("\n★  Your grammar is completely wrong, we will give up the analysis,please check first");
			//printf("exit procedure\n\n");

			local_ornot = 0;
		}
	} while(lex->last_token_type == TOKEN_CONST || lex->last_token_type == TOKEN_VAR || lex->last_token_type == TOKEN_PROCEDURE);
	if(lex->FileContent[lex->position]=='\0') return;
	lex->position-=lex->end - lex->begin + 1;
	S->top++;
	S->length++;							//recover stack
	if(PFlag==TRUE)
    	code[code_index_pro].address = code_index;//记录主函数代码地址
    statement(lex);
} //program_block
void program(PL0Lex *lex){					
	S=(Stack *)malloc(sizeof(Stack));
    if(S==NULL) printf("\n★  allocate memory error\n");
    S->length=0;
    S->top=0;
	Push(S,"PERIOD");
	Push(S,"B");
	Print(S);
	PL0Lex_get_token_valid(S,lex);			//before entering next level of analysis, we've already get the next token

	Gen(PUT,0,0,AdressOrNum);
	Gen(PUT,0,0,AdressOrNum);

	program_block(lex);
	if(lex->last_token_type!=TOKEN_PERIOD){
		if(!IsEmpty(S)&&strcmp(S->S[S->top-1],"PERIOD")!=0)
			printf("\n★  Your program is not completed, please finish it. Or you should check if your 'end' matches 'begin' correctly\n");
		else
			printf("\n★  There must be a '.' at the end of program\n");
	}
	else	
		printf("Annlysis completed\n");
	//sprintf(CodeBuffer+Offset,"INT 1\n");	//terminate the machine
	Gen(INT,0,1,AdressOrNum);
	GenASM();								//Generate asm file
}
void GenASM(){
	int i;
	for(i=0;i<code_index;i++){
		if(code[i].kind==AdressOrNum){
			Offset+=sprintf(CodeBuffer+Offset,"%s %d\n",Instruction[code[i].function_code],code[i].address);
		}
		else
			Offset+=sprintf(CodeBuffer+Offset,"%s\n",Instruction[code[i].function_code]);
	}
	if(fout==NULL){
		printf("file error!\n");
		exit(0);
	}
	else{
		fprintf(fout,"%s",CodeBuffer);
	}
	fclose(fout);
}
