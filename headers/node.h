#ifndef NODE_H
#define NODE_H

template<class dataType>
class node{

public:
    node(dataType* dataToInsert);
    ~node();

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

template<class dataType> node<dataType>::~node()
{
    delete data;
}

#endif // NODE_H
