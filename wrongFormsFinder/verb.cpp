#include "verb.h"

static QStringList multipleFormsVerbs = {"lay"};

static QStringList verbBeForms = {"be", "am", "are", "is", "was", "were", "been", "being"};

QStringList Verb::irregularVerbs = QStringList();
QStringList Verb::verbLexems = QStringList();

Verb::Verb(): Word()
{
    ;
}

Verb::Verb(const QString &newWord): Word (newWord)
{
    ;
}

Verb::Verb(const QString &word, const unsigned int &firstForm, const unsigned int &secondForm,
     const unsigned int &thirdForm, const unsigned int &auxForAdj): Word (word, firstForm, secondForm, thirdForm, auxForAdj)
{
    ;
}

Verb::Verb(const QString &word, const QSet<WordForm> &possibleFormsOfWord,
           const QList<int> &indexesOfAuxiliaries): Word(word, possibleFormsOfWord)
{
    this->indexesOfAuxiliaries = indexesOfAuxiliaries;
}

Verb::Verb(const Verb &v)
{
    this->word = v.word;
    this->possibleFormsOfWord = v.possibleFormsOfWord;
    this->indexesOfAuxiliaries = v.indexesOfAuxiliaries;
}

QList<int> Verb::getIndexesOfAuxiliaries() const
{
    return indexesOfAuxiliaries;
}

void Verb::setIndexesOfAuxiliaries(const QList<int> &newIndexesOfAuxiliaries)
{
    indexesOfAuxiliaries = newIndexesOfAuxiliaries;
}

QSet<Word*> Verb::formAllForms() const
{
    QSet<Word*> allForms;
    Verb tmp;

    //Если глагол be или его формы
    if (verbBeForms.contains(this->word))
    {
        // Образовать все формы глагола be
        allForms = this->formAllFormsOfVerbBe();

        // Вернуть все формы глагола be
        return allForms;
    }

    Verb infinitiveVerb = this->formInfinitive(this->word);
    bool irregularVerb;

    //Если глагол неправильный
    QStringList irregularForms;

    try
    {
        irregularVerb = infinitiveVerb.verbIsIrregular(irregularForms);
    }
    catch (bool fileExist)
    {
        std::cout << "File with irregular verb not exists\n";
    }

    if (multipleFormsVerbs.contains(this->word))
    {
        QStringList tmp;
        if (this->verbIsIrregular(tmp))
        {
            allForms.unite(this->formAllIrregularVerbForms(this->word));
        }
    }

    if (irregularVerb)
    {
        allForms.unite(this->formAllIrregularVerbForms(infinitiveVerb.word));
    }
    else
    {
        allForms.unite(this->formAllRegularVerbForms(infinitiveVerb.word));
    }

    this->mergeFormsForAllWords(allForms);
    return allForms;
}

QSet<Word*> Verb::formAllIrregularVerbForms(const QString &verb) const
{
    QSet<Word*> allForms;
    Verb tmpVerb(verb);
    QStringList allIrregularForms;

    if (tmpVerb.verbIsIrregular(allIrregularForms))
    {
        // Добавляем начальную форму
        allForms << new Verb(verb, notSet, notThird, infinitive, notSet);

        //Образовать форму глагола 3-го лица
        allForms << new Verb(this->formThirdPersonVerb(allIrregularForms[0]));

        //Образовать форму preterite
        allForms << new Verb(this->formPreterite(allIrregularForms[1]));

        //Образовать форму pastParticiple
        allForms << new Verb(this->formPastParticiple(allIrregularForms[2]));

        //Образовать форму presentParticiple
        allForms << new Verb(this->formPresentParticiple(allIrregularForms[0]));
    }

    return allForms;
}

QSet<Word*> Verb::formAllRegularVerbForms(const QString &verb) const
{
    QSet<Word*> allForms;

    // Добавляем начальную форму
    allForms << new Verb(verb, notSet, notThird, infinitive, notSet);

    // Образовать форму глагола 3-го лица
    allForms << new Verb(this->formThirdPersonVerb(verb));

    // Образовать форму прошедшего времени правильного глагола
    allForms << new Verb(this->formPastRightVerb(verb));

    //Образовать форму presentParticiple
    allForms << new Verb(this->formPresentParticiple(verb));

    return allForms;
}

