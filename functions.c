/**
 * @file functions.c
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

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

job *inicializarJob() {
	job *p;
	p = (job *) malloc( sizeof(job));
	
	if(p==NULL) {
		system("cls");
		printf("Can't create list\n\n");
		system("pause");
		return(NULL);
	}
	else {
		(*p).nOperations = 0;
		(*p).op = inicializarOperation();
		return(p);
	}
}
//#####################################################################################################
operation *inicializarOperation() {
	operation *p;
	p = (operation *) malloc( sizeof(operation));
	
	if(p==NULL) {
		system("cls");
		printf("Can't create list\n\n");
		system("pause");
		return(NULL);
	}
	else {
		(*p).id=0;
		(*p).next=NULL;
		return(p);
	}
}
//#####################################################################################################
void checkDataInFile(operation *op, int *idCont, int *nOperations) {
	operation *opP;
	FILE *f_JOB = fopen("dados.txt","r");
	char symb ;
    unsigned char symbI;
	int i = 0, cont = 0, success = 0, arrayM[100], arrayT[100];

    if(f_JOB != NULL) {
		do {
			if((symb = getc(f_JOB)) != EOF) {
				i = cont = 0;
				while ((symb=getc(f_JOB))!='\n') {
					symbI = (int) symb;
					if(symbI >= '0' && symbI <='9') {
						arrayM[i] = symbI - '0';
						cont++;
						i++;
					}
				}
				i=0;
				while ((symb=getc(f_JOB))!='\n') {
					symbI = (int) symb;
					if(symbI >= '0' && symbI <='9') {
						arrayT[i] = symbI - '0';
						i++;
					}
				}

				opP=(operation *)malloc(sizeof(operation));
				(*opP).id = 0;
				(*opP).quantMachines = 0;
				(*opP).next=NULL;

				while((*op).next != NULL) {
					op = (*op).next;
				}

				(*nOperations)++;
				(*idCont)++;
				(*op).id = (*idCont);
				(*op).quantMachines = cont;
				(*op).machineAndTime = (int *)malloc(sizeof(int[2][(*op).quantMachines]));
				for(i=0; i < (*op).quantMachines; i++) {
					(*op).machineAndTime[0*(*op).quantMachines + i] = arrayM[i];
					(*op).machineAndTime[1*(*op).quantMachines + i] = arrayT[i];
				}
				(*op).next = opP;
				success = 0;
			}
			else{
				success = 1;
			}
		}while(success == 0);
	}

    fclose(f_JOB);
}
//#####################################################################################################
void insertNewOperation(operation *op, int *idCont, int *nOperations) {
	operation *auxOp;
    char *input;
    int i, j;

	auxOp = (operation *)malloc(sizeof(operation));
	
	system("cls");
	if(auxOp==NULL) { 
		printf("There is no more memory space. It is impossible to insert\n\n");
		system("pause");
	}
	else {
		system("cls");
		(*auxOp).id = 0;
		(*auxOp).quantMachines = 0;
        (*auxOp).next = NULL;
		while(((*op).next) != NULL) {
			op = (*op).next;
		}

		(*nOperations)++;
		(*idCont)++;
		(*op).id = (*idCont);
		printf("How many machines can be used for this operation: ");
		fgets(input, sizeof(input), stdin);
		(*op).quantMachines = strtol(input, NULL, 0);
		(*op).machineAndTime = (int *)malloc(sizeof(int[2][(*op).quantMachines]));
		for (i = 0; i < 2; ++i) {
			for (j = 0; j < (*op).quantMachines; ++j) {
				if(i==0) {
					printf("What is the id of the machine you want to use: ");
					fgets(input, sizeof(input), stdin);
					(*op).machineAndTime[i*(*op).quantMachines + j] = strtol(input, NULL, 10);
				}
				else {
					printf("How long will machine %d take: ", (*op).machineAndTime[0*(*op).quantMachines + j]);
					fgets(input, sizeof(input), stdin);
					(*op).machineAndTime[i*(*op).quantMachines + j] = strtol(input, NULL, 10);
				}
			}
		}
		(*op).next = auxOp;
	}
}
//#####################################################################################################
void listNode(operation *op) {
	int i = 0, j = 0;

	printf("Id - (%d)\n",(*op).id);
	printf("Machine - (");
	for (j = 0; j < (*op).quantMachines; ++j) {
		if(((*op).quantMachines - j) == 1)
			printf("%d",(*op).machineAndTime[0*(*op).quantMachines + j]);
		else
			printf("%d,",(*op).machineAndTime[0*(*op).quantMachines + j]);
	}
	printf(")\nTime - (");
	for (j = 0; j < (*op).quantMachines; ++j) {
		if(((*op).quantMachines - j) == 1)
			printf("%d",(*op).machineAndTime[1*(*op).quantMachines + j]);
		else
			printf("%d,",(*op).machineAndTime[1*(*op).quantMachines + j]);
	}
	printf(")\n\n");
}

//#####################################################################################################
void listOperations(operation *op, int nOperations) {
	operation *x;
	int j;
	system("cls");

	if((*op).next==NULL) {
		printf("No operations in the list");
	}
	else {
		printf("This job has %d operations\n", nOperations);
		while((*op).next != NULL) {
			x=op;
			listNode(x);
			op=(*op).next;
		}
	}
	printf("\n\n");
	system("pause");
}
//#####################################################################################################
void removeOperation(job **jobList, int *nOperations) {
	operation *x, *y, *atras, *frente, *auxOp;
	int j, intElemRetirar;
	char elemRetirar[40];

	system("cls");
	y=(*jobList)->op;
	
	if(((*y).next)==NULL) { 
		printf("No operations in the list"); 
	}
	else {
		printf("What is the code whose operation you want to remove?\n");
		if(fgets(elemRetirar, sizeof(elemRetirar), stdin)) {
			elemRetirar[strcspn(elemRetirar, "\n")] = 0;
			intElemRetirar = strtol(elemRetirar, NULL, 0);
		}

		if(intElemRetirar == (*(*jobList)->op).id) {
			system ("cls");
			
			(*nOperations)--;
			printf("The element has been removed\n");
			x = (*jobList)->op;
			listNode(x);
			system("pause");
			(*jobList)->op=(*(*jobList)->op).next;
			free(y);
		}
		else {
			auxOp=(*jobList)->op;
			while((intElemRetirar != (*auxOp).id) && ((*(*auxOp).next).next!=NULL)) {
				atras=auxOp;
				auxOp=(*auxOp).next;
				frente=(*auxOp).next;
			}
			
			if(intElemRetirar == (*auxOp).id) {
				(*atras).next=frente;
				system ("cls");
				
				(*nOperations)--;
				printf("The element has been removed\n");
				x = auxOp;
				listNode(x);
				system("pause");
				free(auxOp);
			}
			else {
				system("cls"); 
				printf("The element with code %s does not exist in the list", elemRetirar);
			}
		}
	}
}
//#####################################################################################################
void editOperation(operation *operationList) {
	operation *auxOp, *x;
	int i, j, intElemEditar, *machArray;
	char elemEditar[40], *input;

	system("cls");
	
	if(((*operationList).next) == NULL) { 
		printf("No operations in the list"); 
	}
	else {
		printf("What is the code whose operation you want to edit?\n");
		if(fgets(elemEditar, sizeof(elemEditar), stdin)) {
			elemEditar[strcspn(elemEditar, "\n")] = 0;
			intElemEditar = strtol(elemEditar, NULL, 0);
		}

		if(intElemEditar == (*operationList).id) {
			system ("cls");
			printf("Element to edit\n");
			printf("Id - (%d)\n",(*operationList).id);
			printf("Machine Quant. - (%d)\nMachine - (",(*operationList).quantMachines);
			for (j = 0; j < (*operationList).quantMachines; ++j) {
				if(((*operationList).quantMachines - j) == 1)
					printf("%d",(*operationList).machineAndTime[0*(*operationList).quantMachines + j]);
				else
					printf("%d,",(*operationList).machineAndTime[0*(*operationList).quantMachines + j]);
			}
			printf(")\nTime - (");
			for (j = 0; j < (*operationList).quantMachines; ++j) {
				if(((*operationList).quantMachines - j) == 1)
					printf("%d",(*operationList).machineAndTime[1*(*operationList).quantMachines + j]);
				else
					printf("%d,",(*operationList).machineAndTime[1*(*operationList).quantMachines + j]);
			}
			printf(")\n\n");
			// x = operationList;
			// listNode(x);
			free((*operationList).machineAndTime);

			printf("How many machines can be used for this operation: ");
			fgets(input, sizeof(input), stdin);
			(*operationList).quantMachines = strtol(input, NULL, 0);
			(*operationList).machineAndTime = (int *)malloc(sizeof(int[2][(*operationList).quantMachines]));
			for (i = 0; i < 2; ++i) {
				for (j = 0; j < (*operationList).quantMachines; ++j) {
					if(i==0) {
						printf("What is the id of the machine you want to use: ");
						fgets(input, sizeof(input), stdin);
						(*operationList).machineAndTime[i*(*operationList).quantMachines + j] = strtol(input, NULL, 10);
					}
					else {
						printf("How long will machine %d take: ", (*operationList).machineAndTime[0*(*operationList).quantMachines + j]);
						fgets(input, sizeof(input), stdin);
						(*operationList).machineAndTime[i*(*operationList).quantMachines + j] = strtol(input, NULL, 10);
					}
				}
			}
		}
		else {
			while((intElemEditar != (*operationList).id) && (*operationList).next != NULL) {
				operationList = (*operationList).next;
			}
			
			if(intElemEditar == (*operationList).id) {
				system ("cls");
				printf("Element to edit\n");
				printf("Id - (%d)\n",(*operationList).id);
				printf("Machine Quant. - (%d)\nMachine - (",(*operationList).quantMachines);
				for (j = 0; j < (*operationList).quantMachines; ++j) {
					if(((*operationList).quantMachines - j) == 1)
						printf("%d",(*operationList).machineAndTime[0*(*operationList).quantMachines + j]);
					else
						printf("%d,",(*operationList).machineAndTime[0*(*operationList).quantMachines + j]);
				}
				printf(")\nTime - (");
				for (j = 0; j < (*operationList).quantMachines; ++j) {
					if(((*operationList).quantMachines - j) == 1)
						printf("%d",(*operationList).machineAndTime[1*(*operationList).quantMachines + j]);
					else
						printf("%d,",(*operationList).machineAndTime[1*(*operationList).quantMachines + j]);
				}
				printf(")\n\n");
				// x = operationList;
				// listNode(x);
				free((*operationList).machineAndTime);

				printf("How many machines can be used for this operation: ");
				fgets(input, sizeof(input), stdin);
				(*operationList).quantMachines = strtol(input, NULL, 0);
				(*operationList).machineAndTime = (int *)malloc(sizeof(int[2][(*operationList).quantMachines]));
				for (i = 0; i < 2; ++i) {
					for (j = 0; j < (*operationList).quantMachines; ++j) {
						if(i==0) {
							printf("What is the id of the machine you want to use: ");
							fgets(input, sizeof(input), stdin);
							(*operationList).machineAndTime[i*(*operationList).quantMachines + j] = strtol(input, NULL, 10);
						}
						else {
							printf("How long will machine %d take: ", (*operationList).machineAndTime[0*(*operationList).quantMachines + j]);
							fgets(input, sizeof(input), stdin);
							(*operationList).machineAndTime[i*(*operationList).quantMachines + j] = strtol(input, NULL, 10);
						}
					}
				}
			}
			else {
				system("cls"); 
				printf("The element with code %s does not exist in the list", elemEditar);
			}
		}
	}
}
//#####################################################################################################
void determineShortestTime(operation *op) {
	int i = 0, j = 0, soma = 0, min, mach;

	system("cls");
	if((*op).next==NULL) {
		printf("No operations in the list");
	}
	else {
		printf("Machines used to obtain the shortest result\n");
		while((*op).next != NULL) { 
			min = 99999;
			for (j = 0; j < (*op).quantMachines; ++j) {
				if((*op).machineAndTime[1*(*op).quantMachines + j] < min) {
					min = (*op).machineAndTime[1*(*op).quantMachines + j];
					mach = (*op).machineAndTime[0*(*op).quantMachines + j];
				}
			}
			printf("%d", mach);
			if((*(*op).next).next != NULL)
				printf("->");

			soma = soma + min;
			op=(*op).next;
		}
		printf("\nMinimum number of time units needed to complete the job: %d", soma);
	}
	printf("\n\n");
	system("pause");
}
//#####################################################################################################
void determineLongestTime(operation *op) {
	int i = 0, j = 0, soma = 0, max, mach;

	system("cls");
	if((*op).next==NULL) {
		printf("No operations in the list");
	}
	else {
		printf("Machines used to obtain the longest result\n");
		while((*op).next != NULL) { 
			max = 0;
			for (j = 0; j < (*op).quantMachines; ++j) {
				if((*op).machineAndTime[1*(*op).quantMachines + j] > max) {
					max = (*op).machineAndTime[1*(*op).quantMachines + j];
					mach = (*op).machineAndTime[0*(*op).quantMachines + j];
				}
			}
			printf("%d", mach);
			if((*(*op).next).next != NULL)
				printf("->");

			soma = soma + max;
			op=(*op).next;
		}
		printf("\nMaximum number of time units needed to complete the job: %d", soma);
	}
	printf("\n\n");
	system("pause");
}
//#####################################################################################################
void determineAverageTime(operation *op) {
	// nested loops com quantidades diferentes baseado 
	// na quantidade de opercoes do joe e tamanhos (de loop) diferentes 
	// baseados nas quantidades de maquinas de cada operacao
}
//#####################################################################################################
void saveDataInFile(operation *op) {
	FILE *f_JOB = fopen("dados.txt","w");
	int j;

    if(f_JOB != NULL) {
		if((*op).next==NULL) {
			printf("No data to put in the file");
		}
		else {
			while((*op).next != NULL) {
				for (j = 0; j < (*op).quantMachines; ++j) {
					if( j == 0)
						fprintf(f_JOB,"(%d,",(*op).machineAndTime[0*(*op).quantMachines + j]);
					else if(((*op).quantMachines - j) != 1)
						fprintf(f_JOB,"%d,",(*op).machineAndTime[0*(*op).quantMachines + j]);
					else
						fprintf(f_JOB,"%d)\n",(*op).machineAndTime[0*(*op).quantMachines + j]);
				}
				for (j = 0; j < (*op).quantMachines; ++j) {
					if( j == 0)
						fprintf(f_JOB,"[%d,",(*op).machineAndTime[1*(*op).quantMachines + j]);
					else if(((*op).quantMachines - j) != 1)
						fprintf(f_JOB,"%d,",(*op).machineAndTime[1*(*op).quantMachines + j]);
					else
						fprintf(f_JOB,"%d]\n",(*op).machineAndTime[1*(*op).quantMachines + j]);
				}
				op=(*op).next;
			}
		}
		printf("List of Jobs and Operations was successfully loaded into the file (dados.txt)!!\n");
	}

    fclose(f_JOB);
}
//#####################################################################################################
//#####################################################################################################
void menu(int *opcao) {
    int i, success;
	char *endptr, buf[1024];
	
	do {
		system("cls");

		printf("%c",201); for(i = 0; i < 69; i++) printf("%c",205); printf("%c\n",187);
		_printf_p("%1$c                               MENU                                  %1$c \n"
				  "%1$c   0 - Exit                                                          %1$c \n"
				  "%1$c   1 - Insert Operation                                              %1$c \n"
				  "%1$c   2 - List Operations               5 - Determine Shortest Time     %1$c \n"
				  "%1$c   3 - Remove Operation              6 - Determine Longest Time      %1$c \n"
				  "%1$c   4 - Edit Operation                7 - Determine Average Time      %1$c \n",186);
		printf("%c",200); for(i = 0; i < 69; i++) printf("%c",205); printf("%c\nOption: ",188);

		if (!fgets(buf, sizeof(buf), stdin)) {
			success = 0;
		}
		errno = 0; // reset error number
		(*opcao) = strtol(buf, &endptr, 10);
		if (errno == ERANGE) {
			printf("The number entered is either too large or too small.\n\n");
			system("pause");
			success = 0;
		}
		else if (((*opcao) > 7) || ((*opcao) < 0)) {
			printf("Please enter a number between 0 and 7.\n\n");
			system("pause");
			success = 0;
		}
		else if (endptr == buf)	{
			// no character was read.
			success = 0;
		}
		else if ((*endptr) && (*endptr != '\n')) {
			// *endptr is neither end of string nor newline, so we didn't convert the *whole* input.
			success = 0;
		}
		else {
			success = 1;
		}
	}while(!success);
}