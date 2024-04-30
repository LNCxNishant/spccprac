%{
#include <stdio.h>
int comment_lines = 0;
%}

%option noyywrap

%%

"/*"([^*]|\*+[^*/])*\*+"/" { comment_lines++; }

"//".* { comment_lines++; }

.|\n

%%

int main() {
     yyin=fopen("text2.txt","r");
     yylex();
     printf("the file contains - \n %d comments",comment_lines);
    return 0;
    
}