Verb Verb::formInfinitive(const QString &verb) const
{
    QString infinitiveVerb = verb;
    // Перевод QString в char*
    QByteArray string = verb.toLatin1();
    char* verbInStr = string.data();

    if (wninit()) {
        fprintf(stderr, "morphy: Fatal error - cannot open WordNet database\n");
        exit(-1);
    }

    char *initial = morphstr(verbInStr, VERB);

    if (initial != NULL)
    {
        infinitiveVerb = initial;
    }

    return Verb(infinitiveVerb, notSet, notThird, infinitive, notSet);
}

bool Verb::verbIsIrregular(QStringList &formsOfVerb) const
{
    bool hasMatch = false;

    QMutableStringListIterator iCurrentLine(this->irregularVerbs);

    while (iCurrentLine.hasNext() && !hasMatch)
    { // Пока не дошли до конца файла
        QString line = iCurrentLine.next(); // Считываем строку из файла

        // Делим считанную строку на части, в качестве разделителя - запятые
        QStringList data = line.split(",");

        if (data.contains(this->word))
        {
            if (data.length() == 3)
            {
                formsOfVerb = data;
                hasMatch = true;
            }
        }
    }

    return hasMatch;
}

QSet<Word*> Verb::formAllFormsOfVerbBe() const
{
    QSet<Word*> formsOfBe;

    // Образовать форму Be инфинитиава
    formsOfBe << new Verb("be", notSet, notThird, infinitive, notSet);

    //Образовать формы первого и второго лица: am, are
    //Присвоить им в третье поле метку verbBeAreAmForm
    formsOfBe << new Verb("am", notSet, first, infinitive, notSet);
    formsOfBe << new Verb("are", notSet, notThird, infinitive, notSet);

    //Образовать форму третьего лица: is
    //Присвоить ей в третье поле метку present3P
    formsOfBe << new Verb("is", notSet, third, infinitive, notSet);

    //Образовать формы preterite: was, were
    //Присвоить им в третье поле метку preterite
    formsOfBe << new Verb("was", notSet, notThird, preterite, notSet);
    formsOfBe << new Verb("were", notSet, notThird, preterite, notSet);

    //Образовать форму прошедшего времени: been
    //Присвоить ей в третье поле метку pastParticiple
    formsOfBe << new Verb("been", notSet, notThird, pastParticiple, notSet);

    //Образовать форму presentParticiple: being
    //Присвоить ей в третье поле метку presentParticiple
    formsOfBe << new Verb("being", notSet, notThird, presentParticiple, notSet);

    return formsOfBe;
}

Verb Verb::formThirdPersonVerb(const QString &verb) const
{
    QString tmpThirdPersonVerb = verb;

    if (verb == "have")
    {
        tmpThirdPersonVerb = "has";
    }
    //Если глагол оканчивается на (s, ss, sh, ch, x, o)
    else if (verb.endsWith("s") || verb.endsWith("ss") || verb.endsWith("sh") ||
        verb.endsWith("ch") || verb.endsWith("x") || verb.endsWith("o"))
    {
        // Добавить к его окончанию -es
        tmpThirdPersonVerb.append("es");
    }
    else if (verb.endsWith("y") && verb.length() >= 2 && !isStaticVowel(verb[verb.length() - 2]))
    { //ИначеЕсли глагол оканчивается на -y с предшествующей согласной
        // Заменить -y на -i, Добавить к его окончанию -es
        tmpThirdPersonVerb.replace(verb.length() - 1, 1, "ies");
    }
    else //Иначе
    {
        // Добавить -s к окончанию
        tmpThirdPersonVerb.append("s");
    }

    //Присвоить глаголу во второе поле метку third
    return Verb(tmpThirdPersonVerb, notSet, third, infinitive, notSet);
}

