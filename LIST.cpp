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

struct LIST {
    optional<NODE*> head;
};

void print(const LIST& list);

void add_front(LIST& list, const T& data);

void add_back(LIST& list, const T& data);

void add_after(LIST& list, const T& data_after, const T& data);

void delete_node(LIST& list, const T& data_delete);

void delete_match(LIST& list, const T& data_delete);

void bubble_sort(LIST& list);

void delete_list(LIST& list);

int32_t main() {
    LIST list;

    for(const int32_t& num: std::views::iota(0, 6)) {
        add_front(list, num);
    }

    add_back(list, 5);
    add_after(list, 2, "A");
    add_after(list, 2, "B");
    //delete_node(list, "World");
    //delete_match(list, 5);
    bubble_sort(list);
    print(list);
    delete_list(list);
    return 0;
}

void print(const LIST& list) {
    optional<NODE*> curr = list.head;

    while(curr) {
        std::visit([](const auto& data) { std::cout << data << ' '; }, curr.value()->data);
        curr = curr.value()->next;
    }
}

void add_front(LIST& list, const T& data) {
    optional<NODE*> new_node = new NODE;

    new_node.value()->data = data;
    new_node.value()->next = list.head;
    list.head = new_node;
}

void add_back(LIST& list, const T& data) {
    optional<NODE*> new_node = new NODE;

    new_node.value()->data = data;

    if(!list.head) {
        list.head = new_node;
        return;
    }

    optional<NODE*> curr = list.head;

    while(curr.value()->next) {
        curr = curr.value()->next;
    }
    
    curr.value()->next = new_node;
}

void add_after(LIST& list, const T& data_after, const T& data) {
    if(!list.head) {
        return;
    }

    optional<NODE*> curr = list.head;
    while(curr.value()->data != data_after && curr.value()->next) {
        curr = curr.value()->next;
    }

    if(curr.value()->data != data_after) {
        visit([](const auto& data) { std::cout << "'" << data << "' NOT FOUND!\n"; }, curr.value()->data);
        return;
    }

    optional<NODE*> new_node = new NODE;
    new_node.value()->data = data;
    new_node.value()->next = curr.value()->next;
    curr.value()->next = new_node;
}

void delete_node(LIST& list, const T& data_delete) {
    if(!list.head) {
        return;
    }

    if(list.head.value()->data == data_delete) {
        list.head = list.head.value()->next;
        return;
    }

    optional<NODE*> curr = list.head, prev;
    while(curr.value()->data != data_delete && curr.value()->next) {
        prev = curr;
        curr = curr.value()->next;
    }

    if(curr.value()->data != data_delete) {
        std::visit([](const auto& data_delete) { std::cout << "'" << data_delete << "' NOT FOUND!\n"; }, data_delete);
        return;
    }

    (!prev) ? list.head = curr.value()->next : prev.value()->next = curr.value()->next;
    delete curr.value();
    curr.value() = nullptr;
    
}

void delete_match(LIST& list, const T& data_delete) {
    if(!list.head) {
        return;
    }

    optional<NODE*> curr = list.head, prev;
    while(curr) {
        if(curr.value()->data == data_delete) {
            (!prev) ? list.head = curr.value()->next : prev.value()->next = curr.value()->next;
            NODE* temp = curr.value();
            curr = curr.value()->next;
            delete temp;
            temp = nullptr;
        } else {
            prev = curr;
            curr = curr.value()->next;
        }
    }
}

void bubble_sort(LIST& list) {
    for(optional<NODE*> curr = list.head; curr ;curr = curr.value()->next) {
        for(optional<NODE*> next = curr.value()->next; next ;next = next.value()->next) {
            if(curr.value()->data > next.value()->data) {
                T temp = curr.value()->data;
                curr.value()->data = next.value()->data;
                next.value()->data = temp;
            }
        }
    }
}

void delete_list(LIST& list) {
    while(list.head) {
        NODE* temp = list.head.value();
        list.head = list.head.value()->next;
        delete temp;
        temp = nullptr;
    }
}
/*EOF*/