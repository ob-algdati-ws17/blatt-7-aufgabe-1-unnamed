//
// Created by Lisa on 11.12.2017.
//

#include "AvlTree.h"
#include <functional>

using namespace ::std;

AvlTree::Node::Node(const int k, int h) : key(k), bal(h) {}

AvlTree::Node::Node(const int k, int h, Node *l, Node *r)
        : key(k), bal(h), left(l), right(r) {}

AvlTree::Node::~Node() {
    delete left;
    delete right;
}

AvlTree::~AvlTree() {
    delete root;
}

bool AvlTree::isEmpty() const {
    return root == nullptr;
}

bool AvlTree::isBalanced() {
    //std::cout << "AvlTree isBalanced()" << std::endl;
    if (root == nullptr) {
        return true;
    }
    return root->isBalanced(root);
}

bool AvlTree::Node::isBalanced(AvlTree::Node *r) {
    //cout << "AvlTree::Node isBalanced()" << endl;
    if (r == nullptr) {
        //cout << "Node ist nullpointer" << endl;
        return true;
    }
    else {
        if (r->bal <= 1 && r->bal >= -1) {
            bool righttrue = isBalanced(r->left);
            bool lefttrue = isBalanced(r->right);
            if (righttrue && lefttrue) {
                return true;
            }
        }
    }

    return false;
}

AvlTree::Node *AvlTree::getParent(int value) {
    //parent nullptr (list empty or only root)
    if (isEmpty() || value == root->key) {
        return nullptr;
    }
    else {
        getParent(root, value);
    }
}

AvlTree::Node *AvlTree::getParent(AvlTree::Node *pnode, int value) {
    if (pnode->left == nullptr) {
        if (pnode->right->key == value) {
            return pnode;
        }
    }
    else if (pnode->right == nullptr) {
        if (pnode->left->key == value) {
            return pnode;
        }
    }
    else if (pnode->right->key == value || pnode->left->key == value) {
        return pnode;
    }

    if (pnode->key > value) {
        return getParent(pnode->left, value);
    } else if (pnode->key < value) {
        return getParent(pnode->right, value);
    }
}

void AvlTree::upin(AvlTree::Node *n) {
    int value = n->key;
    if (getParent(value) == nullptr) {
        calculateBalance(n);
        return;
    } else {
        calculateBalance(n);
        auto nodeBefore = getParent(value);
        upin(nodeBefore);
    }
}

void AvlTree::calculateBalance(AvlTree::Node *n) {
    if (n == nullptr) {
        return;
    } else {
        n->bal = getHeight(n->right) - getHeight(n->left);
        return;
    }
}

int AvlTree::getHeight(AvlTree::Node *n) {
    int left, right;

    if (n == nullptr)
        return 0;
    left = getHeight(n->left);
    right = getHeight(n->right);
    if (left > right)
        return left + 1;
    else
        return right + 1;
}


void AvlTree::rightRotate(AvlTree::Node *n) {
    if (getParent(n->key) == nullptr) {
        auto y = n->left;
        n->left = y->right;
        y->right = n;
        root = n;

        calculateBalance(n);
        calculateBalance(y);
    } else {
        auto grandparent = getParent(n->key);
        auto y = n->left;
        n->left = y->right;
        y->right = n;
        if (n->key > grandparent->key) {
            grandparent->right = y;
        }
        else {
            grandparent->left = y;
        }


        calculateBalance(n);
        //calculateBalance(y);
        upin(y);
    }



}

void AvlTree::leftRotate(AvlTree::Node *n)
{
    cout << "leftrotate****" << endl;
    if (getParent(n->key) == nullptr) {
        cout << "getParent ist nullptr" << endl;
        auto y = n->right;
        n->right = y->left;
        y->left = n;
        root = n;

        calculateBalance(n);
        calculateBalance(y);
    }
    else {
        cout << "leftRotate not root" << endl;
        auto grandparent = getParent(n->key);
        auto y = n->right;
        n->right = y->left;
        y->left = n;
        if (n->key > grandparent->key) {
            cout << "granparent ist kleiner als n.key" << endl;
            grandparent->right = y;
        }
        else {
            cout << "grandparent größer als key" << endl;

            grandparent->left = y;
        }
        calculateBalance(n);
        //calculateBalance(y);
        upin(y);

        cout << "Balance n: " << n->bal << endl;
        cout << "Balance y: " << y->bal << endl;
    }
}


/********************************************************************
 * Search
 *******************************************************************/

