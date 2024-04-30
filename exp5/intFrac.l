%{
#include <stdio.h>
int pos_int = 0,pos_frac = 0;
int neg_int = 0,neg_frac = 0;
%}
%%
[+]?[0-9]* {pos_int++;}
[+]?[0-9]*\.[0-9]+ {pos_frac++;}
[-][0-9]* {neg_int++;}
[-][0-9]*\.[0-9]+ {neg_frac++;}
%%
int yywrap(){
	return 1;
}
int main(){
	printf("Enter the number:\n");
	yylex();
	printf("Positive Integer: %d\n",pos_int);
	printf("Positive Fracion: %d\n",pos_frac);
	printf("Negative Integer: %d\n",neg_int);
	printf("Negative Fraction: %d\n",neg_frac);
	return 0;
}