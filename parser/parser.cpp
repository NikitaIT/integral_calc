#include "parser_q.h"


template <typename T>
std::string toString(T val)
{
    std::ostringstream oss;
    oss<< val;
    return oss.str();
}
list<string> Parser::shunting_yard(const char *input)
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

void Parser::printParserList(){
    for ( const auto & item : _List )
    {

        printf("output: %s\n", item.c_str() );
    }
}
double Parser::generateFunction(double x){
    list<string> List = _List;
    //{"1","2","+","x","sin","+"};
    list<string>::iterator it = List.begin();
    while(it!=List.end())
    {

        it = std::find_if (it,
                              List.end(),
                              [](string s)->bool{return  !isdigit(s.c_str()[0]);});
        if(it==List.end())break;
    //      it - 100% функция
    //      is_func - sin
        if(is_func(*it))
        {
            it--;
            list<string>::iterator first = it;
            it++;
            string token = (string)(*it);
            double token_arg_val = atof(first->data());

            token=="sin"? *it = toString(sin(token_arg_val)):
            token=="cos"? *it = toString(cos(token_arg_val)):
            token=="acos"? *it = toString(acos(token_arg_val)):
            token=="asin"? *it = toString(asin(token_arg_val)):
            token=="tan"? *it = toString(tan(token_arg_val)):
            token=="cot"? *it = toString(1/ tan(token_arg_val)):
            token=="atan"? *it = toString(atan(token_arg_val)):
            token=="acot"? *it = toString(atan(1/token_arg_val)):
            token=="exp"? *it = toString(exp(token_arg_val)):
            token=="ln"||token=="log"? *it = toString(log(token_arg_val)):
            token=="sqrt"? *it = toString(sqrt(token_arg_val)):
            token=="sqrt3"? *it = toString(pow(token_arg_val,(1/3))):
            *it = toString(token_arg_val);
            List.erase(first);

        } else if(is_operator((string )(*it).c_str()))
        {
            it--;
            list<string>::iterator second = it;
            it--;
            list<string>::iterator first = it;
            it++;it++;
            string token = (string)(*it);
            token=="+"? *it = toString(atof(first->data()) + atof(second->data())):
            token=="-"? *it = toString(atof(first->data()) - atof(second->data())):
            token=="/"? *it = toString(atof(first->data()) / atof(second->data())):
            token=="*"? *it = toString(atof(first->data()) * atof(second->data())):
            token=="%"? *it = toString(atoi(first->data()) % atoi(second->data())):
            token=="="? *it = toString(atof(first->data()) == atof(second->data())):
                    *it=toString(atof(first->data()) + atof(second->data()));
            List.erase(first);
            List.erase(second);
        } else if((*it).c_str()[0]=='x')
        {
            (*it)=toString(x);
        } else if((*it).c_str()[0]=='-')
        {
            it++;
        }
//        for ( const auto & item : List )
//        {
//            printf("output: %s\n", item.c_str() );
//        }
    }
    return atof(List.begin()->data());//[=](double x){return sin(x);}; //Например, sin(x)
}
unsigned int Parser::op_arg_count(const string op)
{
    return  //
            op == "*" || op == "/" || op == "%" || op == "+" || op == "-" || op == "=" ? 2 :
                                                                                         //
                                                                                         op == "!" ? 1 :
                                                                                                     0;
    return 0;
}

int Parser::op_preced(const string op)
{
    return
            op == "!" ? 4 :
                        op == "*" || op == "/" || op == "%" ? 3 :
                                                              op == "+" || op == "-" ? 2 :
                                                                                       op == "=" ? 1 :
                                                                                                   0;
}

bool Parser::op_left_assoc(const string op)
{
    return
            op == "*" || op == "/" || op == "%" || op == "+" || op == "-" || op == "=" ? true :
                                                                                         op == "!" ? false :
                                                                                                     false;
}

bool Parser::is_func(const string token)
{
    return token=="sin"||token=="cos"||token=="acos"||token=="asin"||token=="tan"||
            token=="cot"||token=="atan"||token=="acot"||token=="exp"||token=="ln"||
            token=="sqrt"||token=="sqrt3"? true :
                                           false;
}
