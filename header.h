#include <iostream>
#include <fstream>

#ifndef BST_H
#define BST_H

class Game;
class GamesPlayedNode;
class Player;

// Class to represent a single node in the binary search tree, containing information about a game played
class GamesPlayedNode
{
private:
    std::string ID;    // Unique identifier for the game
    float hrsPlayed;   // Total hours played for this game
    int achievements;  // Number of achievements unlocked for this game

public:
    // Constructors
    GamesPlayedNode(std::string id = "", float hrs = 0.0f, int ach = 0) : ID(id), hrsPlayed(hrs), achievements(ach) {}
    GamesPlayedNode(const GamesPlayedNode &obj) { this->ID = obj.ID; this->hrsPlayed = obj.hrsPlayed; this->achievements = obj.achievements; }

    // Getter and setter methods
    std::string getID() const { return ID; }
    void setID(const std::string &id) { ID = id; }
    float getHrsPlayed() const { return hrsPlayed; }
    void setHrsPlayed(float hours) { hrsPlayed = hours; }
    int getAchievements() const { return achievements; }
    void setAchievements(int ach) { achievements = ach; }

    // Operator overloading for comparison and equality
    bool operator<(GamesPlayedNode &other) { return this->ID < other.ID; }
    bool operator>(GamesPlayedNode &other) { return this->ID > other.ID; }
    bool operator==(GamesPlayedNode &other) { return this->ID == other.ID; }
    bool operator<(std::string other) { return this->ID < other; }
    bool operator>(std::string other) { return this->ID > other; }
    bool operator==(std::string other) { return this->ID == other; }

    // Overloading the << operator to easily output the contents of a GamesPlayedNode
    friend std::ostream &operator<<(std::ostream &out, GamesPlayedNode &obj)
    {
        out << "ID: " << obj.ID << '\n';
        out << "Hours Played: " << obj.hrsPlayed << '\n';
        out << "Acheivements Unlocked: " << obj.achievements << '\n';
        out << '\n';
        return out;
    }
};

template <typename T>
class BST;

// A simple node struct to be used in the Queue class
template <typename T>
struct Node
{
    T data;
    Node<T> *next;

    Node() { next = nullptr; }
    Node(const T &val) : data(val) { next = nullptr; }
};

// A simple queue implementation to be used in the BST class
template <typename T>
class Queue
{
    Node<T> *head;
    Node<T> *tail;
    int size;

public:
    // Constructor and destructor
    Queue() : head(nullptr), tail(nullptr), size(0) {}
    ~Queue()
    {
        while (head)
        {
            Node<T> *toDel = head;
            head = head->next;
            delete toDel;
        }
        head = tail = nullptr;
    }

    // Enqueue and dequeue operations
    void enqueue(const T &val)
    {
        size++;
        if (head == nullptr) { head = tail = new Node<T>(val); return; }
        else { tail->next = new Node<T>(val); tail = tail->next; return; }
    }
    T dequeue()
    {
        Node<T> *temp = head;
        head = head->next;
        T value = temp->data;
        delete temp;
        size--;
        return value;
    }

    // Helper methods
    bool isEmpty() { return head == nullptr; }
    int getSize() { return size; }
};

// A struct to represent a single node in the binary search tree
template <typename T>
struct TreeNode
{
    T data;     // Data stored in this node
    TreeNode *left, *right;  // Pointers to the left and right child nodes

    TreeNode() { left = right = nullptr; }
    TreeNode(T &val) : data(val) { left = right = nullptr; }
};

// A generic binary search tree implementation
template <typename T>
class BST
{
protected:
    TreeNode<T> *root;  // Pointer to the root node of the tree

    // Helper functions
    void destroy(TreeNode<T> *curr)
    {
        // Recursively delete all nodes in the tree
        if (curr)
        {
            destroy(curr->left);
            destroy(curr->right);
            delete curr;
        }
    }
    TreeNode<T> *findMin(TreeNode<T> *curr)
    {
        // Find the node with the minimum value in the subtree starting from the given node
        while (curr->left != NULL) curr = curr->left;
        return curr;
    }
    TreeNode<T> *deleteTreeNode(TreeNode<T> *root, std::string info)
    {
        // Recursively delete the node with the given ID from the tree
        if (root == NULL) return root;
        if (root->data > info) root->left = (deleteTreeNode(root->left, info));
        else if (root->data < info) root->right = (deleteTreeNode(root->right, info));
        else
        {
            if (root->left == NULL && root->right == NULL) { delete root; return NULL; }
            else if (root->left == NULL) { TreeNode<T> *temp = root->right; delete root; return temp; }
            else if (root->right == NULL) { TreeNode<T> *temp = root->left; delete root; return temp; }
            TreeNode<T> *temp = findMin(root->right);
            root->data = (temp->data);
            root->right = (deleteTreeNode(root->right, temp->data.getID()));
        }
        return root;
    }
    TreeNode<T> *search(TreeNode<T> *root, std::string key)
    {
        // Search the tree for the node with the given ID, and return a pointer to it
        if (root == NULL || root->data == key) return root;
        TreeNode<T> *curr = root;
        while (curr)
        {
            std::cout << "ID of current data: " << curr->data.getID() << '\n';  // Debugging output
            if (curr->data > key) curr = curr->left;
            else if (curr->data < key) curr = curr->right;
            else return curr;
        }
        return nullptr;
    }
    void preorderTraversal(TreeNode<T> *curr)
    {
        // Perform a preorder traversal of the tree, starting from the given node
        if (curr != nullptr)
        {
            std::cout << curr->data << '\n';
            preorderTraversal(curr->left);
            preorderTraversal(curr->right);
        }
    }
    void TopKElements(TreeNode<T> *root, int &k)
    {
        // Print the top k elements in the tree, in descending order
        if (!root || k <= 0) return;
        TopKElements(root->right, k);  // Traverse the right subtree first
        if (k > 0) { k--; std::cout << root->data << '\n'; }
        if (k != 0) TopKElements(root->left, k);  // If needed, traverse the left subtree
    }

public:
    // Constructor and destructor
    BST() { root = nullptr; }
    ~BST()
    {
        if (root) { destroy(root); }
        root = nullptr;
    }

