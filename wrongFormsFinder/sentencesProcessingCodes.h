/**
 * @file sentencesProcessingCodes.h
 * @brief Содержит перечисление sentencesProcessingCodes.
 */

#ifndef SENTENCESPROCESSINGCODES_H
#define SENTENCESPROCESSINGCODES_H

enum sentencesProcessingCodes {
    sentenceSuccessfulProcessed,
    fewerWordsThanTags,
    fewerTagsThanWords,
    incorrectPosTag,
    zeroWordsInSentence
};

#endif // SENTENCESPROCESSINGCODES_H
