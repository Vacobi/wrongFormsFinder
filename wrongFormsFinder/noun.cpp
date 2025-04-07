#include "noun.h"

QStringList Noun::exceptionsNouns = QStringList();
QStringList Noun::onlyPluralNouns = QStringList();
QStringList Noun::uncountableNouns = QStringList();

Noun::Noun(): Word()
{
    ;
}

Noun::Noun(const QString &newWord): Word (newWord)
{
    ;
}

Noun::Noun(const QString &word, const unsigned int &firstForm, const unsigned int &secondForm,
                 const unsigned int &thirdForm, const unsigned int &auxForAdj)
    : Word (word, firstForm, secondForm, thirdForm, auxForAdj)
{
    ;
}

Noun::Noun(const QString &word, const QSet<WordForm> &possibleFormsOfWord) : Word(word, possibleFormsOfWord)
{
    ;
}

QSet<Word*> Noun::formAllForms() const
{
    unsigned int countOfNoun;

    Noun initialForm = this->formInitial(countOfNoun);
    QSet<Word*> forms;

    forms << new Noun(initialForm);

    //Если слово имеет только множественную форму или оно неисчисляемое
    if (countOfNoun == plural || countOfNoun == uncountable)
    {
        forms << new Noun(this->formCaseOfNoun(initialForm.word, countOfNoun));
    }
    else
    {
        //Образовать форму притяжательного падежа единственного числа
        forms << new Noun(this->formCaseOfNoun(initialForm.word, countOfNoun));

        //Образовать форму множественного числа
        Noun pluralForm = this->formPlural(initialForm.word);
        forms << new Noun(pluralForm);

        //Образовать форму притяжательного падежа множественного числа
        forms << new Noun(this->formCaseOfNoun(pluralForm.word, plural));
    }

    return forms;
}

Noun Noun::formInitial(unsigned int &countOfInitial) const
{
    QString initialNoun = this->word;
    QStringList tmpForms;

    //Удалить все символы после апострофа, включая его, если он имеется
    if (initialNoun.contains("\'"))
    {
        initialNoun.truncate(initialNoun.indexOf('\''));
    }

    //Образовать начальную форму
    if (!nounIsException(initialNoun, tmpForms))
    {
        // Перевод QString в char*
        QByteArray string = initialNoun.toLatin1();
        char* nounInStr = string.data();

        if (!this->nounIsOnlyPlural(nounInStr))
        {
            if (wninit()) {
                fprintf(stderr, "morphy: Fatal error - cannot open WordNet database\n");
                exit(-1);
            }

            char *initial = morphstr(nounInStr, NOUN);

            if (initial != NULL)
            {
                initialNoun = initial;
            }
        }
    }
    else
    {
        initialNoun = tmpForms[0];
    }

    // Если существует только во множественном
    if (this->nounIsOnlyPlural(initialNoun))
    {
        countOfInitial = plural;
        return Noun(initialNoun, plural, objective, notSet, notSet);
    }
    else if (this->nounIsUncountable(initialNoun))
    {
        countOfInitial = uncountable;
        return Noun(initialNoun, uncountable, objective, notSet, notSet);
    }
    else
    {
        countOfInitial = singular;
        return Noun(initialNoun, singular, objective, notSet, notSet);
    }
}

Noun Noun::formPlural(const QString &noun) const
{
    QStringList formsOfNoun;
    QString pluralNoun = noun;
    int lengthOfNoun = noun.length();

    //Если слово является исключением
    if (this->nounIsException(noun, formsOfNoun))
    {
        // Взять из таблицы форму его множественного числа
        pluralNoun = formsOfNoun[1];
    }
    else //Иначе
    {
        //Если существительное оканчивается на -s, -ss, -ch, -sh, -x, -z
        if (noun.endsWith("s") || noun.endsWith("ss") || noun.endsWith("ch") ||
            noun.endsWith("sh") || noun.endsWith("x") || noun.endsWith("z"))
        {
            // Добавить к слову окончание -es
            pluralNoun.append("es");
        }
        else if (lengthOfNoun >= 2 && noun.endsWith("y") && !isStaticVowel(noun[lengthOfNoun - 2]))
        { //Если существительное оканчивается на согласный + -y
            //Заменить -y на -ies
            pluralNoun.replace(lengthOfNoun - 1, 1, "ies");
        }
        else if (noun.endsWith("f") || noun.endsWith("fe"))
        { //Если существительное оканчивается на -f или -fe
            //Заменить -f/-fe на -v
            if (noun.endsWith("f"))
            {
                pluralNoun.replace(lengthOfNoun - 1, 1, "ves");
            }
            else
            {
                pluralNoun.replace(lengthOfNoun - 2, 2, "ves");
            }
        }
        else //Иначе
        {
            //Добавить к слову окончание -s
            pluralNoun.append("s");
        }
    }

    //Присвоить слову в первое поле метку plural
    //Вернуть получившееся слово
    return Noun(pluralNoun, plural, objective, notSet, notSet);
}

