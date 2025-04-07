#include <QCoreApplication>
#include <QtTest/QtTest>

#include "../wrongFormsFinder/linkedsentences.h"
#include "../wrongFormsFinder/adjective.h"
#include "../wrongFormsFinder/auxiliary.h"
#include "../wrongFormsFinder/noun.h"
#include "../wrongFormsFinder/numeral.h"
#include "../wrongFormsFinder/pronoun.h"
#include "../wrongFormsFinder/verb.h"

class GenerateAllPairs: public QObject
{
    Q_OBJECT

private slots:
    void generateAllPairs_data();
    void generateAllPairs();

    void initTestCase();
};

void GenerateAllPairs::generateAllPairs_data()
{
    QTest::addColumn<Sentence>("correctSentence");
    QTest::addColumn<Sentence>("verifiedSentence");
    QTest::addColumn<QList<Pair>>("expPairs");

    Sentence correctSentence, verifiedSentence;
    WordForm tmpCorrectForm, tmpVerifiedForm;
    QList<int> tmpCorrectAux, tmpVerifiedAux;
    QList<Pair> expPairsList;
    Pair currentPair;

//    // 1 тест. На каждое слово по 1 паре
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
//    expPairsList.append(currentPair);

//    // 2 пара
//    tmpCorrectForm.setWordForm(presentSimple, notThird, infinitive, notSet);
//    tmpVerifiedForm.setWordForm(presentSimple, notThird, infinitive, notSet);

//    tmpCorrectAux.clear();
//    tmpVerifiedAux.clear();

//    currentPair.setAllParameters(1, tmpCorrectAux, tmpCorrectForm, // correct
//                                 3, tmpVerifiedAux, tmpVerifiedForm, // verified
//                                 verb, 0);
//    expPairsList.append(currentPair);

//    // 3 пара
//    tmpCorrectForm.setWordForm(positive, notSet, notSet, notNeed);
//    tmpVerifiedForm.setWordForm(positive, notSet, notSet, notNeed);

//    tmpCorrectAux.clear();
//    tmpVerifiedAux.clear();

//    currentPair.setAllParameters(3, tmpCorrectAux, tmpCorrectForm, // correct
//                                 0, tmpVerifiedAux, tmpVerifiedForm, // verified
//                                 adj, 0);
//    expPairsList.append(currentPair);

//    // 4 пара
//    tmpCorrectForm.setWordForm(singular, objective, notSet, notSet);
//    tmpVerifiedForm.setWordForm(singular, objective, notSet, notSet);

//    tmpCorrectAux.clear();
//    tmpVerifiedAux.clear();

//    currentPair.setAllParameters(4, tmpCorrectAux, tmpCorrectForm, // correct
//                                 1, tmpVerifiedAux, tmpVerifiedForm, // verified
//                                 noun, 0);
//    expPairsList.append(currentPair);

//    QTest::newRow("onePairToEveryWord") <<
//        correctSentence << verifiedSentence << expPairsList;

//    // 2 Тест. Одному глаголу в правильном предложении соответствует 2 формы того же глагола в проверяемом
//    expPairsList.clear();
//    correctSentence.clear();
//    verifiedSentence.clear();

//    correctSentence.addWordToEnd(new Pronoun("i"));
//    correctSentence.addWordToEnd(new Auxiliary("had"));
//    correctSentence.addWordToEnd(new Auxiliary("been"));
//    correctSentence.addWordToEnd(new Verb("quitting"));

//    verifiedSentence.addWordToEnd(new Word("i"));
//    verifiedSentence.addWordToEnd(new Word("quit"));

//    // 1 пара
//    tmpCorrectForm.setWordForm(objective, nominative, singular, notSet);
//    tmpVerifiedForm.setWordForm(objective, nominative, singular, notSet);

//    tmpCorrectAux.clear();
//    tmpVerifiedAux.clear();

//    currentPair.setAllParameters(0, tmpCorrectAux, tmpCorrectForm, // correct
//                                 0, tmpVerifiedAux, tmpVerifiedForm, // verified
//                                 pron, 0);
//    expPairsList.append(currentPair);

//    // 2 пара
//    tmpCorrectForm.setWordForm(pastPerfCont, notThird, presentParticiple, notSet);
//    tmpVerifiedForm.setWordForm(presentSimple, notThird, infinitive, notSet);

//    tmpCorrectAux.clear();
//    tmpVerifiedAux.clear();
//    tmpCorrectAux.append(1);
//    tmpCorrectAux.append(2);

//    currentPair.setAllParameters(3, tmpCorrectAux, tmpCorrectForm, // correct
//                                 1, tmpVerifiedAux, tmpVerifiedForm, // verified
//                                 verb, 80);
//    expPairsList.append(currentPair);

//    // 3 пара
//    tmpCorrectForm.setWordForm(pastPerfCont, notThird, presentParticiple, notSet);
//    tmpVerifiedForm.setWordForm(pastSimple, notThird, preterite, notSet);

//    tmpCorrectAux.clear();
//    tmpVerifiedAux.clear();
//    tmpCorrectAux.append(1);
//    tmpCorrectAux.append(2);

//    currentPair.setAllParameters(3, tmpCorrectAux, tmpCorrectForm, // correct
//                                 1, tmpVerifiedAux, tmpVerifiedForm, // verified
//                                 verb, 80);
//    expPairsList.append(currentPair);

//    QTest::newRow("twoFormsOfOneVerbMatchesWithOneInCorrect") <<
//        correctSentence << verifiedSentence << expPairsList;

//    // 3 Тест. Одно и то же слово из проверяемого предложения входит в пары несколько раз
//    expPairsList.clear();
//    correctSentence.clear();
//    verifiedSentence.clear();

//    correctSentence.addWordToEnd(new Pronoun("i"));
//    correctSentence.addWordToEnd(new Verb("love"));
//    correctSentence.addWordToEnd(new Pronoun("my"));
//    correctSentence.addWordToEnd(new Noun("name"));

//    verifiedSentence.addWordToEnd(new Word("me"));
//    verifiedSentence.addWordToEnd(new Word("love"));
//    verifiedSentence.addWordToEnd(new Word("my"));
//    verifiedSentence.addWordToEnd(new Word("name"));

//    // 1 пара
//    tmpCorrectForm.setWordForm(objective, nominative, singular, notSet);
//    tmpVerifiedForm.setWordForm(objective, objectivePron, singular, notSet);

//    tmpCorrectAux.clear();
//    tmpVerifiedAux.clear();

//    currentPair.setAllParameters(0, tmpCorrectAux, tmpCorrectForm, // correct
//                                 0, tmpVerifiedAux, tmpVerifiedForm, // verified
//                                 pron, 30);
//    expPairsList.append(currentPair);

//    // 2 пара
//    tmpCorrectForm.setWordForm(objective, nominative, singular, notSet);
//    tmpVerifiedForm.setWordForm(possessive, mainForm, singular, notSet);

//    tmpCorrectAux.clear();
//    tmpVerifiedAux.clear();

//    currentPair.setAllParameters(0, tmpCorrectAux, tmpCorrectForm, // correct
//                                 2, tmpVerifiedAux, tmpVerifiedForm, // verified
//                                 pron, 30);
//    expPairsList.append(currentPair);

//    // 3 пара
//    tmpCorrectForm.setWordForm(presentSimple, notThird, infinitive, notSet);
//    tmpVerifiedForm.setWordForm(presentSimple, notThird, infinitive, notSet);

//    tmpCorrectAux.clear();
//    tmpVerifiedAux.clear();

//    currentPair.setAllParameters(1, tmpCorrectAux, tmpCorrectForm, // correct
//                                 1, tmpVerifiedAux, tmpVerifiedForm, // verified
//                                 verb, 0);
//    expPairsList.append(currentPair);

//    // 4 пара
//    tmpCorrectForm.setWordForm(possessive, mainForm, singular, notSet);
//    tmpVerifiedForm.setWordForm(objective, objectivePron, singular, notSet);

//    tmpCorrectAux.clear();
//    tmpVerifiedAux.clear();

//    currentPair.setAllParameters(2, tmpCorrectAux, tmpCorrectForm, // correct
//                                 0, tmpVerifiedAux, tmpVerifiedForm, // verified
//                                 pron, 60);
//    expPairsList.append(currentPair);

//    // 5 пара
//    tmpCorrectForm.setWordForm(possessive, mainForm, singular, notSet);
//    tmpVerifiedForm.setWordForm(possessive, mainForm, singular, notSet);

//    tmpCorrectAux.clear();
//    tmpVerifiedAux.clear();

//    currentPair.setAllParameters(2, tmpCorrectAux, tmpCorrectForm, // correct
//                                 2, tmpVerifiedAux, tmpVerifiedForm, // verified
//                                 pron, 0);
//    expPairsList.append(currentPair);

//    // 6 пара
//    tmpCorrectForm.setWordForm(singular, objective, notSet, notSet);
//    tmpVerifiedForm.setWordForm(singular, objective, notSet, notSet);

//    tmpCorrectAux.clear();
//    tmpVerifiedAux.clear();

//    currentPair.setAllParameters(3, tmpCorrectAux, tmpCorrectForm, // correct
//                                 3, tmpVerifiedAux, tmpVerifiedForm, // verified
//                                 noun, 0);
//    expPairsList.append(currentPair);

//    QTest::newRow("oneWordFromCorrectInDifferentPairs") <<
//        correctSentence << verifiedSentence << expPairsList;

//    // 4 Тест. Глагол из правильного предложения может быть как основным глаголом,
//    // так и вспомогательным в проверяемом предложении
//    expPairsList.clear();
//    correctSentence.clear();
//    verifiedSentence.clear();

//    correctSentence.addWordToEnd(new Pronoun("i"));
//    correctSentence.addWordToEnd(new Verb("have"));
//    correctSentence.addWordToEnd(new Numeral("five"));
//    correctSentence.addWordToEnd(new Noun("apples"));

//    verifiedSentence.addWordToEnd(new Word("i"));
//    verifiedSentence.addWordToEnd(new Word("have"));
//    verifiedSentence.addWordToEnd(new Word("had"));
//    verifiedSentence.addWordToEnd(new Word("five"));
//    verifiedSentence.addWordToEnd(new Word("apples"));

//    // 1 пара
//    tmpCorrectForm.setWordForm(objective, nominative, singular, notSet);
//    tmpVerifiedForm.setWordForm(objective, nominative, singular, notSet);

//    tmpCorrectAux.clear();
//    tmpVerifiedAux.clear();

//    currentPair.setAllParameters(0, tmpCorrectAux, tmpCorrectForm, // correct
//                                 0, tmpVerifiedAux, tmpVerifiedForm, // verified
//                                 pron, 0);
//    expPairsList.append(currentPair);

//    // 2 пара
//    tmpCorrectForm.setWordForm(presentSimple, notThird, infinitive, notSet);
//    tmpVerifiedForm.setWordForm(presentSimple, notThird, infinitive, notSet);

//    tmpCorrectAux.clear();
//    tmpVerifiedAux.clear();

//    currentPair.setAllParameters(1, tmpCorrectAux, tmpCorrectForm, // correct
//                                 1, tmpVerifiedAux, tmpVerifiedForm, // verified
//                                 verb, 0);
//    expPairsList.append(currentPair);

//    // 3 пара
//    tmpCorrectForm.setWordForm(presentSimple, notThird, infinitive, notSet);
//    tmpVerifiedForm.setWordForm(pastSimple, notThird, preterite, notSet);

//    tmpCorrectAux.clear();
//    tmpVerifiedAux.clear();

//    currentPair.setAllParameters(1, tmpCorrectAux, tmpCorrectForm, // correct
//                                 2, tmpVerifiedAux, tmpVerifiedForm, // verified
//                                 verb, 50);
//    expPairsList.append(currentPair);

//    // 4 пара
//    tmpCorrectForm.setWordForm(presentSimple, notThird, infinitive, notSet);
//    tmpVerifiedForm.setWordForm(presentPerf, notThird, pastParticiple, notSet);

//    tmpCorrectAux.clear();
//    tmpVerifiedAux.clear();
//    tmpVerifiedAux.append(1);

//    currentPair.setAllParameters(1, tmpCorrectAux, tmpCorrectForm, // correct
//                                 2, tmpVerifiedAux, tmpVerifiedForm, // verified
//                                 verb, 80);
//    expPairsList.append(currentPair);

//    // 5 пара
//    tmpCorrectForm.setWordForm(cardinal, notSet, notSet, notSet);
//    tmpVerifiedForm.setWordForm(cardinal, notSet, notSet, notSet);

//    tmpCorrectAux.clear();
//    tmpVerifiedAux.clear();

//    currentPair.setAllParameters(2, tmpCorrectAux, tmpCorrectForm, // correct
//                                 3, tmpVerifiedAux, tmpVerifiedForm, // verified
//                                 num, 0);
//    expPairsList.append(currentPair);

//    // 6 пара
//    tmpCorrectForm.setWordForm(plural, objective, notSet, notSet);
//    tmpVerifiedForm.setWordForm(plural, objective, notSet, notSet);

//    tmpCorrectAux.clear();
//    tmpVerifiedAux.clear();

//    currentPair.setAllParameters(3, tmpCorrectAux, tmpCorrectForm, // correct
//                                 4, tmpVerifiedAux, tmpVerifiedForm, // verified
//                                 noun, 0);
//    expPairsList.append(currentPair);

//    QTest::newRow("verbFromVerifiedIsVerbAndIsAux") <<
//        correctSentence << verifiedSentence << expPairsList;

//    // 5 Тест. Существительному из правильного предложения соответствует 2 слова в проверяемом предложении
//    expPairsList.clear();
//    correctSentence.clear();
//    verifiedSentence.clear();

//    correctSentence.addWordToEnd(new Pronoun("my"));
//    correctSentence.addWordToEnd(new Adjective("gold"));
//    correctSentence.addWordToEnd(new Noun("mine"));

//    verifiedSentence.addWordToEnd(new Word("my"));
//    verifiedSentence.addWordToEnd(new Word("gold"));
//    verifiedSentence.addWordToEnd(new Word("mine"));

//    // 1 пара
//    tmpCorrectForm.setWordForm(possessive, mainForm, singular, notSet);
//    tmpVerifiedForm.setWordForm(possessive, mainForm, singular, notSet);

//    tmpCorrectAux.clear();
//    tmpVerifiedAux.clear();

//    currentPair.setAllParameters(0, tmpCorrectAux, tmpCorrectForm, // correct
//                                 0, tmpVerifiedAux, tmpVerifiedForm, // verified
//                                 pron, 0);
//    expPairsList.append(currentPair);

//    // 2 пара
//    tmpCorrectForm.setWordForm(possessive, mainForm, singular, notSet);
//    tmpVerifiedForm.setWordForm(possessive, absoluteForm, singular, notSet);

//    tmpCorrectAux.clear();
//    tmpVerifiedAux.clear();

//    currentPair.setAllParameters(0, tmpCorrectAux, tmpCorrectForm, // correct
//                                 2, tmpVerifiedAux, tmpVerifiedForm, // verified
//                                 pron, 30);
//    expPairsList.append(currentPair);

//    // 3 пара
//    tmpCorrectForm.setWordForm(positive, notSet, notSet, notNeed);
//    tmpVerifiedForm.setWordForm(positive, notSet, notSet, notNeed);

//    tmpCorrectAux.clear();
//    tmpVerifiedAux.clear();

//    currentPair.setAllParameters(1, tmpCorrectAux, tmpCorrectForm,
//                                 1, tmpVerifiedAux, tmpVerifiedForm,
//                                 adj, 0);
//    expPairsList.append(currentPair);

//    // 4 пара
//    tmpCorrectForm.setWordForm(singular, objective, notSet, notSet);
//    tmpVerifiedForm.setWordForm(singular, objective, notSet, notSet);

//    tmpCorrectAux.clear();
//    tmpVerifiedAux.clear();

//    currentPair.setAllParameters(2, tmpCorrectAux, tmpCorrectForm, // correct
//                                 2, tmpVerifiedAux, tmpVerifiedForm, // verified
//                                 noun, 0);
//    expPairsList.append(currentPair);

//    QTest::newRow("nounInCorrectMathcesTwoWordsFromVerified") <<
//        correctSentence << verifiedSentence << expPairsList;

//    // 6 Тест. Прилагательному из правильного предложения соответствует
//    // прилагательное со вспомогательным в проверяемом
//    expPairsList.clear();
//    correctSentence.clear();
//    verifiedSentence.clear();

//    correctSentence.addWordToEnd(new Adjective("interesting"));
//    correctSentence.addWordToEnd(new Noun("day"));

//    verifiedSentence.addWordToEnd(new Word("the"));
//    verifiedSentence.addWordToEnd(new Word("most"));
//    verifiedSentence.addWordToEnd(new Word("interesting"));
//    verifiedSentence.addWordToEnd(new Word("day"));

//    // 1 пара
//    tmpCorrectForm.setWordForm(positive, notSet, notSet, notNeed);
//    tmpVerifiedForm.setWordForm(positive, notSet, notSet, notNeed);

//    tmpCorrectAux.clear();
//    tmpVerifiedAux.clear();

//    currentPair.setAllParameters(0, tmpCorrectAux, tmpCorrectForm,
//                                 2, tmpVerifiedAux, tmpVerifiedForm,
//                                 adj, 0);
//    expPairsList.append(currentPair);

//    // 2 пара
//    tmpCorrectForm.setWordForm(positive, notSet, notSet, notNeed);
//    tmpVerifiedForm.setWordForm(superlative, notSet, notSet, most);

//    tmpCorrectAux.clear();
//    tmpVerifiedAux.clear();
//    tmpVerifiedAux.append(1);

//    currentPair.setAllParameters(0, tmpCorrectAux, tmpCorrectForm,
//                                 2, tmpVerifiedAux, tmpVerifiedForm,
//                                 adj, 100);
//    expPairsList.append(currentPair);

//    // 3 пара
//    tmpCorrectForm.setWordForm(singular, objective, notSet, notSet);
//    tmpVerifiedForm.setWordForm(singular, objective, notSet, notSet);

//    tmpCorrectAux.clear();
//    tmpVerifiedAux.clear();

//    currentPair.setAllParameters(1, tmpCorrectAux, tmpCorrectForm, // correct
//                                 3, tmpVerifiedAux, tmpVerifiedForm, // verified
//                                 noun, 0);
//    expPairsList.append(currentPair);

//    QTest::newRow("adjFromCorrectMathcesWithAdjWithAuxiliariesInVerified") <<
//        correctSentence << verifiedSentence << expPairsList;

    // 7 Тест. В вопросительном предложении между глаголом и вспомогательными есть посторонние слова
    expPairsList.clear();
    correctSentence.clear();
    verifiedSentence.clear();

    correctSentence.addWordToEnd(new Auxiliary("does"));
    correctSentence.addWordToEnd(new Pronoun("your"));
    correctSentence.addWordToEnd(new Noun("brother"));
    correctSentence.addWordToEnd(new Verb("like"));
    correctSentence.addWordToEnd(new Noun("apples"));

    verifiedSentence.addWordToEnd(new Word("your"));
    verifiedSentence.addWordToEnd(new Word("brother"));
    verifiedSentence.addWordToEnd(new Word("does"));
    verifiedSentence.addWordToEnd(new Word("like"));
    verifiedSentence.addWordToEnd(new Word("apples"));

    // 1 пара
    tmpCorrectForm.setWordForm(possessive, mainForm, singular, notSet);
    tmpVerifiedForm.setWordForm(possessive, mainForm, singular, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(1, tmpCorrectAux, tmpCorrectForm, // correct
                                 0, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 pron, 0);
    expPairsList.append(currentPair);

    // 2 пара
    tmpCorrectForm.setWordForm(possessive, mainForm, plural, notSet);
    tmpVerifiedForm.setWordForm(possessive, mainForm, plural, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(1, tmpCorrectAux, tmpCorrectForm, // correct
                                 0, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 pron, 0);
    expPairsList.append(currentPair);

    // 5 пара
    tmpCorrectForm.setWordForm(singular, objective, notSet, notSet);
    tmpVerifiedForm.setWordForm(singular, objective, notSet, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(2, tmpCorrectAux, tmpCorrectForm, // correct
                                 1, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 noun, 0);
    expPairsList.append(currentPair);

    // 6 пара
    tmpCorrectForm.setWordForm(presentSimple, third, infinitive, notSet);
    tmpVerifiedForm.setWordForm(presentSimple, notThird, infinitive, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();
    tmpCorrectAux.append(0);

    currentPair.setAllParameters(3, tmpCorrectAux, tmpCorrectForm, // correct
                                 3, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 verb, 20);
    expPairsList.append(currentPair);

    // 7 пара
    tmpCorrectForm.setWordForm(presentSimple, third, infinitive, notSet);
    tmpVerifiedForm.setWordForm(presentSimple, third, infinitive, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();
    tmpCorrectAux.append(0);
    tmpVerifiedAux.append(2);

    currentPair.setAllParameters(3, tmpCorrectAux, tmpCorrectForm, // correct
                                 3, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 verb, 0);
    expPairsList.append(currentPair);

    // 8 пара
    tmpCorrectForm.setWordForm(plural, objective, notSet, notSet);
    tmpVerifiedForm.setWordForm(plural, objective, notSet, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(4, tmpCorrectAux, tmpCorrectForm, // correct
                                 4, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 noun, 0);
    expPairsList.append(currentPair);

    QTest::newRow("betweenVerbAndAuxiliariesOtherWordsInCorrect") <<
        correctSentence << verifiedSentence << expPairsList;

    // 8 Тест. Глагол в правильном предложении имеет два возможных времени, как и в проверяемом предложении
    expPairsList.clear();
    correctSentence.clear();
    verifiedSentence.clear();

    correctSentence.addWordToEnd(new Pronoun("he"));
    correctSentence.addWordToEnd(new Verb("read"));
    correctSentence.addWordToEnd(new Word("a"));
    correctSentence.addWordToEnd(new Noun("book"));

    verifiedSentence.addWordToEnd(new Word("a"));
    verifiedSentence.addWordToEnd(new Word("book"));
    verifiedSentence.addWordToEnd(new Word("he"));
    verifiedSentence.addWordToEnd(new Word("read"));

    // 1 пара
    tmpCorrectForm.setWordForm(objective, nominative, singular, notSet);
    tmpVerifiedForm.setWordForm(objective, nominative, singular, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(0, tmpCorrectAux, tmpCorrectForm, // correct
                                 2, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 pron, 0);
    expPairsList.append(currentPair);

    // 2 пара
    tmpCorrectForm.setWordForm(presentSimple, notThird, infinitive, notSet);
    tmpVerifiedForm.setWordForm(presentSimple, notThird, infinitive, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(1, tmpCorrectAux, tmpCorrectForm, // correct
                                 3, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 verb, 0);
    expPairsList.append(currentPair);

    // 3 пара
    tmpCorrectForm.setWordForm(pastSimple, notThird, preterite, notSet);
    tmpVerifiedForm.setWordForm(pastSimple, notThird, preterite, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(1, tmpCorrectAux, tmpCorrectForm, // correct
                                 3, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 verb, 0);
    expPairsList.append(currentPair);

    // 4 пара
    tmpCorrectForm.setWordForm(singular, objective, notSet, notSet);
    tmpVerifiedForm.setWordForm(singular, objective, notSet, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(3, tmpCorrectAux, tmpCorrectForm, // correct
                                 1, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 noun, 0);
    expPairsList.append(currentPair);

    QTest::newRow("verbInCorrectAndVerifiedHasToTenses") <<
        correctSentence << verifiedSentence << expPairsList;

    // 9 Тест. Местоимение в правильном предложении может иметь несколько форм
    expPairsList.clear();
    correctSentence.clear();
    verifiedSentence.clear();

    correctSentence.addWordToEnd(new Pronoun("you"));

    verifiedSentence.addWordToEnd(new Word("you"));

    // 1 пара
    tmpCorrectForm.setWordForm(objective, nominative, singular, notSet);
    tmpVerifiedForm.setWordForm(objective, nominative, singular, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(0, tmpCorrectAux, tmpCorrectForm, // correct
                                 0, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 pron, 0);
    expPairsList.append(currentPair);

    // 2 пара
    tmpCorrectForm.setWordForm(objective, objectivePron, singular, notSet);
    tmpVerifiedForm.setWordForm(objective, objectivePron, singular, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(0, tmpCorrectAux, tmpCorrectForm, // correct
                                 0, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 pron, 0);
    expPairsList.append(currentPair);

    // 3 пара
    tmpCorrectForm.setWordForm(objective, nominative, plural, notSet);
    tmpVerifiedForm.setWordForm(objective, nominative, plural, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(0, tmpCorrectAux, tmpCorrectForm, // correct
                                 0, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 pron, 0);
    expPairsList.append(currentPair);

    // 4 пара
    tmpCorrectForm.setWordForm(objective, objectivePron, plural, notSet);
    tmpVerifiedForm.setWordForm(objective, objectivePron, plural, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(0, tmpCorrectAux, tmpCorrectForm, // correct
                                 0, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 pron, 0);
    expPairsList.append(currentPair);

    QTest::newRow("pronounHasSeveralForms") <<
        correctSentence << verifiedSentence << expPairsList;

    // 10 Тест. Нет ни одной пары
    expPairsList.clear();
    correctSentence.clear();
    verifiedSentence.clear();

    correctSentence.addWordToEnd(new Noun("word"));

    verifiedSentence.addWordToEnd(new Word("me"));

    QTest::newRow("zeroPairs") <<
        correctSentence << verifiedSentence << expPairsList;

    // 11 Тест. Два одинаковых глагола в одинаковом времени
    expPairsList.clear();
    correctSentence.clear();
    verifiedSentence.clear();

    correctSentence.addWordToEnd(new Auxiliary("has"));
    correctSentence.addWordToEnd(new Verb("stayed"));
    correctSentence.addWordToEnd(new Word("and"));
    correctSentence.addWordToEnd(new Auxiliary("has"));
    correctSentence.addWordToEnd(new Verb("stayed"));

    verifiedSentence.addWordToEnd(new Word("has"));
    verifiedSentence.addWordToEnd(new Word("stayed"));
    verifiedSentence.addWordToEnd(new Word("and"));
    verifiedSentence.addWordToEnd(new Word("has"));
    verifiedSentence.addWordToEnd(new Word("stayed"));

    // 1 пара
    tmpCorrectForm.setWordForm(presentPerf, third, past, notSet);
    tmpVerifiedForm.setWordForm(pastSimple, notThird, past, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();
    tmpCorrectAux.append(0);

    currentPair.setAllParameters(1, tmpCorrectAux, tmpCorrectForm, // correct
                                 1, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 verb, 51);
    expPairsList.append(currentPair);

    // 2 пара
    tmpCorrectForm.setWordForm(presentPerf, third, past, notSet);
    tmpVerifiedForm.setWordForm(pastSimple, notThird, past, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();
    tmpCorrectAux.append(0);

    currentPair.setAllParameters(1, tmpCorrectAux, tmpCorrectForm, // correct
                                 4, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 verb, 51);
    expPairsList.append(currentPair);

    // 3 пара
    tmpCorrectForm.setWordForm(presentPerf, third, past, notSet);
    tmpVerifiedForm.setWordForm(pastSimple, notThird, past, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();
    tmpCorrectAux.append(3);

    currentPair.setAllParameters(4, tmpCorrectAux, tmpCorrectForm, // correct
                                 1, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 verb, 51);
    expPairsList.append(currentPair);


    // 4 пара
    tmpCorrectForm.setWordForm(presentPerf, third, past, notSet);
    tmpVerifiedForm.setWordForm(pastSimple, notThird, past, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();
    tmpCorrectAux.append(3);

    currentPair.setAllParameters(4, tmpCorrectAux, tmpCorrectForm, // correct
                                 4, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 verb, 51);
    expPairsList.append(currentPair);


    // 5 пара
    tmpCorrectForm.setWordForm(presentPerf, third, past, notSet);
    tmpVerifiedForm.setWordForm(presentPerf, third, past, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();
    tmpCorrectAux.append(0);
    tmpVerifiedAux.append(0);

    currentPair.setAllParameters(1, tmpCorrectAux, tmpCorrectForm, // correct
                                 1, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 verb, 0);
    expPairsList.append(currentPair);

    // 6 пара
    tmpCorrectForm.setWordForm(presentPerf, third, past, notSet);
    tmpVerifiedForm.setWordForm(presentPerf, third, past, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();
    tmpCorrectAux.append(0);
    tmpVerifiedAux.append(3);

    currentPair.setAllParameters(1, tmpCorrectAux, tmpCorrectForm, // correct
                                 4, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 verb, 0);
    expPairsList.append(currentPair);

    // 7 пара
    tmpCorrectForm.setWordForm(presentPerf, third, past, notSet);
    tmpVerifiedForm.setWordForm(presentPerf, third, past, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();
    tmpCorrectAux.append(3);
    tmpVerifiedAux.append(0);

    currentPair.setAllParameters(4, tmpCorrectAux, tmpCorrectForm, // correct
                                 1, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 verb, 0);
    expPairsList.append(currentPair);


    // 8 пара
    tmpCorrectForm.setWordForm(presentPerf, third, past, notSet);
    tmpVerifiedForm.setWordForm(presentPerf, third, past, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();
    tmpCorrectAux.append(3);
    tmpVerifiedAux.append(3);

    currentPair.setAllParameters(4, tmpCorrectAux, tmpCorrectForm, // correct
                                 4, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 verb, 0);
    expPairsList.append(currentPair);

    QTest::newRow("twoIdenticalVerbsInSameTense") <<
        correctSentence << verifiedSentence << expPairsList;

    // 12 Тест. В проверяемом предложении не хватает глагола, который является вспомогательным
    expPairsList.clear();
    correctSentence.clear();
    verifiedSentence.clear();

    correctSentence.addWordToEnd(new Pronoun("he"));
    correctSentence.addWordToEnd(new Verb("had"));
    correctSentence.addWordToEnd(new Noun("potential"));
    correctSentence.addWordToEnd(new Word("and"));
    correctSentence.addWordToEnd(new Word("now"));
    correctSentence.addWordToEnd(new Pronoun("he"));
    correctSentence.addWordToEnd(new Verb("has"));
    correctSentence.addWordToEnd(new Adjective("good"));
    correctSentence.addWordToEnd(new Noun("skills"));

    verifiedSentence.addWordToEnd(new Word("he"));
    verifiedSentence.addWordToEnd(new Word("have"));
    verifiedSentence.addWordToEnd(new Word("had"));
    verifiedSentence.addWordToEnd(new Word("potential"));
    verifiedSentence.addWordToEnd(new Word("and"));
    verifiedSentence.addWordToEnd(new Word("now"));
    verifiedSentence.addWordToEnd(new Word("good"));
    verifiedSentence.addWordToEnd(new Word("skills"));

    // 1 пара
    tmpCorrectForm.setWordForm(objective, nominative, singular, notSet);
    tmpVerifiedForm.setWordForm(objective, nominative, singular, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(0, tmpCorrectAux, tmpCorrectForm, // correct
                                 0, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 pron, 0);
    expPairsList.append(currentPair);

    // 2 пара
    tmpCorrectForm.setWordForm(pastSimple, notThird, preterite, notSet);
    tmpVerifiedForm.setWordForm(presentSimple, notThird, infinitive, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(1, tmpCorrectAux, tmpCorrectForm, // correct
                                 1, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 verb, 50);
    expPairsList.append(currentPair);

    // 3 пара
    tmpCorrectForm.setWordForm(pastSimple, notThird, preterite, notSet);
    tmpVerifiedForm.setWordForm(pastSimple, notThird, preterite, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(1, tmpCorrectAux, tmpCorrectForm, // correct
                                 2, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 verb, 0);
    expPairsList.append(currentPair);

    // 4 пара
    tmpCorrectForm.setWordForm(pastSimple, notThird, preterite, notSet);
    tmpVerifiedForm.setWordForm(presentPerf, notThird, pastParticiple, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();
    tmpVerifiedAux.append(1);

    currentPair.setAllParameters(1, tmpCorrectAux, tmpCorrectForm, // correct
                                 2, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 verb, 31);
    expPairsList.append(currentPair);

    // 5 пара
    tmpCorrectForm.setWordForm(singular, objective, notSet, notSet);
    tmpVerifiedForm.setWordForm(singular, objective, notSet, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(2, tmpCorrectAux, tmpCorrectForm, // correct
                                 3, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 noun, 0);
    expPairsList.append(currentPair);

    // 6 пара
    tmpCorrectForm.setWordForm(objective, nominative, singular, notSet);
    tmpVerifiedForm.setWordForm(objective, nominative, singular, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(5, tmpCorrectAux, tmpCorrectForm, // correct
                                 0, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 pron, 0);
    expPairsList.append(currentPair);

    // 7 пара
    tmpCorrectForm.setWordForm(presentSimple, third, infinitive, notSet);
    tmpVerifiedForm.setWordForm(presentSimple, notThird, infinitive, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(6, tmpCorrectAux, tmpCorrectForm, // correct
                                 1, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 verb, 20);
    expPairsList.append(currentPair);

    // 8 пара
    tmpCorrectForm.setWordForm(presentSimple, third, infinitive, notSet);
    tmpVerifiedForm.setWordForm(pastSimple, notThird, preterite, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(6, tmpCorrectAux, tmpCorrectForm, // correct
                                 2, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 verb, 70);
    expPairsList.append(currentPair);

    // 9 пара
    tmpCorrectForm.setWordForm(presentSimple, third, infinitive, notSet);
    tmpVerifiedForm.setWordForm(presentPerf, notThird, pastParticiple, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();
    tmpVerifiedAux.append(1);

    currentPair.setAllParameters(6, tmpCorrectAux, tmpCorrectForm, // correct
                                 2, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 verb, 100);
    expPairsList.append(currentPair);

    // 10 пара
    tmpCorrectForm.setWordForm(positive, notSet, notSet, notNeed);
    tmpVerifiedForm.setWordForm(positive, notSet, notSet, notNeed);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(7, tmpCorrectAux, tmpCorrectForm, // correct
                                 6, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 adj, 0);
    expPairsList.append(currentPair);

    // 11 пара
    tmpCorrectForm.setWordForm(plural, objective, notSet, notSet);
    tmpVerifiedForm.setWordForm(plural, objective, notSet, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(8, tmpCorrectAux, tmpCorrectForm, // correct
                                 7, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 noun, 0);
    expPairsList.append(currentPair);

    QTest::newRow("inVerifiedSentenceMissingAuxVerb") <<
        correctSentence << verifiedSentence << expPairsList;

    // 13. В вопросительном проверяемом предложении между глаголом и
    // вспомогательными есть посторонние слова
    expPairsList.clear();
    correctSentence.clear();
    verifiedSentence.clear();

    correctSentence.addWordToEnd(new Auxiliary("does"));
    correctSentence.addWordToEnd(new Pronoun("your"));
    correctSentence.addWordToEnd(new Noun("brother"));
    correctSentence.addWordToEnd(new Verb("like"));
    correctSentence.addWordToEnd(new Noun("apples"));

    verifiedSentence.addWordToEnd(new Word("does"));
    verifiedSentence.addWordToEnd(new Word("your"));
    verifiedSentence.addWordToEnd(new Word("brother"));
    verifiedSentence.addWordToEnd(new Word("like"));
    verifiedSentence.addWordToEnd(new Word("apples"));

    // 1 пара
    tmpCorrectForm.setWordForm(possessive, mainForm, singular, notSet);
    tmpVerifiedForm.setWordForm(possessive, mainForm, singular, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(1, tmpCorrectAux, tmpCorrectForm, // correct
                                 1, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 pron, 0);
    expPairsList.append(currentPair);

    // 2 пара
    tmpCorrectForm.setWordForm(possessive, mainForm, plural, notSet);
    tmpVerifiedForm.setWordForm(possessive, mainForm, plural, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(1, tmpCorrectAux, tmpCorrectForm, // correct
                                 1, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 pron, 0);
    expPairsList.append(currentPair);

    // 3 пара
    tmpCorrectForm.setWordForm(singular, objective, notSet, notSet);
    tmpVerifiedForm.setWordForm(singular, objective, notSet, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(2, tmpCorrectAux, tmpCorrectForm, // correct
                                 2, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 noun, 0);
    expPairsList.append(currentPair);

    // 4 пара
    tmpCorrectForm.setWordForm(presentSimple, third, infinitive, notSet);
    tmpVerifiedForm.setWordForm(presentSimple, notThird, infinitive, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();
    tmpCorrectAux.append(0);

    currentPair.setAllParameters(3, tmpCorrectAux, tmpCorrectForm, // correct
                                 3, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 verb, 20);
    expPairsList.append(currentPair);

    // 5 пара
    tmpCorrectForm.setWordForm(presentSimple, third, infinitive, notSet);
    tmpVerifiedForm.setWordForm(presentSimple, third, infinitive, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();
    tmpCorrectAux.append(0);
    tmpVerifiedAux.append(0);

    currentPair.setAllParameters(3, tmpCorrectAux, tmpCorrectForm, // correct
                                 3, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 verb, 0);
    expPairsList.append(currentPair);

    // 6 пара
    tmpCorrectForm.setWordForm(plural, objective, notSet, notSet);
    tmpVerifiedForm.setWordForm(plural, objective, notSet, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(4, tmpCorrectAux, tmpCorrectForm, // correct
                                 4, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 noun, 0);
    expPairsList.append(currentPair);

    QTest::newRow("betweenVerbAndAuxiliariesOtherWordsInVerified") <<
        correctSentence << verifiedSentence << expPairsList;

    // 14 Тест. Глагол be в правильном предложении, в проверяемом несколько его формы
    expPairsList.clear();
    correctSentence.clear();
    verifiedSentence.clear();

    correctSentence.addWordToEnd(new Pronoun("i"));
    correctSentence.addWordToEnd(new Verb("am"));
    correctSentence.addWordToEnd(new Noun("person"));
    correctSentence.addWordToEnd(new Pronoun("who"));
    correctSentence.addWordToEnd(new Auxiliary("does"));
    correctSentence.addWordToEnd(new Word("not"));
    correctSentence.addWordToEnd(new Verb("write"));
    correctSentence.addWordToEnd(new Noun("programs"));

    verifiedSentence.addWordToEnd(new Word("i"));
    verifiedSentence.addWordToEnd(new Word("was"));
    verifiedSentence.addWordToEnd(new Word("person"));
    verifiedSentence.addWordToEnd(new Word("who"));
    verifiedSentence.addWordToEnd(new Word("was"));
    verifiedSentence.addWordToEnd(new Word("not"));
    verifiedSentence.addWordToEnd(new Word("writing"));
    verifiedSentence.addWordToEnd(new Word("programs"));

    // 1 пара
    tmpCorrectForm.setWordForm(objective, nominative, singular, notSet);
    tmpVerifiedForm.setWordForm(objective, nominative, singular, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(0, tmpCorrectAux, tmpCorrectForm, // correct
                                 0, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 pron, 0);
    expPairsList.append(currentPair);

    // 2 пара
    tmpCorrectForm.setWordForm(presentSimple, first, infinitive, notSet);
    tmpVerifiedForm.setWordForm(pastSimple, notThird, preterite, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(1, tmpCorrectAux, tmpCorrectForm, // correct
                                 1, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 verb, 70);
    expPairsList.append(currentPair);

    // 3 пара
    tmpCorrectForm.setWordForm(presentSimple, first, infinitive, notSet);
    tmpVerifiedForm.setWordForm(pastSimple, notThird, preterite, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(1, tmpCorrectAux, tmpCorrectForm, // correct
                                 4, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 verb, 70);
    expPairsList.append(currentPair);

    // 4 пара
    tmpCorrectForm.setWordForm(singular, objective, notSet, notSet);
    tmpVerifiedForm.setWordForm(singular, objective, notSet, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(2, tmpCorrectAux, tmpCorrectForm, // correct
                                 2, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 noun, 0);
    expPairsList.append(currentPair);

    // 5 пара
    tmpCorrectForm.setWordForm(presentSimple, third, infinitive, notSet);
    tmpVerifiedForm.setWordForm(pastCont, notThird, presentParticiple, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();
    tmpCorrectAux.append(4);
    tmpCorrectAux.append(5);
    tmpVerifiedAux.append(4);
    tmpVerifiedAux.append(5);

    currentPair.setAllParameters(6, tmpCorrectAux, tmpCorrectForm, // correct
                                 6, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 verb, 100);
    expPairsList.append(currentPair);

    // 6 пара
    tmpCorrectForm.setWordForm(plural, objective, notSet, notSet);
    tmpVerifiedForm.setWordForm(plural, objective, notSet, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(7, tmpCorrectAux, tmpCorrectForm, // correct
                                 7, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 noun, 0);
    expPairsList.append(currentPair);

    QTest::newRow("differentFormsOfVerbBe") <<
        correctSentence << verifiedSentence << expPairsList;
}

void GenerateAllPairs::generateAllPairs()
{
    QFETCH(Sentence, correctSentence);
    QFETCH(Sentence, verifiedSentence);
    QFETCH(QList<Pair>, expPairs);

    LinkedSentences currentLink;
    correctSentence.setFormsInCorrectSentence();
    QList<Pair> realPairs = currentLink.generateAllPairs(correctSentence, verifiedSentence);

    Pair matchingPair;
    QString pairsDifference;
    int currentPairNumber = 0;

    QMutableListIterator<Pair> iExpPairsList(expPairs);

    while (iExpPairsList.hasNext())
    {
        if (!realPairs.removeOne(iExpPairsList.next()))
        { // Вывод сообщения о том, что текущая пара не была сопоставлена с реальной
            QVERIFY2(false, ("Pair number " + QString::number(currentPairNumber) + " with word: " +
                             correctSentence.getSentence()[iExpPairsList.value().getWordIndexFromCorrectSentence()]->getWord() + ": Wasn't matched").toUtf8());
        }

        currentPairNumber++;
    }

    QMutableListIterator<Pair> iCurrentRealPairsList(realPairs);
    while (iCurrentRealPairsList.hasNext())
    {
        iCurrentRealPairsList.next();

        QVERIFY2(false, ("Unexpected pair with main word index of correct sentence: " +
                         QString::number(iCurrentRealPairsList.value().getWordIndexFromCorrectSentence()) +
                         ", verified sentence: " +
                         QString::number(iCurrentRealPairsList.value().getWordIndexFromVerifiedSentence())).toUtf8());

        realPairs.removeOne(iCurrentRealPairsList.value());
    }
}

void GenerateAllPairs::initTestCase()
{
    Verb::readFileWithIrregularVerbs();
    Verb::readFileWithVerbLexems();
    Noun::readFileWithExceptionsNouns();
    Noun::readaFileWithOnlyPluralNouns();
    Noun::readFileWithUncountableNouns();
    Adjective::readFileWithAdjectiveExceptions();
}

QTEST_APPLESS_MAIN(GenerateAllPairs)

#include "test_GenerateAllPairs.moc"
