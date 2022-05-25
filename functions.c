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

#include <sys/types.h>
#include <sys/stat.h>

#include "header.h"
#include "colors.h"

#ifdef _WIN32
#include <Windows.h>
# define DIR_SEPARATOR "\\"
#else
#include <unistd.h>
# define DIR_SEPARATOR "/"
#endif

void pauseProgram() {
	printf("\nPress any key to continue . . .");
	getchar();
}

/**
 * @brief It creates a new node for the jobList tree.
 * 
 * @param key the job id
 * 
 * @return A pointer to a jobList node.
 */
jobList *newJobNode(int key) {
	jobList *node = (jobList *) malloc(sizeof(jobList));

	if(node == NULL) {
		system("cls");
		printf(_FG_RED"Can't create tree or branch"_RESET"\n\n");
		pauseProgram();
		return NULL;
	}
	else {
		iniJb(&(node->jb));
		node->jb.id = key;
		node->jb.height = 1;
		node->opL = newOperationNode();
		node->left = NULL;
		node->right = NULL;
		return node;
	}
}
/**
 * @brief It creates a new node for the operation list
 * 
 * @return A pointer to a node of the operationList type.
 */
operationList *newOperationNode() {
	operationList *p = (operationList *) malloc( sizeof(operationList));
	
	if(p == NULL) {
		system("cls");
		printf(_FG_RED"Can't create list"_RESET"\n\n");
		pauseProgram();
		return NULL;
	}
	else {
		iniOp(&(p->op));
		p->next = NULL;
		return p;
	}
}

/**
 * @brief It creates a new node for the proposal list.
 * 
 * @return A pointer to a proposalList struct.
 */
proposalList *newProposalNode() {
	proposalList *node = (proposalList *) malloc(sizeof(proposalList));

	if(node == NULL) {
		system("cls");
		printf(_FG_RED"Can't create list"_RESET"\n\n");
		pauseProgram();
		return NULL;
	}
	else {
		strcpy(node->proposalVersionFile,"--");
		for(int i = 0; i < _MAXM; i++) {
			for(int j = 0; j < _MAXT; j++){
				node->proposalData[i][j] = NULL;
			}
		}
		node->next = NULL;
		return node;
	}
}
/**
 * @brief It initializes the job structure
 * 
 * @param jb pointer to the job
 */
void iniJb(job *jb) {
	jb->id = 0;
	jb->nOperations = 0;
	jb->height = 0;
}
/**
 * @brief It initializes the operation structure
 * 
 * @param op pointer to the operation
 */
void iniOp(operation *op) {
	op->id = 0;
	op->quantMachines = 0;
	op->machineAndTime = NULL;
}
/**
 * @brief It returns the maximum of two integers
 * 
 * @param a The first number to compare.
 * @param b the number of bits in the integer
 * 
 * @return The maximum of the two numbers.
 */
int maximum(int a, int b) {
	return (a > b) ? a : b;
}
/**
 * @brief If the node is null, return 0. Otherwise, return the height of the node.
 * 
 * @param N The node to be checked
 * 
 * @return The height of the node.
 */
int height(jobList *node) {
	if (node == NULL)
		return 0;
	return node->jb.height;
}
/**
 * @brief It returns the height of the left subtree minus the height of the right subtree.
 * 
 * @param N The node to be balanced
 * 
 * @return The difference between the height of the left subtree and the height of the right subtree.
 */
int getBalance(jobList *N) {
	if (N == NULL)
		return 0;
	return height(N->left) - height(N->right);
}
/**
 * @brief It rotates the tree to the right.
 * 
 * @param y the node that is being rotated
 * 
 * @return The root of the rotated subtree.
 */
jobList *rightRotate(jobList *y) {
	jobList *x = y->left;
	jobList *T2 = x->right;

	x->right = y;
	y->left = T2;

	y->jb.height = maximum(height(y->left), height(y->right)) + 1;
	x->jb.height = maximum(height(x->left), height(x->right)) + 1;

	return x;
}
/**
 * @brief The leftRotate function performs a single left rotation on the node x, and returns the new root of
 * the subtree
 * 
 * @param x the node to be rotated
 * 
 * @return The root of the subtree.
 */
jobList *leftRotate(jobList *x) {
	jobList *y = x->right;
	jobList *T2 = y->left;

	y->left = x;
	x->right = T2;

	x->jb.height = maximum(height(x->left), height(x->right)) + 1;
	y->jb.height = maximum(height(y->left), height(y->right)) + 1;

	return y;
}
/**
 * @brief The above function finds the minimum value in the tree.
 * 
 * @param node the node to be deleted
 * 
 * @return The node with the smallest value in the tree.
 */
jobList *minValueNode(jobList *node) {
	jobList *current = node;

	while (current->left != NULL)
		current = current->left;

	return current;
}
/**
 * @brief It prints the tree in a way that makes it easy to see the structure of the tree
 * 
 * @param root the root of the tree
 * @param level the level of the tree
 * 
 * @return the root of the tree.
 */
void printJobTreeByLevel(jobList *root, int level) {
	if (root == NULL)
		return;
	for (int i = 0; i < level; i++)
		printf(i == level - 1 ? "|->" : "  ");

	printf(_FG_B_CYAN"%d\n"_FG_GREEN, root->jb.id);
	printJobTreeByLevel(root->left, level + 1);
	printJobTreeByLevel(root->right, level + 1);
}
/**
 * @brief It prints the operation's id, the machines it can be done on, and the time it takes to do it on each
 * machine
 * 
 * @param op is a operation structure
 */
