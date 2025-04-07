#include <QCoreApplication>
#include <QtTest/QtTest>

#include "../wrongFormsFinder/linkedsentences.h"
//#include "../wrongFormsFinder/adjective.h"
//#include "../wrongFormsFinder/auxiliary.h"
//#include "../wrongFormsFinder/noun.h"
//#include "../wrongFormsFinder/numeral.h"
//#include "../wrongFormsFinder/pronoun.h"
//#include "../wrongFormsFinder/verb.h"

#define mainWordInPair 1

class RecoursivePairsLink: public QObject
{
    Q_OBJECT

private slots:
    void recoursivePairsLink_data();
    void recoursivePairsLink();
};

void RecoursivePairsLink::recoursivePairsLink_data()
{
    QTest::addColumn<QList<Pair>>("allAvailablePairs");
    QTest::addColumn<int>("expFallacyOfSet");
    QTest::addColumn<int>("expCountOfLinkedWords");
    QTest::addColumn<int>("expTotalCountOfDifferentSets");

    Pair currentPair;
    WordForm tmpCorrectForm, tmpVerifiedForm;
    QList<int> tmpCorrectAux, tmpVerifiedAux;
    QList<Pair> entrySet;
    int fallacyOfSet, countOfLinkedWords, totalCountOfDifferentSets;

    // 1 Тест. Вся совокупность пар на входе является решением
    // 1 пара
    tmpCorrectForm.setWordForm(objective, nominative, notSet, notSet);
    tmpVerifiedForm.setWordForm(objective, nominative, notSet, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(0, tmpCorrectAux, tmpCorrectForm,
                                 2, tmpVerifiedAux, tmpVerifiedForm,
                                 pron, 0);
    entrySet.append(currentPair);

    // 2 пара
    tmpCorrectForm.setWordForm(presentSimple, notThird, infinitive, notSet);
    tmpVerifiedForm.setWordForm(presentSimple, notThird, infinitive, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(1, tmpCorrectAux, tmpCorrectForm,
                                 3, tmpVerifiedAux, tmpVerifiedForm,
                                 verb, 0);
    entrySet.append(currentPair);

    // 3 пара
    tmpCorrectForm.setWordForm(positive, notSet, notSet, notNeed);
    tmpVerifiedForm.setWordForm(positive, notSet, notSet, notNeed);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(3, tmpCorrectAux, tmpCorrectForm,
                                 0, tmpVerifiedAux, tmpVerifiedForm,
                                 adj, 0);
    entrySet.append(currentPair);

    // 4 пара
    tmpCorrectForm.setWordForm(singular, objective, notSet, notSet);
    tmpVerifiedForm.setWordForm(singular, objective, notSet, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(4, tmpCorrectAux, tmpCorrectForm,
                                 1, tmpVerifiedAux, tmpVerifiedForm,
                                 pron, 0);
    entrySet.append(currentPair);

    // Выходные данные
    fallacyOfSet = 0;
    countOfLinkedWords = 4;
    totalCountOfDifferentSets = 1;

    QTest::newRow("allPairsAreSolution") <<
        entrySet << fallacyOfSet << countOfLinkedWords << totalCountOfDifferentSets;

    // 2 Тест. Согласование происходит на основе ошибочности
    entrySet.clear();

    // 1 пара
    tmpCorrectForm.setWordForm(possessive, mainForm, notSet, notSet);
    tmpVerifiedForm.setWordForm(possessive, mainForm, notSet, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(0, tmpCorrectAux, tmpCorrectForm,
                                 0, tmpVerifiedAux, tmpVerifiedForm,
                                 pron, 0);
    entrySet.append(currentPair);

    // 2 пара
    tmpCorrectForm.setWordForm(possessive, mainForm, notSet, notSet);
    tmpVerifiedForm.setWordForm(possessive, absoluteForm, notSet, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(0, tmpCorrectAux, tmpCorrectForm,
                                 2, tmpVerifiedAux, tmpVerifiedForm,
                                 pron, 30);
    entrySet.append(currentPair);

    // 3 пара
    tmpCorrectForm.setWordForm(positive, notSet, notSet, notNeed);
    tmpVerifiedForm.setWordForm(positive, notSet, notSet, notNeed);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(1, tmpCorrectAux, tmpCorrectForm,
                                 1, tmpVerifiedAux, tmpVerifiedForm,
                                 adj, 0);
    entrySet.append(currentPair);

    // 4 пара
    tmpCorrectForm.setWordForm(singular, objective, notSet, notSet);
    tmpVerifiedForm.setWordForm(singular, objective, notSet, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(2, tmpCorrectAux, tmpCorrectForm, // correct
                                 2, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 noun, 0);
    entrySet.append(currentPair);

    // Выходные данные
    fallacyOfSet = 0;
    countOfLinkedWords = 3;
    totalCountOfDifferentSets = 1;

    QTest::newRow("linkingBasedOnFallacy") <<
        entrySet << fallacyOfSet << countOfLinkedWords << totalCountOfDifferentSets;

    // 3 Тест. Одному слову из правильного предложения соответствует
    // несколько слов из проверяемого с разной ошибочностью
    entrySet.clear();

    // 1 пара
    tmpCorrectForm.setWordForm(objective, nominative, notSet, notSet);
    tmpVerifiedForm.setWordForm(objective, objectivePron, notSet, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(0, tmpCorrectAux, tmpCorrectForm,
                                 0, tmpVerifiedAux, tmpVerifiedForm,
                                 pron, 30);
    entrySet.append(currentPair);

    // 2 пара
    tmpCorrectForm.setWordForm(objective, nominative, notSet, notSet);
    tmpVerifiedForm.setWordForm(possessive, mainForm, notSet, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(0, tmpCorrectAux, tmpCorrectForm,
                                 2, tmpVerifiedAux, tmpVerifiedForm,
                                 pron, 30);
    entrySet.append(currentPair);

    // 3 пара
    tmpCorrectForm.setWordForm(presentSimple, notThird, infinitive, notSet);
    tmpVerifiedForm.setWordForm(presentSimple, notThird, infinitive, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(1, tmpCorrectAux, tmpCorrectForm, // correct
                                 1, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 verb, 0);
    entrySet.append(currentPair);

    // 4 пара
    tmpCorrectForm.setWordForm(possessive, mainForm, singular, notSet);
    tmpVerifiedForm.setWordForm(objective, objectivePron, singular, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(2, tmpCorrectAux, tmpCorrectForm,
                                 0, tmpVerifiedAux, tmpVerifiedForm,
                                 pron, 60);
    entrySet.append(currentPair);

    // 5 пара
    tmpCorrectForm.setWordForm(possessive, mainForm, singular, notSet);
    tmpVerifiedForm.setWordForm(possessive, mainForm, singular, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(2, tmpCorrectAux, tmpCorrectForm,
                                 2, tmpVerifiedAux, tmpVerifiedForm,
                                 pron, 0);
    entrySet.append(currentPair);

    // 6 пара
    tmpCorrectForm.setWordForm(singular, objective, notSet, notSet);
    tmpVerifiedForm.setWordForm(singular, objective, notSet, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(3, tmpCorrectAux, tmpCorrectForm, // correct
                                 3, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 noun, 0);
    entrySet.append(currentPair);

    // Выходные данные
    fallacyOfSet = 30;
    countOfLinkedWords = 4;
    totalCountOfDifferentSets = 1;

    QTest::newRow("severalWordsFromVerifiedMatchesWithOneWordFromCorrect") <<
        entrySet << fallacyOfSet << countOfLinkedWords << totalCountOfDifferentSets;

    // 4 Тест. Одному слову из правильного предложения соответствует
    // несколько слов из проверяемого с одинаковой ошибочностью
    entrySet.clear();

    // 1 пара
    tmpCorrectForm.setWordForm(objective, nominative, notSet, notSet);
    tmpVerifiedForm.setWordForm(objective, nominative, notSet, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(0, tmpCorrectAux, tmpCorrectForm,
                                 2, tmpVerifiedAux, tmpVerifiedForm,
                                 pron, 0);
    entrySet.append(currentPair);

    // 2 пара
    tmpCorrectForm.setWordForm(presentSimple, notThird, infinitive, notSet);
    tmpVerifiedForm.setWordForm(presentSimple, notThird, infinitive, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(1, tmpCorrectAux, tmpCorrectForm, // correct
                                 3, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 verb, 0);
    entrySet.append(currentPair);

    // 3 пара
    tmpCorrectForm.setWordForm(pastSimple, notThird, preterite, notSet);
    tmpVerifiedForm.setWordForm(pastSimple, notThird, preterite, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(1, tmpCorrectAux, tmpCorrectForm, // correct
                                 3, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 verb, 0);
    entrySet.append(currentPair);

    // 4 пара
    tmpCorrectForm.setWordForm(singular, objective, notSet, notSet);
    tmpVerifiedForm.setWordForm(singular, objective, notSet, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(3, tmpCorrectAux, tmpCorrectForm, // correct
                                 1, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 noun, 0);
    entrySet.append(currentPair);

    // Выходные данные
    fallacyOfSet = 0;
    countOfLinkedWords = 3;
    totalCountOfDifferentSets = 2;

    QTest::newRow("severalWordsFromCorrectMatchesWithOneWordFromVerified") <<
        entrySet << fallacyOfSet << countOfLinkedWords << totalCountOfDifferentSets;


    // 5 Тест. Согласование происходит на основе количества согласованных
    // слов проверяемого предложения, есть пересечения слов при согласовании
    entrySet.clear();

    // 1 пара
    tmpCorrectForm.setWordForm(presentSimple, notThird, infinitive, notSet);
    tmpVerifiedForm.setWordForm(presentSimple, notThird, infinitive, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(0, tmpCorrectAux, tmpCorrectForm, // correct
                                 0, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 verb, 0);
    entrySet.append(currentPair);

    // 2 пара
    tmpCorrectForm.setWordForm(presentSimple, notThird, infinitive, notSet);
    tmpVerifiedForm.setWordForm(pastSimple, notThird, preterite, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(0, tmpCorrectAux, tmpCorrectForm, // correct
                                 1, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 verb, 50);
    entrySet.append(currentPair);

    // 3 пара
    tmpCorrectForm.setWordForm(presentSimple, notThird, infinitive, notSet);
    tmpVerifiedForm.setWordForm(presentPerf, notThird, pastParticiple, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();
    tmpVerifiedAux.append(0);

    currentPair.setAllParameters(0, tmpCorrectAux, tmpCorrectForm, // correct
                                 1, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 verb, 80);
    entrySet.append(currentPair);

    // 4 пара
    tmpCorrectForm.setWordForm(cardinal, notSet, notSet, notSet);
    tmpVerifiedForm.setWordForm(cardinal, notSet, notSet, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(1, tmpCorrectAux, tmpCorrectForm, // correct
                                 2, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 num, 0);
    entrySet.append(currentPair);

    // 5 пара
    tmpCorrectForm.setWordForm(plural, objective, notSet, notSet);
    tmpVerifiedForm.setWordForm(plural, objective, notSet, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(2, tmpCorrectAux, tmpCorrectForm, // correct
                                 3, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 noun, 0);
    entrySet.append(currentPair);

    // Выходные данные
    fallacyOfSet = 80;
    countOfLinkedWords = 4;
    totalCountOfDifferentSets = 1;

    QTest::newRow("linkingByCountOfLinkedWordsInVerifiedSentence") <<
        entrySet << fallacyOfSet << countOfLinkedWords << totalCountOfDifferentSets;

    // 6 Тест. На вход не поступило пар
    entrySet.clear();

    // Выходные данные
    fallacyOfSet = 0;
    countOfLinkedWords = 0;
    totalCountOfDifferentSets = 0;

    QTest::newRow("zeroPairsInInputData") <<
        entrySet << fallacyOfSet << countOfLinkedWords << totalCountOfDifferentSets;

    // 7 Тест. Пары всех поддерживаемых частей речи, все с ошибками
    entrySet.clear();

    // 1 пара
    tmpCorrectForm.setWordForm(objective, nominative, notSet, notSet);
    tmpVerifiedForm.setWordForm(possessive, mainForm, notSet, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(0, tmpCorrectAux, tmpCorrectForm,
                                 3, tmpVerifiedAux, tmpVerifiedForm,
                                 pron, 30);
    entrySet.append(currentPair);

    // 2 пара
    tmpCorrectForm.setWordForm(pastSimple, notThird, preterite, notSet);
    tmpVerifiedForm.setWordForm(presentSimple, notThird, infinitive, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(1, tmpCorrectAux, tmpCorrectForm, // correct
                                 4, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 verb, 50);
    entrySet.append(currentPair);

    // 3 пара
    tmpCorrectForm.setWordForm(cardinal, notSet, notSet, notSet);
    tmpVerifiedForm.setWordForm(ordinal, notSet, notSet, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(2, tmpCorrectAux, tmpCorrectForm, // correct
                                 0, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 num, 100);
    entrySet.append(currentPair);

    // 4 пара
    tmpCorrectForm.setWordForm(positive, notSet, notSet, notNeed);
    tmpVerifiedForm.setWordForm(comparative, notSet, notSet, notNeed);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(3, tmpCorrectAux, tmpCorrectForm,
                                 1, tmpVerifiedAux, tmpVerifiedForm,
                                 adj, 80);
    entrySet.append(currentPair);

    // 5 пара
    tmpCorrectForm.setWordForm(plural, objective, notSet, notSet);
    tmpVerifiedForm.setWordForm(singular, possessive, notSet, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(4, tmpCorrectAux, tmpCorrectForm, // correct
                                 2, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 noun, 100);
    entrySet.append(currentPair);

    // Выходные данные
    fallacyOfSet = 360;
    countOfLinkedWords = 5;
    totalCountOfDifferentSets = 1;

    QTest::newRow("allPosAndAllWithMisstakes") <<
        entrySet << fallacyOfSet << countOfLinkedWords << totalCountOfDifferentSets;

    // 8 Тест. В сформированных парах имеются пересечения слов
    entrySet.clear();

    // 1 пара
    tmpCorrectForm.setWordForm(objective, nominative, notSet, notSet);
    tmpVerifiedForm.setWordForm(objective, nominative, notSet, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(0, tmpCorrectAux, tmpCorrectForm,
                                 0, tmpVerifiedAux, tmpVerifiedForm,
                                 pron, 0);
    entrySet.append(currentPair);

    // 2 пара
    tmpCorrectForm.setWordForm(objective, nominative, notSet, notSet);
    tmpVerifiedForm.setWordForm(objective, nominative, notSet, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(0, tmpCorrectAux, tmpCorrectForm,
                                 4, tmpVerifiedAux, tmpVerifiedForm,
                                 pron, 0);
    entrySet.append(currentPair);

    // 3 пара
    tmpCorrectForm.setWordForm(futureSimple, notThird, infinitive, notSet);
    tmpVerifiedForm.setWordForm(pastSimple, notThird, preterite, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();
    tmpCorrectAux.append(1);

    currentPair.setAllParameters(2, tmpCorrectAux, tmpCorrectForm, // correct
                                 2, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 verb, 80);
    entrySet.append(currentPair);

    // 4 пара
    tmpCorrectForm.setWordForm(futureSimple, notThird, infinitive, notSet);
    tmpVerifiedForm.setWordForm(presentPerf, notThird, pastParticiple, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();
    tmpCorrectAux.append(1);
    tmpVerifiedAux.append(1);

    currentPair.setAllParameters(2, tmpCorrectAux, tmpCorrectForm, // correct
                                 2, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 verb, 80);
    entrySet.append(currentPair);

    // 5 пара
    tmpCorrectForm.setWordForm(objective, nominative, notSet, notSet);
    tmpVerifiedForm.setWordForm(objective, nominative, notSet, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(4, tmpCorrectAux, tmpCorrectForm,
                                 0, tmpVerifiedAux, tmpVerifiedForm,
                                 pron, 0);
    entrySet.append(currentPair);

    // 6 пара
    tmpCorrectForm.setWordForm(objective, nominative, notSet, notSet);
    tmpVerifiedForm.setWordForm(objective, nominative, notSet, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(4, tmpCorrectAux, tmpCorrectForm,
                                 4, tmpVerifiedAux, tmpVerifiedForm,
                                 pron, 0);
    entrySet.append(currentPair);

    // 7 пара
    tmpCorrectForm.setWordForm(presentSimple, notThird, infinitive, notSet);
    tmpVerifiedForm.setWordForm(presentSimple, notThird, infinitive, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(5, tmpCorrectAux, tmpCorrectForm, // correct
                                 1, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 verb, 0);
    entrySet.append(currentPair);

    // 8 пара
    tmpCorrectForm.setWordForm(presentSimple, notThird, infinitive, notSet);
    tmpVerifiedForm.setWordForm(pastSimple, notThird, preterite, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(5, tmpCorrectAux, tmpCorrectForm, // correct
                                 5, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 verb, 50);
    entrySet.append(currentPair);

    // 9 пара
    tmpCorrectForm.setWordForm(singular, objective, notSet, notSet);
    tmpVerifiedForm.setWordForm(singular, objective, notSet, notSet);

    tmpCorrectAux.clear();
    tmpVerifiedAux.clear();

    currentPair.setAllParameters(6, tmpCorrectAux, tmpCorrectForm, // correct
                                 6, tmpVerifiedAux, tmpVerifiedForm, // verified
                                 noun, 0);
    entrySet.append(currentPair);

    // Выходные данные
    fallacyOfSet = 130;
    countOfLinkedWords = 6;
    totalCountOfDifferentSets = 2;

    QTest::newRow("intersectionsOfWordsInPairs") <<
        entrySet << fallacyOfSet << countOfLinkedWords << totalCountOfDifferentSets;
}

void RecoursivePairsLink::recoursivePairsLink()
{
    QFETCH(QList<Pair>, allAvailablePairs);
    QFETCH(int, expFallacyOfSet);
    QFETCH(int, expCountOfLinkedWords);
    QFETCH(int, expTotalCountOfDifferentSets);

    LinkedSentences currentRealLink;
    QList<Pair> currentPairList;
    currentRealLink.recoursivePairsLink(allAvailablePairs, 0, currentPairList, 0, 0);

    int fallacyOfRealSet, realCountOfLinkedWords, realTotalCountOfDifferentSets;
    QList<QSet<Pair>> tmpReal = currentRealLink.getLinkedSentences();
    QMutableListIterator<QSet<Pair>> iRealLinkedOptions(tmpReal);
    realTotalCountOfDifferentSets = 0;

    // Смотрим все получившиеся варианты согласования
    while(iRealLinkedOptions.hasNext())
    {
        iRealLinkedOptions.next();

        QMutableSetIterator<Pair> iRealCurrentLinkedOption(iRealLinkedOptions.value());

        fallacyOfRealSet = 0;
        realCountOfLinkedWords = 0;
        while (iRealCurrentLinkedOption.hasNext())
        {
            iRealCurrentLinkedOption.next();

            fallacyOfRealSet += iRealCurrentLinkedOption.value().getDegreeOfFallacy();
            realCountOfLinkedWords += mainWordInPair + iRealCurrentLinkedOption.value().getIndexesOfAuxiliariesInVerified().count();
        }

        QVERIFY2(fallacyOfRealSet == expFallacyOfSet, ("Set of linked pairs with index " +
                                                       QString::number(realTotalCountOfDifferentSets) +
                                                       " has expected fallacy: " +
                                                       QString::number(expFallacyOfSet) +
                                                       ", real fallacy: " +
                                                       QString::number(fallacyOfRealSet)).toUtf8());

        QVERIFY2(realCountOfLinkedWords == expCountOfLinkedWords, ("Set of linked pairs with index " +
                                                       QString::number(realTotalCountOfDifferentSets) +
                                                       " has expected count of linked words: " +
                                                       QString::number(expCountOfLinkedWords) +
                                                       ", count of linked words: " +
                                                       QString::number(realCountOfLinkedWords)).toUtf8());

        realTotalCountOfDifferentSets++;
    }

    QVERIFY2(realTotalCountOfDifferentSets == expTotalCountOfDifferentSets,
             ("Expected " +
              QString::number(expTotalCountOfDifferentSets) +
              " different linked sets, real:  " +
              QString::number(realTotalCountOfDifferentSets)).toUtf8());
}

QTEST_APPLESS_MAIN(RecoursivePairsLink)

#include "test_RecoursivePairsLink.moc"
