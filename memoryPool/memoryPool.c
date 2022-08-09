// memoryPool.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <malloc.h>


typedef struct _memPool
{
	char* next;
	char* end;
} MemPool;

MemPool* memPool_create(size_t size);
void memPool_destroyMemory(MemPool* p);
size_t memPool_getAvailableMemory(MemPool* p);
void* memPool_alloc(MemPool* p, size_t size);


int main()
{
	MemPool*p;
	char *c,*c1,*c2;
	p = memPool_create(1000);
	printf("get available mem %zu\n", memPool_getAvailableMemory(p));

	c = (char*)memPool_alloc(p, 100);
	if (c != NULL) {
		printf("get available mem %zu\n", memPool_getAvailableMemory(p));
	}
	else {
		printf("alloc memory failed\n");
	}
	c[0] = 'g';
	c[1] = 'a';
	c[2] = 'l';
	c[3] = '\0';

	printf("c2=%s\n", c);

	/*
	c2[0] = 'g';
	c2[1] = 'a';
	c2[2] = 'l';
	c2[3] = '\0';

	printf("c2=%s\n", c2);
	*/

	c1 = (char*)memPool_alloc(p, 901);
	if (c1 != NULL) {
		printf("get available mem %zu\n", memPool_getAvailableMemory(p));
	}
	else {
		printf("alloc memory failed\n");
	}

	memPool_destroyMemory(p);
	printf("get available mem %zu\n", memPool_getAvailableMemory(p));

   
}

MemPool* memPool_create(size_t size)
{
	MemPool* p = (MemPool*)malloc(size + sizeof(MemPool));
	p->next = (char*)&p[1];//p->next point to start useable memory
	p->end = p->next + size;
	return p;
}

void memPool_destroyMemory(MemPool* p) {
	free(p);
}

size_t memPool_getAvailableMemory(MemPool* p) {
	return p->end - p->next;
}

void* memPool_alloc(MemPool* p, size_t size) {
	if (memPool_getAvailableMemory(p) < size) {
		return NULL;
	}
	void* mem = (void*)p->next;
	p->next += size;
	return mem;
}
