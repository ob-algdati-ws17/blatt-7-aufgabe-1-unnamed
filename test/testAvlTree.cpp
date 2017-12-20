//
// Created by Lisa on 11.12.2017.
//

#include "testAvlTree.h"
#include <memory>

using namespace std;

// empty tree:
// isEmpty() == true
// isBalanced() == true

TEST(TreeTest, Test_EmptyTree) {
    AvlTree avl;
    EXPECT_TRUE(avl.isEmpty());
    EXPECT_TRUE(avl.isBalanced());
}

// tree with one node
// isEmpty() == false
// isBalanced() == true
// search(1) == true, search(2) == false

TEST(TreeTest, One_Node) {
    AvlTree avl;
    avl.insert(1);
    EXPECT_FALSE(avl.isEmpty());
    EXPECT_TRUE(avl.isBalanced());
    EXPECT_TRUE(avl.search(1));
    EXPECT_FALSE(avl.search(2));
}

// test with two nodes
// isEmpty() == false
// isBalanced() == true

TEST(TreeTest, Two_Nodes) {
    AvlTree avl;
    avl.insert(1);
    avl.insert(5);
    EXPECT_TRUE(avl.search(5));
    EXPECT_FALSE(avl.search(7));
    EXPECT_FALSE(avl.isEmpty());
}

TEST(TreeTest, Three_Nodes) {
    AvlTree avl;
    avl.insert(2);
    avl.insert(1);
    avl.insert(3);
    EXPECT_TRUE(avl.isBalanced());
}

TEST(TreeTest, Three_Nodes_LeftRotate) {
    AvlTree avl;
    avl.insert(1);
    avl.insert(2);
    avl.insert(3);
    EXPECT_TRUE(avl.isBalanced());
}

TEST(TreeTest, Three_Nodes_RightRotate) {
    AvlTree avl;
    avl.insert(3);
    avl.insert(2);
    avl.insert(1);
    EXPECT_TRUE(avl.isBalanced());
}

TEST(TreeTest, Five_Nodes_RightRotate) {
    AvlTree avl;
    avl.insert(13);
    avl.insert(26);
    avl.insert(5);
    EXPECT_TRUE(avl.isBalanced());
    avl.insert(27);
    EXPECT_TRUE(avl.isBalanced());
    avl.insert(30);
    EXPECT_TRUE(avl.isBalanced());
}

TEST(TreeTest, Five_Nodes_LeftRotate) {
    AvlTree avl;
    avl.insert(13);
    avl.insert(26);
    avl.insert(5);
    avl.insert(4);
    avl.insert(3);
    EXPECT_TRUE(avl.isBalanced());
}

TEST(TreeTest, Ten_Nodes_Left) {
    AvlTree avl;
    avl.insert(1);
    avl.insert(2);
    avl.insert(3);
    avl.insert(4);
    avl.insert(5);
    avl.insert(6);
    avl.insert(7);
    avl.insert(8);
    avl.insert(9);
    avl.insert(10);
    EXPECT_TRUE(avl.isBalanced());
}

TEST(TreeTest, Ten_Nodes_Right) {
    AvlTree avl;
    avl.insert(10);
    avl.insert(9);
    avl.insert(8);
    avl.insert(7);
    avl.insert(6);
    avl.insert(5);
    avl.insert(4);
    avl.insert(3);
    avl.insert(2);
    avl.insert(1);
    EXPECT_TRUE(avl.isBalanced());

}

TEST(TreeTest, Left_Right) {
    AvlTree avl;
    avl.insert(13);
    avl.insert(10);
    avl.insert(15);
    avl.insert(5);
    avl.insert(16);
    avl.insert(11);
    avl.insert(4);
    avl.insert(6);
    EXPECT_TRUE(avl.isBalanced());
    avl.insert(7);
    EXPECT_TRUE(avl.isBalanced());
}

TEST(TreeTest, Right_Left) {
    AvlTree avl;
    avl.insert(5);
    avl.insert(2);
    avl.insert(7);
    avl.insert(1);
    avl.insert(4);
    avl.insert(6);
    avl.insert(9);
    avl.insert(3);
    avl.insert(16);
    EXPECT_TRUE(avl.isBalanced());
    avl.insert(15);
    EXPECT_TRUE(avl.isBalanced());
}

TEST(TreeTest, Simple_Remove) {
    AvlTree avl;
    avl.insert(1);
    avl.remove(1);
    EXPECT_FALSE(avl.search(1));
    avl.insert(1);
    avl.insert(3);
    EXPECT_TRUE(avl.search(1));
    avl.remove(1);
    EXPECT_FALSE(avl.search(1));
}

TEST(TreeTest, Remove_Nullptr) {
    AvlTree avl;
    avl.remove(1);
    EXPECT_TRUE(avl.isBalanced());
}

TEST(TreeTest, Remove_Three_Nodes) {
    AvlTree avl;
    avl.insert(1);
    avl.insert(2);
    avl.insert(3);
    EXPECT_TRUE(avl.isBalanced());
    avl.remove(2);
    EXPECT_TRUE(avl.isBalanced());
}

TEST(TreeTest, Remove_Four_Nodes) {
    AvlTree avl;
    avl.insert(4);
    avl.insert(2);
    avl.insert(5);
    avl.insert(3);
    avl.remove(2);
    EXPECT_TRUE(avl.isBalanced());
}