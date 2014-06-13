#ifndef NODE_H
#define NODE_H

template<class dataType>
class node{

public:
    node(dataType* dataToInsert);

    dataType *data;
    node *left;
    node *middle;
    node *right;
};

#endif // NODE_H
