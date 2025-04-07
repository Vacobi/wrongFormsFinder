/**
 * @file Verb.h
 * @brief Класс Verb. Заголовки.
 */

#ifndef VERB_H
#define VERB_H

#include "Word.h"
#include "wn.h"

/**
 * @class Verb
 * @brief Описывает глагол и его формы.
 */
class Verb: public Word {
private:
    QList<int> indexesOfAuxiliaries;

public:
    Verb();
    Verb(const QString &newWord);
    Verb(const QString &word, const unsigned int &firstForm, const unsigned int &secondForm,
            const unsigned int &thirdForm, const unsigned int &auxForAdj);
    Verb(const QString &word, const QSet<WordForm> &possibleFormsOfWord, const QList<int> &indexesOfAuxiliaries);

    Verb(const Verb &v);

    bool operator==(const Verb &wordToCompare) const;

    bool operator==(const Verb* lhs) const {
        return this == lhs;
    }

    bool operator<(const Verb &other) const;

    QList<int> getIndexesOfAuxiliaries() const;
    void setIndexesOfAuxiliaries(const QList<int> &newIndexesOfAuxiliaries);

    /**
     * @brief Verb::formAllForms
     * Образует все формы глагола, группируя их по написанию.
     * @return Все возможные формы глагола, сгруппированные по написанию.
     */
    QSet<Word*> formAllForms() const override;

    /**
     * @brief Verb::calculateFallacy
     * Рассчитывает ошибочность пары глаголов.
     * Текущий объект класса сравнивается с передаваемым глаголом.
     * @param[in] other - глагол для сравнения.
     * @return Ошибочность в виде целого числа от 0 до 100,
     * где 0 - глаголы абсолютно идентичны.
     */
    int calculateFallacy(const WordForm& firstForm, const WordForm& secondForm) const override;

    /**
     * @brief Verb::getType
     * Возвращает тип класса в виде строки.
     * @return Строка, состоящая из типа класса.
     */
    QString getType() const override;

    /**
     * @brief Verb::wordsAreEqual
     * Сравнивает два глагола. Возвращает результат сравнения и
     * сообщение, содержащее все различия между глаголами.
     * @param[in] otherWord - глагол, которой сравниваем с полем класса.
     * @param[out] misstakeMessage - сообщение, содержащее все различия между глаголами.
     * @return true, если глаголы полностью равны;
     * false - если глаголы различаются хотя бы одним значением любого поля.
     */
    bool wordsAreEqual(const Word* otherWord, QString &misstakeMessage) const override;

    /**
     * @brief Verb::clearAllWord
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
     * @brief formInfinitive
     * Присваивает переданному глаголу (строке) форму инфинитива.
     * @param[in] verb - глагол (строка).
     * @return глагол в форме инфинитива.
     */
    Verb formInfinitive(const QString &verb) const;

    /**
     * @brief verbIsIrregular
     * Проверяет, является ли глагол неправильным.
     * @param[out] formsOfVerb - все формы неправильного глагола.
     * @return true - если глагол неправильный, false - правильный.
     */
    bool verbIsIrregular(QStringList &formsOfVerb) const;

    /**
     * @brief formAllFormsOfVerbBe
     * Образует все формы глагола Be.
     * @return Все формы глагола Be.
     */
    QSet<Word*> formAllFormsOfVerbBe() const;

    /**
     * @brief formThirdPersonVerb
     * Присваивает переданному глаголу (строке) форму третьего лица глагола.
     * @param[in] verb - глагол.
     * @return Глагол в форме третьего лица.
     */
    Verb formThirdPersonVerb(const QString &verb) const;

    /**
     * @brief formPreterite
     * Присваивает переданному глаголу (строке) форму preterite.
     * @param[in] verb - глагол.
     * @return Глагол в форме preterite.
     */
    Verb formPreterite(const QString &verb) const;

    /**
     * @brief formPastParticiple
     * Присваивает переданному глаголу (строке) форму past participle.
     * @param[in] verb - Глагол.
     * @return Глагол в форме past participle.
     */
    Verb formPastParticiple(const QString &verb) const;

    /**
     * @brief formPastRightVerb
     * Присваивает переданному глаголу (строке) форму прошедшего времени правильного глагола.
     * @param[in] verb - глагол.
     * @return Правильный глагол в форме прошедшего времени.
     */
    Verb formPastRightVerb(const QString &verb) const;

    /**
     * @brief formPresentParticiple
     * Присваивает переданному глаголу (строке) форму present participle.
     * @param[in] verb - Глагол.
     * @return Глагол в форме present participle.
     */
    Verb formPresentParticiple(const QString &verb) const;

    /**
     * @brief formAllIrregularVerbForms
     * Образует все формы неправильного глагола.
     * @param[in] verb - начальная форма глагола.
     * @return Список всех форм неправильного глагола.
     */
    QSet<Word*> formAllIrregularVerbForms(const QString &verb) const;

    /**
     * @brief formAllRegularVerbForms
     * Образует все формы правильного глагола.
     * @param[in] verb - начальная форма глагола.
     * @return Список всех форм правильного глагола.
     */
    QSet<Word*> formAllRegularVerbForms(const QString &verb) const;

    /**
     * @brief setVerbWithForms
     * Присваивает объекту класса текст, формы и индексы вспомогательных слов.
     * @param[in] newWord - новое слово;
     * @param[in] newPossibleFormsOfWord - новые формы;
     * @param[in] newAuxiliaries - индексы новых вспомогательных;
     */
    void setVerbWithForms(const QString &newWord, const QSet<WordForm> &newPossibleFormsOfWord,
                          const QList<int> &newAuxiliaries);

    /**
     * @brief readFileWithIrregularVerbs
     * Читает файл irrregularVerbs, результат записывает в поле класса
     * @return true - если записывание произошло, false - иначе
     */
    static bool readFileWithIrregularVerbs();

    /**
     * @brief readFileWithVerbLexems
     * Читает файл tensesLexems, результат записывает в поле класса
     * @return true - если записывание произошло, false - иначе
     */
    static bool readFileWithVerbLexems();

    static QStringList irregularVerbs;
    static QStringList verbLexems;
};

inline uint qHash(const Verb* key, uint seed = 0) {
    return qHashMulti (seed, key->getWord(), key->getPossibleFormsOfWord());
}

#endif // VERB_H
