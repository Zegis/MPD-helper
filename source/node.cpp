#include "headers/node.h"

template<class dataType> node<dataType>::node(dataType *dataToInsert){

    data = dataToInsert;
    right = 0;
    left = 0;
    middle = 0;
}
