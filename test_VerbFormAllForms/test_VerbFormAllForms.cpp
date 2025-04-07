#include <QCoreApplication>
#include <QtTest/QtTest>

#include "../wrongFormsFinder/verb.h"

class TestVerbFormAllForms: public QObject
{
    Q_OBJECT

private slots:
    void verbFormAllForms_data();
    void verbFormAllForms();

    void initTestCase();
};

void TestVerbFormAllForms::verbFormAllForms_data()
{
    QTest::addColumn<QString>("word");
    QTest::addColumn<QSet<Verb>>("expFormsOfWord");

    Verb currentVerb;
    QSet<Verb> allFormsOfVerb;
    WordForm tmpWordForm;
    QSet<WordForm> currentWordForms;

    // 1 Тест. Глагол be
    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, notThird, infinitive, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("be", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, first, infinitive, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("am", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, third, infinitive, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("is", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, notThird, infinitive, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("are", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, notThird, preterite, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("was", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, notThird, preterite, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("were", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, notThird, pastParticiple, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("been", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, notThird, presentParticiple, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("being", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    QTest::newRow("VerbBe") << "be" << allFormsOfVerb;

    // 2 Тест. Глагол с шипящим окончанием
    allFormsOfVerb.clear();

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, notThird, infinitive, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("approach", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, third, infinitive, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("approaches", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, notThird, past, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("approached", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, notThird, presentParticiple, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("approaching", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    QTest::newRow("verbWithSibilantEnding") << "approach" << allFormsOfVerb;

    // 3 Тест. Глагол с окончанием согласная + -y
    allFormsOfVerb.clear();

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, notThird, infinitive, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("apply", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, third, infinitive, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("applies", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, notThird, past, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("applied", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, notThird, presentParticiple, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("applying", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    QTest::newRow("verbWithEndsWithConsonantPlusY") << "apply" << allFormsOfVerb;

    // 4 Тест. Глагол с окончанием -e
    allFormsOfVerb.clear();

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, notThird, infinitive, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("approve", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, third, infinitive, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("approves", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, notThird, past, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("approved", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, notThird, presentParticiple, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("approving", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    QTest::newRow("verbWithEndsWithE") << "approve" << allFormsOfVerb;

    // 5 Тест. Глагол с окончанием согласная + гласная + согласная
    allFormsOfVerb.clear();

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, notThird, infinitive, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("stop", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, third, infinitive, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("stops", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, notThird, past, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("stopped", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, notThird, presentParticiple, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("stopping", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    QTest::newRow("verbWithEndsWithConsonantVowelConsonant") << "stop" << allFormsOfVerb;

    // 6 Тест. Глагол-исключение cover
    allFormsOfVerb.clear();

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, notThird, infinitive, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("cover", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, third, infinitive, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("covers", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, notThird, past, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("covered", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, notThird, presentParticiple, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("covering", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    QTest::newRow("verbExceptionCover") << "cover" << allFormsOfVerb;

    // 7 Тест. Глагол-исключение remember
    allFormsOfVerb.clear();

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, notThird, infinitive, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("remember", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, third, infinitive, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("remembers", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, notThird, past, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("remembered", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, notThird, presentParticiple, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("remembering", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    QTest::newRow("verbExceptionRemember") << "remember" << allFormsOfVerb;

    // 8 Тест. Неправильный глагол с 3 разными словесными формами
    allFormsOfVerb.clear();

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, notThird, infinitive, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("begin", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, third, infinitive, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("begins", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, notThird, preterite, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("began", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, notThird, pastParticiple, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("begun", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, notThird, presentParticiple, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("beginning", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    QTest::newRow("irregularVerbWithThreeDiffrentForms") << "begin" << allFormsOfVerb;

    // 9 Тест. Глагол в форме 3-го лица
    allFormsOfVerb.clear();

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, notThird, infinitive, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("ask", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, third, infinitive, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("asks", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, notThird, past, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("asked", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, notThird, presentParticiple, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("asking", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    QTest::newRow("thirdPersonVerb") << "asks" << allFormsOfVerb;

    // 10 Тест. Правильный глагол в прошедшем времени
    allFormsOfVerb.clear();

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, notThird, infinitive, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("care", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, third, infinitive, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("cares", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, notThird, past, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("cared", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, notThird, presentParticiple, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("caring", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    QTest::newRow("rightVerbInPast") << "cared" << allFormsOfVerb;

    // 11 Тест. Глагол в форме preterite (V2)
    allFormsOfVerb.clear();

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, notThird, infinitive, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("break", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, third, infinitive, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("breaks", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, notThird, preterite, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("broke", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, notThird, pastParticiple, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("broken", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, notThird, presentParticiple, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("breaking", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    QTest::newRow("verbInPreterite") << "broke" << allFormsOfVerb;

    // 12 Тест. Глагол в форме past participle (V3)
    allFormsOfVerb.clear();

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, notThird, infinitive, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("rise", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, third, infinitive, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("rises", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, notThird, preterite, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("rose", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, notThird, pastParticiple, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("risen", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, notThird, presentParticiple, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("rising", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    QTest::newRow("verbInPastParticiple") << "risen" << allFormsOfVerb;

    // 13 Тест. Глагол в форме present participle
    allFormsOfVerb.clear();

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, notThird, infinitive, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("catch", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, third, infinitive, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("catches", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, notThird, preterite, notSet);
    currentWordForms.insert(tmpWordForm);
    tmpWordForm.setWordForm(notSet, notThird, pastParticiple, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("caught", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, notThird, presentParticiple, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("catching", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    QTest::newRow("verbInPresentParticiple") << "catching" << allFormsOfVerb;

    // 14 Тест. Глагол be в форме третьего лица is
    allFormsOfVerb.clear();

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, notThird, infinitive, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("be", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, first, infinitive, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("am", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, third, infinitive, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("is", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, notThird, infinitive, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("are", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, notThird, preterite, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("was", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, notThird, preterite, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("were", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, notThird, pastParticiple, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("been", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, notThird, presentParticiple, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("being", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    QTest::newRow("VerbBeInThirdPerson") << "is" << allFormsOfVerb;

    // 15 Тест. Глагол be в форме preterite was
    allFormsOfVerb.clear();

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, notThird, infinitive, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("be", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, first, infinitive, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("am", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, third, infinitive, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("is", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, notThird, infinitive, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("are", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, notThird, preterite, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("was", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, notThird, preterite, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("were", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, notThird, pastParticiple, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("been", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, notThird, presentParticiple, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("being", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    QTest::newRow("VerbBeInPreterite") << "was" << allFormsOfVerb;

    // 16 Тест. Глагол be в форме past participle been
    allFormsOfVerb.clear();

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, notThird, infinitive, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("be", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, first, infinitive, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("am", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, third, infinitive, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("is", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, notThird, infinitive, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("are", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, notThird, preterite, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("was", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, notThird, preterite, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("were", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, notThird, pastParticiple, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("been", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, notThird, presentParticiple, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("being", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    QTest::newRow("VerbBeInPastParticiple") << "been" << allFormsOfVerb;

    // 17 Тест. Глагол be в present participle
    allFormsOfVerb.clear();

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, notThird, infinitive, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("be", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, first, infinitive, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("am", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, third, infinitive, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("is", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, notThird, infinitive, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("are", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, notThird, preterite, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("was", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, notThird, preterite, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("were", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, notThird, pastParticiple, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("been", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, notThird, presentParticiple, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("being", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    QTest::newRow("VerbBeInPresentParticiple") << "being" << allFormsOfVerb;

    // 18 Тест. Глагол может быть в двух значениях (lay)
    allFormsOfVerb.clear();

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, notThird, infinitive, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("lie", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, notThird, infinitive, notSet);
    currentWordForms.insert(tmpWordForm);
    tmpWordForm.setWordForm(notSet, notThird, preterite, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("lay", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, third, infinitive, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("lies", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, third, infinitive, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("lays", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, notThird, pastParticiple, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("lain", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, notThird, preterite, notSet);
    currentWordForms.insert(tmpWordForm);
    tmpWordForm.setWordForm(notSet, notThird, pastParticiple, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("laid", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, notThird, presentParticiple, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("lying", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    currentWordForms.clear();
    tmpWordForm.setWordForm(notSet, notThird, presentParticiple, notSet);
    currentWordForms.insert(tmpWordForm);
    currentVerb.setWordWithForms("laying", currentWordForms);
    allFormsOfVerb.insert(currentVerb);

    QTest::newRow("verbCanHaveTwoMeanings") << "lay" << allFormsOfVerb;
}

void TestVerbFormAllForms::initTestCase()
{
    Verb::readFileWithIrregularVerbs();
    Verb::readFileWithVerbLexems();
}

void TestVerbFormAllForms::verbFormAllForms()
{
    QFETCH(QString, word);
    QFETCH(QSet<Verb>, expFormsOfWord);

    Verb currentExpWord, currentRealWord;
    QSet<WordForm> expWordForms;

    Verb realWord(word);
    QSet<Word*> tmpRealWords = realWord.formAllForms();

    QMutableSetIterator<Verb> iExpVerbs(expFormsOfWord);

    while (iExpVerbs.hasNext())
    {
        Word* tmpMatchedWord;
        if (iExpVerbs.next().hasMatchingWord(tmpRealWords, tmpMatchedWord))
        {
            QString misstakeMessage;
            if(!iExpVerbs.value().wordsAreEqual(tmpMatchedWord, misstakeMessage))
            {
                QVERIFY2(false, misstakeMessage.toUtf8());
            }

            tmpRealWords.remove(tmpMatchedWord);
        }
        else
        {
            QSet<WordForm> currentWordForms = iExpVerbs.value().getPossibleFormsOfWord();
            QMutableSetIterator<WordForm> iCurrentForm(currentWordForms);

            while (iCurrentForm.hasNext())
            {
                iCurrentForm.next();

                QVERIFY2(false,
                         ("Word " + iExpVerbs.value().getWord() +
                          " has no match: " + iCurrentForm.value().getWordFormByStr()
                          + "; ").toUtf8());
            }
        }
    }

    QSetIterator<Word*> iUnmatchedVerb(tmpRealWords);
    while (iUnmatchedVerb.hasNext())
    {
        QSet<WordForm> tmpUnmatchedForms = iUnmatchedVerb.next()->getPossibleFormsOfWord();
        QMutableSetIterator<WordForm> iUnmatchedForm(tmpUnmatchedForms);

        while (iUnmatchedForm.hasNext())
        {
            QVERIFY2(false,
                     ("Word " + iUnmatchedVerb.next()->getWord() +
                      " is unexpected with form: " +
                      iUnmatchedForm.value().getWordFormByStr()
                      + "; ").toUtf8());
        }
    }
}

QTEST_APPLESS_MAIN(TestVerbFormAllForms)

#include "test_VerbFormAllForms.moc"
