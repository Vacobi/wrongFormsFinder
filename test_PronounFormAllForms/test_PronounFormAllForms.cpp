#include <QCoreApplication>
#include <QtTest/QtTest>

#include "../wrongFormsFinder/pronoun.h"

class TestPronounFormAllForms: public QObject
{
    Q_OBJECT

private slots:
    void pronounFormAllForms_data();
    void pronounFormAllForms();
};

void TestPronounFormAllForms::pronounFormAllForms_data()
{
    QTest::addColumn<QString>("word");
    QTest::addColumn<QSet<Pronoun>>("expFormsOfWord");

    Pronoun currentPronoun;
    QSet<Pronoun> allFormsOfPronoun;
    WordForm tmpWordForm;
    QSet<WordForm> currentWordForms;

    // 1 Тест. На входе личное местоимение именительного падежа
    currentWordForms.clear();
    tmpWordForm.setWordForm(objective, nominative, singular, notSet);
    currentWordForms.insert(tmpWordForm);
    currentPronoun.setWordWithForms("i", currentWordForms);
    allFormsOfPronoun.insert(currentPronoun);

    currentWordForms.clear();
    tmpWordForm.setWordForm(objective, objectivePron, singular, notSet);
    currentWordForms.insert(tmpWordForm);
    currentPronoun.setWordWithForms("me", currentWordForms);
    allFormsOfPronoun.insert(currentPronoun);

    currentWordForms.clear();
    tmpWordForm.setWordForm(possessive, mainForm, singular, notSet);
    currentWordForms.insert(tmpWordForm);
    currentPronoun.setWordWithForms("my", currentWordForms);
    allFormsOfPronoun.insert(currentPronoun);

    currentWordForms.clear();
    tmpWordForm.setWordForm(possessive, absoluteForm, singular, notSet);
    currentWordForms.insert(tmpWordForm);
    currentPronoun.setWordWithForms("mine", currentWordForms);
    allFormsOfPronoun.insert(currentPronoun);

    QTest::newRow("objectiveNominativePronoun") << "i" << allFormsOfPronoun;

    // 2 Тест. На входе личное местоимения объектного падежа
    allFormsOfPronoun.clear();

    currentWordForms.clear();
    tmpWordForm.setWordForm(objective, nominative, plural, notSet);
    currentWordForms.insert(tmpWordForm);
    currentPronoun.setWordWithForms("we", currentWordForms);
    allFormsOfPronoun.insert(currentPronoun);

    currentWordForms.clear();
    tmpWordForm.setWordForm(objective, objectivePron, plural, notSet);
    currentWordForms.insert(tmpWordForm);
    currentPronoun.setWordWithForms("us", currentWordForms);
    allFormsOfPronoun.insert(currentPronoun);

    currentWordForms.clear();
    tmpWordForm.setWordForm(possessive, mainForm, plural, notSet);
    currentWordForms.insert(tmpWordForm);
    currentPronoun.setWordWithForms("our", currentWordForms);
    allFormsOfPronoun.insert(currentPronoun);

    currentWordForms.clear();
    tmpWordForm.setWordForm(possessive, absoluteForm, plural, notSet);
    currentWordForms.insert(tmpWordForm);
    currentPronoun.setWordWithForms("ours", currentWordForms);
    allFormsOfPronoun.insert(currentPronoun);

    QTest::newRow("objectivePronoun") << "us" << allFormsOfPronoun;

    // 3 Тест. На входе притяжательная основная форма местоимения
    allFormsOfPronoun.clear();

    currentWordForms.clear();
    tmpWordForm.setWordForm(objective, nominative, plural, notSet);
    currentWordForms.insert(tmpWordForm);
    currentPronoun.setWordWithForms("we", currentWordForms);
    allFormsOfPronoun.insert(currentPronoun);

    currentWordForms.clear();
    tmpWordForm.setWordForm(objective, objectivePron, plural, notSet);
    currentWordForms.insert(tmpWordForm);
    currentPronoun.setWordWithForms("us", currentWordForms);
    allFormsOfPronoun.insert(currentPronoun);

    currentWordForms.clear();
    tmpWordForm.setWordForm(possessive, mainForm, plural, notSet);
    currentWordForms.insert(tmpWordForm);
    currentPronoun.setWordWithForms("our", currentWordForms);
    allFormsOfPronoun.insert(currentPronoun);

    currentWordForms.clear();
    tmpWordForm.setWordForm(possessive, absoluteForm, plural, notSet);
    currentWordForms.insert(tmpWordForm);
    currentPronoun.setWordWithForms("ours", currentWordForms);
    allFormsOfPronoun.insert(currentPronoun);

    QTest::newRow("possessivePronoun") << "our" << allFormsOfPronoun;

    // 4 Тест. На входе притяжательная абсолютная форма местоимения
    allFormsOfPronoun.clear();

    currentWordForms.clear();
    tmpWordForm.setWordForm(objective, nominative, plural, notSet);
    currentWordForms.insert(tmpWordForm);
    currentPronoun.setWordWithForms("they", currentWordForms);
    allFormsOfPronoun.insert(currentPronoun);

    currentWordForms.clear();
    tmpWordForm.setWordForm(objective, objectivePron, plural, notSet);
    currentWordForms.insert(tmpWordForm);
    currentPronoun.setWordWithForms("them", currentWordForms);
    allFormsOfPronoun.insert(currentPronoun);

    currentWordForms.clear();
    tmpWordForm.setWordForm(possessive, mainForm, plural, notSet);
    currentWordForms.insert(tmpWordForm);
    currentPronoun.setWordWithForms("their", currentWordForms);
    allFormsOfPronoun.insert(currentPronoun);

    currentWordForms.clear();
    tmpWordForm.setWordForm(possessive, absoluteForm, plural, notSet);
    currentWordForms.insert(tmpWordForm);
    currentPronoun.setWordWithForms("theirs", currentWordForms);
    allFormsOfPronoun.insert(currentPronoun);

    QTest::newRow("possesiveAbsoluteFormPronoun") << "theirs" << allFormsOfPronoun;

    // 5 Тест. Прилагательное пишется одинаково в нескольких формах
    allFormsOfPronoun.clear();

    currentWordForms.clear();
    tmpWordForm.setWordForm(objective, nominative, singular, notSet);
    currentWordForms.insert(tmpWordForm);
    currentPronoun.setWordWithForms("she", currentWordForms);
    allFormsOfPronoun.insert(currentPronoun);

    currentWordForms.clear();
    tmpWordForm.setWordForm(objective, objectivePron, singular, notSet);
    currentWordForms.insert(tmpWordForm);
    tmpWordForm.setWordForm(possessive, mainForm, singular, notSet);
    currentWordForms.insert(tmpWordForm);
    currentPronoun.setWordWithForms("her", currentWordForms);
    allFormsOfPronoun.insert(currentPronoun);

    currentWordForms.clear();
    tmpWordForm.setWordForm(possessive, absoluteForm, singular, notSet);
    currentWordForms.insert(tmpWordForm);
    currentPronoun.setWordWithForms("hers", currentWordForms);
    allFormsOfPronoun.insert(currentPronoun);

    QTest::newRow("pronounHasSeveralFormsWithOneWord") << "her" << allFormsOfPronoun;

    // 6 Тест. На входе местоимение, которое может быть как в единственном числе, так и во множественном
    allFormsOfPronoun.clear();

    currentWordForms.clear();
    tmpWordForm.setWordForm(objective, nominative, singular, notSet);
    currentWordForms.insert(tmpWordForm);
    tmpWordForm.setWordForm(objective, nominative, plural, notSet);
    currentWordForms.insert(tmpWordForm);
    tmpWordForm.setWordForm(objective, objectivePron, singular, notSet);
    currentWordForms.insert(tmpWordForm);
    tmpWordForm.setWordForm(objective, objectivePron, plural, notSet);
    currentWordForms.insert(tmpWordForm);
    currentPronoun.setWordWithForms("you", currentWordForms);
    allFormsOfPronoun.insert(currentPronoun);

    currentWordForms.clear();
    tmpWordForm.setWordForm(possessive, mainForm, singular, notSet);
    currentWordForms.insert(tmpWordForm);
    tmpWordForm.setWordForm(possessive, mainForm, plural, notSet);
    currentWordForms.insert(tmpWordForm);
    currentPronoun.setWordWithForms("your", currentWordForms);
    allFormsOfPronoun.insert(currentPronoun);

    currentWordForms.clear();
    tmpWordForm.setWordForm(possessive, absoluteForm, singular, notSet);
    currentWordForms.insert(tmpWordForm);
    tmpWordForm.setWordForm(possessive, absoluteForm, plural, notSet);
    currentWordForms.insert(tmpWordForm);
    currentPronoun.setWordWithForms("yours", currentWordForms);
    allFormsOfPronoun.insert(currentPronoun);

    QTest::newRow("pronounCanBeSingularAndPlural") << "you" << allFormsOfPronoun;
}

