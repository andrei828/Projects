#include <iostream>

using namespace std;

struct Node
{
    int data;
    Node * leftNode;
    Node * rightNode;
};

Node * FindMin(Node * root)
{
    Node * tmp = root;
    
    while (tmp -> rightNode == nullptr)
    {
        tmp = tmp -> rightNode;
    }
    return tmp;
}

Node * AddNode(Node * root, int data)
{
    if (root == NULL)
    {
        root = new Node;
        root -> data      = data;
        root -> leftNode  = nullptr;
        root -> rightNode = nullptr;
    }
    else if (root -> data > data)
    {
        return AddNode(root -> leftNode, data);
    }
    else if (root -> data < data)
    {
        return AddNode(root -> rightNode, data);
    }
    return root;
}

Node * DeleteNode(Node * root, int data)
{
    if (root == NULL)
    {
        return root;
    }
    else if (root -> data < data)
    {
        root -> rightNode = DeleteNode(root -> rightNode, data);
    }
    else if (root -> data < data)
    {
        root -> leftNode = DeleteNode(root -> leftNode, data);
    }
    else {
        // case 1: Node is a leaf
        if (root -> leftNode == nullptr && root -> rightNode == nullptr)
        {
            delete root;
            root = NULL;
        }
        
        // case 2: Node with 1 child
        else if (root -> leftNode == nullptr)
        {
            Node * tmp = root;
            root = root -> rightNode;
            delete tmp;
        }
        else if (root -> rightNode == nullptr)
        {
            Node * tmp = root;
            root = root -> leftNode;
            delete tmp;
        }
        
        // case 3: Node with 2 children
        else
        {
            Node * tmp = FindMin(root -> rightNode);
            root -> data = tmp -> data;
            root -> rightNode = DeleteNode(root -> rightNode, tmp -> data);
        }
    }
    return root;
}

int main()
{
    Node * root = NULL;
    
    root = AddNode(root, 23);
    root = AddNode(root, 26);
    root = AddNode(root, 12);
    
    root = DeleteNode(root, 26);
    
}
