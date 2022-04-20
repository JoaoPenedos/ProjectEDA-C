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
#include "functions.c"

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

int main(int argc, char const *argv[]) {
    job *jobList;
    int opcao, idCont = 0;
    
    jobList = inicializarJob(); // inicializar a lista
	checkDataInFile(jobList->op,&idCont,&(jobList->nOperations)); // verificar dados no ficheiro
    listOperations(jobList->op,jobList->nOperations); // listar as opercoes da lista

    do {
        menu(&opcao);

        switch(opcao) {
            case 0: printf("Goodbye!!\n\n");
					break;
            case 1: insertNewOperation(jobList->op,&idCont,&(jobList->nOperations)); 
					break; // inserir nova opercao
            case 2: listOperations(jobList->op,jobList->nOperations); 
					break; // listar as opercoes da lista
            case 3: removeOperation(&jobList,&(jobList->nOperations));
					break; // remover opercao da lista
            case 4: editOperation(jobList->op);
					break; // editar as operacoes da lista
            case 5: determineShortestTime(jobList->op);
					break; // determinar o tempo mais curto
            case 6: determineLongestTime(jobList->op);
					break; // determinar o tempo mais longo
            case 7: determineAverageTime(jobList->op);
            		break; // determinar o tempo medio de todas as possibilidades
        }
    }while(opcao != 0);

    saveDataInFile(jobList->op); // salvar as mudanças da lista no ficheiro

    while((jobList->op) != NULL) {
        free(jobList->op);
        jobList->op = jobList->op->next;
    }
    free(jobList);
    return 0;
}