void listOperationNode(operation op) {
	int j = 0;

	printf(_FG_YELLOW"Id - ("_FG_CYAN"%d"_FG_YELLOW")\n",op.id);
	printf("Machine - ("_FG_CYAN);
	for (j = 0; j < op.quantMachines; ++j) {
		if((op.quantMachines - j) == 1)
			printf("%d",op.machineAndTime[_MACHINES*op.quantMachines + j]);
		else
			printf("%d"_FG_YELLOW","_FG_CYAN,op.machineAndTime[_MACHINES*op.quantMachines + j]);
	}
	printf(_FG_YELLOW")\nTime - ["_FG_CYAN);
	for (j = 0; j < op.quantMachines; ++j) {
		if((op.quantMachines - j) == 1)
			printf("%d",op.machineAndTime[_TIMES*op.quantMachines + j]);
		else
			printf("%d"_FG_YELLOW","_FG_CYAN,op.machineAndTime[_TIMES*op.quantMachines + j]);
	}
	printf(_FG_YELLOW"]"_RESET"\n\n");

}
/**
 * @brief It lists the operations of a given operation list
 * 
 * @param auxOpL operationList 
 */
void listOperations(operationList *auxOpL) {
	while(auxOpL->next != NULL) {
		listOperationNode(auxOpL->op);
		auxOpL = auxOpL->next;
	}
}
/**
 * @brief It lists the operations of a job
 * 
 * @param auxOpL is a pointer to the first node of the operation list
 * @param jb is a job structure
 */
void listJobNode(operationList *auxOpL, job jb) {
	int i = 0;

	for(i = 0; i < 25; i++) printf(_FG_GREY"%c",205);
	printf("\nJOB N%c "_FG_B_CYAN"%d\n"_FG_GREY,167,jb.id);

	if(jb.nOperations > 0) {
		printf("Operations count: "_FG_B_CYAN"%d"_RESET"\n",jb.nOperations);
		listOperations(auxOpL);
	}
	else {
		printf(_FG_RED"The job has no operations"_RESET"\n\n");
	}
}
/**
 * @brief It prints the job list in order.
 * 
 * @param n the node to be printed
 * 
 * @return the jobList pointer.
 */
void ListJobTreeInOrder(jobList *n) {
	if(n == NULL)
		return;

	ListJobTreeInOrder(n->left);
	listJobNode(n->opL,n->jb);
	ListJobTreeInOrder(n->right);
}
/**
 * @brief It checks if the current machine is equal to any of the previous machines
 * 
 * @param m the operation
 * @param elemToFind the element to find in the array
 * @param currentPosition the current position of the machine in the array
 * 
 * @return 0 if it finds equal machines and 1 if it doesn't find
 */
int searchEqualMachine(operation m, int elemToFind, int currentPosition) {
	for(int i = currentPosition - 1; i >= 0; i--) {
		if(m.machineAndTime[i] == m.machineAndTime[currentPosition])
			return 0;
	}

	return 1;
}
/**
 * @brief It creates a new operation node and inserts it at the end of the operation list
 * 
 * @param opL pointer to the first node of the linked list
 * @param idOp is the operation id
 * @param nMachines number of machines
 * @param arrM array of machines
 * @param arrT array of times
 */
void createOperationFromFile(operationList *opL, int idOp, int nMachines, int arrM[], int arrT[]) {
	operationList *pOpL;
	operation auxOp;
	int i = 0;

	pOpL = newOperationNode();

	while(opL->next != NULL) {
		opL = opL->next;
	}

	iniOp(&auxOp);
	auxOp.id = idOp;
	auxOp.quantMachines = nMachines;
	auxOp.machineAndTime = (int *)malloc(sizeof(int[_ARRAY_MACHINES_TIMES][auxOp.quantMachines]));
	for(i=0; i < auxOp.quantMachines; i++) {
		auxOp.machineAndTime[_MACHINES*auxOp.quantMachines + i] = arrM[i];
		auxOp.machineAndTime[_TIMES*auxOp.quantMachines + i] = arrT[i];
	}
	opL->op = auxOp;
	opL->next = pOpL;
}
/**
 * @brief It reads a file with the following format:
 * #
 * (1,2,3,4,5)
 * [1,2,3,4,5]
 * #
 * (1,2,3,4,5)
 * [1,2,3,4,5]
 * And it creates a binary tree of jobs, each job node having a linked list of operations.
 * 
 * @param jbL pointer to the job list
 * @param idContJob is the job id counter
 * 
 * @return The root of the jobList.
 */
jobList *checkDataInFile(jobList *jbL, int *idContJob) {
	jobList *nodePointer, *root = NULL;
	FILE *f_JOB = fopen("dados.txt","r");
	int i = 0, cont = 0, arrayM[100], arrayT[100], digitCount = 0, iochar;
	char simpleBuffer[12];//max 10 int digits + 1 negative sign + 1 null char string....if you read more, then you probably don't    have an int there....

	if(f_JOB != NULL) {
		do {
			i = cont = 0;
			while (iochar = getc(f_JOB), iochar != '\n' && iochar != EOF) {
				if(iochar == '#'){
					do {
						iochar = getc(f_JOB); 
					}while( iochar != '\n' && iochar != EOF);

					(*idContJob)++;
					root = insertNode(root,(*idContJob),&nodePointer);
				}
				if(iochar != '(' && iochar != ')' && iochar != ',' && iochar != ' ' && iochar != '\n') {
					simpleBuffer[digitCount++] = (char) iochar;
				}
				else if(digitCount > 0){
					simpleBuffer[digitCount] = 0; //append null char to end string format
					arrayM[i] = strtol(simpleBuffer, NULL, 0);
					cont++;
					i++;
					digitCount = 0;  //reset buffer to read new number
				}
			}
			i = 0;
			while (iochar = getc(f_JOB), iochar != '\n' && iochar != EOF) {
				if(iochar != '[' && iochar != ']' && iochar != ',' && iochar != ' ' && iochar != '\n') {
					simpleBuffer[digitCount++] = (char) iochar;
				}
				else if(digitCount > 0){
					simpleBuffer[digitCount] = 0; //append null char to end string format
					arrayT[i] = strtol(simpleBuffer, NULL, 0);
					i++;
					digitCount = 0;  //reset buffer to read new number
				}
			}

			if(i > 0){
				nodePointer->jb.nOperations++;
				createOperationFromFile(nodePointer->opL,nodePointer->jb.nOperations,cont,arrayM,arrayT);
			}
			
		}while(iochar != EOF);
	}
	fclose(f_JOB);

	return root;
}
/**
 * @brief The function takes a node, a key, and a pointer to a node pointer as parameters. It then inserts the
 * node into the tree and balances it
 * 
 * @param node The node to insertNode the new node into
 * @param key The key to be inserted into the tree
 * @param nodePointer A pointer to the pointer of the node that is to be inserted.
 * 
 * @return The node that was inserted.
 */
