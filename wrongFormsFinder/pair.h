/**
 * @file Pair.h
 * @brief класс Pair. Заголовки.
 */

#ifndef PAIR_H
#define PAIR_H

#include "Sentence.h"

#define replaceItem 0
#define addItem 1
#define skipItem 2
#define pairsNotMatch 3

/**
 * @class Pair
 * @brief Класс для хранения пары слов и работе с ней.
 */
class Pair {
    int wordIndexFromCorrectSentence;
    QList<int> indexesOfAuxiliariesInCorrect;
    WordForm wordFormFromCorrectSentence;
    int wordIndexFromVerifiedSentence;
    QList<int> indexesOfAuxiliariesInVerified;
    WordForm wordFormFromVerifiedSentence;
    posTags posTag;
    int degreeOfFallacy;

public:
    Pair();

    Pair(const int &newWordIndexFromCorrectSentence, const QList<int> &NewIndexesOfAuxiliariesInCorrect,
         const WordForm &newWordFormFromCorrectSentence, const int &newWordIndexFromVerifiedSentence,
         const QList<int> &newIndexesOfAuxiliariesInVerified, const WordForm &newWordFormFromVerifiedSentence,
         const posTags &newPosTag, const int &newDegreeOfFallacy);

    Pair(Word* &wordFromCorrect, Word* &wordFromVerified,
         const WordForm &formFromCorrect, const WordForm &formFromVerified,
         const int &indexOfCorrect, const int &indexOfVerified);

    Pair(Word* &wordFromCorrect, Word* &wordFromVerified,
         const int &indexOfCorrect, const int &indexOfVerified);

    bool operator==(const Pair &pairToCompare) const;

    int getWordIndexFromCorrectSentence() const;
    void setWordIndexFromCorrectSentence(int newWordIndexFromCorrectSentence);
    QList<int> getIndexesOfAuxiliariesInCorrect() const;
    void setIndexesOfAuxiliariesInCorrect(const QList<int> &newIndexesOfAuxiliariesInCorrect);
    WordForm getWordFormFromCorrectSentence() const;
    void setWordFormFromCorrectSentence(const WordForm &newWordFormFromCorrectSentence);
    int getWordIndexFromVerifiedSentence() const;
    void setWordIndexFromVerifiedSentence(int newWordIndexFromVerifiedSentence);
    QList<int> getIndexesOfAuxiliariesInVerified() const;
    void setIndexesOfAuxiliariesInVerified(const QList<int> &newIndexesOfAuxiliariesInVerified);
    WordForm getWordFormFromVerifiedSentence() const;
    void setWordFormFromVerifiedSentence(const WordForm &newWordFormFromVerifiedSentence);
    posTags getPosTag() const;
    void setPosTag(posTags newPosTag);
    int getDegreeOfFallacy() const;
    void setDegreeOfFallacy(int newDegreeOfFallacy);

    /**
     * @brief setAllParameters
     * Устанавливает все поля данного объекта
     * @param[in] newWordIndexFromCorrectSentence
     * @param[in] newIndexesOfAuxiliariesInCorrect
     * @param[in] newWordFormFromCorrectSentence
     * @param[in] newWordIndexFromVerifiedSentence
     * @param[in] newIndexesOfAuxiliariesInVerified
     * @param[in] newWordFormFromVerifiedSentence
     * @param[in] newPosTag
     * @param[in] newDegreeOfFallacy
     */
    void setAllParameters(const int &newWordIndexFromCorrectSentence, const QList<int> &newIndexesOfAuxiliariesInCorrect,
                          const WordForm &newWordFormFromCorrectSentence, const int &newWordIndexFromVerifiedSentence,
                          const QList<int> &newIndexesOfAuxiliariesInVerified, const WordForm &newWordFormFromVerifiedSentence,
                          const posTags &newPosTag, const int &newDegreeOfFallacy);

    /**
     * @brief getIndexesOfAuxiliariesInCorrectByStr
     * Возвращает индексы вспомогательных слов правильного предложения в виде строки.
     * @return Индексы вспомогательных слов правильного предложения в виде строки.
     */
    QString getIndexesOfAuxiliariesInCorrectByStr() const;

