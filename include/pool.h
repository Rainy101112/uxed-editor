#ifndef INCLUDE_POOL_H_
#define INCLUDE_POOL_H

#include <stdio.h>

typedef struct stringPool {	// String pool link list
	char *data;
	struct stringPool *next;
} poolNode;


poolNode* poolAllocNode(char *data);
void poolPushBack(poolNode** pphead, char *data);
void poolPushFront(poolNode** pphead, char *data);
void poolPopBack(poolNode** pphead);
void poolPopFront(poolNode** pphead);
void poolPrint(poolNode* phead);
poolNode* poolFind(poolNode** pphead, char *data);
void poolInsert(poolNode** pphead, poolNode* pos, char *data);
void poolInsertAfter(poolNode** pphead, poolNode* pos, char *data);
void poolErase(poolNode** pphead, poolNode* pos);
void poolEraseAfter(poolNode* pos);
void poolListDesTroy(poolNode** pphead);

#endif // INCLUDE_POOL_H_