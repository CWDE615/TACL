#pragma once
#include <iostream>
#include <string>
#include <vector>

namespace tacl
{
    /* code in this file is resused from CW Ellis' submssion in Project 1. Retooled to use templates instead of just ints */
    // types U and D represent unique and data, respectively. As written, this AVL tree will not allow the existence of two elements
    // that have a matching U and D field
    //template<typename U, typename D>
    struct Node
    {
        // members of the node class. As a convention, names of all member variables in this implementation start with m_
        std::string m_name;  // the name of the node
        long m_id;      // their id
        int m_bal;      // the node's current balance
        int m_height;   // the node's current height
        Node* m_left;   // left and right child pointers
        Node* m_right;

        // Node constructors
        Node(Node* l = nullptr, Node* r = nullptr);
        Node(std::string n, long id, Node* l = nullptr, Node* r = nullptr);
        static int getHeight(Node* node);  // gets the height of the passed node
        int getHeight() const;
        int calcHeight();                  // recalculates and returns the height of a node
        int calcBal();                     // recalculates and returns the balance of a node
    };

    class AvlTree
    {
        Node* m_root; // root node

        // Private helper functions
        std::string traversePreRec(Node* root); // Recursive Preorder, Inorder and Postorder traversals
        std::string traverseInRec(Node* root);
        std::string traversePostRec(Node* root);

        bool insert(std::string name, long id, Node* root); // insertion, removal and rotation
        bool remove(long id, Node* root);
        Node* remover(Node* root);
        Node* checkRotation(Node* root);
        void checkRotations(Node* root);
        Node* leftRotation(Node* root);
        Node* rightRotation(Node* root);
        Node* leftRightRotation(Node* root);
        Node* rightLeftRotation(Node* root);

        void search(std::string name, Node* root, std::vector<long>& ids) const; // searching
        long search(std::string name, Node* root) const;
        std::string search(long id, Node* root) const;

        // Other helper functions
        void delTree(Node* root);
        void fillIdsInOrder(Node* root, std::vector<long>& ids) const;
        void removeBalHeightFixer(Node* root);


    public:
        AvlTree(Node* root = nullptr); // AvlTree class constructor. Creates a Tree with a root node
        ~AvlTree();                    // AvlTree class destructor.

        // Public Member Functions
        bool insert(std::string name, long id); // insertion and removals
        bool remove(long id);
        bool removeNth(long n);            // removes the Nth iten in the Inorder traversal
        void search(std::string name, std::vector<long>& ids) const; // search by name and receive all results
        long search(std::string name) const;                    // search by name and get the greatest id as a result
        std::string search(long id) const;                      // search by id

        std::string traversePreorder();         // public traversal functions. Act as a launcher for the recursive
        std::string traverseInorder();          // implementations thereof.
        std::string traversePostorder();

        int countLevels();                 // returns the number of levels in the tree
        void fillIdsInOrder(std::vector<long>& ids) const; // gives a public overload of fillIdsInOrder for testing

        static bool idNameValidation(std::string name, long id);
        static bool idValidation(long id);
        static bool nameValidation(std::string name);
        bool isBalanced() const;
        bool isBalanced(Node* root) const; // test function to determine balance of the tree
    };

    // preorder traversal
    // runs in O(n) time in any case where n is the number of nodes, as it performs a preorder traversal over the whole tree, meaning that it has to visit each node and
    // return its value.
    std::string AvlTree::traversePreRec(Node* root)
    {
        if (root == nullptr)
            return "";

        return root->m_name + ", " + traversePreRec(root->m_left) + traversePreRec(root->m_right);
    }

    // inorder traversal
    // same runtime as the preorder traversal for the same reason, except the algorithm for visiting nodes is different.
    std::string AvlTree::traverseInRec(Node* root)
    {
        if (root == nullptr)
            return "";

        return traverseInRec(root->m_left) + root->m_name + ", " + traverseInRec(root->m_right);
    }

    // postorder traversal
    // same runtime as preorder for the same reasons, except visiting in postorder
    std::string AvlTree::traversePostRec(Node* root)
    {
        if (root == nullptr)
            return "";

        return traversePostRec(root->m_left) + traversePostRec(root->m_right) + root->m_name + ", ";
    }

    // checks the rotation of a node
    // This function has no loops and only calls O(1) time functions of the root node. This, with a little further examination reveals that the function's runtime
    // is O(1) in any case, as the worst case is O(1), and the other two cases, such as the best where the root is null, are just constant
    // time improvement 
    Node* AvlTree::checkRotation(Node* root)
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
    void AvlTree::checkRotations(Node* root)
    {
        root->m_left = checkRotation(root->m_left);   // rotates and reassigns the left child, if needed
        root->m_right = checkRotation(root->m_right); // rotates and reassigns the right child, if needed

        if (root == m_root)                 // if the root is the tree's root in general, then the m_root variable
            m_root = checkRotation(m_root); // special reassignment. Further, m_root would not have a parent, so it must
                                            // be treated on its own as an edge case
    }

