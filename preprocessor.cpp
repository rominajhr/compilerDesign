#include "preprocessor.h"
#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;

preprocessor :: preprocessor (const string &sc) : source_code(sc){}

string preprocessor :: findLibrary(const string & lbn){
    
    ifstream file("data/libraries/" + lbn);
    if (!file.is_open()) return "// Missing library: " + lbn;

    stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

string preprocessor :: proces(){
    stringstream input(source_code);
    string line;
    string result;

    cout<<"\n\n\033[91m ---------------- PREPROCESSOR ---------------- \033[0m\n\n";


    while(getline(input , line)){

        size_t pos = line.find("#include");
        string libname;

        if(pos != string::npos){
            while(line[pos] != '<')
                pos++;
            pos++;
            
            while(line[pos] != '>'){
                libname += line[pos];
                pos++;
            }

            libname += ".txt";
            result += findLibrary(libname);
            
        }
        else{
            result += line + '\n';
        }
    }

    cout<<result<<endl;

    return result;
}
