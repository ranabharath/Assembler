/////////////////////////////////////////////////////////////////
//              Name : V.Rana Bharath                          // 
//              Roll no : 2301CS39                             //
///////////////////////////////////////////////////////////////// 
#include<bits/stdc++.h>
using namespace std;

typedef struct{
    string LabelName;
    int Address;
    int LineNumber;
} Label;

typedef struct{
    string mnemonic;
    vector<string> operands;
    int LineNumber;
} Instructions;

string Update(const string &str) {
    size_t start = str.find_first_not_of(" \t\n\r\f\v");
    if (start == string::npos) {
        return ""; // Return an empty string if no non-space character is found
    }
    size_t end = str.find_last_not_of(" \t\n\r\f\v");
    return str.substr(start, end - start + 1); // Return trimmed substring
}

Instructions SplitInstruction(string s, int linenumber) {
    Instructions instruction;
    instruction.LineNumber = linenumber;

    stringstream ss(s);
    ss >> instruction.mnemonic;  // Extract the first word as the mnemonic

    string operand;
    while (ss >> operand) {      // Extract remaining words as operands
        instruction.operands.push_back(operand);
    }

    return instruction;
}

int safeStoi(const string& str) {
    try {
        if (str.size() > 2 && (str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))) {
            return stoi(str, nullptr, 16); // Convert hexadecimal string
        } else if (str.size() > 1 && str[0] == '0' && isdigit(str[1])) {
            return stoi(str, nullptr, 8); // Convert octal string
        }
        return stoi(str); // Default decimal conversion
    } catch (const invalid_argument&) {
        cerr << "Invalid argument: " << str << " is not a valid integer." << endl;
        return 0;
    } catch (const out_of_range&) {
        cerr << "Out of range: " << str << " is too large to fit in an int." << endl;
        return 0;
    }
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

int hexToInt(string& hexStr) {
    size_t start = (hexStr.size() > 2 && hexStr[0] == '0' && (hexStr[1] == 'x' || hexStr[1] == 'X')) ? 2 : 0;
    return stoi(hexStr.substr(start), nullptr, 16); // Convert hex to int
}

vector<pair<int,string>> Errors;
map<string, pair<string, int>> OP_Table = {
    // Type 0: No operand
    {"add", {"06", 0}}, {"sub", {"07", 0}}, {"shl", {"08", 0}}, {"shr", {"09", 0}},
    {"a2sp", {"0B", 0}}, {"sp2a", {"0C", 0}}, {"return", {"0E", 0}}, {"HALT", {"12", 0}},

    // Type 1: Argument is given
    {"data", {"", 1}}, {"ldc", {"00", 1}}, {"adc", {"01", 1}}, {"set", {"", 1}}, {"adj", {"0A", 1}},

    // Type 2: Offset is given
    {"ldl", {"02", 2}}, {"stl", {"03", 2}}, {"ldnl", {"04", 2}}, {"stnl", {"05", 2}},
    {"call", {"0D", 2}}, {"brz", {"0F", 2}}, {"brlz", {"10", 2}}, {"br", {"11", 2}}
};

map<string,int> MapOfMnemonics = {
    {"add", 1}, {"sub", 1}, {"shl", 1}, {"shr", 1},
    {"a2sp", 1}, {"sp2a", 1}, {"return", 1}, {"HALT", 1},
    {"data", 1}, {"ldc", 1}, {"adc", 1}, {"set", 1}, {"adj", 1},
    {"ldl", 1}, {"stl", 1}, {"ldnl", 1}, {"stnl", 1},
    {"call", 1}, {"brz", 1}, {"brlz", 1}, {"br", 1}
};

vector<string> FileContent;
vector<string> DataContent;
map<string,int> Map_of_DataContent;
map<string,string> Map_of_Machine_code;
vector<Label> label;
vector<Instructions> instruction;
map<string,string> Map_of_Labels;
map<string,string> Map_of_Instruction;

