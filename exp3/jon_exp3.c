#include <stdio.h>
#include <string.h>

#define SUCCESS 1
#define FAILED 0

//Grammar
// E -> T E'
// E' -> + T E' | ε
// T -> F T'
// T' -> * F T' | ε
// F -> ( E ) | i

//All non-terminals =  E, E', T, T', F

//Function declarations for recursive parsing
int E();
int Edash();
int T();
int Tdash();
int F();



const char *pt; //Pointer to travse the input string
char grammar[64]; //Input sentence 



int main(){

    printf("Enter an arithmetic Expression: ");
    scanf("%s", grammar);

    //Initialize pointer to start of expression
    pt = grammar;

    puts("\nInput\t\tAction");

    //Start parsing as E() is called.
    if(E() && *pt == '\0'){
        //Success
        puts("String is successfully parsed");
        return 0;
    } else{
        //Error
        printf("Parsing failed");
        return 1;
    }
 
}

//E -> T E'
int E(){
    printf("%-16s E->T E'\n", pt);

    //Parse the term  & then the Expression Tail
    if(T() && Edash()){
        return SUCCESS;
    }else{
        return FAILED;
    }
}

//Edash -> + T E' | ε
int Edash(){
    if(*pt == '+'){
        //if the next character is '+', continue parsing // it is matching the syntax
        printf("%-16s E' -> + T E'\n", pt);
        pt++; 

        //Parse the term & then the next expression tail
        if(T() && Edash()){
            return SUCCESS;
        }else{
            return FAILED;
        }
    }else{
        //If no more '+' is found, ε(empty) production indicates end of expression
        printf("%-16s E' -> $\n", pt);
        return SUCCESS;
    }
}

//T -> F T'
int T(){
    printf("%-16s T -> F T'\n", pt);
    
    if(F() && Tdash()){
        return SUCCESS;
    }else{
        return FAILED;
    }
}

//Tdash -> *F T' | ε
int Tdash(){

    if(*pt == '*'){
        printf("%-16s T' -> * F T'\n", pt);
        pt++;

        if(F() && Tdash()){
            return SUCCESS;
        }else{
            return FAILED;
        }
    }else{
        printf("%-16s T' -> $\n", pt);
        return SUCCESS;
    }
}

// F -> ( E ) | i
int F(){

    if(*pt == '('){
        printf("%-16s F -> ( E )\n", pt);
        pt++;


        if(E() && *pt == ')'){
            pt++;
            return SUCCESS;
        }else{
            return FAILED;
        }
    }else if(*pt == 'i'){
        printf("%-16s F -> i\n", pt);
        pt++;
        return SUCCESS;
    }else{
        return FAILED;
    }
}