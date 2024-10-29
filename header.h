#include <iostream>

template <typename T>
struct Node
{
    T data;
    Node<T> *next;

    Node() { next = nullptr; }
    Node(const T &val) : data(val) { next = nullptr; }
};

template <typename T>
class Queue
{
    Node<T> *head;
    Node<T> *tail;

public:
    Queue() : head(nullptr), tail(nullptr) {}

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
    void enqueue(const T &val)
    {
        if (head == nullptr)
        {
            head = tail = new Node<T>(val);
            return;
        }
        else
        {
            tail->next = new Node<T>(val);
            tail = tail->next;
            return;
        }
    }
    T dequeue()
    {
        Node<T> *temp = head;
        head = head->next;

        T value = temp->data;
        delete temp;
        return value;
    }

    bool isEmpty()
    {
        return head == nullptr;
    }

    int getSize()
    {
        int size = 0;
        Node<T> *temp = head;
        while (temp != nullptr)
        {
            size++;
            temp = temp->next;
        }
        return size;
    }
};

template <typename T>
struct TreeNode
{
    T data;
    TreeNode *left, *right;

    TreeNode() { left = right = nullptr; }
    TreeNode(const T &val) : data(val) { left = right = nullptr; }
};

template <typename T>
class BST
{
    TreeNode<T> *root;

    void destroy(TreeNode<T> *curr)
    {
        if (curr)
        {
            destroy(curr->left);
            destroy(curr->right);
            delete curr;
        }
    }
    TreeNode<T> *findMin(TreeNode<T> *curr)
    {
        while (curr->left != NULL)
            curr = curr->left;
        return curr;
    }
    TreeNode<T> *deleteTreeNode(TreeNode<T> *root, const T &info)
    {
        if (root == NULL)
        { // Tree is empty or element not found
            return root;
        }
        if (info < root->data)
        { // Traverse left subtree
            root->left = (deleteTreeNode(root->left, info));
        }
        else if (info > (root->data))
        {
            // Traverse right subtree
            root->right = (deleteTreeNode(root->right, info));
        }
        else
        { // TreeNode to be deleted is found
            // Case 1: TreeNode has no children (it's a leaf)
            if (root->left == NULL && root->right == NULL)
            {
                delete root;
                return NULL;
            }
            // Case 2: TreeNode has one child
            else if (root->left == NULL)
            {
                TreeNode<T> *temp = root->right;
                delete root;
                return temp;
            }
            else if (root->right == NULL)
            {
                TreeNode<T> *temp = root->left;
                delete root;
                return temp;
            }
            // Case 3: TreeNode has two children
            TreeNode<T> *temp = findMin(root->right);
            root->data = (temp->data);
            root->right = (deleteTreeNode(root->right, temp->data));
        }
        return root;
    }
    TreeNode<T> *search(TreeNode<T> *root, std::string key)
    {
        if (root == NULL || root->data == key)
            return root;
        TreeNode<T> *curr = root;
        while (curr)
        {
            if (key < curr->data)
            {
                curr = curr->left;
            }
            else if (key > curr->data)
            {
                curr = curr->right;
            }
            else
            {
                return curr;
            }
        }
        return nullptr;
    }
    void preorderTraversal(TreeNode<T> *curr)
    {
        if (curr != nullptr)
        {
            std::cout << curr->data << '\n';
            preorderTraversal(curr->left);
            preorderTraversal(curr->right);
        }
    }

public:
    BST() { root = nullptr; }
    ~BST()
    {
        destroy(root);
    }

    void moveOwnerShip(BST<T> &from)
    {
        this->root = from.root;
        from.root = nullptr;
    }

    // Methods
    void insert(T &val)
    {
        if (!root)
        {
            root = new TreeNode<T>(val);
            return;
        }
        TreeNode<T> *curr = root;
        while (curr)
        {
            if (val < curr->data)
            {
                if (!curr->left)
                {
                    curr->left = new TreeNode<T>(val);
                    return;
                }
                curr = curr->left;
            }
            else if (val > curr->data)
            {
                if (!curr->right)
                {
                    curr->right = new TreeNode<T>(val);
                    return;
                }
                curr = curr->right;
            }
            else
            {
                std::cout << "Value Already Exists\n";
                return;
            }
        }
    }
    void deleteTreeNode(const T &info)
    {
        deleteTreeNode(root, info);
    }
    TreeNode<T> *search(std::string dataID)
    {
        return search(root, dataID);
    }
    void showNlayers(int layers)
    {
        if (layers < 0)
            return;

        Queue<Node<T> *> q;
        q.push(root);

        int currLayer = 0;
        while (currLayer < layers && !q.isEmpty())
        {
            int size = q.size();
            for (int i = 0; i < size; i++)
            {
                Node<T> *node = q.enqueue();
                std::cout << *node;

                if (node->left)
                    q.enqueue(node->left);
                if (node->right)
                    q.enqueue(node->right);
            }
            ++currLayer;
        }
        if (currLayer < layers)
        {
            std::cout << "No More Layers\n";
        }
    }
    void findAndEdit(std::string ID)
    {
        TreeNode<T> *toDel = search(ID);
        if (toDel)
        {

            TreeNode<T> *newNode = TreeNode<T>();
            newNode = toDel;
            bool changedID = newNode->edit();
            if (changedID)
            {
                deleteTreeNode(toDel->ID);
                insertNode(newNode);
            }
            else
            {
                toDel = newNode;
            }
        }
    }

    // Operator overload
    friend std::ostream &operator<<(std::ostream &out, BST &obj)
    {
        obj.preorderTraversal(obj.root);
        return out;
    }
    // friend std::istream &operator >> (std::istream &in, const BST &obj) {

    // }
};

// template <typename T>
// class GamesPlayedBST : public BST<GamesPlayedNode>
// {
//     int nodes = 0;

// public:
//     GamesPlayedBST() : BST<GamesPlayedNode>() {}
//     void insert(std::string ID)
//     {
//         BST<GamesPlayedNode>::insert(ID);
//         ++nodes;
//     }
//     void deleteTreeNode(std::string ID) {
//         BST<GamesPlayedNode>::deleteTreeNode(ID);
//         --nodes;
//     }

//     int getGamesPlayed () const { return nodes; }
// };

// template <typename T>
// class PlayerBST : public BST<Player>
// {
//     public:
//     PlayerBST() : BST<Player>() {}

// };