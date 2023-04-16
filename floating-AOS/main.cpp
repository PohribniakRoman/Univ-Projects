#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<int> decToBinary(int n){
    vector<int> number;
    for (int i = 0;n > 0;i++) {
        number.push_back(n % 2);
        n /= 2;
    }
    return number;
}

vector<int> fractToBinary(double n,int len){
    vector<int> res;
    for (int i = 0; n != 0; ++i) {
        if(i == len)return res;
        n *= 2;
        res.push_back(floor(n));
        n -= floor(n);
    }
    while(res.size() != 12){
        res.push_back(0);
    }
    return res;
}

class Float {
private:
    const int explicitLength = 8;
    const int significantLength = 12;
    void visualize(vector<int> arr){
        for (int i = 0; i < arr.size(); ++i) {
            cout << arr[i];
        }
    }
    vector<int> reverse(vector<int> arr,int len){
        vector<int> res;
        while (len != arr.size()){
            arr.push_back(0);
        }
        for (int i = 0; i < arr.size(); ++i) {
            res.push_back(arr[arr.size()-i-1]);
        }
        return res;
    }
public:
    void toFloat(double num){
        if(num != 0) {
            cout << ((num < 0) ? "1" : "0") << "|";
            num = abs(num);
            vector<int> binary = decToBinary(num);
            vector<int> floatExplicit = reverse(decToBinary(floor(log(num) / log(2.)) + 127), explicitLength);
            double res = num >= 1 ?
                         (num - pow(2, binary.size() - 1)) / pow(2, binary.size() - 1) :
                         abs(num - pow(2, floor(log(num) / log(2.))));
            vector<int> significant = fractToBinary(res, significantLength);

            this->visualize(floatExplicit);
            if(res == 0){
                cout << "|0|";
            }else{
                cout << "|1|";
            }
            this->visualize(significant);
        }else{
            cout << "0|00000000|0|000000000000\n";
        }
    }
};


int main(){
    cout << "s - sign ; e - exponents bits ; i - implicit bit ; m - mantissa bits\n";
    cout << "1\t:   s|hhhhhhhh|i|mmmmmmmmmmmm - What number is it\n";
    cout << "2\t :  0|11111111|1|000000000000 - Positive infinity\n";
    cout << "3\t :  1|11111111|1|000000000000 - Negative infinity\n";
    cout << "4\t :  0|00000000|0|000000000000 - Zero\n";
    cout << "5\t :  0|00000001|1|000000000000 - Minimal absolute value\n";
    cout << "6\t :  0|11111110|1|111111111111 - Max positive \n";
    cout << "7\t :  1|11111110|1|111111111111 - Min negative \n";
    cout << "8\t :  0|01111111|1|000000000000 - One \n";
    cout << "9\t :  1|00000000|1|111111111111 - Not normalized\n";
    cout << "10\t :  0|11111111|1|100111100111 - Not a number \n";
    cout << "Please, enter your x value: ";
    Float FloatConstructor;
    double x;
    cin >>x;
    cout << "Float number is: ";
    FloatConstructor.toFloat(x);
  return 0;
}