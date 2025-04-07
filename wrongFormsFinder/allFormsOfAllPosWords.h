/**
 * @file allFormsOfAllPosWords.h
 * @brief Перечисления, определяющие формы слова.
 */

#ifndef ALLFORMSOFALLPOSWORDS_H
#define ALLFORMSOFALLPOSWORDS_H

#endif // ALLFORMSOFALLPOSWORDS_H

#define notSet 0

enum auxiliaryForAdj {
    more = 1,
    most = 2,
    notNeed = 3 
};

enum tenseOfVerb {
    presentSimple = 4,
    presentCont = 5,
    pastSimple = 6,
    pastCont = 7,
    presentPerf = 8,
    presentPerfCont = 9,
    pastPerf = 10,
    pastPerfCont = 11,
    futureSimple = 12,
    futureCont = 13,
    futurePerfSimple = 14,
    futurePerfCont = 15,
    futureSimpleInThePast = 16,
    futureContInThePast = 17,
    futurePerfInThePast = 18,
    futurePerfContInThePast = 19,
    undefined = 20
};

enum formOfVerb {
    infinitive = 21,
    verbBeAreAmForm = 22,
    present3P = 23,
    past = 24,
    preterite = 25,
    pastParticiple = 26,
    presentParticiple = 27
};

enum person {
    first = 28,
    third = 29,
    notThird = 30,
    notFirst = 31
};

enum number {
    singular = 32,
    plural = 33,
    uncountable = 34
};

enum caseOfNounAndPron {
    objective = 35,
    possessive = 36
};

enum formOfPron {
    nominative = 37,
    objectivePron = 38,
    mainForm = 39,
    absoluteForm = 40
};

enum formOfNumeral {
    cardinal = 41,
    ordinal = 42
};

enum formOfAdjective {
    positive = 43,
    comparative = 44,
    superlative = 45
};
