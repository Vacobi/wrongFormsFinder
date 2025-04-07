/**
 * @file FilesProcessing.h
 * @brief класс FilesProcessing. Заголовки.
 */

#ifndef FILESPROCESSING_H
#define FILESPROCESSING_H

#include "FileDataError.h"
#include <QFile>
#include <QTextStream>

/**
 * @class FilesProcessing
 * @brief Описывает ошибки при обработке данных, находящихся в файлах.
 */
class FilesProcessing {
private:
    QString correctSentence;
    QString posTagSentence;
    QString verifiedSentence;

public:
    FilesProcessing();

    QString getCorrectSentence() const;
    void setCorrectSentence(const QString &newCorrectSentence);
    QString getPosTagSentence() const;
    void setPosTagSentence(const QString &newPosTagSentence);
    QString getVerifiedSentence() const;
    void setVerifiedSentence(const QString &newVerifiedSentence);

    /**
     * @brief readFileWithCorrectSentence
     * Читает данные из файла с правильным предложением.
     * @param[in] correctSentenceFilename - имя файла с правильным предложением.
     * @return Результат обработки файла.
     */
    FileDataError readFileWithCorrectSentence(const QString &correctSentenceFilename);

    /**
     * @brief readFileWithVerifiedSentence
     * Читает данные из файла с проверяемым предложением.
     * @param[in] verifiedSentenceFilename - имя файла с проверяемым предложением.
     * @return Результат обработки файла.
     */
    FileDataError readFileWithVerifiedSentence(const QString &verifiedSentenceFilename);

    FileDataError writeErrorsToFile(const QString &filename, const QString &misstake) const;

    FileDataError readFileWithData(const QString &filename) const;
};

#endif // FILESPROCESSING_H
