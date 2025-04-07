#include "linkedsentences.h"

void LinkedSentences::setLinkedSentences(const QList<QSet<Pair> > &newLinkedSentences)
{
    linkedSentences = newLinkedSentences;
}

QList<QSet<Pair>> LinkedSentences::getLinkedSentences()
{
    return linkedSentences;
}

int LinkedSentences::getFallacy() const
{
    return fallacy;
}

void LinkedSentences::setFallacy(int newFallacy)
{
    fallacy = newFallacy;
}

int LinkedSentences::getCountOfLinkedWords() const
{
    return countOfLinkedWords;
}

void LinkedSentences::setCountOfLinkedWords(int newCountOfLinkedWords)
{
    countOfLinkedWords = newCountOfLinkedWords;
}

LinkedSentences::LinkedSentences()
{
    this->fallacy = 0;
    this->countOfLinkedWords = 0;
}

void LinkedSentences::linkSentences(Sentence &correctSentence, Sentence &verifiedSentence)
{
    //Очистить список согласованных пар
    this->linkedSentences.clear();

    //Установить формы слов и вспомогательные в правильном предложении
    correctSentence.setFormsInCorrectSentence();

    //Составить все возможные пары слов первого предложения со вторым, рассчитав их правильность
    QList<Pair> currentPairList;
    QList<Pair> allAvailablePairs = this->generateAllPairs(correctSentence, verifiedSentence);

    //Составить все возможные варианты согласования предложений с наибольшим количеством согласованных слов и с наименьшей ошибочностью
    this->recoursivePairsLink(allAvailablePairs, 0, currentPairList, 0, 0);
}

void LinkedSentences::clearList()
{
    ;
}

QList<Pair> LinkedSentences::generateAllPairs(const Sentence &correctSentence, const Sentence &verifiedSentence) const
{
    QList<Pair> listOfPairs;
    int indexOfWordFromCorrect = 0;
    QStringList wordsInVerified;

    for (Word* currentWord: verifiedSentence.getSentence())
    {
        wordsInVerified << currentWord->getWord();
    }

    //Для каждого слова в правильном предложении, имеющего pos-тег adj, noun, pron, num или verb
    for (Word* currentWordInCorrect: correctSentence.getSentence())
    {
        if (typeid(*currentWordInCorrect) == typeid(Adjective) ||
            typeid(*currentWordInCorrect) == typeid(Noun) ||
            typeid(*currentWordInCorrect) == typeid(Pronoun) ||
            typeid(*currentWordInCorrect) == typeid(Numeral) ||
            typeid(*currentWordInCorrect) == typeid(Verb))
        {
            // Образовать все формы данного слова
            QSet<Word*> tmpFormsOfWord = currentWordInCorrect->formAllForms();

            QMutableSetIterator<Word*> iCurrentWordFromCorrect(tmpFormsOfWord);
            // Для каждой формы, различной по написанию
            for (Word* currentFormOfWordToSearch: tmpFormsOfWord)
            {
                unsigned int startSearchPos = 0;
                int indexOfWordFromVerified;
                //Пока текущее слово встречается в проверяемом предложении
                while ((indexOfWordFromVerified = wordsInVerified.indexOf(currentFormOfWordToSearch->getWord(), startSearchPos)) != -1)
                {
                    // Определить все соответствующие ему наборы вспомогательных слов
                    QSet<Word*> wordsInVerified = verifiedSentence.setFormInVerifiedSentence(indexOfWordFromVerified,
                                                                                             currentFormOfWordToSearch->getPossibleFormsOfWord(),
                                                                                             currentFormOfWordToSearch->getPosTag());

                    // Создать пары, соединив все формы слова, одинаковых по написанию из правильного предложения,
                    // со всеми наборами вспомогательных слов и установить правильность
                    this->createPairs(listOfPairs, currentWordInCorrect,
                                wordsInVerified, indexOfWordFromCorrect, indexOfWordFromVerified);

                    startSearchPos = indexOfWordFromVerified + 1;
                }
            }
        }

        indexOfWordFromCorrect++;
    }

    return listOfPairs;
}

