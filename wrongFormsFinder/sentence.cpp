#include "sentence.h"
#include "inputdataerror.cpp"

/// Pos-теги, обрабатываемые программой
static QStringList validPosTags = {"adj", "adp", "adv", "aux", "cconj", "det", "intj",
                                   "noun", "num", "part", "pron", "propn",
                                    "sconj", "sym", "verb", "x"};

static QStringList verbAuxiliaries = {"do", "does", "am", "is", "are",
                                      "was", "were", "have", "has", "been", "be",
                                      "had", "will", "shall", "would", "should"};

static QStringList presentSimpleAux = {};
static QStringList presentSimpleInterrogativeAux = {"do"};
static QStringList presentSimpleInterrogativeThirdPersonAux = {"does"};
static QStringList presentContinousAux = {"are"};
static QStringList presentContinousThirdPersonAux = {"is"};
static QStringList presentContinousFirstPersonAux = {"am"};
static QStringList pastSimpleAux = {};
static QStringList pastContinuousSingularAux = {"was"};
static QStringList pastContinuousPluralAux = {"were"};
static QStringList presentPerfectAux = {"have"};
static QStringList presentPerfectThirdPersonAux = {"has"};
static QStringList presentPerfectContinuousAux = {"have", "been"};
static QStringList presentPerfectContinuousThirdPersonAux = {"has", "been"};
static QStringList pastPerfectAux = {"had"};
static QStringList pastPerfectContinuousAux = {"had", "been"};
static QStringList futureSimpleAux = {"will"};
static QStringList futureSimpleFirstPersonAux = {"shall"};
static QStringList futureContinuousAux = {"will", "be"};
static QStringList futureContinuousFirstPersonAux = {"shall", "be"};
static QStringList futurePerfectSimpleAux = {"will", "have"};
static QStringList futurePerfectSimpleFirstPersonAux = {"shall", "have"};
static QStringList futurePerfectContinuousAux = {"will", "have", "been"};
static QStringList futurePerfectContinuousFirstPersonAux = {"shall", "have", "been"};
static QStringList futureSimpleInThePastAux = {"would"};
static QStringList futureSimpleInThePastFirstPersonAux = {"should"};
static QStringList futureContinuousInThePastAux = {"would", "be"};
static QStringList futureContinuousInThePastFirstPersonAux = {"should", "be"};
static QStringList futurePerfectInThePastAux = {"would", "have"};
static QStringList futurePerfectInThePastFirstPersonAux = {"should", "have"};
static QStringList futurePerfectContinuousInThePastAux = {"would", "have", "been"};
static QStringList futurePerfectContinuousInThePastFirstPersonAux = {"should", "have", "been"};

void Sentence::setSentence(const QList<Word*> &newSentence)
{
    sentence = newSentence;
}

Sentence::Sentence()
{
    ;
}

QList<Word*> Sentence::getSentence() const
{
    return this->sentence;
}

QString formSeparators(QString string) {
    QString separators = "";
    for (int i = 0; i < string.length(); ++i) {
        if ( !string[i].isDigit() && !string[i].isLetter() && string[i] != QString("'")) {
            separators.append(string[i]);
        }
    }

    return separators;
}

void Sentence::parseSentence(const QString &notParsedSentence)
{
    // приводим строку к нижнему регистру
    QString notParsedSentenceInLower = notParsedSentence.toLower();

    notParsedSentenceInLower.append(" ");

    // формируем массив с разделителями
    QString separators = formSeparators(notParsedSentenceInLower);

    // разделяем строку по разделителям в ней
    QStringList list = notParsedSentenceInLower.split(QRegularExpression("[" + separators + "]+"));

    // создаем массив, где будут находится только корректные подпоследовательности
    QStringList newList;
    for (int i = 0; i < list.length(); ++i) {
        // если подпоследовательность имеет меньше 2 апострофов, то добавляем ее полностью
        if (list[i].count("'") < 2) {
            newList.push_back(list[i]);
        }
        else if (list[i].count("'") >= 2){
            int index = list[i].indexOf("'", list[i].indexOf("'") + 1);

            newList.push_back(list[i].left(index));
        }
        // если подпоследовательность имеет 2 и более подряд идущих апострофа, то обрезаем строку от начала до первого найденного двойного апострофа
        else if (list[i].contains(QRegularExpression("'[']+")) ) {
            int index = list[i].indexOf("''");
            newList.push_back(list[i].left(index + 1));
        }
    }

    QStringList returnString;

    for (int i = 0; i < newList.length(); ++i) {
        if (newList[i] != "") {
            returnString.push_back(newList[i]);
        }
    }

    QList<Word*> newSentence;

    for (QString currentWord: returnString)
    {
        newSentence << new Word(currentWord);
    }

    this->sentence = newSentence;
}

