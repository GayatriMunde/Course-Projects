#ifndef BST_H
#define BST_H
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template <typename T>
struct TreeNode{
    T val;
    TreeNode<T> *left;
    TreeNode<T> *right;
    TreeNode<T> () : val(0), left(nullptr), right(nullptr) {}
    TreeNode<T> (T x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode<T> (T x, TreeNode<T> *left, TreeNode<T> *right) : val(x), left(left), right(right) {}
};

template <class T>
class BST{
    int height, nodeCount;
    TreeNode<T> *root;

    //Traversal Functions
    void inorderTraversal(TreeNode<T> *tempRoot);
    void preTraversal(TreeNode<T> *tempRoot);
    void postTraversal(TreeNode<T> *tempRoot);

    //Helper functions for insert and delete functions
    TreeNode<T> *insertNode(T num, TreeNode<T> *tempRoot);
    TreeNode<T> *removeNode(T val, TreeNode<T> *temp);


 public:
    //Constructors
    BST();
    BST(T value);
    BST(T value, TreeNode<T> *left = NULL, TreeNode<T> *right = NULL);
    BST(vector<T> values);

    TreeNode<T> *createBST(vector<T> values, TreeNode<T> *tempRoot = nullptr);

    void insert(vector<T> values);
    void insert(T value);

    TreeNode<T> *deleteNode(T val){
        return removeNode(val, root);
    }

    bool has(T num, TreeNode<T> *tempRoot = nullptr);
    
    int getHeight(TreeNode<T> *node = NULL);
    T getMaximum(TreeNode<T> *temp = NULL);
    T getMinimum(TreeNode<T> *temp = NULL);
    void display(int choice = 2);
};

#include "bst.cpp"
#endif