    // Move ownership of the tree to another BST object
    void moveOwnerShip(BST<T> &from)
    {
        this->root = from.root;
        from.root = nullptr;
    }

    // Public methods
    void insert(T &val)
    {
        // Insert a new node with the given value into the tree
        if (!root) { root = new TreeNode<T>(val); return; }
        TreeNode<T> *curr = root;
        while (curr)
        {
            if (val < curr->data)
            {
                if (!curr->left) { curr->left = new TreeNode<T>(val); return; }
                curr = curr->left;
            }
            else if (val > curr->data)
            {
                if (!curr->right) { curr->right = new TreeNode<T>(val); return; }
                curr = curr->right;
            }
            else { std::cout << "Value Already Exists\n"; return; }
        }
    }
    void deleteTreeNode(const std::string &info) { deleteTreeNode(root, info); }
    TreeNode<T> *search(std::string dataID) { return search(root, dataID); }
    void showNlayers(int layers)
    {
        // Print the first 'layers' levels of the tree, using a breadth-first traversal
        if (layers < 0) return;
        Queue<TreeNode<T> *> q;
        q.enqueue(root);
        int currLayer = 0;
        while (currLayer < layers && !q.isEmpty())
        {
            int size = q.getSize();
            for (int i = 0; i < size; i++)
            {
                TreeNode<T> *node = q.dequeue();
                std::cout << node->data;
                if (node->left) q.enqueue(node->left);
                if (node->right) q.enqueue(node->right);
            }
            ++currLayer;
        }
        if (currLayer < layers) { std::cout << "No More Layers\n"; }
    }
    void findAndEdit(std::string ID)
    {
        // Find the node with the given ID, allow the user to edit the data, and update the tree
        TreeNode<T> *toDel = search(ID);
        if (toDel)
        {
            TreeNode<T> *newNode = toDel;
            bool changedID = newNode->data.edit();
            if (changedID)
            {
                deleteTreeNode(toDel->data.getID());
                insert(newNode->data);
            }
            else { toDel = newNode; }
        }
    }
    void TopKElements(int k) { TopKElements(root, k); }

    // Operator overload
    friend std::ostream &operator<<(std::ostream &out, BST<T> &obj)
    {
        obj.preorderTraversal(obj.root);
        return out;
    }
};

// A specialized version of the BST class for GamesPlayedNode objects
class GamesPlayedBST : public BST<GamesPlayedNode>
{
    int nodes;  // Keep track of the number of nodes in the tree

    // Helper function to recursively write the games data to a file
    void writeGames(TreeNode<GamesPlayedNode>* root, std::ofstream& file)
    {
        if (root != nullptr)
        {
            file << root->data.getID() << ',' << root->data.getHrsPlayed() << ',' << root->data.getAchievements() << ',';
            writeGames(root->left, file);
            writeGames(root->right, file);
        }
    }

public:
    // Constructor
    GamesPlayedBST() : BST<GamesPlayedNode>() { nodes = 0; }

    // Overridden methods
    void insert(GamesPlayedNode &obj)
    {
        // Insert a new node and increment the node count
        BST<GamesPlayedNode>::insert(obj);
        ++nodes;
    }
    void moveOwnerShip(GamesPlayedBST &other)
    {
        // Move ownership of the tree and update the node count
        BST::moveOwnerShip(other);
        this->nodes = other.nodes;
    }
    void deleteTreeNode(std::string ID)
    {
        // Delete the node with the given ID and decrement the node count
        BST<GamesPlayedNode>::deleteTreeNode(ID);
        --nodes;
    }
    void writeGames(std::ofstream& file)
    {
        // Write all the games data to the provided file
        writeGames(root, file);
        file << '\n';
    }

    // Getter method
    int getGamesPlayed() const { return nodes; }
};

#endif