bool AvlTree::search(const int value) const {
    if (root == nullptr)
        return false;
    return root->search(value);
}

bool AvlTree::Node::search(const int value) const {
    if (value == key) return true;
    if (value < key && left != nullptr) return left->search(value);
    if (value > key && right != nullptr) return right->search(value);
    return false;
}


/********************************************************************
 * Insert
 *******************************************************************/

/*
//Maybe idea for insert but not working yet

void AvlTree::insert(int value) {
    //insert in empty tree
    if (root == nullptr) {
        root = new Node(value, 0);
        calculateBalance(root);
    }
    else
        insert(root, value);
}

AvlTree::Node* AvlTree::insert(Node *r, int value) {

    if (r == nullptr) {
        r = new Node(value, 0);
        r->left = nullptr;
        r->right = nullptr;
        return r;
        //has to be balanced because only one node
    }

    //value is in the left part of the tree
    else if (value < r->key)    {
        if (r->bal == 1) {

            r->left = insert(r->left, value);
            calculateBalance(r->left);
            upin(r);
            while (!isBalanced()) {
                //rotate oder doublerotate
            }
        }

        return r->left;

    }

    //value is on right side of the tree
    else if (value >= r->key)  {

        r->right = insert(r->right, value);
        calculateBalance(r->right);
        upin(r->right);
        while (!isBalanced()) {
            //rotate oder doublerotate
        }
        return r->right;
    }


}
*/


void AvlTree::insert(int value) {
    //insert in empty tree
    if (root == nullptr) {
        cout << "root is nullptr" << endl;
        root = new Node(value, 0);
    }
    else {
        cout << "root not nullptr" << endl;
        insert(value, root);
    }
}

void AvlTree::insert(int value, AvlTree::Node *parent) {
    //value already exists - no insertion
    if (search(value))
        return;

    //cout << "Value existiert noch nicht" << endl;

    //value is smaller: left side of the tree
    if (value < parent->key) {
        if (parent->left == nullptr) {
            parent->left = new Node(value, 0);
            upin(parent->left);
            //wenn balance (parent(parent(left))) < -1 und ganz links angefügt --> rightrotate
            if (getParent(getParent(value)->key) != nullptr) {
                if (getParent(getParent(value)->key)->bal < -1 ) {
                    rightRotate(getParent(parent->key));
                }
                    //wenn balance (parent(parent(left))) > 1 und ganz links --> rightrotate leftrotate
                else if (getParent(value)->bal > 1) {
                    rightRotate(parent->left);
                    leftRotate(getParent(value));
                }
            }
        }
        else
            insert(value, parent->left);
    }

    //value is bigger: right side of the tree
    if (value > parent->key) {
        cout << "Value is bigger" << endl;
        if (parent->right == nullptr) {
            parent->right = new Node(value, 0);
            upin(parent->right);
            //wenn balance (parent(parent(right))) > 1 und ganz rechts angefügt --> leftrotate
            if(getParent(getParent(value)->key) != nullptr) {
                if (getParent(getParent(value)->key)->bal > 1) { //grandparent
                    leftRotate(getParent(parent->key));
                }
                    //wenn balance (parent(parent(right))) < -1 und ganz rechts --> leftrotate rightrotate
                else if (getParent(getParent(value)->key)->bal < -1) {
                    cout << "zweites if" << endl;
                    leftRotate(getParent(parent->key));
                    rightRotate(getParent(parent->key));
                }
            }
        }
        else
            insert(value, parent->right);
    }

    //while(!isBalanced()) {
    // rotate or double rotate
}


/********************************************************************
 * Remove
 *******************************************************************/

