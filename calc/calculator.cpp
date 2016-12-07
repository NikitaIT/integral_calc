#include "calculator.h"



void Calculator::setInputString(const char *input){_input = input; parseInputString();}
void Calculator::parseInputString(){_parser = new Parser(_input); }
double Calculator::calculate(double a, double b, int n) {
    return _integral_calc->calculate(a,b,n,*_parser);//[](double x) ->double {return sin(x);}
}


