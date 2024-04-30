#include <stdio.h>
#include <string.h>

int tempCount = 1; // Counter for generating unique temporary variable names

void generateAssignmentCode() {
    // Example expression for assignment code generation
    const char expression[] = "a = b * c + d";
    printf("Expression: %s\n", expression);

    // Split the expression into left-hand side (LHS) and right-hand side (RHS)
    char lhs[10], rhs[50];
    sscanf(expression, "%s = %[^\n]", lhs, rhs);

    // Split the RHS into terms to identify operations and operands
    char* terms[10];
    int termCount = 0;
    char* term = strtok(rhs, " ");
    while (term != NULL) {
        terms[termCount++] = term;
        term = strtok(NULL, " ");
    }

    // Generate three-address code
    char code[1000] = ""; // Buffer to store generated code
    char temp[10]; // Temporary variable name
    for (int i = 0; i < termCount; i++) {
        if (strcmp(terms[i], "+") == 0 || strcmp(terms[i], "*") == 0) {
            // Create a new temporary variable
            sprintf(temp, "t%d", tempCount++);
            // Generate TAC for the operation
            sprintf(code + strlen(code), "%s = %s %s %s;\n", temp, terms[i - 1], terms[i], terms[i + 1]);
            // Update the next operand to use the temporary variable
            terms[i + 1] = temp;
        }
    }

    // Assign the final result to the LHS
    sprintf(code + strlen(code), "%s = %s;", lhs, terms[termCount - 1]);
    printf("Three-address code:\n%s\n", code); // Display generated TAC
}

void generateConditionalCode() {
    // Example expression for conditional code generation
    const char expression[] = "if (a < b) then c = d + e else c = d - e";
    printf("Expression: %s\n", expression);

    // Extract condition, then-part, and else-part
    char condition[20], thenPart[50], elsePart[50];
    sscanf(expression, "if %[^(] then %[^\n] else %[^\n]", condition, thenPart, elsePart);

    // Create labels for branching in TAC
    char trueLabel[10], endLabel[10];
    sprintf(trueLabel, "L%d", tempCount++);
    sprintf(endLabel, "L%d", tempCount++);

    // Generate TAC for conditional branching
    char code[1000] = "";
    sprintf(code, "if %s goto %s;\n%s goto %s;\n%s: %s;\n%s: ", condition, trueLabel, elsePart, endLabel, trueLabel, thenPart, endLabel);

    printf("Three-address code:\n%s\n", code); // Display generated TAC
}

void generateCopyCode() {
    // Example expression for copy operation
    const char expression[] = "x = y";
    printf("Expression: %s\n", expression);

    char target[10], source[10];
    sscanf(expression, "%s = %s", target, source);

    // Generate TAC for simple copy operation
    printf("Three-address code:\n%s = %s;\n", target, source);
}

void generateIndexedAssignmentCode() {
    // Example expression for indexed assignment
    const char expression[] = "x[2] = y + 5";
    printf("Expression: %s\n", expression);

    char arrayName[10], index[10], operation[50];
    sscanf(expression, "%s[%[^]]] = %[^\n]", arrayName, index, operation);

    // Split the operation into operand and operator
    char* operationParts[3];
    int operationPartCount = 0;
    char* opPart = strtok(operation, " ");
    while (opPart != NULL) {
        operationParts[operationPartCount++] = opPart;
        opPart = strtok(NULL, " ");
    }

    // Generate TAC for indexed assignment
    char code[1000] = "";
    char intermediateVar[10];
    sprintf(intermediateVar, "t%d", tempCount++);

    sprintf(code, "%s = %s %s %s;\n%s[%s] = %s;", intermediateVar, operationParts[0], operationParts[1], operationParts[2], arrayName, index, intermediateVar);

    printf("Three-address code:\n%s\n", code);
}

int main() {
    int choice;

    while (1) {
        // Display menu for user input
        printf("Generate three-address code for: 1)Assignment 2)Conditional 3)Indexed Assignment 4)Copy 5)Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline character

        switch (choice) {
            case 1:
                generateAssignmentCode();
                break;
            case 2:
                generateConditionalCode();
                break;
            case 3:
                generateIndexedAssignmentCode();
                break;
            case 4:
                generateCopyCode();
                break;
            case 5:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Please enter a number from 1 to 5.\n");
        }

        printf("\n");
    }
}
