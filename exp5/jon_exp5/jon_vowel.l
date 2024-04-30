%{
#include <stdio.h>
int vow = 0, con = 0;
%}
%%
[aeiouAEIOU] {vow++}
[a-zA-Z] {con++}
%%
int yywrap(){
    return 1;
}
int main(){
    printf("Enter the string: ");
    yylex();
    printf("Vowels: %d \nConsonants: %d\n", vow, con);
}