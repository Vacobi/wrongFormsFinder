/**
 * @file Auxiliary.h
 * @brief класс Auxiliary. Заголовки.
 */

#ifndef AUXILIARY_H
#define AUXILIARY_H

#include "Word.h"

/**
 * @class Auxiliary
 * @brief Описывает вспомогательные слова.
 */
class Auxiliary: public Word {
public:
    Auxiliary();
    Auxiliary(const QString &newWord);
    Auxiliary(const QString &word, const unsigned int &firstForm, const unsigned int &secondForm,
            const unsigned int &thirdForm, const unsigned int &auxForAdj);
    Auxiliary(const QString &word, const QSet<WordForm> &possibleFormsOfWord);

    /**
     * @brief Auxiliary::formAllForms
     * Образует все формы вспомогательного, группируя их по написанию.
     * @return Все возможные формы вспомогательного, сгруппированные по написанию.
     */
    QSet<Word*> formAllForms() const override;

    /**
     * @brief Auxiliary::calculateFallacy
     * Рассчитывает ошибочность пары вспомогательного.
     * Текущий объект класса сравнивается с передаваемым вспомогательным.
     * @param[in] other - вспомогательное для сравнения.
     * @return Ошибочность в виде целого числа от 0 до 100,
     * где 0 - вспомогательные абсолютно идентичны.
     */
    int calculateFallacy(const WordForm& firstForm, const WordForm& secondForm) const override;

    /**
     * @brief Auxiliary::getType
     * Возвращает тип класса в виде строки.
     * @return Строка, состоящая из типа класса.
     */
    QString getType() const override;

    /**
     * @brief Auxiliary::wordsAreEqual
     * Сравнивает два вспомогательных. Возвращает результат сравнения и
     * сообщение, содержащее все различия между вспомогательными.
     * @param[in] otherWord - вспомогательное, которой сравниваем с полем класса.
     * @param[out] misstakeMessage - сообщение, содержащее все различия между вспомогательными.
     * @return true, если вспомогательные полностью равны;
     * false - если вспомогательные различаются хотя бы одним значением любого поля.
     */
    bool wordsAreEqual(const Word* otherWord, QString &misstakeMessage) const override;

    /**
     * @brief Auxiliary::clearAllWord
     * Очищает все поля класса текущего объекта.
     */
    void clearAllWord() override;

    /**
     * @brief getPosTag
     * Возвращает pos-тег, соответствующий текущему классу.
     * @return pos-тег, соответствующий текущему классу.
     */
    posTags getPosTag() const override;
};

#endif // AUXILIARY_H
