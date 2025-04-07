QT = core

CONFIG += c++17 cmdline

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        WordForm.cpp \
        adjective.cpp \
        auxiliary.cpp \
        filedataerror.cpp \
        filesprocessing.cpp \
        inputdataerror.cpp \
        linkedsentences.cpp \
        main.cpp \
        misstakedeterminer.cpp \
        noun.cpp \
        numeral.cpp \
        pair.cpp \
        pronoun.cpp \
        sentence.cpp \
        verb.cpp \
        word.cpp \
        binsrch.c \
        morph.c \
        search.c \
        wnglobal.c \
        wnhelp.c \
        wnrtl.c \
        wnutil.c \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    WordForm.h \
    adjective.h \
    allFormsOfAllPosWords.h \
    auxiliary.h \
    filedataerror.h \
    filesprocessing.h \
    inputdataerror.h \
    linkedsentences.h \
    misstakedeterminer.h \
    noun.h \
    numeral.h \
    pair.h \
    postags.h \
    pronoun.h \
    sentence.h \
    sentencesProcessingCodes.h \
    verb.h \
    word.h \
    wn.h \

