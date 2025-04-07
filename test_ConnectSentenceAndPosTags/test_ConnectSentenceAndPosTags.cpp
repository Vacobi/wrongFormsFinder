#include <QCoreApplication>
#include <QtTest/QtTest>

#include "../wrongFormsFinder/sentence.h"
#include "../wrongFormsFinder/adjective.h"
#include "../wrongFormsFinder/auxiliary.h"
#include "../wrongFormsFinder/noun.h"
#include "../wrongFormsFinder/numeral.h"
#include "../wrongFormsFinder/pronoun.h"
#include "../wrongFormsFinder/verb.h"

class ConnectSentenceAndPosTags: public QObject
{
    Q_OBJECT

private slots:
    void connectSentenceAndPosTags_data();
    void connectSentenceAndPosTags();
};

void ConnectSentenceAndPosTags::connectSentenceAndPosTags_data()
{
    QTest::addColumn<Sentence>("sentenceByWords");
    QTest::addColumn<Sentence>("posTagsByWords");
    QTest::addColumn<InputDataError>("expError");
    QTest::addColumn<Sentence>("expSentenceWithPosTags");

    Sentence sentence, posTags, expSentenceByPosTags;
    QList<Word*> sentenceByWords, posTagsByWords, expSentenceWithPosTags;
    InputDataError expError;

    // 1 Тест. Количество слов совпадает с количеством pos-тегов

    sentenceByWords.append(new Word("this"));
    sentenceByWords.append(new Word("is"));
    sentenceByWords.append(new Word("a"));
    sentenceByWords.append(new Word("sentence"));
    sentence.setSentence(sentenceByWords);

    posTagsByWords.append(new Word("det"));
    posTagsByWords.append(new Word("verb"));
    posTagsByWords.append(new Word("adp"));
    posTagsByWords.append(new Word("noun"));
    posTags.setSentence(posTagsByWords);

    expError.setParameters(sentenceSuccessfulProcessed, 4, 4, "");

    expSentenceWithPosTags.append(new Word("this"));
    expSentenceWithPosTags.append(new Verb("is"));
    expSentenceWithPosTags.append(new Word("a"));
    expSentenceWithPosTags.append(new Noun("sentence"));
    expSentenceByPosTags.setSentence(expSentenceWithPosTags);

    QTest::newRow("wordCountMatchesPosTagCount") <<
        sentence << posTags << expError << expSentenceByPosTags;

    // 2 Тест. 1 слово и 1 pos-тег
    sentenceByWords.clear();
    posTagsByWords.clear();
    expSentenceWithPosTags.clear();

    sentenceByWords.append(new Word("this"));
    sentence.setSentence(sentenceByWords);

    posTagsByWords.append(new Word("det"));
    posTags.setSentence(posTagsByWords);

    expError.setParameters(sentenceSuccessfulProcessed, 1, 1, "");

    expSentenceWithPosTags.append(new Word("this"));
    expSentenceByPosTags.setSentence(expSentenceWithPosTags);

    QTest::newRow("oneWordAndOnePosTag") <<
        sentence << posTags << expError << expSentenceByPosTags;

    // 3 Тест. Слов в предложении больше, чем pos-тегов
    sentenceByWords.clear();
    posTagsByWords.clear();
    expSentenceWithPosTags.clear();

    sentenceByWords.append(new Word("this"));
    sentenceByWords.append(new Word("is"));
    sentenceByWords.append(new Word("a"));
    sentenceByWords.append(new Word("sentence"));
    sentence.setSentence(sentenceByWords);

    posTagsByWords.append(new Word("det"));
    posTagsByWords.append(new Word("verb"));
    posTags.setSentence(posTagsByWords);

    expError.setParameters(fewerTagsThanWords, 4, 2, "");

    expSentenceWithPosTags.append(new Word("this"));
    expSentenceWithPosTags.append(new Word("is"));
    expSentenceWithPosTags.append(new Word("a"));
    expSentenceWithPosTags.append(new Word("sentence"));
    expSentenceByPosTags.setSentence(expSentenceWithPosTags);

    QTest::newRow("fewerTagsThanWords") <<
        sentence << posTags << expError << expSentenceByPosTags;

    // 4 Тест. Слов в предложении меньше, чем pos-тегов
    sentenceByWords.clear();
    posTagsByWords.clear();
    expSentenceWithPosTags.clear();

    sentenceByWords.append(new Word("this"));
    sentenceByWords.append(new Word("is"));
    sentenceByWords.append(new Word("a"));
    sentenceByWords.append(new Word("sentence"));
    sentence.setSentence(sentenceByWords);

    posTagsByWords.append(new Word("det"));
    posTagsByWords.append(new Word("verb"));
    posTagsByWords.append(new Word("adp"));
    posTagsByWords.append(new Word("noun"));
    posTagsByWords.append(new Word("verb"));
    posTagsByWords.append(new Word("noun"));
    posTagsByWords.append(new Word("adp"));
    posTags.setSentence(posTagsByWords);

    expError.setParameters(fewerWordsThanTags, 4, 7, "");

    expSentenceWithPosTags.append(new Word("this"));
    expSentenceWithPosTags.append(new Word("is"));
    expSentenceWithPosTags.append(new Word("a"));
    expSentenceWithPosTags.append(new Word("sentence"));
    expSentenceByPosTags.setSentence(expSentenceWithPosTags);

    QTest::newRow("fewerWordsThanTags") <<
        sentence << posTags << expError << expSentenceByPosTags;

    // 5 Тест. Некорректный pos-тег
    sentenceByWords.clear();
    posTagsByWords.clear();
    expSentenceWithPosTags.clear();

    sentenceByWords.append(new Word("this"));
    sentenceByWords.append(new Word("is"));
    sentenceByWords.append(new Word("a"));
    sentenceByWords.append(new Word("sentence"));
    sentence.setSentence(sentenceByWords);

    posTagsByWords.append(new Word("det"));
    posTagsByWords.append(new Word("veverbrb"));
    posTagsByWords.append(new Word("adp"));
    posTagsByWords.append(new Word("noun"));
    posTags.setSentence(posTagsByWords);

    expError.setParameters(incorrectPosTag, 4, 4, "veverbrb");

    expSentenceWithPosTags.append(new Word("this"));
    expSentenceWithPosTags.append(new Word("is"));
    expSentenceWithPosTags.append(new Word("a"));
    expSentenceWithPosTags.append(new Noun("sentence"));
    expSentenceByPosTags.setSentence(expSentenceWithPosTags);

    QTest::newRow("incorrectPosTag") <<
        sentence << posTags << expError << expSentenceByPosTags;

    // 6 Тест. Все pos-теги
    sentenceByWords.clear();
    posTagsByWords.clear();
    expSentenceWithPosTags.clear();

    sentenceByWords.append(new Word("one"));
    sentenceByWords.append(new Word("two"));
    sentenceByWords.append(new Word("three"));
    sentenceByWords.append(new Word("four"));
    sentenceByWords.append(new Word("five"));
    sentenceByWords.append(new Word("six"));
    sentenceByWords.append(new Word("seven"));
    sentenceByWords.append(new Word("eight"));
    sentenceByWords.append(new Word("nine"));
    sentenceByWords.append(new Word("ten"));
    sentenceByWords.append(new Word("eleven"));
    sentenceByWords.append(new Word("twelve"));
    sentenceByWords.append(new Word("thirteen"));
    sentenceByWords.append(new Word("fourteen"));
    sentenceByWords.append(new Word("fifteen"));
    sentence.setSentence(sentenceByWords);

    posTagsByWords.append(new Word("adj"));
    posTagsByWords.append(new Word("adp"));
    posTagsByWords.append(new Word("aux"));
    posTagsByWords.append(new Word("cconj"));
    posTagsByWords.append(new Word("det"));
    posTagsByWords.append(new Word("intj"));
    posTagsByWords.append(new Word("noun"));
    posTagsByWords.append(new Word("num"));
    posTagsByWords.append(new Word("part"));
    posTagsByWords.append(new Word("pron"));
    posTagsByWords.append(new Word("propn"));
    posTagsByWords.append(new Word("sconj"));
    posTagsByWords.append(new Word("sym"));
    posTagsByWords.append(new Word("verb"));
    posTagsByWords.append(new Word("x"));
    posTags.setSentence(posTagsByWords);

    expError.setParameters(sentenceSuccessfulProcessed, 4, 4, "");

    expSentenceWithPosTags.append(new Adjective("one"));
    expSentenceWithPosTags.append(new Word("two"));
    expSentenceWithPosTags.append(new Auxiliary("three"));
    expSentenceWithPosTags.append(new Word("four"));
    expSentenceWithPosTags.append(new Word("five"));
    expSentenceWithPosTags.append(new Word("six"));
    expSentenceWithPosTags.append(new Noun("seven"));
    expSentenceWithPosTags.append(new Numeral("eight"));
    expSentenceWithPosTags.append(new Word("nine"));
    expSentenceWithPosTags.append(new Pronoun("ten"));
    expSentenceWithPosTags.append(new Word("eleven"));
    expSentenceWithPosTags.append(new Word("twelve"));
    expSentenceWithPosTags.append(new Word("thirteen"));
    expSentenceWithPosTags.append(new Verb("fourteen"));
    expSentenceWithPosTags.append(new Word("fifteen"));
    expSentenceByPosTags.setSentence(expSentenceWithPosTags);

    QTest::newRow("allPosTags") <<
        sentence << posTags << expError << expSentenceByPosTags;
}

