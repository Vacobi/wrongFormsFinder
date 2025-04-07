#include <QCoreApplication>

#include "../wrongFormsFinder/adjective.h"
#include <QtTest\QtTest>

class TestAdjectiveFormAllForms: public QObject
{
    Q_OBJECT

private slots:
    void adjectiveFormAllForms_data();
    void adjectiveFormAllForms();

    void initTestCase();
};

void TestAdjectiveFormAllForms::adjectiveFormAllForms_data()
{
    QTest::addColumn<QString>("word");
    QTest::addColumn<QSet<Adjective>>("expFormsOfWord");

    Adjective currentAdjective;
    QSet<Adjective> allFormsOfAdjective;
    WordForm tmpWordForm;
    QSet<WordForm> currentWordForms;

    // Тест 1. Слово-исключение good, положительная степень
    currentWordForms.clear();
    tmpWordForm.setWordForm(positive, notSet, notSet, notNeed);
    currentWordForms.insert(tmpWordForm);
    currentAdjective.setWordWithForms("good", currentWordForms);
    allFormsOfAdjective.insert(currentAdjective);

    currentWordForms.clear();
    tmpWordForm.setWordForm(comparative, notSet, notSet, notNeed);
    currentWordForms.insert(tmpWordForm);
    currentAdjective.setWordWithForms("better", currentWordForms);
    allFormsOfAdjective.insert(currentAdjective);

    currentWordForms.clear();
    tmpWordForm.setWordForm(superlative, notSet, notSet, notNeed);
    currentWordForms.insert(tmpWordForm);
    currentAdjective.setWordWithForms("best", currentWordForms);
    allFormsOfAdjective.insert(currentAdjective);

    QTest::newRow("exceptionPositiveAdjectiveGood") << "good" << allFormsOfAdjective;

    // Тест 2. Односложное прилагательное заканчивается на -e, положительная степень
    allFormsOfAdjective.clear();

    currentWordForms.clear();
    tmpWordForm.setWordForm(positive, notSet, notSet, notNeed);
    currentWordForms.insert(tmpWordForm);
    currentAdjective.setWordWithForms("nice", currentWordForms);
    allFormsOfAdjective.insert(currentAdjective);

    currentWordForms.clear();
    tmpWordForm.setWordForm(comparative, notSet, notSet, notNeed);
    currentWordForms.insert(tmpWordForm);
    currentAdjective.setWordWithForms("nicer", currentWordForms);
    allFormsOfAdjective.insert(currentAdjective);

    currentWordForms.clear();
    tmpWordForm.setWordForm(superlative, notSet, notSet, notNeed);
    currentWordForms.insert(tmpWordForm);
    currentAdjective.setWordWithForms("nicest", currentWordForms);
    allFormsOfAdjective.insert(currentAdjective);

    QTest::newRow("oneSyllableAdjectiveEndsWithE") << "nice" << allFormsOfAdjective;

    // Тест 3. Односложное прилагательное оканчивается сочетанием
    // согласная + гласная + согласная, положительная степень
    allFormsOfAdjective.clear();

    currentWordForms.clear();
    tmpWordForm.setWordForm(positive, notSet, notSet, notNeed);
    currentWordForms.insert(tmpWordForm);
    currentAdjective.setWordWithForms("big", currentWordForms);
    allFormsOfAdjective.insert(currentAdjective);

    currentWordForms.clear();
    tmpWordForm.setWordForm(comparative, notSet, notSet, notNeed);
    currentWordForms.insert(tmpWordForm);
    currentAdjective.setWordWithForms("bigger", currentWordForms);
    allFormsOfAdjective.insert(currentAdjective);

    currentWordForms.clear();
    tmpWordForm.setWordForm(superlative, notSet, notSet, notNeed);
    currentWordForms.insert(tmpWordForm);
    currentAdjective.setWordWithForms("biggest", currentWordForms);
    allFormsOfAdjective.insert(currentAdjective);

    QTest::newRow("oneSyllableAdjectiveEndsWithConsonantVowelConsonant") << "big" <<
        allFormsOfAdjective;

    // Тест 4. Односложное прилагательное, которое не подходит под остальные правила
    allFormsOfAdjective.clear();

    currentWordForms.clear();
    tmpWordForm.setWordForm(positive, notSet, notSet, notNeed);
    currentWordForms.insert(tmpWordForm);
    currentAdjective.setWordWithForms("clean", currentWordForms);
    allFormsOfAdjective.insert(currentAdjective);

    currentWordForms.clear();
    tmpWordForm.setWordForm(comparative, notSet, notSet, notNeed);
    currentWordForms.insert(tmpWordForm);
    currentAdjective.setWordWithForms("cleaner", currentWordForms);
    allFormsOfAdjective.insert(currentAdjective);

    currentWordForms.clear();
    tmpWordForm.setWordForm(superlative, notSet, notSet, notNeed);
    currentWordForms.insert(tmpWordForm);
    currentAdjective.setWordWithForms("cleanest", currentWordForms);
    allFormsOfAdjective.insert(currentAdjective);

    QTest::newRow("oneSyllableAdjective") << "clean" <<
        allFormsOfAdjective;

    // Тест 5. В прилагательном 2 слога и последняя буква -y, положительная степень
    allFormsOfAdjective.clear();

    currentWordForms.clear();
    tmpWordForm.setWordForm(positive, notSet, notSet, notNeed);
    currentWordForms.insert(tmpWordForm);
    currentAdjective.setWordWithForms("cozy", currentWordForms);
    allFormsOfAdjective.insert(currentAdjective);

    currentWordForms.clear();
    tmpWordForm.setWordForm(comparative, notSet, notSet, notNeed);
    currentWordForms.insert(tmpWordForm);
    currentAdjective.setWordWithForms("cozier", currentWordForms);
    allFormsOfAdjective.insert(currentAdjective);

    currentWordForms.clear();
    tmpWordForm.setWordForm(superlative, notSet, notSet, notNeed);
    currentWordForms.insert(tmpWordForm);
    currentAdjective.setWordWithForms("coziest", currentWordForms);
    allFormsOfAdjective.insert(currentAdjective);

    QTest::newRow("twoSyllablePositiveAdjectiveEndsWithY") << "cozy" <<
        allFormsOfAdjective;

    // Тест 6. Сравнительная и превосходная степени образуются
    // с помощью добавления more и most соответственно
    allFormsOfAdjective.clear();

    currentWordForms.clear();
    tmpWordForm.setWordForm(positive, notSet, notSet, notNeed);
    currentWordForms.insert(tmpWordForm);
    tmpWordForm.setWordForm(comparative, notSet, notSet, more);
    currentWordForms.insert(tmpWordForm);
    tmpWordForm.setWordForm(superlative, notSet, notSet, most);
    currentWordForms.insert(tmpWordForm);
    currentAdjective.setWordWithForms("convenient", currentWordForms);
    allFormsOfAdjective.insert(currentAdjective);

    QTest::newRow("comparativeAndSuperlativeWithMoreAndMost") << "convenient" <<
        allFormsOfAdjective;

    // Тест 7. Слово-исключение в сравнительной степени
    allFormsOfAdjective.clear();

    currentWordForms.clear();
    tmpWordForm.setWordForm(positive, notSet, notSet, notNeed);
    currentWordForms.insert(tmpWordForm);
    currentAdjective.setWordWithForms("bad", currentWordForms);
    allFormsOfAdjective.insert(currentAdjective);

    currentWordForms.clear();
    tmpWordForm.setWordForm(comparative, notSet, notSet, notNeed);
    currentWordForms.insert(tmpWordForm);
    currentAdjective.setWordWithForms("worse", currentWordForms);
    allFormsOfAdjective.insert(currentAdjective);

    currentWordForms.clear();
    tmpWordForm.setWordForm(superlative, notSet, notSet, notNeed);
    currentWordForms.insert(tmpWordForm);
    currentAdjective.setWordWithForms("worst", currentWordForms);
    allFormsOfAdjective.insert(currentAdjective);

    QTest::newRow("exceptionInComparativeForm") << "worse" <<
        allFormsOfAdjective;

    // Тест 8. Слово не исключение, в сравнительной степени
    allFormsOfAdjective.clear();

    currentWordForms.clear();
    tmpWordForm.setWordForm(positive, notSet, notSet, notNeed);
    currentWordForms.insert(tmpWordForm);
    currentAdjective.setWordWithForms("clean", currentWordForms);
    allFormsOfAdjective.insert(currentAdjective);

    currentWordForms.clear();
    tmpWordForm.setWordForm(comparative, notSet, notSet, notNeed);
    currentWordForms.insert(tmpWordForm);
    currentAdjective.setWordWithForms("cleaner", currentWordForms);
    allFormsOfAdjective.insert(currentAdjective);

    currentWordForms.clear();
    tmpWordForm.setWordForm(superlative, notSet, notSet, notNeed);
    currentWordForms.insert(tmpWordForm);
    currentAdjective.setWordWithForms("cleanest", currentWordForms);
    allFormsOfAdjective.insert(currentAdjective);

    QTest::newRow("notExceptionAdjectiveInComparativeForm") << "cleaner" <<
        allFormsOfAdjective;

    // Тест 9. Слово-исключение в превосходной степени
    allFormsOfAdjective.clear();

    currentWordForms.clear();
    tmpWordForm.setWordForm(positive, notSet, notSet, notNeed);
    currentWordForms.insert(tmpWordForm);
    currentAdjective.setWordWithForms("far", currentWordForms);
    allFormsOfAdjective.insert(currentAdjective);

    currentWordForms.clear();
    tmpWordForm.setWordForm(comparative, notSet, notSet, notNeed);
    currentWordForms.insert(tmpWordForm);
    currentAdjective.setWordWithForms("further", currentWordForms);
    allFormsOfAdjective.insert(currentAdjective);

    currentWordForms.clear();
    tmpWordForm.setWordForm(superlative, notSet, notSet, notNeed);
    currentWordForms.insert(tmpWordForm);
    currentAdjective.setWordWithForms("furthest", currentWordForms);
    allFormsOfAdjective.insert(currentAdjective);

    QTest::newRow("exceptionAdjectiveInSuperlativeForm") << "furthest" <<
        allFormsOfAdjective;

    // Тест 10. Слово не исключение, в превосходной степени
    allFormsOfAdjective.clear();

    currentWordForms.clear();
    tmpWordForm.setWordForm(positive, notSet, notSet, notNeed);
    currentWordForms.insert(tmpWordForm);
    currentAdjective.setWordWithForms("round", currentWordForms);
    allFormsOfAdjective.insert(currentAdjective);

    currentWordForms.clear();
    tmpWordForm.setWordForm(comparative, notSet, notSet, notNeed);
    currentWordForms.insert(tmpWordForm);
    currentAdjective.setWordWithForms("rounder", currentWordForms);
    allFormsOfAdjective.insert(currentAdjective);

    currentWordForms.clear();
    tmpWordForm.setWordForm(superlative, notSet, notSet, notNeed);
    currentWordForms.insert(tmpWordForm);
    currentAdjective.setWordWithForms("roundest", currentWordForms);
    allFormsOfAdjective.insert(currentAdjective);

    QTest::newRow("notExceptionAdjectiveInSuperlativeForm") << "roundest" <<
        allFormsOfAdjective;
}

