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

    map<string, int> Sym_hash {
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
        {"R0",21},
        {"R1",22},
        {"R2",23},
        {"R3",24},
        {"WORD",24},
        {"END",24},
    };

    //just for testing:
    //printProgram(program);

    

    firstStep(program,Sym_hash);
 



  







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
int firstStep (Program &program, map<string, int> Hash ){
    Instruction instAux;
    for(size_t i = 0; i<program.amountOfLines-1;  i++){
        for(auto item: program.lines[i]){


            //identificando R);
            if((Hash.find(item) == Hash.end() ) ) {
                cout<<item + " nao é um opcode/reg"<<endl;
            }
            else {cout<<item +" É um opcode/reg"<<endl;}
            


        }
    }




    return 0;
}

