#include <iostream>
#include <iomanip> 
#include <Windows.h>
using namespace std;
class Node
{
public:
    int data;
    Node* left;
    Node* right;

    Node(int value) {
        data = value;
        left = right = NULL;
    }
};

class BST {
public:
    Node* root;

    BST() 
    {
        root = nullptr;
    }

    void insert(int value) 
    {
        root = insertRec(root, value);
    }

    Node* insertRec(Node* root, int value)
    {
        if (root == nullptr) {return new Node(value);}

        if (value < root->data) {root->left = insertRec(root->left, value);}

        else if (value > root->data) {root->right = insertRec(root->right, value);}

        return root;
    }

    void inorder() 
    {
        inorderRec(root);
    }

    void inorderRec(Node* root)
    {
        if (root != nullptr) 
        {
            inorderRec(root->left);
            cout << root->data << " ";
            inorderRec(root->right);
        }
    }

    Node* minValue(Node* node)
    {
        Node* current = node;
        while (current && current->left != NULL) 
        {
            current = current->left;
        }
        return current;
    }
    Node* maxValue(Node* node)
    {
        Node* current = node;

        while (current->right != NULL) 
        {
            current = current->right;
        }

        return current;
    }
    Node* deleteNode(Node* root, int value) 
    {
        if (root == nullptr) {return root;}

        if (value < root->data) {root->left = deleteNode(root->left, value);}

        else if (value > root->data) {root->right = deleteNode(root->right, value);}

        else 
        {
            if (root->left == nullptr)
            {
                Node* temp = root->right;
                delete root;
                return temp;
            }
            else if (root->right == nullptr) 
            {
                Node* temp = root->left;
                delete root;
                return temp;
            }

            Node* temp = minValue(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }

        return root;
    }

    void deleteValue(int value) 
    {
        root = deleteNode(root, value);
    }

    bool search(int value) 
    {
        return searchRec(root, value);
    }

    bool searchRec(Node* root, int value) 
    {
        if (root == nullptr) {return false;}

        if (root->data == value) {return true; }

        else if (value < root->data) {return searchRec(root->left, value);}
        else {return searchRec(root->right, value);}
    }
    Node* inOrderSuccessor(Node* root, Node* n)
    {
        if (n->right != nullptr) {return minValue(n->right);}
    
        Node* succ = nullptr;
        Node* temp = root;
        while (temp != nullptr)
        {
            if (n->data < temp->data) 
            {
                succ = temp;
                temp = temp->left;
            }
            else if (n->data > temp->data) 
            {
                temp = temp->right;
            }
            else break;
        }
        return succ;
    }

    Node* inOrderPredecessor(Node* root, Node* n)
    {
        if (n->left != nullptr) {return maxValue(n->left);}

        Node* pred = nullptr;
        Node* temp = root;
        while (temp != nullptr) {
            if (n->data > temp->data) 
            {
                pred = temp;
                temp = temp->right;
            }
            else if (n->data < temp->data) 
            {
                temp = temp->left;
            }
            else break;
        }
        return pred;
    }


    int findMin()
    {
        Node* current = root;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return (current != nullptr) ? current->data : -1;
    }

    int findMax()
    {
        Node* current = root;
        while (current && current->right != nullptr) {
            current = current->right;
        }
        return (current != nullptr) ? current->data : -1;
    }

    void printTree(Node* root, int space = 0, int height = 10) 
    {
        if (root == nullptr) return;

        space += height;
        printTree(root->right, space);
        cout << endl;
        for (int i = height; i < space; i++) cout << " ";
        cout << root->data << "\n";
        printTree(root->left, space);
    }

    Node* findNode(Node* root, int value) 
    {
        while (root != nullptr) 
        {
            if (value < root->data) {root = root->left;}

            else if (value > root->data) {root = root->right;}

            else {return root;}
        }
        return nullptr;
    }

};
void outro()
{
	for (int i = 3; i > 0; i--)
	{
		cout<<i<<"   ";
		Sleep(1000);
	}
}
void displayMenu() 
{
    cout << "1. Insert node" << endl;
    cout << "2. Delete node" << endl;
    cout << "3. Search node" << endl;
    cout << "4. Inorder traversal" << endl;
    cout << "5. Find min value" << endl;
    cout << "6. Find max value" << endl;
    cout << "7. Print tree structure" << endl;
    cout << "8. Find in-order predecessor and successor" << endl;
    cout << "9. Exit" << endl;
    cout << "Choose an option: ";
}

int main()
{
    BST tree;
    int choice, value;

    while (true)
    {
        displayMenu();
        cin >> choice;


        switch (choice)
        {
        case 1:
        {
            cout << "Enter value to insert: ";
            cin >> value;
            tree.insert(value);
            break;
        }
        case 2:
        {
            cout << "Enter value to delete: ";
            cin >> value;
            tree.deleteValue(value);
            break;
        }
        case 3:
        {
            cout << "Enter value to search: ";
            cin >> value;
            cout << "Is " << value << " present? " << (tree.search(value) ? "Yes" : "No") << endl;
            break;
        }
        case 4:
        {
            cout << "Inorder traversal: ";
            tree.inorder();
            cout << endl;
            break;
        }
        case 5:
        {
            cout << "Min value: " << tree.findMin() << endl;
            break;
        }
        case 6:
        {
            cout << "Max value: " << tree.findMax() << endl;
            break;
        }
        case 7:
        {
            cout << "Tree structure:" << endl;
            tree.printTree(tree.root);
            break;
        }
        case 8:
        {
            cout << "Enter value to find predecessor and successor: ";
            cin >> value;
            Node* node = tree.findNode(tree.root, value);
            if (node == nullptr) 
            {
                cout << "Node not found in the tree!" << endl;
            }
            else 
            {
                Node* pred = tree.inOrderPredecessor(tree.root, node);
                Node* succ = tree.inOrderSuccessor(tree.root, node);
                cout << "Inorder Predecessor of " << value << ": " << (pred ? pred->data : -1) << endl;
                cout << "Inorder Successor of " << value << ": " << (succ ? succ->data : -1) << endl;
            }
            break;
        }

        case 9:
        {
            cout<<"GOODBYE!"<<endl;
            outro();
            return 0;
        }
        default:
        {
            cout << "Invalid option! Please try again." << endl;
            break;
        }
        }
    }

    return 0;
}
