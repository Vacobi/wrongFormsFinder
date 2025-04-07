#include "adjective.h"

static QStringList adjectiveIbjectiveForm = {"good", "bad", "much", "far", "less", "little", "many", "well"};
static QStringList adjectiveComparative = {"better", "worse", "more", "further", "lesser", "less", "more", "better"};
static QStringList adjectiveSuperlative = {"best", "worst", "most", "furthest", "least", "least", "most", "best"};

QStringList Adjective::adjectiveExceptions = QStringList();

Adjective::Adjective(): Word()
{
    this->indexOfAuxiliary = -1;
}

Adjective::Adjective(const QString &newWord): Word (newWord)
{
    this->indexOfAuxiliary = -1;
}

Adjective::Adjective(const QString &word, const unsigned int &firstForm, const unsigned int &secondForm,
          const unsigned int &thirdForm, const unsigned int &auxForAdj): Word (word, firstForm, secondForm, thirdForm, auxForAdj)
{
    this->indexOfAuxiliary = -1;
}

Adjective::Adjective(const QString &word, const QSet<WordForm> &possibleFormsOfWord, const int &indexOfAuxiliary): Word(word, possibleFormsOfWord)
{
    this->indexOfAuxiliary = indexOfAuxiliary;
}

int Adjective::getIndexOfAuxiliary() const
{
    return indexOfAuxiliary;
}

void Adjective::setIndexOfAuxiliary(int newIndexOfAuxiliary)
{
    indexOfAuxiliary = newIndexOfAuxiliary;
}

QString Adjective::getType() const
{
    return "adjective";
}

void Adjective::clearAllWord()
{
    this->clearWordAndPossibleForms();
    this->indexOfAuxiliary = -1;
}

posTags Adjective::getPosTag() const
{
    return adj;
}

QSet<Word*> Adjective::formAllForms() const
{
    QSet<Word*> allForms;
    QStringList exceptionFormsList;

    if (this->adjIsException(exceptionFormsList) && !(exceptionFormsList.length() % 3))
    {
        QMutableListIterator iExceptionWord(exceptionFormsList);
        while (iExceptionWord.hasNext())
        {
            allForms << new Adjective(iExceptionWord.next(), positive, notSet, notSet, notNeed);

            allForms << new Adjective(iExceptionWord.next(), comparative, notSet, notSet, notNeed);

            allForms << new Adjective(iExceptionWord.next(), superlative, notSet, notSet, notNeed);
        }
    }
    else
    {
        //Образовать начальную форму прилагательного
        Adjective initialAdjective = this->formInitial();
        allForms << new Adjective (initialAdjective);

        //Образовать сравнительную форму прилагательного
        allForms << new Adjective (this->formComparative(initialAdjective.word));

        //Образовать превосходную форму прилагательного
        allForms << new Adjective (this->formSuperlative(initialAdjective.word));
    }

    //Объединить все слова, совпадающие по написанию
    this->mergeFormsForAllWords(allForms);

    //Вернуть получившийся список
    return allForms;
}

Adjective Adjective::formInitial() const
{
    QString initialAdjective = this->word;

    // Перевод QString в char*
    QByteArray string = this->word.toLatin1();
    char* adjectiveInStr = string.data();

    if (wninit())
    {
        fprintf(stderr, "morphy: Fatal error - cannot open WordNet database\n");
        exit(-1);
    }

    char *initial = morphstr(adjectiveInStr, ADJ);

    if (initial != NULL)
    {
        initialAdjective = initial;
    }

    //Присвоить данной форме в первое поле метку positive
    //Присвоить в четвертое поле метку notNeed
    return Adjective(initialAdjective, positive, notSet, notSet, notNeed);
}

bool Adjective::adjIsException(QStringList &forms) const
{    
    QMutableStringListIterator iCurrentLine(this->adjectiveExceptions);

    while (iCurrentLine.hasNext())
    { // Пока не дошли до конца файла
        QString line = iCurrentLine.next(); // Считываем строку из файла

        // Делим считанную строку на части, в качестве разделителя - запятые
        QStringList data = line.split(",");

        if (data.contains(this->word))
        {
            if (data.length() == 3)
            {
                forms << data;
            }
        }
    }

    return forms.length();
}

bool Adjective::readFileWithAdjectiveExceptions()
{
    QFile file("..\\adjectiveExceptions.csv"); // Создаем файл с указанным именем

    if (!file.exists())
    { // Если файл не существует
        return false;
    }

    if (!file.open(QIODevice::ReadOnly))
    { // Если файл не доступен для чтения
        return false;
    }

    QTextStream stream(&file); // Поток данных файла

    QMutableListIterator<QString> onlyPluralNounsList(adjectiveExceptions);

    while (!stream.atEnd())
    { // Пока не дошли до конца файла
        adjectiveExceptions << stream.readLine(); // Считываем строку из файла
    }

    file.close(); // Закрываем файл

    return true;
}

