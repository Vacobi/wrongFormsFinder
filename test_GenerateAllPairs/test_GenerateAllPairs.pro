QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  \
           ../wrongFormsFinder/linkedsentences.cpp \
    test_GenerateAllPairs.cpp \
    ../wrongFormsFinder/sentence.cpp \
    ../wrongFormsFinder/pair.cpp \
    ../wrongFormsFinder/WordForm.cpp \
    ../wrongFormsFinder/Word.cpp \
    ../wrongFormsFinder/binsrch.c \
    ../wrongFormsFinder/morph.c \
    ../wrongFormsFinder/search.c \
    ../wrongFormsFinder/wnglobal.c \
    ../wrongFormsFinder/wnhelp.c \
    ../wrongFormsFinder/wnrtl.c \
    ../wrongFormsFinder/wnutil.c \
    ../wrongFormsFinder/adjective.cpp \
    ../wrongFormsFinder/auxiliary.cpp \
    ../wrongFormsFinder/noun.cpp \
    ../wrongFormsFinder/pronoun.cpp \
    ../wrongFormsFinder/verb.cpp \

HEADERS += ../wrongFormsFinder/linkedsentences.h
HEADERS += ../wrongFormsFinder/sentence.h
HEADERS += ../wrongFormsFinder/WordForm.h
HEADERS += ../wrongFormsFinder/Word.h
HEADERS += ../wrongFormsFinder/wn.h
HEADERS += ../wrongFormsFinder/adjective.h
HEADERS += ../wrongFormsFinder/auxiliary.h
HEADERS += ../wrongFormsFinder/noun.h
HEADERS += ../wrongFormsFinder/pronoun.h
HEADERS += ../wrongFormsFinder/verb.h
HEADERS += ../wrongFormsFinder/pair.h
