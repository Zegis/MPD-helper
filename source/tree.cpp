#include "headers/tree.h"
#include "QList"

template<class nodeType> Tree<nodeType>::Tree(){
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
    node<nodeType>* newNode = node<nodeType>(jobToInsert);

    if(parent->left != 0)
        parent->left = newNode;
    else if(parent->middle != 0)
        parent->middle = newNode;
    else if(parent->right != 0)
        parent->right = newNode;
}

template<class nodeType> node<nodeType>* Tree<nodeType>::searchForNode(int nodeId)
{
    node<nodeType>* nodeToCheck;
    QList< node<nodeType>* > nodesToVisit;
    nodesToVisit.append(root);

    while(nodesToVisit.size() != 0)
    {
        nodeToCheck = nodesToVisit.takeFirst();

        if( nodeToCheck->data = nodeId)
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
