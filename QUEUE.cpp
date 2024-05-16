#include <iostream>
#include <ranges>
#include <optional>
#include <variant>

#define T variant<int32_t, double, string>

using std::string;
using std::variant;
using std::optional;

struct NODE {
    T data;
    optional<NODE*> next;
};

struct QUEUE {
    optional<NODE*> front;
    optional<NODE*> back;
};

void print(const QUEUE& queue);

void enqueue(QUEUE& queue, const T& data);

void dequeue(QUEUE& queue);

void destroy(QUEUE& queue);

int32_t main() {
    QUEUE queue;

    for(const int32_t& num: std::views::iota(0, 6)) {
        enqueue(queue, num);
    }

    dequeue(queue);
    enqueue(queue, "Hello");
    enqueue(queue, 3.14);
    
    print(queue);
    destroy(queue);
    return 0;
}

void print(const QUEUE& queue) {
    optional<NODE*> curr = queue.front;

    while(curr) {
        std::visit([](const auto& data) { std::cout << data << " "; }, curr.value()->data);
        curr = curr.value()->next;
    }
}

void enqueue(QUEUE& queue, const T& data) {
    NODE* new_node = new NODE;

    new_node->data = data;
    
    if(!queue.front) {
        queue.front = queue.back = new_node;
        return;
    }
        
    queue.back.value()->next = new_node;
    queue.back = new_node;
}

void dequeue(QUEUE& queue) {
    if(!queue.front) {
        return;
    }

    NODE* temp = queue.front.value();
    queue.front = queue.front.value()->next;

    delete temp;
    temp = nullptr;
}

void destroy(QUEUE& queue) {
    while(queue.front) {
        dequeue(queue);
    }
}
/*EOF*/