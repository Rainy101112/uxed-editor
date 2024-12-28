#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

int fd = 0;
int showpmt = 0;
char *filepath;

int modea();
int modei();
int looping();

typedef struct stringPool {
	char *data;
	struct stringPool *next;
} poolNode;

poolNode* pool = NULL;

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

poolNode* poolAllocNode(char *data) {
	poolNode* newNode = (poolNode*)malloc(sizeof(poolNode));
	if (newNode == NULL){
		printf("String pool allocates a node failed.\n");
		return NULL;
	}
	newNode->data = (char *)malloc(strlen(data) + 1);
	if (newNode->data == NULL) {
		printf("Memory allocation failed.\n");
		free(newNode);
		return NULL;
	}
	strcpy(newNode->data, data);
	// 错误的行，这会覆盖之前分配的内存
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
	if (prve != NULL) { // 确保 prve 不是 NULL
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
	if (prev == NULL || prev->next == NULL) return; // 检查边界条件
	poolNode* toDelete = prev->next;
	prev->next = toDelete->next;
	free(toDelete->data); // 释放节点数据的内存
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
		free(pcur->data); // 释放节点数据的内存
		free(pcur);
		pcur = next;
	}
	*pphead = NULL;
}

int modea(){
	char command[32768];

	while (1){
		scanf("%s", command);

		if ((!strcmp(command, ".")) != 1){
			poolPushBack(&pool, command);
			poolPushBack(&pool, "\n");
			continue;
		} else {
			break;
		}
	}

	return 0;
}

int modei(){
	return 0;
}

long long getFilesize(){
	off_t size = lseek(fd, 0, SEEK_END);

	if (size == -1) {
		printf("lseek failed");
		return -1;
	} else {
		return (long long)size;
	}
}

int looping(){
	char command[32768];

	while (1){
		if (showpmt == 1){
			printf("*");
		}
		scanf("%s", command);

		if ((!strcmp(command, "f")) == 1){
			printf("%s\n", filepath);

		} else 
		if ((!strcmp(command, "a")) == 1){
			modea();

		} else 
		if ((!strcmp(command, "w")) == 1){
			poolNode* pcur = pool;

			while (pcur) {
				ssize_t written = write(fd, pcur->data, strlen(pcur->data));
				if (written == -1) {
					printf("Write failed");
					break;
				}
				pcur = pcur->next;
			}

			long size = getFilesize();

			if (size != -1) {
				printf("%lld\n", (long long)size); // Show current file size(bytes).
			}

		} else 
		if ((!strcmp(command, "P")) == 1){
			showpmt = 1;

		} else 
		if ((!strcmp(command, "q")) == 1){
			poolListDesTroy(&pool);
			return 0;
		}
		else {
			printf("?\n");
		}
	}

	return 0;
}

int main(int argc, char **argv){
	if (argc > 1){
		if (argv[1][0] == '-' || (argv[1][0] == '-' && argv[1][1] == '-')) {
			if ((!strcmp(argv[1], "-h")) == 1 || (!strcmp(argv[1], "--help")) == 1){
				printf("Uinxed ed is a line-oriented text editor. It is used to create, display,\n"
						"modify and otherwise manipulate text files, both interactively and via\n"
						"shell scripts. A restricted version of ed, red, can only edit files in\n"
						"the current directory and cannot execute shell commands. Ed is the	\n"
						"'standard' text editor in the sense that it is the original editor for\n"
						"Unix, and thus widely available. For most purposes, however, it is	\n"
						"superseded by full-screen editors such as GNU Emacs or GNU Moe.\n"
						"\n"
						"Usage: ed [options] [file]\n"
						"\n"
						"Options:\n"
						"  -h, --help                 display this help and exit\n"
						"  -V, --version              output version information and exit\n"
						"  -E, --extended-regexp      use extended regular expressions\n"
						"  -G, --traditional          run in compatibility mode\n"
						"  -l, --loose-exit-status    exit with 0 status even if a command fails\n"
						"  -p, --prompt=STRING        use STRING as an interactive prompt\n"
						"  -q, --quiet, --silent      suppress diagnostics written to stderr\n"
						"  -r, --restricted           run in restricted mode\n"
						"  -s, --script               suppress byte counts and '!' prompt\n"
						"  -v, --verbose              be verbose; equivalent to the 'H' command\n"
						"      --strip-trailing-cr    strip carriage returns at end of text lines\n"
						"\n"
						"Start edit by reading in 'file' if given.\n"
						"If 'file' begins with a '!', read output of shell command.\n"
						"\n"
						"Exit status: 0 for a normal exit, 1 for environmental problems\n"
						"(file not found, invalid command line options, I/O errors, etc), 2 to\n"
						"indicate a corrupt or invalid input file, 3 for an internal consistency\n"
						"error (e.g., bug) which caused ed to panic.\n"
						);
			} else 
			if ((!strcmp(argv[1], "-v")) == 1 || (!strcmp(argv[1], "--version")) == 1){
				printf(
					"Uinxed ed 0.1\n"
					"Copyright (C) 2024 Rainy101112.\n"
					"License MIT. <https://opensource.org/license/MIT> <https://mit-license.org/>\n"
					"This is free software: you are free to change and redistribute it.\n"
				);
			} 
			else {
				printf("ed: Wrong options or options is unavailable.\n");
			}
		} else {
			pool = NULL;
			filepath = strdup(argv[1]); // 使用 strdup 复制字符串

			fd = open(filepath, O_RDWR);

			if (fd == -1){
				printf("ed: Could not open file: %s\n", filepath);
				free(filepath); // 释放 filepath 内存
				return -1;
			}
			
			long size = getFilesize();

			if (size != -1) {
				printf("%lld\n", (long long)size); // Show current file size(bytes).
			}

			looping();
			close(fd); // 关闭文件描述符
			free(filepath); // 释放 filepath 内存
			}
	} else {
		printf("Usage: ed [Options] [file]\n");
	}

	return 0;
}