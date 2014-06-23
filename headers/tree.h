#ifndef TREE_H
#define TREE_H

#include "headers/node.h"
#include <QList>
#include <QVector>

template<class nodeType>
class Tree{

public:
    Tree();
    ~Tree();

    void insertRoot(nodeType* jobToInsert);

    void insertJob(nodeType* jobToInsert, int ParentId);

    node<nodeType>* searchForNode(int nodeId);

    QVector<QList <int> > getNodeLevels() ;

private:
   node<nodeType>* root;
   void delete_Tree(node<nodeType>* leaf);
};

template<class nodeType> Tree<nodeType>::Tree()
{
    root = 0;
}

template<class nodeType> Tree<nodeType>::~Tree()
{
    if(root != 0)
        delete_Tree(root);
}

template<class nodeType> void Tree<nodeType>::delete_Tree(node<nodeType> *leaf)
{
    if(leaf != 0)
    {
        delete_Tree(leaf->left);
        delete_Tree(leaf->middle);
        delete_Tree(leaf->right);

        delete leaf;
    }
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

template<class nodeType> QVector< QList<int> > Tree<nodeType>::getNodeLevels()
{
    QVector< QList<int> > ret(1);

    node<nodeType>* levelDelimiterNode;
    node<nodeType>* currentNode;
    QList <node<nodeType>* > nodesToVisit;


    levelDelimiterNode = root->left;
    nodesToVisit.append(root);

    //int currentLevel = 0;
    while(nodesToVisit.size() != 0)
    {
        currentNode = nodesToVisit.takeFirst();

        if(currentNode->left != 0)
            nodesToVisit.append(currentNode->left);
        if(currentNode->middle != 0)
            nodesToVisit.append(currentNode->middle);
        if(currentNode->right != 0)
            nodesToVisit.append(currentNode->right);

        if(currentNode != levelDelimiterNode)
        {
            ret.last().append(*(currentNode->data));
        }
        else
        {
            ret.resize(ret.size()+1);
            ret.last().append(*(currentNode->data));
            levelDelimiterNode = currentNode->left;
        }
    }

    return ret;
}

#endif // TREE_H
