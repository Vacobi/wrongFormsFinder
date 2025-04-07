/**
 * @file Pronoun.h
 * @brief Класс Pronoun. Заголовки.
 */

#ifndef PRONOUN_H
#define PRONOUN_H

#include "Word.h"
#include "number.h"
#include "caseOfNounAndPron.h"

/**
 * @class Pronoun
 * @brief Описывает местоимение и его формы.
 */
class Pronoun: public Word {
public:
    Pronoun();
    Pronoun(const QString &newWord);
    Pronoun(const QString &word, const unsigned int &firstForm, const unsigned int &secondForm,
            const unsigned int &thirdForm, const unsigned int &auxForAdj);
    Pronoun(const QString &word, const QSet<WordForm> &possibleFormsOfWord);

    /**
     * @brief Pronoun::formAllForms
     * Образует все формы местоимения, группируя их по написанию.
     * @return Все возможные формы местоимения, сгруппированные по написанию.
     */
    QSet<Word*> formAllForms() const override;

    /**
     * @brief Pronoun::calculateFallacy
     * Рассчитывает ошибочность пары местоимений.
     * Текущий объект класса сравнивается с передаваемым местоимением.
     * @param[in] other - местоимение для сравнения.
     * @return Ошибочность в виде целого числа от 0 до 100,
     * где 0 - местоимения абсолютно идентичны.
     */
    int calculateFallacy(const WordForm& firstForm, const WordForm& secondForm) const override;

    /**
     * @brief Pronoun::getType
     * Возвращает тип класса в виде строки.
     * @return Строка, состоящая из типа класса.
     */
    QString getType() const override;

    /**
     * @brief Pronoun::wordsAreEqual
     * Сравнивает два местоимения. Возвращает результат сравнения и
     * сообщение, содержащее все различия между местоимениями.
     * @param[in] otherWord - местоимение, которое сравниваем с полем класса
     * @param[out] misstakeMessage - сообщение, содержащее все различия между местоимениями.
     * @return true, если местоимения полностью равны;
     * false - если местоимения различаются хотя бы одним значением любого поля.
     */
    bool wordsAreEqual(const Word* otherWord, QString &misstakeMessage) const override;

    /**
     * @brief Pronoun::clearAllWord
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
     * @brief findPronoun
     * Ищет местоимение по написанию (по тексту в поле класса).
     * @return текстовый список всех форм местоимения.
     */
    QStringList findPronoun() const;

    /**
     * @brief formObjeciveNominative
     * Присваивает переданной строке форму объектного
     * местоимения именительного падежа и число.
     * @param[in] pron - текст местоимения.
     * @return объектное местоимение именительного падежа.
     */
    Pronoun formObjeciveNominative(const QString &pron) const;

    /**
     * @brief formObjeciveObjectiveForm
     * Присваивает переданной строке форму объектного
     * местоимения объектного падежа и число.
     * @param[in] pron - текст местоимения.
     * @return объектное местоимение объектного падежа.
     */
    Pronoun formObjeciveObjectiveForm(const QString &pron) const;

    /**
     * @brief formPossessiveMainForm
     * Присваивает переданной строке форму притяжательного
     * местоимения основной формы и число.
     * @param[in] pron - текст местоимения.
     * @return притяжательное местоимение основной формы.
     */
    Pronoun formPossessiveMainForm(const QString &pron) const;

    /**
     * @brief formPossessiveAbsoluteForm
     * Присваивает переданной строке форму притяжательного
     * местоимения абсолютной формы и число.
     * @param[in] pron - текст местоимения.
     * @return притяжательное местоимение абсолютной формы.
     */
    Pronoun formPossessiveAbsoluteForm(const QString &pron) const;
};

#endif // PRONOUN_H
