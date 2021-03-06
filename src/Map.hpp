#pragma once
/*
MIT License

Copyright (c) 2021 Christopher William Driggers-Ellis

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

#include "UnorderedSet.hpp" // UnorderedSet.hpp is responsible for organizing occurrences of the data in Map
#include <iostream>
#include <exception>
#include <string>
#include <vector>
#include <sstream>

namespace tacl
{
    /* code in the rest of this file is retooled from CW Ellis' submission to Project 1. It has been edited to use templates instead of just ints and strings */
    // make an AVL based map
    template<typename K, typename V>
    class Map
    {
        struct Node
        {
            // members of the node class. As a convention, names of all member variables in this implementation start with
            V m_name;    // the name of the node
            K m_id;      // their id
            int m_bal;      // the node's current balance
            int m_height;   // the node's current height
            Node* m_left;   // left and right child pointers
            Node* m_right;

            // Node constructors
            Node(Node* l = nullptr, Node* r = nullptr);
            Node(V n, K id, Node* l = nullptr, Node* r = nullptr);
            static int getHeight(Node* node);  // gets the height of the passed node
            int getHeight() const;
            int calcHeight();                  // recalculates and returns the height of a node
            int calcBal();                     // recalculates and returns the balance of a node
        };

        Node* m_root; // root node

        int m_size = 0; //number of nodes within the tree
        int m_trueSize = 0;

        // Private helper functions

        bool insert(V val, K id, Node* root); // insertion, removal and rotation
        bool remove(K id, Node* root);
        Node* remover(Node* root);
        Node* checkRotation(Node* root);
        void checkRotations(Node* root);
        Node* leftRotation(Node* root);
        Node* rightRotation(Node* root);
        Node* leftRightRotation(Node* root);
        Node* rightLeftRotation(Node* root);

        // search
        V& search(K id, Node* root) const;

        // Other helper functions
        void delTree(Node* root);
        void fillIdsInOrder(Node* root, std::vector<K>& ids) const;
        void removeBalHeightFixer(Node* root);
        Node* copyTree(Node* rhsRoot);

    public:
        Map(); // AvlTree class constructor. Creates a Tree with a root node
        ~Map();                    // AvlTree class destructor.
        Map(const Map& rhs);
        Map& operator=(const Map& rhs);

        // Public Member Functions
        bool insert(K id, V name); // insertion and removals
        bool remove(K id);
        V& search(K id) const;      // search by id

        int countLevels();                 // returns the number of levels in the tree
        void fillIdsInOrder(std::vector<K>& ids) const; // gives a public overload of fillIdsInOrder for testing
        bool isBalanced() const;
        bool isBalanced(Node* root) const; // test function to determine balance of the tree

        int size();
    };

    // checks the rotation of a node
    // This function has no loops and only calls O(1) time functions of the root node. This, with a little further examination reveals that the function's runtime
    // is O(1) in any case, as the worst case is O(1), and the other two cases, such as the best where the root is null, are just constant
    // time improvement 
    template<typename K, typename V>
    typename Map<K, V>::Node* Map<K, V>::checkRotation(Node* root)
    {
        if (root != nullptr)
        {
            int bal = root->calcBal(); // calculate the nodes balance

            if (bal >= 2)              // a leftward imbalance
            {
                if (root->m_left->m_bal >= 1)       // left-left calls for a right rotation
                    root = rightRotation(root);
                else if (root->m_left->m_bal <= -1) // left-right calls for a left-right rotation
                    root = leftRightRotation(root);

            }
            else if (bal <= -2)                      // a rightward imbalance
            {
                if (root->m_right->m_bal <= -1)      // right-right calls for a left rotation
                    root = leftRotation(root);
                else if (root->m_right->m_bal >= 1)  // right-left calls for a right-left rotation
                    root = rightLeftRotation(root);
            }

            root->calcHeight();

        }

        return root; // the root is reset after each rotation, and returned
    }

    // checkRotations is a function that checks the rotation of the left and right children of the passed root for their balance and performs
    // appropriate rotations, if they are needed. It just calls the constant time checkRotations() function and is therefore a constant time function itself,
    // as it will call an O(1) operation a constant number of times.
    template<typename K, typename V>
    void Map<K, V>::checkRotations(Node* root)
    {
        root->m_left = checkRotation(root->m_left);   // rotates and reassigns the left child, if needed
        root->m_right = checkRotation(root->m_right); // rotates and reassigns the right child, if needed

        if (root == m_root)                 // if the root is the tree's root in general, then the m_root variable
            m_root = checkRotation(m_root); // special reassignment. Further, m_root would not have a parent, so it must
                                            // be treated on its own as an edge case
    }

    // all rotation functions adapted from my solution to Stepik 5.1.1.
    // These rotation algorithms were informed by information given
    // in the resources for that assignment. These clearly run in O(1) in any case,
    // for the rotation occurs in a clearly constant time, and the only other operations
    // are calling four other constant time functions
    template<typename K, typename V>
    typename Map<K, V>::Node* Map<K, V>::leftRotation(Node* root)
    {
        Node* top = root;     // set a temp pointer to the roots location
        root = root->m_right; // the root is then set to its right child
        Node* temp = root->m_left; // another temp is set to the new root's left
        top->m_right = temp;  // the top's right becomes the new temp node
        root->m_left = top;   // with a link established for the root's left child becomes the top


        top->calcHeight();    // recalculate the height and balance of top
        top->calcBal();

        root->calcHeight();   // recalculate balance and height of root
        root->calcBal();      // NOTE: it is important to call the height calculations first
                              // as the height of top may affect the balance of root.

        return root; // returns the root, which is now the top of the balanced structure
    }

    // performs a right rotation on the passed in node
    // again operates in O(1) time
    template<typename K, typename V>
    typename Map<K, V>::Node* Map<K, V>::rightRotation(Node* root) // works like left rotation but mirrored
    {
        Node* top = root;
        root = root->m_left;
        Node* temp = root->m_right;
        top->m_left = temp;
        root->m_right = top;

        top->calcHeight();
        top->calcBal();


        root->calcHeight();
        root->calcBal();

        return root;
    }

    // leftRightRotation is also an adaptation from my solution to Stepik exercise 5.1.1
    template<typename K, typename V>
    typename Map<K, V>::Node* Map<K, V>::leftRightRotation(Node* root)   // left-right rotation is merely a two step left then right rotation
    {
        root->m_left = leftRotation(root->m_left); // left rotation of the left node
        return rightRotation(root);                // returns a right rotation of the current node
    }

    // because right-left rotation is a mirror of left-right rotation, this too is adapted from 5.1.1
    template<typename K, typename V>
    typename Map<K, V>::Node* Map<K, V>::rightLeftRotation(Node* root)
    {
        root->m_right = rightRotation(root->m_right);
        return leftRotation(root);
    }

    // deallocates the tree using a postorder traversal
    // to avoid memory leakage during testing/grading, a destructor is defined for the class and uses this function to deallocate memory.
    // This uses a postorder traversal to visit each node in the tree a single time, and is therefore O(n) time for any case, with n being the number
    // of nodes in the tree.
    template<typename K, typename V>
    void Map<K, V>::delTree(Node* root)
    {
        if (root != nullptr)
        {
            delTree(root->m_left);
            delTree(root->m_right);
            delete root;
        }
    }

    // fill a vector of ids using an inorder traversal
    // runs in O(n) in any case, where n is the number of nodes in the subtree whose root is passed
    // for any case as all nodes are visited once and placed into the vector.
    template<typename K, typename V>
    void Map<K, V>::fillIdsInOrder(Node* root, std::vector<K>& ids) const
    {
        if (root != nullptr)
        {
            fillIdsInOrder(root->m_left, ids);
            ids.push_back(root->m_id);
            fillIdsInOrder(root->m_right, ids);
        }
    }

    // balances the height of nodes down the path of the inorder successor
    // since it only goes through the left children of the root and calls 2 O(1) functions, it is O(h) where h is the height of the given subtree
    // with root, instead of linear with the number of nodes in that tree in any case. h ~ O(log(n)) for the number of nodes n, so we can expect
    // that the function is O(log(n)).
    template<typename K, typename V>
    void Map<K, V>::removeBalHeightFixer(Node* root)
    {
        if (root != nullptr)
        {
            removeBalHeightFixer(root->m_left);
            root->calcHeight();
            root->calcBal();
        }
    }

    // recursive copy tree function
    template<typename K, typename V>
    typename Map<K, V>::Node* Map<K, V>::copyTree(Node* rhsRoot)
    {
        if (rhsRoot == nullptr)
            return nullptr;

        Node* left = copyTree(rhsRoot->m_left);
        Node* right = copyTree(rhsRoot->m_right);

        return new Node(rhsRoot.m_name, rhsRoot.m_id, left, right);

    }

    // Runs in the same time as the isBalanced function below it.
    // citation
    template<typename K, typename V>
    bool Map<K, V>::isBalanced() const
    {
        return isBalanced(m_root);
    }

    // Runs in O(n) time in the worst and average cases where n is the number of nodes in the tree whose root is passed in. The reason for this is that it performs a type of
    // preorder traversal of the tree in any case but the base case or imbalance. Therefore, the worst case would be the one in which all nodes were checked for
    // their balance, which implies O(n). The best case, however, is going to be the one in which the root fails to be balanced. In this case, it fails immediately
    // and is therefore O(1).
    template<typename K, typename V>
    bool Map<K, V>::isBalanced(Node* root) const
    {
        if (root == nullptr)
            return true;
        else if (root->m_bal > 1 || root->m_bal < -1)
            return false;
        else
            return isBalanced(root->m_left) && isBalanced(root->m_right);
    }

    // constructor of the AvlTree class. It is a constant time operation
    template<typename K, typename V>
    Map<K, V>::Map() : m_root(nullptr) {}; // initialize root to null

    // destructor of the AvlTree class 
    template<typename K, typename V>
    Map<K, V>::~Map()
    {
        delTree(m_root);
        m_root = nullptr; // set m_root to null following the tree's deletion
    }

    // copy constructor
    template<typename K, typename V>
    Map<K, V>::Map(const Map& rhs)
    {
        m_root = copyTree(rhs.m_root);
    }

    // copy assignment operator
    template<typename K, typename V>
    Map<K, V>& Map<K, V>::operator=(const Map<K, V>& rhs)
    {
        delTree(m_root);
        m_root = copyTree(rhs.m_root);
    }

    // return true if insertion successful. Implementation of insertion adapted from
    // my solution to Stepik exercise 4.3.2. Rotations adapted from my solution to 5.1.1
    template<typename K, typename V>
    bool Map<K, V>::insert(V name, K id, Node* root)
    {
        if (root == nullptr)
        {
            m_root = new Node(name, id); // set the true root to the new node, if the tree is empty
            return true;
        }
        else
        {
            if (id < root->m_id)                     // less than or equal goes left
            {
                if (root->m_left != nullptr)
                {
                    if (!insert(name, id, root->m_left))
                        return false;
                }
                else
                {
                    root->m_left = new Node(name, id);  // creates a new node
                }

            }
            else if (id > root->m_id)                   // greater than goes right
            {
                if (root->m_right != nullptr)
                {
                    if (!insert(name, id, root->m_right))
                        return false;
                }
                else
                {
                    root->m_right = new Node(name, id);
                }

            }
            else
            {
                return false; // in this case id equals the id of the current node.
                              // Hence, the insertion cannot occur or else it would
                              // violate the principle that ids are unique
            }
        }

        checkRotations(root);  // check rotation in all cases except no insertion or
        return true;           // insertion at the root.

    }

    // interface for inserting elements into the tree. Technically runs in O(s + log(n)), for the length of the name s and number of nodes already in the tree n 
    // in the worst case and O(1) in the best case, as either can fail immediately and result in a best case complexity of O(1).
    template<typename K, typename V>
    bool Map<K, V>::insert(K id, V name)
    {
        bool result = insert(name, id, m_root);
        if (result) {
            ++m_size;
        }
        return result;
    }


    // removes a node from the tree.
    template<typename K, typename V>
    bool Map<K, V>::remove(K id, Node* root)
    {
        if (root == nullptr)        // this will only happen in the case that there is no node in the AVL with the given id
            return false;
        else if (id < root->m_id)   // go down the left subtree
        {
            if (root->m_left != nullptr && root->m_left->m_id == id) // remove the left child, if it's the desired node
            {
                root->m_left = remover(root->m_left);                // removal done by helper, and reassignment is done to set children
                root->calcHeight();
                root->calcBal();
                return true;
            }

            if (remove(id, root->m_left)) // if the left child is not the node, continue down the tree recursively, and return appropriately
            {
                root->calcHeight();
                root->calcBal();          // recalculate balance. This ensures that the balance is accurate for each node following deletion
                return true;
            }
            else
            {
                return false;
            }

        }
        else if (id > root->m_id)    // going down the right subtree is a mirror of going down the left
        {
            if (root->m_right != nullptr && root->m_right->m_id == id)
            {
                root->m_right = remover(root->m_right);
                root->calcHeight();
                root->calcBal();
                return true;
            }

            if (remove(id, root->m_right)) // if the left child is not the node, continue down the tree recursively, and return appropriately
            {
                root->calcHeight();
                root->calcBal();                // recalculate balance. This ensures that the balance is accurate for each node following deletion
                return true;
            }
            else
            {
                return false;
            }
        }
        else // because the children are always checked for the desired id, the only case in which the root's id might be equivalent to id is at the root
        {    // of the whole tree, because the tree's root is the only node without a parent, as per the tree ADT. This special case facilitates setting the
             // the tree's m_root member variable without checking further.
            m_root = remover(m_root);
            return true;
        }

    }

    // helper for the recursive removal function. Runs in variable time, dependent on whether the root node pointer is pointing to a leaf, a node with a single
    // child or a node with two children. In the first and second cases, the function will run in constant time, for the calculations for finding the children are constant and
    // so are the operations of switching and deleting the pointers. Thus the best case is definitely O(1), whereas the worst can be defined as any case falling under the two children
    // category. In this case, the complexity is found by analyzing the fact that O(log(r)), where r is the number of nodes in the root's right subtree,
    // operations are required to find the root's inoreder successor, the fact that the functions calcHeight and calcBal are O(1) and that the function removeBalHeightFixer is O(log(r)) in any case itself.
    // This means that the whole operation would be bounded by log(r) and thus O(log(r)) represents a worst case complexity for the remover function.
    template<typename K, typename V>
    typename Map<K, V>::Node* Map<K, V>::remover(Node* root)
    {
        if (root->m_left != nullptr && root->m_right != nullptr) // if the node has two children
        {
            // go to the right subtree and follow the m_left pointers of the children to find the inorder successor
            Node* successor = root->m_right;
            Node* temp = nullptr;
            while (successor->m_left != nullptr)
            {
                temp = successor;
                successor = successor->m_left;
            }

            if (temp != nullptr)  // if temp is null, then the root's right child had no left child.
            {
                temp->m_left = successor->m_right; // temp's m_left, which pointed to successor, now points to successor's right child

                // set successors children pointers to the root's children
                successor->m_right = root->m_right;
                successor->m_left = root->m_left;
            }
            else
            {
                successor->m_left = root->m_left; // without a left child, the root's right child is the inorder successor
            }

            removeBalHeightFixer(root->m_right);  // fix the balance of all nodes leading to the inorder successor

            successor->calcBal();
            successor->calcHeight();

            // in either case, the successor pointer now holds the new root. Delete the root and return successor
            delete root;
            return successor;
        }
        else if (root->m_left != nullptr || root->m_right != nullptr) // one child
        {
            // Because we know root has only one child, we know that only one temp is necessary.
            Node* temp = root->m_left; // this sets temp to either the one child or null
            if (temp == nullptr)       // if temp is null the child is a right child, else it was a left child
            {
                temp = root->m_right;  // since the left pointer must be null, this ensures that temp is the child afterward
            }

            delete root;
            return temp;               // return the child. The parent's child pointer is reassigned outside.
        }
        else // root is a leaf
        {
            delete root; // delete the root and return a nullptr since root has no children to deal with
            return nullptr;
        }
    }

    // removal interface. Runs in the same cases as remove as idValidation is a constant time function.
    template<typename K, typename V>
    bool Map<K, V>::remove(K id)
    {
        bool result = remove(id, m_root);
        if (result) {
            m_size--;
        }
        return result;
    }

    // search for student by id. Simple BST searching algorithm based on the assumption that the ids are unique.
    template<typename K, typename V>
    V& Map<K, V>::search(K id, Node* root) const
    {
        if (root == nullptr)
            throw std::exception();            // return empty string signifying unsuccessful if not found
        else if (id < root->m_id)
            return search(id, root->m_left);  // go down the tree until a leaf is reached
        else if (id > root->m_id)
            return search(id, root->m_right);
        else                                  // or until id matches the current root's id.
            return root->m_name;
    }

    // search for an element by its id. Runs in O(log(n)) in the worst case, as it calls the id-based search function and O(1) in the best case, for idValidation
    // is O(1) in any case.
    template<typename K, typename V>
    V& Map<K, V>::search(K id) const
    {
        return search(id, m_root);
    }

    template<typename K, typename V>
    int Map<K, V>::countLevels()
    {
        return Node::getHeight(m_root);
    }

    // simply calls the fillIdsInOrder function, which runs in O(n)
    template<typename K, typename V>
    void Map<K, V>::fillIdsInOrder(std::vector<K>& ids) const
    {
        fillIdsInOrder(m_root, ids);
    }

    // constructors of the node class. Both use initialization lists and need only calculate m_bal after that.
    template<typename K, typename V>
    Map<K, V>::Node::Node(Node* l, Node* r) : m_name(""), m_left(l), m_right(r)
    {
        calcHeight();
        calcBal();
    }

    template<typename K, typename V>
    Map<K, V>::Node::Node(V n, K id, Node* l, Node* r) : m_name(n), m_id(id), m_left(l), m_right(r)
    {
        calcHeight();
        calcBal();
    }

    // getHeight appeared as a recursive function in my solution to Stepik exercise 5.2.1. This, however, uses the m_height's of child nodes
    // to accomplish the same task in constant time, also with an algorithm infromed by slide 18 of the Trees-1 slides
    template<typename K, typename V>
    int Map<K, V>::Node::getHeight(Node* node)
    {
        if (node == nullptr)
            return 0;              // return 0 if the node is null
        else
            return node->m_height; // else return its height

    }

    // functionality has been split in two here, one as a static and on as a const member function of the node struct
    template<typename K, typename V>
    int Map<K, V>::Node::getHeight() const
    {
        return m_height;
    }

    // calculate and return the height of the current node. Runs in O(1) time.
    template<typename K, typename V>
    int Map<K, V>::Node::calcHeight()
    {
        if (m_left != nullptr && m_right != nullptr)      // both children exist
            m_height = 1 + std::max(m_left->m_height, m_right->m_height);              // return the max of its children's heights
        else if (m_left != nullptr || m_right != nullptr) // only one exists
            m_height = 1 + ((m_left == nullptr) ? m_right->m_height : m_left->m_height);
        else
            m_height = 1;

        return m_height;
    }

    // calcBal appeared with some differences in my solution to Stepik exercise 5.2.1. Runs in O(1) time
    template<typename K, typename V>
    int Map<K, V>::Node::calcBal()
    {
        m_bal = getHeight(m_left) - getHeight(m_right); // sets m_bal. Enforces the left-right convention for this implementation
                                                        // uses static getHeight to catch null pointers and avoid seg faults
        return m_bal; // return copy of m_bal to caller.
    }

    template<typename K, typename V>
    int Map<K, V>::size()
    {
        return m_size;
    }

    int getStringData(const std::string& value, std::vector<std::string>& vec, Map<std::string, tacl::UnorderedSet<unsigned int>>& map)
    {
        std::istringstream iss(value);
        unsigned int counter = 0;

        std::string word;
        while (getline(iss, word, ' '))
        {
            vec.push_back(word);

            try
            {
                UnorderedSet<unsigned int>& posSet = map.search(word);
                posSet.insert(counter);
            }
            catch (std::exception& e)
            {
                UnorderedSet<unsigned int> temp;
                temp.insert(counter);
                map.insert(word, temp);
            }

            counter++;
        }

        return counter;
    }
}

