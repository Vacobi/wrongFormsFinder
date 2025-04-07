#include "word.h"
#include "verb.cpp"
#include "adjective.cpp"
#include "noun.cpp"
#include "numeral.cpp"
#include "pronoun.cpp"

static QString vowels = "aeiou";

Word::Word()
{
    this->word = "";
    QSet<WordForm> wordForms;
    wordForms.insert(WordForm(notSet, notSet, notSet, notSet));
    this->possibleFormsOfWord = wordForms;
}

Word::Word(const QString &word)
{
    this->word = word;
    QSet<WordForm> wordForms;
    wordForms.insert(WordForm(notSet, notSet, notSet, notSet));
    this->possibleFormsOfWord = wordForms;
}

Word::Word(const QString &word, const unsigned int &firstForm, const unsigned int &secondForm,
           const unsigned int &thirdForm, const unsigned int &auxForAdj)
{
    this->word = word;
    QSet<WordForm> wordForms;
    wordForms.insert(WordForm(firstForm, secondForm, thirdForm, auxForAdj));
    this->possibleFormsOfWord = wordForms;
}

Word::Word(const QString &word, const QSet<WordForm> &possibleFormsOfWord)
{
    this->word = word;
    this->possibleFormsOfWord = possibleFormsOfWord;
}

bool Word::operator==(const Word &wordToCompare) const
{
    return (this->word == wordToCompare.word &&
            this->possibleFormsOfWord == wordToCompare.possibleFormsOfWord);
}

bool Word::operator==(const Word* &lhs) const
{
    return this == lhs;
}

bool Word::operator==(const Word* lhs) const
{
    return this == lhs;
}

bool Word::operator==(const QString &toCompare) const
{
    return this->word == toCompare;
}

bool Word::operator<(const Word &other) const
{
    return word < other.word;
}

void Word::setWord(const QString &newWord)
{
    word = newWord;
}

QString Word::getWord() const
{
    return word;
}

void Word::setPossibleFormsOfWord(const QSet<WordForm> &newPossibleFormsOfWord)
{
    possibleFormsOfWord = newPossibleFormsOfWord;
}

void Word::addWordForm(const WordForm &newWordForm)
{
    this->possibleFormsOfWord << newWordForm;
}

QSet<WordForm> Word::getPossibleFormsOfWord() const
{
    return possibleFormsOfWord;
}

QSet<Word*> Word::formAllForms() const
{
    QSet<Word*> allForms;

    allForms << new Word(this->word);
    return allForms;
}

int Word::calculateFallacy(const WordForm& firstForm, const WordForm& secondForm) const
{
    int fallacy = 0;

    if (!(firstForm == secondForm))
    {
        fallacy += 100;
    }

    return fallacy;
}

QString Word::getType() const
{
    return "word";
}

bool Word::wordsAreEqual(const Word* otherWord, QString &misstakeMessage) const
{
    return this->wordsSame(*otherWord, misstakeMessage);
}

void Word::clearAllWord()
{
    this->clearWordAndPossibleForms();
}

posTags Word::getPosTag() const
{
    return notFound;
}

void Word::setWordWithForms(const QString &newWord, const QSet<WordForm> &newPossibleFormsOfWord)
{
    this->word = newWord;
    this->possibleFormsOfWord= newPossibleFormsOfWord;
}

bool Word::hasMatchingWord(const QSet<Word*> &setOfWordsToSearch, Word* &matchingWord) const
{
    QSet<Word*> tmpWordToSearch = setOfWordsToSearch;
    QMutableSetIterator<Word*> iWord(tmpWordToSearch);

    while (iWord.hasNext())
    {
        if(iWord.next()->word == this->word)
        {
            matchingWord = iWord.value();
            return true;
        }
    }

    return false;
}

bool Word::wordsSame(const Word &otherWord, QString &misstakeMessage) const
{
    //Word tmp = *this;

    if (*this == otherWord)
    {
        return true;
    }

    misstakeMessage = "In word " + this->word;

    if (this->getWord() != otherWord.getWord())
    {
        misstakeMessage += " expected word: " + this->getWord() + ", real: " + otherWord.getWord() + "; ";
    }

    QSet<WordForm> tmpExpWordForms = this->possibleFormsOfWord;
    QSet<WordForm> tmpOtherWordForms = otherWord.possibleFormsOfWord;

    QMutableSetIterator<WordForm> iExpWordForm(tmpExpWordForms);    

    while (iExpWordForm.hasNext())
    {
        if (!tmpOtherWordForms.remove(iExpWordForm.next()))
        {
            misstakeMessage += " correct form not generated: " + iExpWordForm.value().getWordFormByStr();
        }
    }

    QSetIterator<WordForm> iOtherWordForm(tmpOtherWordForms);

    while (iOtherWordForm.hasNext())
    {
        misstakeMessage += " unexpected form: " + iOtherWordForm.next().getWordFormByStr();
    }

    return false;
}

