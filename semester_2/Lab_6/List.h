
#include "element.h"

struct Node;

class List {
public:
    Node* head;

    List* create_empty();

    void add_element(int value);

    void add_node(Node* node);

    void delete_element(int value);

    int find_by_range(int st, int fin);

    void print();
};

