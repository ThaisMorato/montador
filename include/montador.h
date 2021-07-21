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

// map<string, int> Sym_hash {
//         {"Halt" , 0},  // Stop the program.
//         {"Load" , 1},  // Reg[R] <- Mem[M + PC]
//         {"Store" , 2}, // Mem[M + PC] <- Reg[R]
//         {"Read" , 3},  // Reg[R] <- input
//         {"Write" , 4}, // output <- Reg[R]
//         {"Copy" , 5},  // Reg[R1] <- Reg[R2], update PSW
//         {"Push" , 6},  // SP <- SP - 1; Mem[SP] <- Reg[R]
//         {"Pop" , 7},   // Reg[R] <- Mem[SP]; SP <- SP + 1;
//         {"Add" , 8},   // Reg[R1] <- Reg[R1] + Reg[R2], update PSW
//         {"Sub" , 9},   // Reg[R1] <- Reg[R1] - Reg[R2], update PSW
//         {"Mul" , 10},  // Reg[R1] <- Reg[R1] * Reg[R2], update PSW
//         {"Div" , 11},  // Reg[R1] <- Reg[R1] / Reg[R2], update PSW
//         {"Mod" , 12},  // Reg[R1] <- Reg[R1] % Reg[R2], update PSW
//         {"And" , 13},  // Reg[R1] <- Reg[R1] & Reg[R2], update PSW
//         {"Or" , 14},   // Reg[R1] <- Reg[R1] | Reg[R2], update PSW
//         {"Not" , 15},  // Reg[R1] <- ~Reg[R1], update PSW
//         {"Jump" , 16}, // PC <- PC + M
//         {"JZ" , 17},   // If PSW[0] == 1, PC <- PC + M
//         {"JN" , 18},   // If PSW[1] == 1, PC <- PC + M
//         {"Call" , 19}, // SP <- SP - 1; Mem[SP] <- PC; PC <- PC + M
//         {"Ret" , 20},  // PC <- Mem[SP]; SP <- SP + 1
//     };

enum Symbol {
    HALT = 0,  // Stop the program.
    LOAD = 1,  // Reg[R] <- Mem[M + PC]
    STORE = 2, // Mem[M + PC] <- Reg[R]
    READ = 3,  // Reg[R] <- input
    WRITE = 4, // output <- Reg[R]
    COPY = 5,  // Reg[R1] <- Reg[R2], update PSW
    PUSH = 6,  // SP <- SP - 1; Mem[SP] <- Reg[R]
    POP = 7,   // Reg[R] <- Mem[SP]; SP <- SP + 1;
    ADD = 8,   // Reg[R1] <- Reg[R1] + Reg[R2], update PSW
    SUB = 9,   // Reg[R1] <- Reg[R1] - Reg[R2], update PSW
    MUL = 10,  // Reg[R1] <- Reg[R1] * Reg[R2], update PSW
    DIV = 11,  // Reg[R1] <- Reg[R1] / Reg[R2], update PSW
    MOD = 12,  // Reg[R1] <- Reg[R1] % Reg[R2], update PSW
    AND = 13,  // Reg[R1] <- Reg[R1] & Reg[R2], update PSW
    OR = 14,   // Reg[R1] <- Reg[R1] | Reg[R2], update PSW
    NOT = 15,  // Reg[R1] <- ~Reg[R1], update PSW
    JUMP = 16, // PC <- PC + M
    JZ = 17,   // If PSW[0] == 1, PC <- PC + M
    JN = 18,   // If PSW[1] == 1, PC <- PC + M
    CALL = 19, // SP <- SP - 1; Mem[SP] <- PC; PC <- PC + M
    RET = 20,  // PC <- Mem[SP]; SP <- SP + 1
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


//class to accommodate an instruction
class Instruction {
    public:
	    Symbol sym;
        vector<int> operands; // 0, 1, or 2 operands, depending on the symbol <sym>.

        void setInstruction (Symbol sym, vector<int> operands ){
            this->sym = sym;
            this->operands = operands;
        }
};




//assembler functions
int assemble(char *fileName);  					//called in main
Program readProgram(ifstream &programFile);		//read a file (programFile) and return a  Program instance
vector<string> getMeaningfulVec(string &line);	
int firstStep (Program &program);

#endif
