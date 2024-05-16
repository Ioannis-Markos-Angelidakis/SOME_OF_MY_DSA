#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

void i32(void* i32);

void f32(void* f32);

void str(void* str);

bool binary_search(void* data, void* array, size_t size, void (*type)(void*));

void bubble_sort(void* array, size_t size, void (*type)(void*));

int32_t main() {
    int32_t nums[] = {2, 7, 6, 1, 4, 3, 5};
    float f32_arr[] = {1.2, 3.4, 5.6, 7.8};
    char* str_arr[] = {"EFG", "CAB", "AAB", "AAA", "GHI", "DEF", "FGH", "BCD", "ABC"};
    size_t size = sizeof(nums) / sizeof(nums[0]);
    
    bubble_sort(&nums, size, i32);
    for (int32_t num = -2; num <= 10; ++num) {
        printf("'");
        i32(&num);
        printf("' %sFOUND!\n", (binary_search(&num, nums, size, i32)) ? "" : "NOT ");
    }
    
    float f32_t = 5.6; 
    printf("'");
    f32(&f32_t);
    printf("' %sFOUND!\n", (binary_search(&f32_t, f32_arr, size, f32)) ? "" : "NOT ");
    
    size = sizeof str_arr / sizeof str_arr[0];
    bubble_sort(&str_arr, size, str);
    for(uint32_t i = 0; i < size ;++i) {
        printf("'");
        str(str_arr[i]);
        printf("' %sFOUND!\n", (binary_search(str_arr[i], str_arr, size, str)) ? "" : "NOT ");
    }
    
    printf("'");
    str("AQA");
    printf("' %sFOUND!\n", (binary_search("AQA", str_arr, size, str)) ? "" : "NOT ");
    
    return 0;
}

void bubble_sort(void* array, size_t size, void (*type)(void*)) {
    for(size_t i = 0; i < size; ++i) {
        for(size_t j = 0; j < size - i - 1; ++j) {
            if(type == i32 && ((int32_t*)array)[j] > ((int32_t*)array)[j + 1]) {
                int32_t temp = ((int32_t*)array)[j];
                ((int32_t*)array)[j] = ((int32_t*)array)[j + 1];
                ((int32_t*)array)[j + 1] = temp;
            }else if(type == f32 && ((float*)array)[j] > ((float*)array)[j + 1]) {
                float temp = ((float*)array)[j];
                ((float*)array)[j] = ((float*)array)[j + 1];
                ((float*)array)[j + 1] = temp;
            }else if(type == str && strcmp(((char**)array)[j], ((char**)array)[j + 1]) > 0) {
                char* temp = ((char**)array)[j];
                ((char**)array)[j] = ((char**)array)[j + 1];
                ((char**)array)[j + 1] = temp;
            }
        }
    }
}

void i32(void* i32) {
    printf("%d", *((int32_t*)i32));
}

void f32(void* f32) {
    printf("%.2f", *((float*)f32));
}

void str(void* str) {
    printf("%s", (char*)str);
}

bool binary_search(void* data, void* array, size_t size, void (*type)(void*)) {
    uint32_t low = 0, high = size;

    do {
        uint32_t mid = low + (high - low) / 2;

        if((type == i32  && ((int32_t*)array)[mid] == *((int32_t*)data))   ||
          (type  == f32  && ((float*)array)[mid]   == *((float*)data))     ||
          (type  == str  && strcmp(((char**)array)[mid], (char*)data) == 0)) {
            return true;
        }else if((type == i32 && ((int32_t*)array)[mid] > *((int32_t*)data)) ||
                (type  == f32 && ((float*)array)[mid]   > *((float*)data))   ||
                (type  == str && strcmp(((char**)array)[mid], (char*)data) > 0)) {
            high = mid;
        } else {
            low = mid + 1;
        }
    } while (low < high);

    return false;
}
/*EOF*/