
#include "calc/integralcalc.h"
#include "parser/parser_q.h"
#include "calc/calculator.h"

using namespace std;


/**
 *  @brief TZ
 *  Разработать программу вычисления определенного интеграла
 *  методами трапеций и прямоугольников для функции,
 *  задаваемой в инфиксной форме с клавиатуры.
 *  Выбор метода интегрирования и пределов интегрирования
 *  так же задается с клавиатуры. Вычисления проводить в постфиксной форме.
 *  Для преобразования инфиксной формы записи в постфиксную форму использовать стек.
 */
int f(int &arr){cout <<arr;}
int main()
{
    cout << "Integral calc!" << endl;
    string input ="";
    //sin(123 - 3 * 5 + x/cos(9))
    //integral[0,5] sin(123 - 3 * 5 + x/cos(9))
    printf("input: %s\n", input.c_str());
    cout << "print func:";
    //getline(cin,input);
    Calculator* p_calculator = 0;
    char method='1';
    while (method != '0') {
        cout << " Exet:0; Choose method(t or r):";
        cin>>method;
        cout<< endl;
        if(method=='r') {
            p_calculator = new Calculator( new Rectangles_IntegralCalc);
        } else if(method=='t'){
            p_calculator = new Calculator( new Trapezoids_IntegralCalc);
        } else {break;}
        method='1';
        p_calculator->setInputString(input.c_str());
        cout <<"integral_0^5 sin(123-3 5+x/(cos(9))) dx = cos(9) (cos(108)-cos(108+5 sec(9))) ≈ -0.70578"<< " : expected value" <<endl;
        cout << p_calculator->calculate(0,5)<< endl;
    }

    delete p_calculator;



    //    cout <<Identity(zz)<< endl; // 3
    //[](double x) ->double {return sin(x);}
//        auto Identity = [](auto x)->decltype(x) { if(is_function(x))return x(); else return x; };
//        auto func = Identity;
//        cout <<func(5)<< endl;

//        auto mul = [](auto x)->decltype(x) { return x; };
//        cout <<func(mul(5))<< " : " << endl;
//        func = reinterpret_cast<auto> func(mul);
//        func =  mul(func);
//        cout <<func(5)<< endl;
//        function<int(int)> func1 = mul;
//        cout <<func1(5)<< endl;

//        function<function<int (int)> (int)> lambdaGen =
//                [] (int _val3) -> function<int (int)>
//                {
//                    return
//                            [_val3] (int _val2) -> function<int (int)>
//                            {
//                                return [_val2] (int _val1) -> int { return _val1 + _val2; };
//                            };
//                };
//       cout <<lambdaGen(3)(5)(3);
//        function<int (function<int (int)>)> lambdaGen2 =
//                    [] (a _val2) -> function<int (function<int (int)>)>
//                    {
//                        return [_val2] (int _val1) -> int { return _val1 + _val2; };
//                    };

//        auto x = [](auto f) {return f + 5; };
//          function<double(function<double(double)>, double)> lambdaGen3 = [](function<double(double)> val, double a)->double {return val(a); };
//          cout << lambdaGen3(x, 5)<< endl;

    int qy = 100;
    int qy1 = 10;
    auto y = [&](auto &a,auto b) {return a+qy+b; };
    auto rez = y(qy1,0);
    auto x = [&](auto f) {return f; };
    auto s = x(rez);
    cout <<s<< endl;
    qy = 200;
    qy1 = 2000;
    cout <<s<< endl;
    auto lambdaGen = [](auto func, double a)->double {return func(a); };
    cout << lambdaGen(x, 7) << endl;

//        auto p5 = [](auto x, auto y) {
//          return [](auto X,auto Y)->int {return x(X) * y(Y);};
//        };

//        auto mul = [](auto x, auto y) {
//          return [](auto X,auto Y)->int {return x(X) * y(Y);};
//        };

//        if(1) func = Identity(func);
//        if(1) func = mul(func,7);
//        cout <<func(5)<< endl;
        //cout <<Identit(zz)<< endl; // 3
    return 0;
}

