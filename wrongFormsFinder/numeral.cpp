#include "numeral.h"

Numeral::Numeral(): Word()
{
    ;
}

Numeral::Numeral(const QString &newWord): Word (newWord)
{
    ;
}

Numeral::Numeral(const QString &word, const unsigned int &firstForm, const unsigned int &secondForm,
        const unsigned int &thirdForm, const unsigned int &auxForAdj)
    : Word (word, firstForm, secondForm, thirdForm, auxForAdj)
{
    ;
}

Numeral::Numeral(const QString &word, const QSet<WordForm> &possibleFormsOfWord) : Word(word, possibleFormsOfWord)
{
    ;
}

bool Numeral::operator==(const Numeral &toCompare) const
{
    return (this->word == toCompare.word &&
            this->possibleFormsOfWord == toCompare.possibleFormsOfWord);
}

QSet<Word*> Numeral::formAllForms() const
{
    QSet<Word*> tmpWordSet;
    Numeral tmpCardinal, tmpOrdinal;

    //Образовать количественную форму числительного
    tmpCardinal = this->formCardinal();
    //Добавить ее в список
    tmpWordSet << new Numeral(tmpCardinal);

    //Образовать порядковую форму числительного
    tmpOrdinal = tmpCardinal.formOrdinal(tmpCardinal.word);
    //Добавить ее в список
    tmpWordSet << new Numeral(tmpOrdinal);

    return tmpWordSet;
}

int Numeral::calculateFallacy(const WordForm& firstForm, const WordForm& secondForm) const
{
    int fallacy = 0;

    //Если формы не совпадают
    if (!(firstForm == secondForm))
    {
        // Прибавить к ошибочности 100
        fallacy = 100;
    }

    return fallacy;
}

QString Numeral::getType() const
{
    return "num";
}

bool Numeral::wordsAreEqual(const Word* otherWord, QString &misstakeMessage) const
{
    return this->wordsSame(*otherWord, misstakeMessage);
}

void Numeral::clearAllWord()
{
    this->clearWordAndPossibleForms();
}

posTags Numeral::getPosTag() const
{
    return num;
}

void Numeral::setForm(const QString &newWord, const formOfNumeral &newForm)
{
    this->word = newWord;
    QSet<WordForm> wordForms;
    wordForms.insert(WordForm(newForm, notSet, notSet, notSet));
    this->possibleFormsOfWord = wordForms;
}

Numeral Numeral::formCardinal() const
{
    int lenOfWord = this->word.length();
    QString tmpWord = this->word;

    if (lenOfWord)
    {
        //Если слово заканчивается на th или оно first, second, third
        if (tmpWord.endsWith("th") ||
            this->word == "first" ||
            this->word == "second" || this->word == "third")
        {
            if (tmpWord == "first")
            {
                // Его количественная форма one
                tmpWord = "one";
            }
            else if (tmpWord == "second")
            {
                tmpWord = "two";
            }
            else if (tmpWord == "third")
            {
                tmpWord = "three";
            }
            else if (tmpWord.endsWith("fth"))
            {
                tmpWord.replace(lenOfWord - 3, 3, "ve");
            }
            else if (tmpWord.endsWith("ieth"))
            {
                tmpWord.replace(lenOfWord - 4, 4, "y");
            }
            else if (tmpWord == "ninth")
            {
                tmpWord = "nine";
            }
            else
            {
                tmpWord.replace(lenOfWord - 2, 2, "");
            }
        }
    }

    WordForm tmpForm;
    // Присвоить слову в первое поле метку cardinal
    Numeral cardinalForm;
    cardinalForm.setForm(tmpWord, cardinal);
    // Вернуть слово
    return cardinalForm;
}

Numeral Numeral::formOrdinal(const QString &numeral) const
{
    int lenOfWord = numeral.length();
    QString tmpWord = numeral;
    Numeral ordinalForm;

    if (numeral == "one")
    {
        // Его количественная форма one
        tmpWord = "first";
    }
    else if (numeral == "two")
    {
        tmpWord = "second";
    }
    else if (numeral == "three")
    {
        tmpWord = "third";
    }
    else if (numeral.endsWith("ve"))
    {
        tmpWord.replace(lenOfWord - 2, 2,"fth");
    }
    else if (numeral.endsWith("y"))
    {
        tmpWord.replace(lenOfWord - 1, 1, "ieth");
    }
    else if (numeral == "nine")
    {
        tmpWord = "ninth";
    }
    else
    {
        tmpWord.append("th");
    }

    WordForm tmpForm;
    // Присвоить слову в первое поле метку cardinal
    ordinalForm.setForm(tmpWord, ordinal);
    // Вернуть слово
    return ordinalForm;
}
