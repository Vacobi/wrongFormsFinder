/**
 * @file LinkedSentences.h
 * @brief класс LinkedSentences. Заголовки.
 */

#ifndef LINKEDSENTENCES_H
#define LINKEDSENTENCES_H

#include "Pair.h"

/**
 * @class LinkedSentences
 * @brief Класс для согласования предложений.
 */
class LinkedSentences {
    QList<QSet<Pair>> linkedSentences;
    int fallacy;
    int countOfLinkedWords;

public:
    LinkedSentences();

    void setLinkedSentences(const QList<QSet<Pair> > &newLinkedSentences);
    QList<QSet<Pair>> getLinkedSentences();
    int getFallacy() const;
    void setFallacy(int newFallacy);
    int getCountOfLinkedWords() const;
    void setCountOfLinkedWords(int newCountOfLinkedWords);

    /**
     * @brief linkSentences Согласует 2 предложение
     * @param[in] correctSentence - правильное предложение
     * @param[in] verifiedSentence - проверяемое предложение
     * @return В поле класса записываются все варинаты сочетания пар
     * с наименьшей ошибочностью и большим количеством согласованных слов
     * во втором предложении
     */
    void linkSentences(Sentence &correctSentence, Sentence &verifiedSentence);

    /**
     * @brief clearList
     * Очищает список пар.
     */
    void clearList();

    /**
     * @brief generateAllPairs Сгенерировать все пары слов первого предложения со словами второго предложения
     * @param[in] correctSentence Правильное предложение
     * @param[in] verifiedSentence Проверяемое предложение
     * @return
     */
    QList<Pair> generateAllPairs(const Sentence &correctSentence, const Sentence &verifiedSentence) const;

    /**
     * @brief recoursivePairsLink
     * Рекурсивное создание всех возможных вариантов согласования
     * @param[in][out] listOfPairs Список всех пар
     * @param[in][out] numberOfPair Номер текущей пары
     * @param[in][out] currentLinkedPairsList Текущий вариант согласования, представляющий собой набор пар
     * @param[in][out] bitCartForCorrectSentence Карта занятости слов в правильном предложении
     * @param[in][out] bitCartForVerifiedSentence Карта занятости слов в проверяемом предложении
     */
    void recoursivePairsLink(const QList<Pair> &listOfPairs, int numberOfPair, QList<Pair> &currentLinkedPairsList,
                             unsigned long long int bitCartForCorrectSentence, unsigned long long int bitCartForVerifiedSentence);

    /**
     * @brief createPairs
     * Создает все пары с переданной формой слова. (Один ко многим)
     * @param[in][out] currentPairList - список с парами.
     * @param[in] currentWordInCorrect - текущее слово из правильного предложения.
     * @param[in] wordsInVerified - Набор пар в проевряемом предложении.
     * @param[in] indexOfWordFromCorrect - индекс слова в правильном предложении.
     * @param[in] indexOfWordFromVerified - индекс слова в проверяемом предложении.
     */
    void createPairs(QList<Pair> &currentPairList, Word* &currentWordInCorrect,
                     QSet<Word*> &wordsInVerified, const int &indexOfWordFromCorrect, const int &indexOfWordFromVerified) const;

    /**
     * @brief processSolution
     * Обрабатывает текущее решение, определяя, помещать его в текущий набор или нет.
     * @param[in] currentLinkedPairsList - текущее решение.
     */
    void processSolution(const QList<Pair> &currentLinkedPairsList);

    /**
     * @brief getCurrentSetsMisstakes
     * Возвращает все ошибки в парах текущего согласования.
     * @param correctSentence - правильное предложение.
     * @param verifiedSentence - проверяемое предложение.
     * @return Строка, содержащая все ошибки в парах текущих согласований.
     */
    QString getCurrentSetsMisstakes(const Sentence &correctSentence, const Sentence &verifiedSentence);
};

/**
 * @brief resetBits
 * Обнуляет указанные биты в битовой карте.
 * @param[in] indexOfMainWord - индекс главного слова.
 * @param[in] indexesOfAuxiliaries - индексы вспомогательных
 * @param[in] bitCard - битовая карта.
 * @return битовая карта с обнуленными указанными битами.
 */
unsigned long long int resetBits(unsigned int indexOfMainWord, QList<int> indexesOfAuxiliaries, unsigned long long int bitCard);

/**
 * @brief setBits
 * Устанавливает указанные биты в битовой карте.
 * @param[in] indexOfMainWord - индекс главного слова.
 * @param[in] indexesOfAuxiliaries - индексы вспомогательных
 * @param[in] bitCard - битовая карта.
 * @return битовая карта с установленными указанными битами.
 */
unsigned long long int setBits(unsigned int indexOfMainWord, QList<int> indexesOfAuxiliaries, unsigned long long int bitCard);

/**
 * @brief bitsAreFree
 * Определяет, обнулены ли биты в указанных позициях.
 * @param[in] indexOfMainWord - индекс главного слова.
 * @param[in] indexesOfAuxiliaries - индексы вспомогательных
 * @param[in] bitCard - битовая карта.
 * @return true - если все биты обнулены, false - иначе.
 */
bool bitsAreFree(unsigned int indexOfMainWord, QList<int> indexesOfAuxiliaries, unsigned long long int bitCard);

/**
 * @brief bitSetted
 * Определяет, установлены ли биты в указанных позициях.
 * @param[in] indexOfMainWord - индекс главного слова.
 * @param[in] indexesOfAuxiliaries - индексы вспомогательных
 * @param[in] bitCard - битовая карта.
 * @return true - если все биты установлены, false - иначе.
 */
bool bitSetted(unsigned long long int value, unsigned long long int position);

/**
 * @brief setBit
 * Устанавливает бит в указанной позиции.
 * @param value - битовая карта.
 * @param position - позиция бита, который устанавливаем.
 * @return битовая карта с установленными битами.
 */
unsigned int setBit(const unsigned long long int value, unsigned long long int position);

/**
 * @brief resetBit
 * Обнуляет бит в указанной позиции.
 * @param value - битовая карта.
 * @param position - позиция бита, который обнуляем.
 * @return битовая карта с обнуленными битами.
 */
int resetBit(const unsigned long long int value, unsigned long long int position);

#endif // LINKEDSENTENCES_H
