//
//  jsoniter.c
//  JSONiter
//
//  Created by Seyyed Parsa Neshaei on 2/3/20.
//  Copyright © 2020 Seyyed Parsa Neshaei. All rights reserved.
//

#include "jsoniter.h"

#define MAX 10000

void splitStringWithDoubleQuotes(char str[1000000], char newString[1000][1000], int *countOfWords) {
    int j = 0, count = 0;
    for(int i = 0; i <= strlen(str); i++) {
        if (str[i] == '\0' || str[i] == '\"' || str[i] == '\n') {
            newString[count][j] = '\0';
            count += 1;
            j = 0;
        } else {
            newString[count][j] = str[i];
            j++;
        }
    }
    *countOfWords = count;
}

void splitStringWithOnlyCommas(char str[1000000], char newString[1000][1000], int *countOfWords) {
    int j = 0, count = 0;
    for(int i = 0; i <= strlen(str); i++) {
        if (str[i] == '\0' || str[i] == ',' || str[i] == '\n') {
            newString[count][j] = '\0';
            count += 1;
            j = 0;
        } else {
            newString[count][j] = str[i];
            j++;
        }
    }
    *countOfWords = count;
}

void splitString(char str[1000000], char newString[1000][1000], int *countOfWords) {
    int j = 0, count = 0;
    for(int i = 0; i <= strlen(str); i++) {
        if (str[i] == '\0' || str[i] == ' ' || str[i] == ',' || str[i] == '\n') {
            newString[count][j] = '\0';
            count += 1;
            j = 0;
        } else {
            newString[count][j] = str[i];
            j++;
        }
    }
    *countOfWords = count;
}

void findSubstring(char *destination, const char *source, int beg, int n)
{
    // extracts n characters from source string starting from beg index
    // and copy them into the destination string
    while (n > 0)
    {
        *destination = *(source + beg);
        
        destination++;
        source++;
        n--;
    }
    
    // null terminate destination string
    *destination = '\0';
}

int stringContainsWord(char *string, char *word) {
    int c = -1;
    char newString[1000][1000] = {};
    splitString(string, newString, &c);
    if (c < 0) {
        return 0;
    }
    for (int i = 0; i < c; i++) {
        if (strcmp(newString[i], word) == 0) {
            return 1;
        }
    }
    return 0;
}

int numberOfOccurencesOfWordInString(char *word, char *string) {
    int c = -1;
    int result = 0;
    char newString[1000][1000] = {};
    splitString(string, newString, &c);
    if (c < 0) {
        return 0;
    }
    for (int i = 0; i < c; i++) {
        if (strcmp(newString[i], word) == 0) {
            result += 1;
        }
    }
    return result;
}

void occurences(char *str, char *toSearch, int *numberOfOccurences, int occurencesArr[500]) {
    if (strlen(str) < strlen(toSearch)) {
        return;
    }
    *numberOfOccurences = 0;
    unsigned long stringLen = strlen(str), searchLen = strlen(toSearch);
    for (int i = 0; i <= stringLen - searchLen; i++) {
        int found = 1;
        for (int j = 0; j < searchLen; j++) {
            if (str[i + j] != toSearch[j]) {
                found = 0;
                break;
            }
        }
        if (found) {
            occurencesArr[*numberOfOccurences] = i;
            (*numberOfOccurences)++;
        }
    }
}

int getObjectValueOfKey(char *source, char *key, char *destination) { // returns -1 if error
    int numberOfOccurences = -1;
    int occurencesArr[1000] = {};
    char toSearch[200] = "\"";
    strcat(toSearch, key);
    strcat(toSearch, "\":");
    occurences(source, toSearch, &numberOfOccurences, occurencesArr);
    if (numberOfOccurences < 1) {
        return -1;
    }
    int pos = occurencesArr[0];
    unsigned long wholeLen = strlen(source);
    int numberOfOpenBraces = 0;
    int i;
    for (i = pos; i < wholeLen; i++) {
        if (source[i] == '{') {
            numberOfOpenBraces++;
        } else if (source[i] == '}') {
            numberOfOpenBraces--;
            if (numberOfOpenBraces == 0) {
                break;
            }
        }
    }
    findSubstring(destination, source, pos + 3 + (int)(strlen(key)), i - pos - 2 - (int)(strlen(key)));
    return 0;
}

int getStringValueOfKey(char *source, char *key, char *destination) { // returns -1 if error
    int numberOfOccurences = -1;
    int occurencesArr[1000] = {};
    char toSearch[200] = "\"";
    strcat(toSearch, key);
    strcat(toSearch, "\":");
    occurences(source, toSearch, &numberOfOccurences, occurencesArr);
    if (numberOfOccurences < 1) {
        return -1;
    }
    int pos = occurencesArr[0];
    unsigned long wholeLen = strlen(source);
    int i;
    for (i = pos; i < wholeLen - 1; i++) {
        if (source[i] == ',' && source[i + 1] == '\"') {
            break;
        }
    }
    findSubstring(destination, source, pos + 3 + (int)(strlen(key)), i - pos - 3 - (int)(strlen(key)));
    if (destination[strlen(destination) - 1] != '\"') {
        strcat(destination, "\"");
    }
    return 0;
}