void Sentence::addWordToEnd(Word* newWord)
{
    this->sentence.append(newWord);
}

void Sentence::clear()
{
    this->sentence.clear();
}

InputDataError Sentence::connectSentenceAndPosTags(const Sentence &posTagsSentence)
{
    InputDataError errorOfInput;
    QList<Word*> sentenceByTags;

    if (this->sentence.count() == 0)
    {
        errorOfInput.setParameters(zeroWordsInSentence, this->sentence.count(), posTagsSentence.sentence.count(), "");
        return errorOfInput;
    }

    if (this->sentence.count() < posTagsSentence.sentence.count())
    {
        errorOfInput.setParameters(fewerWordsThanTags, this->sentence.count(), posTagsSentence.sentence.count(), "");
        return errorOfInput;
    }
    else if (this->sentence.count() > posTagsSentence.sentence.count())
    {
        errorOfInput.setParameters(fewerTagsThanWords, this->sentence.count(), posTagsSentence.sentence.count(), "");
        return errorOfInput;
    }

    QMutableListIterator<Word*> iWordsIterator(this->sentence);
    QListIterator<Word*> iPosTagsIterator(posTagsSentence.getSentence());

    while (iWordsIterator.hasNext())
    {
        iWordsIterator.next();

        QString currentTag = iPosTagsIterator.next()->getWord();

        if (currentTag == "adj")
        {
            sentenceByTags.append(new Adjective(iWordsIterator.value()->getWord(), iWordsIterator.value()->getPossibleFormsOfWord(), -1));
        }
        else if (currentTag == "noun")
        {
            sentenceByTags.append(new Noun(iWordsIterator.value()->getWord(), iWordsIterator.value()->getPossibleFormsOfWord()));
        }
        else if (currentTag == "num")
        {
            sentenceByTags.append(new Numeral(iWordsIterator.value()->getWord(), iWordsIterator.value()->getPossibleFormsOfWord()));
        }
        else if (currentTag == "pron")
        {
            sentenceByTags.append(new Pronoun(iWordsIterator.value()->getWord(), iWordsIterator.value()->getPossibleFormsOfWord()));
        }
        else if (currentTag == "verb")
        {
            sentenceByTags.append(new Verb(iWordsIterator.value()->getWord(), iWordsIterator.value()->getPossibleFormsOfWord(), QList<int> ()));
        }
        else if (currentTag == "aux")
        {
            sentenceByTags.append(new Auxiliary(iWordsIterator.value()->getWord(), iWordsIterator.value()->getPossibleFormsOfWord()));
        }
        else if (!validPosTags.contains(currentTag))
        {
            errorOfInput.setParameters(incorrectPosTag, this->sentence.count(), posTagsSentence.sentence.count(), currentTag);
            return errorOfInput;
        }
        else
        {
            sentenceByTags.append(new Word(iWordsIterator.value()->getWord(), iWordsIterator.value()->getPossibleFormsOfWord()));
        }
    }

    errorOfInput.setParameters(sentenceSuccessfulProcessed, this->sentence.count(), posTagsSentence.sentence.count(), "");
    this->sentence = sentenceByTags;
    return errorOfInput;
}

