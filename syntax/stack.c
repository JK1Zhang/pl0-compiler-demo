#include <stdio.h>
#include <stdlib.h>
#include "../common/common.h"
#include "stack.h"

void Init(Stack *S){
    int i;
    /*for(i=0;i<Max_Stack_Size;i++)
        S->S[i]=(char *) malloc(sizeof(char *)*Max_Len);*/
    S=(Stack *)malloc(sizeof(Stack));
    if(S==NULL) printf("allocate memory error\n");
    S->length=0;
    S->top=0;
}

void Print(Stack *S){
    int i;
    for(i=0;i<S->length;i++){
        printf("%s ",S->S[i]);
    }
    printf("\n");
}
int GetLength(Stack *S){
    return S->length;
}

BOOL Push(Stack *S, char *c){
    if(IsFull(S)){
        printf("The Stack is already full\n");
        return FALSE; 
    }
    strcpy(S->S[S->top],c);
    S->top++;
    S->length++;
    return TRUE;
}
BOOL Pop(Stack *S, char *c){
    if(IsEmpty(S)){
        printf("The Stack is empty\n");
        return FALSE;
    }
    strcpy(c,S->S[S->top-1]);
    S->top--;
    S->length--;
    return TRUE;
}

BOOL GetTop(Stack *S, char *c){
    if(IsEmpty(S)){
        printf("The Stack is empty\n");
        return FALSE;
    }
    strcpy(c,S->S[S->top-1]);
    return TRUE;
}

BOOL IsEmpty(Stack *S){
    if(S->top==0)
        return TRUE;
    return FALSE;
}

BOOL IsFull(Stack *S){
    if(S->top>=Max_Stack_Size)
        return TRUE;
    return FALSE;
}

BOOL Search(Stack *S, char *c){
    int i;
    for (i=0;i<S->top;i++)
        if(strcmp(S->S[i],c)==0)
            return TRUE;
    return FALSE;
}