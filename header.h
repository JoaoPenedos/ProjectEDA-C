#ifndef DATA
#define DATA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <errno.h>

#pragma region Structs 

// typedef struct machine {
//     int id;
//     int OnOff;
//     struct machine *next;
// }machine;
//-------------------------------------------------------
typedef struct operation {
    int id;
    int quantMachines;
    int *machineAndTime;
    struct operation *next;
}operation;
//-------------------------------------------------------
typedef struct job {
    //int id;
    operation *op;
    //struct job *next;
}job;

#pragma endregion
//#####################################################################################################
//#####################################################################################################
#pragma region Signatures
job *inicializarJob();
operation *inicializarOperation();
// machine *inicializarMachine();
void verificarDadosNoFicheiro(job *jobList);
void menu(int *opcao);
void insertNewOperation(job *jobList);
void listOperation(job *jobList);
void removeOperation(job **jobList);
void editOperation(job *jobList);
void determineShortestTime(job *jobList);
void determineLongestTime(job *jobList);
void determineAverageTime(job *jobList);
#pragma endregion

#endif