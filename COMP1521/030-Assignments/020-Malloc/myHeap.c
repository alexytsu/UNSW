// COMP1521 18s1 Assignment 2
// Implementation of heap management system

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myHeap.h"

// a macro for a max "function"
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

	// would make more sense to include
	/*
	if(size < 0) return -1;
	but a strict interpretation of the specification doesn't require this
	*/

	heapSize = max(size, MIN_HEAP); // establish a minimum heap size
	if((heapSize % 4) != 0){ // round up to the nearest multiple of 4
		heapSize += 4 - (heapSize % 4);
	}

	// create the heap and store its start address
	heapMem = calloc(heapSize, 1); 
	if(heapMem == NULL) return -1;

	// initialise the heap as one large chunk of free space 
	Header *initialHeap = (Header *) heapMem;
	initialHeap->status = FREE;
	initialHeap->size = heapSize;

	// create a large enough array to hold max possible freeElems
	freeElems = heapSize/MIN_CHUNK;
	freeList = calloc(sizeof(Addr), freeElems);
	if(freeList == NULL) return -1;
	freeList[0] = heapMem;
	nFree = 1;

	return 0;
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
	/* This function first does a search through freeList to search for the
	best useable chunk. If no useable chunk is found, it returns NULL. Else,
	it returns the address of the useable memory with two subcases:

	1. There is enough free space but not enough for another MIN_CHUNK to be 
	created with the excess.
		- Alloc the whole chunk

	2. There is enough free space and enough leftover for a new FREE chunk to 
	be kept in the heap
		- Alloc the necessary space and create a "new" free chunk from the 
		remaining space

	Then the function tidies up and updates the freeList as necessary 
	*/

	// myMalloc cannot return zero or negative memory...
	if(size < 1) return NULL;

	if((size % 4) != 0){ // round up to the nearest multiple of 4
		size += 4 - (size % 4);
	}

	// our chunk needs "size" free space but the chunk also includes the header
	// (which cannot be used for storage).
	int desiredSize = size + sizeof(Header);

	// find the smallest useable chunk (if multiple same, use the first one)
	Header * chunk;
	Addr minChunkAddr = NULL;
	int minChunkSize = heapSize + 1;
	int freeListIndex = -1;
	for(int i = 0; i < nFree; i++) {
		chunk = (Header *)freeList[i];
		// first check if the chunk is FREE and large enough
		if(chunk->status == FREE && chunk->size >= desiredSize){
			// if it is smaller than the current smallest, it is more optimal
			if(chunk->size < minChunkSize){
				minChunkSize = chunk->size;
				minChunkAddr = freeList[i];
				freeListIndex = i;
			}
		}else{
			continue;
		}
	}

	// if freeListIndex hasn't been updated, 
	// no free chunk large enough was found
	if(freeListIndex == -1){
		return NULL;
	}

	// if the chunk is larger than we need, mark the unused portion of
	// the chunk as FREE. (only do this if the unused portion is large 
	// enough to be a chunk itself)
	if(minChunkSize >= desiredSize + MIN_CHUNK){
		// the slot in freeList holding the newly allocated chunk is perfectly positioned to hold
		// the address of its trailing half
		freeList[freeListIndex] = minChunkAddr + desiredSize;
		// update the header values for the new block
		chunk = (Header *) freeList[freeListIndex];
		chunk->size = minChunkSize - desiredSize;
		chunk->status = FREE;
		
		// update the header values for the allocated block
		chunk = (Header *)minChunkAddr;
		chunk->size = desiredSize; 
		chunk->status = ALLOC;
		nFree ++;
	}else{ // just use the whole chunk
		// shuffle the entries in freeList down now that a free chunk is allocated
		for(int i = freeListIndex; i < nFree - 1; i++){
			freeList[i] = freeList[i+1];
		}
		freeList[nFree - 1] = NULL;

		// no need to update the chunk->size
		chunk = (Header *)minChunkAddr;
		chunk->status = ALLOC;
	}

	// mark the allocated chunk and update its header
	nFree --; 

	return minChunkAddr + sizeof(Header); // return the address of the usable memory
}

// free a chunk of memory
void myFree(void *block)
{
	/*
	This function sets the header of the chunk to be freed to FREE and then updates 
	freeList and merges any adcjacent FREE blocks in the heap.
	*/

	// find the header of the memory in question
	block -= sizeof(Header);
	Header * chunk = (Header *) block;

	// check the chunk is valid for free-ing
	Addr heapTop = (Addr)((char *)heapMem + heapSize);
	if(chunk == NULL || (Addr) chunk < heapMem || (Addr) chunk >= heapTop || chunk->status != ALLOC){
		fprintf(stderr, "Attempt to free unallocated chunk\n");
		exit(1);
	}

	// mark the chunk as freed
	chunk->status = FREE;

	// find where to slot it in to freeList
	int index = 0;
	while(block > freeList[index]){
		index++;
		if(index == nFree) break;
	}

	// shuffle entries in freeList to make space for the newly freed chunk
	for(int i = nFree; i > index; i--){
		freeList[i] = freeList[i-1];
	}

	// add the newly freed chunk into the list
	freeList[index] = block;
	nFree++;
	
	// if a block is freed next to an already free block, we should merge the two
	mergeFree();
}

// merge adjacent FREE chunks in the heap
static void mergeFree()
{
	// no merging possible
	if(nFree <= 1) return;

	/*
	We know that freeList stores all freeChunks and stores them 
	in ascending order by address.

	So we go through this list and find if any of the free chunks
	are adjacent to eachother.
	- For each chunk, we store the addr of the next chunk in "adjacentChunk"
	- If the next chunk in freeList matches the addr of "adjacentChunk" then
	we know that these two chunks are adjacent and are both FREE (since they
	must come from freeList)
	*/

	int merged = 0; // flag to check if a merge occurred
	Header * chunk;
	Header * mergeChunk;
	Addr adjacentChunk = NULL; // holds address of the chunk following a free chunk

	for(int i = 0; i < nFree; i ++){ // loop through all the free chunks
		chunk = (Header *) freeList[i];

		// if it is adjacent to the previous chunk, merge the two
		if(chunk == adjacentChunk){
			// find the two headers we need to update
			chunk = (Header *) freeList[i-1];
			mergeChunk = (Header *) freeList[i];
			// increase the size of the chunk appropriately
			chunk->size += mergeChunk->size;

			// shuffle entries in since there is now one less entry
			for(int j = i; j < nFree - 1; j++){
				freeList[j] = freeList[j+1];
			}

			// two free blocks become one free block
			nFree--;
			merged = 1;
			break;
		}
		adjacentChunk = (Addr)chunk + chunk->size;
	}

	// if a merge occurred, there may be another merge necessary say we free B of
	// A|B|C where A and C are both FREE. By running the second check we know that
	// after A and B are merged, the new (AB) and C will also be merged.
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
