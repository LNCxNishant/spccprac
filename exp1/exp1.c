#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
    char string[100];
    printf("enter an exprression \n");
    scanf("%s",&string);
    printf("\n\nSymbl table \n\n type\t\t symbol\t\taddress\n");
    for(int i=0; string[i]!='\0';i++){
        char a =string[i];
        if (a>='a'&&a<='z'|| a>='A'&& a<='Z'){
            printf("identifier \t");

        }
        else if(a>='0'&& a<='9') {
            printf("constants \t");

        }
        else if(a=='+'|| a=='-'|| a=='*'|| a=='/'|| a=='%'|| a=='^')
        {
            printf("operator \t");
        }
        else{
            printf("special symbol\t");

        }
        printf("%c \t %p \n", string[i],(void*)&string[i]);

    }

    return 0;
}