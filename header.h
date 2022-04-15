#ifndef DATA
#define DATA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <errno.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#pragma region Structs 

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
    int nOperations;
    operation *op;
    //struct job *next;
}job;

#pragma endregion
//#####################################################################################################
//#####################################################################################################
#pragma region Signatures
job *inicializarJob();
operation *inicializarOperation();
void verificarDadosNoFicheiro(operation *op, int *idCont, int *nOperations);
void menu(int *opcao);
void insertNewOperation(operation *op, int *idCont);
void listOperation(operation *op, int nOperations);
void removeOperation(job **jobList);
void editOperation(operation *op);
void determineShortestTime(operation *op);
void determineLongestTime(operation *op);
void determineAverageTime(operation *op);
#pragma endregion

#endif