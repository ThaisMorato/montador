#include <iostream>
#include <string>
#include "montador.h"

StringIntHash instructionHash(Instructions);
StringIntHash registerHash(Registers);

int assemble(char *fileName) {
    ifstream programFile(fileName);
    Program program;
    StringIntHash symbolHash;
    string machineCommands;

    firstStep(programFile, program, symbolHash);
    secondStep(program, symbolHash, machineCommands);
    genAssemblerOutput(machineCommands, program.amountOfCommands);

    programFile.close();
    return 0;
}

void genAssemblerOutput(string machineCommands, int machineCommandAmmount) {
    cout << "MV-EXE\n\n";
    cout << to_string(machineCommandAmmount) + " 100 999 100\n\n";
    cout << machineCommands + "\n";
}

void firstStep(ifstream &programFile, Program &program, StringIntHash &symbolHash) {
    string line;
    string symbol;
    string command;
    while(getline(programFile, line)) {
        vector<string> meaningfulVec = getMeaningfulVec(line);
        if(meaningfulVec.size() > 0 && meaningfulVec[0].back() == *LABEL_DELIMITER) {
            symbol = meaningfulVec[0].substr(0, meaningfulVec[0].size()-1);
            meaningfulVec.erase(meaningfulVec.begin());
        }
        if(meaningfulVec.size() > 0) {
            command = meaningfulVec[0];
            if(command == PSEUDO_INST_WORD && !symbol.empty() && meaningfulVec.size() > 1) {
                symbolHash.addToHash(symbol, program.amountOfCommands + 1);
                program.addLine({meaningfulVec[1]});
            }
            else if(command == PSEUDO_INST_END) {
                return;
            }
            else if(instructionHash.getCorrespondent(command) >= 0) {
                if(!symbol.empty()) {
                    symbolHash.addToHash(symbol, program.amountOfCommands + 1);
                }
                program.addLine(meaningfulVec);
            }
        }
        symbol.clear();
        command.clear();
    }
    return;
}

void secondStep(Program &program, StringIntHash &symbolHash, string &machineCommands) {
    string command;
    int correspondent;
    int machineCommand;
    int currentCommand = 1;
    for(size_t i = 0; i < program.amountOfLines; i++) {
        for(size_t j = 0; j < program.lines[i].size(); j++) {
            command = program.lines[i][j];
            correspondent = instructionHash.getCorrespondent(command);
            machineCommand = correspondent;
            if(correspondent < 0) {
                correspondent = registerHash.getCorrespondent(command);
                machineCommand = correspondent;
            }
            if(correspondent < 0) {
                correspondent = symbolHash.getCorrespondent(command);
                machineCommand = correspondent - (currentCommand + 1);
            }
            if(correspondent >= 0) {
                machineCommands = machineCommands + to_string(machineCommand) + " ";
            }
            else {
                machineCommands = machineCommands + command + " ";
            }
            currentCommand++;
        }
    }
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

