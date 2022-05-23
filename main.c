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
#else
#include <unistd.h>
#endif

int main() {
	jobList *jbL = NULL, *jobToFind;
	int option, optionEditJob, idContJob = 0;
	
	system("cls");
	jbL = checkDataInFile(jbL,&idContJob);

	// printJobTreeByLevel(jbL, 0);
	// ListJobTreeInOrder(jbL);
	// system("pause");

	do {
		menu(&option);

		switch(option) {
			default:
			case 0: printf("Goodbye!!\n\n");
					break;
			case 1: system("cls");
					ListJobTreeInOrder(jbL);
					system("pause");
					break;
			case 2: system("cls");
					printJobTreeByLevel(jbL,0);
					system("pause");
					break;
			case 3: jobToFind = findJob(jbL);
					system("pause");
					break;
			case 4: insertJob(&jbL,&idContJob);
					break;
			case 5: removeJob(&jbL);
					system("pause");
			break;
			case 6: jobToFind = findJob(jbL);
					system("pause");
					if(jobToFind != NULL) {
						do {
							menuEditJob(&optionEditJob);
							switch(optionEditJob) {
								default:
								case 0: break;
								case 1: listOperations(jobToFind->opL); 
										system("pause"); 
										break;
								case 2: insertOperationNode(jobToFind->opL,&(jobToFind->jb.nOperations));
										system("pause");
										break;
								case 3: removeOperation(jobToFind->opL,&(jobToFind->jb.nOperations));
										system("pause");
										break;
								case 4: editOperation(jobToFind->opL);
										system("pause");
										break;
								case 5: determineShortestTime(jobToFind->opL);
										system("pause");
										break;
								case 6: determineLongestTime(jobToFind->opL);
										system("pause");
										break;
								case 7: determineAverageTime(jobToFind->opL);
										system("pause");
										break;
							}
						}while(optionEditJob != 0);
					}
					break;
			case 7: calcEscalationProposal(jbL);
					break;
		}
	}while(option != 0);
	
	saveDataYN(jbL);

	deallocate(jbL); 
	
	return 0;
}

// case 5: determineShortestTime(jbL->op);
//         break;
// case 6: determineLongestTime(jbL->op);
//         break;