void TestAdjectiveFormAllForms::adjectiveFormAllForms()
{
    QFETCH(QString, word);
    QFETCH(QSet<Adjective>, expFormsOfWord);

    Adjective currentExpWord, currentRealWord;
    QSet<WordForm> expWordForms;

    Adjective realWord(word);
    QSet<Word*> tmpRealWords = realWord.formAllForms();

    QMutableSetIterator<Adjective> iExpAdjectives(expFormsOfWord);

    while (iExpAdjectives.hasNext())
    {
        Word* tmpMatchedWord;
        if (iExpAdjectives.next().hasMatchingWord(tmpRealWords, tmpMatchedWord))
        {
            QString misstakeMessage;
            if(!iExpAdjectives.value().wordsAreEqual(tmpMatchedWord, misstakeMessage))
            {
                QVERIFY2(false, misstakeMessage.toUtf8());
            }

            tmpRealWords.remove(tmpMatchedWord);
        }
        else
        {
            QSet<WordForm> currentWordForms = iExpAdjectives.value().getPossibleFormsOfWord();
            QMutableSetIterator<WordForm> iCurrentForm(currentWordForms);

            while (iCurrentForm.hasNext())
            {
                iCurrentForm.next();

                QVERIFY2(false,
                         ("Word " + iExpAdjectives.value().getWord() +
                          " with forms: " + iCurrentForm.value().getWordFormByStr()
                          + " has no match.").toUtf8());
            }
        }
    }

    QSetIterator<Word*> iUnmatchedAdjective(tmpRealWords);
    while (iUnmatchedAdjective.hasNext())
    {
        QSet<WordForm> tmpUnmatchedForms = iUnmatchedAdjective.next()->getPossibleFormsOfWord();
        QMutableSetIterator<WordForm> iUnmatchedForm(tmpUnmatchedForms);

        while (iUnmatchedForm.hasNext())
        {
            QVERIFY2(false,
                     ("Word " + iUnmatchedAdjective.next()->getWord() +
                      " is unexpected with form: " +
                      iUnmatchedForm.value().getWordFormByStr()).toUtf8());
        }
    }
}

void TestAdjectiveFormAllForms::initTestCase()
{
    Adjective::readFileWithAdjectiveExceptions();
}

QTEST_MAIN(TestAdjectiveFormAllForms)

#include "test_AdjectiveFormAllForms.moc"
