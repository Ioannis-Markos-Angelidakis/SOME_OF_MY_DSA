#include <iostream>
#include <ranges>
#include <variant>
#include <span>

#define T variant<int32_t, float, string>

using std::variant;
using std::span;
using std::string;

bool binary_search(const span<T>& array, T data);

void bubble_sort(span<T>&& array);

int32_t main() {
    std::array<T, 7> nums {2, 7, 6, 1, 4, 3, 5}, strs {"EFG", "CAB", "AAB", "AAA", "GHI", "DEF"};

    bubble_sort(nums);
    for(const T& num: std::views::iota(-2, 10)) {
        visit([](const auto& num){std::cout << "'"<< num << "' ";}, num);
        binary_search(nums, num)? std::cout << "FOUND\n": std::cout << "NOT FOUND\n";
    }
    
    bubble_sort(strs);
    for(const T& str: strs) {
        visit([](const auto& str){std::cout << "'"<< str << "' ";}, str);
        binary_search(strs, str)? std::cout << "FOUND\n": std::cout << "NOT FOUND\n";
    }
    return 0;
}

bool binary_search(const span<T>& array, T data) {
    uint32_t low = 0, high = array.size();
    
    do {
        uint32_t mid = low + (high - low) / 2;
        
        if(array[mid] == data) {
            return true;
        }else if(array[mid] > data) {
            high = mid;
        }else {
            low = mid + 1;
        }
        
    } while(low < high);
    
    return false;
}

void bubble_sort(span<T>&& array) {
    for(uint32_t i = 0; i < array.size() ;++i) {
        for(uint32_t j = 0; j < array.size() - i - 1 ;++j) {
            if(array[j] > array[j+1]) {
                T temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
            }
        }
    }
}
/*EOF*/