void CheckCorrectMnemonic(vector<Instructions> &b){
    for(int i=0; i < b.size(); i++){
        string s = (b[i].mnemonic);
        if(MapOfMnemonics[s] != 1){
            string t = "Error at line " + to_string(b[i].LineNumber) + " of type Incorrect mnemonic";
            Errors.push_back({b[i].LineNumber,t});
        }
    }
}

void CheckNoofOperands(vector<Instructions> &b){
    for(int i=0; i < b.size(); i++){
        if(OP_Table[b[i].mnemonic].second == 0 && b[i].operands.size() != 0){
            string t = "Error at line " + to_string(b[i].LineNumber) + " of type Incorrect number of operands";
            Errors.push_back({b[i].LineNumber,t});
        }

        if(OP_Table[b[i].mnemonic].second == 1 && b[i].operands.size() != 1){
            string t = "Error at line " + to_string(b[i].LineNumber) + " of type Incorrect number of operands";
            Errors.push_back({b[i].LineNumber,t});            
        }

        if(OP_Table[b[i].mnemonic].second == 2 && b[i].operands.size() != 1){
            string t = "Error at line " + to_string(b[i].LineNumber) + " of type Incorrect number of operands";
            Errors.push_back({b[i].LineNumber,t});            
        }
    }
}

void CheckDuplicateLabel(vector<Label> &a){
    map<string, int> labelMap;
    for(int i=0; i < a.size(); i++){
        labelMap[a[i].LabelName]++;
        if(labelMap[a[i].LabelName] > 1){
            string t = "Error at line " + to_string((a[i].LineNumber)) + " of type Duplicate Label";
            Errors.push_back({(a[i].LineNumber),t});
        }
    }
}

void UndeclaredLabelUse(vector<Label> &a, vector<Instructions> &b){
    map<string, int> DeclaredLabels;
    for(int i=0; i < a.size(); i++){
        DeclaredLabels[a[i].LabelName] = 1;
    }
    for(int i=0; i < b.size(); i++){
        if(b[i].mnemonic == "br" || b[i].mnemonic == "brz" || b[i].mnemonic == "brlz" || b[i].mnemonic == "call"){
            if(b[i].operands.size() == 1 && DeclaredLabels.find(b[i].operands[0]) == DeclaredLabels.end()){
                string t = "Error at line " + to_string(b[i].LineNumber) + " of type Undeclared Label";
                Errors.push_back({b[i].LineNumber,t});
            }
        }
    }    
}

bool isHexadecimal(const string& str) {
    if (str.size() > 2 && str[0] == '0' && (str[1] == 'x' || str[1] == 'X')) {
        for (size_t i = 2; i < str.size(); ++i) {
            if (!isxdigit(str[i])) return false; // Check each character is hex
        }
        return true;
    }
    return false;
}

bool isOctal(const string& str) {
    if (str.empty() || str[0] != '0') return false; // Octal numbers start with '0'
    for (size_t i = 1; i < str.size(); ++i) {
        if (str[i] < '0' || str[i] > '7') return false; // Check each character is in 0-7
    }
    return true;
}

bool isValidLabel(string &str) {
    
    if(str == " " || str.size() == 0){
        return false;
    }
    
    if(!(str[0] >= 'A' && str[0] <= 'Z') && !(str[0] >= 'a' && str[0] <= 'z')){
        return false;
    }

    for(int i=1;i<str.size();i++){
        if(!(str[i] >= 'A' && str[i] <= 'Z') && !(str[i] >= 'a' && str[i] <= 'z') && !(str[i] >= '0' && str[i] <= '9') && !(str[i] == '_')){
            return false;
        }
    }
    
    return true;
}

void CheckValidNumbers(vector<Instructions> &b){
    for(int i=0;i<(b.size());i++){
        if(b[i].operands.size() == 1){
            string temp = b[i].operands[0];

            if(temp.substr(0,2) == "0x" && !isHexadecimal(temp)){
                string t = "Error at line " + to_string(b[i].LineNumber) + " of type Not a Valid  Hexadecimal Number";
                Errors.push_back({b[i].LineNumber,t});
            } else if(!(temp.substr(0,2) == "0x") && (temp.substr(0,1) == "0") && !isOctal(temp) && temp.size()>1){
                string t = "Error at line " + to_string(b[i].LineNumber) + " of type Not a Valid Octal Number";
                Errors.push_back({b[i].LineNumber,t});
            }
        }
    }   
}