int getRawValueOfKey(char *source, char *key, char *destination) { // returns -1 if error
    int numberOfOccurences = -1;
    int occurencesArr[1000] = {};
    char toSearch[200] = "\"";
    strcat(toSearch, key);
    strcat(toSearch, "\":");
    occurences(source, toSearch, &numberOfOccurences, occurencesArr);
    if (numberOfOccurences < 1) {
        return -1;
    }
    int pos = occurencesArr[0];
    unsigned long wholeLen = strlen(source);
    int i;
    for (i = pos; i < wholeLen - 1; i++) {
        if (source[i] == ',' && source[i + 1] == '\"') {
            break;
        }
    }
    findSubstring(destination, source, pos + 4 + (int)(strlen(key)), i - pos - 5 - (int)(strlen(key)));
    return 0;
}

int getArrayValueOfKey(char *source, char *key, char *destination) { // returns -1 if error
    int numberOfOccurences = -1;
    int occurencesArr[1000] = {};
    char toSearch[200] = "\"";
    strcat(toSearch, key);
    strcat(toSearch, "\":");
    occurences(source, toSearch, &numberOfOccurences, occurencesArr);
    if (numberOfOccurences < 1) {
        return -1;
    }
    int pos = occurencesArr[0];
    unsigned long wholeLen = strlen(source);
    int numberOfOpenBrackets = 0;
    int i;
    for (i = pos; i < wholeLen; i++) {
        if (source[i] == '[') {
            numberOfOpenBrackets++;
        } else if (source[i] == ']') {
            numberOfOpenBrackets--;
            if (numberOfOpenBrackets == 0) {
                break;
            }
        }
    }
    findSubstring(destination, source, pos + 3 + (int)(strlen(key)), i - pos - 2 - (int)(strlen(key)));
    return 0;
}

int getStringValueOfArray(char *source, int index, char *destination) {
    int c = -1;
    char newString[1000][1000] = {};
    splitStringWithDoubleQuotes(source, newString, &c);
    if (c < 1) {
        return -1;
    }
    int innerIndex = 0;
    for (int i = 1; i < c; i += 2) {
        if (innerIndex == index) {
            strcpy(destination, "\"");
            strcat(destination, newString[i]);
            strcat(destination, "\"");
            return 0;
        }
        innerIndex++;
    }
    return -1;
}

int getRawValueOfArray(char *source, int index, char *destination) {
    int c = -1;
    char newString[1000][1000] = {};
    splitStringWithDoubleQuotes(source, newString, &c);
    if (c < 1) {
        return -1;
    }
    int innerIndex = 0;
    for (int i = 1; i < c; i += 2) {
        if (innerIndex == index) {
            strcat(destination, newString[i]);
            return 0;
        }
        innerIndex++;
    }
    return -1;
}

void getObjectValueOfArray(char *source, int index, char *destination) {
    int commaBeforeStartIndex = -1, commaAfterEndIndex = -1, isInsideObjectNumber = 0;
    int currentIndex = 0;
    unsigned long len = strlen(source);
    for (int i = 0; i < len; i++) {
        if (index == 0 && source[i] == ',') {
            commaBeforeStartIndex = 0;
            commaAfterEndIndex = i;
            break;
        } else if (source[i] == ',' && commaBeforeStartIndex == -1 && isInsideObjectNumber == 0) {
            if (currentIndex + 1 == index) {
                commaBeforeStartIndex = i;
            }
            currentIndex++;
        } else if (source[i] == ',' && commaAfterEndIndex == -1 && isInsideObjectNumber == 0) {
            commaAfterEndIndex = i;
            break;
        } else if (source[i] == '{') {
            isInsideObjectNumber++;
        } else if (source[i] == '}') {
            isInsideObjectNumber--;
        }
    }
    if (commaAfterEndIndex == -1) {
        commaAfterEndIndex = (int)(strlen(source)) - 1;
    }
    findSubstring(destination, source, commaBeforeStartIndex + 1, commaAfterEndIndex - commaBeforeStartIndex - 1);
}

void getArrayValueOfArray(char *source, int index, char *destination) {
    int commaBeforeStartIndex = -1, commaAfterEndIndex = -1, isInsideArrayNumber = 0;
    int currentIndex = 0;
    unsigned long len = strlen(source);
    for (int i = 0; i < len; i++) {
        if (index == 0 && source[i] == ',') {
            commaBeforeStartIndex = 0;
            commaAfterEndIndex = i;
            break;
        } else if (source[i] == ',' && commaBeforeStartIndex == -1 && isInsideArrayNumber == 0) {
            if (currentIndex + 1 == index) {
                commaBeforeStartIndex = i;
            }
            currentIndex++;
        } else if (source[i] == ',' && commaAfterEndIndex == -1 && isInsideArrayNumber == 0) {
            commaAfterEndIndex = i;
            break;
        } else if (source[i] == '[') {
            isInsideArrayNumber++;
        } else if (source[i] == ']') {
            isInsideArrayNumber--;
        }
    }
    if (commaAfterEndIndex == -1) {
        commaAfterEndIndex = (int)(strlen(source)) - 1;
    }
    findSubstring(destination, source, commaBeforeStartIndex + 1, commaAfterEndIndex - commaBeforeStartIndex - 1);
}

void loopOverArrayForStrings(char *source, void (*eachElementCompletion)(int, char *)) {
    int c = -1;
    char newString[1000][1000] = {};
    findSubstring(source, source, 1, (int)(strlen(source)) - 2);
    splitStringWithOnlyCommas(source, newString, &c);
    for (int i = 0; i < c; i++) {
        eachElementCompletion(i, newString[i]);
    }
}
