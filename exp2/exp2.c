#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main() {
    // Open the input and output files
    FILE *input = fopen("input1.txt", "r");
    FILE *output = fopen("output2.txt", "w");
    
    // If file can't be opened, exit with error
    if (input == NULL || output == NULL) {
        printf("Error opening file.\n");
        return 1;
    }
    
    // Initialize counters for lines and tokens
    int lineNumber = 1;
    int tokenNumber = 0;

    // Define a list of keywords
    const char *keywords[] = {
        "int", "main", "if", "else", "do", "while", "include", "stdio", 
        "malloc", "for", "printf", "scanf", "ctype", "stdlib", "string", 
        "math", "void", "char", "getchar", "type", "isalpha", "toascii", 
        "switch", "case", "break", "exit", "return"
    };

    // Write the header to the output file
    fprintf(output, "Line No.\tToken No.\tToken Type\tValue\n");

    char ch; // Character buffer to hold current character
    char str[20]; // Buffer to build strings (e.g., identifiers)
    int i; // Index for building strings

    // Loop through all characters in the input file
    while ((ch = fgetc(input)) != EOF) {
        if (ch == '\n') { 
            // Increment line number when encountering a newline
            lineNumber++;
        } else if (strchr("+-*/", ch)) {
            // Detect operators and write to the output file
            fprintf(output, "%d\t\t%d\t\tOperator\t%c\n", lineNumber, tokenNumber++, ch);
        } else if (strchr(";{}()?@!%", ch)) {
            // Detect special symbols and write to the output file
            fprintf(output, "%d\t\t%d\t\tSpecial Symbol\t%c\n", lineNumber, tokenNumber++, ch);
        } else if (isdigit(ch)) {
            // Detect digits and write to the output file
            fprintf(output, "%d\t\t%d\t\tDigit\t\t%c\n", lineNumber, tokenNumber++, ch);
        } else if (isalpha(ch)) {
            // Build an identifier or keyword
            i = 0; // Reset index for string building
            str[i++] = ch; // Start with the first alphabetic character
            while (isalnum((ch = fgetc(input))) && ch != ' ') {
                // Build a string while reading alphanumeric characters
                str[i++] = ch;
            }
            str[i] = '\0'; // Null-terminate the string

            // Check if the built string is a keyword
            int isKeyword = 0;
            for (i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++) {
                if (strcmp(str, keywords[i]) == 0) {
                    isKeyword = 1; // It's a keyword
                    break;
                }
            }

            // Write to the output file depending on whether it's a keyword or an identifier
            if (isKeyword) {
                fprintf(output, "%d\t\t%d\t\tKeyword\t\t%s\n", lineNumber, tokenNumber++, str);
            } else {
                fprintf(output, "%d\t\t%d\t\tIdentifier\t%s\n", lineNumber, tokenNumber++, str);
            }
        }
    }

    // Close the files to avoid memory leaks
    fclose(input);
    fclose(output);

    return 0; // Exit the program successfully
}