jobList *insertNode(jobList *node, int key, jobList **nodePointer) {
	// Find the correct position to insertNode the node and insertNode it
	if (node == NULL)
		return ((*nodePointer) = newJobNode(key));

	if (key < node->jb.id)
		node->left = insertNode(node->left, key, &(*nodePointer));
	else if (key > node->jb.id)
		node->right = insertNode(node->right, key, &(*nodePointer));
	else
		return node;

	// Update the balance factor of each node and
	// Balance the tree
	node->jb.height = 1 + maximum(height(node->left), height(node->right));

	int balance = getBalance(node);
	if (balance > 1 && key < node->left->jb.id)
		return rightRotate(node);

	if (balance < -1 && key > node->right->jb.id)
		return leftRotate(node);

	if (balance > 1 && key > node->left->jb.id) {
		node->left = leftRotate(node->left);
		return rightRotate(node);
	}

	if (balance < -1 && key < node->right->jb.id) {
		node->right = rightRotate(node->right);
		return leftRotate(node);
	}

	return node;
}
/**
 * @brief It inserts a job node in a job list, and then asks the user if he wants to add operations to the
 * current added job node.
 * 
 * @param jbL pointer to the jobList
 * @param idContJob is a counter that keeps track of the number of jobs that have been added to the
 * list.
 */
void insertJob(jobList **jbL,int *idContJob) {
	jobList *currentNode = NULL;
	int opYN;

	system("cls");
	(*idContJob)++;
	(*jbL) = insertNode((*jbL), (*idContJob), &currentNode);

	printf(_FG_CYAN"Do you want to add operations to the current added Job node? \n"_RESET);
	while (opYN = yesNo(), opYN == 1) {
		insertOperationNode(currentNode->opL,&(currentNode->jb.nOperations));
	}
}
/**
 * @brief It deletes a node from the tree and then balances the tree
 * 
 * @param root The root of the tree
 * @param key the id of the job to be deleted
 * @param originalKey the id of the original key for the job to be deleted
 * @param success 1 if succeded in deleted the job node
 * 
 * @return The root of the tree.
 */
jobList *deleteNode(jobList *root, int key, int originalKey, int *success) {
	if (root == NULL)
		return root;

	if (key < root->jb.id)
		root->left = deleteNode(root->left,key,originalKey,&(*success));
	else if (key > root->jb.id)
		root->right = deleteNode(root->right,key,originalKey,&(*success));
	else {
		if(originalKey == root->jb.id)
			listJobNode(root->opL,root->jb);
		
		if ((root->left == NULL) || (root->right == NULL)) {
			jobList *temp = root->left ? root->left : root->right;

			if (temp == NULL) {
				temp = root;
				root = NULL;
			} 
			else {
				*root = *temp;
			}

			(*success) = 1;
			while((temp->opL) != NULL) {
				free(temp->opL);
				temp->opL = temp->opL->next;
			}
			free(temp);
		} 
		else {
			jobList *temp = minValueNode(root->right);

			root->jb.id = temp->jb.id;
			root->right = deleteNode(root->right,temp->jb.id,originalKey,&(*success));
		}
	}

	if (root == NULL)
		return root;

	// Update the balance factor of each node and
	// balance the tree
	root->jb.height = 1 + maximum(height(root->left), height(root->right));

	int balance = getBalance(root);
	if (balance > 1 && getBalance(root->left) >= 0)
		return rightRotate(root);

	if (balance > 1 && getBalance(root->left) < 0) {
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}

	if (balance < -1 && getBalance(root->right) <= 0)
		return leftRotate(root);

	if (balance < -1 && getBalance(root->right) > 0) {
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}

	return root;
}
/**
 * It removes a job from the list and updates the proposals that are affected by the removal
 * 
 * @param jbL pointer to the job list
 * @param pL pointer to the proposal list
 * @param changeProposalCounter is a counter that is used to know if the proposals have changed.
 */
void removeJob(jobList **jbL, proposalList **pL, int *changeProposalCounter) {
	int intElemRetirar, success = 0;

	system("cls");
	
	if((*jbL) == NULL) { 
		printf(_FG_RED"No operations in the list\n"_RESET); 
	}
	else {
		intElemRetirar = askUserIntegers(_FG_YELLOW"What is the code whose job you want to remove?\n"_RESET);

		(*jbL) = deleteNode((*jbL),intElemRetirar,intElemRetirar,&success);
		
		if(!success)
			printf(_FG_RED"The job with id "_FG_CYAN"%d"_FG_RED" does not exist in the list"_RESET, intElemRetirar);
		else
			(*pL) = updateEscalationProposal((*pL),(*jbL),&(*changeProposalCounter));

	}
}
/**
 * @brief If the root is null, return null. If the root is the job we're looking for, print the job and return
 * the root. Otherwise, search the left subtree for the job, and if it's not there, search the right
 * subtree
 * 
 * @param root the root of the tree
 * @param k the job id
 * 
 * @return The jobList node that contains the job with the id k.
 */
