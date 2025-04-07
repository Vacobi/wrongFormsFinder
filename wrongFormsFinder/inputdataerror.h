/**
 * @file InputDataError.h
 * @brief класс InputDataError. Заголовки.
 */

#ifndef INPUTDATAERROR_H
#define INPUTDATAERROR_H

#include <QString>
#include <iostream>

enum sentencesProcessingCodes {
    sentenceSuccessfulProcessed,
    fewerWordsThanTags,
    fewerTagsThanWords,
    incorrectPosTag,
    zeroWordsInSentence,
    initialized
};

/**
 * @class InputDataError
 * @brief Описывает ошибки при обработке строк из файлов.
 */
class InputDataError {
    enum sentencesProcessingCodes fileProcessingResult;
    int countOfWordsInFile;
    int countOfPosTagsInFile;
    QString wrongPosTag;

public:
    InputDataError();
    bool operator==(const InputDataError &errorToCompare) const;

    sentencesProcessingCodes getFileProcessingResult() const;
    void setFileProcessingResult(sentencesProcessingCodes newFileProcessingResult);
    int getCountOfWordsInFile() const;
    void setCountOfWordsInFile(int newCountOfWordsInFile);
    int getCountOfPosTagsInFile() const;
    void setCountOfPosTagsInFile(int newCountOfPosTagsInFile);
    QString getWrongPosTag() const;
    void setWrongPosTag(const QString &newWrongPosTag);

    /**
     * @brief setParameters
     * Устанавливает все параметры объекта класса.
     * @param[in] processingCode - код обработки.
     * @param[in] wordsCount - количество слов.
     * @param[in] posTagsCount - количество pos-тегов.
     * @param[in] wrongTag - некорректный тег.
     */
    void setParameters(enum sentencesProcessingCodes processingCode, int wordsCount, int posTagsCount, QString wrongTag);

    /**
     * @brief getFileProcessingResultByStr
     * Выводит ошибку при обработке файла.
     */
    QString getFileProcessingResultByStr();

    /**
     * @brief printInputDataMessage
     * Выводит сообщение об ошибке обработки файла.
     * @param[in] filename - имя файла.
     */
    void printInputDataMessage(const QString &filename);
};

#endif // INPUTDATAERROR_H
