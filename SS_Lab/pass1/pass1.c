#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main() {
    char label[10], opcode[10], operand[10];
    char code[10], mnemonic[10];
    int locctr, start;
    FILE *input, *output, *optab, *symtab;

    input = fopen("input.txt", "r");
    optab = fopen("optab.txt", "r");
    output = fopen("output.txt", "w");
    symtab = fopen("symtab.txt", "w");

    fscanf(input, "%s\t%s\t%s", label, opcode, operand);

    if (strcmp(opcode, "START") == 0) {
        locctr = atoi(operand);
        start = locctr;
        fprintf(output, "%s\t%s\t%s\n", label, opcode, operand);
        fscanf(input, "%s\t%s\t%s", label, opcode, operand);
    } else
        start = locctr = 0;

    while (strcmp(opcode, "END") != 0) {
        fprintf(output, "%d\t", locctr);

        if (strcmp(label, "") != 0 && strcmp(label, "**") != 0) {
            fprintf(symtab, "%s\t%d\n", label, locctr);
        }

        rewind(optab);
        fscanf(optab, "%s\t%s", code, mnemonic);
        int found = 0;

        while (strcmp(code, "END") != 0) {
            if (strcmp(code, opcode) == 0) {
                locctr += 3;
                found = 1;
                break;
            }
            fscanf(optab, "%s\t%s", code, mnemonic);
        }

        if (!found) {
            if (strcmp(opcode, "WORD") == 0)
                locctr += 3;
            else if (strcmp(opcode, "RESW") == 0)
                locctr += 3 * atoi(operand);
            else if (strcmp(opcode, "RESB") == 0)
                locctr += atoi(operand);
            else
                locctr++;
        }

        fprintf(output, "%s\t%s\t%s\n", label, opcode, operand);
        fscanf(input, "%s\t%s\t%s", label, opcode, operand);
    }

    fprintf(output, "%s\t%s\t%s\n", label, opcode, operand);
    printf("Program length is: %d", locctr - start);

    fclose(input);
    fclose(output);
    fclose(symtab);
    fclose(optab);
}
