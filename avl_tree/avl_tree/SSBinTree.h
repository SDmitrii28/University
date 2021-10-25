#pragma once
#include "SSBinTree.h"
#include "BinTree.h"

class SSBinTree : public BinTree {
public:
    SSBinTree() : BinTree() {};
    SSBinTree(int n);
    SSBinTree(int* a, int n);
    SSBinTree(const SSBinTree&);
    SSBinTree& operator=(const SSBinTree&);
    virtual ~SSBinTree() {};
    virtual void Add(int k, Node* p) override;
    virtual void Del(Node* p) override;
private:
    int SSHeight(Node* p);
    void Balance(Node* t, int turn);
    void checkBalance(Node* p);
};
SSBinTree::SSBinTree(int n)
{
    if (n == 0)
    {
        root = NULL;
    }
    else
    {
        root = new Node(rand() % 50);
        for (int i = 0; i < n; i++)
        {
            Add(rand() % 50, root);
        }
    }
}

SSBinTree::SSBinTree(int* a, int n)
{
    root = new Node(a[0]);
    for (int i = 1; i < n; i++)
    {
        Add(a[i], root);
    }
}

SSBinTree::SSBinTree(const SSBinTree& T)
{
    if (T.root == NULL)
        root = NULL;
    else
    {
        root = new Node(T.root->key);
        Copy(T.root->left, root, 0);
        Copy(T.root->right, root, 1);
    }
}

SSBinTree& SSBinTree::operator=(const SSBinTree& T)
{
    if (T.root != root)
    {
        delete root;
        root = new Node(T.root->key);
        Copy(T.root->left, root, 0);
        Copy(T.root->right, root, 1);
    }
    return *this;
}

void SSBinTree::Add(int k, Node* p)
{
    Node* q;
    if (k < p->key)
    {
        if (p->left == NULL)
        {
            q = new Node(k);
            p->left = q;
            q->parent = p;
            checkBalance(p);
        }
        else
        {
            Add(k, p->left);
        }
    }
    else
    {
        if (p->right == NULL)
        {
            q = new Node(k);
            p->right = q;
            q->parent = p;
            checkBalance(p);
        }
        else
        {
            Add(k, p->right);
        }
    }
}

void SSBinTree::Del(Node* p)
{
    Node* q = p->parent;
    if (p->left == NULL && p->right == NULL)
    {
        if (q->left == p)
            q->left = NULL;
        else
            q->right = NULL;
        delete p;
        checkBalance(q);
        return;
    }
    if (p->left == NULL && p->right != NULL)
    {
        if (q->left == p)
            q->left = p->right;
        else
            q->right = p->right;
        p->right->parent = q;
        delete p;
        checkBalance(q);
        return;
    }
    if (p->left != NULL && p->right == NULL)
    {
        if (q->left == p)
            q->left = p->left;
        else
            q->right = p->left;
        p->left->parent = q;
        delete p;
        checkBalance(q);
        return;
    }
    Node* t = p->left;
    if (t->right == NULL)
    {
        t->parent = q;
        if (q->left == p)
            q->left = t;
        else
            q->right = t;
        t->right = p->right;
        p->right->parent = t;
        checkBalance(q);
    }
    else
    {
        while (t->right != NULL)
        {
            t = t->right;
        }
        Node* t_parent = t->parent;
        t->parent->right = t->left;
        if (t->left != NULL)
            t->left->parent = t->parent;
        t->left = p->left;
        t->right = p->right;
        p->left->parent = t;
        p->right->parent = t;
        t->parent = q;
        if (q->left == p)
            q->left = t;
        else
            q->right = t;
        checkBalance(t_parent);
    }
    delete p;
    return;
}

int SSBinTree::SSHeight(Node* p)
{
    int r = FindHeight(p->right);
    int l = FindHeight(p->left);
    return r - l;
}

void SSBinTree::checkBalance(Node* p)
{
    Node* t = p->parent;
    int node_heights_son = SSHeight(p);
    int node_heights_parent;
    while (t != NULL)
    {
        node_heights_parent = SSHeight(t);
        if (abs(node_heights_parent) == 2)
        {
            int multiply = node_heights_parent * node_heights_son;
            if (multiply < 0 && node_heights_son < 0)
                Balance(t, 12);
            else if (multiply < 0 && node_heights_son > 0)
                Balance(t, 21);
            else if (multiply > 0 && node_heights_son < 0)
                Balance(t, 1);
            else if (multiply > 0 && node_heights_son > 0)
                Balance(t, 2);
            break;
        }
        t = t->parent;
        node_heights_son = node_heights_parent;
    }
}

void SSBinTree::Balance(Node* t, int turn)
{
    switch (turn)
    {
    case 1:
    {
        Node* p = t->left;
        if (t->parent != NULL)
            if (t->parent->left == t)
                t->parent->left = p;
            else
                t->parent->right = p;
        if (root == t)
            root = p;
        p->parent = t->parent;
        t->parent = p;
        t->left = p->right;
        if (p->right != NULL)
        {
            p->right->parent = t;
        }
        p->right = t;
        break;
    }
    case 2:
    {
        Node* p = t->right;
        if (t->parent != NULL)
            if (t->parent->left == t)
                t->parent->left = p;
            else
                t->parent->right = p;
        if (root == t)
            root = p;
        p->parent = t->parent;
        t->parent = p;
        t->right = p->left;
        if (p->left != NULL)
        {
            p->left->parent = t;
        }
        p->left = t;
        break;
    }
    case 21:
    {
        Node* p = t->left;
        //step 1
        Node* u = p->right;
        t->left = u;
        u->parent = t;
        p->parent = u;
        p->right = u->left;
        if (u->left != NULL)
        {
            u->left->parent = p;
        }
        u->left = p;
        //step 2
        Balance(t, 1);
        break;
    }
    case 12:
    {
        Node* p = t->right;

        Node* u = p->left;
        t->right = u;
        u->parent = t;
        p->parent = u;
        p->left = u->right;
        if (u->right != NULL)
        {
            u->right->parent = p;
        }
        u->right = p;

        Balance(t, 2);
        break;
    }
    default:
        break;
    }
}