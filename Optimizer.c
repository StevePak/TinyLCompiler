/*
 *********************************************
 *  314 Principles of Programming Languages  *
 *  Fall 2014                                *
 *********************************************
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "Instr.h"
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
	instr1 = head;
	instr2 = instr1->next;
	instr3 = instr2->next;

	while(instr3 != NULL)
	{
		switch(instr1->opcode)
		{
			case LOADI:
				if(instr2->opcode == LOAD && instr3->field2 == instr1->field1 && instr3->field3 == instr2->field1)
				{
					switch(instr1->field2)
					{
						case 0:
							switch(instr3->opcode)
							{
								case ADD:
								{
									Instruction *newInstr = (Instruction *) malloc(sizeof(Instruction));
									newInstr->opcode = LOAD;
									newInstr->field1 = instr3->field1;
									newInstr->field2 = instr2->field2;
									newInstr->field3 = 0xFFFFF;
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
									else
										head = newInstr;
									instr1 = newInstr->next;
									break;
								}
								case MUL:
								{
									Instruction *newInstr = (Instruction *) malloc(sizeof(Instruction));
									newInstr->opcode = LOADI;
									newInstr->field1 = instr3->field1;
									newInstr->field2 = instr1->field2;
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
									else
										head = newInstr;
									instr1 = newInstr->next;
									break;
								}
								default:
								{
									instr1 = instr2;
									break;
								}
							}
							break;
						case 1:
							if (instr3->opcode == MUL)
							{
								Instruction *newInstr = (Instruction *) malloc(sizeof(Instruction));
								newInstr->opcode = LOAD;
								newInstr->field1 = instr3->field1;
								newInstr->field2 = instr2->field2;
								newInstr->field3 = 0xFFFFF;
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
								else
									head = newInstr;
								instr1 = newInstr->next;
								break;
							}
							else
								instr1 = instr2;
							break;
						default:
							instr1 = instr2;
							break;
					}
				}
				else
					instr1 = instr2;
			case LOAD:
				if(instr2->opcode == LOADI && instr3->field2 == instr1->field1 && instr3->field3 == instr2->field1)
				{
					switch(instr2->field2)
					{
						case 0:
							switch(instr3->opcode)
							{
								case MUL:
								{
									Instruction *newInstr = (Instruction *) malloc(sizeof(Instruction));
									newInstr->opcode = LOADI;
									newInstr->field1 = instr3->field1;
									newInstr->field2 = instr2->field2;
									newInstr->field3 = 0xFFFFF;
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
									else
										head = newInstr;
									instr1 = newInstr->next;
									break;
								}
								case ADD:
								{
									Instruction *newInstr = (Instruction *) malloc(sizeof(Instruction));
									newInstr->opcode = LOAD;
									newInstr->field1 = instr3->field1;
									newInstr->field2 = instr1->field2;
									newInstr->field3 = 0xFFFFF;
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
									else
										head = newInstr;
									instr1 = newInstr->next;
									break;
								}
								case SUB:
								{
									Instruction *newInstr = (Instruction *) malloc(sizeof(Instruction));
									newInstr->opcode = LOAD;
									newInstr->field1 = instr3->field1;
									newInstr->field2 = instr1->field2;
									newInstr->field3 = 0xFFFFF;
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
									else
										head = newInstr;
									instr1 = newInstr->next;
									break;
								}
								default:
								{
									instr1 = instr2;
									break;
								} 
							}
						case 1:
							if(instr3->opcode == MUL)
							{
								Instruction *newInstr = (Instruction *) malloc(sizeof(Instruction));
								newInstr->opcode = LOAD;
								newInstr->field1 = instr3->field1;
								newInstr->field2 = instr1->field2;
								newInstr->field3 = 0xFFFFF;
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
								else
									head = newInstr;
								instr1 = newInstr->next;
							}
							else
								instr1 = instr2;
							break;
						default:
							instr1 = instr2;
							break;
					}
				}
				else if(instr2->opcode == LOAD && instr3->opcode == SUB && instr3->field2 == instr1->field1 && instr3->field3 == instr2->field1)
				{
					Instruction *newInstr = (Instruction *) malloc(sizeof(Instruction));
					newInstr->opcode = LOADI;
					newInstr->field1 = instr3->field1;
					newInstr->field2 = 0;
					newInstr->field3 = 0xFFFFF;
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
					else
						head = newInstr;
					instr1 = newInstr->next;
				}
				else
					instr1 = instr2;
				break;
			default:
				instr1 = instr2;
				break;
		}
		instr2 = instr1->next;
		instr3 = instr2->next;
	}

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
		if(instr1->opcode == LOADI && instr2->opcode == LOADI && ((instr1->field1 == instr3->field2 && instr2->field1 == instr3->field3) || (instr1->field1 == instr3->field3 && instr2->field1 == instr3->field2)))
		{
			switch(instr3->opcode)
			{
				case ADD:
				{
					Instruction *newInstr = (Instruction *) malloc(sizeof(Instruction));
					newInstr->opcode = LOADI;
					newInstr->field1 = instr3->field1;
					newInstr->field2 = instr1->field2 + instr2->field2;
					newInstr->field3 = 0xFFFFF;
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
					else
						head = newInstr;
					instr1 = newInstr->next;
					break;
				}
				case SUB:
				{
					Instruction *newInstr = (Instruction *) malloc(sizeof(Instruction));
					newInstr->opcode = LOADI;
					newInstr->field1 = instr3->field1;
					newInstr->field2 = instr1->field2 - instr2->field2;
					newInstr->field3 = 0xFFFFF;
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
					else
						head = newInstr;
					instr1 = newInstr->next;
					break;
				}
				case MUL:
				{
					Instruction *newInstr = (Instruction *) malloc(sizeof(Instruction));
					OpCode op = LOADI;
					newInstr->opcode = op;
					newInstr->field1 = instr3->field1;
					newInstr->field2 = instr1->field2 * instr2->field2;
					newInstr->field3 = 0xFFFFF;
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
					else
						head = newInstr;
					instr1 = newInstr->next;
				}
				break;
				default:
				{
					instr1 = instr2;
					break;
				}
			}
		}
		else
			instr1 = instr2;
		instr2 = instr1->next;
		instr3 = instr2->next;
	}

	PrintInstructionList(stdout, head);
	DestroyInstructionList(head);
	return EXIT_SUCCESS;
}
