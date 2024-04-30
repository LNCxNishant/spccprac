#include <stdio.h>
#include <string.h>

#define SUCCESS 1  // Indicates successful parsing
#define FAILED 0   // Indicates failed parsing

// Function declarations for recursive parsing
int E();        // Expression
int Edash();    // Expression Tail
int T();        // Term
int Tdash();    // Term Tail
int F();        // Factor

const char *pt;  // Pointer to traverse the input string
char grammar[64];  // Buffer to store the input expression

int main() {
    // Prompt the user for an arithmetic expression
    printf("Enter an arithmetic expression: ");
    scanf("%s", grammar);

    // Initialize pointer to the start of the expression
    pt = grammar;

    // Display the parsing output
    puts("\nInput\t\tAction");
    
    // Start parsing from the expression and check if the entire input is parsed
    if (E() && *pt == '\0') {
        // If parsing is successful, output success message
        puts("String is successfully parsed");
        return 0;
    } else {
        // If parsing failed, output error message
        puts("Error in parsing string");
        return 1;
    }
}

// E -> T E'
int E() {
    // Display the current action
    printf("%-16s E -> T E'\n", pt);

    // Parse the Term and then the Expression Tail
    if (T() && Edash()) {
        return SUCCESS;  // Parsing was successful
    } else {
        return FAILED;   // Parsing failed
    }
}

// Edash -> + T E' | ε
int Edash() {
    if (*pt == '+') {
        // If the next character is '+', continue parsing
        printf("%-16s E' -> + T E'\n", pt);
        pt++;  // Move to the next character

        // Parse the Term and then the next Expression Tail
        if (T() && Edash()) {
            return SUCCESS;  // Parsing successful
        } else {
            return FAILED;   // Parsing failed
        }
    } else {
        // If no more '+' is found, ε production (empty) indicates end of expression
        printf("%-16s E' -> $\n", pt);
        return SUCCESS;  // Parsing successful
    }
}

// T -> F T'
int T() {
    printf("%-16s T -> F T'\n", pt);

    // Parse the Factor and then the Term Tail
    if (F() && Tdash()) {
        return SUCCESS;  // Parsing successful
    } else {
        return FAILED;   // Parsing failed
    }
}

// Tdash -> * F T' | ε
int Tdash() {
    if (*pt == '*') {
        // If the next character is '*', continue parsing
        printf("%-16s T' -> * F T'\n", pt);
        pt++;  // Move to the next character

        // Parse the Factor and then the next Term Tail
        if (F() && Tdash()) {
            return SUCCESS;  // Parsing successful
        } else {
            return FAILED;   // Parsing failed
        }
    } else {
        // If no more '*' is found, ε production (empty) indicates end of term
        printf("%-16s T' -> $\n", pt);
        return SUCCESS;  // Parsing successful
    }
}

// F -> ( E ) | i
int F() {
    if (*pt == '(') {
        // If the next character is '(', it's a sub-expression
        printf("%-16s F -> ( E )\n", pt);
        pt++;  // Move past '('

        // Parse the inner expression and expect a closing ')'
        if (E() && *pt == ')') {
            pt++;  // Move past ')'
            return SUCCESS;  // Parsing successful
        } else {
            return FAILED;   // Parsing failed
        }
    } else if (*pt == 'i') {
        // If the character is 'i', it's an identifier
        printf("%-16s F -> i\n", pt);
        pt++;  // Move to the next character
        return SUCCESS;  // Parsing successful
    } else {
        return FAILED;  // Parsing failed due to unexpected character
    }
}
