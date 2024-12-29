#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "../include/pool.h"

poolNode* pool = NULL;

poolNode* poolAllocNode(char *data) {
	poolNode* newNode = (poolNode*)malloc(sizeof(poolNode));
	if (newNode == NULL){
		printf("[%s %d] String pool allocates a node failed.\n", __FILE__, __LINE__);
		return NULL;
	}
	newNode->data = (char *)malloc(strlen(data) + 1);
	if (newNode->data == NULL) {
		printf("[%s %d] Memory allocation failed.\n", __FILE__, __LINE__);
		free(newNode);
		return NULL;
	}
	strcpy(newNode->data, data);
	// Wrong line, it will write over the old memories
	// newNode->data = data;
	newNode->next = NULL;
	return newNode;
}

void poolPushBack(poolNode** pphead, char *data) {
	assert(pphead);

	poolNode* newNode = poolAllocNode(data);

	if (*pphead == NULL) {
		*pphead = newNode;
		return;
	}

	poolNode* ptail = *pphead;

	while (ptail->next) {
		ptail = ptail->next;
	}

	ptail->next = newNode;

	return;
}

void poolPushFront(poolNode** pphead, char *data) {
	assert(pphead);

	poolNode* newNode = poolAllocNode(data);

	newNode->next = *pphead;

	*pphead = newNode;
}

void poolPopBack(poolNode** pphead) {
	assert(pphead);
	assert(*pphead);
	if ((*pphead)->next == NULL) {
		free(*pphead);
		*pphead = NULL;
		return;
	}
	poolNode* ptail = *pphead;
	poolNode* prve = NULL;
	while (ptail->next) {
		prve = ptail;
		ptail = ptail->next;
	}
	if (prve != NULL) { // Check prve is not NULL
		prve->next = NULL;
		free(ptail);
	}
}
void poolPopFront(poolNode** pphead) {
	assert(pphead);
	assert(*pphead);

	poolNode* newnod = *pphead;

	*pphead = newnod->next;

	free(newnod);

	newnod = NULL;
}

void poolPrint(poolNode* phead) {
	poolNode* pcur = phead;
	while (pcur) {
		printf("%s->", pcur->data);
		pcur = pcur->next;
	}

	printf("NULL\n");
}

poolNode* poolFind(poolNode** pphead, char *data) {
	assert(pphead);

	poolNode* pcur = *pphead;

	while (pcur) {
		if (strcmp(pcur->data, data) == 0) {
			return pcur;
		}

		pcur = pcur->next;
	}

	return NULL;
}

void poolInsert(poolNode** pphead, poolNode* pos, char *data) {
	assert(pphead);
	assert(*pphead);
	assert(pos);

	poolNode* newnode = poolAllocNode(data);

	if (pos == *pphead) {
		poolPushFront(pphead, data);
		return;
	}

	poolNode* prev = *pphead;
	while (prev->next != pos) {
		prev = prev->next;
	}

	newnode->next = pos;
	prev->next = newnode;
}

void poolInsertAfter(poolNode** pphead, poolNode* pos, char *data) {
	assert(pphead);
	assert(*pphead);
	assert(pos);

	poolNode* newnode = poolAllocNode(data);

	newnode->next = pos->next;
	pos->next = newnode;
}

void poolErase(poolNode** pphead, poolNode* pos) {
	assert(pphead);
	assert(*pphead);
	assert(pos);
	poolNode* prev = *pphead;
	while (prev->next != pos) {
		prev = prev->next;
	}
	if (prev == NULL || prev->next == NULL) return; // Check leak
	poolNode* toDelete = prev->next;
	prev->next = toDelete->next;
	free(toDelete->data); // Free node data
	free(toDelete);
}

void poolEraseAfter(poolNode* pos) {
	assert(pos);
	assert(pos->next);

	poolNode* del = pos->next;
	pos->next = del->next;
	free(del);
}

void poolListDesTroy(poolNode** pphead) {
	assert(pphead);
	poolNode* pcur = *pphead;
	while (pcur) {
		poolNode* next = pcur->next;
		free(pcur->data); // Free node data
		free(pcur);
		pcur = next;
	}
	*pphead = NULL;
}