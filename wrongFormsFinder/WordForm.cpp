#include "WordForm.h"

WordForm::WordForm()
{
    this->firstForm = notSet;
    this->secondForm = notSet;
    this->thirdForm = notSet;
    this->auxForAdj = notSet;
}

WordForm::WordForm(const unsigned int &newFirstForm, const unsigned int &newSecondForm,
         const unsigned int &newThirdForm, const unsigned int &newAuxForAdj)
{
    this->firstForm = newFirstForm;
    this->secondForm = newSecondForm;
    this->thirdForm = newThirdForm;
    this->auxForAdj = newAuxForAdj;
}

bool WordForm::operator==(const WordForm &toCompare) const
{
    return (this->firstForm == toCompare.firstForm &&
            this->secondForm == toCompare.secondForm &&
            this->thirdForm == toCompare.thirdForm &&
            this->auxForAdj == toCompare.auxForAdj);
}

bool WordForm::operator<(const WordForm &other) const
{
    return (this->firstForm < other.firstForm);
}

unsigned int WordForm::getSecondForm() const
{
    return secondForm;
}

void WordForm::setSecondForm(unsigned int newSecondForm)
{
    secondForm = newSecondForm;
}

unsigned int WordForm::getThirdForm() const
{
    return thirdForm;
}

void WordForm::setThirdForm(unsigned int newThirdForm)
{
    thirdForm = newThirdForm;
}

unsigned int WordForm::getAuxForAdj() const
{
    return auxForAdj;
}

void WordForm::setAuxForAdj(unsigned int newAuxForAdj)
{
    auxForAdj = newAuxForAdj;
}

void WordForm::setWordForm(const unsigned int &firstFormToSet, const unsigned int &secondFormToSet, const unsigned int &thirdFormToSet, const unsigned int &auxForAdjToSet)
{
    this->firstForm = firstFormToSet;
    this->secondForm = secondFormToSet;
    this->thirdForm = thirdFormToSet;
    this->auxForAdj = auxForAdjToSet;
}

void WordForm::setWordForm(const WordForm &newWordForm)
{
    this->firstForm = newWordForm.firstForm;
    this->secondForm = newWordForm.secondForm;
    this->thirdForm = newWordForm.thirdForm;
    this->auxForAdj = newWordForm.auxForAdj;
}

unsigned int WordForm::getFirstForm() const
{
    return firstForm;
}

void WordForm::setFirstForm(unsigned int newFirstForm)
{
    firstForm = newFirstForm;
}

bool WordForm::wordFormsAreEqual(const WordForm &wordFormToCompare, QString &misstakeOfForm) const
{
    misstakeOfForm = "";

    if (this->firstForm != wordFormToCompare.firstForm)
    {
        misstakeOfForm += " wrong first form. Expected: " + getSpecifiedFormByStr(this->firstForm) +
                          " real: " + getSpecifiedFormByStr(wordFormToCompare.firstForm) + "; ";
    }

    if (this->secondForm != wordFormToCompare.secondForm)
    {
        misstakeOfForm += " wrong second form. Expected: " + getSpecifiedFormByStr(this->secondForm) +
                          " real: " + getSpecifiedFormByStr(wordFormToCompare.secondForm) + "; ";
    }

    if (this->thirdForm != wordFormToCompare.thirdForm)
    {
        misstakeOfForm += " wrong third form. Expected: " + getSpecifiedFormByStr(this->thirdForm) +
                          " real: " + getSpecifiedFormByStr(wordFormToCompare.thirdForm) + "; ";
    }

    if (this->auxForAdj != wordFormToCompare.auxForAdj)
    {
        misstakeOfForm += " wrong aux for adjective form. Expected: " + getSpecifiedFormByStr(this->auxForAdj) +
                          " real: " + getSpecifiedFormByStr(wordFormToCompare.auxForAdj) + "; ";
    }

    if (misstakeOfForm == "")
        return true;
    else
        return false;
}

QString WordForm::getWordFormByStr() const
{
    return ("first form: " + getSpecifiedFormByStr(firstForm) +
            ", second form: " + getSpecifiedFormByStr(secondForm) +
            ", third form: " + getSpecifiedFormByStr(thirdForm) +
            ", aux for adjective: " + getSpecifiedFormByStr(auxForAdj) + "; ");
}

