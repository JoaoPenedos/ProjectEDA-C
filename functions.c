#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <errno.h>
#include "header.h"

job *inicializarJob() {
	job *p;
	p = (job *) malloc( sizeof(job));
	
	if(p==NULL) {
		system("cls");
		printf("E impossivel criar a estrutura\n\n");
		system("pause");
		return(NULL);
	}
	else {
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
		printf("E impossivel criar a lista\n\n");
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
// machine *inicializarMachine() {
// 	machine *p;
// 	p = (machine *) malloc( sizeof(machine));	
// 	if(p==NULL) {
// 		system("cls");
// 		printf("E impossivel criar a lista\n\n");
// 		system("pause");
// 		return(NULL);
// 	}
// 	else {
// 		(*p).id=0;
// 		(*p).OnOff=0;
// 		(*p).next=NULL;
// 		return(p);
// 	}
// }
//#####################################################################################################
void lerOp(operation *opP) {
    char input[50];
    int cont = 0, i, j;

	//snprintf((*m).codigo,sizeof((*m).codigo),"M_%d",lastCodM);

	(*opP).id = 1;

    printf("Qunatas maquinas vao poder ser utilizadas para esta operacao: ");
	fgets(input, sizeof(input), stdin);
	cont = strtol(input, NULL, 0);

	(*opP).quantMachines = cont;
	(*opP).machineAndTime = (int *)malloc(sizeof(int[2][cont]));
	for (i = 0; i < 2; ++i) {
		for (j = 0; j < cont; ++j) {
			if(i==0) {
				printf("Qual o id da maquina que pertende usar: ");
				fgets(input, sizeof(input), stdin);
				(*opP).machineAndTime[i*cont + j] = strtol(input, NULL, 0);
			}
			else {
				printf("Qual o tempo que a %d maquina vai demorar: ", (*opP).machineAndTime[0*cont + j]);
				fgets(input, sizeof(input), stdin);
				(*opP).machineAndTime[i*cont + j] = strtol(input, NULL, 0);
			}
		}
	}

    (*opP).next=NULL;
}
//#####################################################################################################
void verificarDadosNoFicheiro(job *jobList) {
	operation *opP, *auxOp;
	FILE *f_JOB = fopen("test.txt","r");
	char symb ;
    unsigned char symbI;
	int x = 4, i = 0, cont = 0, success = 0, arrayM[100], arrayT[100];

    if(f_JOB != NULL) {
		auxOp = jobList->op;
		do {
			if((symb = getc(f_JOB)) != EOF) {
				i=0;
				cont=0;
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

				while((*auxOp).next != NULL) {
					auxOp = (*auxOp).next;
				}

				(*auxOp).id = 1;
				(*auxOp).quantMachines = cont;
				(*auxOp).machineAndTime = (int *)malloc(sizeof(int[2][cont]));
				(*auxOp).next = (operation *)malloc(sizeof(operation));
				(*(*auxOp).next).next = NULL;

				for(i=0; i < cont; i++) {
					(*auxOp).machineAndTime[0*cont + i] = arrayM[i];
					// printf("+%c",(*auxOp).machineAndTime[0*cont + i]);
					(*auxOp).machineAndTime[1*cont + i] = arrayT[i];
					// printf("-%c\n",(*auxOp).machineAndTime[1*cont + i]);
				}
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
void insertNewOperation(job *jobList) {
    char *input;
    int cont = 0, i, j;
	operation *auxOp;

	auxOp = jobList->op;
	
	system("cls");
	if(auxOp==NULL) { 
		printf("Nao existe mais espaço em memoria. E impossivel inserir\n\n");
		system("pause");
	}
	else {		
		system("cls");

		while(((*auxOp).next) != NULL) {
			auxOp = (*auxOp).next;
		}
		(*auxOp).id = 1;

		printf("Quantas maquinas vao poder ser utilizadas para esta operacao: ");
		fgets(input, sizeof(input), stdin);
		cont = strtol(input, NULL, 0);
		(*auxOp).quantMachines = cont;

		(*auxOp).machineAndTime = (int *)malloc(sizeof(int[2][cont]));
		(*auxOp).next = (operation *)malloc(sizeof(operation));
		(*(*auxOp).next).next = NULL;
		for (i = 0; i < 2; ++i) {
			for (j = 0; j < cont; ++j) {
				if(i==0) {
					printf("Qual o id da maquina que pertende usar: ");
					fgets(input, sizeof(input), stdin);
					(*auxOp).machineAndTime[i*cont + j] = strtol(input, NULL, 10);
				}
				else {
					printf("Qual o tempo que a %d maquina vai demorar: ", (*auxOp).machineAndTime[0*cont + j]);
					fgets(input, sizeof(input), stdin);
					(*auxOp).machineAndTime[i*cont + j] = strtol(input, NULL, 10);
				}
			}
		}
	}
}

void listOperation(job *jobList) {
	int i = 0, j = 0;
	operation *auxOp;
	
	auxOp = jobList->op;

	system("cls");
	puts("Dados disponiveis: ");
	if(auxOp==NULL)	{
		puts("Nenhum");
	}
	else {
		// printf("\n\n%-10s%-15s%s\n","Id","machine","Tempo");
		while((*auxOp).next != NULL) {
			printf("Id - (%d)\n",(*auxOp).id);
			printf("Machine Quant. - (%d)\nMachine - (",(*auxOp).quantMachines);
			for (j = 0; j < (*auxOp).quantMachines; ++j) {
				printf("%d,",(*auxOp).machineAndTime[0*(*auxOp).quantMachines + j]);
			}
			printf(")\nTime - (");
			for (j = 0; j < (*auxOp).quantMachines; ++j) {
				printf("%d,",(*auxOp).machineAndTime[1*(*auxOp).quantMachines + j]);	
			}
			printf(")\n\n");
			auxOp=(*auxOp).next;
		}
	}
	printf("\n\n");
	system("pause");
}
void removeOperation(job **jobList) {}
void editOperation(job *jobList) {}
void determineShortestTime(job *jobList) {}
void determineLongestTime(job *jobList) {}
void determineAverageTime(job *jobList) {}




//#####################################################################################################
//#####################################################################################################
void menu(int *opcao) {
    int i, success;
	char *endptr, buf[1024];
	
	do {
		system("cls");

		printf("%c",201); for(i = 0; i < 86; i++) printf("%c",205); printf("%c\n",187);
		_printf_p("%1$c                                         MENU                                         %1$c \n"
					"%1$c   0 - Exit                                                                           %1$c \n"
					"%1$c   1 - Insert Operation                                                               %1$c \n"
					"%1$c   2 - List Operations               5 - Inserir Pedido de Utilizacao                 %1$c \n"
					"%1$c   3 - Remove Operation              6 - Listagem de todos os Pedidos de utilizacao   %1$c \n"
					"%1$c   4 - Edit Operation                7 - Remover Pedidos de Utilizacao                %1$c \n",186);
		printf("%c",200); for(i = 0; i < 86; i++) printf("%c",205); printf("%c\nOption: ",188);

		if (!fgets(buf, sizeof(buf), stdin)) {
			//return 1;
		}
		errno = 0; // reset error number
		(*opcao) = strtol(buf, &endptr, 10);
		if (errno == ERANGE) {
			printf("Desculpe, o numero inserido e muito grande ou demasiado pequeno.\n\n");
			system("pause");
			success = 0;
		}
		else if (((*opcao) > 7) || ((*opcao) < 0)) {
			printf("Por favor insira um numero entre 0 e 7.\n\n");
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