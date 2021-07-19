#ifndef MONTADOR_H
#define MONTADOR_H

//includes and namespaces
#include <fstream>
#include <vector>
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

//assembler functions
int assemble(char *fileName);
Program readProgram(ifstream &programFile);
vector<string> getMeaningfulVec(string &line);

#endif
