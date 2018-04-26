// COMP1521 18s1 Assignment 2
// Implementation of heap management system

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myHeap.h"

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

// initialise heap
int initHeap(int size)
{
   // TODO
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
   // TODO
   return NULL; // this just keeps the compiler quiet
}

// free a chunk of memory
void myFree(void *block)
{
   // TODO
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
