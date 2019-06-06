#include <iostream>
#include "Binary_Tree.cpp"

void interactive(){
   std::cout << "Hello, dear user!\n";
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

   std::cout << "Now that would be transformed into binary tree (Task 19, unit 4):\n";
   Binary_node* bin_root = build_binary_tree(root);
   print_tree(bin_root);

   std::cout << "Now let's make that a sewd tree (Task 20, Unit 5):\n";
   Binary_node* prev = nullptr;
   sewd_tree(bin_root,prev);
   std::cout << "Now we can go through sewd tree (is symmetric order):\n";
   print_sewd_tree(bin_root);
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