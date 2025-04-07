#include <QCoreApplication>
#include <QtTest/QtTest>

#include "../wrongFormsFinder/linkedsentences.h"
#include "../wrongFormsFinder/adjective.h"
#include "../wrongFormsFinder/auxiliary.h"
#include "../wrongFormsFinder/noun.h"
#include "../wrongFormsFinder/numeral.h"
#include "../wrongFormsFinder/pronoun.h"
#include "../wrongFormsFinder/verb.h"

class LinkSentences: public QObject
{
    Q_OBJECT

private slots:
    void linkSentences_data();
    void linkSentences();

    void initTestCase();
};

void LinkSentences::linkSentences_data()
{
    QTest::addColumn<Sentence>("correctSentence");
    QTest::addColumn<Sentence>("verifiedSentence");
    QTest::addColumn<QList<QSet<Pair>>>("expPairsSets");

    Sentence correctSentence, verifiedSentence;
    QList<QSet<Pair>> allExpPairsLists;
    QSet<Pair> tmpPairsSet;
    Pair currentPair;
    WordForm tmpCorrectForm, tmpVerifiedForm;
    QList<int> tmpCorrectAux, tmpVerifiedAux;

//    // 1 Тест. Каждому слову правильного предложения соответствует только 1 форма слова из проверяемого предложения
//    correctSentence.clear();
//    verifiedSentence.clear();

//    correctSentence.addWordToEnd(new Pronoun("i"));
//    correctSentence.addWordToEnd(new Verb("have"));
//    correctSentence.addWordToEnd(new Word("a"));
//    correctSentence.addWordToEnd(new Adjective("positive"));
//    correctSentence.addWordToEnd(new Noun("attitude"));

//    verifiedSentence.addWordToEnd(new Word("positive"));
//    verifiedSentence.addWordToEnd(new Word("attitude"));
//    verifiedSentence.addWordToEnd(new Word("i"));
//    verifiedSentence.addWordToEnd(new Word("have"));

//    // 1 пара
//    tmpCorrectForm.setWordForm(objective, nominative, singular, notSet);
//    tmpVerifiedForm.setWordForm(objective, nominative, singular, notSet);

//    tmpCorrectAux.clear();
//    tmpVerifiedAux.clear();

//    currentPair.setAllParameters(0, tmpCorrectAux, tmpCorrectForm, // correct
//                                 2, tmpVerifiedAux, tmpVerifiedForm, // verified
//                                 pron, 0);
//    tmpPairsSet.insert(currentPair);

//    // 2 пара
//    tmpCorrectForm.setWordForm(presentSimple, notThird, infinitive, notSet);
//    tmpVerifiedForm.setWordForm(presentSimple, notThird, infinitive, notSet);

//    tmpCorrectAux.clear();
//    tmpVerifiedAux.clear();

//    currentPair.setAllParameters(1, tmpCorrectAux, tmpCorrectForm, // correct
//                                 3, tmpVerifiedAux, tmpVerifiedForm, // verified
//                                 verb, 0);
//    tmpPairsSet.insert(currentPair);

//    // 3 пара
//    tmpCorrectForm.setWordForm(positive, notSet, notSet, notNeed);
//    tmpVerifiedForm.setWordForm(positive, notSet, notSet, notNeed);

//    tmpCorrectAux.clear();
//    tmpVerifiedAux.clear();

//    currentPair.setAllParameters(3, tmpCorrectAux, tmpCorrectForm, // correct
//                                 0, tmpVerifiedAux, tmpVerifiedForm, // verified
//                                 adj, 0);
//    tmpPairsSet.insert(currentPair);

//    // 4 пара
//    tmpCorrectForm.setWordForm(singular, objective, notSet, notSet);
//    tmpVerifiedForm.setWordForm(singular, objective, notSet, notSet);

//    tmpCorrectAux.clear();
//    tmpVerifiedAux.clear();

//    currentPair.setAllParameters(4, tmpCorrectAux, tmpCorrectForm, // correct
//                                 1, tmpVerifiedAux, tmpVerifiedForm, // verified
//                                 noun, 0);
//    tmpPairsSet.insert(currentPair);

//    allExpPairsLists.append(tmpPairsSet);

//    QTest::newRow("onePairToEveryWord") <<
//        correctSentence << verifiedSentence << allExpPairsLists;

    // 2 Тест. Имеются вспомогательные в проверяемом предложении
    correctSentence.clear();
    verifiedSentence.clear();
    tmpPairsSet.clear();
    allExpPairsLists.clear();

    correctSentence.addWordToEnd(new Pronoun("i"));
    correctSentence.addWordToEnd(new Verb("have"));
    correctSentence.addWordToEnd(new Numeral("five"));
    correctSentence.addWordToEnd(new Noun("apples"));

    verifiedSentence.addWordToEnd(new Word("i"));
    verifiedSentence.addWordToEnd(new Word("have"));
    verifiedSentence.addWordToEnd(new Word("had"));
    verifiedSentence.addWordToEnd(new Word("five"));
    verifiedSentence.addWordToEnd(new Word("apples"));

    // 1 пара
    tmpCorrectForm.setWordForm(objective, nominative, singular, notSet);
    tmpVerifiedForm.setWordForm(objective, nominative, singular, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(0, tmpCorrectAux, tmpCorrectForm, // correct
                                 0, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 pron, 0);
    tmpPairsSet.insert(currentPair);

    // 2 пара
    tmpCorrectForm.setWordForm(presentSimple, notThird, infinitive, notSet);
    tmpVerifiedForm.setWordForm(presentPerf, notThird, pastParticiple, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();
    tmpVerifiedAux.append(1);

    currentPair.setAllParameters(1, tmpCorrectAux, tmpCorrectForm, // correct
                                 2, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 verb, 80);
    tmpPairsSet.insert(currentPair);

    // 3 пара
    tmpCorrectForm.setWordForm(cardinal, notSet, notSet, notSet);
    tmpVerifiedForm.setWordForm(cardinal, notSet, notSet, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(2, tmpCorrectAux, tmpCorrectForm, // correct
                                 3, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 num, 0);
    tmpPairsSet.insert(currentPair);

    // 4 пара
    tmpCorrectForm.setWordForm(plural, objective, notSet, notSet);
    tmpVerifiedForm.setWordForm(plural, objective, notSet, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(3, tmpCorrectAux, tmpCorrectForm, // correct
                                 4, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 noun, 0);
    tmpPairsSet.insert(currentPair);

    allExpPairsLists.append(tmpPairsSet);

    QTest::newRow("auxiliariesInVerifiedSentence") <<
        correctSentence << verifiedSentence << allExpPairsLists;

    // 3 Тест. Имеются вспомогательные слова у глагола в правильном и проверяемом предложении
    correctSentence.clear();
    verifiedSentence.clear();
    tmpPairsSet.clear();
    allExpPairsLists.clear();

    correctSentence.addWordToEnd(new Pronoun("i"));
    correctSentence.addWordToEnd(new Auxiliary("will"));
    correctSentence.addWordToEnd(new Verb("have"));
    correctSentence.addWordToEnd(new Numeral("five"));
    correctSentence.addWordToEnd(new Noun("apples"));

    verifiedSentence.addWordToEnd(new Word("i"));
    verifiedSentence.addWordToEnd(new Word("have"));
    verifiedSentence.addWordToEnd(new Word("had"));
    verifiedSentence.addWordToEnd(new Word("five"));
    verifiedSentence.addWordToEnd(new Word("apples"));

    // 1 пара
    tmpCorrectForm.setWordForm(objective, nominative, singular, notSet);
    tmpVerifiedForm.setWordForm(objective, nominative, singular, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(0, tmpCorrectAux, tmpCorrectForm, // correct
                                 0, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 pron, 0);
    tmpPairsSet.insert(currentPair);

    // 2 пара
    tmpCorrectForm.setWordForm(futureSimple, notThird, infinitive, notSet);
    tmpVerifiedForm.setWordForm(presentPerf, notThird, pastParticiple, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();
    tmpCorrectAux.append(1);
    tmpVerifiedAux.append(1);

    currentPair.setAllParameters(2, tmpCorrectAux, tmpCorrectForm, // correct
                                 2, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 verb, 80);
    tmpPairsSet.insert(currentPair);

    // 3 пара
    tmpCorrectForm.setWordForm(cardinal, notSet, notSet, notSet);
    tmpVerifiedForm.setWordForm(cardinal, notSet, notSet, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(3, tmpCorrectAux, tmpCorrectForm, // correct
                                 3, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 num, 0);
    tmpPairsSet.insert(currentPair);

    // 4 пара
    tmpCorrectForm.setWordForm(plural, objective, notSet, notSet);
    tmpVerifiedForm.setWordForm(plural, objective, notSet, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(4, tmpCorrectAux, tmpCorrectForm, // correct
                                 4, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 noun, 0);
    tmpPairsSet.insert(currentPair);

    allExpPairsLists.append(tmpPairsSet);

    QTest::newRow("auxiliariesInCorrectAndVerifiedSentence") <<
        correctSentence << verifiedSentence << allExpPairsLists;

    // 4 Тест. Имеются вспомогательные слова у глагола только в правильном предложении
    correctSentence.clear();
    verifiedSentence.clear();
    tmpPairsSet.clear();
    allExpPairsLists.clear();

    correctSentence.addWordToEnd(new Pronoun("i"));
    correctSentence.addWordToEnd(new Auxiliary("will"));
    correctSentence.addWordToEnd(new Verb("have"));
    correctSentence.addWordToEnd(new Numeral("five"));
    correctSentence.addWordToEnd(new Noun("apples"));

    verifiedSentence.addWordToEnd(new Word("i"));
    verifiedSentence.addWordToEnd(new Word("have"));
    verifiedSentence.addWordToEnd(new Word("five"));
    verifiedSentence.addWordToEnd(new Word("apples"));

    // 1 пара
    tmpCorrectForm.setWordForm(objective, nominative, singular, notSet);
    tmpVerifiedForm.setWordForm(objective, nominative, singular, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(0, tmpCorrectAux, tmpCorrectForm, // correct
                                 0, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 pron, 0);
    tmpPairsSet.insert(currentPair);

    // 2 пара
    tmpCorrectForm.setWordForm(futureSimple, notThird, infinitive, notSet);
    tmpVerifiedForm.setWordForm(presentSimple, notThird, infinitive, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();
    tmpCorrectAux.append(1);

    currentPair.setAllParameters(2, tmpCorrectAux, tmpCorrectForm, // correct
                                 1, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 verb, 35);
    tmpPairsSet.insert(currentPair);

    // 3 пара
    tmpCorrectForm.setWordForm(cardinal, notSet, notSet, notSet);
    tmpVerifiedForm.setWordForm(cardinal, notSet, notSet, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(3, tmpCorrectAux, tmpCorrectForm, // correct
                                 2, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 num, 0);
    tmpPairsSet.insert(currentPair);

    // 4 пара
    tmpCorrectForm.setWordForm(plural, objective, notSet, notSet);
    tmpVerifiedForm.setWordForm(plural, objective, notSet, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(4, tmpCorrectAux, tmpCorrectForm, // correct
                                 3, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 noun, 0);
    tmpPairsSet.insert(currentPair);

    allExpPairsLists.append(tmpPairsSet);

    QTest::newRow("auxiliariesInCorrectSentence") <<
        correctSentence << verifiedSentence << allExpPairsLists;

    // 5 Тест. Имеются вспомогательные слова у прилагательного
    correctSentence.clear();
    verifiedSentence.clear();
    tmpPairsSet.clear();
    allExpPairsLists.clear();

    correctSentence.addWordToEnd(new Word("the"));
    correctSentence.addWordToEnd(new Auxiliary("most"));
    correctSentence.addWordToEnd(new Adjective("expensive"));
    correctSentence.addWordToEnd(new Noun("car"));

    verifiedSentence.addWordToEnd(new Word("the"));
    verifiedSentence.addWordToEnd(new Word("more"));
    verifiedSentence.addWordToEnd(new Word("expensive"));
    verifiedSentence.addWordToEnd(new Word("car"));

    // 1 пара
    tmpCorrectForm.setWordForm(superlative, notSet, notSet, most);
    tmpVerifiedForm.setWordForm(comparative, notSet, notSet, more);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();
    tmpCorrectAux.append(1);
    tmpVerifiedAux.append(1);

    currentPair.setAllParameters(2, tmpCorrectAux, tmpCorrectForm,
                                 2, tmpVerifiedAux, tmpVerifiedForm,
                                 adj, 100);
    tmpPairsSet.insert(currentPair);

    // 2 пара
    tmpCorrectForm.setWordForm(singular, objective, notSet, notSet);
    tmpVerifiedForm.setWordForm(singular, objective, notSet, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(3, tmpCorrectAux, tmpCorrectForm, // correct
                                 3, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 noun, 0);
    tmpPairsSet.insert(currentPair);

    allExpPairsLists.append(tmpPairsSet);

    QTest::newRow("adjectiveWithAuxiliaries") <<
        correctSentence << verifiedSentence << allExpPairsLists;

    // 6 Тест. Ошибка в числительном
    correctSentence.clear();
    verifiedSentence.clear();
    tmpPairsSet.clear();
    allExpPairsLists.clear();

    correctSentence.addWordToEnd(new Pronoun("he"));
    correctSentence.addWordToEnd(new Verb("is"));
    correctSentence.addWordToEnd(new Numeral("first"));

    verifiedSentence.addWordToEnd(new Word("he"));
    verifiedSentence.addWordToEnd(new Word("is"));
    verifiedSentence.addWordToEnd(new Word("one"));

    // 1 пара
    tmpCorrectForm.setWordForm(objective, nominative, singular, notSet);
    tmpVerifiedForm.setWordForm(objective, nominative, singular, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(0, tmpCorrectAux, tmpCorrectForm, // correct
                                 0, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 pron, 0);
    tmpPairsSet.insert(currentPair);

    // 2 пара
    tmpCorrectForm.setWordForm(presentSimple, third, infinitive, notSet);
    tmpVerifiedForm.setWordForm(presentSimple, third, infinitive, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(1, tmpCorrectAux, tmpCorrectForm, // correct
                                 1, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 verb, 0);
    tmpPairsSet.insert(currentPair);

    // 3 пара
    tmpCorrectForm.setWordForm(ordinal, notSet, notSet, notSet);
    tmpVerifiedForm.setWordForm(cardinal, notSet, notSet, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(2, tmpCorrectAux, tmpCorrectForm, // correct
                                 2, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 num, 100);
    tmpPairsSet.insert(currentPair);

    allExpPairsLists.append(tmpPairsSet);

    QTest::newRow("misstakeInNumeral") <<
        correctSentence << verifiedSentence << allExpPairsLists;

    // 7 Тест. Ошибка в существительном
    correctSentence.clear();
    verifiedSentence.clear();
    tmpPairsSet.clear();
    allExpPairsLists.clear();

    correctSentence.addWordToEnd(new Numeral("five"));
    correctSentence.addWordToEnd(new Noun("dresses"));

    verifiedSentence.addWordToEnd(new Numeral("five"));
    verifiedSentence.addWordToEnd(new Noun("dress's"));

    // 1 пара
    tmpCorrectForm.setWordForm(cardinal, notSet, notSet, notSet);
    tmpVerifiedForm.setWordForm(cardinal, notSet, notSet, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(0, tmpCorrectAux, tmpCorrectForm, // correct
                                 0, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 num, 0);
    tmpPairsSet.insert(currentPair);

    // 2 пара
    tmpCorrectForm.setWordForm(plural, objective, notSet, notSet);
    tmpVerifiedForm.setWordForm(singular, possessive, notSet, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(1, tmpCorrectAux, tmpCorrectForm, // correct
                                 1, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 noun, 100);
    tmpPairsSet.insert(currentPair);

    allExpPairsLists.append(tmpPairsSet);

    QTest::newRow("misstakeInNoun") <<
        correctSentence << verifiedSentence << allExpPairsLists;

    // 8 Тест. Несколько вариантов согласования с ошибочной парой
    correctSentence.clear();
    verifiedSentence.clear();
    tmpPairsSet.clear();
    allExpPairsLists.clear();

    correctSentence.addWordToEnd(new Pronoun("he"));
    correctSentence.addWordToEnd(new Verb("read"));
    correctSentence.addWordToEnd(new Word("a"));
    correctSentence.addWordToEnd(new Noun("book"));

    verifiedSentence.addWordToEnd(new Word("a"));
    verifiedSentence.addWordToEnd(new Word("book"));
    verifiedSentence.addWordToEnd(new Word("he"));
    verifiedSentence.addWordToEnd(new Word("read"));

    // 1 вариант согласования
    // 1 пара
    tmpCorrectForm.setWordForm(objective, nominative, singular, notSet);
    tmpVerifiedForm.setWordForm(objective, nominative, singular, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(0, tmpCorrectAux, tmpCorrectForm, // correct
                                 2, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 pron, 0);
    tmpPairsSet.insert(currentPair);

    // 2 пара
    tmpCorrectForm.setWordForm(presentSimple, notThird, infinitive, notSet);
    tmpVerifiedForm.setWordForm(presentSimple, notThird, infinitive, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(1, tmpCorrectAux, tmpCorrectForm, // correct
                                 3, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 verb, 0);
    tmpPairsSet.insert(currentPair);

    // 3 пара
    tmpCorrectForm.setWordForm(singular, objective, notSet, notSet);
    tmpVerifiedForm.setWordForm(singular, objective, notSet, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(3, tmpCorrectAux, tmpCorrectForm, // correct
                                 1, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 noun, 0);
    tmpPairsSet.insert(currentPair);

    allExpPairsLists.append(tmpPairsSet);

    // 2 вариант согласования
    tmpPairsSet.clear();
    // 1 пара
    tmpCorrectForm.setWordForm(objective, nominative, singular, notSet);
    tmpVerifiedForm.setWordForm(objective, nominative, singular, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(0, tmpCorrectAux, tmpCorrectForm, // correct
                                 2, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 pron, 0);
    tmpPairsSet.insert(currentPair);

    // 2 пара
    tmpCorrectForm.setWordForm(pastSimple, notThird, preterite, notSet);
    tmpVerifiedForm.setWordForm(pastSimple, notThird, preterite, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(1, tmpCorrectAux, tmpCorrectForm, // correct
                                 3, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 verb, 0);
    tmpPairsSet.insert(currentPair);

    // 3 пара
    tmpCorrectForm.setWordForm(singular, objective, notSet, notSet);
    tmpVerifiedForm.setWordForm(singular, objective, notSet, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(3, tmpCorrectAux, tmpCorrectForm, // correct
                                 1, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 noun, 0);
    tmpPairsSet.insert(currentPair);

    allExpPairsLists.append(tmpPairsSet);

    QTest::newRow("severalLinkOptions") <<
        correctSentence << verifiedSentence << allExpPairsLists;

    // 9 Тест. Пары всех поддерживаемых частей речи, все с ошибками
    correctSentence.clear();
    verifiedSentence.clear();
    tmpPairsSet.clear();
    allExpPairsLists.clear();

    correctSentence.addWordToEnd(new Pronoun("he"));
    correctSentence.addWordToEnd(new Verb("broke"));
    correctSentence.addWordToEnd(new Numeral("five"));
    correctSentence.addWordToEnd(new Adjective("weird"));
    correctSentence.addWordToEnd(new Noun("toys"));

    verifiedSentence.addWordToEnd(new Word("fifth"));
    verifiedSentence.addWordToEnd(new Word("weirder"));
    verifiedSentence.addWordToEnd(new Word("toy's"));
    verifiedSentence.addWordToEnd(new Word("his"));
    verifiedSentence.addWordToEnd(new Word("break"));

    // 1 пара
    tmpCorrectForm.setWordForm(objective, nominative, singular, notSet);
    tmpVerifiedForm.setWordForm(possessive, mainForm, singular, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(0, tmpCorrectAux, tmpCorrectForm, // correct
                                 3, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 pron, 30);
    tmpPairsSet.insert(currentPair);

    // 2 пара
    tmpCorrectForm.setWordForm(pastSimple, notThird, preterite, notSet);
    tmpVerifiedForm.setWordForm(presentSimple, notThird, infinitive, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(1, tmpCorrectAux, tmpCorrectForm, // correct
                                 4, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 verb, 50);
    tmpPairsSet.insert(currentPair);

    // 3 пара
    tmpCorrectForm.setWordForm(cardinal, notSet, notSet, notSet);
    tmpVerifiedForm.setWordForm(ordinal, notSet, notSet, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(2, tmpCorrectAux, tmpCorrectForm, // correct
                                 0, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 num, 100);
    tmpPairsSet.insert(currentPair);

    // 4 пара
    tmpCorrectForm.setWordForm(positive, notSet, notSet, notNeed);
    tmpVerifiedForm.setWordForm(comparative, notSet, notSet, notNeed);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(3, tmpCorrectAux, tmpCorrectForm, // correct
                                 1, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 adj, 100);
    tmpPairsSet.insert(currentPair);

    // 5 пара
    tmpCorrectForm.setWordForm(plural, objective, notSet, notSet);
    tmpVerifiedForm.setWordForm(singular, possessive, notSet, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(4, tmpCorrectAux, tmpCorrectForm, // correct
                                 2, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 noun, 100);
    tmpPairsSet.insert(currentPair);

    allExpPairsLists.append(tmpPairsSet);

    QTest::newRow("wordsAllPosAllHaveMisstakes") <<
        correctSentence << verifiedSentence << allExpPairsLists;

    // 10 Тест. Два ошибочных глагола
    correctSentence.clear();
    verifiedSentence.clear();
    tmpPairsSet.clear();
    allExpPairsLists.clear();

    correctSentence.addWordToEnd(new Pronoun("i"));
    correctSentence.addWordToEnd(new Verb("slept"));
    correctSentence.addWordToEnd(new Word("while"));
    correctSentence.addWordToEnd(new Pronoun("he"));
    correctSentence.addWordToEnd(new Auxiliary("would"));
    correctSentence.addWordToEnd(new Auxiliary("have"));
    correctSentence.addWordToEnd(new Auxiliary("been"));
    correctSentence.addWordToEnd(new Verb("working"));

    verifiedSentence.addWordToEnd(new Word("he"));
    verifiedSentence.addWordToEnd(new Word("should"));
    verifiedSentence.addWordToEnd(new Word("work"));
    verifiedSentence.addWordToEnd(new Word("while"));
    verifiedSentence.addWordToEnd(new Word("i"));
    verifiedSentence.addWordToEnd(new Word("would"));
    verifiedSentence.addWordToEnd(new Word("have"));
    verifiedSentence.addWordToEnd(new Word("been"));
    verifiedSentence.addWordToEnd(new Word("sleeping"));

    // 1 пара
    tmpCorrectForm.setWordForm(objective, nominative, singular, notSet);
    tmpVerifiedForm.setWordForm(objective, nominative, singular, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(0, tmpCorrectAux, tmpCorrectForm, // correct
                                 4, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 pron, 0);
    tmpPairsSet.insert(currentPair);

    // 2 пара
    tmpCorrectForm.setWordForm(pastSimple, notThird, preterite, notSet);
    tmpVerifiedForm.setWordForm(futurePerfContInThePast, notThird, presentParticiple, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();
    tmpVerifiedAux.append(5);
    tmpVerifiedAux.append(6);
    tmpVerifiedAux.append(7);

    currentPair.setAllParameters(1, tmpCorrectAux, tmpCorrectForm, // correct
                                 8, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 verb, 80);
    tmpPairsSet.insert(currentPair);

    // 3 пара
    tmpCorrectForm.setWordForm(objective, nominative, singular, notSet);
    tmpVerifiedForm.setWordForm(objective, nominative, singular, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(3, tmpCorrectAux, tmpCorrectForm, // correct
                                 0, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 pron, 0);
    tmpPairsSet.insert(currentPair);

    // 4 пара
    tmpCorrectForm.setWordForm(futurePerfContInThePast, notThird, presentParticiple, notSet);
    tmpVerifiedForm.setWordForm(futureSimpleInThePast, first, infinitive, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();
    tmpCorrectAux.append(4);
    tmpCorrectAux.append(5);
    tmpCorrectAux.append(6);
    tmpVerifiedAux.append(1);

    currentPair.setAllParameters(7, tmpCorrectAux, tmpCorrectForm, // correct
                                 2, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 verb, 100);
    tmpPairsSet.insert(currentPair);

    allExpPairsLists.append(tmpPairsSet);

    QTest::newRow("twoVerbsWithMisstakes") <<
        correctSentence << verifiedSentence << allExpPairsLists;

    // 11 Тест. Несколько вариантов согласования с правильной парой
    correctSentence.clear();
    verifiedSentence.clear();
    tmpPairsSet.clear();
    allExpPairsLists.clear();

    correctSentence.addWordToEnd(new Pronoun("you"));
    correctSentence.addWordToEnd(new Auxiliary("will"));
    correctSentence.addWordToEnd(new Verb("finish"));
    correctSentence.addWordToEnd(new Numeral("second"));

    verifiedSentence.addWordToEnd(new Word("you"));
    verifiedSentence.addWordToEnd(new Word("was"));
    verifiedSentence.addWordToEnd(new Word("finishing"));
    verifiedSentence.addWordToEnd(new Word("two"));

    // 1 вариант
    // 1 пара
    tmpCorrectForm.setWordForm(objective, nominative, singular, notSet);
    tmpVerifiedForm.setWordForm(objective, nominative, singular, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(0, tmpCorrectAux, tmpCorrectForm, // correct
                                 0, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 pron, 0);
    tmpPairsSet.insert(currentPair);

    // 2 пара
    tmpCorrectForm.setWordForm(futureSimple, notThird, infinitive, notSet);
    tmpVerifiedForm.setWordForm(pastCont, notThird, presentParticiple, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();
    tmpCorrectAux.append(1);
    tmpVerifiedAux.append(1);

    currentPair.setAllParameters(2, tmpCorrectAux, tmpCorrectForm, // correct
                                 2, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 verb, 80);
    tmpPairsSet.insert(currentPair);

    // 3 пара
    tmpCorrectForm.setWordForm(ordinal, notSet, notSet, notSet);
    tmpVerifiedForm.setWordForm(cardinal, notSet, notSet, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(3, tmpCorrectAux, tmpCorrectForm, // correct
                                 3, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 num, 100);
    tmpPairsSet.insert(currentPair);

    allExpPairsLists.append(tmpPairsSet);

    // 2 вариант
    // 1 пара
    tmpPairsSet.clear();
    tmpCorrectForm.setWordForm(objective, nominative, plural, notSet);
    tmpVerifiedForm.setWordForm(objective, nominative, plural, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(0, tmpCorrectAux, tmpCorrectForm, // correct
                                 0, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 pron, 0);
    tmpPairsSet.insert(currentPair);

    // 2 пара
    tmpCorrectForm.setWordForm(futureSimple, notThird, infinitive, notSet);
    tmpVerifiedForm.setWordForm(pastCont, notThird, presentParticiple, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();
    tmpCorrectAux.append(1);
    tmpVerifiedAux.append(1);

    currentPair.setAllParameters(2, tmpCorrectAux, tmpCorrectForm, // correct
                                 2, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 verb, 80);
    tmpPairsSet.insert(currentPair);

    // 3 пара
    tmpCorrectForm.setWordForm(ordinal, notSet, notSet, notSet);
    tmpVerifiedForm.setWordForm(cardinal, notSet, notSet, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(3, tmpCorrectAux, tmpCorrectForm, // correct
                                 3, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 num, 100);
    tmpPairsSet.insert(currentPair);

    allExpPairsLists.append(tmpPairsSet);

    // 3 вариант
    // 1 пара
    tmpPairsSet.clear();
    tmpCorrectForm.setWordForm(objective, objectivePron, singular, notSet);
    tmpVerifiedForm.setWordForm(objective, objectivePron, singular, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(0, tmpCorrectAux, tmpCorrectForm, // correct
                                 0, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 pron, 0);
    tmpPairsSet.insert(currentPair);

    // 2 пара
    tmpCorrectForm.setWordForm(futureSimple, notThird, infinitive, notSet);
    tmpVerifiedForm.setWordForm(pastCont, notThird, presentParticiple, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();
    tmpCorrectAux.append(1);
    tmpVerifiedAux.append(1);

    currentPair.setAllParameters(2, tmpCorrectAux, tmpCorrectForm, // correct
                                 2, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 verb, 80);
    tmpPairsSet.insert(currentPair);

    // 3 пара
    tmpCorrectForm.setWordForm(ordinal, notSet, notSet, notSet);
    tmpVerifiedForm.setWordForm(cardinal, notSet, notSet, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(3, tmpCorrectAux, tmpCorrectForm, // correct
                                 3, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 num, 100);
    tmpPairsSet.insert(currentPair);

    allExpPairsLists.append(tmpPairsSet);

    // 4 вариант
    // 1 пара
    tmpPairsSet.clear();
    tmpCorrectForm.setWordForm(objective, objectivePron, plural, notSet);
    tmpVerifiedForm.setWordForm(objective, objectivePron, plural, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(0, tmpCorrectAux, tmpCorrectForm, // correct
                                 0, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 pron, 0);
    tmpPairsSet.insert(currentPair);

    // 2 пара
    tmpCorrectForm.setWordForm(futureSimple, notThird, infinitive, notSet);
    tmpVerifiedForm.setWordForm(pastCont, notThird, presentParticiple, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();
    tmpCorrectAux.append(1);
    tmpVerifiedAux.append(1);

    currentPair.setAllParameters(2, tmpCorrectAux, tmpCorrectForm, // correct
                                 2, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 verb, 80);
    tmpPairsSet.insert(currentPair);

    // 3 пара
    tmpCorrectForm.setWordForm(ordinal, notSet, notSet, notSet);
    tmpVerifiedForm.setWordForm(cardinal, notSet, notSet, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(3, tmpCorrectAux, tmpCorrectForm, // correct
                                 3, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 num, 100);
    tmpPairsSet.insert(currentPair);

    allExpPairsLists.append(tmpPairsSet);

    QTest::newRow("severalLinkedOptionsWithSameCorrectPair") <<
        correctSentence << verifiedSentence << allExpPairsLists;

    // 12 Тест. Одному слову из правильного предложения соответствует
    // несколько слов из проверяемого предложения
    correctSentence.clear();
    verifiedSentence.clear();
    tmpPairsSet.clear();
    allExpPairsLists.clear();

    correctSentence.addWordToEnd(new Pronoun("i"));
    correctSentence.addWordToEnd(new Verb("love"));
    correctSentence.addWordToEnd(new Pronoun("my"));
    correctSentence.addWordToEnd(new Noun("name"));

    verifiedSentence.addWordToEnd(new Word("me"));
    verifiedSentence.addWordToEnd(new Word("love"));
    verifiedSentence.addWordToEnd(new Word("me"));
    verifiedSentence.addWordToEnd(new Word("name"));

    // 1 вариант
    // 1 пара
    tmpCorrectForm.setWordForm(objective, nominative, singular, notSet);
    tmpVerifiedForm.setWordForm(objective, objectivePron, singular, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(0, tmpCorrectAux, tmpCorrectForm, // correct
                                 0, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 pron, 30);
    tmpPairsSet.insert(currentPair);

    // 2 пара
    tmpCorrectForm.setWordForm(presentSimple, notThird, infinitive, notSet);
    tmpVerifiedForm.setWordForm(presentSimple, notThird, infinitive, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(1, tmpCorrectAux, tmpCorrectForm, // correct
                                 1, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 verb, 0);
    tmpPairsSet.insert(currentPair);

    // 3 пара
    tmpCorrectForm.setWordForm(possessive, mainForm, singular, notSet);
    tmpVerifiedForm.setWordForm(objective, objectivePron, singular, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(2, tmpCorrectAux, tmpCorrectForm, // correct
                                 2, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 pron, 60);
    tmpPairsSet.insert(currentPair);

    // 4 пара
    tmpCorrectForm.setWordForm(singular, objective, notSet, notSet);
    tmpVerifiedForm.setWordForm(singular, objective, notSet, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(3, tmpCorrectAux, tmpCorrectForm, // correct
                                 3, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 noun, 0);
    tmpPairsSet.insert(currentPair);

    allExpPairsLists.append(tmpPairsSet);

    // 2 вариант
    // 1 пара
    tmpPairsSet.clear();
    tmpCorrectForm.setWordForm(objective, nominative, singular, notSet);
    tmpVerifiedForm.setWordForm(objective, objectivePron, singular, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(0, tmpCorrectAux, tmpCorrectForm, // correct
                                 2, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 pron, 30);
    tmpPairsSet.insert(currentPair);

    // 2 пара
    tmpCorrectForm.setWordForm(presentSimple, notThird, infinitive, notSet);
    tmpVerifiedForm.setWordForm(presentSimple, notThird, infinitive, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(1, tmpCorrectAux, tmpCorrectForm, // correct
                                 1, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 verb, 0);
    tmpPairsSet.insert(currentPair);

    // 3 пара
    tmpCorrectForm.setWordForm(possessive, mainForm, singular, notSet);
    tmpVerifiedForm.setWordForm(objective, objectivePron, singular, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(2, tmpCorrectAux, tmpCorrectForm, // correct
                                 0, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 pron, 60);
    tmpPairsSet.insert(currentPair);

    // 4 пара
    tmpCorrectForm.setWordForm(singular, objective, notSet, notSet);
    tmpVerifiedForm.setWordForm(singular, objective, notSet, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(3, tmpCorrectAux, tmpCorrectForm, // correct
                                 3, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 noun, 0);
    tmpPairsSet.insert(currentPair);

    allExpPairsLists.append(tmpPairsSet);

    QTest::newRow("severalWordsFromVerifiedMatchesToOneFromCorrect") <<
        correctSentence << verifiedSentence << allExpPairsLists;
}

void LinkSentences::linkSentences()
{
    QFETCH(Sentence, correctSentence);
    QFETCH(Sentence, verifiedSentence);
    QFETCH(QList<QSet<Pair>>, expPairsSets);

    LinkedSentences currentLink;
    currentLink.linkSentences(correctSentence, verifiedSentence);

    QList<QSet<Pair>> realPairsSets = currentLink.getLinkedSentences();

    QMutableListIterator<QSet<Pair>> iAllExpLists(expPairsSets);
    QMutableListIterator<QSet<Pair>> iAllRealLists(realPairsSets);

    QSet<Pair> currentExpPairList;
    Pair matchingPair;

    QMutableSetIterator<Pair> iCurrentExpPairsList(currentExpPairList);

    int currentSetNumber = 0;

    while (iAllExpLists.hasNext())
    {  
        if (!realPairsSets.removeOne(iAllExpLists.next()))
        { // Вывод сообщения о том, что текущая пара не была сопоставлена с реальной
            QVERIFY2(false, ("Set number " + QString::number(currentSetNumber) + ": Wasn't matched").toUtf8());
        }

        currentSetNumber++;
    }

    // Все оставшиеся списки не были возвращены функцией
    iAllRealLists.toFront();

    if (!realPairsSets.empty())
    {
        QVERIFY2(false, ("unexpected set found."));
    }
}

void LinkSentences::initTestCase()
{
    Verb::readFileWithIrregularVerbs();
    Verb::readFileWithVerbLexems();
    Noun::readFileWithExceptionsNouns();
    Noun::readaFileWithOnlyPluralNouns();
    Noun::readFileWithUncountableNouns();
    Adjective::readFileWithAdjectiveExceptions();
}

QTEST_APPLESS_MAIN(LinkSentences)

#include "test_LinkSentences.moc"
