#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define STR_SIZE 24

typedef struct {
    union {
        int32_t i32;
        float f32;
        char str[STR_SIZE];
    } data;
    void (*print)(void*);
    void* next;
} NODE;

typedef struct {
    NODE* front;
    NODE* back;
} QUEUE;

void i32(void* i32);

void f32(void* f32);

void str(void* str);

void print(QUEUE* queue);

NODE* create_node(void* data, void (*type)(void*));

void enqueue(QUEUE* queue, void* data, void (*type)(void*));

void dequeue(QUEUE* queue);

void destroy(QUEUE* queue);

int32_t main() {
    QUEUE queue = {NULL, NULL};
    float f32_num = 3.14;

    for (int32_t num = 0; num <= 5; ++num) {
        enqueue(&queue, &num, i32);
    }

    dequeue(&queue);
    enqueue(&queue, "Hello", str);
    enqueue(&queue, &f32_num, f32);
    print(&queue);
    destroy(&queue);
    return 0;
}

void i32(void* i32) {
    printf("%d ", *((int32_t*)i32));
}

void f32(void* f32) {
    printf("%.2f ", *((float*)f32));
}

void str(void* str) {
    printf("%s ", (char*)str);
}

void print(QUEUE* queue) {
    NODE* curr = queue->front;

    while(curr != NULL) {
        curr->print(&curr->data);
        curr = curr->next;
    }
}

NODE* create_node(void* data, void (*type)(void*)) {
    NODE* new_node = malloc(sizeof(NODE));
    if(new_node == NULL) {
        return NULL;
    }

    new_node->print = type;
    new_node->next = NULL;

    if (type == i32) {
        new_node->data.i32 = *((int32_t*)data);
    } else if (type == f32) {
        new_node->data.f32 = *((float*)data);
    } else if (type == str) {
        strncpy(new_node->data.str, (char*)data, STR_SIZE - 1);
        new_node->data.str[STR_SIZE - 1] = '\0'; // Ensure null termination
    }

    return new_node;
}

void enqueue(QUEUE* queue, void* data, void (*type)(void*)) {
    NODE* new_node = create_node(data, type);
    if (new_node == NULL) {
        return;
    }

    if (queue->front == NULL) {
        queue->front = queue->back = new_node;
        return;
    }
    
    queue->back->next = new_node;
    queue->back = new_node;
}

void dequeue(QUEUE* queue) {
    if (queue->front == NULL) {
        return;
    }

    NODE* temp = queue->front;
    queue->front = queue->front->next;
    free(temp);
    temp = NULL;
}

void destroy(QUEUE* queue) {
    while (queue->front != NULL) {
        dequeue(queue);
    }
}
/*EOF*/