#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#define MEMORY_SIZE 1024

typedef struct Block {
    size_t size;
    int free;
    struct Block *next;
} Block;

char* getArray() {
    static char arr[MEMORY_SIZE];
    return arr;
}

Block* freeList = NULL;

void initMemory() {
    freeList = (Block*)getArray();
    freeList->size = MEMORY_SIZE - sizeof(Block);
    freeList->free = 1;
    freeList->next = NULL;
}
void* allocate(size_t size) {
    Block* curr = freeList;
    while (curr) {
        if (curr->free && curr->size >= size) {
            curr->free = 0;
            return (char*)curr + sizeof(Block);
        }
        curr = curr->next;
    }
    return NULL;
}
void freeMem(void* ptr) {
    if (!ptr) return;
    Block* curr = (Block*)((char*)ptr - sizeof(Block));
    curr->free=1;
}
int main() {
    initMemory();

    char* p1 = (char*)allocate(100);
    char* p2 = (char*)allocate(200);

    printf("p1 = %p, p2 = %p\n", p1, p2);

    freeMem(p1);
    char* p3 = (char*)allocate(50); // should reuse freed block
    printf("p3 = %p (reused p1 space)\n", p3);

    return 0;
}