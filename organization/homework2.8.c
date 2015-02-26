/* File: disassem.c
   Purpose: Disassemble MIPS machine instructions to assembly
   Note: This program only works for R-type and J-type instructions
         as specified in Fig. 2.1 (p. 64) given the book.
         It works properly on linprog (or little endian machine).

   To compile
         gcc -o disassem disassem.c 
   To read instructions from a file, use the following
         ./disassem  < file-name
   History: January 13, 2007 - Xiuwen Liu, Created based on Prof. Whalley's
            program
            January 21, 2015 - Xiuwen Liu, Updated for the fifth edition of 
            the textbook
*/

#include <stdio.h>


struct insttypeR {
  // For R-format instructions, the op code is 0
  int funct;
  char mnem[6];
  char format;
};

struct insttypeR instsR[] =
   { { 32,   "add", 'R' },
     { 34,   "sub", 'R' },
     { 33,  "addu", 'R' },
     { 35,  "subu", 'R' },
     { 24,  "mult", 'R' },
     { 25, "multu", 'R' },
     { 26,   "div", 'R' },
     { 27,  "divu", 'R' },
     { 16,  "mfhi", 'R' },
     { 18,  "mflo", 'R' },
     { 36,   "and", 'R' },
     { 37,    "or", 'R' },
     { 39,   "nor", 'R' },
     {  0,   "sll", 'R' },
     {  2,   "srl", 'R' },
     { 42,   "slt", 'R' },
     { 43,  "sltu", 'R' },
     {  8,    "jr", 'R' },
     { -1, "unimp", 'U' } };

struct insttype {
  int opcode;
  char mnem[6];
  char format;
};

struct insttype insts[] =
  { {  2,     "j", 'J' },
    {  3,   "jal", 'J' },
    {  8,   "addi", 'I'},
    { 35,   "lw", 'I'},
	{ 43,	"sw", 'I'}, // Started adding from here
	{ 33,	"lh", 'I'},
	{ 37,	"lhu", 'I'},
	{ 41,	"sh", 'I'},
	{ 32,	"lb", 'I'},
	{ 36,	"lbu", 'I'},
	{ 40,	"sb", 'I'},
	{ 48,	"ll", 'I'},
	{ 56,	"sc", 'I'},
	{ 15,	"lui", 'I'},
	{ 12,	"andi", 'I'},
	{ 13,	"ori", 'I'},
	{ 4,	"beq", 'I'},
	{ 5,	"bne", 'I'},
	{ 10,	"slti", 'I'},
	{ 11,	"sltiu", 'I'}, // To here
    { -1, "unimp", 'U' } };

/*
 * findfunc - finds the location of the R-instruction in the array instsR
 */
int findfunct(unsigned int funct)
{
   int i;

   for (i = 0; instsR[i].funct != -1; i++)
     if (instsR[i].funct == funct)
       return i;
   return i;
}

int findop(unsigned int op)
{
   int i;
   
   for (i = 0; insts[i].opcode != -1; i++)
     if (insts[i].opcode == op)
       return i;
   return i;
}


/*
 * extend - extends a 16-bit signed value to a 32-bit signed value
 */
int extend(uimmed)
unsigned short uimmed;
{
   short simmed;
   simmed = uimmed;
   return (int) simmed;
}

int main(int argc, char *argv[])
{
   struct R_format {
     unsigned funct : 6;
     unsigned shamt : 5;
     unsigned    rd : 5;
     unsigned    rt : 5;
     unsigned    rs : 5;
     unsigned    op : 6;
   };

   struct J_format {
     unsigned addr : 26;
     unsigned   op :  6;
   };

   struct I_format {
     unsigned immed : 16;
     unsigned rt : 5;
     unsigned rs : 5;
     unsigned op : 6;
   };

   union inst_format {
     unsigned int hexvalue;
     struct R_format rform;
     struct J_format jform;
     struct I_format iform;
   };
   
   int index, addr;
   union inst_format inst;
   
   /* print headings */
   printf("machine code\t         \tassembly instructions\n");
   printf("------------\t         \t---------------------\n");

   /* while there are instructions to read */
   addr = 0;
   while (scanf("%x", &inst.hexvalue) != EOF) {
      /* print machine code  */
      printf(" 0x%08x \t          \t", inst.hexvalue);
      if (inst.rform.op == 0) {
	/* For R-type instructions */
	index = findfunct(inst.rform.funct);
	/* print the mnemonic */
	printf("%s", instsR[index].mnem);
	if (instsR[index].format != 'U') {
	  switch (inst.rform.funct) {
	  case 0:
	  case 2:
	    printf("\t$%u, $%u, %u", inst.rform.rd, inst.rform.rt,
		   inst.rform.shamt);
	    break;
	    
	  case 16:
	  case 18:
	    printf("\t$%u", inst.rform.rd);
	    break;
	    
	  case 24:
	  case 25:
	  case 26:
	  case 27:
	    printf("\t$%u,$%u", inst.rform.rs, inst.rform.rt);
	    break;
	    
	  case 8:
	    printf("\t$%u", inst.rform.rs);
	    break;
	    
	  default:
	    printf("\t$%u, $%u, $%u", inst.rform.rd, inst.rform.rs,
		   inst.rform.rt);
	  }
	}
	else {
	  printf("\t(Not implemented)");
	}
      }
      else {
	/* This includes I-format and J-format instructions */
         index = findop(inst.jform.op);
	 printf("%s", insts[index].mnem);

	 /* print the operands */
	 switch (insts[index].format) {
         case 'U':
	   printf("\t(Not implemented)");
	   break;
	 case 'I':
	   switch(inst.iform.op) {
		   case 43: // added cases for the "Not implemented"
		   case 33:
		   case 37:
		   case 41:
		   case 32:
		   case 36:
		   case 40:
		   case 48:
		   case 56:
	   case 35:
	     printf("\t$%u, %d($%u)", inst.iform.rt, 
		    (extend(inst.iform.immed)),
		    inst.iform.rs);
	     break;
	   case 15: // for "lui rt, imm."
		 printf("\t$%u, %d", inst.iform.rt, (extend(inst.iform.immed)));
		 break;
	   case 12:
	   case 13:
	   case 10:
	   case 11: // for "andi rt, rs, imm.
		 printf("\t$%u, $%u, %d", inst.iform.rt, inst.iform.rs, (extend(inst.iform.immed)));
		 break;
	   case 4:
	   case 5: // for "beq rs, rt, offset"
		 printf("\t$%u, $%u, %d", inst.iform.rs, inst.iform.rt, (extend(inst.iform.immed)));
		 break;
	   default:
	     printf("\t$%u, $%u, %d", inst.iform.rt, inst.iform.rs, 
		    extend(inst.iform.immed));
	     break;
	   }
	   break;
         case 'J':
	   printf("\t%d", inst.jform.addr);  
	   break;
	   
         default:
	   fprintf(stderr, "illegal format type %c\n", insts[index].format);
         }
      }
      printf("\n");
   }
   return (0);
}
