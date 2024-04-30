#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){

    char label[10], opcode[10], operand[10], mnemonic[10], locctr[10], mlabel[10];

    FILE *fp1, *fp2, *fp3, *fp4, *fp5;

    fp1 = fopen("input.txt", "r");
    fp2 = fopen("mot.txt", "r");
    fp3 = fopen("output.txt", "r");
    fp4 = fopen("outTable.txt","w");
    fp5 = fopen("BT.txt", "w"); //Base Registers

    fscanf(fp3, "%s %s %s %s", locctr, label, opcode, operand);
    fscanf(fp3, "%s %s %s %s", locctr, label, opcode, operand);

    fprintf(fp5, "Y  %c%c 00 00 00", operand[2], operand[3]);

    fscanf(fp3, "%s %s %s %s", locctr, label, opcode, operand);
    
    while(strcmp(opcode, "END") !=  0){

        if(strcmp(opcode, "DC")==0){
            fprintf(fp4, "%s\t%c\n", locctr, operand[2]);
        }
        else if(strcmp(opcode, "DS") == 0){
            fprintf(fp4, "%s\t_\n", locctr);
        }
        else{
            fscanf(fp2, "%s %s",mnemonic, mlabel);
            while(strcmp(mnemonic, "end")!= 0){
                if(strcmp(opcode, mnemonic) == 0){
                    fprintf(fp4,"%s\t%s\n", mlabel, operand);
                    break;
                }
                fscanf(fp2, "%s %s", mnemonic, mlabel);
            }
            rewind(fp2);
        }
        fscanf(fp3, "%s %s %s %s", locctr, label, opcode, operand);
    }
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);
    fclose(fp5);

    return 0;
}