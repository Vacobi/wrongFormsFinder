#include "pair.h"

int Pair::getWordIndexFromCorrectSentence() const
{
    return wordIndexFromCorrectSentence;
}

void Pair::setWordIndexFromCorrectSentence(int newWordIndexFromCorrectSentence)
{
    wordIndexFromCorrectSentence = newWordIndexFromCorrectSentence;
}

QList<int> Pair::getIndexesOfAuxiliariesInCorrect() const
{
    return indexesOfAuxiliariesInCorrect;
}

void Pair::setIndexesOfAuxiliariesInCorrect(const QList<int> &newIndexesOfAuxiliariesInCorrect)
{
    indexesOfAuxiliariesInCorrect = newIndexesOfAuxiliariesInCorrect;
}

WordForm Pair::getWordFormFromCorrectSentence() const
{
    return wordFormFromCorrectSentence;
}

void Pair::setWordFormFromCorrectSentence(const WordForm &newWordFormFromCorrectSentence)
{
    wordFormFromCorrectSentence = newWordFormFromCorrectSentence;
}

int Pair::getWordIndexFromVerifiedSentence() const
{
    return wordIndexFromVerifiedSentence;
}

void Pair::setWordIndexFromVerifiedSentence(int newWordIndexFromVerifiedSentence)
{
    wordIndexFromVerifiedSentence = newWordIndexFromVerifiedSentence;
}

QList<int> Pair::getIndexesOfAuxiliariesInVerified() const
{
    return indexesOfAuxiliariesInVerified;
}

void Pair::setIndexesOfAuxiliariesInVerified(const QList<int> &newIndexesOfAuxiliariesInVerified)
{
    indexesOfAuxiliariesInVerified = newIndexesOfAuxiliariesInVerified;
}

WordForm Pair::getWordFormFromVerifiedSentence() const
{
    return wordFormFromVerifiedSentence;
}

void Pair::setWordFormFromVerifiedSentence(const WordForm &newWordFormFromVerifiedSentence)
{
    wordFormFromVerifiedSentence = newWordFormFromVerifiedSentence;
}

posTags Pair::getPosTag() const
{
    return posTag;
}

void Pair::setPosTag(posTags newPosTag)
{
    posTag = newPosTag;
}

int Pair::getDegreeOfFallacy() const
{
    return degreeOfFallacy;
}

void Pair::setDegreeOfFallacy(int newDegreeOfFallacy)
{
    degreeOfFallacy = newDegreeOfFallacy;
}

Pair::Pair()
{
    wordIndexFromCorrectSentence = -1;
    //indexesOfAuxiliariesInCorrect.append(-1);
    wordFormFromCorrectSentence.setWordForm(notSet, notSet, notSet, notSet);
    wordIndexFromVerifiedSentence = -1;
    //indexesOfAuxiliariesInVerified.append(-1);
    wordFormFromVerifiedSentence.setWordForm(notSet, notSet, notSet, notSet);
    posTag = x;
    degreeOfFallacy = -1;
}

Pair::Pair(const int &newWordIndexFromCorrectSentence, const QList<int> &NewIndexesOfAuxiliariesInCorrect,
     const WordForm &newWordFormFromCorrectSentence, const int &newWordIndexFromVerifiedSentence,
     const QList<int> &newIndexesOfAuxiliariesInVerified, const WordForm &newWordFormFromVerifiedSentence,
     const posTags &newPosTag, const int &newDegreeOfFallacy)
{
    wordIndexFromCorrectSentence = newWordIndexFromCorrectSentence;
    indexesOfAuxiliariesInCorrect = NewIndexesOfAuxiliariesInCorrect;
    wordFormFromCorrectSentence.setWordForm(newWordFormFromCorrectSentence);
    wordIndexFromVerifiedSentence = newWordIndexFromVerifiedSentence;
    indexesOfAuxiliariesInVerified = newIndexesOfAuxiliariesInVerified;
    wordFormFromVerifiedSentence.setWordForm(newWordFormFromVerifiedSentence);
    posTag = newPosTag;
    degreeOfFallacy = newDegreeOfFallacy;
}

