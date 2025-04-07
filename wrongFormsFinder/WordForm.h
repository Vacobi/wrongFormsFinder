/**
 * @file WordForm.h
 * @brief класс WordForm. Заголовки.
 */

#ifndef WORDFORM_H
#define WORDFORM_H

#include <QString>
#include <QHash>
#include "allFormsOfAllPosWords.h"

/**
 * @class WordForm
 * @brief Содержит формы слова.
 */
class WordForm {
private:
    unsigned int firstForm:8;
    unsigned int secondForm:8;
    unsigned int thirdForm:8;
    unsigned int auxForAdj:2;

public:
    WordForm();

    WordForm(const unsigned int &newFirstForm, const unsigned int &newSecondForm,
             const unsigned int &newThirdForm, const unsigned int &newAuxForAdj);

    bool operator==(const WordForm &toCompare) const;
    bool operator<(const WordForm &other) const;

    unsigned int getFirstForm() const;
    void setFirstForm(unsigned int newFirstForm);
    unsigned int getSecondForm() const;
    void setSecondForm(unsigned int newSecondForm);
    unsigned int getThirdForm() const;
    void setThirdForm(unsigned int newThirdForm);
    unsigned int getAuxForAdj() const;
    void setAuxForAdj(unsigned int newAuxForAdj);

    void setWordForm(const unsigned int &firstFormToSet,
                     const unsigned int &secondFormToSet,
                     const unsigned int &thirdFormToSet,
                     const unsigned int &auxForAdjToSet);

    void setWordForm(const WordForm &newWordForm);

    bool wordFormsAreEqual(const WordForm &wordFormToCompare, QString &misstakesInForm) const;

    QString getWordFormByStr() const;

    /**
     * @brief getFirstFormToDisplay
     * Получить первую форму в виде строки для отображения пользователю.
     * @return Первая форма в виде строки для отображения пользователю.
     */
    QString getFirstFormToDisplay() const;

    /**
     * @brief getSecondFormToDisplay
     * Получить вторую форму в виде строки для отображения пользователю.
     * @return Вторая форма в виде строки для отображения пользователю.
     */
    QString getSecondFormToDisplay() const;

    /**
     * @brief getThirdFormToDisplay
     * Получить третью форму в виде строки для отображения пользователю.
     * @return Третья форма в виде строки для отображения пользователю.
     */
    QString getThirdFormToDisplay() const;
};

QString getSpecifiedFormByStr(const unsigned int &form);

inline uint qHash(const WordForm &key, uint seed)
{
    return qHashMulti (seed, key.getFirstForm(), key.getSecondForm(), key.getThirdForm(), key.getAuxForAdj());
}

inline uint qHash(const WordForm &key)
{
    return qHashMulti (key.getFirstForm(), key.getSecondForm(), key.getThirdForm(), key.getAuxForAdj());
}

#endif // WORDFORM_H

//inline size_t qHash(const WordForm &key, size_t seed)
//{
//    return qHashMulti (seed, key.getFirstForm(), key.getSecondForm(), key.getThirdForm(), key.getAuxForAdj());

//}
