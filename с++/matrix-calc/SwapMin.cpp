#include <iostream>

using namespace std;

void swap_min(int *arr[], unsigned rows, unsigned cols){
    int min = arr[0][0];
    int lowestNumRow = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if(min > arr[i][j]){
                min = arr[i][j];
                lowestNumRow = i;
            }
        }
    }
    swap(arr[0],arr[lowestNumRow]);
}

void visualize(int *arr[], unsigned rows, unsigned cols){
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << arr[i][j] << "\t";
        }
        cout << "|" << endl;
    }
}


int main(){
    const int rows = 5;
    const int cols = 4;
    int** arr = new int*[rows];
    cout << "Enter data:\n";
    for (int i = 0; i < 5; ++i) {
        arr[i] = new int[cols];
        for (int j = 0; j < 4; ++j) {
            cin >> arr[i][j];
        }
    }
    cout << "Before refactor: \n";
    visualize(arr, rows, cols);
    swap_min(arr, rows, cols);
    cout << "After refactor: \n";
    visualize(arr, rows, cols);
    delete [] arr;
    return 0;
}

//input data
//10
//22
//13
//15
//120
//130
//150
//160
//1
//2
//3
//5
//14
//3000
//-12
//16
//66
//73
//84
//92