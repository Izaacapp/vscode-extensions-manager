/*
 * vm.c
 * P-Machine (PM/0) Virtual Machine Implementation
 * COP 3402: Systems Software
 * 
 * Authors: [Devon Villalona]
 *          [Izaac Plambeck]
 * 
 * Description:
 * This program implements a virtual machine (PM/0) that reads and executes
 * instructions from an input file specified as a command line argument.
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

#define MEM_SIZE 500 // Memory size for the virtual machine

typedef struct {
    int val;           // Value stored in the memory cell
    int is_ar_start;   // Indicator if it's the start of an activation record
} mem_cell;

mem_cell memory[MEM_SIZE]; // Array representing memory cells
int cur_lex_level = 0;     // Current lexical level
int prog_start = 10;       // Start address of the program

const int INIT_BP = 499;   // Initial base pointer
const int INIT_SP = 500;   // Initial stack pointer
const int INIT_PC = 10;    // Initial program counter

int bp, sp, pc;            // Machine registers
int op, l, m;              // Instruction fields

FILE *in_file_ptr, *out_file_ptr; // File pointers for input and output

// Function to find the base address of a given level
int find_base(int bp, int l) {
    int arb = bp;
    while (l > 0) {
        arb = memory[arb].val;
        l--;
    }
    return arb;
}

// Function to get the operation name based on the opcode
void get_operation_name(char op_name[4]) {
    switch (op) {
        case 1: strcpy(op_name, "LIT"); break;
        case 2: 
            switch (m) {
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

// Function to print the current state of the stack
void print_stack_trace() {
    char operation_name[4];
    get_operation_name(operation_name);

    // Print the executed instruction and the state of the VM
    printf("%-4s %2d %2d    %-5d %-5d %-5d", operation_name, l, m, pc, bp, sp);
    fprintf(out_file_ptr, "%-4s %2d %2d    %-5d %-5d %-5d", operation_name, l, m, pc, bp, sp);

    // Print each value in the stack
    for (int i = INIT_SP - 1; i >= sp; i--) {
        if (memory[i].is_ar_start) {
            printf(" | ");
            fprintf(out_file_ptr, " | ");
        }
        printf("%d ", memory[i].val);
        fprintf(out_file_ptr, "%d ", memory[i].val);
    }
    printf("\n");
    fprintf(out_file_ptr, "\n");
}

// Initialize memory cells to default values
void initialize_memory() {
    for (int i = 0; i < MEM_SIZE; i++) {
        memory[i].val = 0;
        memory[i].is_ar_start = 0;
    }
}

// Load the program from the input file into memory
void load_program(const char* filename) {
    in_file_ptr = fopen(filename, "r");
    if (!in_file_ptr) {
        printf("Error opening file\n");
        exit(1);
    }

    int i = 10;
    while (fscanf(in_file_ptr, "%d %d %d", &op, &l, &m) != EOF) {
        memory[i].val = op;
        memory[i + 1].val = l;
        memory[i + 2].val = m;
        i += 3;
    }
    fclose(in_file_ptr);
}

// Execute the loaded program
void execute_program() {
    int halt = 0;

    while (!halt) {
        op = memory[pc].val;
        l = memory[pc + 1].val;
        m = memory[pc + 2].val;
        pc += 3;

        switch (op) {
            case 1: // Load literal
                sp--;
                memory[sp].val = m;
                break;
            case 2: // Arithmetic operations
                switch (m) {
                    case 0: // Return
                        sp = bp + 1;
                        bp = memory[sp - 2].val;
                        pc = memory[sp - 3].val;
                        break;
                    case 1: // Add
                        memory[sp + 1].val += memory[sp].val;
                        sp++;
                        break;
                    case 2: // Subtract
                        memory[sp + 1].val -= memory[sp].val;
                        sp++;
                        break;
                    case 3: // Multiply
                        memory[sp + 1].val *= memory[sp].val;
                        sp++;
                        break;
                    case 4: // Divide
                        memory[sp + 1].val /= memory[sp].val;
                        sp++;
                        break;
                    case 5: // Equal
                        memory[sp + 1].val = (memory[sp + 1].val == memory[sp].val);
                        sp++;
                        break;
                    case 6: // Not equal
                        memory[sp + 1].val = (memory[sp + 1].val != memory[sp].val);
                        sp++;
                        break;
                    case 7: // Less than
                        memory[sp + 1].val = (memory[sp + 1].val < memory[sp].val);
                        sp++;
                        break;
                    case 8: // Less than or equal
                        memory[sp + 1].val = (memory[sp + 1].val <= memory[sp].val);
                        sp++;
                        break;
                    case 9: // Greater than
                        memory[sp + 1].val = (memory[sp + 1].val > memory[sp].val);
                        sp++;
                        break;
                    case 10: // Greater than or equal
                        memory[sp + 1].val = (memory[sp + 1].val >= memory[sp].val);
                        sp++;
                        break;
                }
                break;
            case 3: // Load value from memory
                sp--;
                memory[sp].val = memory[find_base(bp, l) - m].val;
                break;
            case 4: // Store value to memory
                memory[find_base(bp, l) - m].val = memory[sp].val;
                sp++;
                break;
            case 5: // Call procedure
                memory[sp - 1].val = find_base(bp, l);
                memory[sp - 2].val = bp;
                memory[sp - 3].val = pc;
                bp = sp - 1;
                pc = m;
                memory[bp].is_ar_start = 1;
                break;
            case 6: // Increment stack pointer
                sp -= m;
                break;
            case 7: // Jump to address
                pc = m;
                break;
            case 8: // Conditional jump
                if (memory[sp].val == 0) {
                    pc = m;
                }
                sp++;
                break;
            case 9: // System operations
                switch (m) {
                    case 1:
                        printf("Output result is: %d\n", memory[sp].val);
                        fprintf(out_file_ptr, "Output result is: %d\n", memory[sp].val);
                        sp++;
                        break;
                    case 2:
                        sp--;
                        printf("Please enter an integer: ");
                        fprintf(out_file_ptr, "Please enter an integer: ");
                        scanf("%d", &memory[sp].val);
                        fprintf(out_file_ptr, "%d\n", memory[sp].val);
                        break;
                    case 3:
                        halt = 1;
                        break;
                }
                break;
        }

        print_stack_trace();
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    out_file_ptr = fopen("./output.txt", "w");

    initialize_memory();
    load_program(argv[1]);

    bp = INIT_BP;
    sp = INIT_SP;
    pc = INIT_PC;

    printf("%21s%5s%5s%8s\n", "PC", "BP", "SP", "Stack");
    fprintf(out_file_ptr, "%21s%5s%5s%8s\n", "PC", "BP", "SP", "Stack");
    printf("Initial values:%6d%5d%5d\n\n", pc, bp, sp);
    fprintf(out_file_ptr, "Initial values:%6d%5d%5d\n\n", pc, bp, sp);

    execute_program();

    fclose(out_file_ptr);
    return 0;
}