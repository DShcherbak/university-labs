#include <iostream>
#include "Binary_Tree.cpp"

void interactive(){
   std::cout << "Hello, dear user!\n";
   Node* root = nullptr;
   Binary_node* bin_root = nullptr, *prev = nullptr;
    char key; char tree_num; int v;

    while(true){
        std::cout << "Here's list of your options:\n";
        std::cout << "Enter \"n\" to add a new node to one of the trees\n";
        std::cout << "Enter \"d\" to delete all nodes with some value from a tree\n";
        std::cout << "Enter \"b\" to create a binary tree based on regular one\n";
        std::cout << "Enter \"p\" to print one of the trees\n";
        std::cout << "Enter \"t\" to make a threaded tree out of binary (and print it in symetric order)\n";
        std::cout << "Enter \"q\" to quit.\n";
        std::cin >> key;
        if(key == 'q'){
            std::cout << "Good bye!\n";
            return;
        }
        else if (key == 'n' || key == 'd' || key == 'p') {
            std::cout << "You should choose operand for your function.\n";
            std::cout << "Enter 0 to choose binary tree.\n";
            std::cout << "Enter anything else otherwise.\n";
            std::cin >> tree_num;
        }
        switch(key){
            case 'n':
                std::cout << "Enter value to add:";
                std::cin >> v;
                if(tree_num == '0')
                    add_value_to_tree(bin_root,v);
                else
                    add_value_to_tree(root,v);
                break;
            case 'd':
                std::cout << "Enter value to delete:";
                std::cin >> v;
                if(tree_num == '0')
                    delete_node_by_value(bin_root,v);
                else
                    delete_node_by_value(root,v);
                break;
            case 'b':
                delete_tree(bin_root);
                bin_root = build_binary_tree(root);
                break;
            case 'p':
                if(tree_num == '0')
                    print_tree(bin_root);
                else
                    print_tree(root);
                break;
            case 't':
                threaded_tree(bin_root,prev);
                print_threaded_tree(bin_root);

                break;
            case 'q':
                delete_tree(root);
                delete_tree(bin_root);
                return;
            default:
                std::cout << "No such command.\n";
                break;
        }
    }
}

void demo(){
   std::cout << "Hello, dear user!\n";
   Node* root = build_tree();
   std::cout << "Enter root's value:";
   int v; std::cin >> v; add_value_to_tree(root,v);
   std::cout << "Enter number or nodes in tree (task 4, unit 1):";
   int n; std::cin >> n;
   std::cout << n << "number's are generated randomly and added to the tree\n";
   for(int i = 0; i < n; i++){
       v = randomInt(0,100000);
       add_value_to_tree(root,v);
   }
   std::cout << "(task 8, unit 2)";
   print_tree(root);

   std::cout << "Here deleting would be...(Task 16, Unit 3):\n";
   std::cin >> v;
   delete_node_by_value(root,v);

   print_tree(root);

   std::cout << "Now that would be transformed into binary tree (Task 19, unit 4):\n";
   Binary_node* bin_root = build_binary_tree(root);
   print_tree(bin_root);

   std::cout << "Now let's make that a threaded tree (Task 20, Unit 5):\n";
   Binary_node* prev = nullptr;
   threaded_tree(bin_root,prev);
   std::cout << "Now we can go through threaded tree (is symmetric order):\n";
   print_threaded_tree(bin_root);
   std::cout << "Good bye! :)\n";
}

int main() {
   int key;
   while(true) {
       std::cout << "MAIN MENU\n";
       std::cout << "Please, choose your mode:\n";
       std::cout << "Press 1 for interactive mode.\n";
       std::cout << "Press 2 for demonstration mode.\n";
       std::cout << "Press 3 to exit the program\n";
       std::cin >> key;
       switch(key){
           case 1:
               interactive();
               return 0;
           case 2:
               demo();
               return 0;
           case 3:
               return 0;
           default:
               std::cout << "Try another command!\n";

       }
   }
}