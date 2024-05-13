#include "string_.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
void assertString(const char *expected, const char *got,
                  char const *fileName, char const *funcName,
                  int line) {
    if (strcmp_(expected, got)) {
        fprintf(stderr, "File %s\n", fileName);
        fprintf(stderr, "%s - failed on line %d\n", funcName, line);
        fprintf(stderr, "Expected: \"%s\"\n", expected);
        fprintf(stderr, "Got: \"%s\"\n\n", got);
    }
    else
        fprintf(stderr, "%s - OK\n", funcName);
}
size_t strlen_(char* begin) {
    char* end = begin;

    while (*end != '\0')
        end++;

    return end - begin;
}
char* find(char* begin, const char* end, int ch) {
    while (begin != end && *begin != ch)
        begin++;

    return begin;
}


char* findNonSpace(char* begin) {
    while (isspace(*begin))
        begin++;

    return begin;
}


char* findSpace(char* begin) {
    while (!isspace(*begin))
        begin++;

    return begin;
}


char* findNonSpaceReverse(char* rbegin, const char* rend) {
    while (isspace(*rbegin) && rbegin != rend)
        rbegin--;

    return rbegin;
}


int strcmp_(const char* left, const char* right) {
    while (*left++ == *right++);

    if (*left != 0 && *right != 0) return 0;

    return (*right > *left) ? 1 : -1;
}


int strAreEqual(char* left, char* right) {
    while (*left++ == *right++);

    if (*left != 0 && *right != 0) return 0;

    return (*right > *left) ? 1 : -1;
}


char* copy(const char* begin, const char* end, char* destination) {
    size_t length = end - begin;

    memcpy(destination, begin, CHAR_SIZE * length);

    return destination + length;
}


char* copyIf(char* begin, const char* end, char* destination, int (*f)(int)) {
    while(begin != end) {
        if (f(*begin))
            memcpy(destination++, begin, CHAR_SIZE);

        begin++;
    }

    return destination;
}


char* copyIfReverse(char* rbegin, const char* rend, char* destination, int (*f)(int)) {
    while(rbegin != rend - 1) {
        if (f(*rbegin))
            memcpy(destination++, rbegin, CHAR_SIZE);

        rbegin--;
    }

    return destination;
}
char* getEndOfString(char *begin) {
    char *end = begin;

    while (*end != '\0')
        end += sizeof(char);

    return end;
}


void removeNonLetters(char *string) {
    char *end_source = getEndOfString(string);
    char *destination = copyIf(string, end_source, string, isgraph);
    *destination = '\0';
}
void removeAdjacentEqualLetters(char *string) {
    char *end_source = getEndOfString(string);
    char prev = *string;
    char *destination = string;

    for (char *i = string + sizeof(char); i <= end_source; i += sizeof(char)) {
        if(*i != prev) {
            *destination = prev;
            destination += sizeof(char);
            prev = *i;
        }
    }

    *destination = *end_source;
    destination += sizeof(char);
    *destination = '\0';
}


int getWord(char *begin_search, WordDescriptor *word) {
    word->begin = findNonSpace(begin_search);
    if (*word->begin == '\0')
        return 0;

    word->end = findSpace(word->begin);

    return 1;
}
void digitToStart(WordDescriptor word) {
    char *end_string_buffer = copy(word.begin, word.end,
                                   _string_buffer);
    char *rec_position = copyIfReverse(end_string_buffer - 1,
                                       _string_buffer - 1,
                                       word.begin, isdigit);
    copyIf(_string_buffer, end_string_buffer, rec_position, isalpha);
}
int getWordReverse(char *begin_search, char *end_search, WordDescriptor *word) {
    word->begin = findNonSpaceReverse(begin_search, end_search);

    if (word->begin == begin_search)
        return 0;

    word->end = begin_search;

    return 1;
}
void digitToEnd(WordDescriptor word) {
    char *end_string_buffer = copy(word.begin, word.end,
                                   _string_buffer);
    char *rec_position = copyIf(_string_buffer, end_string_buffer - 1, word.begin, isalpha);
    copyIf(_string_buffer, end_string_buffer - 1, rec_position, isdigit);
    *word.end = ' ';
}


void numToSpace(char *source) {
    copy(source, getEndOfString(source), _string_buffer);
    char *end_source = getEndOfString(_string_buffer);
    char *rec_position = source;

    for (char *read_position = _string_buffer; read_position <= end_source; read_position += sizeof(char)) {
        if (isdigit(*read_position)) {
            int num = *read_position - '0' - 1;
            for (int j = 0; j <= num; j++) {
                *rec_position = ' ';
                rec_position += sizeof(char);
            }
        }
        else {
            *rec_position = *read_position;
            rec_position += sizeof(char);
        }
    }

    *rec_position = '\0';
}


int findWord(char *begin_search, WordDescriptor *pattern_word, WordDescriptor *res_word) {
    int amount = 0;
    int word_len = pattern_word->end - pattern_word->begin;
    char *search_position = pattern_word->begin;

    while (*begin_search != '\0') {
        if (*begin_search == *search_position) {
            amount++;
            search_position += sizeof(char);
        } else {
            amount = 0;
            search_position = pattern_word->begin;
        }

        if (amount == word_len) {
            res_word->begin = begin_search - word_len + 1;
            res_word->end = begin_search + 1;
            return 1;
        }
        begin_search += sizeof(char);
    }

    return 0;
}


void replace(char *source, char *w1, char *w2) {
    size_t w1_size = strlen_(w1);
    size_t w2_size = strlen_(w2);
    WordDescriptor word1 = {w1, w1 + w1_size * sizeof(char)};
    WordDescriptor word2 = {w2, w2 + w2_size * sizeof(char)};
    WordDescriptor wordRes;

    char *read_position, *rec_position;

    if (w1_size >= w2_size) {
        read_position = source;
        rec_position = source;
    }
    else {
        copy(source, getEndOfString(source), _string_buffer);
        read_position = _string_buffer;
        rec_position = source;
    }

    while (findWord(read_position, &word1, &wordRes)) {
        if (read_position != wordRes.begin)
            rec_position = copy(read_position, wordRes.begin - 1, rec_position);

        rec_position = copy(word2.begin, word2.end - 1, rec_position);
        read_position = wordRes.end;
    }

    char *read_position_end = getEndOfString(read_position);
    if (read_position >= read_position_end)
        read_position = copy(read_position, read_position_end, rec_position);

    *read_position = '\0';
}
void wordDescriptorToString(WordDescriptor word, char *destination) {
    copy(word.begin, word.end, destination);
}
void getBagOfWords(BagOfWords *bag, char *string) {
    WordDescriptor word_res;

    int i = 0;
    while (getWord(string, &word_res)) {
        bag->words[i++] = word_res;
        bag->size++;

        string = word_res.end;
    }
}