jobList *findJobInTree(jobList *root, int k) {
	if(root == NULL) {
		return NULL;
	} 
	else if (root->jb.id == k) {
		listJobNode(root->opL,root->jb);
		return root;
	} 
	else {
		jobList* x = findJobInTree(root->left,k);
		if (x) 
			return x;         //if we find in left subtree, return result
		return findJobInTree(root->right,k);
	}
}
/**
 * @brief It takes a jobList pointer as an argument, asks the user for an id, and returns a jobList pointer to
 * the job with that id.
 * 
 * @param auxjbL pointer to the first element of the job list
 * 
 * @return The job with the id that the user wants to find.
 */
jobList *findJob(jobList *auxjbL) {
	jobList *jobToFind;
	int intElemFind;

	system("cls");
	
	if(auxjbL == NULL) { 
		printf(_FG_RED"No jobs in the list\n"_RESET);
		pauseProgram();
		return NULL;
	}
	else {
		intElemFind = askUserIntegers(_FG_YELLOW"What is the id whose job you want to find?\n"_RESET);

		jobToFind = findJobInTree(auxjbL,intElemFind);
		if(jobToFind != NULL)
			return jobToFind;
		
		printf(_FG_RED"The job with id "_FG_CYAN"%d"_FG_RED" doesn't exist!\n"_RESET, intElemFind);
		return NULL;
	}
}
/**
 * @brief It reads the number of machines that can be used for an operation, then it reads the id of the
 * machines and the time it takes to complete the operation
 * 
 * @param op is a pointer to a struct operation
 */
void readOperation(operation *op) {
	char str[100];
	int i, j, check;

	op->quantMachines = askUserIntegers(_FG_YELLOW"How many machines can be used for this operation: "_RESET);

	op->machineAndTime = (int *)malloc(sizeof(int[_ARRAY_MACHINES_TIMES][op->quantMachines]));
	for (i = 0; i < 2; i++) {
		for (j = 0; j < op->quantMachines; j++) {
			if(i == 0) {
				do {
					if( j > 0) {
						check = 0;
						op->machineAndTime[i*op->quantMachines + j] = askUserIntegers(_FG_YELLOW"What is the id of the machine you want to use: "_RESET);

						check = searchEqualMachine((*op),op->machineAndTime[i*op->quantMachines + j],j);
						if(check == 0) {
							printf(_FG_RED"\nMachine "_FG_CYAN"%d"_FG_RED" already in use!! Chose another\n\n"_RESET, op->machineAndTime[i*op->quantMachines + j]);
						}
					}
					else {
						check = 1;
						op->machineAndTime[i*op->quantMachines + j] = askUserIntegers(_FG_YELLOW"What is the id of the machine you want to use: "_RESET);
					}
				}while(check == 0);
			}
			else {
				snprintf(str, sizeof(str), _FG_YELLOW"How long will machine "_FG_CYAN"%d"_FG_YELLOW" take: "_RESET, op->machineAndTime[_MACHINES*op->quantMachines + j]);
				op->machineAndTime[i*op->quantMachines + j] = askUserIntegers(str);
			}
		}
	}
}
/**
 * @brief It reads the information of a new operation and inserts it in the end of the list
 * 
 * @param op pointer to the first node of the list
 * @param nOperations Pointer to update the number of operations of desired the job node
 */
void insertOperationNode(operationList *op, int *nOperations) {
	operationList *auxOp;
	int id = 1;

	auxOp = newOperationNode();
	system("cls");

	if(auxOp==NULL) { 
		printf(_FG_RED"There is no more memory space. It is impossible to insert\n\n"_RESET);
		pauseProgram();
	}
	else {
		while((op->next) != NULL) {
			id = op->op.id + 1;
			op = op->next;
		}

		(*nOperations)++;
		op->op.id = id;
		readOperation(&op->op);
		op->next = auxOp;
	}
}
/**
 * It removes an operation from the list, and updates the proposals that are affected by the removal
 * 
 * @param opL operationList, a linked list of operations
 * @param nOperations number of operations in the list
 * @param pL pointer to the proposal list
 * @param jbL pointer to jobList
 * @param changeProposalCounter is a counter that counts the number of proposals that have been
 * changed.
 */
void removeOperation(operationList *opL, int *nOperations, proposalList **pL, jobList *jbL, int *changeProposalCounter) {
	operationList *y, *atras, *frente, *auxOp;
	int intElemRetirar;

	system("cls");
	y = opL;
	
	if((y->next)==NULL) { 
		printf(_FG_RED"No operations in the list\n"_RESET); 
	}
	else {
		intElemRetirar = askUserIntegers(_FG_YELLOW"What is the code whose operation you want to remove?\n"_RESET);

		if(intElemRetirar == opL->op.id) {
			system ("cls");
			
			(*nOperations)--;
			printf(_FG_YELLOW"The element has been removed\n"_RESET);
			listOperationNode(opL->op);
			opL = opL->next;
			free(y);
			(*pL) = updateEscalationProposal((*pL),jbL,&(*changeProposalCounter));
		}
		else {
			auxOp = opL;
			while((intElemRetirar != auxOp->op.id) && (auxOp->next != NULL)) {
				atras = auxOp;
				auxOp = auxOp->next;
				frente = auxOp->next;
			}
			
			if(intElemRetirar == auxOp->op.id) {
				atras->next = frente;
				system ("cls");
				
				(*nOperations)--;
				printf(_FG_YELLOW"The element has been removed\n"_RESET);
				listOperationNode(auxOp->op);
				free(auxOp);
				(*pL) = updateEscalationProposal((*pL),jbL,&(*changeProposalCounter));
			}
			else {
				system("cls");
				printf(_FG_RED"The element with code "_FG_CYAN"%d"_FG_RED" does not exist in the list"_RESET, intElemRetirar);
			}
		}
	}
}
/**
 * @brief It searches for a node in a linked list, and if it finds it, it asks the user for new data to
 * replace the old data. If succeded it updates the proposal
 * 
 * @param opL operationList *opL;
 * @param pL pointer to the proposal list
 * @param jbL
 * @param changeProposalCounter is a counter that counts the number of proposals that have been
 * changed.
 */
