//AVL.h

#ifndef MyDS_H
#define MyDS_H
#include <iostream>
#include <string>
//#include "graphviz/gvc.h"
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

class AVL
{
private:
    struct treeNode
    {
        treeNode *left = nullptr;
        treeNode *right = nullptr;
        int height = 0;
        std::string data;

        treeNode(std::string v, treeNode *l, treeNode *r, int h)
            : data(std::move(v)), left(l), right(r), height(h) {}
    };
    treeNode *root;
    void pushNode(const std::string &n, treeNode *&v);
    bool searchNode(const std::string &s, treeNode *&tree);
    void preOrderDigraph(std::ostream &out, treeNode *pre) const;
    std::string dot() const;

public:
    AVL();
    ~AVL();
    void push(const std::string &n);
    void printPreOrder() const;
    void preOrder(treeNode *pre) const;
    void clear(treeNode *&tree);
    void leftSingleRotate(treeNode *&n);
    void rightLeftDoubleRotate(treeNode *&n);
    void rightSingleRotate(treeNode *&n);
    void leftRightDoubleRotate(treeNode *&n);
    bool search(const std::string &s);
    int avlHeight(treeNode *h) const;
    int balancedFactor(treeNode *&h) const;
    void display() const;
};

AVL::AVL()
{
    root = NULL;
}

AVL::~AVL()
{
    clear(root);
}

void AVL::push(const std::string &n)
{
    pushNode(n, root);
}

void AVL::leftSingleRotate(treeNode *&n)
{
    treeNode *temp;
    temp = n->right;
    n->right = temp->left;
    temp->left = n;
    n->height = std::max(avlHeight(n->left), avlHeight(n->right)) + 1;
    n = temp;
    temp->height = std::max(avlHeight(temp->left), avlHeight(temp->right)) + 1;
}

void AVL::rightSingleRotate(treeNode *&n)
{
    treeNode *temp;
    temp = n->left;
    n->left = temp->right;
    temp->right = n;
    n->height = std::max(avlHeight(n->left), avlHeight(n->right)) + 1;
    n = temp;
    temp->height = std::max(avlHeight(temp->left), avlHeight(temp->right)) + 1;
}

void AVL::rightLeftDoubleRotate(treeNode *&n)
{
    rightSingleRotate(n->right);
    leftSingleRotate(n);
}

void AVL::leftRightDoubleRotate(treeNode *&n)
{
    leftSingleRotate(n->left);
    rightSingleRotate(n);
}

int AVL::avlHeight(treeNode *h) const
{
    int n;
    if (h == NULL)
    {
        return -1;
    }
    else
    {
        n = h->height;
        return n;
    }
}

int AVL::balancedFactor(treeNode *&h) const
{
    int n;
    if (h == NULL)
    {
        return -1;
    }
    else
    {
        n = avlHeight(h->right) - avlHeight(h->left);
        return n;
    }
}

bool AVL::searchNode(const std::string &s, treeNode *&tree)
{
    if (tree == NULL)
    {
        return false;
    }
    if (s < tree->data)
    {
        return searchNode(s, tree->left); // goes to left node
    }
    if (tree->data < s)
    {
        return searchNode(s, tree->right); // goes to right node
    }
    return true; // We found the value.
}

bool AVL::search(const std::string &x)
{
    if (searchNode(x, root))
    {
        return true;
    }
    else
        return false;
}

void AVL::clear(treeNode *&tree)
{
    if (tree != NULL)
    {
        clear(tree->left);  // clear left node
        clear(tree->right); // clear right node
        delete tree;
    }

    tree = NULL;
}

void AVL::pushNode(const std::string &n, treeNode *&v)
{
    if (v == NULL)
    {
        v = new treeNode(n, NULL, NULL, 0);
    }
    else
    {
        if (n < v->data)
        {
            pushNode(n, v->left); // goes to left node

            if ((avlHeight(v->left) - avlHeight(v->right)) == 2)
            {
                if (n < v->left->data) // new node is the left node of its parent node
                {
                    rightSingleRotate(v);
                }
                else // new node is the right node of its parent node
                {
                    leftRightDoubleRotate(v);
                }
            }
        }
        else if (n > v->data)
        {
            pushNode(n, v->right); // goes to right node
            if ((avlHeight(v->right) - avlHeight(v->left)) == 2)
            {
                if (n > v->right->data) // new node is the right node of its parent node
                {
                    leftSingleRotate(v);
                }
                else // new node is the left node of its parent node
                {
                    rightLeftDoubleRotate(v);
                }
            }
        }
        else
        {
            ; // duplicate; do nothing.
        }
    }
    int a, b, c;
    a = avlHeight(v->left);
    b = avlHeight(v->right);
    c = std::max(a, b);
    v->height = c + 1;
}

void AVL::printPreOrder() const
{
    preOrder(root);
}

void AVL::preOrder(treeNode *pre) const
{
    if (pre != NULL)
    {
        std::cout << " " << pre->data << " ";
        preOrder(pre->left);
        preOrder(pre->right);
    }
}

// translate tree to dot language
// void AVL::preOrderDigraph(std::ostream &out, treeNode *pre) const
// {
//     if (pre != NULL)
//     {
//         out << "\"" + pre->data + "\""
//             << "[label=\"" << pre->data
//             << "\\n"
//             << balancedFactor(pre) << "\"];\n";
//         if (pre->left)
//             out << "\"" + pre->data + "\""
//                 << " -> "
//                 << "\"" + pre->left->data + "\""
//                 << ";\n";
//         if (pre->right)
//             out << "\"" + pre->data + "\""
//                 << " -> "
//                 << "\"" + pre->right->data + "\""
//                 << ";\n";
//         preOrderDigraph(out, pre->left);
//         preOrderDigraph(out, pre->right);
//     }
// }

// std::string AVL::dot() const
// {
//     std::stringstream stm;
//     stm << "digraph {\n";
//     preOrderDigraph(stm, root);
//     stm << "}\n";
//     return stm.str();
// }

// generate graph of the tree
// void AVL::display() const
// {
//     std::ofstream out("tmp/avl.gv");
//     out << dot() << std::endl;
//     out.close();
//     system("dot -Tpng tmp/avl.gv -o tmp/avl.png");
// }

#endif