void TestPronounFormAllForms::pronounFormAllForms()
{
    QFETCH(QString, word);
    QFETCH(QSet<Pronoun>, expFormsOfWord);

    Pronoun currentExpWord, currentRealWord;

    Pronoun realWord(word);
    QSet<Word*> tmpRealWords = realWord.formAllForms();

    QMutableSetIterator<Pronoun> iExpPronouns(expFormsOfWord);

    while (iExpPronouns.hasNext())
    {
        Word* tmpMatchedWord;
        if (iExpPronouns.next().hasMatchingWord(tmpRealWords, tmpMatchedWord))
        {
            QString misstakeMessage;
            if(!iExpPronouns.value().wordsAreEqual(tmpMatchedWord, misstakeMessage))
            {
                QVERIFY2(false, misstakeMessage.toUtf8());
            }

            tmpRealWords.remove(tmpMatchedWord);
        }
        else
        {
            QSet<WordForm> currentWordForms = iExpPronouns.value().getPossibleFormsOfWord();
            QMutableSetIterator<WordForm> iCurrentForm(currentWordForms);

            while (iCurrentForm.hasNext())
            {
                iCurrentForm.next();

                QVERIFY2(false,
                         ("Word " + iExpPronouns.value().getWord() +
                          " has no match. " + iCurrentForm.value().getWordFormByStr()
                          + "; ").toUtf8());
            }
        }
    }

    QSetIterator<Word*> iUnmatchedPronoun(tmpRealWords);
    while (iUnmatchedPronoun.hasNext())
    {
        QSet<WordForm> tmpUnmatchedForms = iUnmatchedPronoun.next()->getPossibleFormsOfWord();
        QMutableSetIterator<WordForm> iUnmatchedForm(tmpUnmatchedForms);

        while (iUnmatchedForm.hasNext())
        {
            QVERIFY2(false,
                     ("Word " + iUnmatchedPronoun.next()->getWord() +
                      " is unexpected with form: " +
                      iUnmatchedForm.value().getWordFormByStr()
                      + "; ").toUtf8());
        }
    }
}

QTEST_APPLESS_MAIN(TestPronounFormAllForms)

#include "test_PronounFormAllForms.moc"
