/**
 * @file Adjective.h
 * @brief Класс Adjective. Заголовки.
 */

#ifndef ADJECTIVE_H
#define ADJECTIVE_H

#include "Word.h"
#include "wn.h"

/**
 * @class Adjective
 * @brief Описывает прилагательное и его формы.
 */
class Adjective: public Word {
private:
    int indexOfAuxiliary;

public:
    Adjective();
    Adjective(const QString &newWord);
    Adjective(const QString &word, const unsigned int &firstForm, const unsigned int &secondForm,
         const unsigned int &thirdForm, const unsigned int &auxForAdj);
    Adjective(const QString &word, const QSet<WordForm> &possibleFormsOfWord, const int &indexOfAuxiliary);

    int getIndexOfAuxiliary() const;
    void setIndexOfAuxiliary(int newIndexOfAuxiliary);

    /**
     * @brief Adjective::formAllForms
     * Образует все формы прилагательного, группируя их по написанию.
     * @return Все возможные формы прилагательного, сгруппированные по написанию.
     */
    QSet<Word*> formAllForms() const override;

    /**
     * @brief Adjective::calculateFallacy
     * Рассчитывает ошибочность пары прилагательных.
     * Текущий объект класса сравнивается с передаваемым прилагательным.
     * @param[in] other - прилагательное для сравнения.
     * @return Ошибочность в виде целого числа от 0 до 100,
     * где 0 - прилагательные абсолютно идентичны.
     */
    int calculateFallacy(const WordForm& firstForm, const WordForm& secondForm) const override;

    /**
     * @brief Adjective::getType
     * Возвращает тип класса в виде строки.
     * @return Строка, состоящая из типа класса.
     */
    QString getType() const override;

    /**
     * @brief Adjective::wordsAreEqual
     * Сравнивает два прилагательных. Возвращает результат сравнения и
     * сообщение, содержащее все различия между прилагательнми.
     * @param[in] otherWord - прилагательное, которой сравниваем с полем класса.
     * @param[out] misstakeMessage - сообщение, содержащее все различия между прилагательными.
     * @return true, если прилагательные полностью равны;
     * false - если прилагательные различаются хотя бы одним значением любого поля.
     */
    bool wordsAreEqual(const Word* otherWord, QString &misstakeMessage) const override;

    /**
     * @brief Adjective::clearAllWord
     * Очищает все поля класса текущего объекта.
     */
    void clearAllWord() override;

    /**
     * @brief getPosTag
     * Возвращает pos-тег, соответствующий текущему классу.
     * @return pos-тег, соответствующий текущему классу.
     */
    posTags getPosTag() const override;

    /**
     * @brief formInitial
     * Образует начальную форму прилагательного,
     * не являющегося исключением.
     * @return Прилагательное в начальной форме
     */
    Adjective formInitial() const;

    /**
     * @brief formComparative
     * Образует сравнительную степень прилагательного
     * из слова в начальной форме.
     * @param adjective - прилагательное в начальной форме.
     * @return Прилагательное в сравнительной степени.
     */
    Adjective formComparative(const QString &adjective) const;

    /**
     * @brief formSuperlative
     * Образует превосходную степень прилагательного
     * из слова в начальной форме.
     * @param adjective - прилагательное в начальной форме.
     * @return Прилагательное в превосходной степени.
     */
    Adjective formSuperlative(const QString &adjective) const;

    /**
     * @brief setAdjWithForms
     * Устанавливает в поля данных новый текст,
     * возможные формы и индекс вспомогательного.
     * @param newWord - новый текст прилагательного.
     * @param newPossibleFormsOfWord - новые возможные формы прилагательного.
     * @param newAuxiliary - новый индекс вспомогательного.
     */
    void setAdjWithForms(const QString &newWord, const QSet<WordForm> &newPossibleFormsOfWord,
                         const int &newAuxiliary);

    /**
     * @brief adjIsException
     * Проверяет, является ли прилагательное исключнием.
     * Если явялется, записывает все его формы в forms.
     * @param forms - все формы прилагательного, являющегося исключением.
     * @return true - если прилагаетльное исключение,
     * false - Иначе.
     */
    bool adjIsException(QStringList &forms) const;

    /**
     * @brief readFileWithAdjectiveExceptions
     * Читает файл adjectiveExceptions, результат записывает в поле класса
     * @return true - если записывание произошло, false - иначе
     */
    static bool readFileWithAdjectiveExceptions();

    static QStringList adjectiveExceptions;
};

#endif // ADJECTIVE_H