void Word::clearWordAndPossibleForms()
{
    this->word = "";
    this->possibleFormsOfWord.clear();
}

int max(const int &firstInteger, const int &secondInteger)
{
    if (firstInteger > secondInteger)
        return firstInteger;
    else
        return secondInteger;
}

int Word::countSyllables() const
{
    QString wordInLowercase = this->word.toLower();

    //... Гласными считаются буквы a, e, i, o, u

    //...Считать количество слогов 0
    int countOfSyllables = 0;
    //...Считать, что предыдущий символ не был гласной
    bool lastWasVowel = false;
    bool prevWasConsonant = true;

    // Для каждой буквы в слове
    for (QChar letter : wordInLowercase)
    {
        // Если текущая буква - гласная ИЛИ (y (которая является гласной. когда до нее согласная) и предыдущая буква согласная)
        if (vowels.contains(letter) || (letter == 'y' && prevWasConsonant))
        {
            // Если предыдущая буква согласная
            if (prevWasConsonant)
            {
                // Инкрементировать счетчик слогов
                countOfSyllables++;
                // Считать, что предыдущая буква была гласной
                prevWasConsonant = false;
            }
        }
        else
        {
            // Считать, что предыдущая буква была была согласной
            prevWasConsonant = true;
        }
    }

    //Если последняя буква e И предпоследняя буква не e
    if (wordInLowercase.endsWith('e') && wordInLowercase[wordInLowercase.length() - 2] != 'e')
    {
        // Уменьшить количество слогов на 1
        countOfSyllables--;
    }

    //Вернуть максимальное из количества слогов в слове и единицы
    return max(countOfSyllables, 1);
}

void Word::mergeFormsForAllWords(QSet<Word*> &words) const
{
    QMutableSetIterator<Word*> iFormsOfWord(words);
    QSet<WordForm> currentWordFormSet;

    QSet<Word*> mergedList;

    while (iFormsOfWord.hasNext())
    {
        if (!iFormsOfWord.next()->currentWordAlreadyInSet(mergedList))
        {
            currentWordFormSet.clear();
            currentWordFormSet.unite(iFormsOfWord.value()->possibleFormsOfWord);

            QMutableSetIterator<Word*> iMergedWord = iFormsOfWord;
            while (iMergedWord.hasNext())
            {
                if (iMergedWord.next()->getWord() == iFormsOfWord.value()->getWord())
                {
                    currentWordFormSet.unite(iMergedWord.value()->possibleFormsOfWord);
                }
            }

            if (typeid(*iFormsOfWord.value()) == typeid(Verb))
            {
                mergedList << new Verb(iFormsOfWord.value()->word, currentWordFormSet, QList<int> ());
            }
            else if (typeid(*iFormsOfWord.value()) == typeid(Adjective))
            {
                mergedList << new Adjective(iFormsOfWord.value()->word, currentWordFormSet, -1);
            }
            else if (typeid(*iFormsOfWord.value()) == typeid(Noun))
            {
                mergedList << new Noun(iFormsOfWord.value()->word, currentWordFormSet);
            }
            else if (typeid(*iFormsOfWord.value()) == typeid(Numeral))
            {
                mergedList << new Numeral(iFormsOfWord.value()->word, currentWordFormSet);
            }
            else if (typeid(*iFormsOfWord.value()) == typeid(Pronoun))
            {
                mergedList << new Pronoun(iFormsOfWord.value()->word, currentWordFormSet);
            }
            else
            {
                mergedList << new Word(iFormsOfWord.value()->word, currentWordFormSet);
            }
        }
    }

    words = mergedList;
}

bool Word::currentWordAlreadyInSet(const QSet<Word*> &set) const
{
    QSetIterator<Word*> iCurrentWordInSet(set);

    while (iCurrentWordInSet.hasNext())
    {
        if (iCurrentWordInSet.next()->word == this->word)
            return true;
    }

    return false;
}

QSet<WordForm> Word::definePossibleForms() const
{
    QSet<Word*> allForms = this->formAllForms();
    QSet<WordForm> allPossibleForms;

    for (Word* currentWord: allForms)
    {
        if (currentWord->word == this->word)
        {
            allPossibleForms.unite(currentWord->possibleFormsOfWord);
        }
    }

    if (allPossibleForms.empty())
    {
        allPossibleForms << WordForm();
    }

    return allPossibleForms;
}

bool isStaticVowel(QChar letter)
{
    return vowels.contains(letter.toLower());
}
