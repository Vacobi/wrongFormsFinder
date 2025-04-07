#include "filesprocessing.h"
#include <iostream>

QString FilesProcessing::getCorrectSentence() const
{
    return correctSentence;
}

void FilesProcessing::setCorrectSentence(const QString &newCorrectSentence)
{
    correctSentence = newCorrectSentence;
}

QString FilesProcessing::getPosTagSentence() const
{
    return posTagSentence;
}

void FilesProcessing::setPosTagSentence(const QString &newPosTagSentence)
{
    posTagSentence = newPosTagSentence;
}

QString FilesProcessing::getVerifiedSentence() const
{
    return verifiedSentence;
}

void FilesProcessing::setVerifiedSentence(const QString &newVerifiedSentence)
{
    verifiedSentence = newVerifiedSentence;
}

FilesProcessing::FilesProcessing()
{
    this->correctSentence = "";
    this->posTagSentence = "";
    this->verifiedSentence = "";
}

FileDataError FilesProcessing::readFileWithCorrectSentence(const QString &correctSentenceFilename)
{
    FileDataError currentError;

    QFile file1(correctSentenceFilename);

    if (!file1.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        currentError.setSentenceProcessingResult(inputCorrectFileNotExist);
        return currentError;
    }

    // Читаем первые две строки
    QTextStream in1(&file1);
    if (in1.atEnd()) {
        currentError.setSentenceProcessingResult(wrongStrCountInCorrectFile);
        currentError.setStrCountInFile(0);
        return currentError;
    }

    // Сохранение корректного предложения
    this->correctSentence = in1.readLine();

    // Проверка на наличие частей речи во второй строке
    if (in1.atEnd()) {
        currentError.setSentenceProcessingResult(wrongStrCountInCorrectFile);
        currentError.setStrCountInFile(1);
        return currentError;
    }

    // Сохранение частей речи
    this->posTagSentence = in1.readLine();

    // Проверка на наличие третьей строки (которая не должна быть)
    if (!in1.atEnd()) {
        currentError.setSentenceProcessingResult(wrongStrCountInCorrectFile);
        currentError.setStrCountInFile(3);
        return currentError;
    }

    // Установить успешный результат обработки файлов в объекте InputDataError
    currentError.setSentenceProcessingResult(filesProcessed);

    // Закрыть оба файла
    file1.close();

   return currentError;
}

FileDataError FilesProcessing::readFileWithVerifiedSentence(const QString &verifiedSentenceFilename)
{
   FileDataError currentError;

   QFile file1(verifiedSentenceFilename);

   if (!file1.open(QIODevice::ReadOnly | QIODevice::Text))
   {
        currentError.setSentenceProcessingResult(inputCorrectFileNotExist);
        return currentError;
   }

   // Читаем первую строку
   QTextStream in1(&file1);
   if (in1.atEnd()) {
        currentError.setSentenceProcessingResult(wrongStrCountInVerifiedFile);
        currentError.setStrCountInFile(0);
        return currentError;
   }

   // Сохранение корректного предложения
   this->verifiedSentence = in1.readLine();

   // Проверка на наличие третьей строки (которая не должна быть)
   if (!in1.atEnd()) {
        currentError.setSentenceProcessingResult(wrongStrCountInVerifiedFile);
        currentError.setStrCountInFile(2);
        return currentError;
   }

   // Установить успешный результат обработки файлов в объекте InputDataError
   currentError.setSentenceProcessingResult(filesProcessed);

   // Закрыть оба файла
   file1.close();

   return currentError;
}

FileDataError FilesProcessing::writeErrorsToFile(const QString &filename, const QString &misstake) const
{
   FileDataError currentError;

   QFile file(filename);

   // Попытка открыть выходной файл для записи
   if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        currentError.setSentenceProcessingResult(cantCreateOutputFile);
        return currentError;
   }

   QTextStream out(&file);

   out << misstake;

   // Будем считать, что файлы записаны без ошибок
   currentError.setSentenceProcessingResult(filesProcessed);

   // Закрываем выходной файл
   file.close();

   return currentError;
}

FileDataError FilesProcessing::readFileWithData(const QString &filename) const
{
   FileDataError currentError;

   QFile file(filename);

   if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
   {
        currentError.setSentenceProcessingResult(cantReadFileWithData);
        return currentError;
   }

   // Будем считать, что файлы существует
   currentError.setSentenceProcessingResult(filesProcessed);

   // Закрываем файл
   file.close();

   return currentError;
}
