#include "headers/tree.h"
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
    // Search for parentNode;
    // Insert as a child of that node
}