void Sentence::setFormsInCorrectSentence()
{
    //...Считать, что индекс предыдущего глагола 0
    int lastVerbIndex = 0, i = 0;
    QSet<WordForm> correctForms;

    for (Word* currentWord: this->sentence)
    { // Для каждого слова с тегами adj, noun, pron, num или verb
        correctForms.clear();

        // По написанию слова определить его возможные формы
        currentWord->setPossibleFormsOfWord(currentWord->definePossibleForms());

        // Если текущий тег verb
        if (typeid(*currentWord) == typeid(Verb))
        {
            Verb *currentVerb = dynamic_cast<Verb*>(currentWord);
            // Между предыдущим глаголом и текущим найти все Auxiliary для глаголов
            // Добавить вспомогательные к глаголу
            currentVerb->setIndexesOfAuxiliaries(this->findAllVerbAuxiliaries(lastVerbIndex, i));

            // Для каждой возможной формы глагола
            for (WordForm currentForm: currentVerb->getPossibleFormsOfWord())
            {   // Если данная форма глагола дает в сочетании с вспомогательными какое-либо время
                WordForm currentTense = this->defineTense(currentForm, currentVerb->getIndexesOfAuxiliaries());
                if (currentTense.getFirstForm() != undefined)
                {
                    // Добавить данную форму к слову в предложении
                    correctForms << currentTense;
                }
            }

            if (correctForms.isEmpty())
            {
                correctForms << WordForm(undefined, notSet, notSet, notSet);
            }

            lastVerbIndex = i;
        }
        else if (typeid(*currentWord) == typeid(Adjective)) // ИначеЕсли текущий тег adj
        {
            QString auxLeftFromAdj;
            // Определить вспомогательное слово, находящееся слева от прилагательного
            if (i < this->sentence.length() && i > 0 && typeid(*(this->sentence[i - 1])) == typeid(Auxiliary))
            {
                auxLeftFromAdj = this->sentence[i - 1]->getWord();
            }

            Adjective *currentAdjective = dynamic_cast<Adjective*>(currentWord);

            // Для каждой возможной формы прилагательного
            for (WordForm currentForm: currentAdjective->getPossibleFormsOfWord())
            {
                // Если текущей форме требуется more
                if (auxLeftFromAdj == "more" && currentForm.getAuxForAdj() == more)
                {
                    if (auxLeftFromAdj == "more")
                    { // Если вспомогательное more
                        // Добавить вспомогательное к прилагательному и добавить к нему данную форму слова
                        currentAdjective->setIndexOfAuxiliary(i - 1);

                        correctForms << currentForm;
                    }
                }
                else if (auxLeftFromAdj == "most" && currentForm.getAuxForAdj() == most)
                { // ИначеЕсли текущей форме требуется most и вспомогательное most
                    // Добавить вспомогательное к прилагательному и добавить к нему данную форму слова
                    currentAdjective->setIndexOfAuxiliary(i - 1);

                    correctForms << currentForm;
                }
                else if (auxLeftFromAdj == "" && currentForm.getAuxForAdj() == notNeed)// Иначе
                { // Добавляем текущую форму без вспомогательных
                    correctForms << currentForm;
                }
            }
        }
        else //Иначе
        {
            // Добавить все формы к слову в предложении
            correctForms = currentWord->definePossibleForms();
        }

        currentWord->setPossibleFormsOfWord(correctForms);

        i++;
    }
}