QString getSpecifiedFormToDisplay(const unsigned int &form)
{
    switch (form)
    {
    case notSet:                  return "Не указана";
    case presentSimple:           return "Present simple";
    case presentCont:             return "Present continuous";
    case pastSimple:              return "Past simple";
    case pastCont:                return "Past continuous";
    case presentPerf:             return "Present perfect";
    case presentPerfCont:         return "Present perfect continuous";
    case pastPerf:                return "Past perfect";
    case pastPerfCont:            return "Past perfect continuous";
    case futureSimple:            return "Future simple";
    case futureCont:              return "Future continuous";
    case futurePerfSimple:        return "Future perfect simple";
    case futurePerfCont:          return "Future perfect continuous";
    case futureSimpleInThePast:   return "Future simple in the past";
    case futureContInThePast:     return "Future continuous in the past";
    case futurePerfInThePast:     return "Future perfect in the past";
    case futurePerfContInThePast: return "Future perfect continuous in the past";
    case undefined:               return "Невозможно определить время";
    case infinitive:              return "Начальная форма";
    case first:                   return "Первого лица";
    case third:                   return "Третьего лица";
    case notThird:                return "Не третьего лица";
    case notFirst:                return "Не первого лица";
    case singular:                return "Единственного числа";
    case plural:                  return "Множественного числа";
    case uncountable:             return "Неисчисляемого";
    case objective:               return "Объектного падежа";
    case possessive:              return "Притяжательного падежа";
    case nominative:              return "Именительного падежа";
    case objectivePron:           return "Объектного падежа местоимения";
    case mainForm:                return "Главной формы";
    case absoluteForm:            return "Абсолютной формы";
    case cardinal:                return "Количественное";
    case ordinal:                 return "Порядковое";
    case positive:                return "Положительной степени";
    case comparative:             return "Сравнительной степени";
    case superlative:             return "Превосходной степени";
    default:                      return "Невозможно определить";
    }
}

QString WordForm::getFirstFormToDisplay() const
{
    return getSpecifiedFormToDisplay(this->firstForm);
}

QString WordForm::getSecondFormToDisplay() const
{
    return getSpecifiedFormToDisplay(this->secondForm);
}

QString WordForm::getThirdFormToDisplay() const
{
    return getSpecifiedFormToDisplay(this->thirdForm);
}

QString getSpecifiedFormByStr(const unsigned int &form)
{
    switch (form)
    {
    case notSet:                  return "not set";
    case more:                    return "more";
    case most:                    return "most";
    case notNeed:                 return "not need";
    case presentSimple:           return "present simple";
    case presentCont:             return "present continuous";
    case pastSimple:              return "past simple";
    case pastCont:                return "past continuous";
    case presentPerf:             return "present perfect";
    case presentPerfCont:         return "present perfect continuous";
    case pastPerf:                return "past perfect";
    case pastPerfCont:            return "past perfect continuous";
    case futureSimple:            return "future simple";
    case futureCont:              return "future continuous";
    case futurePerfSimple:        return "future perfect simple";
    case futurePerfCont:          return "future perfect continuous";
    case futureSimpleInThePast:   return "future simple in the past";
    case futureContInThePast:     return "future continuous in the past";
    case futurePerfInThePast:     return "future perfect in the past";
    case futurePerfContInThePast: return "future perfect continuous in the past";
    case undefined:               return "undefined";
    case infinitive:              return "infinitive";
    case verbBeAreAmForm:         return "verb be are am form";
    case present3P:               return "present third person";
    case past:                    return "past";
    case preterite:               return "preterite";
    case pastParticiple:          return "pastParticiple";
    case presentParticiple:       return "presentParticiple";
    case first:                   return "first";
    case third:                   return "third";
    case notThird:                return "not third";
    case notFirst:                return "not first";
    case singular:                return "singular";
    case plural:                  return "plural";
    case uncountable:             return "uncountable";
    case objective:               return "objective";
    case possessive:              return "possessive";
    case nominative:              return "nominative";
    case objectivePron:           return "objective form";
    case mainForm:                return "mainForm";
    case absoluteForm:            return "absoluteForm";
    case cardinal:                return "cardinal";
    case ordinal:                 return "ordinal";
    case positive:                return "positive";
    case comparative:             return "comparative";
    case superlative:             return "superlative";
    default:                      return "not defined";
    }
}
