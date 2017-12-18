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
    EXPECT_TRUE(avl.isBalanced());
}


//tree with one node

TEST(TreeTest, One_Node) {
    AvlTree avl;
    avl.insert(1);
    EXPECT_FALSE(avl.isEmpty());
    EXPECT_TRUE(avl.search(1));
    EXPECT_FALSE(avl.search(2));
    //EXPECT_TRUE(avl.isBalanced());
}

TEST(TreeTest, Two_Nodes) {
    AvlTree avl;
    avl.insert(1);
    //avl.insert(5);
    //EXPECT_TRUE(avl.search(5));
    EXPECT_FALSE(avl.search(7));
    EXPECT_FALSE(avl.isEmpty());
}


