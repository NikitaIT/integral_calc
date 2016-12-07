#ifndef PARSER_H
#define PARSER_H
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string.h>
#include <stack>
#include <list>
#include <functional>
#include <algorithm>

using namespace std;
class Parser
{
public:
    Parser(const char * input){_List = shunting_yard(input); printParserList();}
    #define is_operator(c) (c == "+" || c == "-" || c == "/" || c == "*" || c == "!" || c == "%" || c == "=")
    #define is_leter(c) ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
    list<string> shunting_yard(const char * input);
    void printParserList();
    double generateFunction(double x);
private:
    /**
     * Сколько аргументов у оператора?
     * @brief op_arg_count
     * @param op
     * @return uint {2 аргумента,1 аргумент,0 аргументов}
     */
    static unsigned int op_arg_count(const string op);
    /**
     * Приоритет Операторов
     * @brief op_preced
     * @param op
     * @return int {4 {!} правая,3 {*,/,%} левая,2 {+,-} левая, 1 {=} левая}
     */
    static int op_preced(const string op);
    /**
     * Ассоциативность Операторов
     * @brief op_left_assoc
     * @param op
     * @return bool {1 - лево, 2 - право}
     */
    static bool op_left_assoc(const string op);
    /**
     * @brief is_func
     * @param token
     * @return bool {true - если функция }
     */
    static bool is_func(const string token);
private:
    list<string> _List;
};

#endif // PARSER_H
