QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  \
           ../wrongFormsFinder/numeral.cpp \
           test_NumeralFormAllForms.cpp \
           ../wrongFormsFinder/WordForm.cpp \
           ../wrongFormsFinder/Word.cpp \
           ../wrongFormsFinder/binsrch.c \
           ../wrongFormsFinder/morph.c \
           ../wrongFormsFinder/search.c \
           ../wrongFormsFinder/wnglobal.c \
           ../wrongFormsFinder/wnhelp.c \
           ../wrongFormsFinder/wnrtl.c \
           ../wrongFormsFinder/wnutil.c \

HEADERS += ../wrongFormsFinder/numeral.h
HEADERS += ../wrongFormsFinder/WordForm.h
HEADERS += ../wrongFormsFinder/Word.h
HEADERS += ../wrongFormsFinder/wn.h
