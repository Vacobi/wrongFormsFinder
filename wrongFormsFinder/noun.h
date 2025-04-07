/**
 * @file Noun.h
 * @brief Класс Noun. Заголовки.
 */

#ifndef NOUN_H
#define NOUN_H

#include "Word.h"
#include "number.h"
#include "caseOfNounAndPron.h"

/**
 * @class Noun
 * @brief Описывает существительное и его формы.
 */
class Noun: public Word {
public:
    Noun();
    Noun(const QString &newWord);
    Noun(const QString &word, const unsigned int &firstForm, const unsigned int &secondForm,
            const unsigned int &thirdForm, const unsigned int &auxForAdj);
    Noun(const QString &word, const QSet<WordForm> &possibleFormsOfWord);

    /**
     * @brief Noun::formAllForms
     * Образует все формы существительного, группируя их по написанию.
     * @return Все возможные формы существительного, сгруппированные по написанию.
     */
    QSet<Word*> formAllForms() const override;

    /**
     * @brief Noun::calculateFallacy
     * Рассчитывает ошибочность пары существительныъ.
     * Текущий объект класса сравнивается с передаваемым существительными.
     * @param[in] other - существительное для сравнения.
     * @return Ошибочность в виде целого числа от 0 до 100,
     * где 0 - существительные абсолютно идентичны.
     */
    int calculateFallacy(const WordForm& firstForm, const WordForm& secondForm) const override;

    /**
     * @brief Noun::getType
     * Возвращает тип класса в виде строки.
     * @return Строка, состоящая из типа класса.
     */
    QString getType() const override;

    /**
     * @brief Noun::wordsAreEqual
     * Сравнивает два существительных. Возвращает результат сравнения и
     * сообщение, содержащее все различия между существительными.
     * @param[in] otherWord - существительное, которое сравниваем с полем класса
     * @param[out] misstakeMessage - сообщение, содержащее все различия между существительными.
     * @return true, если существительные полностью равны;
     * false - если существительные различаются хотя бы одним значением любого поля.
     */
    bool wordsAreEqual(const Word* otherWord, QString &misstakeMessage) const override;

    /**
     * @brief Noun::clearAllWord
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
     * Образует начальную форму существительного.
     * @param[out] countOfInitial - тип существительного.
     * plural - если существительное существует только во множественном числе,
     * uncountable - если оно неисчисляемое,
     * singular - существует как во сножественном, так и единственном числе.
     * @return Существительное начальной формы.
     */
    Noun formInitial(unsigned int &countOfInitial) const;

    /**
     * @brief formPlural
     * Образует начальную форму множественного числа существительного.
     * @param[in] noun
     * @return
     */
    Noun formPlural(const QString &noun) const;

    /**
     * @brief formCaseOfNoun
     * Образует притяжательный падеж существительного.
     * @param[in] noun - существительное.
     * @param[in] countOfNoun - число существительного.
     * @return Существительное притяжательного падежа в указанном числе.
     */
    Noun formCaseOfNoun(const QString &noun, const unsigned int &countOfNoun) const;

    /**
     * @brief nounIsException
     * Проверяет, является ли существительное икслючением.
     * @param[in] noun - существительное.
     * @param[out] forms - формы существительного, если оно является исключнем.
     * @return true - если существительное является исключением,
     * false - если нет.
     */
    bool nounIsException(const QString &noun, QStringList &forms) const;

    /**
     * @brief nounIsOnlyPlural
     * Проверяет, существует ли существительное только во множественной форме.
     * @param[in] noun - существительное.
     * @return true - если существует только во множественной форме,
     * false - иначе
     */
    bool nounIsOnlyPlural(const QString &noun) const;

    /**
     * @brief nounIsUncountable
     * Проверяет, является ли существительное неисчисляемым.
     * @param[in] noun - существительное.
     * @return true - если существительное неисчисляемое,
     * false - иначе.
     */
    bool nounIsUncountable(const QString &noun) const;

    /**
     * @brief readFileWithExceptionsNouns
     * Читает файл exceptionsNouns, результат записывает в поле класса
     * @return true - если записывание произошло, false - иначе
     */
    static bool readFileWithExceptionsNouns();

    /**
     * @brief readaFileWithOnlyPluralNouns
     * Читает файл onlyPluralNouns, результат записывает в поле класса
     * @return true - если записывание произошло, false - иначе
     */
    static bool readaFileWithOnlyPluralNouns();

    /**
     * @brief readFileWithUncountableNouns
     * Читает файл tensesLexems, результат записывает в поле класса
     * @return true - если записывание произошло, false - иначе
     */
    static bool readFileWithUncountableNouns();

    static QStringList exceptionsNouns;
    static QStringList onlyPluralNouns;
    static QStringList uncountableNouns;
};

#endif // NOUN_H