Verb Verb::formPreterite(const QString &verb) const
{
    //Присвоить глаголу в третье поле метку preterite
    return Verb(verb, notSet, notThird, preterite, notSet);
}

Verb Verb::formPastParticiple(const QString &verb) const
{
    //Присвоить глаголу в третье поле метку pastParticiple
    return Verb(verb, notSet, notThird, pastParticiple, notSet);
}

Verb Verb::formPastRightVerb(const QString &verb) const
{
    Verb pastRightVerb(verb);
    int lenOfVerb = verb.length();

    //Если слово заканчивается на e
    if (verb.endsWith("e"))
    {
        // Добавить к нему окончание -d
        pastRightVerb.word.append("d");
    }
    else if (pastRightVerb.countSyllables() == 1 &&
               lenOfVerb >= 3 && !isStaticVowel(verb[lenOfVerb - 3]) &&
               isStaticVowel(verb[lenOfVerb - 2]) && !isStaticVowel(verb[lenOfVerb - 1]) && !verb.endsWith("y"))
    { //ИначеЕсли в слове 1 слог и оно оканчивается на согласная-гласная-согласная
        // Удвоить последнюю букву
        pastRightVerb.word.append(verb[lenOfVerb - 1]);
        // Добавить к нему окончание -ed
        pastRightVerb.word.append("ed");
    }
    else if (lenOfVerb > 1 && verb.endsWith('y') && !isStaticVowel(verb[lenOfVerb - 2]))
    { //ИначеЕсли заканчивается на согласную + y
        // Заменить окончание -y на окончание -ied
        pastRightVerb.word.replace(verb.length() - 1, 1, "ied");
    }
    else //Иначе
    {
        // Добавить окончание -ed
        pastRightVerb.word.append("ed");
    }

    //Присвоить глаголу в третье поле метку past
    QSet<WordForm> verbForms;
    WordForm tmpForm(notSet, notThird, past, notSet);
    verbForms << tmpForm;
    pastRightVerb.setPossibleFormsOfWord(verbForms);
    //Вернуть получившийся глагол
    return pastRightVerb;
}

Verb Verb::formPresentParticiple(const QString &verb) const
{
    QString verbInPresentParticiple = verb;
    int lenOfVerb = verbInPresentParticiple.length();

    if (verb.endsWith("ie"))
    {
        verbInPresentParticiple.replace(verb.length() - 2, 2, "ying");
    }
    else if (verb.endsWith("e"))
    { //Если слово заканчивается на e
        // Заменить окончание -e на окончание -ing
        verbInPresentParticiple.replace(verb.length() - 1, 1, "ing");
    }
    else if ((lenOfVerb >= 3 && !isStaticVowel(verb[lenOfVerb - 3])
                && isStaticVowel(verb[lenOfVerb - 2]) && !isStaticVowel(verb[lenOfVerb - 1])
                && verb != "cover" && verb != "remember" && !verb.endsWith("y")) ||
               (lenOfVerb >= 2 && !isStaticVowel(verb[lenOfVerb - 2])) && verb.endsWith("l") || verb == "quit")
    {//ИначеЕсли слово (оканчивается на согласная-гласная-согласная И оно не cover И оно не remember) ИЛИ
        // (оканчивается на гласную + согласную L)
        // Удвоить последнюю букву
        verbInPresentParticiple.append(verb[lenOfVerb - 1]);
        // Добавить к слову окончание -ing
        verbInPresentParticiple.append("ing");
    }
    else //Иначе
    {
        // Добавить к слову окончание -ing
        verbInPresentParticiple.append("ing");
    }

    //Присвоить глаголу в третье поле метку presentParticiple
    return Verb(verbInPresentParticiple, notSet, notThird, presentParticiple, notSet);
}

void Verb::setVerbWithForms(const QString &newWord, const QSet<WordForm> &newPossibleFormsOfWord, const QList<int> &newAuxiliaries)
{
    this->word = newWord;
    this->possibleFormsOfWord = newPossibleFormsOfWord;
    this->indexesOfAuxiliaries = newAuxiliaries;
}

