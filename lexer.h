#ifndef LEXER_H
#define LEXER_H
#include<iostream>
#include<unordered_map>
using namespace std;


enum TokenType {
    // Keywords
    T_INT,
    T_MAIN,
    T_VOID,
    T_COUT,
    T_AUTO,
    T_PRINT,

    // Identifiers & literals
    T_IDENTIFIER,
    T_NUMBER,

    // Operators
    T_PLUS,
    T_MINUS,
    T_MULT,
    T_DIV,
    T_MOD,

    // Relational
    T_ASSIGN,
    T_EQUAL,
    T_NOT_EQUAL,
    T_LESS,
    T_GREATER,
    T_LESS_EQUAL,
    T_GREATER_EQUAL,

    // Shift
    T_SHIFT_LEFT,
    T_SHIFT_RIGHT,

    // Symbols
    T_OPEN_BRACE,
    T_CLOSE_BRACE,
    T_SEMICOLON,
    T_LEFT_PAREN,
    T_RIGHT_PAREN,

    // Error
    T_ERROR
};


inline string tokenTypeToString(TokenType t) {
    switch (t) {

        // -------- Keywords --------
        case T_INT:   return "\033[34mINT        ";
        case T_VOID:  return "\033[34mVOID       ";
        case T_MAIN:  return "\033[95mMAIN       ";
        case T_COUT:  return "\033[36mCOUT       ";
        case T_AUTO:  return "\033[34mAUTO       ";
        case T_PRINT: return "\033[36mPRINT      ";

        // -------- Identifiers & literals --------
        case T_IDENTIFIER: return "\033[37mIDENTIFIER";
        case T_NUMBER:     return "\033[33mNUMBER    ";

        // -------- Arithmetic operators --------
        case T_PLUS:  return "\033[33mPLUS       ";
        case T_MINUS: return "\033[33mMINUS      ";
        case T_MULT:  return "\033[33mMULT       ";
        case T_DIV:   return "\033[33mDIV        ";
        case T_MOD:   return "\033[33mMOD        ";

        // -------- Assignment --------
        case T_ASSIGN: return "\033[31mASSIGN     ";

        // -------- Relational --------
        case T_EQUAL:         return "\033[34mEQUAL      ";
        case T_NOT_EQUAL:     return "\033[34mNOT_EQUAL  ";
        case T_LESS:          return "\033[34mLESS       ";
        case T_GREATER:       return "\033[34mGREATER    ";
        case T_LESS_EQUAL:    return "\033[34mLESS_EQUAL ";
        case T_GREATER_EQUAL: return "\033[34mGREATER_EQUAL ";

        // -------- Shift --------
        case T_SHIFT_LEFT:  return "\033[35mSHIFT_LEFT ";
        case T_SHIFT_RIGHT: return "\033[35mSHIFT_RIGHT";

        // -------- Symbols --------
        case T_OPEN_BRACE:  return "\033[32mOPENBRACE  ";
        case T_CLOSE_BRACE: return "\033[32mCLOSEBRACE ";
        case T_SEMICOLON:  return "\033[32mSEMICOLON  ";
        case T_LEFT_PAREN:  return "\033[32mLEFT_PAREN ";
        case T_RIGHT_PAREN: return "\033[32mRIGHT_PAREN";

        // -------- Error --------
        case T_ERROR: return "\033[91mERROR      ";

        default: return "UNKNOWN    ";
    }
}

class lexer{
    string src;
    int i;
    int line;

    unordered_map <string, TokenType> keywordTable = {
        {"int",  T_INT},
        {"void", T_VOID},
        {"main", T_MAIN},
        {"cout", T_COUT},
        {"auto" , T_AUTO},
        {"printf" , T_PRINT}
    };

    unordered_map <char , TokenType> symbolORoneCarOpsTable = {
        {';' , T_SEMICOLON},
        {'(' , T_LEFT_PAREN},
        {')' , T_RIGHT_PAREN},
        {'{' , T_OPEN_BRACE},
        {'}' , T_CLOSE_BRACE},
        {'+', T_PLUS},
        {'-', T_MINUS},
        {'*', T_MULT},
        {'/', T_DIV},
        {'%', T_MOD},
        {'=', T_ASSIGN},
        {'<', T_LESS},
        {'>', T_GREATER}
    };

    unordered_map<string, TokenType> twoCharOps = {
        {"==", T_EQUAL},
        {"!=", T_NOT_EQUAL},
        {"<=", T_LESS_EQUAL},
        {">=", T_GREATER_EQUAL},
        {"<<", T_SHIFT_LEFT},
        {">>", T_SHIFT_RIGHT}
    };

    void printToken(TokenType type ,const string & st){
        cout<<"Token : "<< st << "\ttype : " << tokenTypeToString(type)<<  "\033[0m" << "\tLine : "<<line<<endl;
    }


    public : 
        lexer(const string &);


};

#endif
