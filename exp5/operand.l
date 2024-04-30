%{
#include <stdio.h>
int operator=0,operand=0;
%}
%%
[+\-\*\/\%^] {operator++;}
[a-zA-Z0-9]+ {operand++;}
%%
int yywrap(){
	return 1;
}
int main(){
	printf("Enter the string:");
	yylex();
	printf("Operators: %d \nOperands: %d\n",operator,operand);
	return 0;
}