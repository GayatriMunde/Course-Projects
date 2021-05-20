#include "bst.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template <class T>
BST<T>::BST(){
    root = new TreeNode<T> ();
    height = 0;
}

template <class T>
BST<T>::BST(T value){
    root = new TreeNode<T> (value); 
    height = 0;
}

template <class T>
BST<T>::BST(T value, TreeNode<T> *left, TreeNode<T> *right){
    root = new TreeNode<T> (value, left, right);
    height = getHeight(root);
}

template <class T>
BST<T>::BST(vector<T> values){
    sort(values.begin(), values.end());
    root = createBST(values);
}

template <class T>
void BST<T>::inorderTraversal(TreeNode<T> *tempRoot){
    if (!tempRoot)  return;
    if(tempRoot){
        inorderTraversal(tempRoot->left);
        cout << tempRoot->val << " ";
        inorderTraversal(tempRoot->right);
    }
}

template <class T>
void BST<T>::preTraversal(TreeNode<T> *tempRoot){
    if (!tempRoot)  return;
    if(tempRoot){
        cout << tempRoot->val << " ";
        inorderTraversal(tempRoot->left);
        inorderTraversal(tempRoot->right);
    }
}

template <class T>
void BST<T>::postTraversal(TreeNode<T> *tempRoot){
    if (!tempRoot)  return;
    if(tempRoot){
        inorderTraversal(tempRoot->left);
        inorderTraversal(tempRoot->right);
        cout << tempRoot->val << " ";
    }
}

template <class T>
TreeNode<T>* BST<T>::insertNode(T num, TreeNode<T> *tempRoot){
    if (tempRoot == nullptr)
        tempRoot = createBST(vector<T>(1,num));
    else if (num <= tempRoot->val)
        tempRoot->left = put(num, tempRoot->left);
    else if (num > tempRoot->val)
        tempRoot->right = put(num, tempRoot->right);
    return tempRoot;
}

template <class T>
int BST<T>::getHeight(TreeNode<T> *node){
    if (!node)  
        node = root;

    int leftCount = 0, righCount = 0;
    if (node->left)
        leftCount += getHeight(node->left) + 1;
    
    if (node->right)
        righCount += getHeight(node->right) + 1;

    return max(leftCount, righCount);
}

template <class T>
TreeNode<T>* BST<T>::createBST(vector<T> values, TreeNode<T> *tempRoot){
    int size = values.size();
    
    if (size == 0)
        return nullptr;

    if (size == 1){
        TreeNode<T> *temp = new TreeNode<T> (values[0]);
        temp->right = nullptr;
        temp->left = nullptr;
        if (tempRoot != nullptr){
            if (values[0] <= tempRoot->val)
                tempRoot->left = temp;
            else
                tempRoot->right = temp;
        }
        return temp;
    }
    
    int mid = size / 2;
    TreeNode<T> *node = new TreeNode<T> (values[mid]);

    node->left = createBST(vector<T>(values.begin(), values.begin() + mid), node);
    node->right = createBST(vector<T>(values.begin() + mid + 1, values.end()), node);

    return node;
}

template <class T>
void BST<T>::insert(vector<T> values){
    for(int i = 0; i < values.size(); i++)
        insertNode(values[i], root);
}

template <class T>
void BST<T>::insert(T value){
    insertNode(value, root);
}

template <class T>
bool BST<T>::has(T num, TreeNode<T> *tempRoot){
    if (tempRoot == nullptr)
        tempRoot = root;
    if (num == tempRoot->val)
        return true;
    else if (num < tempRoot->val && tempRoot->left != nullptr)
        return has(num, tempRoot->left);
    else if (num > tempRoot->val && tempRoot->right != nullptr)
        return has(num, tempRoot->right);
    return false;
}

template <class T>
TreeNode<T>* BST<T>::removeNode(T val, TreeNode<T> *temp){
    if (!temp)
        return temp;

    if (temp->val == val){
        if (!temp->left && !temp->right){
            delete(temp);
            return NULL;
        }
        else{
            if(temp->left){
                T maximum = getMaximum(temp->left);
                temp->val = maximum;
                temp->left = removeNode(maximum, temp->left);
            }else if(temp->right){
                T minimum = getMinimum(temp->right);
                temp->val = minimum;
                temp->right = removeNode(minimum, temp->right);
            }
        }
    }

    if (temp->val < val)
        temp->right = removeNode(val, temp->right);

    if (temp-> val > val)
        temp->left = removeNode(val, temp->left);

    return temp;
}

template <class T>
T BST<T>::getMaximum(TreeNode<T> *temp){
    if (!temp)  temp = root;
    while(temp->right){
        temp = temp->right;
    }
    return temp->val;
}

template <class T>
T BST<T>::getMinimum(TreeNode<T> *temp){
    if (!temp)  temp = root;
    while(temp->left){
        temp = temp->left;
    }
    return temp->val;
}

template <class T>
void BST<T>::display(int choice){
    switch(choice){
        case 1: 
            preTraversal(root);
            break;
        case 2: 
            inorderTraversal(root);
            break;
        case 3: 
            postTraversal(root);
            break;
        default:
            inorderTraversal(root);
            break;
    }
    cout << endl;
}