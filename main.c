/**
 * @file main.c
 * @author João Penedos
 * @brief
 * @version 0.9
 * 
 * @copyright Copyright (c) 2022 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <errno.h>

#include "header.h"
#include "colors.h"
#include "functions.c"

#ifdef _WIN32
#include <Windows.h>
# define DIR_SEPARATOR "\\"
#else
#include <unistd.h>
# define DIR_SEPARATOR "/"
#endif

int main() {
	jobList *jbL = NULL, *jobToFind = NULL;
	proposalList *pL = newProposalListNode();
	int option, optionEditJob, idContJob = 0, changeProposalCounter = 0, success = 0;

	system("cls");
	jbL = checkDataInFile(jbL,&idContJob);
	pL = updateEscalationProposal(pL,jbL,&changeProposalCounter);


	do {
		menu(&option);

		switch(option) {
			default:
			case 0: printf("Goodbye!!\n\n");
					break;
			case 1: system("cls");
					ListJobTreeInOrder(jbL);
					pauseProgram();
					break;
			case 2: system("cls");
					printJobTreeByLevel(jbL,0);
					printf(_RESET"\n");
					pauseProgram();
					break;
			case 3: jobToFind = findJob(jbL);
					pauseProgram();
					break;
			case 4: insertJob(&jbL,&idContJob,&success);
					if(success)
						pL = updateEscalationProposal(pL,jbL,&changeProposalCounter);
					break;
			case 5: removeJob(&jbL,&success);
					if(success)
						pL = updateEscalationProposal(pL,jbL,&changeProposalCounter);
					pauseProgram();
			break;
			case 6: jobToFind = findJob(jbL);
					pauseProgram();
					if(jobToFind != NULL) {
						do {
							menuEditJob(&optionEditJob);
							switch(optionEditJob) {
								default:
								case 0: break;
								case 1: listOperations(jobToFind->opL); 
										pauseProgram(); 
										break;
								case 2: insertOperationNode(jobToFind->opL,&(jobToFind->jb.nOperations),&success);
										if(success)
											pL = updateEscalationProposal(pL,jbL,&changeProposalCounter);
										pauseProgram();
										break;
								case 3: removeOperation(jobToFind->opL,&(jobToFind->jb.nOperations),&success);
										if(success)
											pL = updateEscalationProposal(pL,jbL,&changeProposalCounter);
										pauseProgram();
										break;
								case 4: editOperation(jobToFind->opL,&success);
										if(success)
											pL = updateEscalationProposal(pL,jbL,&changeProposalCounter);
										pauseProgram();
										break;
								case 5: determineShortestTime(jobToFind->opL);
										pauseProgram();
										break;
								case 6: determineLongestTime(jobToFind->opL);
										pauseProgram();
										break;
								case 7: determineAverageTime(jobToFind->opL);
										pauseProgram();
										break;
							}
						}while(optionEditJob != 0);
					}
					break;
			case 7: printEscalationProposal(pL);
					pauseProgram();
					break;
		}
	}while(option != 0);
	
	saveDataYN(jbL);

	deallocate(jbL);
	deallocateProposal(pL);
	
	return 0;
}