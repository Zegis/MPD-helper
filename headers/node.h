#ifndef NODE_H
#define NODE_H

class Job;

template<class dataType>
class node{

public:
    node(dataType* dataToInsert);

private:
    dataType *data;
    node *left;
    node *middle;
    node *right;
};

#endif // NODE_H
