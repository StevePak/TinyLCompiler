/*
 *********************************************
 *  314 Principles of Programming Languages  *
 *  Fall 2014                                *
 *********************************************
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "InstrUtils.h"
#include "Utils.h"

int main()
{
	Instruction *head;
	Instruction *instr1, *instr2, *instr3;
	int opt_flag, opt_calc;


	head = ReadInstructionList(stdin);

        /* ---  FIRST: ALGEBRAIC SIMPLIFICATION PASS --- */

	if (!head) {
		ERROR("No instructions\n");
		exit(EXIT_FAILURE);
	}

	/* YOUR CODE GOES HERE */


        /* --- SECOND: CONSTANT FOLDING PASS --- */

	if (!head) {
		ERROR("No instructions\n");
		exit(EXIT_FAILURE);
	}

	/* YOUR CODE GOES HERE */
	instr1 = head;
	instr2 = instr1->next;
	instr3 = instr2->next;

	while(instr3 != NULL)
	{
		if(instr1->opcode == LOADI)
		{
			if(instr2->opcode == LOADI)
			{
				switch(instr3->opcode)
				{
					case ADD:
						Instruction *newInstr = (Instruction *) malloc(sizeof(Instruction));
						newInstr->opcode = LOADI;
						newInstr->field1 = instr3->field1;
						newInstr->field2 = instr1->field2 + instr2->field2;
						newInstr->field3 = 0;
						newInstr->next = instr3->next;
						newInstr->prev = instr1->prev;
						free(instr1);
						free(instr2);
						free(instr3);
						if(newInstr->next != NULL)
						{
							newInstr->next->prev = newInstr;
						}
						if(newInstr->prev != NULL)
						{
							newInstr->prev->next = newInstr;
						}
						instr1 = 
				}
			}
		}
	}


	PrintInstructionList(stdout, head);
	DestroyInstructionList(head);
	return EXIT_SUCCESS;
}
