#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (){

    char string[100];
    printf("Enter an expression \n");
    scanf("%s",string);

    printf ("\n\n Symbol Table \n\n Type \t\t Symbol \t\t Address \n");

    for (int i=0; string[i]!='\0'; i++) {

        char a = string[i];

        if (a>='0'&& a<='9'){
            printf("Constant \t");
        }
        else if (a >= 'a' && a <= 'z' || a >= 'A' && a <= 'Z') {
            printf ("Identifier \t");
        }
        else if (a == '+' || a == '-' || a == '*' || a == '/' || a == '%' || a == '^' || a == '=') {
            printf("Operator \t");
        }
        else {
            printf ("Special Symbol \t");
        }

        printf ("%c \t %p \n", string[i], (void*)&string[i]);
    }

    return 0;
}
