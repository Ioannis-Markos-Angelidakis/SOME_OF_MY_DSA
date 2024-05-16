#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define STR_SIZE 24

typedef void (*T)(void*);

typedef struct NODE {
    union {
        int32_t i32;
        float f32;
        char str[STR_SIZE];
        void* T; // Pointer for custom struct types
    } data;
    void (*print)(void*);
    struct NODE* prev;
} NODE;

typedef struct {
    NODE* top;
} STACK;

void i32(void* i32);

void f32(void* f32);

void str(void* str);

void PERSON_T(void* T);

void SHAPE_PRINT(void* T);

NODE* create_node(void* data, T type);

void push(STACK* stack, void* data, T type);

void pop(STACK* stack);

void print(STACK* stack);

void delete_stack(STACK* stack);

typedef struct {
    int32_t ID;
    char name[STR_SIZE];
} PERSON;

typedef struct {
    float a;
    float b;
} SHAPE;

int32_t main() {
    STACK stack = {NULL};
    PERSON person = {123456, "Alice"};
    SHAPE shape = {3.14, 6.6};
    float f32_num = 3.14;

    for(int32_t num = 0; num <= 5; ++num) {
        push(&stack, &num, i32);
    }
    push(&stack, &f32_num, f32);
    push(&stack, (char*)"Test", str);
    push(&stack, &person, PERSON_T);
    push(&stack, &shape, SHAPE_PRINT);
	
    print(&stack);
    delete_stack(&stack);
    return 0;
}

void i32(void* i32) {
    printf("%d ", *(int32_t*)i32);
}

void f32(void* f32) {
    printf("%.2f ", *(float*)f32);
}

void str(void* str) {
    printf("%s ", (char*)str);
}

void PERSON_T(void* T) {
    PERSON* person = (PERSON*)((NODE*)T)->data.T;
    
    i32(&person->ID); 
    str(&person->name);
}

void SHAPE_PRINT(void* T) {
    SHAPE* shape = (SHAPE*)((NODE*)T)->data.T;
    
    f32(&shape->a); 
    f32(&shape->b);
}

NODE* create_node(void* data, T type) {
    NODE* new_node = (NODE*)malloc(sizeof(NODE));
    if (new_node == NULL) {
        return NULL;
    }
	
    new_node->print = type;
    new_node->prev = NULL;

    if (type == i32) {
        new_node->data.i32 = *(int*)data;
    } else if (type == f32) {
        new_node->data.f32 = *(float*)data;
    } else if (type == str) {
        strncpy(new_node->data.str, (char*)data, STR_SIZE - 1);
        new_node->data.str[STR_SIZE - 1] = '\0';
    } else {
        new_node->data.T = data;
    }

    return new_node;
}

void push(STACK* stack, void* data, T type) {
    NODE* new_node = create_node(data, type);
    if (new_node == NULL) {
        return;
    }
	
    new_node->prev = stack->top;
    stack->top = new_node;
}

void pop(STACK* stack) {
    if (stack->top == NULL) {
        return;
    }
	
    NODE* temp = stack->top;
    stack->top = stack->top->prev;
    free(temp);
    temp = NULL;
}

void print(STACK* stack) {
    NODE* curr = stack->top;
	
    while (curr != NULL) {
        curr->print(&curr->data);
		printf("\n");
        curr = curr->prev;
    }
}

void delete_stack(STACK* stack) {
    while (stack->top != NULL) {
        pop(stack);
    }
}
/*EOF*/