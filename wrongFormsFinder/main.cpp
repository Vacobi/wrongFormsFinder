#include <QCoreApplication>

#include "linkedSentences.h"
#include "filesprocessing.h"
#include "iostream"

int main(int argc, char *argv[])
{
    //QCoreApplication a(argc, argv);

    InputDataError errors; // Объект для хранения ошибок при чтении файлов
    FileDataError sentenceErrors; // Объект для храннеия ошибок при обработке предложений
    FilesProcessing currentFilesData;

    // Чтение содержимого файлов

    FileDataError errorOfReadCorrectFile = currentFilesData.readFileWithCorrectSentence(argv[1]);
    //FileDataError errorOfReadCorrectFile = currentFilesData.readFileWithCorrectSentence("D:\\qt\\projects\\findWrongForms\\wrongFormsFinder\\release\\tests\\20test\\correctSentenceFile.txt");

    if (errorOfReadCorrectFile.getSentenceProcessingResult() != filesProcessed)
    {
        errorOfReadCorrectFile.printFileDataMessage(argv[1], 2);
        return -1;
    }

    FileDataError errorOfReadVerifiedFile = currentFilesData.readFileWithVerifiedSentence(argv[2]);
    //FileDataError errorOfReadVerifiedFile = currentFilesData.readFileWithVerifiedSentence("D:\\qt\\projects\\findWrongForms\\wrongFormsFinder\\release\\tests\\20test\\verifiedSentenceFile.txt");

    if (errorOfReadVerifiedFile.getSentenceProcessingResult() != filesProcessed)
    {
        errorOfReadVerifiedFile.printFileDataMessage(argv[2], 1);
        return -1;
    }

    Sentence correctSentence;
    Sentence posTagsSentence;
    Sentence verifiedSentence;

    correctSentence.parseSentence(currentFilesData.getCorrectSentence());
    verifiedSentence.parseSentence(currentFilesData.getVerifiedSentence());
    posTagsSentence.parseSentence(currentFilesData.getPosTagSentence());

    //Проверка существования файлов, необходимых для работы
    FileDataError setupFiles;

    if (Verb::readFileWithIrregularVerbs() == false)
    {
        std::cout << "Can't open file irregularVerbs with data.\n";
        return -1;
    }

    if (Verb::readFileWithVerbLexems() == false)
    {
        std::cout << "Can't open file tensesLexems with data.\n";
        return -1;
    }

    if (Noun::readFileWithExceptionsNouns() == false)
    {
        std::cout << "Can't open file exceptionsNouns with data.\n";
        return -1;
    }

    if (Noun::readaFileWithOnlyPluralNouns() == false)
    {
        std::cout << "Can't open file onlyPluralNouns with data.\n";
        return -1;
    }

    if (Noun::readFileWithUncountableNouns() == false)
    {
        std::cout << "Can't open file uncountableNouns with data.\n";
        return -1;
    }

    if (Adjective::readFileWithAdjectiveExceptions() == false)
    {
        std::cout << "Can't open file adjectiveExceptions with data.\n";
        return -1;
    }

    InputDataError currentConnectError = correctSentence.connectSentenceAndPosTags(posTagsSentence);

    if (currentConnectError.getFileProcessingResult() != sentenceSuccessfulProcessed)
    {
        QByteArray string = currentConnectError.getFileProcessingResultByStr().toUtf8();
        std::cout << string.data();
        return -1;
    }

    LinkedSentences currentSolution;

    currentSolution.linkSentences(correctSentence, verifiedSentence);

    QString misstakeMessage = currentSolution.getCurrentSetsMisstakes(correctSentence, verifiedSentence);

    // Сделать запись в файл

    FileDataError outputError = currentFilesData.writeErrorsToFile(argv[3], misstakeMessage);
    //FileDataError outputError = currentFilesData.writeErrorsToFile("D:\\qt\\projects\\findWrongForms\\wrongFormsFinder\\release\\tests\\20test\\output.txt", misstakeMessage);

    if (outputError.getSentenceProcessingResult() != filesProcessed)
    {
        outputError.printFileDataMessage(argv[3], 1);
        return -1;
    }

    std::cout << "Program correctly complete\n";
    return 0;
}
