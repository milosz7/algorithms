#include "BinaryTree.hpp"

constexpr int N_TO_PRINT = 9;

int main()
{
    int n_elements;
    int to_insert;
    std::cin >> n_elements;
    
    BinaryTree<int> tree = BinaryTree<int>();

    for (int i = 0; i < n_elements; i++) {
        std::cin >> to_insert;
        tree.insert(to_insert);
    }

    std::cout << tree.size() << " " 
              << tree.depth() << " " 
              << tree.minimum() << " " 
              << tree.maximum() << std::endl;
    
    tree.preorder();

    for (int i = 0; i < N_TO_PRINT; i++)
        std::cout << (tree.search(i+1) == nullptr ? "No" : "Yes") << std::endl;
}
