#include <iostream>
#include <string>
#include "montador.h"

StringIntHash instructionHash(Instructions);
StringIntHash registerHash(Registers);

// void printProgram(Program &program) {
//     string command;
//     cout << endl << "--------------------------" << endl;
//     cout << "Programa" << endl;
//     cout << "--------------------------" << endl;
//     for(size_t i = 0; i < program.amountOfLines; i++) {
//         for(size_t j = 0; j < program.lines[i].size(); j++) {
//             command = command + " | " + program.lines[i][j];
//         }
//         cout << i << command + " | " << endl;
//         command.clear();
//     }
//     return;
// }

// void printSymbolHash(SymbolHash &symbolHash) {
//     string command;
//     cout << endl << "--------------------------" << endl;
//     cout << "Tabela de Simbolos" << endl;
//     cout << "--------------------------" << endl;
//     for(auto it = symbolHash.hash.cbegin(); it != symbolHash.hash.cend(); ++it)
//     {
//         std::cout << it->first << " : " << it->second << endl;
//     }
//     return;
// }

int assemble(char *fileName) {
    ifstream programFile(fileName);
    Program program;
    StringIntHash symbolHash;
    firstStep(programFile, program, symbolHash);
    secondStep(program, symbolHash);
  
    // printProgram(program);
    // printSymbolHash(symbolHash);

    programFile.close();
    return 0;
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
                program.addLine({meaningfulVec[1]});
                symbolHash.addToHash(symbol, program.amountOfLines);
            }
            else if(command == PSEUDO_INST_END) {
                return;
            }
            else if(instructionHash.getCorrespondent(command) >= 0) {
                program.addLine(meaningfulVec);
                if(!symbol.empty()) {
                    symbolHash.addToHash(symbol, program.amountOfLines);
                }
            }
        }
        symbol.clear();
        command.clear();
    }
    return;
}

void secondStep(Program &program, StringIntHash &symbolHash) {
    string command;
    int correspondent;
    vector<int> machineCommands;
    int machineCommandAmmount = 0;
    for(size_t i = 0; i < program.amountOfLines; i++) {
        for(size_t j = 0; j < program.lines[i].size(); j++) {
            command = program.lines[i][j];
            correspondent = instructionHash.getCorrespondent(command);
            if(correspondent < 0) {
                correspondent = registerHash.getCorrespondent(command);
            }
            if(correspondent < 0) {
                correspondent = symbolHash.getCorrespondent(command);
            }
            if(correspondent >= 0) {
                machineCommands.push_back(correspondent);
                machineCommandAmmount++;
                cout << correspondent << " ";
            }
            else {
                machineCommands.push_back(atoi(command.c_str()));
                machineCommandAmmount++;
                cout << atoi(command.c_str()) << " ";
            }
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

// vector<int> secondStep (const Program program, map<string, int> Hash,  map<string, int> Sym){
//     int instLine = 0;   //current isntruction line
//     bool WORDappear = 0 ; //accommodates the memory position of WORD storage
//     vector<int> finalBin; //vector with the final decial numbers to be outputed
//     map<string, int>::iterator it;

//     for(size_t i = 0; i<program.amountOfLines;  i++){
//         instLine++;
//         for(auto item: program.lines[i]){
//             if(item == "END") return finalBin;//stops if END is found


//             if((Hash.find(item) == Hash.end()) & (!isNumber(item)) & (item.back() != ':')) { //found a Symbol. substitute with its memory position 

//                 it  = Sym.find(item + ':');
//                 finalBin.push_back(it->second);
                
//             } 
//             else if(item == "WORD"){
//                 WORDappear = true;
//             }
//             else if(isNumber(item) & (WORDappear)){
//                 finalBin.push_back(stoi(item));
//                 WORDappear = false;
//             }
//         }
//     }
//     return finalBin;
// }

// bool isNumber(const string &str) {
//     for(const char &c : str) {
//         if (isdigit(c) != 0) return false;
//     }
//     return true;
// }