void editOperation(operationList *opL, proposalList **pL, jobList *jbL, int *changeProposalCounter) {
	int intElemEditar;

	system("cls");
	
	if((opL->next) == NULL) { 
		printf("No operations in the list\n"); 
	}
	else {
		intElemEditar = askUserIntegers(_FG_YELLOW"What is the code whose operation you want to edit?\n"_RESET);

		if(intElemEditar == opL->op.id) {
			system ("cls");
			printf(_FG_YELLOW"The element being edited\n"_RESET);
			listOperationNode(opL->op);
			readOperation(&(opL->op));
			(*pL) = updateEscalationProposal((*pL),jbL,&(*changeProposalCounter));
		}
		else {
			while((intElemEditar != opL->op.id) && (opL->next != NULL)) {
				opL = opL->next;
			}
			
			if(intElemEditar == opL->op.id) {
				system ("cls");
				printf(_FG_YELLOW"The element being edited\n"_RESET);
				listOperationNode(opL->op);
				readOperation(&(opL->op));
				(*pL) = updateEscalationProposal((*pL),jbL,&(*changeProposalCounter));
			}
			else {
				system("cls");
				printf(_FG_RED"The element with code "_FG_CYAN"%d"_FG_RED" does not exist in the list"_RESET, intElemEditar);
			}
		}
	}
}
/**
 * @brief Print the machines used to obtain the shortest result and the minimum number of
 * time units needed to complete the job
 * 
 * @param opL pointer to the first element of the list
 */
void determineShortestTime(operationList *opL) {
	int j = 0, soma = 0, min, mach;

	system("cls");
	if(opL->next==NULL) {
		printf(_FG_RED"No operations in the list\n"_RESET);
	}
	else {
		printf(_FG_YELLOW"Machines used to obtain the shortest result\n"_RESET);
		while(opL->next != NULL) { 
			min = 99999;
			for (j = 0; j < opL->op.quantMachines; ++j) {
				if(opL->op.machineAndTime[_TIMES*opL->op.quantMachines + j] < min) {
					min = opL->op.machineAndTime[_TIMES*opL->op.quantMachines + j];
					mach = opL->op.machineAndTime[_MACHINES*opL->op.quantMachines + j];
				}
			}
			printf(_FG_CYAN"%d"_FG_YELLOW, mach);
			if(opL->next->next != NULL)
				printf("->");

			soma = soma + min;
			opL = opL->next;
		}
		printf(_FG_YELLOW"\n\nMinimum number of time units needed to complete the job: "_FG_CYAN"%d\n"_RESET, soma);
	}
}
/**
 * @brief Print the machines used to obtain the longest result and the maximum number of time
 * units needed to complete the job
 * 
 * @param opL pointer to the first element of the list
 */
void determineLongestTime(operationList *opL) {
	int j = 0, soma = 0, max, mach;

	system("cls");
	if(opL->next==NULL) {
		printf(_FG_RED"No operations in the list\n"_RESET);
	}
	else {
		printf(_FG_YELLOW"Machines used to obtain the longest result\n"_RESET);
		while(opL->next != NULL) { 
			max = 0;
			for (j = 0; j < opL->op.quantMachines; j++) {
				if(opL->op.machineAndTime[_TIMES*opL->op.quantMachines + j] > max) {
					max = opL->op.machineAndTime[_TIMES*opL->op.quantMachines + j];
					mach = opL->op.machineAndTime[_MACHINES*opL->op.quantMachines + j];
				}
			}
			printf(_FG_CYAN"%d"_FG_YELLOW, mach);
			if(opL->next->next != NULL)
				printf("->");

			soma = soma + max;
			opL = opL->next;
		}
		printf(_FG_YELLOW"\n\nMaximum number of time units needed to complete the job: "_FG_CYAN"%d\n"_RESET, soma);
	}
}
/**
 * @brief It's a recursive function that calculates the average time of all possibilities
 * 
 * @param opL is a linked list of operations
 * @param id is the id of the possibility
 * @param soma is the sum of the times of the machines
 * @param media is the average time of all possibilities
 * 
 * @return The average time of all possibilities.
 */
void determineAverageTimeOfAllPossibilities(operationList *opL,int *id, int soma, float *media) {
	if(opL->next == NULL){
		(*id)++;
		printf(_FG_YELLOW"Possibility Number: %d --> Sum: "_FG_CYAN"%d\n"_RESET, (*id),soma);
		(*media) = (*media) + soma;
		return;
	}

	for(int i=0; i < opL->op.quantMachines; i++) 
		determineAverageTimeOfAllPossibilities(opL->next,&(*id),soma + opL->op.machineAndTime[_TIMES*opL->op.quantMachines + i],&(*media));
}
/**
 * @brief It calculates the average time of all possibilities
 * 
 * @param opL is the list of operations
 */
void determineAverageTime(operationList *opL) {
	int soma = 0, id = 0;
	float media = 0;

	system("cls");
	determineAverageTimeOfAllPossibilities(opL,&id,soma,&media);
	media = media/(float)id;

	printf(_FG_B_YELLOW"Average time of all possibilities: "_FG_B_CYAN"%.2f"_RESET"\n\n",media);
}
/**
 * @brief It takes the operation list of a job and calculates the best time to execute each operation, based
 * on the time it takes to execute it and the machines it can be executed on
 * 
 * @param opL a linked list of operations
 * @param jobId the id of the job
 * @param pL a pointer to a proposalList structure
 */
