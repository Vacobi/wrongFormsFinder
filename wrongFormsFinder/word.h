/**
 * @file Word.h
 * @brief Класс Word. Заголовки.
 */

#ifndef WORD_H
#define WORD_H

#include <QString>
#include <QSet>
#include <QHash>
#include <QFile>
#include <QTextStream>
#include "WordForm.h"
#include "postags.h"
#include "wn.h"
#include <iostream>

/**
 * @class Word
 * @brief Описывает слово и его формы.
 */
class Word {
protected:
    QString word;
    QSet<WordForm> possibleFormsOfWord;

public:
    Word();
    Word(const QString &word);
    Word(const QString &word, const unsigned int &firstForm, const unsigned int &secondForm,
         const unsigned int &thirdForm, const unsigned int &auxForAdj);
    Word(const QString &word, const QSet<WordForm> &possibleFormsOfWord);

    bool operator==(const Word &wordToCompare) const;

    bool operator==(const Word* &lhs) const;

    bool operator==(const Word* lhs) const;

    bool operator==(const QString &toCompare) const;

    bool operator<(const Word &other) const;

    void setWord(const QString &newWord);
    QString getWord() const;
    QSet<WordForm> getPossibleFormsOfWord() const;
    void setPossibleFormsOfWord(const QSet<WordForm> &newPossibleFormsOfWord);

    /**
     * @brief addWordForm
     * Добавляет новую форму к слову.
     * @param[in] newWordForm - новая форма слова.
     */
    void addWordForm(const WordForm &newWordForm);

    /**
     * @brief addWordForm
     * Добавляет новую форму к слову.
     * @param[in] newWordForm - новая форма слова.
     */
    void addWordForms(const QSet<WordForm> &newWordForms);

    /**
     * @brief Word::formAllForms
     * Образует все формы слова, группируя их по написанию.
     * @return Все возможные формы слова, сгруппированные по написанию.
     */
    virtual QSet<Word*> formAllForms() const;

    /**
     * @brief Word::calculateFallacy
     * Рассчитывает ошибочность пары слов.
     * Текущий объект класса сравнивается с передаваемым словом.
     * @param[in] other - слово для сравнения.
     * @return Ошибочность в виде целого числа от 0 до 100,
     * где 0 - слова абсолютно идентичны.
     */
    virtual int calculateFallacy(const WordForm& firstForm, const WordForm& secondForm) const;

    /**
     * @brief Word::getType
     * Возвращает тип класса в виде строки.
     * @return Строка, состоящая из типа класса.
     */
    virtual QString getType() const;

    /**
     * @brief Word::wordsAreEqual
     * Сравнивает два слова. Возвращает результат сравнения и
     * сообщение, содержащее все различия между словами. Является виртаульной функцией.
     * @param[in] otherWord - слово, которое сравниваем с полем класса
     * @param[out] misstakeMessage - сообщение, содержащее все различия между словами.
     * @return true, если слова полностью равны;
     * false - если слова различаются хотя бы одним значением любого поля.
     */
    virtual bool wordsAreEqual(const Word* otherWord, QString &misstakeMessage) const;

    /**
     * @brief Word::clearAllWord
     * Очищает все поля класса текущего объекта.
     */
    virtual void clearAllWord();

    /**
     * @brief getPosTag
     * Возвращает pos-тег, соответствующий текущему классу.
     * @return pos-тег, соответствующий текущему классу.
     */
    virtual posTags getPosTag() const;

    /**
     * @brief Word::setWordWithForms
     * Устанавливает текст слова и его формы в поля класса.
     * @param[in] newWord - новый текст слова.
     * @param[in] newPossibleFormsOfWord - новые формы слова.
     */
    void setWordWithForms(const QString &newWord, const QSet<WordForm> &newPossibleFormsOfWord);

    /**
     * @brief Word::hasMatchingWord
     * Определяет, имеется ли в переданном наборе искомое слово.
     * Поиск производится по тексту слова.
     * В случае нахождения совпадения, в переменную matchingWord
     * записывается найденное слово.
     * @param[in] setOfWordsToSearch - Набор слов, в котором производится поиск.
     * @param[out] matchingWord - Совпавшее слово со всеми его формами (если такое имеется).
     * @return true - если слово было найдено, иначе - false.
     */
    bool hasMatchingWord(const QSet<Word*> &wordToSearch, Word* &matchingWord) const;

    /**
     * @brief Word::wordsSame
     * Находит разницу между двумя словами: в тексте и формах.
     * @param[in] otherWord - слово, с которым сравниваем поле класса.
     * @param[out] misstakeMessage - сообщение, содержащее все различия между словами.
     * @return true, если слова полностью равны;
     * false - если слова различаются хотя бы одним значением любого поля.
     */
    bool wordsSame(const Word &otherWord, QString &misstakeMessage) const;

    /**
     * @brief Word::clearWordAndPossibleForms
     * Очищает текст и форму текущего объекта класса.
     */
    void clearWordAndPossibleForms();

    /**
     * @brief Word::countSyllables
     * Подсчитывает количество слогов в слове.
     * Входные данные - поле класса.
     * @return Количество слогов в слове.
     */
    int countSyllables() const;

    /**
     * @brief Word::mergeFormsForAllWords
     * Объединить формы слов, одинаковых по написанию
     * @param[in, out] words - множество слов для объединения
     */
    void mergeFormsForAllWords(QSet<Word*> &words) const;

    /**
     * @brief Word::currentWordAlreadyInSet
     * Проверяет, находится ли текущий слово (только его текст) в переданном множестве.
     * @param[in] set - множество, в котором выполняется поиск
     * @return true - если слово находится в множестве, false - иначе
     */
    bool currentWordAlreadyInSet(const QSet<Word*> &set) const;

    QSet<WordForm> definePossibleForms() const;

    bool fileWithDataExist(const QString &filename);
};

/**
 * @brief max
 * Вычисляет большее из двух целочисленных чисел.
 * @param[in] firstInteger - первое число.
 * @param[in] secondInteger - второе число.
 * @return Большее из этих двух чисел.
 */
int max(const int &firstInteger, const int &secondInteger);

/**
 * @brief isStaticVowel
 * Проверяет, является ли буква гласной.
 * Гласными считаются: a, e, i, o, u.
 * @param letter - буква.
 * @return true - если является гласной,
 * иначе - false.
 */
bool isStaticVowel(QChar letter);

inline uint qHash(const Word &key, uint seed)
{
    return qHashMulti (seed, key.getWord(), key.getPossibleFormsOfWord(), key.getType());
}

inline uint qHash(const Word* &key, uint seed)
{
    return qHashMulti (seed, key->getWord(), key->getPossibleFormsOfWord(), key->getType());
}

#endif // WORD_
