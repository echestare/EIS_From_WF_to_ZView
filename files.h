#ifndef FILES_H
#define FILES_H

#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;


class Files
{
private:
    bool flagEIS=false;
    fstream fileEIS;
    ifstream fileTXT;
    string fileName, fileNameTXT;

public:
    Files();
    ~Files();
    void checkingEISfile();
    void modifyEISfile();
    void namingTXTfile();
    void checkingTXTfile();

};

#endif // FILES_H
