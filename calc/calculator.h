#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "calc/integralcalc.h"
#include "parser/parser_q.h"

using namespace std;
// Класс для использования
class Calculator
{
public:
    Calculator( IntegralCalc* comp): _integral_calc(comp) {}
    ~Calculator() { delete _input; delete _integral_calc; delete _parser; }
    void setInputString(const char * input);
    double calculate(double a, double b, int n = 500);
private:
    void parseInputString();
private:
    IntegralCalc* _integral_calc;
    Parser* _parser;
    const char* _input;
};


#endif // CALCULATOR_H
