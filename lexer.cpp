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
                printToken(T_DIV , string(1 , src[i]));
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

            auto it = keywordTable.find(word);
            if (it != keywordTable.end())
                printToken(it->second, word);
            else
                printToken(T_IDENTIFIER, word);

            continue;
        }

        // ---------------- TWO CHARACTER OPERATORS ----------------
        string two;
        two += src[i];
        two += src[i + 1];
        auto it2 = twoCharOps.find(two);
        if (it2 != twoCharOps.end()) {
            printToken(it2->second, two);
            i += 2;
            continue;
        }
        
        // ---------------- SYMBOLS OR ONE CHARACTER OPERATORS ----------------
        auto it1 = symbolORoneCarOpsTable.find(src[i]);
        if (it1 != symbolORoneCarOpsTable.end()) {
            printToken(it1->second, string(1, src[i]));
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
