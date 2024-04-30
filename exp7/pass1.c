#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){

    char label[10], opcode[10], operand[10], mnemonic[10];
    int locctr = 0;

    FILE *fp1, *fp2, *fp3, *fp4;

    fp1 = fopen("input.txt","r");
    fp2 = fopen("mot.txt", "r");
    fp3 = fopen("output.txt", "w");
    fp4 = fopen("st.txt", "w");

    //START opcode
    fscanf(fp1, "%s %s %s", label, opcode, operand); 
    fprintf(fp3, "%d %s %s %s\n", locctr, label, opcode, operand);

    //USING opcode
    fscanf(fp1, "%s %s %s", label, opcode, operand);
    fprintf(fp3, "%d %s %s %s\n", locctr, label, opcode, operand);

    while(strcmp(opcode, "END") != 0){

        if(strcmp(opcode, "DC") == 0 || strcmp(opcode, "DS")==0){
            fprintf(fp4, "%s %d\n", label, locctr);
            fprintf(fp3, "%d %s %s %s\n", locctr, label, opcode, operand);
            locctr +=4; //Assume they are taking 4 byte space
        }
        else{
            fscanf(fp2, "%s", mnemonic);
            fprintf(fp3, "%d %s %s %s\n", locctr, label, opcode, operand);
            while(strcmp(mnemonic, "end")!=0){
                if(strcmp(opcode, mnemonic)==0){
                    locctr += 4;
                    break;
                }
                fscanf(fp2, "%s", mnemonic); //Search till opcode is found in mnemonic table
            }
            rewind(fp2); //Bring back to start of mnemonic file.
        }

        fscanf(fp1, "%s %s %s", label, opcode, operand);
    }    

    //END opcode
    fprintf(fp3, "%d %s %s %s\n", locctr, label, opcode, operand);

    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);

    return 0;
}