void writeErrorsToFile(vector<pair<int,string>>& errors, const string& filename) {
    sort(errors.begin(),errors.end());
    ofstream outFile(filename);
    if (!outFile) {
        cerr << "Error opening file for writing!" << endl;
        return;
    }
    for (const auto& error : errors) {
        outFile << error.second << endl;
    }
    outFile.close();
}

void writeMachineCodeToFile(map<string,string> mp,const string& filename){
    ofstream outFile(filename);
    if (!outFile) {
        cerr << "Error opening file for writing!" << endl;
        return;
    }
    for (const auto it: mp) {
        string s = Map_of_Instruction[it.first];
        outFile << it.first << " " << it.second << " " << s << endl;
    }
    outFile.close();
}

void writeObjectFile(map<string,string> mp,const string& filename){
    ofstream outFile(filename);
    if (!outFile) {
        cerr << "Error opening file for writing!" << endl;
        return;
    }
    
    for(auto it:DataContent){
        outFile << it << " ";
    } outFile << endl;

    int temp1 = 0;
    for (const auto it: mp) {
        outFile << it.second << endl;
    }
    outFile.close();
}

void Check_All_Errors(vector<Label> &a,vector<Instructions> &b){
    CheckNoofOperands(b);
    CheckDuplicateLabel(a);
    CheckCorrectMnemonic(b);
    UndeclaredLabelUse(a,b);
    CheckValidNumbers(b);    
}

void pass1(){
    int ProgramCounter = 0;
    int linenumber = 1;
    for(int i=0; i < FileContent.size(); i++){
        string temp = FileContent[i];

        if(temp == ""){
            linenumber += 1;
            ProgramCounter += 0;
            continue;
        }

        int idxColon = temp.find(":");
        int idxSemiColon = temp.find(";");

        if(idxColon == -1){
            idxColon = temp.size();
        }

        if(idxSemiColon == -1){
            idxSemiColon = temp.size();
        }

        string tempLabel = "";
        string tempInstruction = "";

        if(idxColon < idxSemiColon){
            // Both label and instruction are present
            for(int j=0; j < idxColon; j++){
                tempLabel += (temp[j]);
            }
            tempLabel = Update(tempLabel);
            Label temp1;
            temp1.LabelName = tempLabel;
            temp1.Address = ProgramCounter;
            temp1.LineNumber = linenumber;
            if(isValidLabel(temp1.LabelName)){
                label.push_back(temp1);
                ProgramCounter += 0;
            } else {
                string t = "Error at line " + to_string(linenumber) + " of type Not a Valid Label";
                Errors.push_back({linenumber,t});
            }
            for(int j=idxColon + 1; j < idxSemiColon; j++){
                tempInstruction += (temp[j]);
            }
            tempInstruction = Update(tempInstruction);
            Instructions temp2;
            temp2 = SplitInstruction(tempInstruction, linenumber);
            if(tempInstruction != ""){
                instruction.push_back(temp2);
                ProgramCounter += 1;
            }     
        } else if(idxSemiColon <= idxColon){
            // Only instruction after that comment comes;
            for(int j=0; j < idxSemiColon; j++){
                tempInstruction += (temp[j]);
            }
            tempInstruction = Update(tempInstruction);
            Instructions temp2;
            temp2 = SplitInstruction(tempInstruction, linenumber);
            if(tempInstruction != ""){
                instruction.push_back(temp2);
                ProgramCounter += 1;
            } 
        } 
        linenumber += 1;
    }
    Check_All_Errors(label,instruction);
}

