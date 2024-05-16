#include <iostream>
#include <vector>

/*
* PRIORITY QUEUE MIN-HEAP
*/

void heapify_up(std::vector<int32_t>& heap, const uint32_t& index) {
    if(index == 0) {
        return;
    }
    
    uint32_t parent_index = (index - 1) / 2;
    
    if(heap.at(parent_index) > heap.at(index)) {
        std::swap(heap.at(parent_index), heap.at(index));
        heapify_up(heap, parent_index);
    }
}

void heapify_down(std::vector<int32_t>& heap, const uint32_t& index) {
    uint32_t left_child_index = index * 2 + 1;
    uint32_t right_child_index = index * 2 + 2; 
    
    if(index >= heap.size() -1 || left_child_index >= heap.size() - 1) {
        return;
    }
    
    int32_t left_child = heap.at(left_child_index);
    int32_t right_child = heap.at(right_child_index);
    int32_t curr = heap.at(index);
    
    if(left_child > right_child && curr > right_child) {
        std::swap(heap.at(right_child_index), heap.at(index));
        heapify_down(heap, right_child_index);
    }else if(right_child > left_child && curr > left_child) {
        std::swap(heap.at(left_child_index), heap.at(index));
        heapify_down(heap, left_child_index);
    }
    
}

void insert(std::vector<int32_t>& heap, const int32_t& value) {
    heap.emplace_back(value);
    heapify_up(heap, heap.size() - 1);
}

void heap_remove(std::vector<int32_t>& heap) {
    if (heap.size() - 1 == 0) {
        return;
    }
    
    heap.erase(heap.begin());
    
    heapify_down(heap, 0);
}

int32_t main() {
    std::vector<int32_t> heap;
    heap.reserve(6);
    
    insert(heap, 5);
    insert(heap, 3);
    insert(heap, -5);
    insert(heap, 8);
    insert(heap, -2);
    insert(heap, 1);
    
    //heap_remove(heap);

    for (const int32_t& element: heap) {
        std::cout << element << " ";
    }

    return 0;
}
/*EOF*/