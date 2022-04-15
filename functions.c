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
void verificarDadosNoFicheiro(operation *op, int *idCont, int *nOperations) {
	operation *opP, *auxOp;
	FILE *f_JOB = fopen("test.txt","r");
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
				(*opP).next=NULL;

				while((*op).next != NULL) {
					op = (*op).next;
				}

				(*nOperations)++;

				(*idCont)++;
				(*op).id = (*idCont);
				(*op).quantMachines = cont;
				(*op).machineAndTime = (int *)malloc(sizeof(int[2][cont]));
				// (*op).next = (operation *)malloc(sizeof(operation));
				for(i=0; i < cont; i++) {
					(*op).machineAndTime[0*cont + i] = arrayM[i];
					(*op).machineAndTime[1*cont + i] = arrayT[i];
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
void insertNewOperation(operation *op, int *idCont) {
    char *input;
    int i, j;
	operation *auxOp;

	auxOp = (operation *)malloc(sizeof(operation));
	
	system("cls");
	if(auxOp==NULL) { 
		printf("Nao existe mais espaço em memoria. E impossivel inserir\n\n");
		system("pause");
	}
	else {
		system("cls");
        (*auxOp).next=NULL;
		while(((*op).next) != NULL) {
			op = (*op).next;
		}

		(*idCont)++;
		(*op).id = (*idCont);

		printf("Quantas maquinas vao poder ser utilizadas para esta operacao: ");
		fgets(input, sizeof(input), stdin);
		(*op).quantMachines = strtol(input, NULL, 0);
		(*op).machineAndTime = (int *)malloc(sizeof(int[2][(*op).quantMachines]));
		for (i = 0; i < 2; ++i) {
			for (j = 0; j < (*op).quantMachines; ++j) {
				if(i==0) {
					printf("Qual o id da maquina que pertende usar: ");
					fgets(input, sizeof(input), stdin);
					(*op).machineAndTime[i*(*op).quantMachines + j] = strtol(input, NULL, 10);
				}
				else {
					printf("Qual o tempo que a %d maquina vai demorar: ", (*op).machineAndTime[0*(*op).quantMachines + j]);
					fgets(input, sizeof(input), stdin);
					(*op).machineAndTime[i*(*op).quantMachines + j] = strtol(input, NULL, 10);
				}
			}
		}
		(*op).next = auxOp;
	}
}
//#####################################################################################################
void listOperation(operation *op, int nOperations) {
	int i = 0, j = 0;	

	system("cls");
	if((*op).next==NULL)	{
		puts("Nenhum");
	}
	else {
		printf("This job has %d operations\n", nOperations);
		while((*op).next != NULL) {
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
			op=(*op).next;
		}
	}
	printf("\n\n");
	system("pause");
}
//#####################################################################################################
void removeOperation(job **jobList) {
	operation *y, *atras, *frente, *auxOp;
	int j, intElemRetirar;
	char elemRetirar[40];

	system("cls");
	y=(*jobList)->op;
	
	if(((*y).next)==NULL) { 
		printf("A lista nao tem dados"); 
	}
	else {
		printf("Diga o codigo cujo operacao quer retirar?\n");
		if(fgets(elemRetirar, sizeof(elemRetirar), stdin)) {
			elemRetirar[strcspn(elemRetirar, "\n")] = 0;
			intElemRetirar = strtol(elemRetirar, NULL, 0);
		}

		if(intElemRetirar == (*(*jobList)->op).id) {
			system ("cls");
			printf("O elemento foi retirado\n");
			printf("Id - (%d)\n",(*(*jobList)->op).id);
			printf("Machine Quant. - (%d)\nMachine - (",(*(*jobList)->op).quantMachines);
			for (j = 0; j < (*(*jobList)->op).quantMachines; ++j) {
				if(((*(*jobList)->op).quantMachines - j) == 1)
					printf("%d",(*(*jobList)->op).machineAndTime[0*(*(*jobList)->op).quantMachines + j]);
				else
					printf("%d,",(*(*jobList)->op).machineAndTime[0*(*(*jobList)->op).quantMachines + j]);
			}
			printf(")\nTime - (");
			for (j = 0; j < (*(*jobList)->op).quantMachines; ++j) {
				if(((*(*jobList)->op).quantMachines - j) == 1)
					printf("%d",(*(*jobList)->op).machineAndTime[1*(*(*jobList)->op).quantMachines + j]);
				else
					printf("%d,",(*(*jobList)->op).machineAndTime[1*(*(*jobList)->op).quantMachines + j]);
			}
			printf(")\n");
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
				printf("O elemento foi retirado\n");
				printf("Id - (%d)\n",(*auxOp).id);
				printf("Machine - (");
				for (j = 0; j < (*auxOp).quantMachines; ++j) {
					if(((*auxOp).quantMachines - j) == 1)
						printf("%d",(*auxOp).machineAndTime[0*(*auxOp).quantMachines + j]);
					else
						printf("%d,",(*auxOp).machineAndTime[0*(*auxOp).quantMachines + j]);
				}
				printf(")\nTime - (");
				for (j = 0; j < (*auxOp).quantMachines; ++j) {
					if(((*auxOp).quantMachines - j) == 1)
						printf("%d",(*auxOp).machineAndTime[1*(*auxOp).quantMachines + j]);
					else
						printf("%d,",(*auxOp).machineAndTime[1*(*auxOp).quantMachines + j]);
				}
				printf(")\n");
				system("pause");
				free(auxOp);
			}
			else {
				system("cls"); 
				printf("O elemento com o codigo %s nao existe na lista", elemRetirar);
			}
		}
	}
}
//#####################################################################################################
void editOperation(operation *operationList) {
	operation *auxOp;
	int i, j, intElemEditar;
	char elemEditar[40], *input;

	system("cls");
	
	if(((*operationList).next)==NULL) { 
		printf("A lista nao tem dados"); 
	}
	else {
		printf("Diga o codigo cuja operacao quer editar?\n");
		if(fgets(elemEditar, sizeof(elemEditar), stdin)) {
			elemEditar[strcspn(elemEditar, "\n")] = 0;
			intElemEditar = strtol(elemEditar, NULL, 0);
		}

		if(intElemEditar == (*operationList).id) {
			system ("cls");
			printf("O elemento a editar\n");
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
			free((*operationList).machineAndTime);

			printf("Quantas maquinas vao poder ser utilizadas para esta operacao: ");
			fgets(input, sizeof(input), stdin);
			(*operationList).quantMachines = strtol(input, NULL, 0);
			(*operationList).machineAndTime = (int *)malloc(sizeof(int[2][(*operationList).quantMachines]));
			for (i = 0; i < 2; ++i) {
				for (j = 0; j < (*operationList).quantMachines; ++j) {
					if(i==0) {
						printf("Qual o id da maquina que pertende usar: ");
						fgets(input, sizeof(input), stdin);
						(*operationList).machineAndTime[i*(*operationList).quantMachines + j] = strtol(input, NULL, 10);
					}
					else {
						printf("Qual o tempo que a %d maquina vai demorar: ", (*operationList).machineAndTime[0*(*operationList).quantMachines + j]);
						fgets(input, sizeof(input), stdin);
						(*operationList).machineAndTime[i*(*operationList).quantMachines + j] = strtol(input, NULL, 10);
					}
				}
			}
		}
		else {
			auxOp=operationList;
			while((intElemEditar != (*operationList).id) && (*operationList).next != NULL) {
				operationList = (*operationList).next;
			}
			
			if(intElemEditar == (*operationList).id) {
				system ("cls");
				printf("O elemento a editar\n");
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
				free((*operationList).machineAndTime);

				printf("Quantas maquinas vao poder ser utilizadas para esta operacao: ");
				fgets(input, sizeof(input), stdin);
				(*operationList).quantMachines = strtol(input, NULL, 0);
				(*operationList).machineAndTime = (int *)malloc(sizeof(int[2][(*operationList).quantMachines]));
				for (i = 0; i < 2; ++i) {
					for (j = 0; j < (*operationList).quantMachines; ++j) {
						if(i==0) {
							printf("Qual o id da maquina que pertende usar: ");
							fgets(input, sizeof(input), stdin);
							(*operationList).machineAndTime[i*(*operationList).quantMachines + j] = strtol(input, NULL, 10);
						}
						else {
							printf("Qual o tempo que a %d maquina vai demorar: ", (*operationList).machineAndTime[0*(*operationList).quantMachines + j]);
							fgets(input, sizeof(input), stdin);
							(*operationList).machineAndTime[i*(*operationList).quantMachines + j] = strtol(input, NULL, 10);
						}
					}
				}
				operationList = auxOp;
			}
			else {
				system("cls"); 
				printf("O elemento com o codigo %s nao existe na lista", elemEditar);
			}
		}
	}
}
//#####################################################################################################
void determineShortestTime(operation *op) {
	int i = 0, j = 0, soma = 0, min, mach;

	system("cls");
	if((*op).next==NULL) {
		puts("Nenhum dado");
	}
	else {
		printf("Quantidade minima de unidades de tempo necessarias para completar o job pela ordem:\n");
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
		printf("\nShortest Time: %d", soma);
	}
	printf("\n\n");
	system("pause");
}
//#####################################################################################################
void determineLongestTime(operation *op) {
	int i = 0, j = 0, soma = 0, max, mach;

	system("cls");
	if((*op).next==NULL) {
		puts("Nenhum dado");
	}
	else {
		printf("Quantidade maxima de unidades de tempo necessarias para completar o job pela ordem:\n");
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
		printf("\nLongest Time: %d", soma);
	}
	printf("\n\n");
	system("pause");
}
//#####################################################################################################
void determineAverageTime(operation *op) {}
//#####################################################################################################




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