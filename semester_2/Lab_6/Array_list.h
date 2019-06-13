//
// Created by sadoffnick on 13.06.19.
//

#ifndef LAB_6_ARRAY_LIST_H
#define LAB_6_ARRAY_LIST_H

const int MAXSIZE = 1048576;

class Array_list{
public:

    element* elems[MAXSIZE];

    Array_list* create_empty();

    void add_element(int value);

    void delete_element(int value);

    int find_by_range(int st, int fin);

    void print();
};



#endif //LAB_6_ARRAY_LIST_H