WordForm Sentence::defineTense(const WordForm &currentVerbForm,
                                   const QList<int> &indexesOfAuxiliaries) const
{
    QStringList allAuxiliaries;

    for (int currentIndex: indexesOfAuxiliaries)
    {
        if (currentIndex < this->sentence.length() &&
            this->sentence[currentIndex]->getWord() != "not")
        {
            allAuxiliaries.append(this->sentence[currentIndex]->getWord());
        }
    }

    unsigned int formOfVerb = currentVerbForm.getThirdForm();

    if (formOfVerb == infinitive && // Проверка на Present Simple
         (allAuxiliaries == presentSimpleAux ||
          allAuxiliaries == presentSimpleInterrogativeAux ||
          allAuxiliaries == presentSimpleInterrogativeThirdPersonAux))
    {
        if (allAuxiliaries == presentSimpleInterrogativeThirdPersonAux)
        {
            return WordForm(presentSimple, third, currentVerbForm.getThirdForm(), currentVerbForm.getAuxForAdj());
        }

        return WordForm(presentSimple, currentVerbForm.getSecondForm(), currentVerbForm.getThirdForm(), currentVerbForm.getAuxForAdj());
    }
    else if (formOfVerb == presentParticiple && // Проверка на Present Continuous
            (allAuxiliaries == presentContinousAux ||
             allAuxiliaries == presentContinousThirdPersonAux ||
             allAuxiliaries == presentContinousFirstPersonAux))
    {
        if (allAuxiliaries == presentContinousFirstPersonAux)
        {
            return WordForm(presentCont, first, currentVerbForm.getThirdForm(), currentVerbForm.getAuxForAdj());
        }
        else if (allAuxiliaries == presentContinousThirdPersonAux)
        {
            return WordForm(presentCont, third, currentVerbForm.getThirdForm(), currentVerbForm.getAuxForAdj());
        }

        return WordForm(presentCont, currentVerbForm.getSecondForm(), currentVerbForm.getThirdForm(), currentVerbForm.getAuxForAdj());
    }
    else if ((formOfVerb == past || // Проверка на Past Simple
              formOfVerb == preterite) &&
             allAuxiliaries == pastSimpleAux)
    {
        return WordForm(pastSimple, currentVerbForm.getSecondForm(), currentVerbForm.getThirdForm(), currentVerbForm.getAuxForAdj());
    }
    else if (formOfVerb == presentParticiple && // Проверка на Past Continuous
             (allAuxiliaries == pastContinuousSingularAux ||
              allAuxiliaries == pastContinuousPluralAux))
    {
        return WordForm(pastCont, currentVerbForm.getSecondForm(), currentVerbForm.getThirdForm(), currentVerbForm.getAuxForAdj());
    }
    else if ((formOfVerb == past || // Проверка на Present Perfect
              formOfVerb == pastParticiple) &&
             (allAuxiliaries == presentPerfectAux ||
              allAuxiliaries == presentPerfectThirdPersonAux))
    {
        if (allAuxiliaries == presentPerfectThirdPersonAux)
        {
            return WordForm(presentPerf, third, currentVerbForm.getThirdForm(), currentVerbForm.getAuxForAdj());
        }

        return WordForm(presentPerf, currentVerbForm.getSecondForm(), currentVerbForm.getThirdForm(), currentVerbForm.getAuxForAdj());
    }
    else if (formOfVerb == presentParticiple && // Проверка на Present Perfect Continuous
               (allAuxiliaries == presentPerfectContinuousAux ||
                allAuxiliaries == presentPerfectContinuousThirdPersonAux))
    {
        if (allAuxiliaries == presentPerfectContinuousThirdPersonAux)
        {
            return WordForm(presentPerfCont, third, currentVerbForm.getThirdForm(), currentVerbForm.getAuxForAdj());
        }

        return WordForm(presentPerfCont, currentVerbForm.getSecondForm(), currentVerbForm.getThirdForm(), currentVerbForm.getAuxForAdj());
    }
    else if ((formOfVerb == past || // Проверка на Past Perfect
              formOfVerb == pastParticiple) &&
             allAuxiliaries == pastPerfectAux)
    {
        return WordForm(pastPerf, currentVerbForm.getSecondForm(), currentVerbForm.getThirdForm(), currentVerbForm.getAuxForAdj());
    }
    else if (formOfVerb == presentParticiple && // Проверка на Present Perfect Continuous
             allAuxiliaries == pastPerfectContinuousAux)
    {
        return WordForm(pastPerfCont, currentVerbForm.getSecondForm(), currentVerbForm.getThirdForm(), currentVerbForm.getAuxForAdj());
    }
    else if (formOfVerb == infinitive && // Проверка на Future Simple
             (allAuxiliaries == futureSimpleAux ||
              allAuxiliaries == futureSimpleFirstPersonAux))
    {
        if (allAuxiliaries == futureSimpleFirstPersonAux)
        {
            return WordForm(futureSimple, first, currentVerbForm.getThirdForm(), currentVerbForm.getAuxForAdj());
        }

        return WordForm(futureSimple, currentVerbForm.getSecondForm(), currentVerbForm.getThirdForm(), currentVerbForm.getAuxForAdj());
    }
    else if (formOfVerb == presentParticiple && // Проверка на Future Continuous
            (allAuxiliaries == futureContinuousAux ||
             allAuxiliaries == futureContinuousFirstPersonAux))
    {
        if (allAuxiliaries == futureContinuousFirstPersonAux)
        {
            return WordForm(futureCont, first, currentVerbForm.getThirdForm(), currentVerbForm.getAuxForAdj());
        }

        return WordForm(futureCont, currentVerbForm.getSecondForm(), currentVerbForm.getThirdForm(), currentVerbForm.getAuxForAdj());
    }
    else if ((formOfVerb == past || // Проверка на Future Perfect Simple
              formOfVerb == pastParticiple) &&
             (allAuxiliaries == futurePerfectSimpleAux ||
              allAuxiliaries == futurePerfectSimpleFirstPersonAux))
    {
        if (allAuxiliaries == futurePerfectSimpleFirstPersonAux)
        {
            return WordForm(futurePerfSimple, first, currentVerbForm.getThirdForm(), currentVerbForm.getAuxForAdj());
        }

        return WordForm(futurePerfSimple, currentVerbForm.getSecondForm(), currentVerbForm.getThirdForm(), currentVerbForm.getAuxForAdj());
    }
    else if (formOfVerb == presentParticiple && // Проверка на Future Perfect Continuous
             (allAuxiliaries == futurePerfectContinuousAux ||
              allAuxiliaries == futurePerfectContinuousFirstPersonAux))
    {
        if (allAuxiliaries == futurePerfectContinuousFirstPersonAux)
        {
            return WordForm(futurePerfCont, first, currentVerbForm.getThirdForm(), currentVerbForm.getAuxForAdj());
        }

        return WordForm(futurePerfCont, currentVerbForm.getSecondForm(), currentVerbForm.getThirdForm(), currentVerbForm.getAuxForAdj());
    }
    else if (formOfVerb == infinitive  && // Проверка на Future Simple In The Past
             (allAuxiliaries == futureSimpleInThePastAux ||
              allAuxiliaries == futureSimpleInThePastFirstPersonAux))
    {
        if (allAuxiliaries == futureSimpleInThePastFirstPersonAux)
        {
            return WordForm(futureSimpleInThePast, first, currentVerbForm.getThirdForm(), currentVerbForm.getAuxForAdj());
        }

        return WordForm(futureSimpleInThePast, currentVerbForm.getSecondForm(), currentVerbForm.getThirdForm(), currentVerbForm.getAuxForAdj());
    }
    else if (formOfVerb == presentParticiple && // Проверка на Future Continuous In The Past
            (allAuxiliaries == futureContinuousInThePastAux ||
             allAuxiliaries == futureContinuousInThePastFirstPersonAux))
    {
        if (allAuxiliaries == futureContinuousInThePastFirstPersonAux)
        {
            return WordForm(futureContInThePast, first, currentVerbForm.getThirdForm(), currentVerbForm.getAuxForAdj());
        }

        return WordForm(futureContInThePast, currentVerbForm.getSecondForm(), currentVerbForm.getThirdForm(), currentVerbForm.getAuxForAdj());

    }
    else if ((formOfVerb == past || // Проверка на Future Perfect In The Past
              formOfVerb == pastParticiple) &&
            (allAuxiliaries == futurePerfectInThePastAux ||
             allAuxiliaries == futurePerfectInThePastFirstPersonAux))
    {
        if (allAuxiliaries == futurePerfectInThePastFirstPersonAux)
        {
            return WordForm(futurePerfInThePast, first, currentVerbForm.getThirdForm(), currentVerbForm.getAuxForAdj());
        }

        return WordForm(futurePerfInThePast, currentVerbForm.getSecondForm(), currentVerbForm.getThirdForm(), currentVerbForm.getAuxForAdj());
    }
    else if (formOfVerb == presentParticiple && // Проверка на Future Perfect Continuous In The Past
             (allAuxiliaries == futurePerfectContinuousInThePastAux ||
              allAuxiliaries == futurePerfectContinuousInThePastFirstPersonAux))
    {
        if (allAuxiliaries == futurePerfectContinuousInThePastFirstPersonAux)
        {
            return WordForm(futurePerfContInThePast, first, currentVerbForm.getThirdForm(), currentVerbForm.getAuxForAdj());
        }

        return WordForm(futurePerfContInThePast, currentVerbForm.getSecondForm(), currentVerbForm.getThirdForm(), currentVerbForm.getAuxForAdj());
    }

    // Если форма не определена
    return WordForm(undefined, currentVerbForm.getSecondForm(), currentVerbForm.getThirdForm(), currentVerbForm.getAuxForAdj());
}