bool Verb::readFileWithIrregularVerbs()
{
    QFile file("..\\irregularVerbs.csv"); // Создаем файл с указанным именем

    if (!file.exists())
    { // Если файл не существует
        // throw false;
        return false;
    }

    if (!file.open(QIODevice::ReadOnly))
    { // Если файл не доступен для чтения
        return false;
    }

    QTextStream stream(&file); // Поток данных файла

    while (!stream.atEnd())
    { // Пока не дошли до конца файла
        irregularVerbs << stream.readLine(); // Считываем строку из файла
    }

    file.close(); // Закрываем файл

    return true;
}

bool Verb::readFileWithVerbLexems()
{
    QFile file("..\\tensesLexems.txt"); // Создаем файл с указанным именем

    if (!file.exists())
    { // Если файл не существует
        return false;
    }

    if (!file.open(QIODevice::ReadOnly))
    { // Если файл не доступен для чтения
        return false;
    }

    QTextStream stream(&file); // Поток данных файла

    while (!stream.atEnd())
    { // Пока не дошли до конца файла
        verbLexems << stream.readLine(); // Считываем строку из файла
    }

    file.close(); // Закрываем файл

    return true;
}

int Verb::calculateFallacy(const WordForm& firstForm, const WordForm& secondForm) const
{
    //...Считать ошибочность пары 0
    int fallacy = 0;

    //Если не совпадают лица глагола
    if (firstForm.getSecondForm() != secondForm.getSecondForm())
    {
        // Прибавить к ошибочности 20
        fallacy += 20;
    }

    unsigned int firstTense = firstForm.getFirstForm();
    unsigned int secondTense = secondForm.getFirstForm();
    //Если времена совпадают
    if (firstTense == secondTense)
    {
        // Ошибочность не меняется
        ;
    }
    else if ((firstTense == presentSimple && secondTense == presentCont) ||
               (firstTense == presentCont && secondTense == presentSimple))
    { //ИначеЕсли времена Present Simple И Present Continuous
        // Прибавить к ошибочности 30
        fallacy += 30;
    }
    else if ((firstTense == pastSimple && secondTense == presentPerf) ||
               (firstTense == presentPerf && secondTense == pastSimple))
    { //ИначеЕсли времена Past Simple И Present Perfect
        // Прибавить к ошибочности 31
        fallacy += 31;
    }
    else if ((firstTense == pastSimple && secondTense == pastCont) ||
               (firstTense == pastCont && secondTense == pastSimple))
    { //ИначеЕсли времена Past Simple И Past Continuous
        // Прибавить к ошибочности 32
        fallacy += 32;
    }
    else if ((firstTense == presentPerf && secondTense == presentPerfCont) ||
               (firstTense == presentPerfCont && secondTense == presentPerf))
    { //ИначеЕсли времена Present Perfect И Present Perfect Continuous
        // Прибавить к ошибочности 33
        fallacy += 33;
    }
    else if ((firstTense == futureSimple && secondTense == futureCont) ||
               (firstTense == futureCont && secondTense == futureSimple))
    { //ИначеЕсли времена Future Simple И Future Continuous
        // Прибавить к ошибочности 34
        fallacy += 34;
    }
    else if ((firstTense == futureSimple && secondTense == presentSimple) ||
               (firstTense == presentSimple && secondTense == futureSimple))
    { //ИначеЕсли времена Future Simple И Present Simple
        // Прибавить к ошибочности 35
        fallacy += 35;
    }
    else if ((firstTense == pastSimple && secondTense == pastPerf) ||
               (firstTense == pastPerf && secondTense == pastSimple))
    { //ИначеЕсли времена Past Simple И Past Perfect
        // Прибавить к ошибочности 50
        fallacy += 50;
    }
    else if ((firstTense == presentPerf && secondTense == pastPerf) ||
               (firstTense == pastPerf && secondTense == presentPerf))
    { //ИначеЕсли времена Present Perfect И Past Perfect
        // Прибавить к ошибочности 50
        fallacy += 50;
    }
    else if ((firstTense == presentPerf && secondTense == pastPerf) ||
             (firstTense == pastPerf && secondTense == presentPerf))
    { //ИначеЕсли времена Past Continuous И Past Perfect Continuous
        // Прибавить к ошибочности 50
        fallacy += 50;
    }
    else if ((firstTense == presentPerf && secondTense == pastPerfCont) ||
             (firstTense == pastPerfCont && secondTense == presentPerf))
    {//ИначеЕсли времена Present Perfect Continuous И Past Perfect Continuous
        // Прибавить к ошибочности 50
        fallacy += 50;
    }
    else if ((firstTense == pastPerf && secondTense == pastPerfCont) ||
             (firstTense == pastPerfCont && secondTense == pastPerf))
    { //ИначеЕсли времена Past Perfect И Past Perfect Continuous
        // Прибавить к ошибочности 50
        fallacy += 50;
    }
    else if ((firstTense == futureCont && secondTense == futurePerfCont) ||
             (firstTense == futurePerfCont && secondTense == futureCont))
    { //ИначеЕсли времена Future Continuous И Future Perfect Continuous
        // Прибавить к ошибочности 50
        fallacy += 50;
    }
    else if ((firstTense == presentSimple && secondTense == pastSimple) ||
             (firstTense == pastSimple && secondTense == presentSimple))
    { //ИначеЕсли времена Present Simple И Past Simple
        // Прибавить к ошибочности 50
        fallacy += 50;
    }
    else if ((firstTense == presentPerfCont && secondTense == futurePerfCont) ||
             (firstTense == futurePerfCont && secondTense == presentPerfCont))
    { //ИначеЕсли времена Present Perfect Continuous И Future Perfect Continuous
        // Прибавить к ошибочности 50
        fallacy += 50;
    }
    else //Иначе
    {
        // Прибавить к ошибочности 80
        fallacy += 80;
    }

    return fallacy;
}

