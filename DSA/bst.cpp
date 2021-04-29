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

template <typename T>
class BST{
    int height;

 public:
    struct TreeNode<T> *root;
    BST(){
        root = new struct TreeNode<T> ();
        height = 0;
    }

    BST(T value){
        root = new struct TreeNode<T> (value); 
        height = 0;
    }

    BST(T value, TreeNode<T> *left, TreeNode<T> *right){
        root = new struct TreeNode<T> (value, left, right);
        height = getHeight(root);
    }

    BST(vector<T> values){
        root = createBST(values);
    }

    T getHeight(TreeNode<T> *node){
        int leftCount = 0, righCount = 0;
        if (node->left)
            leftCount += getHeight(node->left) + 1;
        
        if (node->right)
            righCount += getHeight(node->right) + 1;

        return max(leftCount, righCount);
    }

    struct TreeNode<T> *createBST(vector<T> values, TreeNode<T> *tempRoot = nullptr){
        int size = values.size();
        //display(values);
        
        if (size == 0)
            return nullptr;

        if (size == 1){
            struct TreeNode<T> *temp = new struct TreeNode<T> (values[0]);
            temp->right = nullptr;
            temp->left = nullptr;
            if (tempRoot != nullptr){
                if (values[0] < tempRoot->val)
                    tempRoot->left = temp;
                else
                    tempRoot->right = temp;
            }
            //cout << temp->val << endl;
            return temp;
        }
        
        int mid = size / 2;
        struct TreeNode<T> *node = new struct TreeNode<T> (values[mid]);

        //cout << node->val << endl;
        node->left = createBST(vector<T>(values.begin(), values.begin() + mid), node);
        node->right = createBST(vector<T>(values.begin() + mid + 1, values.end()), node);

        return node;
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

    void insert(vector<T> values){
        for(int i = 0; i < values.size(); i++)
            put(values[i], root);
    }

    bool Search(T num, TreeNode<T> *tempRoot = nullptr){
        if (tempRoot == nullptr)
            tempRoot = root;
        if (num == tempRoot->val)
            return true;
        else if (num < tempRoot->val && tempRoot->left != nullptr)
            return Search(num, tempRoot->left);
        else if (num > tempRoot->val && tempRoot->right != nullptr)
            return Search(num, tempRoot->right);
        return false;
    }

    void display(vector<T> values){
        cout << "Vector: ";
        for (int i = 0; i < values.size(); i++){
            cout << values[i] << " ";
        }
        cout << endl;
    }

    void inorderTraversal(TreeNode<T> *tempRoot){
        if (!tempRoot)  return;
        if(tempRoot){
            inorderTraversal(tempRoot->left);
            cout << tempRoot->val << " ";
            inorderTraversal(tempRoot->right);
        }
    }

    void displayBST(){
        inorderTraversal(root);
        cout << endl;
    }

};

int main(){

    vector<int> values = {1, 2, 3, 4, 5, 6, 7};
    BST<int> bst(values);
    bst.displayBST();
    vector<int> a = {8, 0, 10};
    bst.insert(a);
    bst.displayBST();
    cout << "Height: " << bst.getHeight(bst.root) << endl;

    cout << endl;

    vector<float> nums = {1.1, 2.3, 6.7, 9.0, 11.9};
    BST<float> bst3(nums);
    bst3.displayBST();
    vector<float> addOn= {3.2, 5.9};
    bst3.insert(addOn);
    bst3.displayBST();
    cout << "Height: " << bst3.getHeight(bst3.root) << endl;

    
    return 0;
}



 