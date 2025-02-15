/////////////////////////////////////////////////////////////////
//              Name : V.Rana Bharath                          // 
//              Roll no : 2301CS39                             //
///////////////////////////////////////////////////////////////// 
#include<bits/stdc++.h>
using namespace std;
const int N = 200000;

int A = 0;
int B = 0;
int PC = 0;
int SP = 0;
int MEMORY_SIZE = N;
vector<int> memory(MEMORY_SIZE);
vector<string> MachineCodes;
vector<string> DataContent;

string Update(const string &str) {
    size_t start = str.find_first_not_of(" \t\n\r\f\v");
    if (start == string::npos) {
        return ""; // Return an empty string if no non-space character is found
    }
    size_t end = str.find_last_not_of(" \t\n\r\f\v");
    return str.substr(start, end - start + 1); // Return trimmed substring
}

int hextoint(const string &s) {
    auto hexLength = s.size();
    
    unsigned int result = stoul(s, nullptr, 16);
    
    if (hexLength <= 6) {
        if (result & 0x800000) {  // Check if the 24th bit is set (sign bit)
            result -= 0x1000000;  // Adjust for two's complement 24-bit negative
        }
    } else if (hexLength <= 8) {
        if (result & 0x80000000) {  // Check if the 32nd bit is set (sign bit)
            result -= 0x100000000;  // Adjust for two's complement 32-bit negative
        }
    }
    
    return static_cast<int>(result);
}

vector<string> splitLine(string& line) {
    vector<string> result;
    stringstream ss(line);
    string temp;
    while(ss >> temp){
        result.push_back(temp);
    }
    return result;
}

string ToHEX(int n) {
    if(n == 0){
        return ("0x00000000");
    }
    unsigned int num = static_cast<unsigned int>(n);
    string ans = "";
    char temp[] = "0123456789ABCDEF";

    while (num > 0) {
        int b = num % 16;
        ans = temp[b] + ans;
        num /= 16;
    }

    while (ans.size() < 8) {
        ans = '0' + ans;
    }

    ans = "0x" + ans;
    return ans;
}

void ldc(int value){
    B = A;
    A = value;
}

void adc(int value){
    A = A + value;
}

void ldl(int offset){
    B = A;
    if((SP+offset < N) && (SP+offset >= 0)){
        A = memory[SP+offset];
    } else {
        cout << "Segmentation fault : Accessing elements that are out of bounds" << endl;
    }
}

void stl(int offset){
    if((SP+offset < N) && (SP+offset >= 0)){
        memory[SP+offset] = A;
    } else {
        cout << "Segmentation fault : Accessing elements that are out of bounds" << endl;
    }
    A = B;
}

void ldnl(int offset){
    if((A+offset < N) && (A+offset >= 0)){
        A = memory[A+offset];
    } else {
        cout << "Segmentation fault : Accessing elements that are out of bounds" << endl;
    }
}

void stnl(int offset){
    if((A+offset < N) && (A+offset >= 0)){
        memory[A+offset] = B;
    } else {
        cout << "Segmentation fault : Accessing elements that are out of bounds" << endl;
    }
}

void add(){
    A = B + A;
}

void sub(){
    A = B - A;
}

void shl(){
    A = B << A;
}

void shr(){
    A = B >> A;
}

void adj(int value){
    SP = SP + value;
}

void a2sp(){
    SP = A;
    A = B;
}

void sp2a(){
    B = A;
    A = SP;
}

void call(int offset){
    B = A;
    A = PC;
    PC = PC + offset;
}

void Return(){
    PC = A;
    A = B;
}

void brz(int offset){
    if(A == 0){
        PC += offset;
    }
}

void brlz(int offset){
    if(A < 0){
        PC += offset;
    }
}

void br(int offset){
    PC += offset;
}

void LoadContent(vector<string> &a){
    for(int i=0;i<a.size();i++){
        int temp = hextoint(a[i]);
        //cout << temp << endl;
        memory[SP] = temp;
        SP+=1;
    }
    PC+=1;
}

void Execute(){
    bool test = true;
    while(test && PC <(MachineCodes.size())){
        string temp = MachineCodes[PC];
        string temp1 = temp.substr(6,2);
        int tempOPCode = hextoint(temp1);
        string temp2 = temp.substr(0,6);
        int tempOperand = hextoint(temp2);
        switch(tempOPCode){
            case 0x00:
                ldc(tempOperand);
                break;
            case 0x01:
                adc(tempOperand);
                break;
            case 0x02:
                ldl(tempOperand);
                test = ((SP+tempOperand < N) && (SP+tempOperand >= 0));
                break;
            case 0x03:
                stl(tempOperand);
                test = ((SP+tempOperand < N) && (SP+tempOperand >= 0));
                break;
            case 0x04:
                ldnl(tempOperand);
                test = ((A+tempOperand < N) && (A+tempOperand >= 0));
                break;
            case 0x05:
                stnl(tempOperand);
                test = ((A+tempOperand < N) && (A+tempOperand >= 0));
                break;
            case 0x06:
                add();
                break;
            case 0x07:
                sub();
                break;
            case 0x08:
                shl();
                break;
            case 0x09:
                shr();
                break;
            case 0x0A:
                adj(tempOperand);
                break;
            case 0x0B:
                a2sp();
                break;
            case 0x0C:
                sp2a();
                break;
            case 0x0D:
                call(tempOperand);
                break;
            case 0x0E:
                Return();
                break;
            case 0x0F:
                brz(tempOperand);
                break;
            case 0x10:
                brlz(tempOperand);
                break;
            case 0x11:
                br(tempOperand);
                break;
            case 0x12:
                test = false;
                break;
        }
        //cout << A << " " << B << " " << SP << " " << PC << endl;
        if(test){
            PC++;
        }
    }
}

void ShowRegisters(){
    cout << "Register A(Accumulator) : " << A << endl;
    cout << "Register B : " << B << endl;
    cout << "Stack Pointer SP : " << SP << endl;
    cout << "Program Counter PC : " << PC << endl;
}

void ShowMemory(){
    for(int i=0;i<100;i+=4){
        string s = ToHEX(i);
        cout << s << " ";
        for(int j=0;j<=3;j++){
            string temp = ToHEX(memory[i+j]);
            cout << temp.substr(2,8) << " ";
        } cout << endl;
    }
}

void Clear(){
    A = 0;
    B = 0;
    SP = 0;
    PC = 0;
    for(int i=0;i<N;i++){
        memory[i] = 0;
    }
}
int main(int argc , char* argv[]){

    FILE *file = fopen(argv[1],"r");
    if(!file){
        cout << "Error Opening the File" << endl;
        return 1;
    }

    int MAX_LINE_LENGTH = 300;
    char line[MAX_LINE_LENGTH];
    while(fgets(line, MAX_LINE_LENGTH, file)){
        string temp = Update(line);
        MachineCodes.push_back(temp);
    }
    fclose(file);
    DataContent = splitLine(MachineCodes[0]);
    LoadContent(DataContent);
    
    bool temptr = true;
    while(temptr){
        cout << "Choose the following functions by selecting number which is mentioned beside the function" << endl;
        cout << "1.Execute " << endl;
        cout << "2.Show Registers " << endl;
        cout << "3.Show Memory " << endl;
        cout << "4.Clear " << endl;
        cout << "5.Exit " << endl;

        int x;
        cin >> x;
        if(x==1){
            Execute();
        } else if(x==2){
            ShowRegisters();
        } else if(x==3){
            ShowMemory();
        } else if(x==4){
            Clear();
        } else if(x==5){
            temptr = false;
        } 
    }
    

    return 0;
}
