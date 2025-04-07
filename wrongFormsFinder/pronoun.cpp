#include "pronoun.h"

static QStringList objectiveNominative    = {"i",    "you",   "he",  "she",  "it",  "we",   "they"};
static QStringList objectiveObjectiveForm = {"me",   "you",   "him", "her",  "it",  "us",   "them"};
static QStringList possessiveMainForm     = {"my",   "your",  "his", "her",  "its", "our",  "their"};
static QStringList possessiveAbsoluteForm = {"mine", "yours", "his", "hers", "its", "ours", "theirs"};

Pronoun::Pronoun(): Word()
{
    ;
}

Pronoun::Pronoun(const QString &newWord): Word (newWord)
{
    ;
}

Pronoun::Pronoun(const QString &word, const unsigned int &firstForm, const unsigned int &secondForm,
                 const unsigned int &thirdForm, const unsigned int &auxForAdj)
    : Word (word, firstForm, secondForm, thirdForm, auxForAdj)
{
    ;
}

Pronoun::Pronoun(const QString &word, const QSet<WordForm> &possibleFormsOfWord) : Word(word, possibleFormsOfWord)
{
    ;
}

QSet<Word*> Pronoun::formAllForms() const
{
    QSet<Word*> setOfPronouns;

    // Определить местоимение
    QStringList allFormsOfPronoun = this->findPronoun();

    // Если такого местоимения не существует
    if (allFormsOfPronoun.length() == 0)
    {
        setOfPronouns << new Pronoun(this->word, QSet<WordForm> ());
    }
    else
    {
        setOfPronouns << new Pronoun(this->formObjeciveNominative(allFormsOfPronoun[0]));
        setOfPronouns << new Pronoun(this->formObjeciveObjectiveForm(allFormsOfPronoun[1]));
        setOfPronouns << new Pronoun(this->formPossessiveMainForm(allFormsOfPronoun[2]));
        setOfPronouns << new Pronoun(this->formPossessiveAbsoluteForm(allFormsOfPronoun[3]));

        // Объединить все слова, совпадающие по написанию
        this->mergeFormsForAllWords(setOfPronouns);
    }

    return setOfPronouns;
}

int Pronoun::calculateFallacy(const WordForm& firstForm, const WordForm& secondForm) const
{
    int fallacy = 0;
    QSet<unsigned int> tmpFirstCol, tmpSecondCol;
    tmpFirstCol << nominative << mainForm;
    tmpSecondCol << objectivePron << absoluteForm;

    //Если не совпадает падеж
    if (firstForm.getFirstForm() != secondForm.getFirstForm())
    {
        // Прибавить к ошибочности 30
        fallacy += 30;
    }

    QSet<unsigned int> realSecondForms;
    realSecondForms << firstForm.getSecondForm() << secondForm.getSecondForm();

    //Если не совпадает форма


    if (((firstForm.getSecondForm() == nominative && secondForm.getSecondForm() == mainForm) ||
         (firstForm.getSecondForm() == mainForm && secondForm.getSecondForm() == nominative) ||
         (firstForm.getSecondForm() == objectivePron && secondForm.getSecondForm() == absoluteForm) ||
         (firstForm.getSecondForm() == absoluteForm && secondForm.getSecondForm() == objectivePron)))
    {
        ;
    }
    else if (firstForm.getSecondForm() != secondForm.getSecondForm())
    {
        fallacy += 30;
    }

    //Если не совпадает число
    if (firstForm.getThirdForm() != secondForm.getThirdForm())
    {
        // Прибавить к ошибочности 40
        fallacy += 40;
    }

    return fallacy;
}

QString Pronoun::getType() const
{
    return "pronoun";
}

bool Pronoun::wordsAreEqual(const Word* otherWord, QString &misstakeMessage) const
{
    return this->wordsSame(*otherWord, misstakeMessage);
}

void Pronoun::clearAllWord()
{
    this->clearWordAndPossibleForms();
}

posTags Pronoun::getPosTag() const
{
    return pron;
}

QStringList Pronoun::findPronoun() const
{
    QList<QStringList> allPronouns;
    allPronouns << objectiveNominative << objectiveObjectiveForm
                << possessiveMainForm << possessiveAbsoluteForm;

    int tmpIndex = -1;
    QStringList allFormsOfPronoun;

    QListIterator<QStringList> iCurrentForm(allPronouns);

    while (iCurrentForm.hasNext() && tmpIndex == -1)
    {
        tmpIndex = iCurrentForm.next().indexOf(this->word);
    }

    if (tmpIndex != -1)
    {
        allFormsOfPronoun << objectiveNominative[tmpIndex] << objectiveObjectiveForm[tmpIndex]
                          << possessiveMainForm[tmpIndex] << possessiveAbsoluteForm[tmpIndex];
    }

    return allFormsOfPronoun;
}

Pronoun Pronoun::formObjeciveNominative(const QString &pron) const
{
    QSet<WordForm> formsOfPronoun;
    Pronoun tmpPron(pron);

    // Местоимения единственного числа
    if (pron != "we" && pron != "they")
    {
        formsOfPronoun << WordForm(objective, nominative, singular, notSet);
    }

    // Местоимение множественного числа
    if (pron == "we" || pron == "they" || pron == "you")
    {
        formsOfPronoun << WordForm(objective, nominative, plural, notSet);
    }

    tmpPron.setPossibleFormsOfWord(formsOfPronoun);
    return tmpPron;
}

Pronoun Pronoun::formObjeciveObjectiveForm(const QString &pron) const
{
    QSet<WordForm> formsOfPronoun;
    Pronoun tmpPron(pron);

    // Местоимения единственного числа
    if (pron != "us" && pron != "them")
    {
        formsOfPronoun << WordForm(objective, objectivePron, singular, notSet);
    }

    // Местоимение множественного числа
    if (pron == "us" || pron == "them" || pron == "you")
    {
        formsOfPronoun << WordForm(objective, objectivePron, plural, notSet);
    }

    tmpPron.setPossibleFormsOfWord(formsOfPronoun);
    return tmpPron;
}

Pronoun Pronoun::formPossessiveMainForm(const QString &pron) const
{
    QSet<WordForm> formsOfPronoun;
    Pronoun tmpPron(pron);

    // Местоимения единственного числа
    if (pron != "our" && pron != "their")
    {
        formsOfPronoun << WordForm(possessive, mainForm, singular, notSet);
    }

    // Местоимение множественного числа
    if (pron == "our" || pron == "their" || pron == "your")
    {
        formsOfPronoun << WordForm(possessive, mainForm, plural, notSet);
    }

    tmpPron.setPossibleFormsOfWord(formsOfPronoun);
    return tmpPron;
}

Pronoun Pronoun::formPossessiveAbsoluteForm(const QString &pron) const
{
    QSet<WordForm> formsOfPronoun;
    Pronoun tmpPron(pron);

    // Местоимения единственного числа
    if (pron != "ours" && pron != "theirs")
    {
        formsOfPronoun << WordForm(possessive, absoluteForm, singular, notSet);
    }

    // Местоимение множественного числа
    if (pron == "ours" || pron == "theirs" || pron == "yours")
    {
        formsOfPronoun << WordForm(possessive, absoluteForm, plural, notSet);
    }

    tmpPron.setPossibleFormsOfWord(formsOfPronoun);
    return tmpPron;
}
