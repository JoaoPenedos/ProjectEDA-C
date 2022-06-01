/**
 * @file header.h
 * @author João Penedos
 * @brief
 * @version 2.0
 * 
 * @copyright Copyright (c) 2022 
 */

#ifndef _HEADER
#define _HEADER

#pragma region Definitions	

#define _ARRAY_MACHINES_TIMES 2
#define _MACHINES 0
#define _TIMES 1
#define _MAXM 15
#define _MAXT 100

#pragma endregion

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

typedef struct proposal {
	int jobId;
	int opId;
	int time;
}proposal;

typedef struct proposalList {
	int success;
	char proposalVersionFile[100];
    proposal *proposalData[_MAXM][_MAXT];
	struct proposalList *next;
}proposalList;

#pragma endregion

#pragma region Signatures

void pauseProgram();

int askUserIntegers(const char *textToAsk);
int yesNo();

void menu(int *option);
void menuEditJob(int *optionEditJob);

jobList *newJobListNode(int key);
operationList *newOperationListNode();
proposalList *newProposalListNode();
proposal *newProposalNode();

void iniJb(job *jb);
void iniOp(operation *op);

int maximum(int a, int b);
int height(jobList *N);
int getBalance(jobList *N);
jobList *rightRotate(jobList *y);
jobList *leftRotate(jobList *x);
jobList *minValueNode(jobList *node);

void printJobTreeByLevel(jobList *root, int level);

void listOperationNode(operation op);
void listOperations(operationList *auxOpL);
void listJobNode(operationList *auxOpL, job jb);
void ListJobTreeInOrder(jobList *n);

int searchEqualMachine(operation m, int currentPosition);

void createOperationFromFile(operationList *opL, int idOp, int cont, int arrM[], int arrT[]);
jobList *checkDataInFile(int *idContJob);

jobList *insertNode(jobList *node, int key, jobList **nodePointer);
void insertJob(jobList **jbL, int *idContJob, int *success);

jobList *deleteNode(jobList *root, int key, int originalKey, int *success);
void removeJob(jobList **jbL, int *success);

jobList *findJobInTree(jobList *root, int key) ;
jobList *findJob(jobList *auxjbL);

void readOperation(operation *op);
void insertOperationNode(operationList *op, int *nOperations, int *success);
void removeOperation(operationList **opL, int *nOperations, int *success);
void editOperation(operationList *opL, int *success);

void determineShortestTime(operationList *opL);
void determineLongestTime(operationList *opL);
void determineAverageTimeOfAllPossibilities(operationList *opL,int *id, int soma, float *media);
void determineAverageTime(operationList *opL);

void calcEscalationProposal(operationList *opL, int jobId, proposalList *pL);
void goThroughByOrderCalcProposal(jobList *n, proposalList *pL);
proposalList *updateEscalationProposal(proposalList *pL, jobList *jbL, int *changeCount);
void printEscalationProposal(proposalList *pL);
void saveProposalInFile(proposalList *pL);

void writeInFile(operationList *opL, int id, FILE *f_JOB);
void saveDataInFile(jobList *jbL, const char *fileName);
void orderTreeToSaveInFile(jobList *n, FILE *f_JOB);
void saveDataYN(jobList *jbL);

void deallocateOperation(operationList *opL);
void deallocateJob(jobList *root);
void deallocateProposal(proposalList *pL);
#pragma endregion

#endif