void LinkedSentences::createPairs(QList<Pair> &currentPairList, Word* &currentWordInCorrect,
                                  QSet<Word*> &wordsInVerified,
                                  const int &indexOfWordFromCorrect, const int &indexOfWordFromVerified) const
{
    for (WordForm currentCorrectForm: currentWordInCorrect->getPossibleFormsOfWord())
    {
        for (Word* currentVerifiedWord: wordsInVerified)
        {
            for (WordForm curentVerifiedForm: currentVerifiedWord->getPossibleFormsOfWord())
            {
                // Создать пары, соединив все формы слова, одинаковых по написанию из правильного предложения, со всеми наборами вспомогательных слов
                Pair generatedPair = Pair(currentWordInCorrect, currentVerifiedWord,
                                          currentCorrectForm, curentVerifiedForm,
                                          indexOfWordFromCorrect, indexOfWordFromVerified);

                int indexOfPair = 0;

                bool pairWasAdded = false;
                bool equalPairFound = false;
                bool betterPairFound = false;

                QMutableListIterator<Pair> iCurrentPair(currentPairList);

                while (iCurrentPair.hasNext() && !betterPairFound)
                {
                    int status = generatedPair.pairMustBeInList(iCurrentPair.next());

                    if (status == replaceItem && !pairWasAdded)
                    {
                        iCurrentPair.setValue(generatedPair);
                        pairWasAdded = true;
                    }
                    else if (status == replaceItem && pairWasAdded)
                    {
                        iCurrentPair.remove();
                    }
                    else if (status == addItem && !pairWasAdded)
                    {
                        equalPairFound = true;
                    }
                    else if (status == skipItem)
                    {
                        betterPairFound = true;
                    }

                    indexOfPair++;
                }

                if(!pairWasAdded && !betterPairFound)
                {
                    currentPairList.append(generatedPair);
                }
            }
        }
    }
}

    /**
     * @brief recoursivePairsLink
     * Рекурсивное создание всех возможных вариантов согласования
     * @param[in] firstSentence - первое предложение, где первое измерение как бы "слово" из данного предложения,
     * а второе - все формы этого слова, причем во втором измерении самым первым идет оригинальное слово из предложения
     * @param[in] secondSentence - второе предложение
     * @param[in] numberOfListFirstSentence - номер элемента первого измерения
     * @param[in] numberInListFIrstSentence - номер слова в данном элементе
     * @param[in|out] currentSolution - текущий список пар
     * Каждое решение записывает в элемент данных класса QList<QList<Pair>> linkedSentences
     */
void LinkedSentences::recoursivePairsLink(const QList<Pair> &listOfPairs, int numberOfPair, QList<Pair> &currentLinkedPairsList,
                         unsigned long long int bitCartForCorrectSentence, unsigned long long int bitCartForVerifiedSentence)
{
    //Считать, что цикл не заходил в рекурсию
    bool enteredInRecursion = false;

    QListIterator<Pair> iCurrentPair(listOfPairs);

    for (int i = 0; i < numberOfPair && iCurrentPair.hasNext(); iCurrentPair.next(), i++);

    //Для каждой пары
    while (iCurrentPair.hasNext())
    {
        Pair tmpPair = iCurrentPair.next();
        numberOfPair++;

        //Если ни одно из слов данной пары (включая вспомогательные) не содержится в текущем сочетании пар
        if (bitsAreFree(tmpPair.getWordIndexFromCorrectSentence(), tmpPair.getIndexesOfAuxiliariesInCorrect(), bitCartForCorrectSentence) &&
            bitsAreFree(tmpPair.getWordIndexFromVerifiedSentence(), tmpPair.getIndexesOfAuxiliariesInVerified(), bitCartForVerifiedSentence))
        {
            //Добавить пару к текущему сочетанию пар
            currentLinkedPairsList << tmpPair;

            //Отметить на картах занятости слова из пары как использованные
            bitCartForCorrectSentence = setBits(tmpPair.getWordIndexFromCorrectSentence(), tmpPair.getIndexesOfAuxiliariesInCorrect(), bitCartForCorrectSentence);
            bitCartForVerifiedSentence = setBits(tmpPair.getWordIndexFromVerifiedSentence(), tmpPair.getIndexesOfAuxiliariesInVerified(), bitCartForVerifiedSentence);

            //Составить с текущем сочетанием пар все возможные последующие сочетания пар
            this->recoursivePairsLink(listOfPairs, numberOfPair, currentLinkedPairsList, bitCartForCorrectSentence, bitCartForVerifiedSentence);

            //Считать, что цикл заходил в рекурсию
            enteredInRecursion = true;

            //Удалить пару из текущего сочетания пар
            currentLinkedPairsList.removeLast();

            //Отметить на картах занятости слова из пары как неиспользованные
            bitCartForCorrectSentence = resetBits(tmpPair.getWordIndexFromCorrectSentence(), tmpPair.getIndexesOfAuxiliariesInCorrect(), bitCartForCorrectSentence);
            bitCartForVerifiedSentence = resetBits(tmpPair.getWordIndexFromVerifiedSentence(), tmpPair.getIndexesOfAuxiliariesInVerified(), bitCartForVerifiedSentence);
        }
    }

    //Если цикл не заходил в рекурсию
    if (!enteredInRecursion)
    {
        // Обработать данное решение
        this->processSolution(currentLinkedPairsList);
    }
}

