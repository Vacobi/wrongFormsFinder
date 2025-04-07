#include <QCoreApplication>
#include <QtTest/QtTest>

#include "../wrongFormsFinder/noun.h"

class TestNounFormAllForms: public QObject
{
    Q_OBJECT

private slots:
    void nounFormAllForms_data();
    void nounFormAllForms();

    void initTestCase();
};

void TestNounFormAllForms::nounFormAllForms_data()
{
    QTest::addColumn<QString>("word");
    QTest::addColumn<QSet<Noun>>("expFormsOfWord");

    Noun currentNoun;
    QSet<Noun> allFormsOfNoun;
    WordForm tmpWordForm;
    QSet<WordForm> currentWordForms;

    // 1 Тест. Слово имеет только множественную форму
    currentWordForms.clear();
    tmpWordForm.setWordForm(plural, objective, notSet, notSet);
    currentWordForms.insert(tmpWordForm);
    currentNoun.setWordWithForms("jeans", currentWordForms);
    allFormsOfNoun.insert(currentNoun);

    currentWordForms.clear();
    tmpWordForm.setWordForm(plural, possessive, notSet, notSet);
    currentWordForms.insert(tmpWordForm);
    currentNoun.setWordWithForms("jeans's", currentWordForms);
    allFormsOfNoun.insert(currentNoun);

    QTest::newRow("nounHasOnlyPlural") << "jeans" << allFormsOfNoun;

    // 2 Тест. Неисчисляемое существительное
    allFormsOfNoun.clear();

    currentWordForms.clear();
    tmpWordForm.setWordForm(uncountable, objective, notSet, notSet);
    currentWordForms.insert(tmpWordForm);
    currentNoun.setWordWithForms("information", currentWordForms);
    allFormsOfNoun.insert(currentNoun);

    currentWordForms.clear();
    tmpWordForm.setWordForm(uncountable, possessive, notSet, notSet);
    currentWordForms.insert(tmpWordForm);
    currentNoun.setWordWithForms("information's", currentWordForms);
    allFormsOfNoun.insert(currentNoun);

    QTest::newRow("nounIsUncountable") << "information" << allFormsOfNoun;

//    // 3 Тест. Существительное в единственном числе, объектном падеже, оканчивается на -y
    allFormsOfNoun.clear();

    currentWordForms.clear();
    tmpWordForm.setWordForm(singular, objective, notSet, notSet);
    currentWordForms.insert(tmpWordForm);
    currentNoun.setWordWithForms("family", currentWordForms);
    allFormsOfNoun.insert(currentNoun);

    currentWordForms.clear();
    tmpWordForm.setWordForm(singular, possessive, notSet, notSet);
    currentWordForms.insert(tmpWordForm);
    currentNoun.setWordWithForms("family's", currentWordForms);
    allFormsOfNoun.insert(currentNoun);

    currentWordForms.clear();
    tmpWordForm.setWordForm(plural, objective, notSet, notSet);
    currentWordForms.insert(tmpWordForm);
    currentNoun.setWordWithForms("families", currentWordForms);
    allFormsOfNoun.insert(currentNoun);

    currentWordForms.clear();
    tmpWordForm.setWordForm(plural, possessive, notSet, notSet);
    currentWordForms.insert(tmpWordForm);
    currentNoun.setWordWithForms("families'", currentWordForms);
    allFormsOfNoun.insert(currentNoun);

    QTest::newRow("nounIsSingularObjectiveCaseEndsWithY") << "family" << allFormsOfNoun;

    // 4 Тест. Существительное в единственном числе, объектном падеже, оканчивается на -ss
    allFormsOfNoun.clear();

    currentWordForms.clear();
    tmpWordForm.setWordForm(singular, objective, notSet, notSet);
    currentWordForms.insert(tmpWordForm);
    currentNoun.setWordWithForms("dress", currentWordForms);
    allFormsOfNoun.insert(currentNoun);

    currentWordForms.clear();
    tmpWordForm.setWordForm(singular, possessive, notSet, notSet);
    currentWordForms.insert(tmpWordForm);
    currentNoun.setWordWithForms("dress's", currentWordForms);
    allFormsOfNoun.insert(currentNoun);

    currentWordForms.clear();
    tmpWordForm.setWordForm(plural, objective, notSet, notSet);
    currentWordForms.insert(tmpWordForm);
    currentNoun.setWordWithForms("dresses", currentWordForms);
    allFormsOfNoun.insert(currentNoun);

    currentWordForms.clear();
    tmpWordForm.setWordForm(plural, possessive, notSet, notSet);
    currentWordForms.insert(tmpWordForm);
    currentNoun.setWordWithForms("dresses'", currentWordForms);
    allFormsOfNoun.insert(currentNoun);

//    QTest::newRow("nounIsSingularPossessiveCaseEndsWithSS") << "dress's" << allFormsOfNoun;

//    // 5 Тест. Существительное во множественном числе, объектном падеже,
//    // в единственном числе оканчивается на -ef
    allFormsOfNoun.clear();

    currentWordForms.clear();
    tmpWordForm.setWordForm(singular, objective, notSet, notSet);
    currentWordForms.insert(tmpWordForm);
    currentNoun.setWordWithForms("wife", currentWordForms);
    allFormsOfNoun.insert(currentNoun);

    currentWordForms.clear();
    tmpWordForm.setWordForm(singular, possessive, notSet, notSet);
    currentWordForms.insert(tmpWordForm);
    currentNoun.setWordWithForms("wife's", currentWordForms);
    allFormsOfNoun.insert(currentNoun);

    currentWordForms.clear();
    tmpWordForm.setWordForm(plural, objective, notSet, notSet);
    currentWordForms.insert(tmpWordForm);
    currentNoun.setWordWithForms("wives", currentWordForms);
    allFormsOfNoun.insert(currentNoun);

    currentWordForms.clear();
    tmpWordForm.setWordForm(plural, possessive, notSet, notSet);
    currentWordForms.insert(tmpWordForm);
    currentNoun.setWordWithForms("wives'", currentWordForms);
    allFormsOfNoun.insert(currentNoun);

    QTest::newRow("nounIsPluralObjectiveCaseEndsWithEFInSingular") << "wives" << allFormsOfNoun;

//    // 6 Тест. Существительное во множественном числе, притяжательном падеже,
//    // в единственном числе оканчивается на -t
    allFormsOfNoun.clear();

    currentWordForms.clear();
    tmpWordForm.setWordForm(singular, objective, notSet, notSet);
    currentWordForms.insert(tmpWordForm);
    currentNoun.setWordWithForms("cat", currentWordForms);
    allFormsOfNoun.insert(currentNoun);

    currentWordForms.clear();
    tmpWordForm.setWordForm(singular, possessive, notSet, notSet);
    currentWordForms.insert(tmpWordForm);
    currentNoun.setWordWithForms("cat's", currentWordForms);
    allFormsOfNoun.insert(currentNoun);

    currentWordForms.clear();
    tmpWordForm.setWordForm(plural, objective, notSet, notSet);
    currentWordForms.insert(tmpWordForm);
    currentNoun.setWordWithForms("cats", currentWordForms);
    allFormsOfNoun.insert(currentNoun);

    currentWordForms.clear();
    tmpWordForm.setWordForm(plural, possessive, notSet, notSet);
    currentWordForms.insert(tmpWordForm);
    currentNoun.setWordWithForms("cats'", currentWordForms);
    allFormsOfNoun.insert(currentNoun);

    QTest::newRow("nounIsPluralObjectiveCaseEndsWithTInSingular") << "cats'" << allFormsOfNoun;

    // 7 Тест. Существительное в единственном числе, исключение
    allFormsOfNoun.clear();

    currentWordForms.clear();
    tmpWordForm.setWordForm(singular, objective, notSet, notSet);
    currentWordForms.insert(tmpWordForm);
    currentNoun.setWordWithForms("man", currentWordForms);
    allFormsOfNoun.insert(currentNoun);

    currentWordForms.clear();
    tmpWordForm.setWordForm(singular, possessive, notSet, notSet);
    currentWordForms.insert(tmpWordForm);
    currentNoun.setWordWithForms("man's", currentWordForms);
    allFormsOfNoun.insert(currentNoun);

    currentWordForms.clear();
    tmpWordForm.setWordForm(plural, objective, notSet, notSet);
    currentWordForms.insert(tmpWordForm);
    currentNoun.setWordWithForms("men", currentWordForms);
    allFormsOfNoun.insert(currentNoun);

    currentWordForms.clear();
    tmpWordForm.setWordForm(plural, possessive, notSet, notSet);
    currentWordForms.insert(tmpWordForm);
    currentNoun.setWordWithForms("men's", currentWordForms);
    allFormsOfNoun.insert(currentNoun);

    QTest::newRow("exceptionNounIsSingular") << "man" << allFormsOfNoun;

    // 8 Тест. Существительное во множественном числе, исключение
    allFormsOfNoun.clear();

    currentWordForms.clear();
    tmpWordForm.setWordForm(singular, objective, notSet, notSet);
    currentWordForms.insert(tmpWordForm);
    currentNoun.setWordWithForms("tooth", currentWordForms);
    allFormsOfNoun.insert(currentNoun);

    currentWordForms.clear();
    tmpWordForm.setWordForm(singular, possessive, notSet, notSet);
    currentWordForms.insert(tmpWordForm);
    currentNoun.setWordWithForms("tooth's", currentWordForms);
    allFormsOfNoun.insert(currentNoun);

    currentWordForms.clear();
    tmpWordForm.setWordForm(plural, objective, notSet, notSet);
    currentWordForms.insert(tmpWordForm);
    currentNoun.setWordWithForms("teeth", currentWordForms);
    allFormsOfNoun.insert(currentNoun);

    currentWordForms.clear();
    tmpWordForm.setWordForm(plural, possessive, notSet, notSet);
    currentWordForms.insert(tmpWordForm);
    currentNoun.setWordWithForms("teeth's", currentWordForms);
    allFormsOfNoun.insert(currentNoun);

    QTest::newRow("exceptionNounIsPlural") << "teeth" << allFormsOfNoun;
}

