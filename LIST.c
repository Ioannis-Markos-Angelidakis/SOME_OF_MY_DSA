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
    void* next;
    void (*print)(void*);
} NODE;

typedef struct {
    NODE* head;
} LIST;

void i32(void* i32);

void f32(void* f32);

void str(void* str);

void print(LIST* list);

NODE* create_node(NODE* next, void* data, void (*type)(void*));

void add_front(LIST* list, void* data, void (*type)(void*));

void add_back(LIST* list, void* data, void (*type)(void*));

void add_after(LIST* list, void* data_after, void* data, void (*type)(void*));

void delete_node(LIST* list, void* data_delete);

void delete_match(LIST* list, void* data_delete);

void bubble_sort(LIST* list);

void delete_list(LIST* list);

int32_t main() {
    LIST list = {NULL};
    float f32_num = 3.14;
    int32_t i32_num = 2, i32_del = 5;

    for(int32_t num = 0; num <= 5; ++num) {
        add_front(&list, &num, i32);
    }
    add_front(&list, "QApple", str);
    add_back(&list, "Hello", str);
    add_back(&list, &i32_del, i32);
    add_after(&list, &i32_num, &f32_num, f32);

    delete_node(&list, "Hello");
    delete_match(&list, &i32_del);

    bubble_sort(&list);

    print(&list);
    delete_list(&list);
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

void print(LIST* list) {
    NODE* curr = list->head;

    while(curr) {
        curr->print(&curr->data);
        curr = curr->next;
    }
    printf("\n");
}

NODE* create_node(NODE* next, void* data, void (*type)(void*)) {
    NODE* new_node = malloc(sizeof(NODE));
    if(new_node == NULL) {
        return NULL;
    }

    new_node->next = next;
    new_node->print = type;
    
    if(type == i32) {
        new_node->data.i32 = *((int32_t*)data);
    } else if(type == f32) {
        new_node->data.f32 = *((float*)data);
    } else if(type == str) {
        strncpy(new_node->data.str, (char*)data, STR_SIZE - 1);
        new_node->data.str[STR_SIZE - 1] = '\0'; // Ensure null termination
    }

    return new_node;
}

void add_front(LIST* list, void* data, void (*type)(void*)) {
    NODE* new_node = create_node(list->head, data, type);
    list->head = new_node;
}

void add_back(LIST* list, void* data, void (*type)(void*)) {
    NODE* new_node = create_node(NULL, data, type);

    if(list->head == NULL) {
        list->head = new_node;
        return;
    }

    NODE* curr = list->head;
    while(curr->next) {
        curr = curr->next;
    }

    curr->next = new_node;
}

void add_after(LIST* list, void* data_after, void* data, void (*type)(void*)) {
    if (list->head == NULL) {
        printf("List is empty\n");
        return;
    }

    NODE* curr = list->head;
    while (curr != NULL) {
        if (curr->data.i32 == *((int32_t*)data_after) ||
            curr->data.f32 == *((float*)data_after)   ||
            strcmp(curr->data.str, (char*)data_after) == 0) {
                NODE* new_node = create_node(curr->next, data, type);
                curr->next = new_node;
                return;
        }
        curr = curr->next;
    }
    
    printf("Data not found!\n");
}

void delete_node(LIST* list, void* data_delete) {
    if(list->head == NULL) {
        printf("List is empty\n");
        return;
    }

    NODE* curr = list->head, *prev = NULL;
    while(curr->next != NULL && 
        (curr->data.i32 != *((int32_t*)data_delete)  ||
        curr->data.f32 != *((float*)data_delete)     ||
        strcmp(curr->data.str, (char*)data_delete) != 0)) {
            prev = curr;
            curr = curr->next;
    }

    (prev == NULL)? (list->head = curr->next) : (prev->next = curr->next);
    free(curr);
}

void delete_match(LIST* list, void* data_delete) {
    if(list->head == NULL) {
        printf("List is empty\n");
        return;
    }

    NODE* curr = list->head, *prev = NULL;
    while(curr != NULL) {
        if(curr->data.i32 == *((int32_t*)data_delete) ||
           curr->data.f32 == *((float*)data_delete)   ||
           strcmp(curr->data.str, (char*)data_delete) == 0) {
                (prev == NULL)? (list->head = curr->next) : (prev->next = curr->next);
                NODE* temp = curr;
                curr = curr->next;
                free(temp);
                temp = NULL;
        } else {
            prev = curr;
            curr = curr->next;
        }
    }
}

void bubble_sort(LIST* list) {
    if(list->head == NULL || list->head->next == NULL) {
        return;
    }

    for(NODE* curr = list->head; curr != NULL; curr = curr->next) {
        for(NODE* next = curr->next; next != NULL; next = next->next) {
            if(curr->print == i32 && next->print == i32 && curr->data.i32 > next->data.i32) {
                int32_t temp_i32 = curr->data.i32;
                curr->data.i32 = next->data.i32;
                next->data.i32 = temp_i32;
            } else if(curr->print == f32 && next->print == f32 && curr->data.f32 > next->data.f32) {
                float temp_f32 = curr->data.f32;
                curr->data.f32 = next->data.f32;
                next->data.f32 = temp_f32;
            } else if(curr->print == str && next->print == str && strcmp(curr->data.str, next->data.str) > 0) {
                char temp[STR_SIZE];
                strncpy(temp, curr->data.str, STR_SIZE); 
                temp[STR_SIZE - 1] = '\0'; 
                strncpy(curr->data.str, next->data.str, STR_SIZE);
                curr->data.str[STR_SIZE - 1] = '\0'; // Ensure null termination
                strncpy(next->data.str, temp, STR_SIZE); 
                next->data.str[STR_SIZE - 1] = '\0';
            } 
        }
    }
}

void delete_list(LIST* list) {
    NODE* curr = list->head, *prev = NULL;

    while(curr != NULL) {
        prev = curr;
        curr = curr->next;
        free(prev);
        prev = NULL;
    }
}
/*EOF*/