Pair::Pair(Word* &wordFromCorrect, Word* &wordFromVerified,
           const WordForm &formFromCorrect, const WordForm &formFromVerified,
           const int &indexOfCorrect, const int &indexOfVerified)
{
    // Устанавливаем индекс слова правильного предложения
    wordIndexFromCorrectSentence = indexOfCorrect;
    // Устанавливаем индекс слова проверяемого предложения
    wordIndexFromVerifiedSentence = indexOfVerified;
    // Устанавливаем часть речи пары
    posTag = wordFromCorrect->getPosTag();

    // Устанавливаем форму правильного слова
    wordFormFromCorrectSentence.setWordForm(formFromCorrect);

    // Устанавливаем форму проверяемого слова
    wordFormFromVerifiedSentence.setWordForm(formFromVerified);

    // Устанавливаем вспомогательные слова к глаголу
    if (typeid(*wordFromCorrect) == typeid(Verb))
    {
        const Verb *currentVerbInCorrect = dynamic_cast<const Verb*>(wordFromCorrect);
        // Устанавливаем вспомогательные к глаголу из правильного предложения
        indexesOfAuxiliariesInCorrect = currentVerbInCorrect->getIndexesOfAuxiliaries();

        const Verb *currentVerbInVerified = dynamic_cast<const Verb*>(wordFromVerified);
        // Устанавливаем вспомогательные к глаголу из правильного предложения
        indexesOfAuxiliariesInVerified = currentVerbInVerified->getIndexesOfAuxiliaries();
    }
    else if (typeid(*wordFromCorrect) == typeid(Adjective))
    { // Устанавливаем вспомогательное слово к прилагательному

        const Adjective *currentAdjectiveInCorrect = dynamic_cast<const Adjective*>(wordFromCorrect);
        QList<int> tmpAdjAuxInCorrect;
        if (currentAdjectiveInCorrect->getIndexOfAuxiliary() != -1)
        {
            tmpAdjAuxInCorrect << currentAdjectiveInCorrect->getIndexOfAuxiliary();
        }
        // Устанавливаем вспомогательное для прилагательного
        indexesOfAuxiliariesInCorrect = tmpAdjAuxInCorrect;

        const Adjective *currentAdjectiveInVerified = dynamic_cast<const Adjective*>(wordFromVerified);
        QList<int> tmpAdjAuxInVerified;
        if (currentAdjectiveInVerified->getIndexOfAuxiliary() != -1)
        {
            tmpAdjAuxInVerified << currentAdjectiveInVerified->getIndexOfAuxiliary();
        }
        // Устанавливаем вспомогательное для прилагательного
        indexesOfAuxiliariesInVerified = tmpAdjAuxInVerified;
    }

    // Рассчитываем ошибочность пары
    this->degreeOfFallacy = wordFromCorrect->calculateFallacy(this->wordFormFromCorrectSentence, this->wordFormFromVerifiedSentence);
}

Pair::Pair(Word* &wordFromCorrect, Word* &wordFromVerified,
           const int &indexOfCorrect, const int &indexOfVerified)
{
    // Устанавливаем индекс слова правильного предложения
    wordIndexFromCorrectSentence = indexOfCorrect;
    // Устанавливаем индекс слова проверяемого предложения
    wordIndexFromVerifiedSentence = indexOfVerified;
    // Устанавливаем часть речи пары
    posTag = wordFromCorrect->getPosTag();

    QSet<WordForm> correctFormSet = wordFromCorrect->getPossibleFormsOfWord();
    QSet<WordForm> VerifiedFormSet = wordFromVerified->getPossibleFormsOfWord();

    // Если в правильном слове есть какие-либо формы, устанавливаем их
    if (!correctFormSet.isEmpty())
    {
        QSetIterator<WordForm> iCurrentFormFromCorrect(correctFormSet);
        wordFormFromCorrectSentence.setWordForm(iCurrentFormFromCorrect.next());
    }
    else // Иначе устанавливаем неопределенную форму
    {
        wordFormFromCorrectSentence.setWordForm(WordForm(notSet, notSet, notSet, notSet));
    }

    // Если в проверяемом слове есть какие-либо формы, устанавливаем их
    if (!VerifiedFormSet.isEmpty())
    {
        QSetIterator<WordForm> iCurrentFormFromVerified(VerifiedFormSet);
        wordFormFromVerifiedSentence.setWordForm(iCurrentFormFromVerified.next());
    }
    else // Иначе устанавливаем неопределенную форму
    {
        wordFormFromVerifiedSentence.setWordForm(WordForm(notSet, notSet, notSet, notSet));
    }

    // Устанавливаем вспомогательные слова к глаголу
    if (typeid(*wordFromCorrect) == typeid(Verb))
    {
        const Verb *currentVerb = dynamic_cast<const Verb*>(wordFromCorrect);
        // Устанавливаем вспомогательные к глаголу из правильного предложения
        indexesOfAuxiliariesInCorrect = currentVerb->getIndexesOfAuxiliaries();
    }
    else if (typeid(*wordFromCorrect) == typeid(Adjective))
    { // Устанавливаем вспомогательное слово к прилагательному

        const Adjective *currentAdjective = dynamic_cast<const Adjective*>(wordFromCorrect);
        QList<int> tmpAdjAux;
        tmpAdjAux << currentAdjective->getIndexOfAuxiliary();
        // Устанавливаем вспомогательное для прилагательного
        indexesOfAuxiliariesInCorrect = tmpAdjAux;
    }

    // Рассчитываем ошибочность пары
    this->degreeOfFallacy = wordFromCorrect->calculateFallacy(this->wordFormFromCorrectSentence, this->wordFormFromVerifiedSentence);
}