/*
AvlTree::Node *findSymSucc(AvlTree::Node *node) {
    if (node->right == nullptr)
        return nullptr;
    auto result = node->right;
    while (result->left != nullptr) {
        result = result->left;
    }
    return result;
}

void AvlTree::remove(const int value) {
    if (root != nullptr) {
        if (root->key == value) {
            auto toDelete = root;
            if (root->left == nullptr && root->right == nullptr) {
                root = nullptr;
            } else if (root->left == nullptr) {
                root = root->right;
            } else if (root->right == nullptr)
                root = root->left;
            else {
                auto symSucc = findSymSucc(root);
                auto toDeleteNode = symSucc;
                root->right = root->right->remove(symSucc->key);
                toDeleteNode->left = nullptr;
                toDeleteNode->right = nullptr;
                root = new Node(symSucc->key, root->left, root->right);
                delete toDeleteNode;
            }
            toDelete->left = nullptr;
            toDelete->right = nullptr;
            delete toDelete;
        } else
            root->remove(value);
    }
}

AvlTree::Node *AvlTree::Node::remove(const int value) {

    if (value < key) {
        if (left != nullptr) {
            auto toDelete = left;
            left = left->remove(value);
            if (toDelete->key == value) {
                toDelete->left = nullptr;
                toDelete->right = nullptr;
                delete toDelete;
            }
        }
        return this;
    }

    if (value > key) {
        if (right != nullptr) {
            auto toDelete = right;
            right = right->remove(value);
            if (toDelete->key == value) {
                toDelete->left = nullptr;
                toDelete->right = nullptr;
                delete toDelete;
            }
        }
        return this;
    }

    if (key == value) {
        if (left == nullptr && right == nullptr)
            return nullptr;
        if (left == nullptr)
            return right;
        if (right == nullptr)
            return left;
        auto symSucc = findSymSucc(this);
        return new Node(symSucc->key, left, right->remove(symSucc->key));
    }
    // code should not be reached, just to make the compiler happy
    return nullptr;
}
*/

/********************************************************************
 * Traversal
 *******************************************************************/

vector<int> *AvlTree::preorder() const {
    if (root == nullptr)
        return nullptr;
    return root->preorder();
}

vector<int> *AvlTree::Node::preorder() const {
    auto vec = new vector<int>();
    // Wurzel in vec
    vec->push_back(key);
    // linken Nachfolger in vec
    if (left != nullptr) {
        auto left_vec = left->preorder();
        vec->insert(vec->end(), left_vec->begin(), left_vec->end());
    }
    // rechten Nachfolger in vec
    if (right != nullptr) {
        auto right_vec = right->preorder();
        vec->insert(vec->end(), right_vec->begin(), right_vec->end());
    }
    return vec;
}

vector<int> *AvlTree::inorder() const {
    if (root == nullptr)
        return nullptr;
    return root->inorder();
}

vector<int> *AvlTree::Node::inorder() const {
    auto vec = new vector<int>();
    // linken Nachfolger in vec
    if (left != nullptr) {
        auto left_vec = left->inorder();
        vec->insert(vec->end(), left_vec->begin(), left_vec->end());
    }
    // Wurzel in vec
    vec->push_back(key);
    // rechten Nachfolger in vec
    if (right != nullptr) {
        auto right_vec = right->inorder();
        vec->insert(vec->end(), right_vec->begin(), right_vec->end());
    }
    return vec;
}

vector<int> *AvlTree::postorder() const {
    if (root == nullptr)
        return nullptr;
    return root->postorder();
}

vector<int> *AvlTree::Node::postorder() const {
    auto vec = new vector<int>();
    // linken Nachfolger in vec
    if (left != nullptr) {
        auto left_vec = left->postorder();
        vec->insert(vec->end(), left_vec->begin(), left_vec->end());
    }
    // rechten Nachfolger in vec
    if (right != nullptr) {
        auto right_vec = right->postorder();
        vec->insert(vec->end(), right_vec->begin(), right_vec->end());
    }
    // Wurzel in vec
    vec->push_back(key);
    return vec;
}


/********************************************************************
 * operator<<
 *******************************************************************/

std::ostream &operator<<(std::ostream &os, const AvlTree &tree) {
    function<void(std::ostream &, const int, const AvlTree::Node *, const string)> printToOs = [&](std::ostream &os,
                                                                                                   const int value,
                                                                                                   const AvlTree::Node *node,
                                                                                                   const string l) {

        static int nullcount = 0;

        if (node == nullptr) {
            os << "    null" << nullcount << "[shape=point];" << endl;
            os << "    " << value << " -> null" << nullcount
               << " [label=\"" << l << "\"];" << endl;
            nullcount++;
        } else {
            os << "    " << value << " -> " << node->key
               << " [label=\"" << l << "\"];" << endl;

            printToOs(os, node->key, node->left, "l");
            printToOs(os, node->key, node->right, "r");
        }
    };
    os << "digraph tree {" << endl;
    if (tree.root == nullptr) {
        os << "    null " << "[shape=point];" << endl;
    } else {
        printToOs(os, tree.root->key, tree.root->left, "l");
        printToOs(os, tree.root->key, tree.root->right, "r");
    }
    os << "}" << endl;
    return os;


}

