/**
A Recursive Decent Parser in C
takes stdin , parses according to the grammar, and outputs the result
	--assume integers (divison discards remainder)

* requires a mutually recursive method per non-terminal in the grammar
	--switch statement for the lookahead
		--case for each element of FIRST(non-terminal) of the method we are in
		--default syntax error
	--mutually recursive --> need a header with function declarations

* global variable "lookahead" holds the currently scanned input var

* next_token to proceed to the next symbol

* match_token to update and consume the token
	--unexpected token, syntax error
	--end of the grammar NULL or '.'

* syntaxError to report an error and stop the recursion

**/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "rdp.h"

void initLookahead() {
	countr = 0;
	lookahead = statement[countr];
}
void nextTerminal() {
	++countr; //go to the next terminal in the statement
	lookahead = statement[countr];
}
void syntaxError() {
	//print the error at the terminal being examined and exit
	printf("
	       error\n");
	exit(0);
}
void runtimeError() {
	printf("runtime error\n");
}
void match(char terminal) {
	if(terminal == lookahead){
		if((lookahead == 0)||(lookahead == '.')) { exit(0); } //done with the statement, exit without an error
		else { nextTerminal(); } //continue
	}
	else { syntaxError(); } //problem
}
void program() { //FIRST(program) = {a, b, c, !}

	switch(lookahead) {
		case 'a': stmtlist();
		printf("finished\n");
		match('.');
		break;
		case 'b': stmtlist();
		printf("finished\n");
		match('.');
		break;
		case 'c': stmtlist();
		printf("finished\n");
		match('.');
		break;
		case '!': stmtlist();
		printf("finished\n");
		match('.');
		break;
		default: syntaxError();
	}
	
}
void stmtlist() { //FIRST(stmtlist) = {a, b, c, !}

	switch(lookahead) {
		case 'a': stmt(); 
		nextstmt();
		break;
		case 'b': stmt();
		nextstmt();
		break;
		case 'c': stmt();
		nextstmt();
		break;
		case '!': stmt();
		nextstmt();
		break;
		default: syntaxError();
	}
}
void stmt() { //FIRST(stmt) = {a, b, c, !}

	switch(lookahead) {
		case 'a': assign();
		break;
		case 'b': assign();
		break;
		case 'c': assign();
		break;
		case '!': print();
		break;
		default: syntaxError();
	}
}
void nextstmt() { //FIRST(nextstmt) = {empty, ;}

	switch(lookahead) {
		case ';': match(';');
		stmtlist();
		break;
		case '.': match('.'); //match will exit gracefully
		break;
		default: syntaxError();
	}	
}

void assign() { //FIRST(assign) = {a, b, c}

	long val;
	switch(lookahead) { 
		case 'a': Id();
		match('=');
		val = expr();
        if((val == A)||(val == B)||(val == C)) {
            //reference unassigned variable
            runtimeError();
            exit(0);
        }
		a = val;
		break;
		case 'b': Id();
		match('=');
		val = expr();
        if((val == A)||(val == B)||(val == C)) {
            //reference unassigned variable
            runtimeError();
            exit(0);
        }
		b = val;
		break;
		case 'c': Id();
		match('=');
		val = expr();
        if((val == A)||(val == B)||(val == C)) {
            //reference unassigned variable
            runtimeError();
            exit(0);
        }
		c = val;
		break;
		default: syntaxError();
	}
}
void print() { //FIRST(print) = {!}

	match('!');
	switch(lookahead) {
		//if it is a variable, print the value
		case 'a':
        if(a == A) {
            //print unassigned variable
            runtimeError();
            exit(0);
        }
        else { printf("%lu\n", a); }
		break;
        case 'b': if(b == B) { //print unassigned variable
            runtimeError();
            exit(0);
        }
        else { printf("%lu\n", b); }
		break;
        case 'c': if(c == C) {
            //print unassigned variable
            runtimeError();
            exit(0);
        }
        else { printf("%lu\n", c); }
		break;
		default: break;
	}
	//consume the terminal
	Id();
}
long expr() { //FIRST(expr) = {a, b, c, +, -, *, /, 0..9}

	long ret1;
	long ret2;
	switch(lookahead) {
		case '0': cons_t();
		return 0;
		case '1': cons_t();
		return 1;
		case '2': cons_t();
		return 2;
		case '3': cons_t();
		return 3;
		case '4': cons_t();
		return 4;
		case '5': cons_t();
		return 5;
		case '6': cons_t();
		return 6;
		case '7': cons_t();
		return 7;
		case '8': cons_t();
		return 8;
		case '9': cons_t();
		return 9;
		case '+': match('+');
		ret1 = expr();
		//if the value given was an Id (not an integer), replace it with the value currently at that Id
        if((ret1 == A)&&(a != A)) { //a is given, and has been assigned a value
            ret1 = a;
        }
        else if((ret1 == B)&&(b != B)) { //b has been assigned a value
            ret1 = b;
        }
        else if((ret1 == C)&&(c != C)) { //c has been assigned a value
            ret1 = c;
        }
        else if((ret1 == A)||(ret1 == B)||(ret1 == C)) {
            //referrence unassigned variable
            runtimeError();
            exit(0);
        }
		ret2 = expr();
        if((ret2 == A)&&(a != A)) {
            ret2 = a;
        }
        else if((ret2 == B)&&(b != B)) {
            ret2 = b;
        }
        else if((ret2 == C)&&(c != C)) {
            ret2 = c;
        }
        else if((ret2 == A)||(ret2 == B)||(ret2 == C)) {
            //unassigned var ref
            runtimeError();
            exit(0);
        }

		return (ret1 + ret2);
		case '-': match('-');
		ret1 = expr();
		//if the value given was an Id (not an integer), replace it with the value currently at that Id
		if((ret1 == A)&&(a != A)) { //a is given, and has been assigned a value
			ret1 = a;
		}
		else if((ret1 == B)&&(b != B)) { //b has been assigned a value
			ret1 = b;
		}
		else if((ret1 == C)&&(c != C)) { //c has been assigned a value
			ret1 = c;
		}
        else if((ret1 == A)||(ret1 == B)||(ret1 == C)) {
            //referrence unassigned variable
            runtimeError();
            exit(0);
        }
		ret2 = expr();
		if((ret2 == A)&&(a != A)) {
			ret2 = a;
		}
		else if((ret2 == B)&&(b != B)) {
			ret2 = b;
		}
		else if((ret2 == C)&&(c != C)) {
			ret2 = c;
		}
        else if((ret2 == A)||(ret2 == B)||(ret2 == C)) {
            //unassigned var ref
            runtimeError();
            exit(0);
        }
            
		return (ret1 - ret2);
		case '*': match('*');
		ret1 = expr();
		//if the value given was an Id (not an integer), replace it with the value currently at that Id
		if((ret1 == A)&&(a != A)) { //A is given, and A has been assigned a value
			ret1 = a;
		}
        else if((ret1 == B)&&(b != B)) { //b has been assigned a value
            ret1 = b;
        }
        else if((ret1 == C)&&(c != C)) { //c has been assigned a value
            ret1 = c;
        }
        else if((ret1 == A)||(ret1 == B)||(ret1 == C)) {
            //referrence unassigned variable
            runtimeError();
            exit(0);
        }
		ret2 = expr();
        if((ret2 == A)&&(a != A)) {
            ret2 = a;
        }
        else if((ret2 == B)&&(b != B)) {
            ret2 = b;
        }
        else if((ret2 == C)&&(c != C)) {
            ret2 = c;
        }
        else if((ret2 == A)||(ret2 == B)||(ret2 == C)) {
            //unassigned var ref
            runtimeError();
            exit(0);
        }

		return (ret1 * ret2);
		case '/': match('/');
		ret1 = expr();
		//if the value given was an Id (not an integer), replace it with the value currently at that Id
       if((ret1 == A)&&(a != A)) { //a is given, and has been assigned a value
           ret1 = a;
       }
       else if((ret1 == B)&&(b != B)) { //b has been assigned a value
           ret1 = b;
       }
       else if((ret1 == C)&&(c != C)) { //c has been assigned a value
           ret1 = c;
       }
       else if((ret1 == A)||(ret1 == B)||(ret1 == C)) {
           //referrence unassigned variable
           runtimeError();
           exit(0);
       }
		ret2 = expr();
        if((ret2 == A)&&(a != A)) {
            ret2 = a;
        }
        else if((ret2 == B)&&(b != B)) {
            ret2 = b;
        }
        else if((ret2 == C)&&(c != C)) {
            ret2 = c;
        }
        else if((ret2 == A)||(ret2 == B)||(ret2 == C)) {
            //unassigned var reference
            runtimeError();
            exit(0);
        }
		else if(ret2 == 0)
		{ //cannot divide by 0
			runtimeError();
			exit(0); //need this bc method does not exit
		}
		return (ret1 / ret2);
		case 'a': Id();
		return A;
		case 'b': Id();
		return B;
		case 'c': Id();
		return C;
		default: syntaxError();
		return 0;
	}
}
void cons_t() { //FIRST(const) = {0...9}

	switch(lookahead) {
		case '0': match('0');
		break;
		case '1': match('1');
		break;
		case '2': match('2');
		break;
		case '3': match('3');
		break;
		case '4': match('4');
		break;
		case '5': match('5');
		break;
		case '6': match('6');
		break;
		case '7': match('7');
		break;
		case '8': match('8');
		break;
		case '9': match('9');
		break;
		default: syntaxError();
	}
}
void Id() { //FIRST(Id) = {a, b, c}

	switch(lookahead) {
		case 'a': match('a');
		break;
		case 'b': match('b');
		break;
		case 'c': match('c');
		break;
		default: syntaxError();
	}
}

int main(int argc, char **argv)
{
	if(argc < 2) {
		runtimeError();
		return 0;
	}
	strncpy(statement, argv[1], strlen(argv[1]));
	initLookahead(); //scan first val
	program(); //parse

	return 0;
}
