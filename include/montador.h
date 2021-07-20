#ifndef MONTADOR_H
#define MONTADOR_H

//includes and namespaces
#include <fstream>
#include <vector>
#include <map>
using namespace std;

//definitions
#define COMMENT_DELIMITER ";"
#define LABEL_DELIMITER ":"

//classes
// class Symbol {
//     public:
//     string label;
//     string command;
//     Symbol(string labelValue, string commandValue) {
//         label = labelValue;
//         command = commandValue;
//     }
// };

enum Symbol {
    Halt = 0,  // Stop the program.
    Load = 1,  // Reg[R] <- Mem[M + PC]
    Store = 2, // Mem[M + PC] <- Reg[R]
    Read = 3,  // Reg[R] <- input
    Write = 4, // output <- Reg[R]
    Copy = 5,  // Reg[R1] <- Reg[R2], update PSW
    Push = 6,  // SP <- SP - 1; Mem[SP] <- Reg[R]
    Pop = 7,   // Reg[R] <- Mem[SP]; SP <- SP + 1;
    Add = 8,   // Reg[R1] <- Reg[R1] + Reg[R2], update PSW
    Sub = 9,   // Reg[R1] <- Reg[R1] - Reg[R2], update PSW
    Mul = 10,  // Reg[R1] <- Reg[R1] * Reg[R2], update PSW
    Div = 11,  // Reg[R1] <- Reg[R1] / Reg[R2], update PSW
    Mod = 12,  // Reg[R1] <- Reg[R1] % Reg[R2], update PSW
    And = 13,  // Reg[R1] <- Reg[R1] & Reg[R2], update PSW
    Or = 14,   // Reg[R1] <- Reg[R1] | Reg[R2], update PSW
    Not = 15,  // Reg[R1] <- ~Reg[R1], update PSW
    Jump = 16, // PC <- PC + M
    JZ = 17,   // If PSW[0] == 1, PC <- PC + M
    JN = 18,   // If PSW[1] == 1, PC <- PC + M
    Call = 19, // SP <- SP - 1; Mem[SP] <- PC; PC <- PC + M
    Ret = 20,  // PC <- Mem[SP]; SP <- SP + 1
};


class Program {
    public:
    vector<vector<string>> lines;
    size_t amountOfLines;
    Program() {
        amountOfLines = 0;
    }
    void addLine(vector<string> line) {
        lines.push_back(line);
        amountOfLines++;
    }
};


//class to acomodate an instruction
class Intruction {
    public:
	Symbol sym;
    vector<int> operands; // 0, 1, or 2 operands, depending on the symbol <sym>.
};




//assembler functions
int assemble(char *fileName);  					//called in main
Program readProgram(ifstream &programFile);		//read a file (programFile) and return a  Program instance
vector<string> getMeaningfulVec(string &line);	

#endif
