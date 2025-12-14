#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H
#include <iostream>
using namespace std;

class preprocessor{
    string source_code;
    string findLibrary(const string &);
    public:
        preprocessor(const string &);
        string proces();
};

#endif