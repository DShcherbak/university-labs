#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <algorithm>
#include <queue>


//const double probability = 0.1;



struct Binary_Node{
    Application *a, *b;
    double dist;
    Binary_Node* left, *right, *parent;



    Binary_Node(Application * _a, Application * _b, double _d){
        a = _a;
        b = _b;
        dist = _d;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }

    bool operator <(Binary_Node* a){
        return a->dist < this->dist;
    }
};

void add_node(Binary_Node* root, Binary_Node* new_node){
    //  std::cout << "Adding to " << root->dist << std::endl;
    if(root == nullptr){
        root = new_node;
        return;
    }
    if(root->dist < new_node->dist){
        if(root->right)
            add_node(root->right,new_node);
        else{
            root->right = new_node;
            new_node->parent = root;
        }
    }
    else{
        if(root->left)
            add_node(root->left,new_node);
        else{
            root->left = new_node;
            new_node->parent = root;
        }
    }

}

void random_shuffle(std::vector <edge> &e) {
    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(e.begin(), e.end(), g);
}

Binary_Node* build_binary_tree(std::vector <Application*> apps){
    int n = apps.size();
    Binary_Node* root = new Binary_Node(apps[1],apps[0],distance(apps[1],apps[0]));
    for(int i = 2; i < n; i++){
        for(int j = 0; j < i; j++){
            Binary_Node* new_node = new Binary_Node(apps[i],apps[j],distance(apps[i],apps[j]));
            add_node(root,new_node);
        }
    }
    return root;
}


Binary_Node* build__binary_tree(std::vector <Application*> apps, std::vector <edge> distances){
    int n = distances.size();
    random_shuffle(distances);
    edge p = distances[0];
    Binary_Node* root = new Binary_Node(apps[p.from],apps[p.to],p.cost);
    for(int i = 1; i <n; i++){
        p = distances[i];
        Binary_Node* new_node = new Binary_Node(apps[p.from],apps[p.to],p.cost);
        add_node(root,new_node);
    }
    return root;

}

int create_new_node(std::vector <Binary_Node*> root, Application* a, Application* b){
    Binary_Node* new_node = new Binary_Node(a,b,distance(a,b));
    if(randomInt(1,1000)*0.1/100.0 < probability)
        root.push_back(new_node);
    else{
        int par = randomInt(0,root.size()-1);
        add_node(root[par],new_node);
    }
}

void print_binary_tree_right(Binary_Node* root){
    std::cout << root->dist << " ";
    if(root->left)
        print_binary_tree_right(root->left);
    if(root->right)
        print_binary_tree_right(root->right);
}

void print_tree_right(std::vector <Binary_Node*> roots){
    int n = roots.size();
    for(int i = 0; i < n; i++){
        print_binary_tree_right(roots[i]);
    }
}

int depth(Binary_Node* root){
    if(root == nullptr)
        return 0;
    if(root->left == nullptr && root->right == nullptr){
        return 1;
    }
    return 1+std::max(depth(root->left),depth(root->right));
}

void delete_node_by_value(Binary_Node* root, int val){
    if(root->dist == val){
        if(root->parent == nullptr) {
            root->right->parent = root->left;
        }
    }
}

void delete_root_by_value(Binary_Node* root, int val){
    if(root->dist == val){
        //delete
    }
    else if(root->dist < val)
        delete_node_by_value(root->left,val);
    else
        delete_node_by_value(root->right,val);
}


void print_tree(Binary_Node *root, int depth = 0) {
    if (!root)
        return;
    std::cout << '|';
    for (int i = 0; i < depth; i++)
        std::cout << '\t' << '|';
    std::cout << root->dist << std::endl;
    print_tree(root->left, depth + 1);
    print_tree(root->right, depth + 1);
}

void search_precision(Binary_Node* root, int left, int right){
    if(root->dist < left){
        if(root->right)
            search_precision(root->right,left,right);
    }
    else if(root->dist > right){
        if(root->left)
            search_precision(root->left,left,right);
    }
    else{
        std::cout << "(" << root->dist << ")\n";
        if(root->right)
            search_precision(root->right,left,right);
        if(root->left)
            search_precision(root->left,left,right);
    }
}

std::vector <double> search_precision_vec(Binary_Node* root , double left, double right){
    std::vector <double> res;
    std::vector <double> nw;
    if(root->dist < left){
        if(root->right){
            nw = search_precision_vec(root->right,left,right);
            res.insert(res.end(),nw.begin(),nw.end());
        }
    }
    else if(root->dist > right){
        if(root->left){
            nw = search_precision_vec(root->left,left,right);
            res.insert(res.end(),nw.begin(),nw.end());
        }
    }
    else{
        res.push_back(root->dist);
        if(root->right){
            nw = search_precision_vec(root->right,left,right);
            res.insert(res.end(),nw.begin(),nw.end());
        }
        if(root->left){
            nw = search_precision_vec(root->left,left,right);
            res.insert(res.end(),nw.begin(),nw.end());
        }
    }
    return res;
}