QList<int> Sentence::findAllVerbAuxiliaries(const unsigned int &startPos, const unsigned int &endPos) const
{
    unsigned int correctEndPos = endPos;
    QList<int> auxIndexes;

    if (endPos >= this->sentence.length())
    {
        correctEndPos = this->sentence.length() - 1;
    }

    if (startPos > correctEndPos)
    {
        return auxIndexes;
    }

    for (unsigned int currentIndex = startPos; currentIndex < correctEndPos; currentIndex++)
    {
        if ((typeid(*(this->sentence[currentIndex])) == typeid(Auxiliary)) && verbAuxiliaries.contains(this->sentence[currentIndex]->getWord()))
        {
            auxIndexes << currentIndex;
        }
    }

    // Собираем частицу not
    if (!auxIndexes.isEmpty() && auxIndexes.first() < correctEndPos)
    {
        if ((typeid(*(this->sentence[auxIndexes.first() + 1])) == typeid(Word)) && this->sentence[auxIndexes.first() + 1]->getWord() == "not")
        {
            auxIndexes.insert(1, auxIndexes.first() + 1);
        }
    }

    return auxIndexes;
}

bool Sentence::canExtendToTense(const QList<int> &auxiliaries) const
{
    // Проверяем, что индексы корректны
    for (int currentIndex: auxiliaries)
    {
        if (currentIndex >= this->sentence.length())
        {
            return false;
        }
    }

    bool canExtend = false;

    Verb toReadLexems;
    QMutableStringListIterator iCurrentLine(toReadLexems.verbLexems);

    while (iCurrentLine.hasNext() && !canExtend)
    { // Пока не дошли до конца файла
        QString line = iCurrentLine.next(); // Считываем строку из файла

        // Делим считанную строку на части, в качестве разделителя - запятые
        QStringList data = line.split(",");

        QListIterator<QString> iData(data);
        QListIterator<int> iAuxiliary(auxiliaries);

        bool match = true;

        iData.toBack();
        iAuxiliary.toBack();
        while (iData.hasPrevious() && iAuxiliary.hasPrevious() && match)
        {
            if (iData.previous() != this->sentence[iAuxiliary.previous()]->getWord())
            {
                match = false;
            }
        }

        if (match == true && iData.hasPrevious())
        {
            canExtend = true;
        }
    }

    return canExtend;
}

