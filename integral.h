#ifndef INTEGRAL_H
#define INTEGRAL_H
#include "include_lib.h"
using namespace std;
class Integral
{
public:
    Integral(){}
    double integralFunction(double x) //Подынтегральная функция
    {
        return atan(x); //Например, sin(x)
    }
    void printIntegralValue(double value, int precision)
    {
        std::stringstream out_stream;
        out_stream << std::setprecision(precision) << value;
        std::string out = out_stream.str();

        cout << "IntegralValue is a:"<< (float)atof(out.c_str()) << endl;
    }
};

class Parser
{
public:
    Parser(const char * input):_List(shunting_yard(input)){printParserList();}
    #define is_operator(c) (c == "+" || c == "-" || c == "/" || c == "*" || c == "!" || c == "%" || c == "=")
    #define is_leter(c) ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
    list<string> shunting_yard(const char * input)
    {
        list<string> List;
        const char * strpos = input, *strend = input + strlen(input);
        string c;
        stack<string> Stack;
        while(strpos < strend)
        {
            c = *strpos;
            std::cout<<strpos;
            if(c != " ")
            {
                // Если токен является числом (идентификатором), то добавить его в очередь вывода.
                if(isdigit(c[0]))
                {
                    string  val = "";
                    while (isdigit(*strpos)&&(strpos < strend))
                    {
                        val += *strpos;
                        ++strpos;
                    }
                    --strpos;
                    List.push_back(val);
                }
                else if(is_leter(c[0]))
                {
                    string  val = "";
                    string a = c;
                    while (is_leter(a[0])&&(strpos < strend))
                    {
                        val += *strpos;
                        ++strpos;
                        a = *strpos;
                    }
                    --strpos;
                    if(c[0] != *strpos){
                        Stack.push(val);
                    }else{
                        List.push_back(val);
                    }
                }
                //Если токен - разделитель аргументов функции (запятая):
                else if(c[0] == ',')
                {
                    bool pe = false;
                    while(!Stack.empty())
                    {
                        if(Stack.top() != "(")
                        {
                            // Пока на вершине не левая круглая скобка,
                            // перекладывать операторы из стека в очередь вывода.
                            List.push_back(Stack.top());
                            Stack.pop();
                        } else
                        {
                            pe = true;
                            break;
                        }
                    }
                    // Если не была достигнута левая круглая скобка, либо разделитель не в том месте
                    // либо была пропущена скобка
                    if(!pe)
                    {
                        printf("Error: separator or parentheses mismatched\n");
                        List.clear();
                        return List;
                    }
                }
                // Если токен оператор op1, то:
                else if(is_operator((string )c))
                {
                    while(!Stack.empty())
                    {
                        // Пока на вершине стека присутствует токен оператор op2,
                        // а также оператор op1 лево-ассоциативный и его приоритет меньше или такой же чем у оператора op2,
                        // или оператор op1 право-ассоциативный и его приоритет меньше чем у оператора op2
                        if(is_operator(Stack.top()) &&
                                ((op_left_assoc((string )c) && (op_preced((string )c) <= op_preced(Stack.top()))) ||
                                 (!op_left_assoc((string )c) && (op_preced((string )c) < op_preced(Stack.top())))))
                        {
                            // Переложить оператор op2 из стека в очередь вывода.
                            List.push_back(Stack.top());
                            Stack.pop();
                        }
                        else
                        {
                            break;
                        }
                    }
                    // положить в стек оператор op1
                    Stack.push((string )c);
                }
                // Если токен - левая круглая скобка, то положить его в стек.
                else if(c[0] == '(')
                {
                    Stack.push((string )c);
                }
                // Если токен - правая круглая скобка:
                else if(c[0] == ')')
                {
                    bool pe = false;
                    // До появления на вершине стека токена "левая круглая скобка"
                    // перекладывать операторы из стека в очередь вывода.
                    while(!Stack.empty())
                    {
                        if(Stack.top() != "(")
                        {
                            // Пока на вершине не левая круглая скобка,
                            // перекладывать операторы из стека в очередь вывода.
                            List.push_back(Stack.top());
                            Stack.pop();
                        } else
                        {
                            pe = true;
                            break;
                        }
                    }
                    // Если стек кончится до нахождения токена левая круглая скобка, то была пропущена скобка.
                    if(!pe)
                    {
                        printf("Error: parentheses mismatched\n");
                        List.clear();
                        return List;
                    }
                    // выкидываем токен "левая круглая скобка" из стека (не добавляем в очередь вывода).
                    Stack.pop();
                    // Если на вершине стека токен - функция, положить его в очередь вывода.
                    if(!Stack.empty())
                    {
                        if(sizeof (Stack.top()) - 1 > 1)
                        {
                            List.push_back(Stack.top());
                            Stack.pop();
                        }
                    }
                }
                else
                {
                    printf("Unknown token %c\n", c[0]);
                    List.clear();
                    return List; // Unknown token
                }
            }
            strpos++;
        }
        // Когда не осталось токенов на входе:
        // Если в стеке остались токены:
        while(!Stack.empty())
        {
            if(Stack.top() == "(" || Stack.top() == ")")
            {
                printf("Error: parentheses mismatched\n");
                List.clear();
                return List;
            }
            List.push_back(Stack.top());
            Stack.pop();
        }
        return List;
    }
    void printParserList(){
        for ( const auto & item : _List )
        {

            printf("output: %s\n", item.c_str() );
        }
    }
    auto generateFunction(){
        return [=](double x){return sin(x);}; //Например, sin(x)
    }
private:
    /**
     * Сколько аргументов у оператора?
     * @brief op_arg_count
     * @param op
     * @return uint {2 аргумента,1 аргумент,0 аргументов}
     */
    unsigned int op_arg_count(const string op)
    {
        return  //
                op == "*" || op == "/" || op == "%" || op == "+" || op == "-" || op == "=" ? 2 :
                //
                op == "!" ? 1 :
                0;
        return 0;
    }
    /**
     * Приоритет Операторов
     * @brief op_preced
     * @param op
     * @return int {4 {!} правая,3 {*,/,%} левая,2 {+,-} левая, 1 {=} левая}
     */
    int op_preced(const string op)
    {
        return
                op == "!" ? 4 :
                op == "*" || op == "/" || op == "%" ? 3 :
                op == "+" || op == "-" ? 2 :
                op == "=" ? 1 :
                0;
    }
    /**
     * Ассоциативность Операторов
     * @brief op_left_assoc
     * @param op
     * @return bool {1 - лево, 2 - право}
     */
    bool op_left_assoc(const string op)
    {
        return
                op == "*" || op == "/" || op == "%" || op == "+" || op == "-" || op == "=" ? true :
                op == "!" ? false :
                false;
    }
    /**
     * @brief is_func
     * @param token
     * @return bool {true - если функция }
     */
    bool is_func(const string &token)
    {
    return token=="sin"||token=="cos"||token=="acos"||token=="asin"||token=="tan"||
                token=="cot"||token=="atan"||token=="acot"||token=="exp"||token=="ln"||
                token=="sqrt"||token=="sqrt3"? true :
                                               false;
    }
private:
    list<string> _List;
};
// Иерархия классов, определяющая алгоритмы вычисляющая интеграл
class IntegralCalc
{
  public:
    virtual ~IntegralCalc() {}
    virtual double calculate( double a,double b,int n= 500,function<double(double)> A=0) = 0;
};