void TestNounFormAllForms::nounFormAllForms()
{
    QFETCH(QString, word);
    QFETCH(QSet<Noun>, expFormsOfWord);

    Noun currentExpWord, currentRealWord;
    QSet<WordForm> expWordForms;

    Noun realWord(word);
    QSet<Word*> tmpRealWords = realWord.formAllForms();

    QMutableSetIterator<Noun> iExpNouns(expFormsOfWord);

    while (iExpNouns.hasNext())
    {
        Word* tmpMatchedWord;
        if (iExpNouns.next().hasMatchingWord(tmpRealWords, tmpMatchedWord))
        {
            QString misstakeMessage;
            if(!iExpNouns.value().wordsAreEqual(tmpMatchedWord, misstakeMessage))
            {
                QVERIFY2(false, misstakeMessage.toUtf8());
            }

            tmpRealWords.remove(tmpMatchedWord);
        }
        else
        {
            QSet<WordForm> currentWordForms = iExpNouns.value().getPossibleFormsOfWord();
            QMutableSetIterator<WordForm> iCurrentForm(currentWordForms);

            while (iCurrentForm.hasNext())
            {
                iCurrentForm.next();

                QVERIFY2(false,
                         ("Word " + iExpNouns.value().getWord() +
                          " has no match. " + iCurrentForm.value().getWordFormByStr()
                          + "; ").toUtf8());
            }
        }
    }

    QSetIterator<Word*> iUnmatchedNoun(tmpRealWords);
    while (iUnmatchedNoun.hasNext())
    {
        QSet<WordForm> tmpUnmatchedForms = iUnmatchedNoun.next()->getPossibleFormsOfWord();
        QMutableSetIterator<WordForm> iUnmatchedForm(tmpUnmatchedForms);

        while (iUnmatchedForm.hasNext())
        {
            QVERIFY2(false,
                     ("Word " + iUnmatchedNoun.next()->getWord() +
                      " is unexpected with form: " +
                      iUnmatchedForm.value().getWordFormByStr()
                      + "; ").toUtf8());
        }
    }
}

void TestNounFormAllForms::initTestCase()
{
    Noun::readFileWithExceptionsNouns();
    Noun::readaFileWithOnlyPluralNouns();
    Noun::readFileWithUncountableNouns();
}

QTEST_APPLESS_MAIN(TestNounFormAllForms)

#include "test_NounFormAllForms.moc"
