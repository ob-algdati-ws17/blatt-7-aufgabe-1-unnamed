//
// Created by Lisa on 11.12.2017.
//

#include "testAvlTree.h"
#include <memory>

using namespace std;

//empty tree

TEST(TreeTest, Test_EmptyTree) {
    AvlTree avl;
    EXPECT_TRUE(avl.isEmpty());
}

