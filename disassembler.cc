#include <stdio.h>
#include <string.h>

#define LIMIT 40

void printAssembly(char filename[]);
void printAdd(int);
void printAnd(int);
void printBr(int, int);
void printJmpRet(int);
void printJsrJsrr(int, int);
void printLd(int, int);
void printLdi(int, int);
void printLdr(int);
void printLea(int, int);
void printNot(int);
void printRti(int);
void printSt(int, int);
void printSti(int, int);
void printStr(int);
void printTrap(int);

//**************************************************
//Make sure to comment main out before submitting
//**************************************************

int main()
{
	char filename[] = "test2.hex";
	printAssembly(filename);
}



void printAssembly(char filename[])
{
	FILE *infile;	
	infile = fopen(filename, "r");
	
	if (infile == NULL)	{
		printf("File %s is null.\n", filename);			
	} else {
    int count = 0;
    int instruction = 0;
    int PC = 0;
    //Read the initial PC as an integer and save
    fscanf(infile, "%X", &PC); 
    count++;
    //While not at end of file and not over the limit
    while (fscanf(infile, "%x", &instruction) != EOF && count < LIMIT) {
      count++;  //Count number of lines for limit
      
      //Remove the print and put your code here
      //Increment the PC
      PC++;
      //Figure out the oppcode from the high order 4 bits of the instruction
      int opcode = (instruction >> 12) & 15;
      //Use a big if or switch to call the appropriate print function.
      switch(opcode) {
        case 0: printBr(instruction, PC);
                break;
        case 1: printAdd(instruction);
                break;
        case 2: printLd(instruction, PC);
                break;
        case 3: printSt(instruction, PC);
                break;
        case 4: printJsrJsrr(instruction, PC);
                break;
        case 5: printAnd(instruction);
                break;
        case 6: printLdr(instruction);
                break;
        case 7: printStr(instruction);
                break;
        case 8: printRti(instruction);
                break;
        case 9: printNot(instruction);
                break;
        case 10: printLdi(instruction, PC);
                break;
        case 11: printSti(instruction, PC);
                break;
        case 12: printJmpRet(instruction);
                break;
        case 14: printLea(instruction, PC);
                break;
        case 15: printTrap(instruction);
                break;
        default: break;    
      }
      //Pass the function the full instruction and the PC, but only if necessary.
      
    }
  }
}

  void printAdd(int instruction) {
    printf("ADD\t");
    int dr = (instruction >> 9) & 7;
    printf("R%X, ", dr);
    int sr1 = (instruction >> 6) & 7;
    printf("R%X, ", sr1);
    int t = (instruction >> 5) & 1;
    if (t == 0) {
        int sr2 = (instruction & 7);
        printf("R%X\n", sr2);
    }
    else {
        int imm5 = (instruction & 31);
        int y = (imm5 >> 4) & 1;
        if (y == 1) {
            imm5 = ~imm5;
            imm5 = (imm5 & 15);
            imm5 = ~imm5;
        }
        printf("#%d\n", imm5);
    }
  }

  void printAnd(int instruction) {
    printf("AND\t");
    int dr = (instruction >> 9) & 7;
    printf("R%X, ", dr);
    int sr1 = (instruction >> 6) & 7;
    printf("R%X, ", sr1);
    int t = (instruction >> 5) & 1;
    if (t == 0) {
        int sr2 = (instruction & 7);
        printf("R%X\n", sr2);
    }
    else {
        int imm5 = (instruction & 31);
        int y = (imm5 >> 4) & 1;
        if (y == 1) {
            imm5 = ~imm5;
            imm5 = (imm5 & 15);
            imm5 = ~imm5;
        }
        printf("#%d\n", imm5);
    }
  }

  void printBr(int instruction, int PC) {
    printf("BR");
    int nzp = (instruction >> 9) & 7;
    if ((nzp & 4) == 4) {
        printf("N");
    }
    if ((nzp & 2) == 2) {
        printf("Z");
    }
    if ((nzp & 1) == 1) {
        printf("P");
    }
    printf("\t");
    int offSet9 = (instruction & 511);
    int y = ((instruction >> 8) & 1);
    if (y == 1) {
        offSet9 = ~offSet9;
        offSet9 = (offSet9 & 255);
        offSet9 = ~offSet9;
    }
    int off = (PC + offSet9);
    printf("x%X\n", off);
  }

  void printJmpRet(int instruction) {
    int br = ((instruction >> 6) & 7);
    if (br == 7) {
        printf("RET\n");
    }
    else {
        printf("JMP\tR%X\n", br);
    }
  }

  void printJsrJsrr(int instruction, int PC) {
    int s = ((instruction >> 11) & 1);
    if (s == 1) {
        printf("JSR\t");
        int offSet11 = (instruction & 2047);
        int y = ((instruction >> 10) & 1);
        if (y == 1) {
            offSet11 = ~offSet11;
            offSet11 = (offSet11 & 1023);
            offSet11 = ~offSet11;
        }
        int off = (PC + offSet11);
        printf("x%X\n", off);
    }
    else {
        int br = ((instruction >> 6) & 7); 
        printf("JSRR\tR%X\n", br);
    }
  }

  void printLd(int instruction, int PC) {
    printf("LD\t");
    int dr = (instruction >> 9) & 7;
    printf("R%X, ", dr);
    int offSet9 = (instruction & 511);
    int y = ((instruction >> 8) & 1);
    if (y == 1) {
        offSet9 = ~offSet9;
        offSet9 = (offSet9 & 255);
        offSet9 = ~offSet9;
    }
    int off = (PC + offSet9);
    printf("x%X\n", off); 
  }

  void printLdi(int instruction, int PC) {
    printf("LDI\t");
    int dr = (instruction >> 9) & 7;
    printf("R%X, ", dr);
    int offSet9 = (instruction & 511);
    int y = ((instruction >> 8) & 1);
    if (y == 1) {
        offSet9 = ~offSet9;
        offSet9 = (offSet9 & 255);
        offSet9 = ~offSet9;
    }
    int off = (PC + offSet9);
    printf("x%X\n", off); 
  }

  void printLdr(int instruction) {
    printf("LDR\t");
    int dr = (instruction >> 9) & 7;
    printf("R%X, ", dr);
    int sr = (instruction >> 6) & 7;
    printf("R%X, ", sr);
    int offSet6 = (instruction & 63);
    int y = ((instruction >> 5) & 1);
    if (y == 1) {
        offSet6 = ~offSet6;
        offSet6 = (offSet6 & 31);
        offSet6 = ~offSet6;
    }
    printf("#%d\n", offSet6);
  }

  void printLea(int instruction, int PC) {
    printf("LEA\t");
    int dr = (instruction >> 9) & 7;
    printf("R%X, ", dr);
    int offSet9 = (instruction & 511);
    int y = ((instruction >> 8) & 1);
    if (y == 1) {
        offSet9 = ~offSet9;
        offSet9 = (offSet9 & 255);
        offSet9 = ~offSet9;
    }
    int off = (PC + offSet9);
    printf("x%X\n", off);
  }

  void printNot(int instruction) {
    printf("NOT\t");
    int dr = (instruction >> 9) & 7;
    printf("R%X, ", dr);
    int sr = (instruction >> 6) & 7;
    printf("R%X\n", sr);
  }

  void printRti(int instruction) {
    printf("RTI\n");
  }

  void printSt(int instruction, int PC) {
    printf("ST\t");
    int sr = (instruction >> 9) & 7;
    printf("R%X, ", sr);
    int offSet9 = (instruction & 511);
    int y = ((instruction >> 8) & 1);
    if (y == 1) {
        offSet9 = ~offSet9;
        offSet9 = (offSet9 & 255);
        offSet9 = ~offSet9;
    }
    int off = (PC + offSet9);
    printf("x%X\n", off);
  }

  void printSti(int instruction, int PC) {
    printf("STI\t");
    int sr = (instruction >> 9) & 7;
    printf("R%X, ", sr);
    int offSet9 = (instruction & 511);
    int y = ((instruction >> 8) & 1);
    if (y == 1) {
        offSet9 = ~offSet9;
        offSet9 = (offSet9 & 255);
        offSet9 = ~offSet9;
    }
    int off = (PC + offSet9);
    printf("x%X\n", off);
  }

  void printStr(int instruction) {
    printf("STR\t");
    int sr = (instruction >> 9) & 7;
    printf("R%X, ", sr);
    int br = (instruction >> 6) & 7;
    printf("R%X, ", br);
    int offSet6 = (instruction & 63);
    int y = ((instruction >> 5) & 1);
    if (y == 1) {
        offSet6 = ~offSet6;
        offSet6 = (offSet6 & 31);
        offSet6 = ~offSet6;
    }
    printf("#%d\n", offSet6);
  }

  void printTrap(int instruction) {
    int trap = (instruction & 15);
    switch(trap) {
        case 0: printf("GETC\n");
                break;
        case 1: printf("OUT\n");
                break;
        case 2: printf("PUTS\n");
                break;
        case 3: printf("IN\n");
                break;
        case 4: printf("PUTSP\n");
                break;
        case 5: printf("HALT\n");
                break;
        default: break;
    }
  }