void pass2(){
    
    // Symbol table i.e Labels and their corresponding addresses;
    int PC = 0;
    
    for(int i=0;i<(label.size());i++){
        Label temp = label[i];
        string temp2 = ToHEX(label[i].Address);
        Map_of_Labels[label[i].LabelName] = temp2;
        //cout << label[i].LabelName << " " << temp2 << endl;
    }

    // Conversion of instructions into machine code
    // Machine code  is of 8 characters with lower 2 characters being the value
    // given in the map of OP_Table 
    //int PC = 0;
    for(int i=0;i<(instruction.size());i++){
        Instructions temp = instruction[i];
        string OPCode = "";
        string Operand = "000000";
        string machinecode = "";

        if(temp.mnemonic != "data" && temp.mnemonic != "set"){
            OPCode += OP_Table[temp.mnemonic].first;           
        } 

        if(temp.operands.size() == 1){
            string temp1 = temp.operands[0];

            if(Map_of_Labels.find(temp1) != Map_of_Labels.end()){
                if(temp.mnemonic == "ldc" || temp.mnemonic == "adc" || temp.mnemonic == "adj"){
                    string s1 = Map_of_Labels[temp1];
                    Operand = s1.substr(4,6);
                } else {    
                    string s1 = Map_of_Labels[temp1];
                    int x1 = hexToInt(s1);
                    int x2 = PC;
                    string ans = ToHEX(x1-x2-1).substr(4,6);
                    Operand = ans;    
                }
            } else {
                if(temp1[0] == '0' && temp1[1] == 'x'){
                    // Number is hexadecimal;
                    string temp_s = "";
                    for(int i=2;i<temp1.size();i++){
                        temp_s += (temp1[i]);
                    }

                    while(temp_s.size() < 6){
                        temp_s = '0' + temp_s;
                    }
                    Operand = temp_s;
                } else if(isOctal(temp1)){
                    // It is octal 
                    int temp2 = safeStoi(temp1);
                    temp1 = ToHEX(temp2);
                    Operand = temp1.substr(4,6);
                } else {
                    // It is decimal 
                    int temp2 = safeStoi(temp1);
                    temp1 = ToHEX(temp2);
                    Operand = temp1.substr(4,6);
                }
            }
        } 

        machinecode = Operand + OPCode;

        if(temp.mnemonic == "data" || temp.mnemonic == "set"){
            string temp1 = temp.operands[0];
            int temp2 = safeStoi(temp1);
            temp1 = ToHEX(temp2);
            machinecode = temp1.substr(2,8);
            DataContent.push_back(machinecode);
        }
        string temp_PC;
        temp_PC = ToHEX(PC);

        Map_of_Machine_code[temp_PC] = machinecode; 
        Map_of_Instruction[temp_PC] = FileContent[temp.LineNumber - 1];
        PC++;
    }

    // writeMachineCodeToFile(Map_of_Machine_code,"listing_file.txt");
    // writeObjectFile(Map_of_Machine_code,"ObjectFile.txt");
}


int main(int argc, char* argv[]){

    FILE *file = fopen(argv[1],"r");
    if(!file){
        cout << "Error Opening the File" << endl;
        return 1;
    }

    int MAX_LINE_LENGTH = 300;
    char line[MAX_LINE_LENGTH];
    while(fgets(line, MAX_LINE_LENGTH, file)){
        string temp = Update(line);
        FileContent.push_back(temp);
    }
    fclose(file);
    pass1();
    string x = string(argv[1]);
    string FileName = x.substr(0,x.size()-4);
    
    if(Errors.size() != 0){
        cout << "There are errors in the file." << endl;
        cout << "Kindly check out those errors in the error file generated." << endl;
        writeErrorsToFile(Errors, FileName+".log");
    } else {
        pass2();
        cout << "Compiled without errors." << endl;
        cout << "Respective listing file, object file,log file have been generated." << endl;
        writeErrorsToFile(Errors, FileName+".log");
        writeMachineCodeToFile(Map_of_Machine_code,FileName+".l");
        writeObjectFile(Map_of_Machine_code,FileName+".o");
    }

    return 0;
}