bool Verb::wordsAreEqual(const Word* otherWord, QString &misstakeMessage) const
{
    QString tmpMessage = "";

    if (typeid(*otherWord) == typeid(Verb))
    {
        //Verb verbWord = static_cast<const Verb&>(otherWord);
        Verb verbWord = *(dynamic_cast<const Verb*>(otherWord));

        this->wordsSame(verbWord, tmpMessage);

        QList<int> tmpExpAuxiliaries = this->indexesOfAuxiliaries;
        QList<int> tmpRealAuxiliaries = verbWord.indexesOfAuxiliaries;

        QMutableListIterator<int> iExpAuxiliary(tmpExpAuxiliaries);
        QMutableListIterator<int> iRealAuxiliary(tmpRealAuxiliaries);

        while (iExpAuxiliary.hasNext() && iRealAuxiliary.hasNext())
        {
            if (iExpAuxiliary.next() != iRealAuxiliary.next())
            {
                tmpMessage += " expected index of aux: " + QString::number(iExpAuxiliary.value()) +
                              ", real index of aux: " + QString::number(iRealAuxiliary.value()) + "; ";
            }
        }

        while (iExpAuxiliary.hasNext())
        {
            tmpMessage += " expected index of aux: " + QString::number(iExpAuxiliary.next()) +
                " has no maches; ";
        }

        while (iExpAuxiliary.hasNext())
        {
            tmpMessage += " unexpected index of aux: " + QString::number(iRealAuxiliary.next()) + "; ";
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

QString Verb::getType() const
{
    return "verb";
}

void Verb::clearAllWord()
{
    this->clearWordAndPossibleForms();
    this->indexesOfAuxiliaries.clear();
}

posTags Verb::getPosTag() const
{
    return verb;
}

bool Verb::operator==(const Verb &wordToCompare) const
{
    return (this->word == wordToCompare.word &&
            this->possibleFormsOfWord == wordToCompare.possibleFormsOfWord &&
            this->indexesOfAuxiliaries == wordToCompare.indexesOfAuxiliaries);
}

bool Verb::operator<(const Verb &other) const
{
    return (this->word < other.word);
}
