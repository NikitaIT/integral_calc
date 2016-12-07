TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt
SOURCES += main.cpp \
    parser/parser.cpp \
    calc/integralcalc.cpp \
    calc/calculator.cpp

HEADERS += \
    include_lib.h \
    calc/integralcalc.h \
    calc/calculator.h \
    parser/parser_q.h

