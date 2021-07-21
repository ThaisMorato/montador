#include <iostream>
#include <string>
#include "montador.h"

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

    //just for testing:
    //printProgram(program);

    

    firstStep(program);






  







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
int firstStep (Program &program){
    Instruction instAux;
    for(size_t i = 0; i<program.amountOfLines-1;  i++){
        for(auto item: program.lines[i]){


            //identificando R);
            if((item != "R0") ) {
                cout<<item + " diferente de R0"<<endl;
            }
            else {cout<<item +" É R0"<<endl;}
            


        }
    }




    return 0;
}