QSet<Word*> Sentence::setFormInVerifiedSentence(const int &indexOfProcessingWord,
                                                const QSet<WordForm> &formsOfProcessingWord,
                                                const posTags &tagOfProcessingWord) const
{
    QSet<Word*> allForms;
    QString processingWord = this->sentence[indexOfProcessingWord]->getWord();
    int indexOfCurrentWord = indexOfProcessingWord;

    if (indexOfProcessingWord >= this->sentence.length())
    {
        return QSet<Word*> ();
    }

    //Если текущий pos-тег - verb
    if (tagOfProcessingWord == verb)
    {
        QList<int> indexesOfAux;

        // Если данные формы глагола без вспомогательных составляют время
        for (WordForm currentForm: formsOfProcessingWord)
        {
            WordForm tense = this->defineTense(currentForm, indexesOfAux);
            // Добавить глагол с указанием времени к решению
            if (tense.getFirstForm() != undefined)
            {
                QSet<WordForm> formsOfTense;
                formsOfTense << tense;
                allForms << new Verb(processingWord, formsOfTense, indexesOfAux);
            }
        }

        // Для каждого слова, находящегося слева от глагола и пока текущий набор можно расширить до какого-либо времени
        while (indexOfCurrentWord > 0 && this->canExtendToTense(indexesOfAux))
        { // Если данное слово - вспомогательное для глагола
            if (verbAuxiliaries.contains(this->sentence[indexOfCurrentWord - 1]->getWord()))
            {
                //Добавить данное слово к списку вспомогательных
                indexesOfAux.prepend(indexOfCurrentWord - 1);

                //Если справа от него not
                if (this->sentence[indexOfCurrentWord]->getWord() == "not")
                {
                    // Добавить not к списку
                    indexesOfAux.insert(1, indexOfCurrentWord);
                }

                //Для каждой формы глагола
                for (WordForm currentForm: formsOfProcessingWord)
                {
                    WordForm tense = this->defineTense(currentForm, indexesOfAux);
                    // Добавить глагол с указанием времени к решению
                    if (tense.getFirstForm() != undefined)
                    {
                        QSet<WordForm> formsOfTense;
                        formsOfTense << tense;
                        allForms << new Verb(processingWord, formsOfTense, indexesOfAux);
                    }
                }

                //Если вторым в списке not - удалить его
                if (indexesOfAux.length() >= 2 && this->sentence[indexesOfAux[1]]->getWord() == "not")
                {
                    indexesOfAux.removeAt(1);
                }
            }

            indexOfCurrentWord--;
        }

        // Если не найдено ни одного решения
        if (allForms.empty())
        {
            // Добавить к решениям глагол без вспомогательных с указанием времени undefined
            QSet<WordForm> formsOfTense;
            formsOfTense << WordForm(undefined, notSet, notSet, notSet);
            allForms << new Verb(processingWord, formsOfTense, QList<int> ());
        }
    }
    else if (tagOfProcessingWord == adj) //ИначеЕсли текущий тег - adj
    {
        QSet<WordForm> formsOfAdjective;

        // Для каждой формы
        for (WordForm currentForm: formsOfProcessingWord)
        {
            if (currentForm.getAuxForAdj() == more)
            { // Если данной форме требуется вспомогательное more
                if (indexOfProcessingWord - 1 >= 0 &&
                    this->sentence[indexOfCurrentWord - 1]->getWord() == "more")
                { // Если more есть слева от прилагательного
                    // Добавить more и прилагательное к решению
                    formsOfAdjective << currentForm;
                    allForms << new Adjective(processingWord, formsOfAdjective, indexOfCurrentWord - 1);
                }
            }
            else if (currentForm.getAuxForAdj() == most)
            { // ИначеЕсли данной форме требуется вспомогательное most
                if (indexOfProcessingWord - 1 >= 0 &&
                     this->sentence[indexOfCurrentWord - 1]->getWord() == "most")
                { // Если most есть слева от прилагательного
                    // Добавить most и прилагательное к решению
                    formsOfAdjective << currentForm;
                    allForms << new Adjective(processingWord, formsOfAdjective, indexOfCurrentWord - 1);
                }
            }
            else // Иначе
            { // Добавить данную форму к решению
                formsOfAdjective << currentForm;
                allForms << new Adjective(processingWord, formsOfAdjective, -1);
            }

            formsOfAdjective.clear();
        }

        if (allForms.empty())
        {
            formsOfAdjective << WordForm(undefined, notSet, notSet, notSet);
            allForms << new Adjective(processingWord, formsOfAdjective, -1);
        }
    }
    else if (tagOfProcessingWord == aux)
    {
        for (WordForm currentForm: formsOfProcessingWord)
        {
            QSet<WordForm> currentForms;
            currentForms << currentForm;
            allForms << new Auxiliary(processingWord, currentForms);
        }
    }
    else if (tagOfProcessingWord == noun)
    {
        for (WordForm currentForm: formsOfProcessingWord)
        {
            QSet<WordForm> currentForms;
            currentForms << currentForm;
            allForms << new Noun(processingWord, currentForms);
        }
    }
    else if (tagOfProcessingWord == pron)
    {
        for (WordForm currentForm: formsOfProcessingWord)
        {
            QSet<WordForm> currentForms;
            currentForms << currentForm;
            allForms << new Pronoun(processingWord, currentForms);
        }
    }
    else
    {
        for (WordForm currentForm: formsOfProcessingWord)
        {
            QSet<WordForm> currentForms;
            currentForms << currentForm;
            allForms << new Word(processingWord, currentForms);
        }
    }

    return allForms;
}
