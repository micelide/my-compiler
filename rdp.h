#ifndef RDP_H
#define RDP_H

//define random numbers to represent a, b, c
#define A 13071L
#define B 10172L
#define C 11022L

//globals
char lookahead; 
char statement[1024];
int countr;
long a = A;
long b = B;
long c = C;

//functions
void initLookahead();
void nextTerminal();
void syntaxError();
void runtimeError();
void match(char terminal);
void cons_t();
void Id();
long expr();
void print();
void assign();
void stmt();
void nextstmt();
void stmtlist();
void program();


#endif
