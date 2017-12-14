//
// Created by Lisa on 11.12.2017.
//

#ifndef AVLTREE_AVLTREE_H
#define AVLTREE_AVLTREE_H

#include <iostream>
#include <vector>

using namespace std;


class AvlTree {


private:

    struct Node {
        const int key;
        int bal;
        Node *left = nullptr;
        Node *right = nullptr;


        Node(const int, int);

        /**
         * Constructor for node.
         */
        Node(const int, int, Node *, Node *);

        /**
         * Destrucor for node.
         */
        ~Node();

        /**
         * Search given value in tree.
         * @param value Integer value that has to be searched.
         * @return true if value is in the tree, false if value cannot be found.
         */
        bool search(const int) const;

        /**
         * Method to check if avl tree is balanced.
         * @param Node to be checked if balanced.
         * @return true if balance is -1, 0, 1, false if not.
         */
        bool isBalanced(Node*);


        /**
         * Insert a given value in the tree.
         * @param value Integer value that has to be inserted.
         */

        /*
        Node *remove(const int);
         */

        /**
         * Preordered walkthrough.
         * @return Root, left tree, right tree.
         */
        vector<int> *preorder() const; // (Hauptreihenfolge)

        /**
         * Inordered walkthrouhg.
         * @return Left tree, root, right tree.
         */
        vector<int> *inorder() const; // (Symmetrische Reihenfolge)

        /**
         * Postordered walkthrough.
         * @return Left tree, right tree, root.
         */
        vector<int> *postorder() const; // (Nebenreihenfolge)

    };

    Node *root = nullptr;

public:

    /**
     * Destructor for complete tree.
     */
    ~AvlTree();

    /**
     * Method to check if avl Tree is empty.
     * @return true if tree is empty, false if tree is not empty.
     */
    bool isEmpty() const;


    bool isBalanced();

    /**
     * Method to get node before given node.
     * @return Parent node.
     */
    Node* getParent(Node*, int);

    /**
     * Method to update balance on path to given (new inserted) node.
     */
    void upin(Node*);

    /**
     * Search given value in tree.
     * @param value Integer value that has to be searched.
     * @return false if tree is empty, go to following method if it is not empty.
     */
    bool search(const int) const;

    /**
     * Calculate balance.
     * @param n Node pointer which balance has to be calculated.
     * @return balance (here: between -1 and 1).
     */
    void calculateBalance(Node *);

    /**
     * Get height.
     * @param n Node pointer which height has to be calculated.
     * @return height, number of longest path after node.
     */
    int getHeight(Node *);

    /**
     * Insert a value in the tree.
     * @param value Integer value that has to be inserted.
     */
    Node* insert(Node *, const int);

    /*

    void remove(const int);

     */

    /**
     * Preordered walkthrough.
     * @return Nullptr if root is nullptr, else go to following method.
     */
    vector<int> *preorder() const; // (Hauptreihenfolge)

    /**
     * Inordered walkthrough.
     * @return Nullptr if root is nullptr, else go to following method.
     */
    vector<int> *inorder() const; // (Symmetrische Reihenfolge)

    /**
     * Postordered walkthrough.
     * @return nullptr if root is nullptr, else go to following method.
     */
    vector<int> *postorder() const; // (Nebenreihenfolge)

    /*

    friend Node *findSymSucc(Node *);

     */

    /**
     * To String method for tree.
     * @param os Stream that has to be converted.
     * @param tree Tree that has to be printed.
     * @return Tree in printed version.
     */
    friend ostream &operator<<(ostream &, const AvlTree &);

};

#endif //AVLTREE_AVLTREE_H

