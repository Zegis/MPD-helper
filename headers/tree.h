#ifndef TREE_H
#define TREE_H

#include "headers/node.h"
#include <QList>

template<class nodeType>
class Tree{

public:
    Tree();

    void insertRoot(nodeType* jobToInsert);

    void insertJob(nodeType* jobToInsert, int ParentId);

    node<nodeType>* searchForNode(int nodeId);

private:
   node<nodeType>* root;
};

template<class nodeType> Tree<nodeType>::Tree()
{
    root = 0;
}

template<class nodeType> void Tree<nodeType>::insertRoot(nodeType *jobToInsert)
{
    if(root)
        return;
    else{
        root = new node<nodeType>(jobToInsert);
    }
}

template<class nodeType> void Tree<nodeType>::insertJob(nodeType *jobToInsert, int ParentId)
{
    node<nodeType>* parent = searchForNode(ParentId);
   // node<nodeType> newNode = node<nodeType>(jobToInsert);

    if(parent->left == 0x0)
    {
        parent->left = new node<nodeType>(jobToInsert);
        return;
    }
    else if(parent->middle == 0)
    {
        parent->middle = new node<nodeType>(jobToInsert);
        return;
    }
    else if(parent->right == 0)
        parent->right = new node<nodeType>(jobToInsert);
}

template<class nodeType> node<nodeType>* Tree<nodeType>::searchForNode(int nodeId)
{
    node<nodeType>* nodeToCheck;
    QList< node<nodeType>* > nodesToVisit;
    nodesToVisit.append(root);

    while(nodesToVisit.size() != 0)
    {
        nodeToCheck = nodesToVisit.takeFirst();

        if( *(nodeToCheck->data) == nodeId)
        {
            return nodeToCheck;
        }
        else
        {
            if(nodeToCheck->left != 0)
                nodesToVisit.append(nodeToCheck->left);
            if(nodeToCheck->middle != 0)
                nodesToVisit.append(nodeToCheck->middle);
            if(nodeToCheck->right != 0)
                nodesToVisit.append(nodeToCheck->right);
        }
    }
    return 0;
}

#endif // TREE_H
