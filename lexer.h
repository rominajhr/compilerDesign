#ifndef LEXER_H
#define LEXER_H
#include<iostream>
using namespace std;


enum TokenType {
    T_KEYWORD,
    T_IDENTIFIER,
    T_NUMBER,
    T_OPERATOR,
    T_SYMBOL,
    T_ERROR
};

inline string tokenTypeToString(TokenType t) {
    switch (t) {
        case T_KEYWORD:    return "\033[34mKEYWORD   ";
        case T_IDENTIFIER: return "\033[37mIDENTIFIER";
        case T_NUMBER:     return "\033[33mNUMBER    ";
        case T_OPERATOR:   return "\033[31mOPERATOR  ";
        case T_SYMBOL:     return "\033[35mSYMBOL    ";
        case T_ERROR:      return "\033[91mERROR     ";
        default:           return "UNKNOWN   ";
    }
}

class lexer{
    string src;
    int i;
    int line;

    void printToken(TokenType type ,const string & st){
        cout<<"Token : "<< st << "\ttype : " << tokenTypeToString(type)<<  "\033[0m" << "\tLine : "<<line<<endl;
    }


    public : 
        lexer(const string &);


};

#endif