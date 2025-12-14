#include<iostream>
#include"preprocessor.h"
#include"lexer.h"
using namespace std;

int main(){
    string source , line;
    while(getline(cin , line)){
        source += line + '\n';
    }
    preprocessor p(source);
    lexer lex(p.proces());
}