#include "include_lib.h"

//Integral::Integral()
//{

//}

//bool execution_order(const char * input)
//{
////        printf("order: (arguments in reverse order)\n");
////        const char * strpos = input, *strend = input + strlen(input);
////        char c, res[4];
////        unsigned int sl = 0, sc, stack[32], rn = 0;
////        // Пока на входе остались токены
////        while(strpos < strend)
////        {
////            // Прочитать следующий токен
////            c = *strpos;
////            // Если токен - значение или идентификатор
////            if(is_ident(c))
////            {
////            // Поместить его в стек
////                stack[sl] = c;
////                ++sl;
////            }
////            // В противном случае, токен - оператор (здесь под оператором понимается как оператор, так и название функции)
////            else if(is_operator(c) || is_function(c))
////            {
////                sprintf(res, "_%02d", rn);
////                printf("%s = ", res);
////                ++rn;
////                // Априори известно, что оператор принимает n аргументов
////                unsigned int nargs = op_arg_count(c);
////                            unsigned int Tnargs = nargs;
////                // Если в стеке значений меньше, чем n
////                if(sl < nargs)
////                {
////                    // (ошибка) Недостаточное количество аргументов в выражении.
////                    return false;
////                }
////                // В противном случае, взять последние n аргументов из стека
////                // Вычислить оператор, взяв эти значения в качестве аргументов
////                if(is_function(c))
////                {
////                    printf("%c(", c);
////                    while(nargs > 0)
////                    {
////                        sc = stack[sl - nargs];
////                        if(nargs > 1)
////                        {
////                            printf("%s, ", &sc);
////                        }
////                        else
////                        {
////                            printf("%s)\n", &sc);
////                        }
////                        --nargs;
////                    }
////                                    sl -= Tnargs;
////                }
////                else
////                {
////                    if(nargs == 1)
////                    {
////                        sc = stack[sl - 1];
////                        sl--;
////                        printf("%c %s;\n", c, &sc);
////                    }
////                    else
////                    {
////                        sc = stack[sl - 2];
////                        printf("%s %c ", &sc, c);
////                        sc = stack[sl - 1];
////                        printf("%s;\n",&sc);
////                                            sl -= 2;

////                    }
////                }
////                // Если получены результирующие значения, поместить таковые в стек.
////                stack[sl] = *(unsigned int*)res;
////                ++sl;
////            }
////            ++strpos;
////        }
////        // Если в стеке осталось лишь одно значение,
////        // оно будет являться результатом вычислений.
////        if(sl == 1)
////        {
////            sc = stack[sl - 1];
////            sl--;
////            printf("%s is a result\n", &sc);
////            return true;
////        }
////        // Если в стеке большее количество значений,
////        // (ошибка) Пользователь ввёл слишком много значений.
//    return false;
//}