class Trapezoids_IntegralCalc : public IntegralCalc
{
  public:
    double calculate( double a,double b,int n= 500,function<double(double)> generateFunction=0) {
        cout << "Trapezoids_IntegralCalc" << endl;
        double h=(b-a)/n;
        double x,s;
        s=(generateFunction(a)+generateFunction(b))/2;
        for (x=a+h; x<b; x+=h)
        {
            s+=generateFunction(x);
        }
        return s*h;
    }
};
class Rectangles_IntegralCalc : public IntegralCalc
{
  public:
    double calculate(double a, double b, int n = 500,function<double(double)> generateFunction=0) {
        cout << "Rectangles_IntegralCalc" << endl;
        int i;
        double result, h;
        result = 0;
        h = (b - a) / n; //Шаг сетки
        for(i = 0; i < n; i++)
        {
            result += generateFunction(a + h * (i + 0.5)); //Вычисляем в средней точке и добавляем в сумму
        }
        result *= h;
        return result;
    }
};

// Класс для использования
class Calculator
{
public:
    Calculator( IntegralCalc* comp): _integral_calc(comp) {}
    ~Calculator() { delete _input; delete _integral_calc; delete _parser; }
    void setInputString(const char * input){_input = input; parseInputString();}
    double calculate(double a, double b, int n = 500) {
        return _integral_calc->calculate(a,b,n,[](double x) ->double {return sin(x);});
    }
private:
    void parseInputString(){_parser = new Parser(_input); }
private:
    IntegralCalc* _integral_calc;
    Parser* _parser;
    const char* _input;
};
#endif // INTEGRAL_H
