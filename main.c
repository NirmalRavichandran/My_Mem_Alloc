#include<stdio.h>
#include <stdlib.h>

#define MEMORY_SIZE 1024

char* getArray() {
    static char arr[MEMORY_SIZE];
    return arr;
}

void* allocate(size_t size) {
    char* ptr = getArray();
    static int free_index = 0;
    if (free_index+size <= MEMORY_SIZE) {
        char* a = &ptr[free_index];
        free_index += size;
        printf("%d",free_index);
        return a;
    }else {
        return NULL;
    }
}
int main() {
    char* p1 = allocate(100);
    char* p2 = allocate(200);
    char* p3 = allocate(800);  // should fail
    printf("%p %p %p\n", p1, p2, p3);
    return 0;
}