#ifndef TREE_H
#define TREE_H

#include "headers/node.h"

template<class nodeType>
class Tree{

public:
    Tree();
    void insertRoot(nodeType* jobToInsert);

    void insertJob(nodeType* jobToInsert, int ParentId);

private:
   node<nodeType>* root;

    node<nodeType>* searchForNode(int nodeId);
    void insertNodeJob(Job* jobToInsert, node<nodeType>* parentNode);

};

#endif // TREE_H
