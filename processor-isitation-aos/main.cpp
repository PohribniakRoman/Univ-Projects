#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

// Create empty register;

vector<int> CreateRegister(){
    vector<int> Register;
    for (int i = 0; i < 16; ++i) {
        Register.push_back(0);
    }
    return Register;
}

// Transform data to binary;

vector<int> negativeNumberToBinary(int acc){
    vector<int> number;
    while (acc > 0) {
        number.push_back(acc % 2);
        acc /= 2;
    }
    while (number.size() != 16) {
        number.push_back(0);
    }
    for (int i = 0; i < number.size()/2; ++i) {
        swap(number[i],number[number.size()-i-1]);
    }

    for (int j = 0; j < number.size(); ++j) {
        if(number[j] == 0){number[j]=1;}else{number[j] = 0;};
    }

    int i = number.size()-1;

    while (i != 0){
        if(number[i] == 0){
            number[i] = 1;
            break;
        }else{
            number[i] = 0;
        }
        i--;
    }
    return number;
}

// Visualize data script;

void visualize(const string& command,const string& cast,vector<vector<int>> Registers,int TICK,int PROCESS,vector<int> result){
    cout<<"Command - "<< command << "\nR1  =  ";
    for (int i = 0;i < Registers[0].size();i++) {
        cout << Registers[0][i] <<" ";
    }
    cout<<"\t Ins = " << cast <<" | ";
    for (int i = 0;i<result.size();i++) {
        cout << result[i] <<" ";
    }
    cout<< "\nR2  =  ";
    for (int i = 0;i<Registers[1].size();i++) {
        cout << Registers[1][i] <<" ";
    }
    cout<< "\t PC = "<<PROCESS <<  "\nR3  =  ";
    for (int i = 0;i<Registers[2].size();i++) {
        cout << Registers[2][i] <<" ";
    }
    cout<< "\t TC = "<<TICK << "\nR4  =  ";
    for (int i = 0;i<Registers[3].size();i++) {
        cout << Registers[3][i] <<" ";
    }
    cout<< "\t PS = "<<Registers[0][0]<<"\n";
}

int main() {
    // Reading file data;
    ifstream file ("index.txt");
    vector<string> CommandList;
    char ch;
    int s = 0;
    while (file.get(ch)){
        if(ch == ' ' || ch == '\n'){
            s++;
        }else{
            if(CommandList.size() > s){
                CommandList[s].push_back(ch);
            } else{
                string newElement = "";
                newElement.push_back(ch);
                CommandList.push_back(newElement);
            }
        }
    }

    // Creating Registers & initialize it

    const int REGISTERS_COUNT = 4;
    int PROCESS = 0;
    vector<vector<int>> Registers;
    for (int i = 0; i < REGISTERS_COUNT; ++i) {
        Registers.push_back(CreateRegister());
    }
    vector<int> Data;
    for (int i = 0; i < REGISTERS_COUNT; ++i) {
        Data.push_back(0);
    }

    // Processing commands

    while (PROCESS*3 < CommandList.size()) {
        int TICK = 0;
        string command = CommandList[PROCESS*3]+" "+CommandList[(PROCESS*3)+1]+" "+CommandList[(PROCESS*3)+2];
        string cast = CommandList[PROCESS*3];
        // command list
        if(cast == "mov"){
            // converting word to binary
            vector<int> currentResult = negativeNumberToBinary(abs(stoi(CommandList[(PROCESS*3)+2])));
            TICK++;
            visualize(command,cast,Registers,TICK,PROCESS+1,currentResult);
            string separator;
            cin>>separator;
            int saveIndex = int(CommandList[(PROCESS*3)+1][1])-49;
            Registers[saveIndex] = currentResult;
            Data[saveIndex] = abs(stoi(CommandList[(PROCESS*3)+2]));
            TICK++;
            visualize(command,cast,Registers,TICK,PROCESS+1,currentResult);
        }else if(cast == "save"){
            // get register index & save data to it
            int saveIndex = int(CommandList[(PROCESS*3)+1][1])-49;
            int dataIndex = int(CommandList[(PROCESS*3)+2][1])-49;
            Registers[saveIndex] = Registers[dataIndex];
            TICK++;
            visualize(command,cast,Registers,TICK,PROCESS+1,Registers[dataIndex]);
            string separator;
            cin>>separator;
            TICK++;
            visualize(command,cast,Registers,TICK,PROCESS+1,Registers[dataIndex]);
        }else if(cast == "add"){
            TICK++;
            int saveIndex = int(CommandList[(PROCESS*3)+1][1])-49;
            int num = Data[saveIndex] + abs(stoi(CommandList[(PROCESS*3)+2]));
            Registers[saveIndex] = negativeNumberToBinary(num);
            visualize(command,cast,Registers,TICK,PROCESS+1,Registers[saveIndex]);
            string separator;
            cin>>separator;
            TICK++;
            visualize(command,cast,Registers,TICK,PROCESS+1, Registers[saveIndex]);
        }else{
            cout<<"Command - "<< cast <<"is Unknown";
        }
        cout<<"______________________________________________________________\n";
        string separator;
        cin>>separator;
        PROCESS++;
    }
    return 0;
}
