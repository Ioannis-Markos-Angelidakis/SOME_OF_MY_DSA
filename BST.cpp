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
    if(new_node->data < root->data) {
        if(root->left) {
            insert_node(root->left.value(), new_node);
        }else {
            root->left = new_node;
        }
    }else {
        if(root->right) {
            insert_node(root->right.value(), new_node);
        }else {
            root->right = new_node;
        }
    }
}

void create_node(TREE& tree, const int32_t& data) {
    NODE* new_node = new NODE;
    new_node->data = data;

    if(!tree.root) {
        tree.root = new_node;
    }else {
        insert_node(tree.root.value(), new_node);
    }
}

void print(const TREE& tree) {
    if(tree.root) {
        print({tree.root.value()->left});
        std::cout << tree.root.value()->data << " ";
        print({tree.root.value()->right});
    }
}

bool search(const TREE& tree, const int32_t& data) {
    if(!tree.root) {
        return false;
    }
    
    if(tree.root.value()->data == data) {
        return true;
    } else if(tree.root.value()->data > data) {
        return search({tree.root.value()->left}, data);
    }else {
        return search({tree.root.value()->right}, data);
    }
}

NODE* delete_node(NODE* root, const int32_t& data) {
    if (!root)
        return root;

    if (root->data > data) {
        root->left = delete_node(root->left.value(), data);
        return root;
    }else if (root->data < data) {
        root->right = delete_node(root->right.value(), data);
        return root;
    }

    if(!root->left) {
        NODE* temp = root->right.value();
        delete root;
        root = nullptr;
        return temp;
    }else if (!root->right) {
        NODE* temp = root->left.value();
        delete root;
        root = nullptr;
        return temp;
    }else {
        NODE* successor_parent = root, *successor = root->right.value();
        while (successor->left) {
            successor_parent = successor;
            successor = successor->left.value();
        }

        if (successor_parent != root)
            successor_parent->left = successor->right;
        else
            successor_parent->right = successor->right;

        root->data = successor->data;

        delete successor;
        successor = nullptr;
        return root;
    }
}

void remove_node(TREE& tree, const int32_t& data) {
    if (!tree.root) {
        std::cout << "\nTree is empty.";
        return;
    }
    
    tree.root = delete_node(tree.root.value(), data);
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
    std::array nums {5, 1, 9, 2, 7, 3, 6, 4, 8};
    
    for(const int32_t& num: nums) {
        create_node(tree, num);
    }
    
    print(tree);
    
    /*for(const int32_t& num: std::views::iota(-2, 12)) {
        std::cout << "\n'" << num << "' ";
        search(tree, num) ? std::cout << "FOUND": std::cout << "NOT FOUND";
    }*/
    
    remove_node(tree, 5);
    std::cout << "\n";
    print(tree);
    delete_tree(tree);
}
/*EOF*/