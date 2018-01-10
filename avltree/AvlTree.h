//
// Created by Lisa on 11.12.2017.
//

#ifndef AVLTREE_AVLTREE_H
#define AVLTREE_AVLTREE_H

#include <iostream>
#include <vector>

using namespace std;

/**
 * Class for our AvlTree.
 */
class AvlTree {


private:

    /**
     * Structure for a node in AvlTree. Key and balance for searchtree and pointer for left and right.
     */
    struct Node {
        const int key;
        int bal;
        //Node *parent = nullptr;
        Node *left = nullptr;
        Node *right = nullptr;


        /**
         * Basic Ccnstructor for node.
         * @param key and balance (default 0).
         * @return new node.
         */
        Node(const int, int);

        /**
         * Constructor for node.
         * @param key and balance (dafault 0); Pointers on following nodes left and right.
         * @return new node.
         */
        Node(const int, int, Node *, Node *);

        /**
         * Destrucor for node.
         */
        ~Node();

        /**
         * Search given value in tree.
         * @param Integer value that has to be searched.
         * @return true if value is in the tree, false if value cannot be found.
         */
        bool search(const int) const;

        /**
         * Method to check if AvlTree is balanced.
         * @param Node from which the tree is checked if it is balanced.
         * @return true if every balance is -1, 0, 1, false if not.
         */
        bool isBalanced(Node*);

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

    /**
     * Root is the root of a new AvlTree.
     */
    Node *root = nullptr;

public:

    /**
     * Destructor for complete tree.
     */
    ~AvlTree();

    /**
     * Method to check if AvlTree is empty.
     * @return true if tree is empty, false if tree is not empty.
     */
    bool isEmpty() const;

    /**
     * Method for getting the parent of any node in the AvlTree.
     * @param key (as int) of the node whose parent is needed.
     * @return Node of the parent.
     */
    Node* getParent(int);

    /**
     * Method for getting the parent of any node in the AvlTree (recursive).
     * @param Node from which part of the tree the parent is needed and the key (as int) of the Node whose parent is looked for.
     * @return Node of the parent.
     */
    Node* getParent(Node*, int);

    /**
     * Method to check, if the whole AvlTree is balanced.
     * @return true, if the tree is balanced, false if any node is not in balance.
     */
    bool isBalanced();

    /**
     * Method to calculate the balance of a node and updates the balance factor of the node.
     * @param Node whose balance needs to be calculated.
     */
    void calculateBalance(Node *);

    /**
     * Method to calculate the height of a node.
     * @param Node whose height is looked for.
     * @return integer heigt of the given node.
     */
    int getHeight(Node *);

    /**
     * Method to update the balance factors of any changes after inserting a new node.
     * @param Node which has just been inserted.
     */
    void upin(Node*);

    /**
     * Mathod to update the balance and rotate the tree if necessary, after a node has been removed.
     * @param root node from which the balance is updated.
     */
    void upout(Node*);

    /**
     * Method to rotate the AvlTree to the right to assure the balance.
     * @param Node which needs to be rotated.
     */
    void rightRotate(Node *);

    /**
     * Method to rotate the AvlTree to the left to assure the balance.
     * @param Node which needs to be rotated.
     */
    void leftRotate(Node *);

    /**
     * Method to remove a Node from the AvlTree.
     * @param Node, from which the given key is looked for and the key of node to be removed.
     * @return Node which moved one stage up.
     */
    Node *remove(Node *, const int);

    /**
     * Search given value in tree.
     * @param value Integer value that has to be searched.
     * @return false if tree is empty, go to following method if it is not empty.
     */
    bool search(const int) const;

    /**
     * Insert a value in the tree.
     * @param value Integer value that has to be inserted.
     */
    void insert(const int);

    /**
     * Insert a given value in the tree.
     * @param value Integer value that has to be inserted.
     */
    void insert(const int, Node*);


    /**
     * Method to remove a Node from the AvlTree.
     * @param key of node to be removed.
     * @return Node which moved one stage up.
     */
    void remove(const int);

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

    /**
     * Method to find the symmetrical follower for a node which is about to be removed.
     * @param Node who is about to removed and whose symmetrical follower is needed.
     * @return symmetrical follower.
     */
    friend Node *findSymSucc(Node *);

    /**
     * To String method for tree.
     * @param os Stream that has to be converted.
     * @param tree Tree that has to be printed.
     * @return Tree in printed version.
     */
    friend ostream &operator<<(ostream &, const AvlTree &);

};

#endif //AVLTREE_AVLTREE_H

