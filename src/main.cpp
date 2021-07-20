#include "montador.h"

int main(int argc, char *argv[]) {
    if(argc > 1) {
        assemble(argv[1]);
    }
    return 0;
}