void calcEscalationProposal(operationList *opL, int jobId, proposalList *pL) {
	int i, j, z, minTime, mach, spaceFree = 0, opId, lastTimeUsed = 0;

	while(opL->next != NULL) {
		minTime = 99999;
		for (z = 0; z < opL->op.quantMachines; z++) {
			if(opL->op.machineAndTime[_TIMES*opL->op.quantMachines + z] < minTime) {
				minTime = opL->op.machineAndTime[_TIMES*opL->op.quantMachines + z];
				mach = opL->op.machineAndTime[_MACHINES*opL->op.quantMachines + z];
				opId = opL->op.id;
			}
		}
		
		for(i = lastTimeUsed; i < _MAXT; i++){
			if(pL->proposalData[mach-1][i] == NULL){
				for(j = i; j < i + minTime; j++) {
					if(pL->proposalData[mach-1][j] != NULL) {
						spaceFree = FALSE;
						break;
					}
					else
						spaceFree = TRUE;
				}

				if(spaceFree) {
					proposal *p = (proposal *) malloc(sizeof(proposal));
					p->jobId = jobId;
					p->opId = opId;
					p->time = minTime;

					for(j = i; j < i + minTime; j++) {
						pL->proposalData[mach-1][j] = p;
					}
					goto nextOperation;
				}
			}
		}

		nextOperation:
		lastTimeUsed = j;
		opL = opL->next;
	}
}
/**
 * @brief It goes through the tree in order, and for each node, it calculates the escalation proposal for the
 * job in that node
 * 
 * @param n a pointer to a jobList node
 * @param pL a pointer to a proposalList
 * 
 * @return the number of proposals that were created.
 */
void goThroughByOrderCalcProposal(jobList *n, proposalList *pL) {
	if(n == NULL)
		return;
	
	goThroughByOrderCalcProposal(n->left,pL);
	calcEscalationProposal(n->opL,n->jb.id,pL);
	goThroughByOrderCalcProposal(n->right,pL);
}
/**
 * @brief It saves the current job list in a file, then calculates the proposal and adds it to the proposal
 * list.
 * 
 * @param pL a pointer to a linked list of proposals
 * @param jbL jobList *jbL;
 * @param changeCount is a pointer to an integer that is used to keep track of the number of changes
 * made to the job list.
 * 
 * @return A pointer to a proposalList, the current version.
 */
proposalList *updateEscalationProposal(proposalList *pL, jobList *jbL, int *changeCount) {
	// char *versionsDirectory = "VersionsDirectory\\";
    // if (mkdir(versionsDirectory) == 1){}
    // else if(errno == EEXIST) {}
	// else 
    //     printf("Unable to create directory\nERROR number:%d",errno);

	if(strcmp(pL->proposalVersionFile,"--") == 0) {
		snprintf(pL->proposalVersionFile, sizeof(pL->proposalVersionFile), /*"VersionsDirectory"DIR_SEPARATOR*/"ProposalVersionNumber_%d.txt",(*changeCount));
		saveDataInFile(jbL,pL->proposalVersionFile);
		goThroughByOrderCalcProposal(jbL,pL);
		(*changeCount)++;
		return pL;
	}
	else {
		proposalList *p = (proposalList * ) malloc(sizeof(proposalList));
		if(p == NULL) {
			system("cls");
			printf(_FG_RED"Can't create list"_RESET"\n\n");
			pauseProgram();
		}
		else {
			snprintf(p->proposalVersionFile, sizeof(pL->proposalVersionFile), /*"VersionsDirectory"DIR_SEPARATOR*/"ProposalVersionNumber_%d.txt",(*changeCount));
			saveDataInFile(jbL,p->proposalVersionFile);
			goThroughByOrderCalcProposal(jbL,p);
			p->next = pL;
			(*changeCount)++;
			return p;
		}
	}
	return pL;
}
/**
 * @brief It prints the proposal in a way that is easy to read
 * 
 * @param pL is a pointer to a proposalList structure, the current version of the proposal
 */
void printEscalationProposal(proposalList *pL) {
	printf("\nPROPOSAL WITH:\nMAX NUMBER OF MACHINES-->%d\nMAX TIME-->%d\n",_MAXM,_MAXT);
	printf("\n\t|123|"
			"\n\t--> o primeiro numero representa job id"
			"\n\t--> o segundo numero representa a operacao Id"
			"\n\t--> o terceiro numero representa o tempo minimo ocupado pela operacao\n");
	for(int i = 0; i < _MAXM; i++) {
		printf("\nM%-2d--> ",i+1);
		for(int j = 0; j < _MAXT; j++) {
			if(pL->proposalData[i][j] != NULL)
				printf("%d%d%d|",pL->proposalData[i][j]->jobId,pL->proposalData[i][j]->opId,pL->proposalData[i][j]->time);
			else
				printf("-|");
		}
		printf("\n");
	}
	printf("\n\n\n");
}
/**
 * @brief It writes the data in the linked list to a file
 * 
 * @param opL a linked list of operations
 * @param id the current job id
 * @param f_JOB the file to write to
 */