Adjective Adjective::formComparative(const QString &adjective) const
{
    Adjective comparativeAdjective = adjective;
    int countOfSyllables = comparativeAdjective.countSyllables();
    int lengthOfAdjective = adjective.length();
    WordForm comparativeForm(comparative, notSet, notSet, notNeed);

    if (countOfSyllables == 1 && adjective.endsWith("e"))
    { //Если прилагательное имеет 1 слог и заканчивается на -e
        // Добавить к нему окончание -r
        comparativeAdjective.word.append("r");
    }
    else if (countOfSyllables == 1 && lengthOfAdjective >= 3 &&
               !isStaticVowel(adjective[lengthOfAdjective - 1]) &&
                isStaticVowel(adjective[lengthOfAdjective - 2]) &&
               !isStaticVowel(adjective[lengthOfAdjective - 3]))
    { //ИначеЕсли односложное прилагательное заканчивается сочетанием согласная + гласная + согласная
        // двоить последнюю букву
        comparativeAdjective.word.append(adjective[lengthOfAdjective - 1]);
        // Добавить окончание -er
        comparativeAdjective.word.append("er");
    }
    else if (countOfSyllables == 1) //ИначеЕсли прилагательное односложное
    {
        // Добавить к нему окончание -er
        comparativeAdjective.word.append("er");
    }
    else if (countOfSyllables == 2 && adjective.endsWith("y"))
    { //ИначеЕсли в прилагательном 2 слога и последняя буква -y
        // Заменить -y на -i, Добавить окончание -er
        comparativeAdjective.word.replace(lengthOfAdjective - 1, 1, "ier");
    }
    else
    {
        comparativeForm.setAuxForAdj(more);
    }

    QSet<WordForm> tmpForm;
    tmpForm << comparativeForm;
    comparativeAdjective.setPossibleFormsOfWord(tmpForm);

    return comparativeAdjective;
}

Adjective Adjective::formSuperlative(const QString &adjective) const
{
    Adjective superlativeAdjective = adjective;
    int countOfSyllables = superlativeAdjective.countSyllables();
    int lengthOfAdjective = adjective.length();
    WordForm superlativeForm(superlative, notSet, notSet, notNeed);

    if (countOfSyllables == 1 && adjective.endsWith("e"))
    { // Если прилагательное имеет 1 слог и заканчивается на -e
        // Добавить к нему окончание -st
        superlativeAdjective.word.append("st");
    }
    else if (countOfSyllables == 1 && lengthOfAdjective >= 3 &&
             !isStaticVowel(adjective[lengthOfAdjective - 1]) &&
             isStaticVowel(adjective[lengthOfAdjective - 2]) &&
             !isStaticVowel(adjective[lengthOfAdjective - 3]))
    { // ИначеЕсли односложное прилагательное заканчивается сочетанием согласная + гласная + согласная
        // Удвоить последнюю букву
        superlativeAdjective.word.append(adjective[lengthOfAdjective - 1]);
        // Добавить окончание -est
        superlativeAdjective.word.append("est");
    }
    else if (countOfSyllables == 1)
    { // ИначеЕсли прилагательное односложное
        // Добавить к нему окончание -est
        superlativeAdjective.word.append("est");
    }
    else if (countOfSyllables == 2 && adjective.endsWith("y"))
    { // ИначеЕсли в прилагательном 2 слога и последняя буква -y
        // Заменить -y на -i, Добавить окончание -est
        superlativeAdjective.word.replace(lengthOfAdjective - 1, 1, "iest");
    }
    else // Иначе
    {
        superlativeForm.setAuxForAdj(most);
    }

    QSet<WordForm> tmpForm;
    tmpForm << superlativeForm;
    superlativeAdjective.setPossibleFormsOfWord(tmpForm);

    return superlativeAdjective;
}

int Adjective::calculateFallacy(const WordForm& firstForm, const WordForm& secondForm) const
{
    int fallacy = 0;

    //Если формы не совпадают
    if (!(firstForm == secondForm))
    {
        // Прибавить к ошибочности 100
        fallacy += 100;
    }

    return fallacy;
}

bool Adjective::wordsAreEqual(const Word* otherWord, QString &misstakeMessage) const
{
    QString tmpMessage = "";

    if (typeid(*otherWord) == typeid(Adjective))
    {
        Adjective adjWord = *(dynamic_cast<const Adjective*>(otherWord));

        this->wordsSame(adjWord, tmpMessage);

        if (this->indexOfAuxiliary != adjWord.indexOfAuxiliary)
        {
            tmpMessage += " expected index of aux: " + QString::number(this->indexOfAuxiliary) +
                          ", real index of aux: " + QString::number(adjWord.indexOfAuxiliary) + "; ";
        }
    }
    else
    {
        tmpMessage += " expected pos: " + this->getType() + ", real pos: " + otherWord->getType() + "; ";
    }

    if (tmpMessage == "")
    {
        return true;
    }
    else
    {
        misstakeMessage = tmpMessage;
        return false;
    }
}
