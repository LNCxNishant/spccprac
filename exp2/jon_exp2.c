#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(){

    //Read Input file and write in an output file
    FILE *input = fopen("input1.txt", "r");
    FILE *output = fopen("jon_exp2Output.txt", "w");

    //if problem in opening file (not necessary)
    if(input == NULL || output == NULL){
        printf("Error in opening file.\n");
        return 1;
    }

    int lineNumber = 1;
    int tokenNumber = 0;

    //List of keywords (Array of pointers)
    const char *keywords[]={
        "int", "main", "if", "else", "do", "while", "include", "stdio", 
        "malloc", "for", "printf", "scanf", "ctype", "stdlib", "string", 
        "math", "void", "char", "getchar", "type", "isalpha", "float", 
        "switch", "case", "break", "exit", "return"
    };

    //Write to the output file stream.
    fprintf(output, "Line No.\tToken No.\tToken Type\tValue\n");

    char ch; //Current Character
    char str[20]; //Buffer to store strings
    int i; 

    while((ch = fgetc(input)) != EOF){

        if(ch == '\n'){
            lineNumber++;
        }
        else if(strchr("+-*/", ch)){
            //Operators detected
            fprintf(output, "%d\t\t\t%d\t\tOperator\t%c\n", lineNumber, tokenNumber++, ch);
        }
        else if(strchr(";{}?@!%", ch)){
            //Special Characters Detected
            fprintf(output, "%d\t\t\t%d\t\tSpecial Symbol\t%c\n", lineNumber, tokenNumber++, ch);
        }
        else if(isdigit(ch)){
            fprintf(output, "%d\t\t\t%d\t\tDigit\t\t%c\n", lineNumber, tokenNumber++, ch);
        }
        else if(isalpha(ch)){
            i = 0;
            str[i++] = ch;
            

            while(isalnum((ch = fgetc(input)))){
                str[i++] = ch;
            }
            str[i] = '\0'; //Terminate string

            //Check if string is keyword
            int isKeyword = 0;
            for(i = 0; i< sizeof(keywords)/sizeof(keywords[0]); i++){
                if(strcmp(str, keywords[i]) == 0){
                    //Str is a keyword(match found)
                    isKeyword = 1;
                    break;
                }
            }

            if(isKeyword){
                fprintf(output, "%d\t\t\t%d\t\tKeyword\t\t%s\n", lineNumber, tokenNumber++, str);
            }
            else{
                fprintf(output, "%d\t\t\t%d\t\tIdentifier\t\t%s\n", lineNumber, tokenNumber++, str);

            }
        }  
    }

    fclose(input);
    fclose(output);

    return 0; 

}