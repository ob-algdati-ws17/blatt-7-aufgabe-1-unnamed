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

AvlTree::Node *AvlTree::getParent(AvlTree::Node *pnode, int value) {
    cout << "***GetParent starts here***" << endl;
    if (isEmpty() || pnode->key == root->key) {
        return nullptr;
    }
    else {
        getParent(pnode, value);
    }
}

AvlTree::Node *AvlTree::Node::getParent(AvlTree::Node *pnode, int value) {
    cout << "***GetParent Node starts here ***" << endl;
    cout << "pnode.key = " << pnode->key << endl;
    cout << "value = " << value << endl;


    if ((pnode->left->key == value) ||
        (pnode->right->key == value)) {
        cout << "aktueller Knoten ist gesuchter Knoten" << endl;
        return pnode;

    } else if (pnode->key > value) {
        cout << "Value ist kleiner als aktueller Schlüssel" << endl;
        return getParent(pnode->left, value);
    } else if (pnode->key < value) {
        cout << "Value ist größter als aktueller schlüssel" << endl;
        return getParent(pnode->right, value);
    }
    cout << "it does nothing" << endl;
}

void AvlTree::Node::upin(AvlTree::Node *n) {
    cout << "***Upin starts here ***" << endl;
    int value = n->key;
    cout << "aktuelles n: " << n << endl;
    cout << "Value " << value << endl;
    if (getParent(n, value) == nullptr) {
        cout << "Parent is nullpointer" << endl;
        calculateBalance(n);
        return;
    } else {
        calculateBalance(n);
        auto nodeBefore = getParent(n, value);
        upin(nodeBefore);
    }
}

void AvlTree::Node::calculateBalance(AvlTree::Node *n) {
    //cout << "***Calculate Balance**" << endl;
    if (n == nullptr) {
        return;
    } else {
        //cout << "n ist nicht Nullpointer" << endl;
        //cout << n->bal << endl;
        n->bal = getHeight(n->right) - getHeight(n->left);
        //cout << n->bal << endl;
        return;
    }
}

int AvlTree::Node::getHeight(AvlTree::Node *n) {
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


void AvlTree::Node::rightRotate(AvlTree::Node *n) {
    auto x = n->left;
    auto z = x->right;

    // Perform rotation
    x->right = n;
    n->left = z;

    //calculateBalance n und x
    calculateBalance(n);
    calculateBalance(x);
}

void AvlTree::Node::leftRotate(AvlTree::Node *n)
{
    auto y = n->right;
    auto z = y->left;

    // Perform rotation
    y->left = n;
    n->right = z;

    // calculate n and y
    calculateBalance(n);
    calculateBalance(y);
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
    cout << "***Insert starts here***" << endl;
    //insert in empty tree
    if (root == nullptr) {
        cout << "insert into empty tree" << endl;
        root = new Node(value, 0);
    }
    else
        root->insert(value);
}

void AvlTree::Node::insert(int value) {
    cout << "***Insert Node starts here***" << endl;
    //value already exists - no insertion
    if (value == key)
        return;

    //cout << "Value existiert noch nicht" << endl;

    //value is smaller: left side of the tree
    if (value < key) {
        cout << "Value is smaller" << endl;
        if (left == nullptr) {
            left = new Node(value, 0);
            calculateBalance(left);
            upin(left);
            //wenn balance (parent(parent(left))) < -1 und ganz links angefügt --> rightrotate
            if (getParent(getParent(left, value), value)->bal < -1 ) {
                rightRotate(getParent(left, value));
            }
            //wenn balance (parent(parent(left))) > 1 und ganz links --> rightrotate leftrotate
            else if (getParent(getParent(left, value), value)->bal > 1) {
                rightRotate(getParent(left, value));
                leftRotate(getParent(getParent(left, value), value));
            }
        }
        else
            left->insert(value);
    }

    //value is bigger: right side of the tree
    if (value > key) {
        cout << "Value is bigger" << endl;
        if (right == nullptr) {
            //cout << right << endl;
            right = new Node(value, 0);

            calculateBalance(right);
            cout << "Balance calculated" << endl;
            cout << right << endl;
            upin(right);
            //wenn balance (parent(parent(right))) > 1 und ganz rechts angefügt --> leftrotate
            if (getParent(getParent(right, value), value)->bal > 1) {
                leftRotate(getParent(right, value));
            }
            //wenn balance (parent(parent(right))) < -1 und ganz rechts --> leftrotate rightrotate
            else if (getParent(getParent(right, value), value)->bal < -1) {
                leftRotate(getParent(right, value));
                rightRotate(getParent(getParent(right, value), value));
            }
        }
        else
            right->insert(value);
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

