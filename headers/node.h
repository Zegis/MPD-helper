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

template<class dataType> node<dataType>::node(dataType *dataToInsert){

    data = dataToInsert;
    right = 0;
    left = 0;
    middle = 0;
}

#endif // NODE_H
