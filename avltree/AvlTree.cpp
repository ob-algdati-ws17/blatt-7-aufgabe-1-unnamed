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
            //cout << "calculate balance not nullptr" << endl;
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

void AvlTree::upout(AvlTree::Node *n) {
    cout << "upout starts here" << endl;

    //ausgangssituation: mit root aufrufen
    int value = n->key;
    cout << "value in upout: " << value << endl;

    calculateBalance(root);
    cout << "balance von n " << n->bal << endl;

    if (n->bal >= -1 && n->bal <= 1) {
        if (getParent(n->key) != nullptr) {
            upout(getParent(n->key));
        }
    }
    cout << "nach if-Abfrage in upout" << endl;

    //durch baum von oben nach unten gehen und balance anpassen
    //if (n->right != nullptr) {

        //if(!isBalanced()) {
    if (!isBalanced()) {
        cout << "nicht balanced " << endl;
    }

            cout << "aktelles n: " << n->key << endl;
            cout << "aktuelle bal: " << n->bal << endl;

                if (n->bal > 1) { //grandparent
                    leftRotate(n);
                }

                if (n->bal < -1) {
                    cout << "n im rightRotate " << n->key << endl;
                    rightRotate(n);
                }



           /* if (!isBalanced()) {
                if (getParent(value) != nullptr) {
                    if (getParent(getParent(value)->key) != nullptr) {
                        if (getParent(getParent(getParent(value)->key)->key) != nullptr) {
                            if (getParent(getParent(getParent(value)->key)->key)->bal < -1) {
                                leftRotate(getParent(n->key));
                                rightRotate(getParent(n->key));
                            }
                        }
                    }
                    if (getParent(getParent(getParent(value)->key)->key) != nullptr) {
                        if (getParent(getParent(getParent(value)->key)->key)->bal > 1) {
                            rightRotate(getParent(getParent(n->key)->key));
                        }
                    }
                }
            }
        //}

        //upout(getParent(value));
    //}

    if (n->left != nullptr) {

        if (!isBalanced()) {

            if (getParent(getParent(value)->key) != nullptr) {
                if (getParent(getParent(value)->key)->bal < -1) {
                    rightRotate(getParent(n->key));
                }
            }
            if (!isBalanced()) {
                if (getParent(value) != nullptr) {
                    if (getParent(getParent(value)->key) != nullptr) {
                        if (getParent(getParent(value)->key)->bal > 1) {
                            rightRotate(n);
                            leftRotate(getParent(getParent(n->key)->key));
                        }
                    }
                    if (getParent(getParent(getParent(value)->key)->key) != nullptr) {
                        if (getParent(getParent(getParent(value)->key)->key)->bal < -1) {
                            leftRotate(getParent(getParent(n->key)->key));
                        }
                    }
                }
            }
        }
        //upout(getParent(value));
    }*/
}

