#include "auxiliary.h"

Auxiliary::Auxiliary(): Word()
{
    ;
}

Auxiliary::Auxiliary(const QString &newWord): Word (newWord)
{
    ;
}

Auxiliary::Auxiliary(const QString &word, const unsigned int &firstForm, const unsigned int &secondForm,
                 const unsigned int &thirdForm, const unsigned int &auxForAdj)
    : Word (word, firstForm, secondForm, thirdForm, auxForAdj)
{
    ;
}

Auxiliary::Auxiliary(const QString &word, const QSet<WordForm> &possibleFormsOfWord) : Word(word, possibleFormsOfWord)
{
    ;
}

QSet<Word*> Auxiliary::formAllForms() const
{
    QSet<Word*> allForms;

    allForms << new Auxiliary(this->word);

    return allForms;
}

int Auxiliary::calculateFallacy(const WordForm& firstForm, const WordForm& secondForm) const
{
    int fallacy = 0;

    if (!(firstForm == secondForm))
    {
        fallacy += 100;
    }

    return fallacy;
}

QString Auxiliary::getType() const
{
    return "auxiliary";
}

bool Auxiliary::wordsAreEqual(const Word* otherWord, QString &misstakeMessage) const
{
    return this->wordsSame(*otherWord, misstakeMessage);
}

void Auxiliary::clearAllWord()
{
    this->clearWordAndPossibleForms();
}

posTags Auxiliary::getPosTag() const
{
    return aux;
}
