#include <iostream>
#include "CommonLib.h"

int main(int argc, char* argv[]) {
    ifstream infile; ofstream outfile;
    CommonLib::initFiles(infile, outfile, argc, argv, "cardCounter");

    return 0;
}
