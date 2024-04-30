%{
#include <stdio.h>
int keyword=0;
int operator=0;
int special=0;
int identifier=0;
%}
%%
[int||char||float||return||if||else||do||while] {keyword++;}
[=+\-\*\/^] {operator++;}
[a-zA-Z0-9]+ {identifier++;}
[%/&/$/;] {special++;}

%%
int yywrap(){
	return 1;
}
int main(){
	printf("Enter the code:");
	yylex();
	printf("Keyword: %d \nOperators: %d \nIdentifier: %d \nSpecial symbols: %d",keyword,operator,identifier,special);
	return 0;
}