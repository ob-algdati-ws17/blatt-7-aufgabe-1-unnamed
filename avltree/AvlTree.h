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
        const int height;
        Node *left = nullptr;
        Node *right = nullptr;


        Node(const int, const int);
        Node(const int, const int, Node *, Node *);
        ~Node();

        bool search(const int) const;

        /*
        void insert(const int);
        Node *remove(const int);
        vector<int> *preorder() const; // (Hauptreihenfolge)
        vector<int> *inorder() const; // (Symmetrische Reihenfolge)
        vector<int> *postorder() const; // (Nebenreihenfolge)
         */
    };

    Node *root = nullptr;

public:

    ~AvlTree();

    bool isEmpty() const;

    bool search(const int) const;

    int balance(Node *);

    /*

    void insert(const int);

    void remove(const int);

    vector<int> *preorder() const; // (Hauptreihenfolge)
    vector<int> *inorder() const; // (Symmetrische Reihenfolge)
    vector<int> *postorder() const; // (Nebenreihenfolge)

    friend Node *findSymSucc(Node *);
    friend ostream &operator<<(ostream &, const AvlTree &);

     */
};

#endif //AVLTREE_AVLTREE_H

