#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

vector<int> CreateRegister(){
    vector<int> Register;
    for (int i = 0; i < 24; ++i) {
        Register.push_back(0);
    }
    return Register;
}

vector<int> wordToBinary(string str,bool capitalize){
    vector<int> number;
    int acc = 0;
    for (char i : str) {
        if(capitalize){
            int asciiIndex = int(i);
            if(asciiIndex > 96 && asciiIndex < 123){
                acc += int(i)-32;
            }else{
                acc += int(i);
            }
        }else{
            acc += int(i);
        }
    }
    while (acc > 0) {
        number.push_back(acc % 2);
        acc /= 2;
    }
    while (number.size() != 24) {
        number.push_back(0);
    }

    for (int i = 0; i < number.size()/2; ++i) {
        swap(number[i],number[number.size()-i-1]);
    }


    return number;
}

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
    cout<< "\n";
}

int main() {
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

    int PROCESS = 0;
    vector<vector<int>> Registers;
    for (int i = 0; i < 4; ++i) {
        Registers.push_back(CreateRegister());
    }
    vector<string> Data;
    for (int i = 0; i < 4; ++i) {
        Data.push_back("template");
    }

    while (PROCESS*3 < CommandList.size()) {
        int TICK = 0;

        string command = CommandList[PROCESS*3]+" "+CommandList[(PROCESS*3)+1]+" "+CommandList[(PROCESS*3)+2];
        string cast = CommandList[PROCESS*3];
        if(cast == "mov"){
            vector<int> currentResult = wordToBinary(CommandList[(PROCESS*3)+2],false);
            TICK++;
            visualize(command,cast,Registers,TICK,PROCESS+1,currentResult);
            TICK++;
            int saveIndex = int(CommandList[(PROCESS*3)+1][1])-49;
            Registers[saveIndex] = currentResult;
            Data[saveIndex] = CommandList[(PROCESS*3)+2];
            visualize(command,cast,Registers,TICK,PROCESS+1,currentResult);
        }else if(cast == "save"){
            TICK++;
            visualize(command,cast,Registers,TICK,PROCESS+1,CreateRegister());
            TICK++;
            int saveIndex = int(CommandList[(PROCESS*3)+1][1])-49;
            int dataIndex = int(CommandList[(PROCESS*3)+2][1])-49;
            Registers[saveIndex] = Registers[dataIndex];
            visualize(command,cast,Registers,TICK,PROCESS+1,CreateRegister());
        }else if(cast == "cap"){
            TICK++;
            visualize(command,cast,Registers,TICK,PROCESS+1,CreateRegister());
            TICK++;
            if(int(CommandList[(PROCESS*3)+2][0])-48 == 1){
                int saveIndex = int(CommandList[(PROCESS*3)+1][1])-49;
                Registers[saveIndex] = wordToBinary(Data[saveIndex],true);
                visualize(command,cast,Registers,TICK,PROCESS+1, Registers[saveIndex]);
            }else{
                visualize(command,cast,Registers,TICK,PROCESS+1,CreateRegister());
            }
        }
        PROCESS++;
    }
    return 0;
}
