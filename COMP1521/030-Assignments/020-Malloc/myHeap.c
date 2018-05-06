// COMP1521 18s1 Assignment 2
// Implementation of heap management system

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myHeap.h"

#define max(A, B) ((A > B) ? (A) : (B))

// minimum total space for heap
#define MIN_HEAP  4096
// minimum amount of space for a free Chunk (excludes Header)
#define MIN_CHUNK 32

#define ALLOC     0x55555555
#define FREE      0xAAAAAAAA

typedef unsigned int uint;   // counters, bit-strings, ...

typedef void *Addr;          // addresses

typedef struct {             // headers for Chunks
	uint  status;             // status (ALLOC or FREE)
	uint  size;               // #bytes, including header
} Header;

static Addr  heapMem;        // space allocated for Heap
static int   heapSize;       // number of bytes in heapMem
static Addr *freeList;       // array of pointers to free chunks
static int   freeElems;      // number of elements in freeList[]
static int   nFree;          // number of free chunks

static void mergeFree();

// initialise heap
int initHeap(int size)
{
	heapSize = max(size, MIN_HEAP); // establish a minimum heap size
	if((heapSize % 4) != 0){ // round up to the nearest multiple of 4
		heapSize += 4 - (heapSize % 4);
	}

	heapMem = calloc(heapSize, 1); 
	if(heapMem == NULL) return -1;

	Header *initialHeap = (Header *) heapMem;
	initialHeap->status = FREE;
	initialHeap->size = heapSize;

	freeElems = heapSize/MIN_CHUNK;
	freeList = calloc(sizeof(Addr), freeElems);
	freeList[0] = heapMem;
	nFree = 1;

	return 0; // this just keeps the compiler quiet
}

// clean heap
void freeHeap()
{
	free(heapMem);
	free(freeList);
}

// allocate a chunk of memory
void *myMalloc(int size)
{
	if(size < 1) return NULL;

	if((size % 4) != 0){ // round up to the nearest multiple of 4
		size += 4 - (size % 4);
	}

	int desiredSize = size + sizeof(Header);

	// find the smallest useable chunk
	Header * chunk;
	Addr minChunkAddr = NULL;
	int minChunkSize = heapSize + 1;
	int freeListIndex = -1;
	for(int i = 0; i < nFree; i++) {
		chunk = (Header *)freeList[i];
		if(chunk->status == FREE){
			if(chunk->size > desiredSize && chunk->size < minChunkSize){
				minChunkSize = chunk->size;
				minChunkAddr = freeList[i];
				freeListIndex = i;
			}
		}else{
			continue;
		}
	}

	if(freeListIndex == -1){
		return NULL;
	}

	if(minChunkSize >= desiredSize + MIN_CHUNK){
		freeList[freeListIndex] = minChunkAddr + desiredSize;
		chunk = (Header *) freeList[freeListIndex];
		chunk->size = minChunkSize - desiredSize;
		chunk->status = FREE;
		nFree++;
	}else{
		for(int i = freeListIndex; i < nFree - 1; i++){
			freeList[i] = freeList[i+1];
		}
		freeList[nFree - 1] = NULL;
	}

	chunk = (Header *)minChunkAddr;
	chunk->size = desiredSize;
	chunk->status = ALLOC;
	nFree --;


	return minChunkAddr + sizeof(Header); // this just keeps the compiler quiet
}

// free a chunk of memory
void myFree(void *block)
{
	printf("Freeing!\n");
	block -= sizeof(Header);
	Header * chunk = (Header *) block;
	if(chunk->status != ALLOC){
		fprintf(stderr, "Attempt to free unallocated chunk\n");
		exit(1);
	}

	chunk->status = FREE;
	
	int index = 0;
	while(block > freeList[index]){
		index++;
		if(index == nFree) break;
	}

	for(int i = nFree; i > index; i--){
		freeList[i] = freeList[i-1];
	}

	freeList[index] = block;

	nFree++;
	
	mergeFree();
}

static void mergeFree()
{
	printf("\tTesting Merging\n");
	int merged = 0;

	Header * chunk;
	Header * mergeChunk;
	int previousFree = 0;
	for(int i = 0; i < nFree; i ++){
		chunk = (Header *) freeList[i];
		
		if(chunk->status == FREE && previousFree){
			chunk = (Header *) freeList[i-1];
			mergeChunk = (Header *) freeList[i];
			
			chunk->size += mergeChunk->size;

			for(int j = i; j < nFree - 1; j++){
				freeList[j] = freeList[j+1];
			}
			
			nFree--;
			
			merged = 1;
			printf("\t\tMerged!\n");
			dumpHeap();
			break;
		}
		previousFree = (chunk->status == FREE) ? 1:0;
	}


	if(merged){
		mergeFree();
	}
}

// convert pointer to offset in heapMem
int  heapOffset(void *p)
{
	Addr heapTop = (Addr)((char *)heapMem + heapSize);
	if (p == NULL || p < heapMem || p >= heapTop)
		return -1;
	else
		return p - heapMem;
}

// dump contents of heap (for testing/debugging)
void dumpHeap()
{
	Addr    curr;
	Header *chunk;
	Addr    endHeap = (Addr)((char *)heapMem + heapSize);
	int     onRow = 0;

	curr = heapMem;
	while (curr < endHeap) {
		char stat;
		chunk = (Header *)curr;
		switch (chunk->status) {
		case FREE:  stat = 'F'; break;
		case ALLOC: stat = 'A'; break;
		default:    fprintf(stderr,"Corrupted heap %08x\n",chunk->status); exit(1); break;
		}
		printf("+%05d (%c,%5d) ", heapOffset(curr), stat, chunk->size);
		onRow++;
		if (onRow%5 == 0) printf("\n");
		curr = (Addr)((char *)curr + chunk->size);
	}
	if (onRow > 0) printf("\n");
}