void Pair::setAllParameters(const int &newWordIndexFromCorrectSentence, const QList<int> &NewIndexesOfAuxiliariesInCorrect,
                            const WordForm &newWordFormFromCorrectSentence, const int &newWordIndexFromVerifiedSentence,
                            const QList<int> &newIndexesOfAuxiliariesInVerified, const WordForm &newWordFormFromVerifiedSentence,
                            const posTags &newPosTag, const int &newDegreeOfFallacy)
{
    this->wordIndexFromCorrectSentence = newWordIndexFromCorrectSentence;
    this->indexesOfAuxiliariesInCorrect = NewIndexesOfAuxiliariesInCorrect;
    this->wordFormFromCorrectSentence.setWordForm(newWordFormFromCorrectSentence);
    this->wordIndexFromVerifiedSentence = newWordIndexFromVerifiedSentence;
    this->indexesOfAuxiliariesInVerified = newIndexesOfAuxiliariesInVerified;
    this->wordFormFromVerifiedSentence.setWordForm(newWordFormFromVerifiedSentence);
    this->posTag = newPosTag;
    this->degreeOfFallacy = newDegreeOfFallacy;;
}


QString Pair::getIndexesOfAuxiliariesInCorrectByStr() const
{
    QString stringWithIndexes;

    for (int currentIndex: this->indexesOfAuxiliariesInCorrect)
    {
        stringWithIndexes += (QString::number(currentIndex) + ", ");
    }

    return stringWithIndexes;
}

QString Pair::getIndexesOfAuxiliariesInVerifiedByStr() const
{
    QString stringWithIndexes;

    for (int currentIndex: this->indexesOfAuxiliariesInVerified)
    {
        stringWithIndexes += (QString::number(currentIndex) + ", ");
    }

    return stringWithIndexes;
}

bool Pair::findMatchingPair(const QSet<Pair> &pairsSet, Pair &matchingPair) const
{
    QSetIterator<Pair> iCurrentPair(pairsSet);
    Pair currentPair;

    while (iCurrentPair.hasNext() && (currentPair = iCurrentPair.next()).getWordIndexFromCorrectSentence() != this->wordIndexFromCorrectSentence);

    if (currentPair.getWordIndexFromCorrectSentence() == this->wordIndexFromCorrectSentence)
    {
        matchingPair = currentPair;
        return true;
    }

    return false;
}

bool Pair::findMatchingPair(const QList<Pair> &pairsSet, Pair &matchingPair) const
{
    QListIterator<Pair> iCurrentPair(pairsSet);
    Pair currentPair;

    while (iCurrentPair.hasNext() && (currentPair = iCurrentPair.next()).getWordIndexFromCorrectSentence() != this->wordIndexFromCorrectSentence);

    if (currentPair.getWordIndexFromCorrectSentence() == this->wordIndexFromCorrectSentence)
    {
        matchingPair = currentPair;
        return true;
    }

    return false;
}

