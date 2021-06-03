#include "hulltree.h"

HullTree::HullTree()
{

}

HullTree::HullTree(bool up){
    upperTree = up;
}

std::vector<std::shared_ptr<Edge>> HullTree::getHull(){return {};}

bool HullTree::hasNode(int x, int y){
    auto current = root;
    if(current == nullptr)
        return false;
    while (true) {
        if (current->x > x) {
            if (current->left) {
                current = current->left;
            } else {
                return false;
            }
        } else if (current->x < x){
            if (current->right) {
                current = current->right;
            } else {
                 return false;
            }
        } else {
            return current->y == y;
        }
    }
}


std::shared_ptr<HullNode> HullTree::fixTree(std::shared_ptr<HullNode> node){
    auto parent = node->parent;
    auto grandparent = node->parent->parent;

    while (grandparent) {
        if ((upperTree && node->y < parent->y) ||
        (!upperTree && node->y > parent->y)) {
            if (parent->left == node) {
                if (node->right) {
                    node->right->parent = parent;
                }
                parent->left = node->right;
                node->right = parent;
            } else {
                if (node->left) {
                    node->left->parent = parent;
                }
                parent->right = node->left;
                node->left = parent;
            }
            parent->parent = node;
            node->parent = grandparent;

            if (grandparent->left == parent) {
                grandparent->left = node;
            } else {
                grandparent->right = node;
            }

            parent = node->parent;
            grandparent = parent->parent;
        } else {
            parent = parent->parent;
            grandparent = parent->parent;
        }
    }

    if ((upperTree && node->y < parent->y) ||
            (!upperTree && node->y > parent->y)) {
        if (parent->left == node) {
            if (node->right) {
                node->right->parent = parent;
            }
            parent->left = node->right;
            node->right = parent;
        } else {
            if (node->left) {
                node->left->parent = parent;
            }
            parent->right = node->left;
            node->left = parent;
        }
        parent->parent = node;
        node->parent = grandparent;
        return node;
    }

    return std::shared_ptr<HullNode>(parent);

}

void printNode(std::shared_ptr<HullNode> node, int depth){
    if(node == nullptr)
        return;
    printNode(node->left, depth + 1);
    for(int i = 0; i < depth; i++){
        std::cout << "\t";
    }
    std::cout << node->x << " " << node->y << std::endl;
    printNode(node->right, depth + 1);
}

void HullTree::printTree(){
    printNode(root, 0);
}

std::shared_ptr<HullNode> HullTree::addNode(int x, int y){
    auto current = root;
    std::cout << "Start!\n";
    if(root == nullptr){
        std::cout << "I'm herewith no roots!\n";
        root = std::make_shared<HullNode>();
        root->x = x;
        root->y = y;
        return current;
    }
    std::cout << "I'm herewith roots!\n";
    std::cout << "I'm here!\n";
    while (true) {
            if (current->x > x) {
                if (current->left) {
                    current = current->left;
                } else {
                    current->left = std::make_shared<HullNode>();
                    current->left->parent = current;
                    current->left->x = x;
                    current->left->y = y;
                    current->left->part = true;
                    return fixTree(current->left);
                }
            } else {
                if (current->right) {
                    current = current->right;
                } else {
                    current->right = std::make_shared<HullNode>();
                    current->right->parent = current;
                    current->right->x = x;
                    current->right->y = y;
                    current->right->part = true;
                    return fixTree(current->right);
                }
            }
        }
}
std::shared_ptr<HullNode> HullTree::eraseNode(int x, int y){
    auto current = root;
    if(root->x == x && root->y == y){
    }
    std::cout << "Start!\n";
    if(root == nullptr){
        std::cout << "I'm herewith no roots!\n";
        root = std::make_shared<HullNode>();
        root->x = x;
        root->y = y;
        return current;
    }
    std::cout << "I'm herewith roots!\n";
    std::cout << "I'm here!\n";
    while (true) {
            if (current->x > x) {
                if (current->left) {
                    current = current->left;
                } else {
                    current->left = std::make_shared<HullNode>();
                    current->left->parent = current;
                    current->left->x = x;
                    current->left->y = y;
                    current->left->part = true;
                    return fixTree(current->left);
                }
            } else {
                if (current->right) {
                    current = current->right;
                } else {
                    current->right = std::make_shared<HullNode>();
                    current->right->parent = current;
                    current->right->x = x;
                    current->right->y = y;
                    current->right->part = true;
                    return fixTree(current->right);
                }
            }
        }
}

void HullTree::reset(){
    root = nullptr;
}
