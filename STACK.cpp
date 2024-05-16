#include <iostream>
#include <ranges>
#include <optional>
#include <variant>

#define T variant<int32_t, double, string>

using std::string;
using std::optional;
using std::variant;

struct NODE {
    T data;
    optional<NODE*> prev;
};

struct STACK {
    optional<NODE*> top;
};

void print(const STACK& stack);

void push(STACK& stack, const T& data);

void pop(STACK& stack);

void destroy(STACK& stack);

int32_t main() {
    STACK stack; 

    for(const int32_t num: std::views::iota(0, 6)) {
        push(stack, num);
    }
    
    pop(stack);
    push(stack, "Hello");
    push(stack, 3.14);
    print(stack);

    destroy(stack);
    return 0;
}

void print(const STACK& stack) {
    optional<NODE*> curr = stack.top;

    while(curr) {
        std::visit([&](const auto& data) {
            std::cout << data << '\n';
        }, curr.value()->data);
        curr = curr.value()->prev;
    }
}

void push(STACK& stack, const T& data) {
    NODE* new_node = new NODE;

    new_node->data = data;
    new_node->prev = stack.top;
    stack.top = new_node;
}

void pop(STACK& stack) {
    if(stack.top) {
        NODE* curr = stack.top.value();
        stack.top = curr->prev;
        delete curr;
        curr = nullptr;
    }
}

void destroy(STACK& stack) {
    while(stack.top) {
        pop(stack);
    }
}
/*EOF*/