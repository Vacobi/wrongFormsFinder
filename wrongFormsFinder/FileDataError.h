/**
 * @file FileDataError.h
 * @brief класс FileDataError. Заголовки.
 */

#ifndef FILEDATAERROR_H
#define FILEDATAERROR_H

#include <QString>

enum fileProcessingCodes {
    filesProcessed,
    inputCorrectFileNotExist,
    inputVerifiedFileNotExist,
    cantCreateOutputFile,
    wrongStrCountInCorrectFile,
    wrongStrCountInVerifiedFile,
    cantReadFileWithData
};

/**
 * @class FileDataError
 * @brief Описывает ошибки при обработке файлов.
 */
class FileDataError {
    enum fileProcessingCodes sentenceProcessingResult;
    int strCountInFile;

public:
    FileDataError();

    fileProcessingCodes getSentenceProcessingResult() const;
    void setSentenceProcessingResult(fileProcessingCodes newSentenceProcessingResult);
    int getStrCountInFile() const;
    void setStrCountInFile(int newStrCountInFile);

    /**
     * @brief printFileDataMessage
     * Выводит сообщение об ошибке обработки файлов.
     * @param[in] filename - имя файла, в котором произошла ошибка обработки.
     * @param[in] countOfStrings - количество строк в этом файле.
     */
    void printFileDataMessage(const QString &filename, int countOfStrings);
};

#endif // FILEDATAERROR_H
