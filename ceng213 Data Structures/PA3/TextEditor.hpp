#ifndef TEXTEDITOR_HPP
#define TEXTEDITOR_HPP

#include <iostream>

#include "HashTable.hpp"

// DO NOT CHANGE THIS FILE.

class TextEditor {
public:
    TextEditor(const std::string & documentName, const std::string & dictionaryName);

    std::vector<int> findWord(const std::string & word);

    void findAndReplaceWord(const std::string & word, const std::string & replacement);

    bool spellCheck(const std::string & word);

    std::vector<std::string> getSuggestedWords(const std::string & word);

    friend std::ostream & operator<<(std::ostream & os, const TextEditor & editor);

private:
    std::string text;

    HashTable<int> dictionary;
};


#endif //TEXTEDITOR_HPP
