#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct TreeNode{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class BST{
    int height;

 public:
    struct TreeNode *root;
    BST(){
        root = new struct TreeNode();
        height = 0;
    }

    BST(int value){
        root = new struct TreeNode(value); 
        height = 0;
    }

    BST(int value, TreeNode *left, TreeNode *right){
        root = new struct TreeNode(value, left, right);
        height = getHeight(root);
    }

    BST(vector<int> nums){
        root = createBST(nums);
    }

    int getHeight(TreeNode *node){
        int leftCount = 0, righCount = 0;
        if (node->left)
            leftCount += getHeight(node->left) + 1;
        
        if (node->right)
            righCount += getHeight(node->right) + 1;

        return max(leftCount, righCount);
    }

    struct TreeNode* createBST(vector<int> nums, TreeNode* tempRoot = nullptr){
        int size = nums.size();
        //display(nums);
        
        if (size == 0)
            return nullptr;

        if (size == 1){
            struct TreeNode* temp = new struct TreeNode(nums[0]);
            temp->right = nullptr;
            temp->left = nullptr;
            if (nums[0] < tempRoot->val)
                tempRoot->left = temp;
            else
                tempRoot->right = temp;

            //cout << temp->val << endl;
            return temp;
        }
        
        int mid = size / 2;
        struct TreeNode* node = new struct TreeNode(nums[mid]);

        //cout << node->val << endl;
        node->left = createBST(vector<int>(nums.begin(), nums.begin() + mid), node);
        node->right = createBST(vector<int>(nums.begin() + mid + 1, nums.end()), node);

        return node;
    }

    void display(vector<int> nums){
        cout << "Nums: ";
        for (int i = 0; i < nums.size(); i++){
            cout << nums[i] << " ";
        }
        cout << endl;
    }

    void inorderTraversal(TreeNode* tempRoot){
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

    vector<int> nums = {1, 2, 3, 4, 5, 6, 7};
    BST bst(nums);
    bst.displayBST();
    cout << "Height: " << bst.getHeight(bst.root) << endl;
    
    return 0;
}



 