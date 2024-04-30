%{
#include <stdio.h>
int capL = 0, smallL = 0, numbers = 0;
%}
%%
[A-Z] {capL++;}
[a-z] {smallL++;}
[0-9] {numbers++;}
%%
int yywrap(){
    return 1;
}
int main()
{
    yyin=fopen("text2.txt","r");
    yylex();
    printf("the file contains - \n %d capital letters  \n %d small letters  \n %d numbers",capL,smallL,numbers);
    return 0;
}