void LinkedSentences::processSolution(const QList<Pair> &currentLinkedPairsList)
{
    int countOfWordsInCurrentLink = 0, fallacyOfSet = 0;
    QSet<Pair> currentLinkedPairsSet;

    // Считаем ошибочность и количество слов в проверяемом предложении текущего решения
    for (Pair currentPair: currentLinkedPairsList)
    {
        // Прибавляем главное слово
        countOfWordsInCurrentLink++;

        // Прибавляем вспомогательные слова
        countOfWordsInCurrentLink += currentPair.getIndexesOfAuxiliariesInVerified().count();

        // Прибавляем ошибочность пары
        fallacyOfSet += currentPair.getDegreeOfFallacy();

        // Добавляем пары в QList, чтобы добавить их к полю класса
        currentLinkedPairsSet.insert(currentPair);
    }

    // Если количество слов в текущем решении больше чем в уже добавленном или
    // столько же слов и меньше ошибочность, заменяем предыдущеие решения
    if (countOfWordsInCurrentLink > this->countOfLinkedWords ||
        (countOfWordsInCurrentLink == this->countOfLinkedWords && fallacyOfSet < this->fallacy))
    {
        this->linkedSentences.clear();

        this->linkedSentences << currentLinkedPairsSet;
        this->countOfLinkedWords = countOfWordsInCurrentLink;
        this->fallacy = fallacyOfSet;
    }
    else if (countOfWordsInCurrentLink == this->countOfLinkedWords && fallacyOfSet == this->fallacy && !currentLinkedPairsList.empty())
    { // Если количество согласованных слов совпадает и у них такая же ошибчность, как у предыдущего решения
      // Добавляем текущее решения в список согласований
        this->linkedSentences << currentLinkedPairsSet;
    }
}

QString LinkedSentences::getCurrentSetsMisstakes(const Sentence &correctSentence, const Sentence &verifiedSentence)
{
    QString currentSetMessage, mesageForAllSolutions;
    QStringList setsOfMissakes;
    int numberOfSolution = 0;

    for (QSet<Pair> currentPairSet: this->linkedSentences)
    {
        for (Pair currentPair: currentPairSet)
        {
            currentSetMessage += currentPair.getPairMisstakeMessage(correctSentence, verifiedSentence);
        }

        if (currentSetMessage == "")
        {
            currentSetMessage += "Все формы слов в предложении употреблены корректно.\n";
        }

        currentSetMessage += "\n";

        if (!setsOfMissakes.contains(currentSetMessage))
        {
            setsOfMissakes << currentSetMessage;
        }

        currentSetMessage.clear();
    }

    for (QString currentSet: setsOfMissakes)
    {
        numberOfSolution++;
        mesageForAllSolutions += QString::number(numberOfSolution) + " Вариант согласования:\n";
        mesageForAllSolutions += currentSet;
    }

    return mesageForAllSolutions;
}

bool bitSetted(unsigned long long int value, unsigned long long int position)
{
    return ((value & (1 << position)) != 0);
}

int resetBit(const unsigned long long int value, unsigned long long int position)
{
    return (value & ~(1 << position));
}

unsigned int setBit(const unsigned long long int value, unsigned long long int position)
{
    return (value | (1 << position));
}

unsigned long long int resetBits(unsigned int indexOfMainWord, QList<int> indexesOfAuxiliaries, unsigned long long int bitCard)
{
    indexesOfAuxiliaries.prepend(indexOfMainWord);

    for (int currentIndex: indexesOfAuxiliaries)
    {
        bitCard = resetBit(bitCard, currentIndex);
    };

    return bitCard;
}

unsigned long long int setBits(unsigned int indexOfMainWord, QList<int> indexesOfAuxiliaries, unsigned long long int bitCard)
{
    indexesOfAuxiliaries.prepend(indexOfMainWord);

    for (int currentIndex: indexesOfAuxiliaries)
    {
        bitCard = setBit(bitCard, currentIndex);
    }

    return bitCard;
}

bool bitsAreFree(unsigned int indexOfMainWord, QList<int> indexesOfAuxiliaries, const unsigned long long int bitCard)
{
    indexesOfAuxiliaries.prepend(indexOfMainWord);

    for (int currentIndex: indexesOfAuxiliaries)
    {
        if (bitSetted(bitCard, currentIndex))
        {
            return false;
        }
    }

    return true;
}
