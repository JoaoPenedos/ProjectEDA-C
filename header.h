/**
 * @file header.h
 * @author João Penedos
 * @brief
 * @version 0.9
 * 
 * @copyright Copyright (c) 2022 
 */

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
    int quantMachines;      // quantidade de maquinas que podem ser usadas
    int *machineAndTime;    // 2d array para guardar as maquinas e os respetivos tempos
    struct operation *next; // apontador para a proxima operacao
}operation;
//-------------------------------------------------------
typedef struct job {
    //int id;
    int nOperations;        // quantidade de operacoes no job
    operation *op;          // apontador para o inicio da lista de operacoes
    //struct job *next;     // apontador para o proximo job
}job;

#pragma endregion
//#####################################################################################################
//#####################################################################################################
#pragma region Signatures
job *inicializarJob();
operation *inicializarOperation();
void checkDataInFile(operation *op, int *idCont, int *nOperations);
void menu(int *opcao);
void insertNewOperation(operation *op, int *idCont, int *nOperations);
void listNode(operation *op);
void listOperations(operation *op, int nOperations);
void removeOperation(job **jobList, int *nOperations);
void editOperation(operation *op);
void determineShortestTime(operation *op);
void determineLongestTime(operation *op);
void determineAverageTime(operation *op);
void saveDataInFile(operation *op);
#pragma endregion

#endif