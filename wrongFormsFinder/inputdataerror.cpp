#include "inputdataerror.h"

InputDataError::InputDataError()
{
    this->countOfPosTagsInFile = -1;
    this->countOfPosTagsInFile = -1;
    this->wrongPosTag = "";
    this->fileProcessingResult = initialized;
}

bool InputDataError::operator==(const InputDataError &errorToCompare) const
{
    return (this->fileProcessingResult == errorToCompare.fileProcessingResult &&
            this->countOfWordsInFile == errorToCompare.countOfWordsInFile &&
            this->countOfPosTagsInFile == errorToCompare.countOfPosTagsInFile &&
            this->wrongPosTag == errorToCompare.wrongPosTag);
}

sentencesProcessingCodes InputDataError::getFileProcessingResult() const
{
    return fileProcessingResult;
}

void InputDataError::setFileProcessingResult(sentencesProcessingCodes newFileProcessingResult)
{
    fileProcessingResult = newFileProcessingResult;
}

int InputDataError::getCountOfWordsInFile() const
{
    return countOfWordsInFile;
}

void InputDataError::setCountOfWordsInFile(int newCountOfWordsInFile)
{
    countOfWordsInFile = newCountOfWordsInFile;
}

int InputDataError::getCountOfPosTagsInFile() const
{
    return countOfPosTagsInFile;
}

void InputDataError::setCountOfPosTagsInFile(int newCountOfPosTagsInFile)
{
    countOfPosTagsInFile = newCountOfPosTagsInFile;
}

QString InputDataError::getWrongPosTag() const
{
    return wrongPosTag;
}

void InputDataError::setWrongPosTag(const QString &newWrongPosTag)
{
    wrongPosTag = newWrongPosTag;
}

void InputDataError::setParameters(sentencesProcessingCodes codeOfProcess, int wordsCount, int posTagsCount, QString wrongTag)
{
    this->fileProcessingResult = codeOfProcess;
    this->countOfWordsInFile = wordsCount;
    this->countOfPosTagsInFile = posTagsCount;
    this->wrongPosTag = wrongTag;
}

QString InputDataError::getFileProcessingResultByStr()
{
    if (this->fileProcessingResult == sentenceSuccessfulProcessed)
    {
        return ("Предложение было успешно обработано.\n");
    }
    else if (this->fileProcessingResult == fewerWordsThanTags ||
             this->fileProcessingResult == fewerTagsThanWords)
    {
        return ("Количество слов в корректном предложении не совпадает с количеством pos-тегов (" + QString::number(this->countOfWordsInFile) +
                " слов, " + QString::number(this->countOfPosTagsInFile) + " pos-тегов).\n");
    }
    else if (this->fileProcessingResult == incorrectPosTag)
    {
        return ("Встречен некорректный pos-тег: " + this->wrongPosTag + ".\n");
    }
    else
    {
        return "В предложении должно содержаться хотя бы одно слово.\n";
    }
}
