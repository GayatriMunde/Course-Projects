#include <bits/stdc++.h>

using namespace std;

template <typename T>
int getIndex(int id, vector<T> temp){
    for (int i = 0; i < temp.size(); i++){
        if (temp[i].getId() == id){
            return i;
        }
    }
    cout << "Invalid id!" << endl;
    return -1;
}