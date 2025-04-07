#include "filedataerror.h"
#include <iostream>
#include <QTextStream>

fileProcessingCodes FileDataError::getSentenceProcessingResult() const
{
    return sentenceProcessingResult;
}

void FileDataError::setSentenceProcessingResult(fileProcessingCodes newSentenceProcessingResult)
{
    sentenceProcessingResult = newSentenceProcessingResult;
}

int FileDataError::getStrCountInFile() const
{
    return strCountInFile;
}

void FileDataError::setStrCountInFile(int newStrCountInFile)
{
    strCountInFile = newStrCountInFile;
}

FileDataError::FileDataError()
{
    this->strCountInFile = -1;
    this->sentenceProcessingResult = filesProcessed;
}

void FileDataError::printFileDataMessage(const QString &filename, int countOfStrings)
{
    QByteArray string = filename.toLatin1();
    char* fileNameInChar = string.data();

    switch (this->sentenceProcessingResult)
    {
    case filesProcessed:
        std::cout << ("Файл был успешно обработан.\n");
        break;
    case inputCorrectFileNotExist:
        std::cout << "Неверно указан файл \"" << fileNameInChar << "\" с входными данными. Возможно, файл не существует.\n";
        break;
    case inputVerifiedFileNotExist:
        std::cout << "Неверно указан файл \"" << fileNameInChar << "\" для выходных данных. Возможно указанного расположения не существует или нет прав на запись.\n";
        break;
    case wrongStrCountInCorrectFile:
        std::cout << "Во входном файле \"" << fileNameInChar << "\" должно находиться " << countOfStrings <<
                " 2 строки. На самом же деле в нем находится " << strCountInFile << " строк.\n";
        break;
    case wrongStrCountInVerifiedFile:
        std::cout << "Во входном файле \"" << fileNameInChar << "\" должна находиться " << countOfStrings <<
                " строка. На самом же деле в нем находится " << strCountInFile << " строк.\n";
        break;
    default:
        std::cout << "Неизвестная ошибка обработки.\n";
        break;
    }
}
