#ifndef NODE_H
#define NODE_H

template<class dataType>
class node{

public:
    node();
    node(dataType dataToInsert);
    node(const node<dataType>& node_in);
    ~node();

    node<dataType>& operator=(const node<dataType>& other);

    dataType *data;
    node *left;
    node *middle;
    node *right;
};

template<class dataType> node<dataType>::node(){
    data = 0;
    right = 0;
    left = 0;
    middle = 0;
}

template<class dataType> node<dataType>::node(dataType dataToInsert){

    data = new dataType(dataToInsert);
    right = 0;
    left = 0;
    middle = 0;
}

template<class dataType> node<dataType>::node(const node<dataType>& node_in)
{
    data = new dataType(*node_in->data);
    right = node_in->right;
    left = node_in->left;
    middle = node_in->middle;
}

template<class dataType> node<dataType>& node<dataType>::operator =(const node<dataType>& other)
{
    if(this == other)
        return *this;
    else
    {
        int* new_data = new int;
        new_data = &other->data;

        delete data;

        data = new_data;
        left = other->left;
        right = other->right;
        middle = other->middle;
    }

    return *this;
}

template<class dataType> node<dataType>::~node()
{
    delete data;
}

#endif // NODE_H
