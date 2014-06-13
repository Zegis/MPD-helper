#ifndef TREE_H
#define TREE_H

#include "headers/node.h"

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

#endif // TREE_H
