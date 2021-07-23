#include <iostream>
#include <string>
#include "montador.h"
#include <map>

void printProgram(Program &program) {
    string command;
    for(size_t i = 0; i < program.amountOfLines; i++) {
        for(size_t j = 0; j < program.lines[i].size(); j++) {
            command = command + " | " + program.lines[i][j];
        }
        cout << command + " | " << endl;
        command.clear();
    }
    return;
}

 ////////////////////////ASSEMBLE//////////////////////////
int assemble(char *fileName) {
    ifstream programFile(fileName);
    Program program = readProgram(programFile);

const map<string, int> known_hash {
        {"HALT" , 0},  // Stop the program.
        {"LOAD" , 1},  // Reg[R] <- Mem[M + PC]
        {"STORE" , 2}, // Mem[M + PC] <- Reg[R]
        {"READ" , 3},  // Reg[R] <- input
        {"WRITE" , 4}, // output <- Reg[R]
        {"COPY" , 5},  // Reg[R1] <- Reg[R2], update PSW
        {"PUSH" , 6},  // SP <- SP - 1; Mem[SP] <- Reg[R]
        {"POP" , 7},   // Reg[R] <- Mem[SP]; SP <- SP + 1;
        {"ADD" , 8},   // Reg[R1] <- Reg[R1] + Reg[R2], update PSW
        {"SUB" , 9},   // Reg[R1] <- Reg[R1] - Reg[R2], update PSW
        {"MUL" , 10},  // Reg[R1] <- Reg[R1] * Reg[R2], update PSW
        {"DIV" , 11},  // Reg[R1] <- Reg[R1] / Reg[R2], update PSW
        {"MOD" , 12},  // Reg[R1] <- Reg[R1] % Reg[R2], update PSW
        {"AND" , 13},  // Reg[R1] <- Reg[R1] & Reg[R2], update PSW
        {"OR" , 14},   // Reg[R1] <- Reg[R1] | Reg[R2], update PSW
        {"NOT" , 15},  // Reg[R1] <- ~Reg[R1], update PSW
        {"JUMP" , 16}, // PC <- PC + M
        {"JZ" , 17},   // If PSW[0] == 1, PC <- PC + M
        {"JN" , 18},   // If PSW[1] == 1, PC <- PC + M
        {"CALL" , 19}, // SP <- SP - 1; Mem[SP] <- PC; PC <- PC + M
        {"RET" , 20},  // PC <- Mem[SP]; SP <- SP + 1
        {"R0",0},
        {"R1",1},
        {"R2",2},
        {"R3",3},
        {"WORD",0},
        {"END",0},
    };

    map<string, int> Symb_hash; //tabela de symbolos a ser populada pela primeira etapa
     firstStep(program, known_hash, Symb_hash);

     //cout<<Symb_hash["test:"]<<endl;
    
    vector<int> finalBin = secondStep(program, known_hash, Symb_hash);
    cout << finalBin[2]<<endl;

  
    //printProgram(program);



    
 


  







    programFile.close();
    return 0;
}
//////////////////////////////////////////////////////////


Program readProgram(ifstream &programFile) {
    string line;
    Program program;
    while(getline(programFile, line)) {
        vector<string> meaningfulVec = getMeaningfulVec(line);
        if(meaningfulVec.size() > 0) {
            program.addLine(meaningfulVec);
        }
    }
    return program;
}

vector<string> getMeaningfulVec(string &line) {
    vector<string> meaningfulVec;
    string meaningful;
    bool foundMeaningful = false;
    char c;
    for (size_t i = 0; i < line.size(); i++) {
        c = line[i];
        if(isspace(c)){
            if(foundMeaningful) {
                meaningfulVec.push_back(meaningful);
                meaningful.clear();
            }
            foundMeaningful = false;
        }
        else if(c == *COMMENT_DELIMITER) {
            break;
        }
        else {
            foundMeaningful = true;
            meaningful = meaningful + c;
        }
    }
    if(foundMeaningful) {
        meaningfulVec.push_back(meaningful);
    }
    return meaningfulVec;
}

//seeks for some undetermined label/sysmbol and creates a symbol table
//it receives a program, a a dictionary with all commands (reg/opcodes) and a Symbol Hash of user diffined sysmbols.
int firstStep ( const Program program, const map<string, int> Hash, map<string, int> &Sym ){
    Instruction instAux;
    map<string, int>::iterator it;
    string item_a; //iterator for Sym
    int instLine = 0;

    for(size_t i = 0; i<program.amountOfLines;  i++){
        instLine++;
        for(auto item: program.lines[i]){
            
            //identificando  comandos indefinidos;
            
            if((Hash.find(item) == Hash.end()) & (!isNumber(item))) { //unknown command

                if(!(item.back()== *LABEL_DELIMITER)) {item_a = item + *LABEL_DELIMITER;} else {item_a = item;}; //adds ':' to item's end
                
                it  = Sym.find(item_a);
                if(it == Sym.end()){ //the unknonw command does NOT exist
                   Sym.insert(pair<string,int>(item_a,*MEM_SIZE)); 
                } 
            else{//the unknonw command DOES exist
                    it->second = instLine;
                }
            }
            else {} //known command
        }
    }
    return 0;
}



vector<int> secondStep (const Program program, map<string, int> Hash,  map<string, int> Sym){
    int instLine = 0;   //current isntruction line
    bool WORDappear = 0 ; //accommodates the memory position of WORD storage
    vector<int> finalBin; //vector with the final decial numbers to be outputed
    map<string, int>::iterator it;

    for(size_t i = 0; i<program.amountOfLines;  i++){
        instLine++;
        for(auto item: program.lines[i]){
            if(item == "END") return finalBin;//stops if END is found


            if((Hash.find(item) == Hash.end()) & (!isNumber(item)) & (item.back() != ':')) { //found a Symbol. substitute with its memory position 

                it  = Sym.find(item + ':');
                finalBin.push_back(it->second);
                
            } 
            else if(item == "WORD"){
                WORDappear = true;
            }
            else if(isNumber(item) & (WORDappear)){
                finalBin.push_back(stoi(item));
                WORDappear = false;
            }
        }
    }
    return finalBin;
}

//check se uma string contém um número
bool isNumber(const string& str)
{
    for (char const &c : str) {
        if (std::isdigit(c) == 0) return false;
    }
    return true;
}

void generateInstructions(){





}