void writeInFile(operationList *opL, int id, FILE *f_JOB) {
	int i;

	fprintf(f_JOB,"#%d\n", id);
	while(opL->next != NULL) {
		if(opL->op.quantMachines == 1) {
			fprintf(f_JOB,"(%d)\n", opL->op.machineAndTime[_MACHINES*opL->op.quantMachines + 0]);
			fprintf(f_JOB,"[%d]\n", opL->op.machineAndTime[_TIMES*opL->op.quantMachines + 0]);
		}
		else {
			for(i = 0; i < opL->op.quantMachines; ++i) {
				if( i == 0)
					fprintf(f_JOB,"(%d,", opL->op.machineAndTime[_MACHINES*opL->op.quantMachines + i]);
				else if((opL->op.quantMachines - i) != 1)
					fprintf(f_JOB,"%d,", opL->op.machineAndTime[_MACHINES*opL->op.quantMachines + i]);
				else
					fprintf(f_JOB,"%d)\n", opL->op.machineAndTime[_MACHINES*opL->op.quantMachines + i]);
			}
			for(i = 0; i < opL->op.quantMachines; ++i) {
				if( i == 0)
					fprintf(f_JOB,"[%d,", opL->op.machineAndTime[_TIMES*opL->op.quantMachines + i]);
				else if((opL->op.quantMachines - i) != 1)
					fprintf(f_JOB,"%d,", opL->op.machineAndTime[_TIMES*opL->op.quantMachines + i]);
				else
					fprintf(f_JOB,"%d]\n", opL->op.machineAndTime[_TIMES*opL->op.quantMachines + i]);
			}
		}
		opL = opL->next;
	}
}
/**
 * @brief It traverses the tree in order and writes the data to a file.
 * 
 * @param n the node of the tree
 * @param f_JOB the file to write to
 * 
 * @return the address of the node that was inserted.
 */
void orderTreeToSaveInFile(jobList *n, FILE *f_JOB) {
	if(n == NULL)
		return;

	orderTreeToSaveInFile(n->left,f_JOB);
	writeInFile(n->opL,n->jb.id,f_JOB);
	orderTreeToSaveInFile(n->right,f_JOB);
}
/**
 * @brief It opens a file, and then calls another function that will write the data to the file
 * 
 * @param jbL pointer to the jobList structure
 * @param fileName name of the file to save data
 */
void saveDataInFile(jobList *jbL, char *fileName) {
	FILE *f_JOB = fopen(fileName,"w");

	if(f_JOB != NULL) {
		orderTreeToSaveInFile(jbL, f_JOB);
	}
	fclose(f_JOB);
}
/**
 * @brief It asks the user if they want to save the data in the file, and if they do, it saves the data
 * 
 * @param jbL a pointer to the tree root 
 * 
 * @return the value of the variable opYN.
 */
void saveDataYN(jobList *jbL) {
	int opYN;

	if (jbL == NULL) {
		printf(_FG_CYAN"The list has no jobs!!"_RESET"\n");
	}
	else {
		printf(_FG_CYAN"Do you to save the data in the file??"_RESET"\n");
		opYN = yesNo();
		if(opYN != 0) {
			saveDataInFile(jbL,"dados.txt");
			return;
		}
	}
	return;
}
/**
 * @brief It's a recursive function that frees the memory allocated to the jobList struct and the
 * operationList struct
 * 
 * @param root the root of the tree
 * 
 * @return the root of the tree.
 */
void deallocate(jobList *root) {
	if(root == NULL)
		return;
	
	while((root->opL) != NULL) {
		free(root->opL->op.machineAndTime);
		root->opL->op.machineAndTime = NULL;
		free(root->opL);
		root->opL = NULL;
		root->opL = root->opL->next;
	}

	deallocate(root->right);
	deallocate(root->left);

	free(root);
}
/**
 * @brief It's a function that deallocates the memory of a linked list of proposals
 * 
 * @param pL pointer to the head of the linked list
 */
void deallocateProposal(proposalList *pL) {
	while((pL->next) != NULL) {
		for(int i = 0; i < _MAXM; i++) {
			for (int j = 0; j < _MAXT; j++)	{
				free(pL->proposalData[i][j]);
				pL->proposalData[i][j] = NULL;
			}
			
		}
		free(pL);
		pL = NULL;
		pL = pL->next;
	}
}
/**
 * @brief It asks the user for an integer, and if the user enters a non-integer, it asks the user to try
 * again.
 * 
 * @param textToAsk The text to ask the user.
 * 
 * @return the inputConverted variable.
 */
int askUserIntegers(const char *textToAsk) {
	int inputConverted;
	char *endptr, buf[1024];

	do {
		printf("%s",textToAsk);

		if(!fgets(buf, sizeof(buf), stdin)) {
			printf("Something went wrong try again\n\n");
			printf("Error: %d\n", errno);
			pauseProgram();
		}
		errno = 0; // reset error number
		inputConverted = strtol(buf, &endptr, 10);
		if(errno == EINVAL) {
			printf("Conversion error occurred: %d\n", errno);
			exit(0);
		}
		if(errno == ERANGE) {
			printf(_FG_RED"The number entered is either too large or too small."_RESET"\n\n");
		}
		else if (endptr == buf)	{
			// no character was read.
			printf(_FG_RED"No character was read."_RESET"\n");
		}
		else if ((*endptr) && (*endptr != '\n')) {
			// *endptr is neither end of string nor newline, so we didn't convert the *whole* input.
			printf(_FG_RED"No character was read."_RESET"\n");
		}
		else {
			return inputConverted;
		}
	}while(TRUE);
}
/**
 * @brief It asks the user to enter a yes or no answer and returns a 1 for yes and a 0 for no.
 * 
 * @return 1 or 0
 */
