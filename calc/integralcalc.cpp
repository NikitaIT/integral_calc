#include "integralcalc.h"

double Rectangles_IntegralCalc::calculate(double a, double b, int n, Parser &parser) {
    cout << "Rectangles_IntegralCalc" << endl;
    int i;
    double result, h;
    result = 0;
    h = (b - a) / n; //Шаг сетки
    for(i = 0; i < n; i++)
    {
        result += parser.generateFunction(a + h * (i + 0.5)); //Вычисляем в средней точке и добавляем в сумму
    }
    result *= h;
    return result;
}

double Trapezoids_IntegralCalc::calculate(double a, double b, int n, Parser &parser) {
    cout << "Trapezoids_IntegralCalc" << endl;
    double h=(b-a)/n;
    double x,s;
    s=(parser.generateFunction(a)+parser.generateFunction(b))/2;
    for (x=a+h; x<b; x+=h)
    {
        s+=parser.generateFunction(x);
    }
    return s*h;
}
