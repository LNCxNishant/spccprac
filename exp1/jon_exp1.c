#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

// Structure of Symbol Entry(each row) in Symbol table
struct SymbolEntry{
    char sybmol;
    void *address;
    char type[40];
};


//find Symbol
int findSymbol(const struct SymbolEntry symbolTable[], int symbolCount, char symbolToFind){
    int foundIndex = -1;

    for(int i = 0; i<symbolCount; i++){
        if(symbolTable[i].sybmol == symbolToFind){
            foundIndex = i;
            break;
        }
    }

    return foundIndex;
}

//Insert Function
void insertSymbol(struct SymbolEntry symbolTable[], int* symbolCount, char newSymbol ){
    
    //Check if symbol exist already
    if(findSymbol(symbolTable, *symbolCount, newSymbol)>=0){
        printf("Symbol Duplicate");
        return;
    }

    //Symbol not found, so need to add it. Allocate Memory for it.
    symbolTable[*symbolCount].address = malloc(sizeof(int));



    //Determine type of symbol
    if(isalpha(newSymbol) || isdigit(newSymbol)){
        strcpy(symbolTable[*symbolCount].type, "identifier");
    }
    else{
        strcpy(symbolTable[*symbolCount].type, "operator");
    }

    symbolTable[*symbolCount].sybmol = newSymbol;
    (*symbolCount)++;
    printf("Success!!\n");
    
}

void displaySymbolTable(const struct SymbolEntry symbolTable[], int symbolCount){

    printf("\nSymbol \t Address \t Type\n");

    for(int i = 0; i<symbolCount; i++){
        printf("%c \t %p \t %s\n", symbolTable[i].sybmol, symbolTable[i].address, symbolTable[i].type);
    }
}

//Delete
void deleteSymbol(struct SymbolEntry symbolTable[], int *symbolCount, char symbolToDelete){
    int foundIndex = findSymbol(symbolTable, *symbolCount, symbolToDelete);

    if(foundIndex == -1){
        printf("Symbol not found.\n");
        return;
    }

    free(symbolTable[foundIndex].address);

    //Shift the remaining symbols
    for(int i = foundIndex; i< *symbolCount-1; i++){
        symbolTable[i] = symbolTable[i+1];
    }

    (*symbolCount)--;
    printf("Deletion Successfull!\n");
}

//Search & Display Symbol
void searchAndDisplaySymbol(const struct SymbolEntry symbolTable[], int symbolCount, char symbolToSearch){
    int foundIndex = findSymbol(symbolTable, symbolCount, symbolToSearch);

    if(foundIndex == -1){
        printf("Symbol not found.\n");
    }
    else{
        printf("\nSymbol Information\n");
        printf("Symbol: %c\n", symbolTable[foundIndex].sybmol);
        printf("Address: %p\n", symbolTable[foundIndex].address);
    }
}

//Modify 
void modifySymbol(struct SymbolEntry symbolTable[], int symbolCount, char symbolToModify){
    int foundIndex = findSymbol(symbolTable, symbolCount, symbolToModify);

    if(foundIndex == -1){
        printf("Symbol not found.\n");
        return;
    }

    strcpy(symbolTable[foundIndex].type, "modified");
    printf("Modification Successfull!!");
}


int main(){
    struct SymbolEntry symbolTable[50]; // Array of Symbol Entries (i.e a table) 
    
    int symbolCount = 0; //Count number of entries in symbol table 
    int choice;
    char newSymbol;

    do{
        //Menu
        printf("\nSymbol Table Operations\n");
        printf(" 1. Insert\n 2. Disply Table\n 3. Delete\n 4. Search\n 5. Modify\n 6. Exit\n");
        printf("Your Choice: ");
        scanf("%d", &choice);

        //Perform Desired Operation
        switch(choice){
            case 1:
                printf("Enter Symbol to Insert: ");
                scanf(" %c", &newSymbol);
                insertSymbol(symbolTable, &symbolCount, newSymbol);
                break;
            
            case 2:
                displaySymbolTable(symbolTable, symbolCount);
                break;

            case 3:
                printf("Enter Symbol to Delete: ");
                scanf(" %c", &newSymbol);
                deleteSymbol(symbolTable, &symbolCount, newSymbol);
                break;
            
            case 4: 
                printf("Enter Symbol to Search: ");
                scanf(" %c", &newSymbol);
                searchAndDisplaySymbol(symbolTable, symbolCount, newSymbol);
                break;
            
            case 5:
                printf("Enter Symbol to Modify: ");
                scanf(" %c", &newSymbol);
                modifySymbol(symbolTable, symbolCount, newSymbol);
                break;
            
            case 6: 
                for(int i =0; i<symbolCount; i++){
                    free(symbolTable[i].address);
                }
                printf("Exit!!");
                break;
            
            default:
                printf("Invalid choice.\n");
        }

    }while(choice != 6); ///Exit, when 6 is choses.

    return 0;
}