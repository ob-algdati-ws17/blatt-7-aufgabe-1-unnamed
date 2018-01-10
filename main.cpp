//
// Created by sissy on 13.12.2017.
//

#include <AvlTree.h>

int main() {
    AvlTree avl;
    avl.insert(2);
    avl.insert(1);
    avl.insert(3);
    avl.remove(3);
    std::cout << avl << std::endl;
        return 0;
};

