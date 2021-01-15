#include "TextEditor.hpp"

#include <fstream>
#include <cmath>

TextEditor::TextEditor(const std::string & documentName, const std::string & dictionaryName) {
    // First, reading the document and saving the whole content as the string "text".
    std::ifstream documentFile(documentName.c_str(), std::ifstream::in);

    text.assign(std::istreambuf_iterator<char>(documentFile), std::istreambuf_iterator<char>());

    documentFile.close();

    // Then reading the dictionary word by word.
    std::ifstream dictionaryFile(dictionaryName.c_str(), std::ifstream::in);

    std::string word;

    for (int i = 1; (dictionaryFile >> word); ++i) {
        // Inserting words to the "dictionary" hash table one by one.
        dictionary.insert(word, i);
    }

    dictionaryFile.close();
}

std::vector<int> TextEditor::findWord(const std::string & word) {
    
    //std::cout<<"find " << std::endl;
    
    std::vector<int> list;
    int len_word = word.size(), len_text = text.size();
    
    std::string substr;
    
    int value_word=0, value_temp=0;
    
    //Calculate the desired hash value
    for(int i=0;i<len_word;i++){
        value_word = (value_word + (word[i]-'a')*word[i] )% 12853 ;
    }
    
    // check the first
    for(int j =0 ; j<len_word;j++){
        value_temp = (value_temp + (text[j]-'a')*text[j]) % 12853;
    }
    
    if(value_temp == value_word){
        if(text.substr(0,len_word)==word){
            list.push_back(0);
        }
    }
    

    int i = 1;
    while(i<len_text - len_word){
        
        //check the rest
        value_temp = (value_temp + (text[i+len_word-1]-'a')*text[i+len_word-1] - (text[i-1]-'a')*text[i-1]) %12853 ;   
        
        if(value_temp == value_word){
            if(text.substr(i,len_word)==word){
                list.push_back(i);
            }
        }
        i++;
    }
    
    return list;
    
}

void TextEditor::findAndReplaceWord(const std::string & word, const std::string &replacement) {
   
   
   
    std::vector<int> list;
    
    list = findWord(word);

    if(!list.empty()){
        
        int lenght = list.size();
        int len_word = word.size();
        
        for(int i=lenght-1;i>=0;i--){
            
            text.replace(list[i],len_word,replacement);
        }
        
        
    }
}

bool TextEditor::spellCheck(const std::string & word) {
    
    
    
    if(dictionary.contains(word)) return true;
    else return false;
}

std::vector<std::string> TextEditor::getSuggestedWords(const std::string &word) {
    
    
    
    int lenght = word.size() ,i,j;
    char h,c;
    bool same;
    
    HashTable<int> suggested;
    
    std::vector<std::string> list;

    std::string suggest = word;
    
    
    
    if(!spellCheck(word)){
    
        for(i=0; i<lenght ;i++){
            
            suggest = word;
            
            for(h = 'a';h <='z' ; h++){
                
                suggest[i] = h;
                
                 bool not_suggested = suggested.insert(suggest,6);
                            
                            if(not_suggested && spellCheck(suggest)){
                                
                                list.push_back(suggest);
                            }
                            
                
                    for(j=i+1; j<lenght; j++ ){
                        
        
                        for(c='a'; c<='z' ; c++){
                           
                                
                                suggest[j] = c;
                                
                                not_suggested = suggested.insert(suggest,6);
                                
                                if(not_suggested && spellCheck(suggest)){
                                    
                                    list.push_back(suggest);
                                    
                                }
                            
                            
                            
                        }
                        suggest[j] = word[j];
                    }
                
            }
            
        }
        
        
        
        int list_size = list.size();
        std::string temp;
        
        for(i=0;i<list_size-1;i++){
            
            for(j=0; j<list_size-i-1; j++){
                
                if(list[j] > list[j+1]) {
                    
                    temp = list[j];
                    list[j] = list[j+1];
                    list[j+1] = temp;
                }
            }
        }

   
    }
    else{
        
        list.push_back(word);
    }
    return list;
}

std::ostream & operator<<(std::ostream & os, const TextEditor & editor) {
    os << editor.text;

    return os;
}
