#include <QCoreApplication>
#include <QtTest/QtTest>

#include "../wrongFormsFinder/sentence.h"

class TestparseSentence: public QObject
{
    Q_OBJECT

private slots:
    void parseSentence_data();
    void parseSentence();
};

void TestparseSentence::parseSentence_data()
{
    QTest::addColumn<QString>("sentenceInString");
    QTest::addColumn<QList<Word>>("expWords");

    QList<Word> currentSolution;

    // 1 Тест. Несколько слов, разделенных пробелами
    currentSolution.append(Word("this"));
    currentSolution.append(Word("is"));
    currentSolution.append(Word("a"));
    currentSolution.append(Word("sentence"));

    QTest::newRow("multipleWordsSeparatedBySpaces") <<
        "This is a sentence" << currentSolution;

    // 2 Тест. Несколько слов, между ними знаки препинания
    currentSolution.clear();

    currentSolution.append(Word("this"));
    currentSolution.append(Word("is"));
    currentSolution.append(Word("a"));
    currentSolution.append(Word("sentence"));

    QTest::newRow("multipleWordsSeparatedByPunctuations") <<
        "This,,,is.,,.,.,a :sentence" << currentSolution;

    // 3 Тест. Имеется слово, в котором имеются цифры
    currentSolution.clear();

    currentSolution.append(Word("this"));
    currentSolution.append(Word("is"));
    currentSolution.append(Word("a1"));
    currentSolution.append(Word("sentence"));

    QTest::newRow("numeralsIntoWord") <<
        "This is a1 sentence" << currentSolution;

    // 4 Тест. Имеется слово, в котором имеется апостроф
    currentSolution.clear();

    currentSolution.append(Word("this"));
    currentSolution.append(Word("is"));
    currentSolution.append(Word("a"));
    currentSolution.append(Word("sentence'"));

    QTest::newRow("apostropheIntoWord") <<
        "This is a sentence'" << currentSolution;

    // 5 Тест. Имеется слово, в котором имеется несколько апострофов
    currentSolution.clear();

    currentSolution.append(Word("this"));
    currentSolution.append(Word("is"));
    currentSolution.append(Word("a"));
    currentSolution.append(Word("sentence'between"));

    QTest::newRow("multipleApostrophesIntoWord") <<
        "This is a sentence'between'after" << currentSolution;

    // 6 Тест. Нет слов
    currentSolution.clear();

    QTest::newRow("noWords") <<
        ",,..,,:;№%    %" << currentSolution;

    // 7 Тест. Все слова в верхнем регистре
    currentSolution.clear();

    currentSolution.append(Word("this"));
    currentSolution.append(Word("is"));
    currentSolution.append(Word("a"));
    currentSolution.append(Word("sentence"));

    QTest::newRow("allWordsInUppercase") <<
        "THIS IS A SENTENCE" << currentSolution;

    // 8 Тест. Одно Слово в предложении
    currentSolution.clear();

    currentSolution.append(Word("this"));

    QTest::newRow("onlyOneWord") <<
        "This" << currentSolution;
}

void TestparseSentence::parseSentence()
{
    QFETCH(QString, sentenceInString);
    QFETCH(QList<Word>, expWords);

    Sentence realSentenceByWords;
    QMutableListIterator<Word> iExpWords(expWords);

    realSentenceByWords.parseSentence(sentenceInString);

    QList<Word*> tmpReal = realSentenceByWords.getSentence();

    QMutableListIterator<Word*> iRealWords(tmpReal);

    while (iExpWords.hasNext() && iRealWords.hasNext())
    {
        QVERIFY2(iExpWords.next().getWord() == iRealWords.next()->getWord(),
                 ("Words do not match. Expected: " + iExpWords.value().getWord() + " , Real: " + iRealWords.value()->getWord()).toUtf8());
    }

    while (iExpWords.hasNext())
    {
        QVERIFY2(false, ("Word: " + iExpWords.next().getWord()).toUtf8() + " not exist.");
    }

    while (iRealWords.hasNext())
    {
        QVERIFY2(false, ("Word: " + iRealWords.next()->getWord()).toUtf8() + " not waited.");
    }
}

QTEST_APPLESS_MAIN(TestparseSentence)

#include "test_parseSentence.moc"
