#include "lexer.h"
#include<iostream>
using namespace std;

lexer :: lexer(const string & code) : src(code) , i(0) , line(1) {

    cout<< "\n\n\033[32m -------------------- TOKEN -------------------- \033[0m \n\n";
    
    while(i < src.length()){

        if(src[i] == ' ' || src[i] == '\t'){
            i++;
            continue;
        }

        if(src[i] == '\n'){
            i++;
            line++;
            continue;
        }


        // ---------------- COMMENTS ----------------
        if(src[i] == '/'){
            if(src[i + 1] == '/'){  // single line
                while(src[i] != '\n' && i <= src.length())
                    i++;
            
                continue;
            }
            else if(src[i + 1] == '*'){  // multi line
                bool closed = false;
                while(src[i] != '\0'){
                    if(src[i] == '*' && src[i + 1] == '/'){
                        closed = true;
                        i += 2;
                        break;
                    }
                    if(src[i] == '\n')
                        line++;

                    i++;
                }

                if(!closed){
                    printToken(T_ERROR , "Unclosed comment");
                    return;
                }
            }
            else{  // operator
                printToken(T_OPERATOR , string(1 , src[i]));
                i++;
            }

            continue;
        }

        // ---------------- NUMBER ----------------
        if(isdigit(src[i])){
            string num;
            while(isdigit(src[i]) || src[i] == '.'){
                num += src[i];
                i++;
            }

            if(isalpha(src[i]) || src[i - 1] == '.'){
                printToken(T_ERROR, "Invalid number format");
                return;
            }

            printToken(T_NUMBER , num);
        }

        // ---------------- IDENTIFIER / KEYWORD ----------------
        if(isalpha(src[i]) || src[i] == '_'){
            string word;
            while(isalnum(src[i]) || src[i] == '_'){
                word += src[i];
                i++;
            }

            if(word == "int" || word == "return")
                printToken(T_KEYWORD , word);
            else
                printToken(T_IDENTIFIER , word);

            continue;
        }

        // ---------------- OPERATORS ----------------
        if(src[i] == '<' && src[i + 1] == '<'){
            printToken(T_OPERATOR , "<<");
            i += 2;
            continue;
        }
        if(src[i] == '>' && src[i + 1] == '>'){
            printToken(T_OPERATOR , ">>");
            i += 2;
            continue;
        }
        if(src[i] == '-' || src[i] == '+' || src[i] == '*' || src[i] == '%' || src[i] == '='){
            printToken(T_OPERATOR , string(1 , src[i]));
            i++;
            continue;
        }

        // ---------------- SYMBOLS ----------------
        if (src[i] == ';' || src[i] == '{' || src[i] == '}' || src[i] == '(' || src[i] == ')') {
                printToken(T_SYMBOL, std::string(1, src[i]));
                i++;
                continue;
        }

        // ---------------- STRING ----------------
        if (src[i] == '\"') {
            i++;
            while (i < src.length() && src[i] != '\"') {

                if (src[i] == '\n') {
                    printToken(T_ERROR, "Unclosed string literal");
                    return;
                }

                i++;
            }

            if (i >= src.length()) {
                printToken(T_ERROR, "Unclosed string literal");
                return;
            }

            i++;
            continue;
        }

        // ---------------- INVALID TOKEN ----------------
        printToken(T_ERROR, "Invalid token: " + src[i]);
        return;

    }


}