    // all rotation functions adapted from my solution to Stepik 5.1.1.
    // These rotation algorithms were informed by information given
    // in the resrouces for that assignment. These clearly run in O(1) in any case,
    // for the rotation occurs in a clearly constant time, and the only other operations
    // are calling four other constant time functions
    Node* AvlTree::leftRotation(Node* root)
    {
        Node* top = root;     // set a temp pointer to the roots location
        root = root->m_right; // the root is then set to its right child
        Node* temp = root->m_left; // another temp is set to the the new root's left
        top->m_right = temp;  // the top's right becomes the new temp node
        root->m_left = top;   // with a link established for the root's left child becomes the top


        top->calcHeight();    // recalculate the height and balance of top
        top->calcBal();

        root->calcHeight();   // recalculate balance and height of root
        root->calcBal();      // NOTE: it is important to call the height calculations first
                              // as the height of top may affect the balance of root.

        return root; // returns the root, which is now the top of the balanced structure
    }

    Node* AvlTree::rightRotation(Node* root) // works like left rotation but mirrored
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
    Node* AvlTree::leftRightRotation(Node* root)   // left-right rotation is merely a two step left then right rotation
    {
        root->m_left = leftRotation(root->m_left); // left rotation of the left node
        return rightRotation(root);                // returns a right rotation of the current node
    }

    // because right-left rotation is a mirror of left-right rotation, this too is adapted from 5.1.1
    Node* AvlTree::rightLeftRotation(Node* root)
    {
        root->m_right = rightRotation(root->m_right);
        return leftRotation(root);
    }

    // essentially a linear search through the whole tree using an inorder traversal for all nodes whose names match the passed one.
    void AvlTree::search(std::string name, Node* root, std::vector<long>& ids) const
    {
        if (root != nullptr)
        {
            if (name.compare(root->m_name) == 0)
                ids.push_back(root->m_id);
            search(name, root->m_left, ids);
            search(name, root->m_right, ids);
        }
    }

    // deallocates the tree using a postorder traversal
    // to avoid memory leakage during testing/grading, a destructor is defined for the class and uses this function to deallocate memory.
    // This uses a postorder traversal to visit each node in the tree a single time, and is therefore O(n) time for any case, with n being the number
    // of nodes in the tree.
    void AvlTree::delTree(Node* root)
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
    void AvlTree::fillIdsInOrder(Node* root, std::vector<long>& ids) const
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
    // with root root, instead of linear with the number of nodes in that tree in any case. h ~ O(log(n)) for the number of nodes n, so we can expect
    // that the function is O(log(n)).
    void AvlTree::removeBalHeightFixer(Node* root)
    {
        if (root != nullptr)
        {
            removeBalHeightFixer(root->m_left);
            root->calcHeight();
            root->calcBal();
        }
    }

    // validates a name and id using separate functions
    // calls two functions. idValidation is a constant time operation whereas nameValidation is O(s) in the worst and average cases and O(1) in the best
    // case. The rationale behind that is explained below, but since idNameValidation calls both and idValidation is constant, the worst and average case complexities
    // of the idNameValidation function are therefore O(s) whereas the best case is O(1).
    bool AvlTree::idNameValidation(std::string name, long id)
    {
        return nameValidation(name) && idValidation(id); // return true if both the id and the name are valid and false otherwise.
    }

    // O(1) time operation of checking that the long id is within the range consistant with the valid ids.
    bool AvlTree::idValidation(long id)
    {
        if (id < 0 || id > 99999999)         // the range of valid ids is 0 to 99999999, so nothing greater than 99999999.
            return false;                    // negatives also fail, as these cannot be IDs

        return true;
    }

    // This functions has different running times in the best and worst case. Suppose that the first character in the string was invalid (not alphabetical or a space)
    // then it would be constant because the test would fail immediately. In the average and best case, however, it would either check the whole string or some average fraction
    // thereof. For the average case, the fraction of the time would be a constant multiplier of s, the length of the string; so we would say that this ran in O(s) time on average.
    // The worst case is that the function actually tests the whole string and it passes the inspection. This is obviously O(s) with respect to the string's length s.
    bool AvlTree::nameValidation(std::string name)
    {
        for (char& c : name)
        {
            if (!isalpha(c) && c != 32) // if c is not alpha or a space
                return false;           // return false
        }

        return true;
    }

    // Runs in the same time as the isBalanced function below it.
    bool AvlTree::isBalanced() const
    {
        return isBalanced(m_root);
    }

