#include <iostream>
#include <optional>
#include <ranges>

using std::optional;

struct NODE {
    int32_t data;
    optional<NODE*> left;
    optional<NODE*> right;
};

struct TREE {
    optional<NODE*> root;
};

void insert_node(NODE* root, NODE* new_node) {
    static int32_t count = 1;
    
    if(!root) {
        count = 1;
        return;
    }
    
    if(!root->left) {
        root->left = new_node;
    }else if(!root->right) {
        root->right = new_node;
    }else if(count % 2 == 0) {
        insert_node(root->left.value(), new_node);
        ++count;
    }else if(count % 2 != 0) {
        insert_node(root->right.value(), new_node);
        ++count;
    }
}

void create_node(TREE& tree, const int32_t& data) {
    NODE* new_node = new NODE;
    new_node->data = data;

    if(!tree.root) {
        tree.root = new_node;
        insert_node(nullptr, nullptr);
    }else {
        insert_node(tree.root.value(), new_node);
    }
}

void pre_order(const TREE& tree) {
    if(tree.root) {
        std::cout << " " << tree.root.value()->data;
        pre_order({tree.root.value()->left});
        pre_order({tree.root.value()->right});
    }
}

void in_order(const TREE& tree) {
    if(tree.root) {
        in_order({tree.root.value()->left});
        std::cout << " " << tree.root.value()->data;
        in_order({tree.root.value()->right});
    }
}

void post_order(const TREE& tree) {
    if(tree.root) {
        post_order({tree.root.value()->left});
        post_order({tree.root.value()->right});
        std::cout << " " << tree.root.value()->data;
    }
}

void delete_tree(const TREE& tree) {
    if(tree.root) {
        delete_tree({tree.root.value()->left});
        delete_tree({tree.root.value()->right});
        NODE* temp = tree.root.value();
        delete temp;
        temp = nullptr;
    }
}

int32_t main() {
    TREE tree;

    for(const int32_t& num: std::views::iota(0, 6)) {
        create_node(tree, num);
    }
    
    std::cout << "Preorder  traversal: ";
    pre_order(tree);
    std::cout << "\nInorder   traversal: ";
    in_order(tree);
    std::cout << "\nPostorder traversal: ";
    post_order(tree);
    delete_tree(tree);
}
/*EOF*/