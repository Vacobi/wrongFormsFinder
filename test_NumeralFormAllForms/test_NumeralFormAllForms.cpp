#include <QCoreApplication>
#include <QtTest/QtTest>

#include "../wrongFormsFinder/numeral.h"

class TestNumeralFormAllForms: public QObject
{
    Q_OBJECT

private slots:
    void numeralFormAllForms_data();
    void numeralFormAllForms();
};

void TestNumeralFormAllForms::numeralFormAllForms_data()
{
    QTest::addColumn<QString>("word");
    QTest::addColumn<QSet<Numeral>>("expFormsOfWord");

    Numeral cardinalForm, ordinalForm;

    // ------------------ 1 test
    QSet<Numeral> allFormsOfOne;
    cardinalForm.setForm("one", cardinal);
    ordinalForm.setForm("first", ordinal);
    allFormsOfOne.insert(cardinalForm);
    allFormsOfOne.insert(ordinalForm);

    QTest::newRow("numeralExceptionOne") << "one" << allFormsOfOne;

    // ------------------ 2 test
    QSet<Numeral> allFormsOfTwo;
    cardinalForm.setForm("two", cardinal);
    ordinalForm.setForm("second", ordinal);
    allFormsOfTwo << cardinalForm << ordinalForm;

    QTest::newRow("numeralExceptionTwo") << "two" << allFormsOfTwo;

    // ------------------ 3 test
    QSet<Numeral> allFormsOfThree;
    cardinalForm.setForm("three", cardinal);
    ordinalForm.setForm("third", ordinal);
    allFormsOfThree << cardinalForm << ordinalForm;

    QTest::newRow("numeralExceptionThree") << "three" << allFormsOfThree;

    // ------------------ 4 test
    QSet<Numeral> allFormsOfFive;
    cardinalForm.setForm("five", cardinal);
    ordinalForm.setForm("fifth", ordinal);
    allFormsOfFive << cardinalForm << ordinalForm;

    QTest::newRow("cardinalEndsWithVE") << "five" << allFormsOfFive;

    // ------------------ 5 test
    QSet<Numeral> allFormsOfTwenty;
    cardinalForm.setForm("twenty", cardinal);
    ordinalForm.setForm("twentieth", ordinal);
    allFormsOfTwenty << cardinalForm << ordinalForm;

    QTest::newRow("cardinalEndsWithY") << "twenty" << allFormsOfTwenty;

    // ------------------ 6 test
    QSet<Numeral> allFormsOfNine;
    cardinalForm.setForm("nine", cardinal);
    ordinalForm.setForm("ninth", ordinal);
    allFormsOfNine << cardinalForm << ordinalForm;

    QTest::newRow("numeralExceptionNine") << "nine" << allFormsOfNine;

    // ------------------ 7 test
    QSet<Numeral> allFormsOfSeven;
    cardinalForm.setForm("seven", cardinal);
    ordinalForm.setForm("seventh", ordinal);
    allFormsOfSeven << cardinalForm << ordinalForm;

    QTest::newRow("commonNumeral") << "seven" << allFormsOfSeven;

    // ------------------ 8 test
    QSet<Numeral> allFormsOfFirst;
    cardinalForm.setForm("one", cardinal);
    ordinalForm.setForm("first", ordinal);
    allFormsOfFirst << cardinalForm << ordinalForm;

    QTest::newRow("numeralExceptionFirst") << "first" << allFormsOfFirst;

    // ------------------ 9 test
    QSet<Numeral> allFormsOfSecond;
    cardinalForm.setForm("two", cardinal);
    ordinalForm.setForm("second", ordinal);
    allFormsOfSecond << cardinalForm << ordinalForm;

    QTest::newRow("numeralExceptionSecond") << "second" << allFormsOfSecond;

    // ------------------ 10 test
    QSet<Numeral> allFormsOfThird;
    cardinalForm.setForm("three", cardinal);
    ordinalForm.setForm("third", ordinal);
    allFormsOfThird << cardinalForm << ordinalForm;

    QTest::newRow("numeralExceptionThird") << "third" << allFormsOfThird;

    // ------------------ 11 test
    QSet<Numeral> allFormsOfFifth;
    cardinalForm.setForm("five", cardinal);
    ordinalForm.setForm("fifth", ordinal);
    allFormsOfFifth << cardinalForm << ordinalForm;

    QTest::newRow("numeralInOrdinalEndsWithFTH") << "fifth" << allFormsOfFifth;

    // ------------------ 12 test
    QSet<Numeral> allFormsOfTwentieth;
    cardinalForm.setForm("twenty", cardinal);
    ordinalForm.setForm("twentieth", ordinal);
    allFormsOfTwentieth << cardinalForm << ordinalForm;

    QTest::newRow("numeralInOrdinalEndsWithIETH") << "twentieth" << allFormsOfTwentieth;

    // ------------------ 13 test
    QSet<Numeral> allFormsOfNinth;
    cardinalForm.setForm("nine", cardinal);
    ordinalForm.setForm("ninth", ordinal);
    allFormsOfNinth << cardinalForm << ordinalForm;

    QTest::newRow("numeralExceptionNinth") << "ninth" << allFormsOfNinth;

    // ------------------ 14 test
    QSet<Numeral> allFormsOfSeventh;
    cardinalForm.setForm("seven", cardinal);
    ordinalForm.setForm("seventh", ordinal);
    allFormsOfSeventh << cardinalForm << ordinalForm;

    QTest::newRow("commonNumeralInOrdinal") << "seventh" << allFormsOfSeventh;
}

void TestNumeralFormAllForms::numeralFormAllForms()
{
    QFETCH(QString, word);
    QFETCH(QSet<Numeral>, expFormsOfWord);

    Numeral currentExpWord, currentRealWord;

    Numeral realWord(word);
    QSet<Word*> tmpRealWords = realWord.formAllForms();

    QMutableSetIterator<Numeral> iExpNums(expFormsOfWord);

    while (iExpNums.hasNext())
    {
        Word* tmpMatchedWord;
        if (iExpNums.next().hasMatchingWord(tmpRealWords, tmpMatchedWord))
        {
            QString misstakeMessage;
            if(!iExpNums.value().wordsAreEqual(tmpMatchedWord, misstakeMessage))
            {
                QVERIFY2(false, misstakeMessage.toUtf8());
            }

            tmpRealWords.remove(tmpMatchedWord);
        }
        else
        {
            QSet<WordForm> currentWordForms = iExpNums.value().getPossibleFormsOfWord();
            QMutableSetIterator<WordForm> iCurrentForm(currentWordForms);

            while (iCurrentForm.hasNext())
            {
                iCurrentForm.next();

                QVERIFY2(false,
                         ("Word " + iExpNums.value().getWord() +
                          " has no match: " + iCurrentForm.value().getWordFormByStr()).toUtf8());
            }
        }
    }

    QSetIterator<Word*> iUnmatchedNumeral(tmpRealWords);
    while (iUnmatchedNumeral.hasNext())
    {
        QSet<WordForm> tmpUnmatchedForms = iUnmatchedNumeral.next()->getPossibleFormsOfWord();
        QMutableSetIterator<WordForm> iUnmatchedForm(tmpUnmatchedForms);

        while (iUnmatchedForm.hasNext())
        {
            QVERIFY2(false,
                     ("Word " + iUnmatchedNumeral.next()->getWord() +
                      " is unexpected with form: " +
                      iUnmatchedForm.value().getWordFormByStr()
                      + "; ").toUtf8());
        }
    }
}

QTEST_APPLESS_MAIN(TestNumeralFormAllForms)

#include "test_NumeralFormAllForms.moc"