void AvlTree::calculateBalance(AvlTree::Node *n) {
    if (n == nullptr) {
        return;
    } else {
        n->bal = getHeight(n->right) - getHeight(n->left);
        calculateBalance(n->right);
        calculateBalance(n->left);
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
        root = y;

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

void AvlTree::leftRotate(AvlTree::Node *n) {
    if (getParent(n->key) == nullptr) {
        auto y = n->right;
        auto z = n->right->right;
        n->right = y->left;
        y->left = n;
        root = y;

        calculateBalance(n);
        calculateBalance(y);
    }
    else {
        auto grandparent = getParent(n->key);
        auto y = n->right;
        n->right = y->left;
        y->left = n;
        if (n->key > grandparent->key) {
            grandparent->right = y;
        }
        else {
            grandparent->left = y;
        }
        calculateBalance(n);
        calculateBalance(y);
        upin(y);
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

void AvlTree::insert(int value) {
    //insert in empty tree
    if (root == nullptr) {
        root = new Node(value, 0);
    }
    else {
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
                /*else if (getParent(value)->bal > 1) {
                    rightRotate(parent->left);
                    leftRotate(getParent(value));
                }*/
            }
            if (!isBalanced()) {
                if (getParent(value) != nullptr) {
                    if (getParent(getParent(value)->key) != nullptr) {
                        //if (getParent(getParent(getParent(value)->key)->key) != nullptr) {
                            //if (getParent(getParent(getParent(value)->key)->key)->bal > 1) {
                                if (getParent(getParent(value)->key)->bal > 1) {
                                    rightRotate((parent));
                                    leftRotate(getParent(getParent(parent->key)->key));
                            }
                        //}
                    }
                    if (getParent(getParent(getParent(value)->key)->key) != nullptr) {
                        if (getParent(getParent(getParent(value)->key)->key)->bal < -1) {
                            rightRotate(getParent(getParent(parent->key)->key));
                        }
                    }
                }
            }
        }
        else
            insert(value, parent->left);
    }

    //value is bigger: right side of the tree
    if (value > parent->key) {
        if (parent->right == nullptr) {
            parent->right = new Node(value, 0);
            upin(parent->right);
            //wenn balance (parent(parent(right))) > 1 und ganz rechts angefügt --> leftrotate
            if(getParent(getParent(value)->key) != nullptr) {
                if (getParent(getParent(value)->key)->bal > 1) { //grandparent
                    leftRotate(getParent(parent->key));
                }
                    //wenn balance (parent(parent(right))) < -1 und ganz rechts --> leftrotate rightrotate
                /*else if (getParent(getParent(value)->key)->bal < -1) {
                    leftRotate(getParent(parent->key));
                    rightRotate(getParent(parent->key));
                }*/
            }
            if (!isBalanced()) {
                if (getParent(value) != nullptr) {
                    if (getParent(getParent(value)->key) != nullptr) {
                        if (getParent(getParent(getParent(value)->key)->key) != nullptr) {
                            if (getParent(getParent(getParent(value)->key)->key)->bal < -1) {
                                leftRotate(getParent(parent->key));
                                rightRotate(getParent(parent->key));
                            }
                        }
                    }
                    if (getParent(getParent(getParent(value)->key)->key) != nullptr) {
                        if (getParent(getParent(getParent(value)->key)->key)->bal > 1) {
                            leftRotate(getParent(getParent(parent->key)->key));
                        }
                    }
                }
            }
        }
        else
            insert(value, parent->right);
    }
}


/********************************************************************
 * Remove
 *******************************************************************/


AvlTree::Node *findSymSucc(AvlTree::Node *node) {
    //cout << "node.key in symsucc: " << node->key << endl;
    if (node->right == nullptr)
        return nullptr;
    auto result = node->right;
    while (result->left != nullptr) {
        result = result->left;
    }
    //cout << "symsucc result " << result->key << endl;
    return result;
}


void AvlTree::remove(const int value) {
    if (root != nullptr) {
        if (root->key == value) {
            //cout << "remove root" << endl;
            auto toDelete = root;
            //root ohne Nachfolger
            if (root->left == nullptr && root->right == nullptr) {
                root = nullptr;
            //ein rechter Nachfolger
            } else if (root->left == nullptr) {
                root = root->right;
            //ein linker Nachfolger
            } else if (root->right == nullptr)
                root = root->left;
            //mehr als ein Nachfolger
            else {
                //cout << "root hat nachfolger" << endl;
                auto symSucc = findSymSucc(root);
                int symSuccKey = symSucc->key;
                auto toDeleteNode = symSucc;
                //Aufruf neu!!! Hier muss root->right zum nullptr werden
                root->right = remove(root, symSucc->key)->right;
                //cout << "root-right" << root->right->key << endl;
                toDeleteNode->left = nullptr;
                toDeleteNode->right = nullptr;
                cout << "SymSucc.key: " << symSuccKey << endl;
                root = new Node(symSuccKey, 0, root->left, root->right);
                //cout << "nach neuem root erstellen" << endl;
                //cout << "neuer Root: " << root->key << endl;
                //cout << "neuer Root.left: " << root->left->key << endl;
                cout << "root.right: " << root->right->key << endl;
                calculateBalance(root);
                cout << "Balance calculated " << endl;
                cout << "Balance root: " << root->bal << " Balance left: " << root->left->bal << endl;
                delete toDeleteNode;
                if (!isBalanced()) {
                    cout << "Baum nicht balanced" << endl;
                    upout(root);
                }

            }
            toDelete->left = nullptr;
            toDelete->right = nullptr;
            delete toDelete;
            if(!isEmpty()) {
                upout(root);
            }
        } else {
            if (getParent(value) != nullptr) {
                auto lastItem = getParent(value);
                remove(root, value);
                calculateBalance(root);
                if (!isBalanced()) {
                    upout(lastItem);
                }
            }
            else {
                remove(root, value);
                if (!isBalanced()) {
                    upout(root);
                }
            }
        }
    }
}


AvlTree::Node *AvlTree::remove(AvlTree::Node *n, const int value) {

    if (value < n->key) {
        //cout << "32 < 44" << endl;
        if (n->left != nullptr) {
            auto toDelete = n->left;
            //cout << "n left " << n->left->key << endl;
            n->left = remove(n->left, value);
            //cout << "n " << n->key << endl;
            if (toDelete->key == value) {
                toDelete->left = nullptr;
                toDelete->right = nullptr;
                delete toDelete;
            }
        }
        return n;
    }

    if (value > n->key) {
        //cout << "32 > 17" << endl;
        if (n->right != nullptr) {
            //cout << "n.right ist nicht nullptr" << endl;
            auto toDelete = n->right;
            //cout << "n right " << n->right->key << endl;
            n->right = remove(n->right, value);
            //cout << "n: " << n->key << endl;
            //cout << "toDelete.key " << toDelete->key << endl;
            if (toDelete->key == value) {
                toDelete->left = nullptr;
                toDelete->right = nullptr;
                delete toDelete;
            }
        }
        return n;
    }

    if (n->key == value) {
        //cout << "32 loeschen" << endl;
        if (n->left == nullptr && n->right == nullptr) {
            //cout << "return nullptr fuer 32" << endl;
            return nullptr;
        }
        if (n->left == nullptr)
            return n->right;
        if (n->right == nullptr)
            return n->left;
        auto symSucc = findSymSucc(n);
        auto symSucc2 = symSucc->key;
        auto nright2 = n->right;
        remove(n->right, symSucc->key);
        //cout << symSucc2 << endl;
        return new Node(symSucc2, 0, n->left, nright2);
    }
    // code should not be reached, just to make the compiler happy
    return nullptr;
}


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
    function<void(std::ostream &, const int, const AvlTree::Node *, const string)> printToOs = [&](std::ostream &,
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

