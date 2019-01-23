#ifndef __STACK_H__
#define __STACK_H__

#define Max_Len 10
#define Max_Stack_Size 100
typedef struct St{
    char S[Max_Stack_Size][Max_Len];
    int top;
    int length;
}Stack;

void Init(Stack *S);
void Print(Stack *S);
int GetLength(Stack *S);
BOOL Push(Stack *S, char *c);
BOOL Pop(Stack *S, char *c);
BOOL GetTop(Stack *S, char *c);
BOOL IsEmpty(Stack *S);
BOOL IsFull(Stack *S);
BOOL Search(Stack *S, char *c);
/*
B → SB | ε						1
S → C | M | N					2
C → const V SEMICOLON //const	3
V → ident EQU number E			4
E → COMMA V | ε					5
M → var W SEMICOLON //var		6
W → ident F						7
F → COMMA W | ε					8
N → procedure ident X //procedure	9
X → SEMICOLON B SEMICOLON		10
*/
#endif