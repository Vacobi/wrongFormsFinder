/**
 * @file Numeral.h
 * @brief Класс Numeral. Заголовки.
 */

#ifndef NUMERAL_H
#define NUMERAL_H

#include "word.h"

/**
 * @class Numeral
 * @brief Описывает числительное и его формы.
 */
class Numeral: public Word {
public:
    Numeral();
    Numeral(const QString &newWord);
    Numeral(const QString &word, const unsigned int &firstForm, const unsigned int &secondForm,
            const unsigned int &thirdForm, const unsigned int &auxForAdj);
    Numeral(const QString &word, const QSet<WordForm> &possibleFormsOfWord);

    bool operator==(const Numeral &toCompare) const;

    /**
     * @brief Numeral::formAllForms
     * Образует все формы числительного, группируя их по написанию.
     * @return Все возможные формы числительного, сгруппированные по написанию.
     */
    QSet<Word*> formAllForms() const override;

    /**
     * @brief Numeral::calculateFallacy
     * Рассчитывает ошибочность пары числительных.
     * Текущий объект класса сравнивается с передаваемым числительным.
     * @param[in] other - числительное для сравнения.
     * @return Ошибочность в виде целого числа от 0 до 100,
     * где 0 - числительные абсолютно идентичны.
     */
    int calculateFallacy(const WordForm& firstForm, const WordForm& secondForm) const override;

    /**
     * @brief Numeral::getType
     * Возвращает тип класса в виде строки.
     * @return Строка, состоящая из типа класса.
     */
    QString getType() const override;

    /**
     * @brief Numeral::wordsAreEqual
     * Сравнивает два числительных. Возвращает результат сравнения и
     * сообщение, содержащее все различия между числительными.
     * @param[in] otherWord - числительное, которое сравниваем с полем класса
     * @param[out] misstakeMessage - сообщение, содержащее все различия между словами.
     * @return true, если слова полностью равны;
     * false - если слова различаются хотя бы одним значением любого поля.
     */
    bool wordsAreEqual(const Word* otherWord, QString &misstakeMessage) const override;

    /**
     * @brief Numeral::clearAllWord
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
     * @brief setForm
     * Устанавливает указанное слово с его единственной формой в поля класса.
     * @param[in] newWord - новый текст числительного.
     * @param[in] newForm - новая форма числительного.
     */
    void setForm(const QString &newWord, const formOfNumeral &newForm);

    /**
     * @brief formCardinal
     * Образует количественную форму числительного.
     * @return Числительное в количественной форме.
     */
    Numeral formCardinal() const;

    /**
     * @brief formOrdinal
     * Образует порядковую форму числительного.
     * @param[in] numeral - числительное(текст) в количественной форме.
     * @return Числительное в порядковой форме.
     */
    Numeral formOrdinal(const QString &numeral) const;
};

#endif // NUMERAL_H
