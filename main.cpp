//
// Created by sissy on 13.12.2017.
//

#include <AvlTree.h>

int main() {
        AvlTree avl;
        avl.insert(44);
        avl.insert(17);
        avl.insert(62);
        avl.insert(32);
        avl.insert(50);
        avl.insert(78);
        avl.insert(48);
        avl.insert(54);
        avl.insert(88);
        avl.remove(88);
        cout << avl << endl;
        return 0;
};