void ConnectSentenceAndPosTags::connectSentenceAndPosTags()
{
    QFETCH(Sentence, sentenceByWords);
    QFETCH(Sentence, posTagsByWords);
    QFETCH(InputDataError, expError);
    QFETCH(Sentence, expSentenceWithPosTags);

    InputDataError currentError;

    Sentence processedSentence;
    processedSentence.setSentence(sentenceByWords.getSentence());

    try
    {
        currentError = processedSentence.connectSentenceAndPosTags(posTagsByWords);
    }
    catch (InputDataError errorOfProcessing)
    {
        if (!(errorOfProcessing == expError))
        {
            QVERIFY2(false, errorOfProcessing.getFileProcessingResultByStr().toUtf8());
        }
    }

    if (currentError.getFileProcessingResult() == sentenceSuccessfulProcessed)
    {
        QList<Word*> realSentence = processedSentence.getSentence();
        QMutableListIterator<Word*> iRealSentenceWithTags(realSentence);

        QList<Word*> expSentence = expSentenceWithPosTags.getSentence();
        QMutableListIterator<Word*> iExpSentenceWithTags(expSentence);

        while (iRealSentenceWithTags.hasNext() && iExpSentenceWithTags.hasNext())
        {
            iRealSentenceWithTags.next();
            iExpSentenceWithTags.next();

            QVERIFY2 (iRealSentenceWithTags.value()->getWord() == iExpSentenceWithTags.value()->getWord(),
                (("Wrong word. expected: ") + iExpSentenceWithTags.value()->getWord() + ", real :" + iRealSentenceWithTags.value()->getWord()).toUtf8());

            QVERIFY2 (iRealSentenceWithTags.value()->getPossibleFormsOfWord() == iExpSentenceWithTags.value()->getPossibleFormsOfWord(),
                     (("Wrong forms in word: ") + iExpSentenceWithTags.value()->getWord()).toUtf8());

            QVERIFY2 (iRealSentenceWithTags.value()->getPosTag() == iExpSentenceWithTags.value()->getPosTag(),
                     (("Wrong pos tag in word: ") + iExpSentenceWithTags.value()->getWord() + ", expected: " + QString::number(iExpSentenceWithTags.value()->getPosTag())
                      + ", real :" +  QString::number(iRealSentenceWithTags.value()->getPosTag())).toUtf8());
        }

        while (iExpSentenceWithTags.hasNext())
        {
            iExpSentenceWithTags.next();

            QVERIFY2(false,
                     ("Unexpected word " + iExpSentenceWithTags.value()->getWord()
                      + " with type: " + iExpSentenceWithTags.value()->getType()).toUtf8());
        }

        while (iRealSentenceWithTags.hasNext())
        {
            iRealSentenceWithTags.next();

            QVERIFY2(false,
                     ("Unexpected word " + iRealSentenceWithTags.value()->getWord()
                      + " with type: " + iRealSentenceWithTags.value()->getType()).toUtf8());
        }
    }
}

QTEST_APPLESS_MAIN(ConnectSentenceAndPosTags)

#include "test_ConnectSentenceAndPosTags.moc"
