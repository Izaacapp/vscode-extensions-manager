/*
 * pm0_vm.c
 * P-Machine (PM/0) Virtual Machine Implementation
 * COP 3402: Systems Software
 * 
 * Authors: Devon Villalona
 *          Izaac Plambeck
 * 
 * Description:
 * This program implements a virtual machine (PM/0) that reads and executes
 * instructions from an input file.
 * 
 * Compilation:
 * gcc -Wall -o vm vm.c
 * 
 * Execution:
 * ./vm modified_input.txt
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Memory size for the PM/0 CPU and Activation Record Markers (AR_Markers) 
#define MEM_SIZE 500 
// Memory for the PM/0 CPU (Program Address Space) and Activation Record Markers (AR_Markers) 
int PAS[MEM_SIZE];
int AR_Markers[MEM_SIZE]; 
int current_lex_level = 0; 
int stack_base_idx = 10; 

FILE *input_file, *output_file;

// Initial register values for the PM/0 CPU
const int INITIAL_BP = 499;
const int INITIAL_SP = 500;
const int INITIAL_PC = 10;
// Initial values for the registers of the PM/0 CPU 
int bp; 
int sp; 
int pc; 
// Variables to hold the current instruction values
int opcode; 
int lex_level; 
int modifier; 

// Function to find the base L levels down
int find_base(int base_pointer, int level) {
    int arb = base_pointer;
    while (level > 0) {
        arb = PAS[arb];
        level--;
    }
    return arb;
}

// Function to get the operation name based on the opcode and modifier
void fetch_opcode_name(char op_name[4]) {
    switch (opcode) {
        case 1: strcpy(op_name, "LIT"); break;
        case 2: 
            switch (modifier) {
                case 0: strcpy(op_name, "RTN"); break;
                case 1: strcpy(op_name, "ADD"); break;
                case 2: strcpy(op_name, "SUB"); break;
                case 3: strcpy(op_name, "MUL"); break;
                case 4: strcpy(op_name, "DIV"); break;
                case 5: strcpy(op_name, "EQL"); break;
                case 6: strcpy(op_name, "NEQ"); break;
                case 7: strcpy(op_name, "LSS"); break;
                case 8: strcpy(op_name, "LEQ"); break;
                case 9: strcpy(op_name, "GTR"); break;
                case 10: strcpy(op_name, "GEQ"); break;
            }
            break;
        case 3: strcpy(op_name, "LOD"); break;
        case 4: strcpy(op_name, "STO"); break;
        case 5: strcpy(op_name, "CAL"); break;
        case 6: strcpy(op_name, "INC"); break;
        case 7: strcpy(op_name, "JMP"); break;
        case 8: strcpy(op_name, "JPC"); break;
        case 9: strcpy(op_name, "SYS"); break;
    }
}

// Function to print the state of the VM
void display_vm_state() {
    char op_name[4];
    fetch_opcode_name(op_name);

    // Print the executed instruction and the state of the VM
    printf("  %-4s %2d %2d    %3d    %4d    %4d", op_name, lex_level, modifier, pc, bp, sp);
    fprintf(output_file, "  %-4s %2d %2d    %3d    %4d    %4d", op_name, lex_level, modifier, pc, bp, sp);

    // Print the current stack state
    for (int i = INITIAL_SP - 1; i >= sp; i--) {
        if (AR_Markers[i] == 1) {
            printf(" | ");
            fprintf(output_file, " | ");
        }
        printf(" %d", PAS[i]);
        fprintf(output_file, " %d", PAS[i]);
    }
    printf("\n");
    fprintf(output_file, "\n");
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    input_file = fopen(argv[1], "r");
    output_file = fopen("./output.txt", "w");

    if (input_file == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    // Load instructions into the PAS starting at index 10
    int i = 10;
    while (fscanf(input_file, "%d %d %d", &opcode, &lex_level, &modifier) != EOF) {
        PAS[i] = opcode;
        PAS[i + 1] = lex_level;
        PAS[i + 2] = modifier;
        i += 3;
    }
    fclose(input_file);

    // Initialize registers
    bp = INITIAL_BP;
    sp = INITIAL_SP;
    pc = INITIAL_PC;

    printf("                PC      BP      SP      Stack\n");
    fprintf(output_file, "                PC      BP      SP      Stack\n");
    printf("Initial values: %3d     %4d     %4d\n\n", pc, bp, sp);
    fprintf(output_file, "Initial values: %3d     %4d     %4d\n\n", pc, bp, sp);

    int halt = 0;

    while (!halt) {
        // Fetch cycle
        opcode = PAS[pc];
        lex_level = PAS[pc + 1];
        modifier = PAS[pc + 2];
        pc += 3;

        // Execute cycle
        switch (opcode) {
            case 1: // LIT
                sp--;
                PAS[sp] = modifier;
                break;
            case 2: // OPR
                switch (modifier) {
                    case 0: // RTN
                        sp = bp + 1;
                        bp = PAS[sp - 2];
                        pc = PAS[sp - 3];
                        break;
                    case 1: // ADD
                        PAS[sp + 1] += PAS[sp];
                        sp++;
                        break;
                    case 2: // SUB
                        PAS[sp + 1] -= PAS[sp];
                        sp++;
                        break;
                    case 3: // MUL
                        PAS[sp + 1] *= PAS[sp];
                        sp++;
                        break;
                    case 4: // DIV
                        PAS[sp + 1] /= PAS[sp];
                        sp++;
                        break;
                    case 5: // EQL
                        PAS[sp + 1] = (PAS[sp + 1] == PAS[sp]);
                        sp++;
                        break;
                    case 6: // NEQ
                        PAS[sp + 1] = (PAS[sp + 1] != PAS[sp]);
                        sp++;
                        break;
                    case 7: // LSS
                        PAS[sp + 1] = (PAS[sp + 1] < PAS[sp]);
                        sp++;
                        break;
                    case 8: // LEQ
                        PAS[sp + 1] = (PAS[sp + 1] <= PAS[sp]);
                        sp++;
                        break;
                    case 9: // GTR
                        PAS[sp + 1] = (PAS[sp + 1] > PAS[sp]);
                        sp++;
                        break;
                    case 10: // GEQ
                        PAS[sp + 1] = (PAS[sp + 1] >= PAS[sp]);
                        sp++;
                        break;
                }
                break;
            case 3: // LOD
                sp--;
                PAS[sp] = PAS[find_base(bp, lex_level) - modifier];
                break;
            case 4: // STO
                PAS[find_base(bp, lex_level) - modifier] = PAS[sp];
                sp++;
                break;
            case 5: // CAL
                PAS[sp - 1] = find_base(bp, lex_level); // static link (SL)
                PAS[sp - 2] = bp;          // dynamic link (DL)
                PAS[sp - 3] = pc;          // return address (RA)
                bp = sp - 1;
                pc = modifier;
                AR_Markers[bp] = 1; // Mark the start of a new activation record
                break;
            case 6: // INC
                sp -= modifier;
                break;
            case 7: // JMP
                pc = modifier;
                break;
            case 8: // JPC
                if (PAS[sp] == 0) {
                    pc = modifier;
                }
                sp++;
                break;
            case 9: // SYS
                switch (modifier) {
                    case 1:
                        printf("Output result is: %d\n", PAS[sp]);
                        fprintf(output_file, "Output result is: %d\n", PAS[sp]);
                        sp++;
                        break;
                    case 2:
                        sp--;
                        printf("Please enter an integer: ");
                        fprintf(output_file, "Please enter an integer: ");
                        scanf("%d", &PAS[sp]);
                        fprintf(output_file, "%d\n", PAS[sp]);
                        break;
                    case 3:
                        halt = 1;
                        break;
                }
                break;
        }

        // Print the stack trace
        display_vm_state();
    }

    fclose(output_file);
    return 0;
}
