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
    if (root == nullptr) {
        return true;
    }
    return root->isBalanced(root);
}

bool AvlTree::Node::isBalanced(AvlTree::Node *r) {
    if (r == nullptr) {
        return true;
    }
    else {
        if (r->bal <= 1 && r->bal >= -1) {
            isBalanced(r->left);
            isBalanced(r->right);
        }
    }

    return false;
}

AvlTree::Node *AvlTree::getParent(AvlTree::Node *pnode, int value) {
    if (isEmpty() || pnode->key == root->key) {
        return root;
    } else {
        if ((pnode->left != nullptr && pnode->left->key == value) ||
            (pnode->right != nullptr && pnode->right->key == value)) {
            return pnode;
        } else if (pnode->key > value) {
            return getParent(pnode->left, value);
        } else if (pnode->key < value) {
            return getParent(pnode->right, value);
        }
    }
}

void AvlTree::upin(AvlTree::Node *n) {
    int value = n->key;
    if (getParent(root, value)->key == root->key) {
        calculateBalance(root);
    } else {
        calculateBalance(n);
        auto nodeBefore = getParent(n, value);
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

void AvlTree::insert(int value) {
    if (root == nullptr) {
        root = new Node(value, 0);
        calculateBalance(root);
    }
    else
        root->insert(value);
}

// insert wie in VL!!!
void AvlTree::Node::insert(int value) {
    if (value == key)
        return;

    if (value < key) {
        if (left == nullptr) {
            left = new Node(value, 0);
            //calculateBalance(left);
        }

        else
            left->insert(value);
    }

    if (value > key) {
        if (right == nullptr)
            right = new Node(value, 0);
        else
            right->insert(value);
    }
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

