#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main(){
    vector<int> uniq = {1,2,3,4,5};
    vector<int> append = {1,3,-2,1231313,5,6,12,123};
    for (auto it = append.begin(); it != append.end(); it++) {
        if(find(uniq.begin(),uniq.end(),*it) == uniq.end()){
            uniq.insert(uniq.end(),*it);
        }
    }
    for (int i = 0; i < uniq.size(); ++i) {
        cout << uniq[i] << "\t";
    }
    return 0;
};