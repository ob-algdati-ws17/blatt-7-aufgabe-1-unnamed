//
// Created by sissy on 13.12.2017.
//

#include <AvlTree.h>

int main() {
    AvlTree avl;
    avl.insert(8);
    avl.insert(5);
    avl.insert(10);
    avl.insert(2);
    avl.insert(6);
    avl.insert(9);
    avl.insert(11);
    avl.insert(1);
    avl.insert(3);
    avl.insert(7);
    avl.insert(12);
    avl.insert(4);
    avl.remove(9);
    std::cout << avl << std::endl;
        return 0;
};