bool Pair::areEqual(const Pair &pairToCompare, QString &pairsDifference) const
{
    Pair tmpPairToCompare = pairToCompare;
    pairsDifference = "";

    QList<int> tmpExpIndexesOfAuxiliariesInCorrect = this->getIndexesOfAuxiliariesInCorrect();
    QList<int> tmpRealIndexesOfAuxiliariesInCorrect = tmpPairToCompare.getIndexesOfAuxiliariesInCorrect();
    QMutableListIterator<int> iExpIndexOfAuxiliariesInCorrect(tmpExpIndexesOfAuxiliariesInCorrect);
    QMutableListIterator<int> iRealIndexOfAuxiliariesInCorrect(tmpRealIndexesOfAuxiliariesInCorrect);

    QList<int> tmpExpIndexesOfAuxiliariesInVerified = this->getIndexesOfAuxiliariesInVerified();
    QList<int> tmpRealIndexesOfAuxiliariesInVerified = tmpPairToCompare.getIndexesOfAuxiliariesInVerified();
    QMutableListIterator<int> iExpIndexOfAuxiliariesInVerified(tmpExpIndexesOfAuxiliariesInVerified);
    QMutableListIterator<int> iRealIndexOfAuxiliariesInVerified(tmpRealIndexesOfAuxiliariesInVerified);

    // Проверка индекса слова из правильного предложения
    if (this->wordIndexFromCorrectSentence != tmpPairToCompare.wordIndexFromCorrectSentence)
    {
        pairsDifference += " not matches word from correct sentence indexes. Expected: " +
                        QString::number(this->wordIndexFromCorrectSentence)
                        + ", real: " + QString::number(tmpPairToCompare.wordIndexFromCorrectSentence) + "; ";
    }

    // Проверка вспомогательных правильного предложения
    while (iExpIndexOfAuxiliariesInCorrect.hasNext())
    {
        if (!tmpRealIndexesOfAuxiliariesInCorrect.removeOne(iExpIndexOfAuxiliariesInCorrect.next()))
        {
            pairsDifference += " Not contain right auxiliary in correct sentence: " +
                            QString::number(iExpIndexOfAuxiliariesInCorrect.value()) + "; ";
        }
    }

    // Лишние вспомогательные из правильного предложения
    while (iRealIndexOfAuxiliariesInCorrect.hasNext())
    {
        pairsDifference += " Unexpected auxiliary in correct sentence: " +
                        QString::number(iRealIndexOfAuxiliariesInCorrect.next()) + "; ";
    }

    QString misstakeOfForm;

    // Проверка формы слова из правильного предложения
    if (!this->wordFormFromCorrectSentence.wordFormsAreEqual(tmpPairToCompare.wordFormFromCorrectSentence, misstakeOfForm))
    {
        pairsDifference += "Wrong form of correct Word: " + misstakeOfForm;
    }

    // Проверка индекса слова из проверяемого предложения
    if (this->wordIndexFromVerifiedSentence != tmpPairToCompare.wordIndexFromVerifiedSentence)
    {
        pairsDifference += " not matches word from verified sentence indexes. Expected: " +
                        QString::number(this->wordIndexFromVerifiedSentence)
                        + ", real: " + QString::number(tmpPairToCompare.wordIndexFromVerifiedSentence) + "; ";
    }

    // Проверка вспомогательных правильного предложения
    while (iExpIndexOfAuxiliariesInVerified.hasNext())
    {
        if (!tmpRealIndexesOfAuxiliariesInVerified.removeOne(iExpIndexOfAuxiliariesInVerified.next()))
        {
            pairsDifference += " Not contain right auxiliary in verified sentence: " +
                            QString::number(iExpIndexOfAuxiliariesInVerified.value()) + "; ";
        }
    }

    // Лишние вспомогательные из правильного предложения
    while (iRealIndexOfAuxiliariesInVerified.hasNext())
    {
        pairsDifference += " Unexpected auxiliary in verified sentence: " +
                        QString::number(iRealIndexOfAuxiliariesInVerified.next()) + "; ";
    }

    // Проверка формы слова из проверяемого предложения
    if (!this->wordFormFromCorrectSentence.wordFormsAreEqual(tmpPairToCompare.wordFormFromVerifiedSentence, misstakeOfForm))
    {
        pairsDifference += "Wrong form of verified Word: " + misstakeOfForm;
    }

    // Проверка pos-тега
    if (this->posTag != tmpPairToCompare.posTag)
    {
        pairsDifference += "Wrong pos tag. Expected: " + QString::number(this->getPosTag()) +
                           ", real: " + QString::number(tmpPairToCompare.getPosTag()) + "; ";
    }

    // Проверка ошибочности
    if (this->degreeOfFallacy != tmpPairToCompare.degreeOfFallacy)
    {
        pairsDifference += "Wrong pos tag. Expected: " + QString::number(this->degreeOfFallacy) +
                        ", real: " + QString::number(tmpPairToCompare.degreeOfFallacy) + "; ";
    }

    if (pairsDifference == "")
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Pair::operator==(const Pair &pairToCompare) const
{
    return (this->wordIndexFromCorrectSentence == pairToCompare.wordIndexFromCorrectSentence &&
            this->wordIndexFromVerifiedSentence == pairToCompare.wordIndexFromVerifiedSentence &&
            this->wordFormFromCorrectSentence == pairToCompare.wordFormFromCorrectSentence &&
            this->wordFormFromVerifiedSentence == pairToCompare.wordFormFromVerifiedSentence &&
            this->indexesOfAuxiliariesInCorrect == pairToCompare.indexesOfAuxiliariesInCorrect &&
            this->indexesOfAuxiliariesInVerified == pairToCompare.indexesOfAuxiliariesInVerified &&
            this->posTag == pairToCompare.posTag &&
            this->degreeOfFallacy == pairToCompare.degreeOfFallacy);
}

int Pair::pairMustBeInList(const Pair &other) const
{
    if (this->wordIndexFromCorrectSentence == other.wordIndexFromCorrectSentence &&
        this->wordIndexFromVerifiedSentence == other.wordIndexFromVerifiedSentence &&
        this->indexesOfAuxiliariesInCorrect == other.indexesOfAuxiliariesInCorrect &&
        this->indexesOfAuxiliariesInVerified == other.indexesOfAuxiliariesInVerified)
    {
        if (this->degreeOfFallacy < other.degreeOfFallacy)
        {
            return replaceItem;
        }
        else if  (this->degreeOfFallacy == other.degreeOfFallacy)
        {
            return addItem;
        }
        else
        {
            return skipItem;
        }
    }

    return pairsNotMatch;
}

QString Pair::getPairMisstakeMessage(const Sentence &correctSentence, const Sentence &verifiedSentence) const
{
    QString misstake;

    if (this->degreeOfFallacy != 0)
    {
        switch (this->getPosTag())
        {
            case verb: misstake = this->getVerbPairMisstake(correctSentence, verifiedSentence); break;
            case noun: misstake = this->getNounPairMisstake(correctSentence, verifiedSentence); break;
            case adj:  misstake = this->getAdjectivePairMisstake(correctSentence, verifiedSentence); break;
            case num:  misstake = this->getNumeralPairMisstake(correctSentence, verifiedSentence); break;
            case pron: misstake = this->getPronounPairMisstake(correctSentence, verifiedSentence); break;
        }
    }

    return misstake;
}

QString Pair::getVerbPairMisstake(const Sentence &correctSentence, const Sentence &verifiedSentence) const
{
    QString misstake;

    QString allWordsInCorrect, allWordsInVerified;

    // Собираем слова, относящиеся к данному глаголу в правильном предложении, для вывода
    // Вспомогательные
    for (int currentIndex: this->indexesOfAuxiliariesInCorrect)
    {
        if (currentIndex < correctSentence.getSentence().length())
        {
            allWordsInCorrect += (correctSentence.getSentence().value(currentIndex)->getWord()) += " ";
        }
    }

    // Главное слово
    allWordsInCorrect += correctSentence.getSentence().value(this->wordIndexFromCorrectSentence)->getWord();

    // Собираем слова, относящиеся к данному глаголу в проверяемом предложении, для вывода
    // Вспомогательных
    for (int currentIndex: this->indexesOfAuxiliariesInVerified)
    {
        if (currentIndex < verifiedSentence.getSentence().length())
        {
            allWordsInVerified += (verifiedSentence.getSentence().value(currentIndex)->getWord()) += " ";
        }
    }

    // Главное слово
    allWordsInVerified += verifiedSentence.getSentence().value(this->wordIndexFromVerifiedSentence)->getWord();

    if (this->wordFormFromCorrectSentence.getFirstForm() != this->wordFormFromVerifiedSentence.getFirstForm())
    {
        misstake += (this->getIndexesOfAuxiliariesInCorrectByStr() + QString::number(this->wordIndexFromCorrectSentence) + " - " +
                    this->getIndexesOfAuxiliariesInVerifiedByStr() + QString::number(this->wordIndexFromVerifiedSentence) + ": " +
                    "Неверно употреблен глагол \"" + allWordsInVerified +
                    "\" (" + this->wordFormFromVerifiedSentence.getFirstFormToDisplay() + "), верная форма - " +
                    allWordsInCorrect + " (" + this->wordFormFromCorrectSentence.getFirstFormToDisplay() + ")\n");
    }

    if (this->wordFormFromCorrectSentence.getSecondForm() != this->wordFormFromVerifiedSentence.getSecondForm())
    {
        misstake += (this->getIndexesOfAuxiliariesInCorrectByStr() + QString::number(this->wordIndexFromCorrectSentence) + " - " +
                    this->getIndexesOfAuxiliariesInVerifiedByStr() + QString::number(this->wordIndexFromVerifiedSentence) + ": " +
                    "Неверно употреблено лицо глагола \"" + allWordsInVerified +
                    "\": Вместо " + this->wordFormFromVerifiedSentence.getSecondFormToDisplay() + ", употреблена форма - " + allWordsInCorrect +
                    " (" + this->wordFormFromCorrectSentence.getSecondFormToDisplay() + ")\n");
    }

    return misstake;
}

QString Pair::getAdjectivePairMisstake(const Sentence &correctSentence, const Sentence &verifiedSentence) const
{
    QString misstake;

    QString allWordsInCorrect, allWordsInVerified;

    // Собираем слова, относящиеся к данному глаголу в правильном предложении, для вывода
    // Вспомогательные
    for (int currentIndex: this->indexesOfAuxiliariesInCorrect)
    {
        if (currentIndex < correctSentence.getSentence().length())
        {
            allWordsInCorrect += (correctSentence.getSentence().value(currentIndex)->getWord()) += " ";
        }
    }

    // Главное слово
    allWordsInCorrect += correctSentence.getSentence().value(this->wordIndexFromCorrectSentence)->getWord();

    // Собираем слова, относящиеся к данному глаголу в проверяемом предложении, для вывода
    // Вспомогательные
    for (int currentIndex: this->indexesOfAuxiliariesInVerified)
    {
        if (currentIndex < verifiedSentence.getSentence().length())
        {
            allWordsInVerified.append(verifiedSentence.getSentence().value(currentIndex)->getWord());
        }
    }

    // Главное слово
    allWordsInVerified += verifiedSentence.getSentence().value(this->wordIndexFromVerifiedSentence)->getWord();

    if (this->wordFormFromCorrectSentence.getFirstForm() != this->wordFormFromVerifiedSentence.getFirstForm())
    {
        misstake += (this->getIndexesOfAuxiliariesInCorrectByStr() + QString::number(this->wordIndexFromCorrectSentence) + " - " +
                    this->getIndexesOfAuxiliariesInVerifiedByStr() + QString::number(this->wordIndexFromVerifiedSentence) + ": " +
                    "Неверно употреблено прилагательное \"" + allWordsInVerified +
                    "\" " + this->wordFormFromVerifiedSentence.getFirstFormToDisplay() + ", верная форма - " +
                    this->wordFormFromCorrectSentence.getFirstFormToDisplay() + " \"" +  allWordsInCorrect + "\"\n");
    }

    return misstake;
}

QString Pair::getPronounPairMisstake(const Sentence &correctSentence, const Sentence &verifiedSentence) const
{
    QString misstake;

    if (this->wordFormFromCorrectSentence.getFirstForm() != this->wordFormFromVerifiedSentence.getFirstForm())
    {
        misstake += (QString::number(this->wordIndexFromCorrectSentence) + " - " +
                    QString::number(this->wordIndexFromVerifiedSentence) + ": " +
                    "Неверный падеж местоимения \"" + verifiedSentence.getSentence().value(this->wordIndexFromVerifiedSentence)->getWord() +
                    "\" вместо " + this->wordFormFromVerifiedSentence.getFirstFormToDisplay() + " использована форма " + this->wordFormFromCorrectSentence.getFirstFormToDisplay() +
                    " \"" +  correctSentence.getSentence().value(this->wordIndexFromCorrectSentence)->getWord() + "\"\n");
    }

    if (this->wordFormFromCorrectSentence.getSecondForm() != this->wordFormFromVerifiedSentence.getSecondForm() &&
        this->wordFormFromCorrectSentence.getFirstForm() == this->wordFormFromVerifiedSentence.getFirstForm())
    {
        misstake += (QString::number(this->wordIndexFromCorrectSentence) + " - " +
                    QString::number(this->wordIndexFromVerifiedSentence) + ": " +
                    "Неверная форма местоимения \"" + verifiedSentence.getSentence().value(this->wordIndexFromVerifiedSentence)->getWord() +
                    "\" вместо " + this->wordFormFromVerifiedSentence.getSecondFormToDisplay() + " использована форма " + this->wordFormFromCorrectSentence.getSecondFormToDisplay() +
                    " \"" +  correctSentence.getSentence().value(this->wordIndexFromCorrectSentence)->getWord() + "\"\n");
    }

    return misstake;
}

QString Pair::getNounPairMisstake(const Sentence &correctSentence, const Sentence &verifiedSentence) const
{
    QString misstake;

    if (this->wordFormFromCorrectSentence.getFirstForm() != this->wordFormFromVerifiedSentence.getFirstForm())
    {
        misstake += (QString::number(this->wordIndexFromCorrectSentence) + " - " +
                    QString::number(this->wordIndexFromVerifiedSentence) + ": " +
                    "Неверное число существительного. Вместо формы " + this->wordFormFromCorrectSentence.getFirstFormToDisplay() +
                    " слова \"" + correctSentence.getSentence().value(this->wordIndexFromCorrectSentence)->getWord() + "\" использована форма " +
                    this->wordFormFromVerifiedSentence.getFirstFormToDisplay() + " \"" +
                    verifiedSentence.getSentence().value(this->wordIndexFromVerifiedSentence)->getWord() + "\"\n");
    }

    if (this->wordFormFromCorrectSentence.getSecondForm() != this->wordFormFromVerifiedSentence.getSecondForm())
    {
        misstake += (QString::number(this->wordIndexFromCorrectSentence) + " - " +
                    QString::number(this->wordIndexFromVerifiedSentence) + ": " +
                    "Неверный падеж существительного \"" + verifiedSentence.getSentence().value(this->wordIndexFromVerifiedSentence)->getWord() +
                    "\": вместо " + this->wordFormFromCorrectSentence.getSecondFormToDisplay() + " \"" +
                     correctSentence.getSentence().value(this->wordIndexFromCorrectSentence)->getWord() +
                     "\" использована форма " + this->wordFormFromVerifiedSentence.getSecondFormToDisplay() +
                     "\n");
    }

    return misstake;
}

QString Pair::getNumeralPairMisstake(const Sentence &correctSentence, const Sentence &verifiedSentence) const
{
    QString misstake;

    if (this->wordFormFromCorrectSentence.getFirstForm() != this->wordFormFromVerifiedSentence.getFirstForm())
    {
        misstake += (QString::number(this->wordIndexFromCorrectSentence) + " - " +
                    QString::number(this->wordIndexFromVerifiedSentence) + ": " +
                    "Неверно употреблено " + this->wordFormFromVerifiedSentence.getFirstFormToDisplay() + " числительное \"" +
                    verifiedSentence.getSentence().value(this->wordIndexFromVerifiedSentence)->getWord() +
                    "\", верная форма - " + this->wordFormFromCorrectSentence.getFirstFormToDisplay() +
                    " числительное \"" +  correctSentence.getSentence().value(this->wordIndexFromCorrectSentence)->getWord() + "\"\n");
    }

    return misstake;
}
