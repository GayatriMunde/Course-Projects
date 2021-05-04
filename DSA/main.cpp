#include <iostream>
#include "bst.h"

using namespace std; 

int main(){
    vector<int> values = {1, 2, 3, 4, 6, 7, 8};
    BST<int> bst(values);
    bst.display();
    bst.deleteNode(4);
    bst.display();

    bst.deleteNode(3);
    bst.display();

    bst.deleteNode(2);
    bst.display();

    bst.deleteNode(10);
    bst.display();




    /*vector<int> a = {8, 0, 10};
    bst.insert(a);
    bst.display(2);
    cout << "Height: " << bst.getHeight() << endl;
    cout << "Minimum: " << bst.getMinimum() << endl;
    cout << "Maximum: " << bst.getMaximum() << endl;

    cout << endl;


    vector<char> vals = {'a', 'c', 'h', 'j', 'k', 'l', 'o'};
    BST<char> bst2(vals);
    bst2.display();
    vector<char> toInsert = {'b', 'z', 'm'};
    bst2.insert(toInsert);
    bst2.display(3);
    cout << "Height: " << bst2.getHeight() << endl;
    cout << "Minimum: " << bst2.getMinimum() << endl;
    cout << "Maximum: " << bst2.getMaximum() << endl;

    cout << endl;

    vector<float> nums = {1.1, 2.3, 6.7, 9.0, 11.9};
    BST<float> bst3(nums);
    bst3.display();
    vector<float> addOn= {3.2, 5.9};
    bst3.insert(addOn);
    bst3.display(1);
    cout << "Height: " << bst3.getHeight() << endl;
    cout << "Minimum: " << bst3.getMinimum() << endl;
    cout << "Maximum: " << bst3.getMaximum() << endl;
*/
    return 0;
}