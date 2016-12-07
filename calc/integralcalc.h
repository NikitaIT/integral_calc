#ifndef INTEGRALCALC_H
#define INTEGRALCALC_H
#include "include_lib.h"
#include "parser/parser_q.h"
using namespace std;
// Иерархия классов, определяющая алгоритмы вычисляющая интеграл
class IntegralCalc
{
  public:
    virtual ~IntegralCalc() {}
    virtual double calculate( double a,double b,int n= 500,Parser &parser= * new Parser("")) = 0;//function<double(double)> A=0 double (*generateFunction)(double)= [](double x){return x;}
};
class Trapezoids_IntegralCalc : public IntegralCalc
{
  public:
    double calculate( double a,double b,int n= 500,Parser &parser= * new Parser(""));
};
class Rectangles_IntegralCalc : public IntegralCalc
{
  public:
    double calculate(double a, double b, int n = 500,Parser &parser= * new Parser(""));
};


#endif // INTEGRALCALC_H