int yesNo() {
	char buf[1024];

	while(TRUE) {
		printf(_FG_YELLOW"Yes or No (Y - y or N - n): "_RESET);

		if(!fgets(buf, sizeof(buf), stdin)) {
			printf("Something went wrong try again\n\n");
			printf("Error: %d\n", errno);
			pauseProgram();
		}
		errno = 0;
		buf[strcspn(buf, "\n")] = 0;
		strlwr(buf);

		if(errno == EINVAL) {
			printf(_FG_RED"Conversion error occurred: %d"_RESET"\n", errno);
			exit(0);
		}
		if(errno == ERANGE) {
			printf(_FG_RED"The option entered is either too large or too small."_RESET"\n\n");
		}
		else if((strcmp(buf,"yes") != 0) && (strcmp(buf,"y") != 0) && (strcmp(buf,"no") != 0) && (strcmp(buf,"n") != 0)) {
			printf(_FG_RED"Please enter a Yes or No (Y - y or N - n)."_RESET"\n\n");
		}
		else if((strcmp(buf,"yes") == 0) || (strcmp(buf,"y") == 0)) {
			return 1;
		}
		else if((strcmp(buf,"no") == 0) || (strcmp(buf,"n") == 0)) {
			return 0;
		}
	}
}
/**
 * @brief It's a function that displays a main menu and gets the user's input
 * 
 * @param option pointer to the integer that will hold the user's input
 */
void menu(int *option) {
	int i, success;
	char *endptr, buf[1024];
	
	do {
		system("cls");
		success = 0;

		printf(_FG_CYAN"%c",201); for(i = 0; i < 77; i++) printf("%c",205); printf("%c\n",187);
		_printf_p("%1$c                                   "_FG_YELLOW"MENU"_FG_CYAN"                                      %1$c\n"
				"%1$c                                                                             %1$c\n"
				"%1$c   0 - Exit                                                                  %1$c\n"
				"%1$c   1 - List Job/s (in Order)      2 - Print Job tree       3 - Find job      %1$c\n"
				"%1$c   4 - Insert Job                 5 - Remove Job           6 - Edit Job      %1$c\n"
				"%1$c                                                                             %1$c\n"
				"%1$c   7 - Escalation proposal                                                   %1$c\n"
				"%1$c                                                                             %1$c\n",186);
		printf("%c",200); for(i = 0; i < 77; i++) printf("%c",205); printf("%c\nOption: "_RESET,188);

		if(!fgets(buf, sizeof(buf), stdin)) {
			printf("Something went wrong try again\n\n");
			printf("Error: %d\n", errno);
			pauseProgram();
		}
		errno = 0; // reset error number
		(*option) = strtol(buf, &endptr, 10);
		if(errno == EINVAL) {
			printf(_FG_RED"Conversion error occurred: %d"_RESET"\n", errno);
			exit(0);
		}
		if(errno == ERANGE) {
			printf(_FG_RED"The number entered is either too large or too small."_RESET"\n\n");
			pauseProgram();
		}
		else if (((*option) > 7) || ((*option) < 0)) {
			printf(_FG_RED"Please enter a number between 0 and 7."_RESET"\n\n");
			pauseProgram();
		}
		else if (endptr == buf)	{
			// no character was read.
			printf(_FG_RED"No character was read. Please enter a number between 0 and 7."_RESET"\n\n");
			pauseProgram();
		}
		else if ((*endptr) && (*endptr != '\n')) {
			// *endptr is neither end of string nor newline, so we didn't convert the *whole* input.
			printf(_FG_RED"No character was read. Please enter a number between 0 and 7."_RESET"\n\n");
			pauseProgram();
		}
		else {
			success = 1;
		}
	}while(!success);
}
/**
 * @brief It's a function that displays a menu, for edit jobs, and gets the user's input
 * 
 * @param optionEditJob pointer to the variable that will hold the user's input
 */
void menuEditJob(int *optionEditJob) {
	int i, success;
	char *endptr, buf[1024];
	
	do {
		system("cls");
		success = 0;

		printf(_FG_CYAN"%c",201); for(i = 0; i < 77; i++) printf("%c",205); printf("%c\n",187);
		_printf_p("%1$c                               "_FG_YELLOW"MENU - Edit Job"_FG_CYAN"                               %1$c\n"
				"%1$c                                                                             %1$c\n"
				"%1$c   0 - Back to main menu                                                     %1$c\n"
				"%1$c   1 - List Operations                      3 - Remove Operation             %1$c\n"
				"%1$c   2 - Insert Operation                     4 - Edit Operation               %1$c\n"
				"%1$c                                                                             %1$c\n"
				"%1$c   5 - Determine Shortest time                                               %1$c\n"
				"%1$c   6 - Determine Longest time                                                %1$c\n"
				"%1$c   7 - Determine Averege time of all possibilities                           %1$c\n"
				"%1$c                                                                             %1$c\n",186);
		printf("%c",200); for(i = 0; i < 77; i++) printf("%c",205); printf("%c\nOption: "_RESET,188);

		if(!fgets(buf, sizeof(buf), stdin)) {
			printf("Something went wrong try again\n\n");
			printf("Error: %d\n", errno);
			pauseProgram();
		}
		errno = 0; // reset error number
		(*optionEditJob) = strtol(buf, &endptr, 10);
		if(errno == EINVAL) {
			printf(_FG_RED"Conversion error occurred: %d"_RESET"\n", errno);
			exit(0);
		}
		if(errno == ERANGE) {
			printf(_FG_RED"The number entered is either too large or too small."_RESET"\n\n");
			pauseProgram();
		}
		else if (((*optionEditJob) > 7) || ((*optionEditJob) < 0)) {
			printf("Please enter a number between 0 and 7.\n\n");
			pauseProgram();
		}
		else if (endptr == buf)	{
			// no character was read.
			printf(_FG_RED"No character was read. Please enter a number between 0 and 7."_RESET"\n\n");
			pauseProgram();
		}
		else if ((*endptr) && (*endptr != '\n')) {
			// *endptr is neither end of string nor newline, so we didn't convert the *whole* input.
			printf(_FG_RED"No character was read. Please enter a number between 0 and 7."_RESET"\n\n");
			pauseProgram();
		}
		else {
			success = 1;
		}
	}while(!success);
}














