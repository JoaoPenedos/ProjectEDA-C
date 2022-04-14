#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <errno.h>

#include "header.h"
#include "functions.c"

int main(int argc, char const *argv[]) {
    job *jobList;
    int opcao, idCont = 0;
    
    jobList = inicializarJob();
	verificarDadosNoFicheiro(jobList->op,&idCont);

    do {
        menu(&opcao);

        switch(opcao) {
            case 0: printf("Goodbye!!\n\n"); 
					break;
            case 1: insertNewOperation(jobList->op,&idCont); 
					break;
            case 2: listOperation(jobList->op); 
					break;
            case 3: removeOperation(&jobList);
					break;
            case 4: editOperation(&(jobList->op));
					break;
            case 5: determineShortestTime(jobList);
					break;
            case 6: determineLongestTime(jobList);
					break;
            case 7: determineAverageTime(jobList);
            		break;
        }
    }while(opcao != 0);

    return 0;
}