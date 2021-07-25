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
#define MEM_SIZE "1000"

class StringIntHash {
    private:
        map<string, int>::iterator it;
        map<string, int> hash;
    public:
        StringIntHash() {}
        StringIntHash(map<string, int> initialHash) {
            hash = initialHash;
        }
        void addToHash(string symbol, int value) {
            hash.insert(pair<string,int>(symbol, value));
        }
        int getCorrespondent(string command) {
            it = hash.find(command);
            if(it == hash.end()) {
                return -1;
            }
            else {
                return it->second;
            }
        }
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

//INUTIL POR ENQUANTO: class to accommodate an instruction
// class Instruction {
//     public:
// 	    int      opcode;
//         vector<int> operands; // 0, 1, or 2 operands, depending on the symbol <sym>.
//         int         mem_addr;


//         void setInstruction (int opcode, vector<int> operands, int mem_addr ){
//             this->opcode =      opcode;
//             this->operands =    operands;
//             this->mem_addr =    mem_addr;
//         }
// };

//assembler functions
int assemble(char *fileName);
void firstStep(ifstream &programFile, Program &program, StringIntHash &symbolHash);
int secondStep(Program &program, StringIntHash &symbolHash, string &machineCommands);
void genAssemblerOutput(string machineCommands, int machineCommandAmmount);
vector<string> getMeaningfulVec(string &line);	

const map<string, int> Instructions {
    {"HALT",    0}, // Stop the program
    {"LOAD",    1}, // Reg[R] <- Mem[M + PC]
    {"STORE",   2}, // Mem[M + PC] <- Reg[R]
    {"READ",    3}, // Reg[R] <- input
    {"WRITE",   4}, // output <- Reg[R]
    {"COPY",    5}, // Reg[R1] <- Reg[R2], update PSW
    {"PUSH",    6}, // SP <- SP - 1; Mem[SP] <- Reg[R]
    {"POP",     7}, // Reg[R] <- Mem[SP]; SP <- SP + 1;
    {"ADD",     8}, // Reg[R1] <- Reg[R1] + Reg[R2], update PSW
    {"SUB",     9}, // Reg[R1] <- Reg[R1] - Reg[R2], update PSW
    {"MUL",    10}, // Reg[R1] <- Reg[R1] * Reg[R2], update PSW
    {"DIV",    11}, // Reg[R1] <- Reg[R1] / Reg[R2], update PSW
    {"MOD",    12}, // Reg[R1] <- Reg[R1] % Reg[R2], update PSW
    {"AND",    13}, // Reg[R1] <- Reg[R1] & Reg[R2], update PSW
    {"OR",     14}, // Reg[R1] <- Reg[R1] | Reg[R2], update PSW
    {"NOT",    15}, // Reg[R1] <- ~Reg[R1], update PSW
    {"JUMP",   16}, // PC <- PC + M
    {"JZ",     17}, // If PSW[0] == 1, PC <- PC + M
    {"JN",     18}, // If PSW[1] == 1, PC <- PC + M
    {"CALL",   19}, // SP <- SP - 1; Mem[SP] <- PC; PC <- PC + M
    {"RET",    20}, // PC <- Mem[SP]; SP <- SP + 1
};

//Pseudo-instructions
#define PSEUDO_INST_WORD "WORD"
#define PSEUDO_INST_END "END"

const map<string, int> Registers {
    {"R0",      0},
    {"R1",      1},
    {"R2",      2},
    {"R3",      3}
};

#endif