Noun Noun::formCaseOfNoun(const QString &noun, const unsigned int &countOfNoun) const
{
    QString tmpPossessiveCaseNoun = noun;
    QStringList tmp;

    //Если существительное во множественном числе и оно существует не только во множественном числе
    if (countOfNoun == plural && !this->nounIsOnlyPlural(noun) && !this->nounIsException(noun, tmp))
    {
        //Добавить к существительному '
        tmpPossessiveCaseNoun.append("\'");
    }
    else //Иначе
    {
        //Добавить к существительному 's
        tmpPossessiveCaseNoun.append("\'s");
    }

    //Присвоить слову во второе поле метку possesiveCase
    return Noun(tmpPossessiveCaseNoun, countOfNoun, possessive, notSet, notSet);
}

int Noun::calculateFallacy(const WordForm& firstForm, const WordForm& secondForm) const
{
    int fallacy = 0;

    //Если не совпадает число
    if (firstForm.getFirstForm() != secondForm.getFirstForm())
    {
        // Прибавить к ошибочности 50
        fallacy += 50;
    }

    //Если не совпадает падеж
    if (firstForm.getSecondForm() != secondForm.getSecondForm())
    {
        // Прибавить к ошибочности 50
        fallacy += 50;
    }

    return fallacy;
}

QString Noun::getType() const
{
    return "noun";
}

bool Noun::wordsAreEqual(const Word* otherWord, QString &misstakeMessage) const
{
    return this->wordsSame(*otherWord, misstakeMessage);
}

void Noun::clearAllWord()
{
    this->clearWordAndPossibleForms();
}

posTags Noun::getPosTag() const
{
    return noun;
}

bool Noun::nounIsException(const QString &noun, QStringList &forms) const
{
    bool hasMatch = false;

    QMutableStringListIterator iCurrentLine(this->exceptionsNouns);

    while (iCurrentLine.hasNext() && !hasMatch)
    { // Пока не дошли до конца файла
        QString line = iCurrentLine.next(); // Считываем строку из файла

        line = line.toLower();
        // Делим считанную строку на части, в качестве разделителя - запятые
        QStringList data = line.split(",");

        if (data.contains(noun))
        {
            if (data.length() == 2)
            {
                forms = data;
                hasMatch = true;
            }
        }
    }

    return hasMatch;
}

bool Noun::nounIsOnlyPlural(const QString &noun) const
{
    bool hasMatch = false;

    QMutableStringListIterator iCurrentLine(this->onlyPluralNouns);

    while (iCurrentLine.hasNext() && !hasMatch)
    { // Пока не дошли до конца файла
        QString line = iCurrentLine.next(); // Считываем строку из файла

        // Делим считанную строку на части, в качестве разделителя - запятые
        QStringList data = line.split(",");

        if (data.contains(noun))
        {
            hasMatch = true;
        }
    }

    return hasMatch;
}

bool Noun::nounIsUncountable(const QString &noun) const
{
    bool hasMatch = false;

    QMutableStringListIterator iCurrentLine(this->uncountableNouns);

    while (iCurrentLine.hasNext() && !hasMatch)
    { // Пока не дошли до конца файла
        QString line = iCurrentLine.next(); // Считываем строку из файла

        // Делим считанную строку на части, в качестве разделителя - запятые
        QStringList data = line.split(",");

        if (data.contains(noun))
        {
            hasMatch = true;
        }
    }

    return hasMatch;
}

bool Noun::readFileWithExceptionsNouns()
{
    QFile file("..\\exceptionsNouns.csv"); // Создаем файл с указанным именем

    if (!file.exists())
    { // Если файл не существует
        return false;
    }

    if (!file.open(QIODevice::ReadOnly))
    { // Если файл не доступен для чтения
        return false;
    }

    QTextStream stream(&file); // Поток данных файла

    QMutableListIterator<QString> exceptionsNounsList(exceptionsNouns);

    while (!stream.atEnd())
    { // Пока не дошли до конца файла
        exceptionsNouns << stream.readLine(); // Считываем строку из файла
    }

    file.close(); // Закрываем файл

    return true;
}

bool Noun::readaFileWithOnlyPluralNouns()
{
    QFile file("..\\onlyPluralNouns.txt"); // Создаем файл с указанным именем

    if (!file.exists())
    { // Если файл не существует
        return false;
    }

    if (!file.open(QIODevice::ReadOnly))
    { // Если файл не доступен для чтения
        return false;
    }

    QTextStream stream(&file); // Поток данных файла

    QMutableListIterator<QString> onlyPluralNounsList(onlyPluralNouns);

    while (!stream.atEnd())
    { // Пока не дошли до конца файла
        onlyPluralNouns << stream.readLine(); // Считываем строку из файла
    }

    file.close(); // Закрываем файл

    return true;
}

bool Noun::readFileWithUncountableNouns()
{
    QFile file("..\\uncountableNouns.txt"); // Создаем файл с указанным именем

    if (!file.exists())
    { // Если файл не существует
        return false;
    }

    if (!file.open(QIODevice::ReadOnly))
    { // Если файл не доступен для чтения
        return false;
    }

    QTextStream stream(&file); // Поток данных файла

    QMutableListIterator<QString> uncountableNounsNounsList(uncountableNouns);

    while (!stream.atEnd())
    { // Пока не дошли до конца файла
        uncountableNouns << stream.readLine(); // Считываем строку из файла
    }

    file.close(); // Закрываем файл

    return true;
}
