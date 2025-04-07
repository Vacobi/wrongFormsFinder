#include <QCoreApplication>
#include <QtTest/QtTest>

#include "../wrongFormsFinder/sentence.h"

class TestSetFormsInCorrectSentence: public QObject
{
    Q_OBJECT

private slots:
    void setFormsInCorrectSentence_data();
    void setFormsInCorrectSentence();

    void initTestCase();
};

void TestSetFormsInCorrectSentence::setFormsInCorrectSentence_data()
{
    QTest::addColumn<Sentence>("sentence");
    QTest::addColumn<Sentence>("sentenceWithExpForms");

    Sentence sentence, sentenceWithExpForms;
    WordForm tmpWordForm;
    QList<int> tmpVerbAuxiliaries;
    QSet<WordForm> currentSetOfForms;

    // Тест 1. Слова без вспомогательных, разные части речи
    sentence.addWordToEnd(new Pronoun("i"));
    sentence.addWordToEnd(new Verb("have"));
    sentence.addWordToEnd(new Word("a"));
    sentence.addWordToEnd(new Adjective("positive"));
    sentence.addWordToEnd(new Noun("attitude"));

    tmpWordForm.setWordForm(objective, nominative, singular, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpPronoun.setPronWithForms("i", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Pronoun("i", currentSetOfForms));

    currentSetOfForms.clear();
    tmpVerbAuxiliaries.clear();
    tmpWordForm.setWordForm(presentSimple, notThird, infinitive, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpVerb.setVerbWithForms("have", currentSetOfForms, tmpVerbAuxiliaries);
    sentenceWithExpForms.addWordToEnd(new Verb("have", currentSetOfForms, tmpVerbAuxiliaries));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(notSet, notSet, notSet, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpWord.setWordWithForms("a", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Word("a", currentSetOfForms));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(positive, notSet, notSet, notNeed);
    currentSetOfForms.insert(tmpWordForm);
    //tmpAdjective.setAdjWithForms("positive", currentSetOfForms, -1);
    sentenceWithExpForms.addWordToEnd(new Adjective("positive", currentSetOfForms, -1));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(singular, objective, notSet, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpNoun.setNounWithForms("attitude", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Noun("attitude", currentSetOfForms));

    QTest::newRow("onePairToEveryWord") <<
        sentence << sentenceWithExpForms;

    // Тест 2. Превосходное прилагательное со вспомогательным
    sentence.clear();
    sentenceWithExpForms.clear();

    sentence.addWordToEnd(new Auxiliary("most"));
    sentence.addWordToEnd(new Adjective("interesting"));
    sentence.addWordToEnd(new Noun("film"));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(notSet, notSet, notSet, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpAuxiliary.setAuxWithForms("most", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Auxiliary("most", currentSetOfForms));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(superlative, notSet, notSet, most);
    currentSetOfForms.insert(tmpWordForm);
    //tmpAdjective.setAdjWithForms("interesting", currentSetOfForms, 0);
    sentenceWithExpForms.addWordToEnd(new Adjective("interesting", currentSetOfForms, 0));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(singular, objective, notSet, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpNoun.setNounWithForms("attitude", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Noun("film", currentSetOfForms));

    QTest::newRow("superlativeAdjWithAuxiliary") <<
        sentence << sentenceWithExpForms;

    // Тест 3. Сравнительное прилагательное со вспомогательными
    sentence.clear();
    sentenceWithExpForms.clear();

    sentence.addWordToEnd(new Auxiliary("more"));
    sentence.addWordToEnd(new Adjective("interesting"));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(notSet, notSet, notSet, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpAuxiliary.setAuxWithForms("more", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Auxiliary("more", currentSetOfForms));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(comparative, notSet, notSet, more);
    currentSetOfForms.insert(tmpWordForm);
    //tmpAdjective.setAdjWithForms("interesting", currentSetOfForms, 0);
    sentenceWithExpForms.addWordToEnd(new Adjective("interesting", currentSetOfForms, 0));

    currentSetOfForms.clear();

    QTest::newRow("comparativeAdjWithAuxiliary") <<
        sentence << sentenceWithExpForms;

    // Тест 4. Глагол во времени Present Simple
    sentence.clear();
    sentenceWithExpForms.clear();

    sentence.addWordToEnd(new Pronoun("i"));
    sentence.addWordToEnd(new Verb("am"));
    sentence.addWordToEnd(new Noun("student"));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(objective, nominative, singular, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpPronoun.setPronWithForms("i", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Pronoun("i", currentSetOfForms));

    currentSetOfForms.clear();
    tmpVerbAuxiliaries.clear();
    tmpWordForm.setWordForm(presentSimple, first, infinitive, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpVerb.setVerbWithForms("am", currentSetOfForms, tmpVerbAuxiliaries);
    sentenceWithExpForms.addWordToEnd(new Verb("am", currentSetOfForms, tmpVerbAuxiliaries));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(singular, objective, notSet, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpNoun.setNounWithForms("student", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Noun("student", currentSetOfForms));

    QTest::newRow("verbInPresentSimple") <<
        sentence << sentenceWithExpForms;

    // Тест 5. Глагол во времени Present Simple, подлежащее в 3-м лице
    sentence.clear();
    sentenceWithExpForms.clear();

    sentence.addWordToEnd(new Pronoun("he"));
    sentence.addWordToEnd(new Verb("sits"));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(objective, nominative, singular, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpPronoun.setPronWithForms("he", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Pronoun("he", currentSetOfForms));

    currentSetOfForms.clear();
    tmpVerbAuxiliaries.clear();
    tmpWordForm.setWordForm(presentSimple, third, infinitive, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpVerb.setVerbWithForms("sits", currentSetOfForms, tmpVerbAuxiliaries);
    sentenceWithExpForms.addWordToEnd(new Verb("sits", currentSetOfForms, tmpVerbAuxiliaries));

    QTest::newRow("verbInPresentSimpleThirdPerson") <<
        sentence << sentenceWithExpForms;

    // Тест 6. Глагол во времени Present Simple, вопросительное предложение
    sentence.clear();
    sentenceWithExpForms.clear();

    sentence.addWordToEnd(new Auxiliary("does"));
    sentence.addWordToEnd(new Pronoun("your"));
    sentence.addWordToEnd(new Noun("brother"));
    sentence.addWordToEnd(new Verb("like"));
    sentence.addWordToEnd(new Noun("apples"));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(notSet, notSet, notSet, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpAuxiliary.setAuxWithForms("does", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Auxiliary("does", currentSetOfForms));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(possessive, mainForm, singular, notSet);
    currentSetOfForms.insert(tmpWordForm);
    tmpWordForm.setWordForm(possessive, mainForm, plural, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpPronoun.setPronWithForms("your", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Pronoun("your", currentSetOfForms));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(singular, objective, notSet, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpNoun.setNounWithForms("brother", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Noun("brother", currentSetOfForms));

    currentSetOfForms.clear();
    tmpVerbAuxiliaries.clear();
    tmpVerbAuxiliaries.append(0);
    tmpWordForm.setWordForm(presentSimple, third, infinitive, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpVerb.setVerbWithForms("like", currentSetOfForms, tmpVerbAuxiliaries);
    sentenceWithExpForms.addWordToEnd(new Verb("like", currentSetOfForms, tmpVerbAuxiliaries));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(plural, objective, notSet, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpNoun.setNounWithForms("apples", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Noun("apples", currentSetOfForms));

    QTest::newRow("verbInPresentSimplebetweenAuxAndVerbOtherWords") <<
        sentence << sentenceWithExpForms;

    // Тест 7. Глагол во времени Present Continuous
    sentence.clear();
    sentenceWithExpForms.clear();

    sentence.addWordToEnd(new Pronoun("i"));
    sentence.addWordToEnd(new Auxiliary("am"));
    sentence.addWordToEnd(new Verb("writing"));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(objective, nominative, singular, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpPronoun.setPronWithForms("i", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Pronoun("i", currentSetOfForms));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(notSet, notSet, notSet, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpAuxiliary.setAuxWithForms("am", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Auxiliary("am", currentSetOfForms));

    currentSetOfForms.clear();
    tmpVerbAuxiliaries.clear();
    tmpVerbAuxiliaries.append(1);
    tmpWordForm.setWordForm(presentCont, first, presentParticiple, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpVerb.setVerbWithForms("writing", currentSetOfForms, tmpVerbAuxiliaries);
    sentenceWithExpForms.addWordToEnd(new Verb("writing", currentSetOfForms, tmpVerbAuxiliaries));

    QTest::newRow("verbInPresentContinous") <<
        sentence << sentenceWithExpForms;

    // Тест 8. Глагол во времени Past simple
    sentence.clear();
    sentenceWithExpForms.clear();

    sentence.addWordToEnd(new Pronoun("i"));
    sentence.addWordToEnd(new Verb("wrote"));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(objective, nominative, singular, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpPronoun.setPronWithForms("i", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Pronoun("i", currentSetOfForms));

    currentSetOfForms.clear();
    tmpVerbAuxiliaries.clear();
    tmpWordForm.setWordForm(pastSimple, notThird, preterite, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpVerb.setVerbWithForms("wrote", currentSetOfForms, tmpVerbAuxiliaries);
    sentenceWithExpForms.addWordToEnd(new Verb("wrote", currentSetOfForms, tmpVerbAuxiliaries));

    QTest::newRow("verbInPastSimple") <<
        sentence << sentenceWithExpForms;

    // Тест 9. Глагол может быть как во времени Present simple, так и во времени Past simple
    sentence.clear();
    sentenceWithExpForms.clear();

    sentence.addWordToEnd(new Pronoun("i"));
    sentence.addWordToEnd(new Verb("read"));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(objective, nominative, singular, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpPronoun.setPronWithForms("i", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Pronoun("i", currentSetOfForms));

    currentSetOfForms.clear();
    tmpVerbAuxiliaries.clear();
    tmpWordForm.setWordForm(presentSimple, notThird, infinitive, notSet);
    currentSetOfForms.insert(tmpWordForm);
    tmpWordForm.setWordForm(pastSimple, notThird, preterite, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpVerb.setVerbWithForms("read", currentSetOfForms, tmpVerbAuxiliaries);
    sentenceWithExpForms.addWordToEnd(new Verb("read", currentSetOfForms, tmpVerbAuxiliaries));

    QTest::newRow("verbInPastSimpleAndInPresentSimple") <<
        sentence << sentenceWithExpForms;

    // Тест 10. Глагол во времени Past Continuous, вспомогательное was
    sentence.clear();
    sentenceWithExpForms.clear();

    sentence.addWordToEnd(new Pronoun("i"));
    sentence.addWordToEnd(new Auxiliary("was"));
    sentence.addWordToEnd(new Verb("writing"));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(objective, nominative, singular, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpPronoun.setPronWithForms("i", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Pronoun("i", currentSetOfForms));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(notSet, notSet, notSet, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpAuxiliary.setAuxWithForms("was", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Auxiliary("was", currentSetOfForms));

    currentSetOfForms.clear();
    tmpVerbAuxiliaries.clear();
    tmpVerbAuxiliaries.append(1);
    tmpWordForm.setWordForm(pastCont, notThird, presentParticiple, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpVerb.setVerbWithForms("writing", currentSetOfForms, tmpVerbAuxiliaries);
    sentenceWithExpForms.addWordToEnd(new Verb("writing", currentSetOfForms, tmpVerbAuxiliaries));

    QTest::newRow("verbInPastContinousAuxWas") <<
        sentence << sentenceWithExpForms;

    // Тест 11. Глагол во времени Past Continuous, вспомогательное were
    sentence.clear();
    sentenceWithExpForms.clear();

    sentence.addWordToEnd(new Pronoun("i"));
    sentence.addWordToEnd(new Auxiliary("were"));
    sentence.addWordToEnd(new Verb("writing"));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(objective, nominative, singular, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpPronoun.setPronWithForms("i", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Pronoun("i", currentSetOfForms));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(notSet, notSet, notSet, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpAuxiliary.setAuxWithForms("were", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Auxiliary("were", currentSetOfForms));

    currentSetOfForms.clear();
    tmpVerbAuxiliaries.clear();
    tmpVerbAuxiliaries.append(1);
    tmpWordForm.setWordForm(pastCont, notThird, presentParticiple, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpVerb.setVerbWithForms("writing", currentSetOfForms, tmpVerbAuxiliaries);
    sentenceWithExpForms.addWordToEnd(new Verb("writing", currentSetOfForms, tmpVerbAuxiliaries));

    QTest::newRow("verbInPastContinousAuxWere") <<
        sentence << sentenceWithExpForms;

    // Тест 12. Глагол во времени Present Perfect
    sentence.clear();
    sentenceWithExpForms.clear();

    sentence.addWordToEnd(new Pronoun("i"));
    sentence.addWordToEnd(new Auxiliary("have"));
    sentence.addWordToEnd(new Verb("written"));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(objective, nominative, singular, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpPronoun.setPronWithForms("i", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Pronoun("i", currentSetOfForms));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(notSet, notSet, notSet, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpAuxiliary.setAuxWithForms("have", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Auxiliary("have", currentSetOfForms));

    currentSetOfForms.clear();
    tmpVerbAuxiliaries.clear();
    tmpVerbAuxiliaries.append(1);
    tmpWordForm.setWordForm(presentPerf, notThird, pastParticiple, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpVerb.setVerbWithForms("wrote", currentSetOfForms, tmpVerbAuxiliaries);
    sentenceWithExpForms.addWordToEnd(new Verb("written", currentSetOfForms, tmpVerbAuxiliaries));

    QTest::newRow("verbInPresentPerfect") <<
        sentence << sentenceWithExpForms;

    // Тест 13. Глагол во времени Present Perfect Continuous
    sentence.clear();
    sentenceWithExpForms.clear();

    sentence.addWordToEnd(new Pronoun("i"));
    sentence.addWordToEnd(new Auxiliary("have"));
    sentence.addWordToEnd(new Auxiliary("been"));
    sentence.addWordToEnd(new Verb("writing"));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(objective, nominative, singular, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpPronoun.setPronWithForms("i", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Pronoun("i", currentSetOfForms));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(notSet, notSet, notSet, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpAuxiliary.setAuxWithForms("have", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Auxiliary("have", currentSetOfForms));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(notSet, notSet, notSet, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpAuxiliary.setAuxWithForms("been", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Auxiliary("been", currentSetOfForms));

    currentSetOfForms.clear();
    tmpVerbAuxiliaries.clear();
    tmpVerbAuxiliaries.append(1);
    tmpVerbAuxiliaries.append(2);
    tmpWordForm.setWordForm(presentPerfCont, notThird, presentParticiple, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpVerb.setVerbWithForms("writing", currentSetOfForms, tmpVerbAuxiliaries);
    sentenceWithExpForms.addWordToEnd(new Verb("writing", currentSetOfForms, tmpVerbAuxiliaries));

    QTest::newRow("verbInPresentPerfectContinuous") <<
        sentence << sentenceWithExpForms;

    // Тест 14. Глагол во времени Past Perfect.
    sentence.clear();
    sentenceWithExpForms.clear();

    sentence.addWordToEnd(new Pronoun("i"));
    sentence.addWordToEnd(new Auxiliary("had"));
    sentence.addWordToEnd(new Verb("written"));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(objective, nominative, singular, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpPronoun.setPronWithForms("i", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Pronoun("i", currentSetOfForms));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(notSet, notSet, notSet, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpAuxiliary.setAuxWithForms("had", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Auxiliary("had", currentSetOfForms));

    currentSetOfForms.clear();
    tmpVerbAuxiliaries.clear();
    tmpVerbAuxiliaries.append(1);
    tmpWordForm.setWordForm(pastPerf, notThird, pastParticiple, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpVerb.setVerbWithForms("wrote", currentSetOfForms, tmpVerbAuxiliaries);
    sentenceWithExpForms.addWordToEnd(new Verb("written", currentSetOfForms, tmpVerbAuxiliaries));

    QTest::newRow("verbInPastPerfect") <<
        sentence << sentenceWithExpForms;

    // Тест 15. Глагол во времени Past Perfect Continuous
    sentence.clear();
    sentenceWithExpForms.clear();

    sentence.addWordToEnd(new Pronoun("i"));
    sentence.addWordToEnd(new Auxiliary("had"));
    sentence.addWordToEnd(new Auxiliary("been"));
    sentence.addWordToEnd(new Verb("writing"));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(objective, nominative, singular, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpPronoun.setPronWithForms("i", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Pronoun("i", currentSetOfForms));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(notSet, notSet, notSet, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpAuxiliary.setAuxWithForms("had", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Auxiliary("had", currentSetOfForms));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(notSet, notSet, notSet, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpAuxiliary.setAuxWithForms("been", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Auxiliary("been", currentSetOfForms));

    currentSetOfForms.clear();
    tmpVerbAuxiliaries.clear();
    tmpVerbAuxiliaries.append(1);
    tmpVerbAuxiliaries.append(2);
    tmpWordForm.setWordForm(pastPerfCont, notThird, presentParticiple, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpVerb.setVerbWithForms("writing", currentSetOfForms, tmpVerbAuxiliaries);
    sentenceWithExpForms.addWordToEnd(new Verb("writing", currentSetOfForms, tmpVerbAuxiliaries));

    QTest::newRow("verbInPastPerfectContinuous") <<
        sentence << sentenceWithExpForms;

    // Тест 16. Глагол во времени Future Simple, местоимение 1-го лица
    sentence.clear();
    sentenceWithExpForms.clear();

    sentence.addWordToEnd(new Pronoun("i"));
    sentence.addWordToEnd(new Auxiliary("shall"));
    sentence.addWordToEnd(new Verb("write"));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(objective, nominative, singular, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpPronoun.setPronWithForms("i", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Pronoun("i", currentSetOfForms));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(notSet, notSet, notSet, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpAuxiliary.setAuxWithForms("shall", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Auxiliary("shall", currentSetOfForms));

    currentSetOfForms.clear();
    tmpVerbAuxiliaries.clear();
    tmpVerbAuxiliaries.append(1);
    tmpWordForm.setWordForm(futureSimple, first, infinitive, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpVerb.setVerbWithForms("write", currentSetOfForms, tmpVerbAuxiliaries);
    sentenceWithExpForms.addWordToEnd(new Verb("write", currentSetOfForms, tmpVerbAuxiliaries));

    QTest::newRow("verbInFutureSimpleFirstPerson") <<
        sentence << sentenceWithExpForms;

    // Тест 17. Глагол во времени Future Simple, местоимение 3-го лица
    sentence.clear();
    sentenceWithExpForms.clear();

    sentence.addWordToEnd(new Pronoun("i"));
    sentence.addWordToEnd(new Auxiliary("will"));
    sentence.addWordToEnd(new Verb("write"));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(objective, nominative, singular, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpPronoun.setPronWithForms("i", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Pronoun("i", currentSetOfForms));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(notSet, notSet, notSet, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpAuxiliary.setAuxWithForms("will", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Auxiliary("will", currentSetOfForms));

    currentSetOfForms.clear();
    tmpVerbAuxiliaries.clear();
    tmpVerbAuxiliaries.append(1);
    tmpWordForm.setWordForm(futureSimple, notThird, infinitive, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpVerb.setVerbWithForms("write", currentSetOfForms, tmpVerbAuxiliaries);
    sentenceWithExpForms.addWordToEnd(new Verb("write", currentSetOfForms, tmpVerbAuxiliaries));

    QTest::newRow("verbInFutureSimpleThirdPerson") <<
        sentence << sentenceWithExpForms;

    // Тест 18. Глагол во времени Future Continuous, местоимение 3-го лица
    sentence.clear();
    sentenceWithExpForms.clear();

    sentence.addWordToEnd(new Pronoun("he"));
    sentence.addWordToEnd(new Auxiliary("will"));
    sentence.addWordToEnd(new Auxiliary("be"));
    sentence.addWordToEnd(new Verb("writing"));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(objective, nominative, singular, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpPronoun.setPronWithForms("he", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Pronoun("he", currentSetOfForms));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(notSet, notSet, notSet, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpAuxiliary.setAuxWithForms("will", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Auxiliary("will", currentSetOfForms));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(notSet, notSet, notSet, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpAuxiliary.setAuxWithForms("be", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Auxiliary("be", currentSetOfForms));

    currentSetOfForms.clear();
    tmpVerbAuxiliaries.clear();
    tmpVerbAuxiliaries.append(1);
    tmpVerbAuxiliaries.append(2);
    tmpWordForm.setWordForm(futureCont, notThird, presentParticiple, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpVerb.setVerbWithForms("writing", currentSetOfForms, tmpVerbAuxiliaries);
    sentenceWithExpForms.addWordToEnd(new Verb("writing", currentSetOfForms, tmpVerbAuxiliaries));

    QTest::newRow("verbInFutureContinuousThirdPerson") <<
        sentence << sentenceWithExpForms;

    // Тест 19. Глагол во времени Future Continuous, местоимение 1-го лица
    sentence.clear();
    sentenceWithExpForms.clear();

    sentence.addWordToEnd(new Pronoun("i"));
    sentence.addWordToEnd(new Auxiliary("shall"));
    sentence.addWordToEnd(new Auxiliary("be"));
    sentence.addWordToEnd(new Verb("writing"));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(objective, nominative, singular, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpPronoun.setPronWithForms("i", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Pronoun("i", currentSetOfForms));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(notSet, notSet, notSet, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpAuxiliary.setAuxWithForms("shall", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Auxiliary("shall", currentSetOfForms));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(notSet, notSet, notSet, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpAuxiliary.setAuxWithForms("be", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Auxiliary("be", currentSetOfForms));

    currentSetOfForms.clear();
    tmpVerbAuxiliaries.clear();
    tmpVerbAuxiliaries.append(1);
    tmpVerbAuxiliaries.append(2);
    tmpWordForm.setWordForm(futureCont, first, presentParticiple, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpVerb.setVerbWithForms("writing", currentSetOfForms, tmpVerbAuxiliaries);
    sentenceWithExpForms.addWordToEnd(new Verb("writing", currentSetOfForms, tmpVerbAuxiliaries));

    QTest::newRow("verbInFutureContinuousFirstPerson") <<
        sentence << sentenceWithExpForms;

    // Тест 20. Глагол во времени Future Perfect Simple, местоимение 1-го лица
    sentence.clear();
    sentenceWithExpForms.clear();

    sentence.addWordToEnd(new Pronoun("i"));
    sentence.addWordToEnd(new Auxiliary("shall"));
    sentence.addWordToEnd(new Auxiliary("have"));
    sentence.addWordToEnd(new Verb("written"));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(objective, nominative, singular, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpPronoun.setPronWithForms("i", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Pronoun("i", currentSetOfForms));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(notSet, notSet, notSet, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpAuxiliary.setAuxWithForms("shall", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Auxiliary("shall", currentSetOfForms));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(notSet, notSet, notSet, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpAuxiliary.setAuxWithForms("have", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Auxiliary("have", currentSetOfForms));

    currentSetOfForms.clear();
    tmpVerbAuxiliaries.clear();
    tmpVerbAuxiliaries.append(1);
    tmpVerbAuxiliaries.append(2);
    tmpWordForm.setWordForm(futurePerfSimple, first, pastParticiple, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpVerb.setVerbWithForms("wrote", currentSetOfForms, tmpVerbAuxiliaries);
    sentenceWithExpForms.addWordToEnd(new Verb("written", currentSetOfForms, tmpVerbAuxiliaries));

    QTest::newRow("verbInFuturePerfectSimpleFirstPerson") <<
        sentence << sentenceWithExpForms;

    // Тест 21. Глагол во времени Future Perfect Simple, местоимение 3-го лица
    sentence.clear();
    sentenceWithExpForms.clear();

    sentence.addWordToEnd(new Pronoun("he"));
    sentence.addWordToEnd(new Auxiliary("will"));
    sentence.addWordToEnd(new Auxiliary("have"));
    sentence.addWordToEnd(new Verb("written"));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(objective, nominative, singular, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpPronoun.setPronWithForms("he", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Pronoun("he", currentSetOfForms));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(notSet, notSet, notSet, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpAuxiliary.setAuxWithForms("will", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Auxiliary("will", currentSetOfForms));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(notSet, notSet, notSet, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpAuxiliary.setAuxWithForms("have", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Auxiliary("have", currentSetOfForms));

    currentSetOfForms.clear();
    tmpVerbAuxiliaries.clear();
    tmpVerbAuxiliaries.append(1);
    tmpVerbAuxiliaries.append(2);
    tmpWordForm.setWordForm(futurePerfSimple, notThird, pastParticiple, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpVerb.setVerbWithForms("wrote", currentSetOfForms, tmpVerbAuxiliaries);
    sentenceWithExpForms.addWordToEnd(new Verb("written", currentSetOfForms, tmpVerbAuxiliaries));

    QTest::newRow("verbInFuturePerfectSimpleThirdPerson") <<
        sentence << sentenceWithExpForms;

    // Тест 22. Глагол во времени Future Perfect Continuous, местоимение 1-го лица
    sentence.clear();
    sentenceWithExpForms.clear();

    sentence.addWordToEnd(new Pronoun("i"));
    sentence.addWordToEnd(new Auxiliary("shall"));
    sentence.addWordToEnd(new Auxiliary("have"));
    sentence.addWordToEnd(new Auxiliary("been"));
    sentence.addWordToEnd(new Verb("writing"));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(objective, nominative, singular, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpPronoun.setPronWithForms("i", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Pronoun("i", currentSetOfForms));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(notSet, notSet, notSet, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpAuxiliary.setAuxWithForms("shall", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Auxiliary("shall", currentSetOfForms));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(notSet, notSet, notSet, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpAuxiliary.setAuxWithForms("have", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Auxiliary("have", currentSetOfForms));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(notSet, notSet, notSet, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpAuxiliary.setAuxWithForms("been", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Auxiliary("been", currentSetOfForms));

    currentSetOfForms.clear();
    tmpVerbAuxiliaries.clear();
    tmpVerbAuxiliaries.append(1);
    tmpVerbAuxiliaries.append(2);
    tmpVerbAuxiliaries.append(3);
    tmpWordForm.setWordForm(futurePerfCont, first, presentParticiple, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpVerb.setVerbWithForms("writing", currentSetOfForms, tmpVerbAuxiliaries);
    sentenceWithExpForms.addWordToEnd(new Verb("writing", currentSetOfForms, tmpVerbAuxiliaries));

    QTest::newRow("verbInFuturePerfectContinuousFirstPerson") <<
        sentence << sentenceWithExpForms;

    // Тест 23. Глагол во времени Future Perfect Continuous, местоимение 3-го лица
    sentence.clear();
    sentenceWithExpForms.clear();

    sentence.addWordToEnd(new Pronoun("i"));
    sentence.addWordToEnd(new Auxiliary("will"));
    sentence.addWordToEnd(new Auxiliary("have"));
    sentence.addWordToEnd(new Auxiliary("been"));
    sentence.addWordToEnd(new Verb("writing"));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(objective, nominative, singular, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpPronoun.setPronWithForms("i", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Pronoun("i", currentSetOfForms));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(notSet, notSet, notSet, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpAuxiliary.setAuxWithForms("will", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Auxiliary("will", currentSetOfForms));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(notSet, notSet, notSet, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpAuxiliary.setAuxWithForms("have", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Auxiliary("have", currentSetOfForms));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(notSet, notSet, notSet, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpAuxiliary.setAuxWithForms("been", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Auxiliary("been", currentSetOfForms));

    currentSetOfForms.clear();
    tmpVerbAuxiliaries.clear();
    tmpVerbAuxiliaries.append(1);
    tmpVerbAuxiliaries.append(2);
    tmpVerbAuxiliaries.append(3);
    tmpWordForm.setWordForm(futurePerfCont, notThird, presentParticiple, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpVerb.setVerbWithForms("writing", currentSetOfForms, tmpVerbAuxiliaries);
    sentenceWithExpForms.addWordToEnd(new Verb("writing", currentSetOfForms, tmpVerbAuxiliaries));

    QTest::newRow("verbInFuturePerfectContinuousThirdPerson") <<
        sentence << sentenceWithExpForms;

    // Тест 24. Глагол во времени Future Simple In The Past, местоимение 1-го лица
    sentence.clear();
    sentenceWithExpForms.clear();

    sentence.addWordToEnd(new Pronoun("i"));
    sentence.addWordToEnd(new Auxiliary("should"));
    sentence.addWordToEnd(new Verb("write"));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(objective, nominative, singular, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpPronoun.setPronWithForms("i", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Pronoun("i", currentSetOfForms));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(notSet, notSet, notSet, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpAuxiliary.setAuxWithForms("should", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Auxiliary("should", currentSetOfForms));

    currentSetOfForms.clear();
    tmpVerbAuxiliaries.clear();
    tmpVerbAuxiliaries.append(1);
    tmpWordForm.setWordForm(futureSimpleInThePast, first, infinitive, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpVerb.setVerbWithForms("write", currentSetOfForms, tmpVerbAuxiliaries);
    sentenceWithExpForms.addWordToEnd(new Verb("write", currentSetOfForms, tmpVerbAuxiliaries));

    QTest::newRow("verbInFutureSimpleInThePastFirstPerson") <<
        sentence << sentenceWithExpForms;

    // Тест 25. Глагол во времени Future Simple In The Past, местоимение 3-го лица
    sentence.clear();
    sentenceWithExpForms.clear();

    sentence.addWordToEnd(new Pronoun("he"));
    sentence.addWordToEnd(new Auxiliary("would"));
    sentence.addWordToEnd(new Verb("write"));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(objective, nominative, singular, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpPronoun.setPronWithForms("he", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Pronoun("he", currentSetOfForms));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(notSet, notSet, notSet, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpAuxiliary.setAuxWithForms("would", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Auxiliary("would", currentSetOfForms));

    currentSetOfForms.clear();
    tmpVerbAuxiliaries.clear();
    tmpVerbAuxiliaries.append(1);
    tmpWordForm.setWordForm(futureSimpleInThePast, notThird, infinitive, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpVerb.setVerbWithForms("write", currentSetOfForms, tmpVerbAuxiliaries);
    sentenceWithExpForms.addWordToEnd(new Verb("write", currentSetOfForms, tmpVerbAuxiliaries));

    QTest::newRow("verbInFutureSimpleInThePastThirdPerson") <<
        sentence << sentenceWithExpForms;

    // Тест 26. Глагол во времени Future Continuous In The Past, местоимение 1-го лица
    sentence.clear();
    sentenceWithExpForms.clear();

    sentence.addWordToEnd(new Pronoun("i"));
    sentence.addWordToEnd(new Auxiliary("should"));
    sentence.addWordToEnd(new Auxiliary("be"));
    sentence.addWordToEnd(new Verb("writing"));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(objective, nominative, singular, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpPronoun.setPronWithForms("i", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Pronoun("i", currentSetOfForms));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(notSet, notSet, notSet, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpAuxiliary.setAuxWithForms("should", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Auxiliary("should", currentSetOfForms));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(notSet, notSet, notSet, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpAuxiliary.setAuxWithForms("be", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Auxiliary("be", currentSetOfForms));

    currentSetOfForms.clear();
    tmpVerbAuxiliaries.clear();
    tmpVerbAuxiliaries.append(1);
    tmpVerbAuxiliaries.append(2);
    tmpWordForm.setWordForm(futureContInThePast, first, presentParticiple, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpVerb.setVerbWithForms("writing", currentSetOfForms, tmpVerbAuxiliaries);
    sentenceWithExpForms.addWordToEnd(new Verb("writing", currentSetOfForms, tmpVerbAuxiliaries));

    QTest::newRow("verbInFutureContinuousInThePastFirstPerson") <<
        sentence << sentenceWithExpForms;

    // Тест 27. Глагол во времени Future Continuous In The Past, местоимение 3-го лица
    sentence.clear();
    sentenceWithExpForms.clear();

    sentence.addWordToEnd(new Pronoun("he"));
    sentence.addWordToEnd(new Auxiliary("would"));
    sentence.addWordToEnd(new Auxiliary("be"));
    sentence.addWordToEnd(new Verb("writing"));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(objective, nominative, singular, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpPronoun.setPronWithForms("he", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Pronoun("he", currentSetOfForms));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(notSet, notSet, notSet, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpAuxiliary.setAuxWithForms("would", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Auxiliary("would", currentSetOfForms));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(notSet, notSet, notSet, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpAuxiliary.setAuxWithForms("be", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Auxiliary("be", currentSetOfForms));

    currentSetOfForms.clear();
    tmpVerbAuxiliaries.clear();
    tmpVerbAuxiliaries.append(1);
    tmpVerbAuxiliaries.append(2);
    tmpWordForm.setWordForm(futureContInThePast, notThird, presentParticiple, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpVerb.setVerbWithForms("write", currentSetOfForms, tmpVerbAuxiliaries);
    sentenceWithExpForms.addWordToEnd(new Verb("writing", currentSetOfForms, tmpVerbAuxiliaries));

    QTest::newRow("verbInFutureContinuousInThePastThirdPerson") <<
        sentence << sentenceWithExpForms;

    // Тест 28. Глагол во времени Future Perfect In The Past, местоимение 1-го лица
    sentence.clear();
    sentenceWithExpForms.clear();

    sentence.addWordToEnd(new Pronoun("i"));
    sentence.addWordToEnd(new Auxiliary("should"));
    sentence.addWordToEnd(new Auxiliary("have"));
    sentence.addWordToEnd(new Verb("written"));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(objective, nominative, singular, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpPronoun.setPronWithForms("i", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Pronoun("i", currentSetOfForms));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(notSet, notSet, notSet, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpAuxiliary.setAuxWithForms("should", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Auxiliary("should", currentSetOfForms));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(notSet, notSet, notSet, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpAuxiliary.setAuxWithForms("have", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Auxiliary("have", currentSetOfForms));

    currentSetOfForms.clear();
    tmpVerbAuxiliaries.clear();
    tmpVerbAuxiliaries.append(1);
    tmpVerbAuxiliaries.append(2);
    tmpWordForm.setWordForm(futurePerfInThePast, first, pastParticiple, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpVerb.setVerbWithForms("wrote", currentSetOfForms, tmpVerbAuxiliaries);
    sentenceWithExpForms.addWordToEnd(new Verb("written", currentSetOfForms, tmpVerbAuxiliaries));

    QTest::newRow("verbInFuturePerfectInThePastFirstPerson") <<
        sentence << sentenceWithExpForms;

    // Тест 29. Глагол во времени Future Perfect In The Past, местоимение 3-го лица
    sentence.clear();
    sentenceWithExpForms.clear();

    sentence.addWordToEnd(new Pronoun("he"));
    sentence.addWordToEnd(new Auxiliary("would"));
    sentence.addWordToEnd(new Auxiliary("have"));
    sentence.addWordToEnd(new Verb("written"));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(objective, nominative, singular, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpPronoun.setPronWithForms("he", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Pronoun("he", currentSetOfForms));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(notSet, notSet, notSet, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpAuxiliary.setAuxWithForms("would", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Auxiliary("would", currentSetOfForms));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(notSet, notSet, notSet, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpAuxiliary.setAuxWithForms("have", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Auxiliary("have", currentSetOfForms));

    currentSetOfForms.clear();
    tmpVerbAuxiliaries.clear();
    tmpVerbAuxiliaries.append(1);
    tmpVerbAuxiliaries.append(2);
    tmpWordForm.setWordForm(futurePerfInThePast, notThird, pastParticiple, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpVerb.setVerbWithForms("wrote", currentSetOfForms, tmpVerbAuxiliaries);
    sentenceWithExpForms.addWordToEnd(new Verb("written", currentSetOfForms, tmpVerbAuxiliaries));

    QTest::newRow("verbInFuturePerfectInThePastThirdPerson") <<
        sentence << sentenceWithExpForms;

    // Тест 30. Глагол во времени Future Perfect Continuous In The Past, местоимение 1-го лица
    sentence.clear();
    sentenceWithExpForms.clear();

    sentence.addWordToEnd(new Pronoun("i"));
    sentence.addWordToEnd(new Auxiliary("should"));
    sentence.addWordToEnd(new Auxiliary("have"));
    sentence.addWordToEnd(new Auxiliary("been"));
    sentence.addWordToEnd(new Verb("writing"));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(objective, nominative, singular, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpPronoun.setPronWithForms("i", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Pronoun("i", currentSetOfForms));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(notSet, notSet, notSet, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpAuxiliary.setAuxWithForms("should", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Auxiliary("should", currentSetOfForms));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(notSet, notSet, notSet, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpAuxiliary.setAuxWithForms("have", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Auxiliary("have", currentSetOfForms));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(notSet, notSet, notSet, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpAuxiliary.setAuxWithForms("been", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Auxiliary("been", currentSetOfForms));

    currentSetOfForms.clear();
    tmpVerbAuxiliaries.clear();
    tmpVerbAuxiliaries.append(1);
    tmpVerbAuxiliaries.append(2);
    tmpVerbAuxiliaries.append(3);
    tmpWordForm.setWordForm(futurePerfContInThePast, first, presentParticiple, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpVerb.setVerbWithForms("writing", currentSetOfForms, tmpVerbAuxiliaries);
    sentenceWithExpForms.addWordToEnd(new Verb("writing", currentSetOfForms, tmpVerbAuxiliaries));

    QTest::newRow("verbInFuturePerfectContinuousInThePastFirstPerson") <<
        sentence << sentenceWithExpForms;

    // Тест 31. Глагол во времени Future Perfect Continuous In The Past, местоимение 3-го лица
    sentence.clear();
    sentenceWithExpForms.clear();

    sentence.addWordToEnd(new Pronoun("he"));
    sentence.addWordToEnd(new Auxiliary("would"));
    sentence.addWordToEnd(new Auxiliary("have"));
    sentence.addWordToEnd(new Auxiliary("been"));
    sentence.addWordToEnd(new Verb("writing"));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(objective, nominative, singular, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpPronoun.setPronWithForms("he", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Pronoun("he", currentSetOfForms));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(notSet, notSet, notSet, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpAuxiliary.setAuxWithForms("would", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Auxiliary("would", currentSetOfForms));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(notSet, notSet, notSet, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpAuxiliary.setAuxWithForms("have", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Auxiliary("have", currentSetOfForms));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(notSet, notSet, notSet, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpAuxiliary.setAuxWithForms("been", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Auxiliary("been", currentSetOfForms));

    currentSetOfForms.clear();
    tmpVerbAuxiliaries.clear();
    tmpVerbAuxiliaries.append(1);
    tmpVerbAuxiliaries.append(2);
    tmpVerbAuxiliaries.append(3);
    tmpWordForm.setWordForm(futurePerfContInThePast, notThird, presentParticiple, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpVerb.setVerbWithForms("writing", currentSetOfForms, tmpVerbAuxiliaries);
    sentenceWithExpForms.addWordToEnd(new Verb("writing", currentSetOfForms, tmpVerbAuxiliaries));

    QTest::newRow("verbInFuturePerfectContinuousInThePastThirdPerson") <<
        sentence << sentenceWithExpForms;

    // Тест 32. Два глагола с вспомогательными
    sentence.clear();
    sentenceWithExpForms.clear();

    sentence.addWordToEnd(new Pronoun("he"));
    sentence.addWordToEnd(new Auxiliary("has"));
    sentence.addWordToEnd(new Auxiliary("been"));
    sentence.addWordToEnd(new Verb("writing"));
    sentence.addWordToEnd(new Word("and"));
    sentence.addWordToEnd(new Pronoun("she"));
    sentence.addWordToEnd(new Auxiliary("was"));
    sentence.addWordToEnd(new Verb("looking"));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(objective, nominative, singular, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpPronoun.setPronWithForms("he", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Pronoun("he", currentSetOfForms));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(notSet, notSet, notSet, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpAuxiliary.setAuxWithForms("has", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Auxiliary("has", currentSetOfForms));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(notSet, notSet, notSet, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpAuxiliary.setAuxWithForms("been", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Auxiliary("been", currentSetOfForms));

    currentSetOfForms.clear();
    tmpVerbAuxiliaries.clear();
    tmpVerbAuxiliaries.append(1);
    tmpVerbAuxiliaries.append(2);
    tmpWordForm.setWordForm(presentPerfCont, third, presentParticiple, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpVerb.setVerbWithForms("writing", currentSetOfForms, tmpVerbAuxiliaries);
    sentenceWithExpForms.addWordToEnd(new Verb("writing", currentSetOfForms, tmpVerbAuxiliaries));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(notSet, notSet, notSet, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpWord.setWordWithForms("and", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Word("and", currentSetOfForms));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(objective, nominative, singular, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpPronoun.setPronWithForms("she", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Pronoun("she", currentSetOfForms));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(notSet, notSet, notSet, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpAuxiliary.setAuxWithForms("was", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Auxiliary("was", currentSetOfForms));

    currentSetOfForms.clear();
    tmpVerbAuxiliaries.clear();
    tmpVerbAuxiliaries.append(6);
    tmpWordForm.setWordForm(pastCont, notThird, presentParticiple, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpVerb.setVerbWithForms("looking", currentSetOfForms, tmpVerbAuxiliaries);
    sentenceWithExpForms.addWordToEnd(new Verb("looking", currentSetOfForms, tmpVerbAuxiliaries));

    QTest::newRow("twoVerbsWithAuxiliaries") <<
        sentence << sentenceWithExpForms;

    // Тест 33. 2 глагола с вспомогательными, между ними прилагательное с вспомогательным
    sentence.clear();
    sentenceWithExpForms.clear();

    sentence.addWordToEnd(new Pronoun("he"));
    sentence.addWordToEnd(new Auxiliary("has"));
    sentence.addWordToEnd(new Auxiliary("been"));
    sentence.addWordToEnd(new Verb("writing"));
    sentence.addWordToEnd(new Word("and"));
    sentence.addWordToEnd(new Auxiliary("more"));
    sentence.addWordToEnd(new Adjective("interesting"));
    sentence.addWordToEnd(new Pronoun("she"));
    sentence.addWordToEnd(new Auxiliary("was"));
    sentence.addWordToEnd(new Verb("looking"));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(objective, nominative, singular, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpPronoun.setPronWithForms("he", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Pronoun("he", currentSetOfForms));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(notSet, notSet, notSet, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpAuxiliary.setAuxWithForms("has", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Auxiliary("has", currentSetOfForms));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(notSet, notSet, notSet, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpAuxiliary.setAuxWithForms("been", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Auxiliary("been", currentSetOfForms));

    currentSetOfForms.clear();
    tmpVerbAuxiliaries.clear();
    tmpVerbAuxiliaries.append(1);
    tmpVerbAuxiliaries.append(2);
    tmpWordForm.setWordForm(presentPerfCont, third, presentParticiple, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpVerb.setVerbWithForms("writing", currentSetOfForms, tmpVerbAuxiliaries);
    sentenceWithExpForms.addWordToEnd(new Verb("writing", currentSetOfForms, tmpVerbAuxiliaries));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(notSet, notSet, notSet, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpWord.setWordWithForms("and", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Word("and", currentSetOfForms));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(notSet, notSet, notSet, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpAuxiliary.setAuxWithForms("more", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Auxiliary("more", currentSetOfForms));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(comparative, notSet, notSet, more);
    currentSetOfForms.insert(tmpWordForm);
    //tmpAdjective.setAdjWithForms("interesting", currentSetOfForms, 5);
    sentenceWithExpForms.addWordToEnd(new Adjective("interesting", currentSetOfForms, 5));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(objective, nominative, singular, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpPronoun.setPronWithForms("she", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Pronoun("she", currentSetOfForms));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(notSet, notSet, notSet, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpAuxiliary.setAuxWithForms("was", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Auxiliary("was", currentSetOfForms));

    currentSetOfForms.clear();
    tmpVerbAuxiliaries.clear();
    tmpVerbAuxiliaries.append(8);
    tmpWordForm.setWordForm(pastCont, notThird, presentParticiple, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpVerb.setVerbWithForms("looking", currentSetOfForms, tmpVerbAuxiliaries);
    sentenceWithExpForms.addWordToEnd(new Verb("looking", currentSetOfForms, tmpVerbAuxiliaries));

    QTest::newRow("twoVerbsWithAuxiliariesBetweenThemAdjectiveWithAux") <<
        sentence << sentenceWithExpForms;

    // Тест 34. Между вспомогательными и глаголом частица not
    sentence.clear();
    sentenceWithExpForms.clear();

    sentence.addWordToEnd(new Auxiliary("have"));
    sentence.addWordToEnd(new Word("not"));
    sentence.addWordToEnd(new Pronoun("you"));
    sentence.addWordToEnd(new Auxiliary("been"));
    sentence.addWordToEnd(new Verb("writing"));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(notSet, notSet, notSet, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpAuxiliary.setAuxWithForms("have", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Auxiliary("have", currentSetOfForms));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(notSet, notSet, notSet, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpWord.setWordWithForms("not", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Word("not", currentSetOfForms));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(objective, nominative, singular, notSet);
    currentSetOfForms.insert(tmpWordForm);
    tmpWordForm.setWordForm(objective, nominative, plural, notSet);
    currentSetOfForms.insert(tmpWordForm);
    tmpWordForm.setWordForm(objective, objectivePron, singular, notSet);
    currentSetOfForms.insert(tmpWordForm);
    tmpWordForm.setWordForm(objective, objectivePron, plural, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpPronoun.setPronWithForms("you", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Pronoun("you", currentSetOfForms));

    currentSetOfForms.clear();
    tmpWordForm.setWordForm(notSet, notSet, notSet, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpAuxiliary.setAuxWithForms("been", currentSetOfForms);
    sentenceWithExpForms.addWordToEnd(new Auxiliary("been", currentSetOfForms));

    currentSetOfForms.clear();
    tmpVerbAuxiliaries.clear();
    tmpVerbAuxiliaries.append(0);
    tmpVerbAuxiliaries.append(1);
    tmpVerbAuxiliaries.append(3);
    tmpWordForm.setWordForm(presentPerfCont, notThird, presentParticiple, notSet);
    currentSetOfForms.insert(tmpWordForm);
    //tmpVerb.setVerbWithForms("writing", currentSetOfForms, tmpVerbAuxiliaries);
    sentenceWithExpForms.addWordToEnd(new Verb("writing", currentSetOfForms, tmpVerbAuxiliaries));

    QTest::newRow("betweenVerbAndAuxiliariesNot") <<
        sentence << sentenceWithExpForms;
}

void TestSetFormsInCorrectSentence::setFormsInCorrectSentence()
{
    QFETCH(Sentence, sentence);
    QFETCH(Sentence, sentenceWithExpForms);

    QList<Word*> tmpExpSentence = sentenceWithExpForms.getSentence();
    sentence.setFormsInCorrectSentence();
    QList<Word*> tmpRealSentenceWithForms = sentence.getSentence();

    QMutableListIterator<Word*> iExpWords(tmpExpSentence);
    QMutableListIterator<Word*> iRealWords(tmpRealSentenceWithForms);

    while (iExpWords.hasNext() && iRealWords.hasNext())
    {
        QString misstakeMessage;
        if(!iExpWords.next()->wordsAreEqual(iRealWords.next(), misstakeMessage))
        {
            QVERIFY2(false, misstakeMessage.toUtf8());
        }
    }

    while (iExpWords.hasNext())
    {
        QVERIFY2(false, ("Word " + iExpWords.next()->getWord() +
                         " with all forms has no match; ").toUtf8());
    }

    while (iRealWords.hasNext())
    {
        QVERIFY2(false, ("Word " + iRealWords.next()->getWord() +
                         " with all forms is unexpected; ").toUtf8());
    }
}

void TestSetFormsInCorrectSentence::initTestCase()
{
    Verb::readFileWithIrregularVerbs();
    Verb::readFileWithVerbLexems();
    Noun::readFileWithExceptionsNouns();
    Noun::readaFileWithOnlyPluralNouns();
    Noun::readFileWithUncountableNouns();
    Adjective::readFileWithAdjectiveExceptions();
}

QTEST_APPLESS_MAIN(TestSetFormsInCorrectSentence)

#include "test_SetFormsInCorrectSentence.moc"
