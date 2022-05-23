/**
 * @file header.h
 * @author João Penedos
 * @brief
 * @version 0.9
 * 
 * @copyright Copyright (c) 2022 
 */

#ifndef _HEADER
#define _HEADER

#pragma region Structs

typedef struct operation {
	int id;
	int quantMachines;
	int *machineAndTime;
}operation;

typedef struct operationList {
	operation op;
	struct operationList *next;
}operationList;

typedef struct job {
	int id;
	int nOperations;
	int height;
}job;

typedef struct jobList {
	job jb;
	operationList *opL;
	struct jobList *left;
	struct jobList *right;
}jobList;

// typedef struct operationList {
//     int id;
//     char **proposta;
// }operationList;

#pragma endregion


#pragma region Definitions	

#define _ARRAY_MACHINES_TIMES 2
#define _MACHINES 0
#define _TIMES 1

#pragma endregion


#pragma region Signatures

void menu(int *option);
void menuEditJob(int *optionEditJob);

int askUserIntegers(char *textToAsk);

void iniJb(job *jb);
void iniOp(operation *op);

jobList *newJobNode(int key);
operationList *newOperationNode();

int maximum(int a, int b);
int height(jobList *N);
int getBalance(jobList *N);
jobList *rightRotate(jobList *y);
jobList *leftRotate(jobList *x);
jobList *minValueNode(jobList *node);

jobList *insertNode(jobList *node, int key, jobList **nodePointer);
jobList *insertJob(jobList **jbL,int *idContJob);

jobList *deleteNode(jobList *root, int key, int originalKey, int *success);
void removeJob(jobList **jbL);

void createOperationFromFile(operationList *opL, int idOp, int cont, int arrM[], int arrT[]);
jobList *checkDataInFile(jobList *jbL, int *idContJob);

void printJobTreeByLevel(jobList *root, int level);

void listOperationNode(operation op);
void listOperations(operationList *auxOpL);
void listJobNode(operationList *auxOpL, job jb);
void ListJobTreeInOrder(jobList *n);

jobList *findJobInTree(jobList *root, int key) ;
jobList *findJob(jobList *auxjbL);

// void calcEscalationProposal(job *jobList);

int searchEqualMachine(operation m, int elemToFind, int currentPosition);
operation readOperation(operation *op);
void insertOperationNode(operationList *op, int *nOperations);
void removeOperation(operationList *opL, int *nOperations);
void editOperation(operationList *opL);

void determineShortestTime(operationList *opL);
void determineLongestTime(operationList *opL);
void determineAverageTime(operationList *opL);
void determineAverageTimeOfAllPossibilities(operationList *opL,int *id, int soma, float *media);

void writeInFile(operationList *opL, int id, FILE *f_JOB);
void saveDataInFile(jobList *jbL);
void orderTreeToSaveInFile(jobList *n, FILE *f_JOB);
void saveDataYN(jobList *jbL);

void deallocate(jobList *root);
#pragma endregion

#endif