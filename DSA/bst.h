#ifndef BST_H
#define BST_H
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template <typename T>
class BST{
    struct TreeNode{
        T val;
        TreeNode<T> *left;
        TreeNode<T> *right;
        TreeNode<T> () : val(0), left(nullptr), right(nullptr) {}
        TreeNode<T> (T x) : val(x), left(nullptr), right(nullptr) {}
        TreeNode<T> (T x, TreeNode<T> *left, TreeNode<T> *right) : val(x), left(left), right(right) {}
    };

    int height;
    struct TreeNode<T> *root;

    void inorderTraversal(TreeNode<T> *tempRoot){
        if (!tempRoot)  return;
        if(tempRoot){
            inorderTraversal(tempRoot->left);
            cout << tempRoot->val << " ";
            inorderTraversal(tempRoot->right);
        }
    }

    void preTraversal(TreeNode<T> *tempRoot){
        if (!tempRoot)  return;
        if(tempRoot){
            cout << tempRoot->val << " ";
            inorderTraversal(tempRoot->left);
            inorderTraversal(tempRoot->right);
        }
    }

    void postTraversal(TreeNode<T> *tempRoot){
        if (!tempRoot)  return;
        if(tempRoot){
            inorderTraversal(tempRoot->left);
            inorderTraversal(tempRoot->right);
            cout << tempRoot->val << " ";
        }
    }

    struct TreeNode<T> *put(T num, TreeNode<T> *tempRoot){
        if (tempRoot == nullptr)
            tempRoot = createBST(vector<T>(1,num));
        else if (num <= tempRoot->val)
            tempRoot->left = put(num, tempRoot->left);
        else if (num > tempRoot->val)
            tempRoot->right = put(num, tempRoot->right);
        return tempRoot;
    }

 public:
    BST(){
        root = new struct TreeNode<T> ();
        height = 0;
    }

    BST(T value){
        root = new struct TreeNode<T> (value); 
        height = 0;
    }

    BST(T value, TreeNode<T> *left = NULL, TreeNode<T> *right = NULL){
        root = new struct TreeNode<T> (value, left, right);
        height = getHeight(root);
    }

    BST(vector<T> values){
        sort(values.begin(), values.end());
        root = createBST(values);
    }

    int getHeight(TreeNode<T> *node = NULL){
        if (!node)  
            node = root;

        int leftCount = 0, righCount = 0;
        if (node->left)
            leftCount += getHeight(node->left) + 1;
        
        if (node->right)
            righCount += getHeight(node->right) + 1;

        return max(leftCount, righCount);
    }

    struct TreeNode<T> *createBST(vector<T> values, TreeNode<T> *tempRoot = nullptr){
        int size = values.size();
        
        if (size == 0)
            return nullptr;

        if (size == 1){
            struct TreeNode<T> *temp = new struct TreeNode<T> (values[0]);
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
        struct TreeNode<T> *node = new struct TreeNode<T> (values[mid]);

        node->left = createBST(vector<T>(values.begin(), values.begin() + mid), node);
        node->right = createBST(vector<T>(values.begin() + mid + 1, values.end()), node);

        return node;
    }

    void insert(vector<T> values){
        for(int i = 0; i < values.size(); i++)
            put(values[i], root);
    }

    void insert(T value){
        put(value, root);
    }

    bool has(T num, TreeNode<T> *tempRoot = nullptr){
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

    struct TreeNode<T> *helper(int val, TreeNode<T> *temp){
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
                    temp->left = helper(maximum, temp->left);
                }else if(temp->right){
                    T minimum = getMinimum(temp->right);
                    temp->val = minimum;
                    temp->right = helper(minimum, temp->right);
                }
            }
        }

        if (temp->val < val)
            temp->right = helper(val, temp->right);

        if (temp-> val > val)
            temp->left = helper(val, temp->left);

        return temp;
    }

    TreeNode<T> *deleteNode(T val){
        return helper(val, root);
    }

    T getMaximum(TreeNode<T> *temp = NULL){
        if (!temp)  temp = root;
        while(temp->right){
            temp = temp->right;
        }
        return temp->val;
    }

    T getMinimum(TreeNode<T> *temp = NULL){
        if (!temp)  temp = root;
        while(temp->left){
            temp = temp->left;
        }
        return temp->val;
    }

    void display(int choice = 2){
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

};
#endif