    /**
     * @brief getIndexesOfAuxiliariesInVerifiedByStr
     * Возвращает индексы вспомогательных слов проверяемого предложения в виде строки.
     * @return Индексы вспомогательных слов проверяемого предложения в виде строки.
     */
    QString getIndexesOfAuxiliariesInVerifiedByStr() const;

    /**
     * @brief findMatchingPair
     * Выполняет поиск соответствущей пары в наборе пар.
     * Поиск выполняется по индексу главного слова.
     * @param pairsSet - набор пар.
     * @param matchingPair - пара, которую ищем.
     * @return true, если пара найдена, false - иначе
     */
    bool findMatchingPair(const QSet<Pair> &pairsSet, Pair &matchingPair) const;

    /**
     * @brief findMatchingPair
     * Выполняет поиск соответствущей пары в списке пар.
     * @param pairsList - список пар.
     * @param matchingPair - пара, которую ищем.
     * @return true, если пара найдена, false - иначе.
     */
    bool findMatchingPair(const QList<Pair> &pairsList, Pair &matchingPair) const;

    /**
     * @brief areEqual
     * Сравнивает текущую пару с прееданной.
     * Разница между ними записывается в pairsDifference.
     * @param pairToCompare - пара для сравнения.
     * @param pairsDifference - разница между парами.
     * @return true - если пары совпадают, false - иначе.
     */
    bool areEqual(const Pair &pairToCompare, QString &pairsDifference) const;

    /**
     * @brief pairMustBeInList
     * Проверяет, должна ли пара находиться в списке согласований.
     * Для этого сравниваем текущущю пару из списка с переданной.
     * @param other - пара из списка.
     * @return replaceItem - если необходимо заменить пару из списка данной,
     * addItem - если пару необходимо добавить к текущему списку пар,
     * skipItem - если пропускаем данную пару,
     * pairsNotMatch - пары не совпадают.
     */
    int pairMustBeInList(const Pair &other) const;

    /**
     * @brief getPairMisstakeMessage
     * Формирует сообщения об ошибке между парами.
     * @param correctSentence - правильное предложение.
     * @param verifiedSentence - проверяемое предложение.
     * @return строка со всеми ошибками данной пары.
     */
    QString getPairMisstakeMessage(const Sentence &correctSentence, const Sentence &verifiedSentence) const;

    /**
     * @brief getVerbPairMisstake
     * Формирует сообщения об ошибке между парой глаголов.
     * @param correctSentence
     * @param verifiedSentence
     * @return
     */
    QString getVerbPairMisstake(const Sentence &correctSentence, const Sentence &verifiedSentence) const;

    /**
     * @brief getAdjectivePairMisstake
     * Формирует сообщения об ошибке между парой прилагательных.
     * @param correctSentence
     * @param verifiedSentence
     * @return
     */
    QString getAdjectivePairMisstake(const Sentence &correctSentence, const Sentence &verifiedSentence) const;

    /**
     * @brief getPronounPairMisstake
     * Формирует сообщения об ошибке между парой местоимений.
     * @param correctSentence
     * @param verifiedSentence
     * @return
     */
    QString getPronounPairMisstake(const Sentence &correctSentence, const Sentence &verifiedSentence) const;

    /**
     * @brief getNounPairMisstake
     * Формирует сообщения об ошибке между парой существительных.
     * @param correctSentence
     * @param verifiedSentence
     * @return
     */
    QString getNounPairMisstake(const Sentence &correctSentence, const Sentence &verifiedSentence) const;

    /**
     * @brief getNumeralPairMisstake
     * Формирует сообщения об ошибке между парой числительных.
     * @param correctSentence
     * @param verifiedSentence
     * @return
     */
    QString getNumeralPairMisstake(const Sentence &correctSentence, const Sentence &verifiedSentence) const;
};

// Перегрузка функции qHash для QSet
inline uint qHash(const Pair &key, uint seed)
{
    return qHashMulti (seed, key.getWordIndexFromCorrectSentence(), key.getWordIndexFromVerifiedSentence(),
                        key.getIndexesOfAuxiliariesInCorrect(), key.getWordIndexFromVerifiedSentence(),
                        key.getDegreeOfFallacy(), key.getPosTag());
}

#endif // PAIR_H
