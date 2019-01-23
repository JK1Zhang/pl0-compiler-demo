# 程序体预测分析表
1.对于已经在代码中实现的各变量的定义，我们通过语法图写出其对应的产生式如下：  

B &rarr; SB | &epsilon;  
S &rarr; C | M | N  
C &rarr; const V SEMICOLON  //const  
V &rarr; ident EQU number E  
E &rarr; COMMA V | &epsilon;    
M &rarr; var W SEMICOLON    //var    
W &rarr; ident F    
F &rarr; COMMA W | &epsilon;    
N &rarr; procedure ident X  //procedure     
X &rarr; SEMICOLON B SEMICOLON

2.根据该产生式构造对应的FIRST和FOLLOW集合如下  

FIRST(B) = {const, var, procedure, &epsilon;}  
FIRST(S) = {const, var, procedure}   
FIRST(C) = {const}  
FIRST(V) = FIRST(W) = {ident}  
FIRST(E) = FIRST(F) = {COMMA, &epsilon;}  
FIRST(M) = {var}  
FIRST(N) = {procedure}  
FIRST(X) = {SEMICOLON}  
FOLLOW(S) = FOLLOW(C) = FOLLOW(M) = FLLOW(N) =FOLLOW(X) = {$}  
FOLLOW(B) = FOLLOW(V) = FOLLOW(E) = FOLLOW(W) = FOLLOW(F) = {SEMICOLON}  

3.然后构造预测分析表如下  

| - | const | var |procedure | ident | EQU | number | COMMA | SEMICOLON | $ |
| :---: | :---: | :---: | :--: |:---: | :---: | :---: | :---: | :---: | :---: |
| B | B &rarr; SB | B &rarr; SB| B &rarr; SB |- | - | - | - | - | B &rarr; &epsilon; |
| S | S &rarr; C | S &rarr; M | S &rarr; N | - | - | - | - | - | - |
| C | C &rarr; const V SEMICOLON | - | - | - | - | - | - | - | - |
| V | - | - | -| V &rarr; ident EQU number E | - | - | - | - | - |
| E | - | - | - | - | - | - | E &rarr; COMMA V | - | E &rarr; &epsilon; |  
| M | - | M &rarr; W SEMICOLON | - | - | - | - | - | - | - |
| W | - | - | - | W &rarr; ident F | - | - | - | - | - | - |
| F | - | - | - | - | - | - | F &rarr; COMMA W | - | F &rarr; &epsilon;
| N | - | - | N &rarr; procedure ident X | - | - | - | - | - | - |
| X | - | - | - | - | - | - | - | X &rarr; SEMICOLON B SEMICOLON | - |