/**
 * @file Sentence.h
 * @brief класс Sentence. Заголовки.
 */

#ifndef SENTENCE_H
#define SENTENCE_H

#include "InputDataError.h"
#include "adjective.h"
#include "auxiliary.h"
#include "noun.h"
#include "numeral.h"
#include "pronoun.h"
#include "verb.h"
#include <QRegularExpression>

/**
 * @class Sentence
 * @brief Класс для хранения предложения и работы с ним.
 */
class Sentence {
    QList<Word*> sentence;

public:
    Sentence();

    QList<Word*> getSentence() const;
    void setSentence(const QList<Word*> &newSentence);

    /**
     * @brief parseSentence
     * Разбивает предложение на слова
     * @param notParsedSentence
     */
    void parseSentence(const QString &notParsedSentence);

    /**
     * @brief addWordToEnd
     * Добавляет слово в конец предложения.
     * @param newWord - Новое слово.
     */
    void addWordToEnd(Word* newWord);

    /**
     * @brief clear
     * Удаляет все данные объекта класса.
     */
    void clear();

    /**
     * @brief connectSentenceAndPosTags Соединяет pos-теги со словами правильного предложения
     * @param posTagsSentence Предложение с pos-тегами
     * @return Записывает исходное предложение с присвоенными pos-тегами в поле класса
     * и возвращает необходимые данные для отображения ошибки соединения, если соединение не удалось
     */
    InputDataError connectSentenceAndPosTags(const Sentence &posTagsSentence);

    /**
     * @brief setFormsInCorrectSentence
     * Установить формы и вспомогательные слова в правильном предложении
     * @param[in] Предложение, поле данных класса
     */
    void setFormsInCorrectSentence();

    /**
     * @brief findAllVerbAuxiliaries
     * Выполняет поиск всех вспомогательных слов глагола,
     * находящихся в предложении от индекса startPos до индекса endPos.
     * ВСпомогательные должны быть объектами соответствующего класса.
     * @param startPos - Начальная позиция поиска.
     * @param endPos - Конечная позиция поиска.
     * @return Набор индексов обнаруженных вспомогательных слов.
     */
    QList<int> findAllVerbAuxiliaries(const unsigned int &startPos, const unsigned int &endPos) const;

    /**
     * @brief setFormInVerifiedSentence
     * Устанавливает время глагола, вспомогательные слова
     * к указанному глаголу или прилагательному в проверяемом предложении.
     * @param indexOfProcessingWord - Индекс слова, для которого устанавливаем форму.
     * @param formsOfProcessingWord - Формы обрабатываемого слова.
     * @param posTagOfProcessingWord - Часть речи обрабатываемого слова.
     * @return Набор всех возможных форм слова, включая вспомогательные.
     */
    QSet<Word*> setFormInVerifiedSentence(const int &indexOfProcessingWord,
                                          const QSet<WordForm> &formsOfProcessingWord,
                                          const posTags &tagOfProcessingWord) const;

    /**
     * @brief defineTense
     * Определяет время глагола (и лицо глагола, когда вспомогательные влияют на него).
     * @param currentVerbForm - Форма глагола, для которой определяем лицло.
     * @param indexesOfAuxiliaries
     * @return
     */
    WordForm defineTense(const WordForm &currentVerbForm,
                             const QList<int> &indexesOfAuxiliaries) const;

    /**
     * @brief canExtendToTense
     * Проверяет, можно ли расширить текущий список вспомогательных до какого-либо времени.
     * @param auxiliaries - Индексы вспомогательных.
     * @return true - если можно расширить текущий список вспомогательных до какого-либо времени,
     * false - если нельзя.
     */
    bool canExtendToTense(const QList<int> &auxiliaries) const;
};

#endif // SENTENCE_H