    // Runs in O(n) time in the worst and average cases where n is the number of nodes in the tree whose root is passed in. The reason for this is that it performs a type of
    // preorder traversal of the tree in any case but the base case or imbalance. Therefore, the worst case would be the one in which all nodes were checked for
    // their balance, which implies O(n). The best case, however, is going to be the one in which the root fails to be balanced. In this case, it fails immediately
    // and is therefore O(1).
    bool AvlTree::isBalanced(Node* root) const
    {
        if (root == nullptr)
            return true;
        else if (root->m_bal > 1 || root->m_bal < -1)
            return false;
        else
            return isBalanced(root->m_left) && isBalanced(root->m_right);
    }

    // constructor of the AvlTree class. It is a constant time operation
    AvlTree::AvlTree(Node* root) : m_root(root) // initialize m_root
    {}

    // destructor of the AvlTree class 
    AvlTree::~AvlTree()
    {
        delTree(m_root);
        m_root = nullptr; // set m_root to null following the tree's deletion
    }

    // return true if insertion successful. Implementation of insertion adapted from
    // my solution to Stepik exercise 4.3.2. Rotations adapted from my solution to 5.1.1
    bool AvlTree::insert(std::string name, long id, Node* root)
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
    bool AvlTree::insert(std::string name, long id)
    {
        if (!idNameValidation(name, id)) // only insert if the name and id are valid
            return false;
        else
            return insert(name, id, m_root);
    }


    // removes a node from the tree.
    bool AvlTree::remove(long id, Node* root)
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

    // helper for the recursive removal function. Runs in variable time, dependant on whether the root node pointer is pointing to a leaf, a node with a single
    // child or a node with two children. In the first and second cases, the function will run in constant time, for the calculations for finding the children are constant and
    // so are the operations of switching and deleting the pointers. Thus the best case is definitely O(1), whereas the worst can be defined as any case falling under the two children
    // category. In this case, the complexity is found by analyizing the fact that O(log(r)), where r is the number of nodes in the root's right subtree,
    // operations are required to find the root's inoreder successor, the fact that the functions calcHeight and calcBal are O(1) and that the function removeBalHeightFixer is O(log(r)) in any case itself.
    // This means that the whole operation would be bounded by log(r) and thus O(log(r)) represents a worst case complexity for the remover function.
    Node* AvlTree::remover(Node* root)
    {
        if (root->m_left != nullptr && root->m_right != nullptr) // if the node has two chldren
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
    bool AvlTree::remove(long id)
    {
        if (!idValidation(id)) // only tries removal on valid id's
            return false;

        return remove(id, m_root);
    }

    // removes the nth element in the inorder traversal of the tree, taking the first to be n==0
    bool AvlTree::removeNth(long n)
    {
        std::vector<long> inOrder;
        fillIdsInOrder(m_root, inOrder); // fill inOrder with the tree's inorder traversal

        if (n > inOrder.size() - 1 || n < 0) // if n is greater than the size of inOrder,
            return false;                    // which is the number of nodes in the tree,
        else                                 // there is no removal.
            return remove(inOrder.at(n), m_root);
    }

    // interface for searching by name. Name validation runs in O(s) in the worst case while the search by name runs in O(n). The final coplexity of this search, therfore,
    // is O(s + n) in the worst case. In the best case, this function is O(1), as it fails to do a search if the name is not valid, which could be determined by its first character
    void AvlTree::search(std::string name, std::vector<long>& ids) const // has no return. If the search fails, then ids will have not changed.
    {
        if (nameValidation(name))  // only do the search if the name is valid
            search(name, m_root, ids);
    }

    // searches by name but only returns a single ID
    // early test function. Not used in final implementation
    long AvlTree::search(std::string name, Node* root) const
    {
        if (root == nullptr)
            return -1;
        else if (name.compare(root->m_name) == 0)
            return root->m_id;
        else
        {
            long idLeft = search(name, root->m_left);     // stores results from the left and right subtrees
            long idRight = search(name, root->m_right);
            return (idLeft < idRight) ? idRight : idLeft; // return the greatest id found. The -1 for failing is ignored if an id exists
        }
    }

    // search by name, returning the greatest id with a matching name
    long AvlTree::search(std::string name) const
    {
        if (!nameValidation(name)) // do not search an invalid name
            return -1;

        return search(name, m_root);
    }

    // search for student by id. Simple BST searching algorithm based on the assumption that the ids are unique.
    std::string AvlTree::search(long id, Node* root) const
    {
        if (root == nullptr)
            return "unsuccessful";            // return unsuccessful if not found
        else if (id < root->m_id)
            return search(id, root->m_left);  // go down the tree until a leaf is reached
        else if (id > root->m_id)
            return search(id, root->m_right);
        else                                  // or until id matches the current root's id.
            return root->m_name;
    }

    // search for an element by its id. Runs in O(log(n)) in the worst case, as it calls the id-based search function and O(1) in the best case, for idValidation
    // is O(1) in any case.
    std::string AvlTree::search(long id) const
    {
        if (!idValidation(id)) // do not search for an invalid id
            return "unsuccessful";

        return search(id, m_root);
    }

    // generates the text for traversePreorder, with extra comma and space cut off the end
    std::string AvlTree::traversePreorder()
    {
        std::string traversal = traversePreRec(m_root);   // use a temp string variable so that we can access its attributes
        return traversal.substr(0, traversal.size() - 2); // trim the final two characters off. These are an extra ", ".
    }

    std::string AvlTree::traverseInorder()
    {
        std::string traversal = traverseInRec(m_root);
        return traversal.substr(0, traversal.size() - 2);
    }

    std::string AvlTree::traversePostorder()
    {
        std::string traversal = traversePostRec(m_root);
        return traversal.substr(0, traversal.size() - 2);
    }

    int AvlTree::countLevels()
    {
        return Node::getHeight(m_root);
    }

    // simply calls the fillIdsInOrder function, which runs in O(n)
    void AvlTree::fillIdsInOrder(std::vector<long>& ids) const
    {
        fillIdsInOrder(m_root, ids);
    }

    // constructors of the node class. Both use initialization lists and need only calculate m_bal after that.
    Node::Node(Node* l, Node* r) : m_name(""), m_left(l), m_right(r)
    {
        calcHeight();
        calcBal();
    }

    Node::Node(std::string n, long id, Node* l, Node* r) : m_name(n), m_id(id), m_left(l), m_right(r)
    {
        calcHeight();
        calcBal();
    }

    // getHeight appeared as a recursvie function in my solution to Stepik exercise 5.2.1. This, however, uses the m_height's of child nodes
    // to accomplish the same task in constant time, also with an algorithm infromed by slide 18 of the Trees-1 slides
    int Node::getHeight(Node* node)
    {
        if (node == nullptr)
            return 0;              // return 0 if the node is null
        else
            return node->m_height; // else return its height

    }

    // functionality has been split in two here, one as a static and on as a const member function of the node struct
    int Node::getHeight() const
    {
        return m_height;
    }

    // calculate and return the height of the current node. Runs in O(1) time.
    int Node::calcHeight()
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
    int Node::calcBal()
    {
        m_bal = getHeight(m_left) - getHeight(m_right); // sets m_bal. Enforces the left-right convention for this implementation
                                                        // uses static getHeight to catch null pointers and avoid seg faults
        return m_bal; // return copy of m_bal to caller.
    }

    // converts the id as a string into an id as a long, if possible. Runs in constant time as all operations after checking the size are bounded by O(s) in
    // the worst case, where s is the length of the sting id, and s == 8 according to the size check. Hence, in any case, the function is O(1).
    long idStringtoLong(std::string id)
    {
        if (id.size() != 8) // fails if the string is not 8 digits. This gives a constant
            return -1;      // upper bound for the rest of the functions operations

        for (int i = 0; i < 7; i++) // check if every character in the number is actually an decimal digit
            if (!isdigit(id.at(i))) // if not, return -1 to signify failure
                return -1;

        int firstNonZero = 0; // holds the index of the first nonzero digit

        while (firstNonZero < 8 && id.at(firstNonZero) == '0') // iterate firstNonZero until it's the desired index. Checks that firstNonZero is actually within range first
            firstNonZero++;

        if (firstNonZero == 8) // if firstNonZero is eight, then all the elements were 0
            return 0;
        else
            return stol(id.substr(firstNonZero, 8 - firstNonZero));
    }

    // constructs the printed version of an ID. Needed to print IDs with leading zeros
    // since an id is, at most, 8 digits, this function is actually O(1) in any case.
    std::string getPrintedId(long id)
    {
        if (!AvlTree::idValidation(id))
            return "error";

        std::string idString = std::to_string(id);
        std::string printed = "00000000";

        for (int i = 0; i < idString.size(); i++)
            printed.at(7 - i) = idString.at(idString.size() - i - 1);

        return printed;
    }

    // prints ids in the passed vector reference. O(n), where n is the number of elements in the vector
    void printIds(std::vector<long>& ids)
    {
        for (auto iter = ids.begin(); iter != ids.end(); iter++)
            std::cout << getPrintedId(*iter) << std::endl;
    }

    // prints the success of a function that returns a bool
    void printSuccess(bool success)
    {
        if (success)
            std::cout << "successful" << std::endl;
        else
            std::cout << "unsuccessful" << std::endl;
    }

    // gets the remainder of a line following the command's first word. substr and getline are O(s), where s is the length of the string, so this runs in
    // that time as well.
    std::string getLineRemoveSpace()
    {
        std::string line;
        std::getline(std::cin, line);
        return line.substr(1, line.size() - 1);
    }
}