#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include <iostream>
#include <vector>

#include "HashTableItem.hpp"

template <class T>
class HashTable {
public: // DO NOT CHANGE THIS PART.
    HashTable();

    bool insert(const std::string & key, const T & value);

    bool remove(const std::string & key);

    bool contains(const std::string & key) const;

    const HashTableItem<T> * find(const std::string & key) const;

    int getTableSize() const;

    int getNumberOfItems() const;

    void print();

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.
    int hashFunction(const std::string & key) const;

    void rehash();

    
    void insert_nearest_free_spot(const std::string & key, const T & value){

        int index = hashFunction(key);
        // Find nearest free spot
        while( table[index].active && !table[index].deleted ){
            index++;

            if(index==tableSize){
                index = 0;
            }
        }

        //insert the key-value in there
        table[index].key = key;
        table[index].value = value;
        table[index].deleted = false;
        table[index].active = true;

        //increment the number of items
        numberOfItems++;
    };

private: // DO NOT CHANGE THIS PART.
    std::vector<HashTableItem<T> > table;

    int tableSize;
    int numberOfItems;
};

template <class T>
HashTable<T>::HashTable() {
    
    tableSize = 2;
    numberOfItems= 0;
    table.resize(2); 
}

template <class T>
bool HashTable<T>::insert(const std::string & key, const T & value) {
    
    
    //check if rehashing is needed 
    if(numberOfItems*2 >= tableSize){
        rehash();
    }
    
    
    
    //check if key-value is already in hashtable
    if(find(key)){
        return false;
    }
    else{
        insert_nearest_free_spot(key,value);
        return true;
    }
        
}

template <class T>
bool HashTable<T>::remove(const std::string & key) {
    
    
    //check if key-value is in table
    if(!contains(key)){
        return false;
    }

    else{
        //find its index by pointer arithmetics
        int index = (find(key) - &table[0]) ;     
        
        //delete it
        table[index].deleted = true;
        numberOfItems--;
        return true;        
    }
}

template <class T>
bool HashTable<T>::contains(const std::string & key) const {
    

    if(find(key))
        return true;
    else
        return false;
}

template <class T>
const HashTableItem<T> * HashTable<T>::find(const std::string & key) const {
    

    int index = hashFunction(key);
    int checked = 0;

    while(table[index].active && table[index].key!=key){
        index++;
        if(index == tableSize){
            index = 0;
        }
        checked ++;

        if(table[index].key == key && !table[index].deleted){
            break;
        }
        if(checked > tableSize){
            return NULL;
        }
    }

    if(table[index].active && table[index].key == key && !table[index].deleted){
        return &table[index];
    }
    else{
        return NULL;
    }
}

template <class T>
int HashTable<T>::getTableSize() const {
    
    return tableSize;
}

template <class T>
int HashTable<T>::getNumberOfItems() const {
    
    return numberOfItems;
}

template <class T>
int HashTable<T>::hashFunction(const std::string & key) const {
    // Hash function that calculates the integer hash code corresponding to the given key string.
    // It maps the given key string to an integer value from 0 to (tableSize - 1).

    int h = 0;

    for (unsigned i = 0; i < key.length(); ++i) {
        h = 37 * h + key[i];
    }

    h %= tableSize;

    if (h < 0) {
        // in case overflows occurs
        h += tableSize;
    }

    return h;
}

template <class T>
void HashTable<T>::rehash() {
    // You will use these prime numbers while rehashing.
    // You will not be asked to expand your hash table further.
    const int primeNumbers[] = {2, 5, 11, 23, 47, 97, 197, 397, 797, 1597, 3203, 6421, 12853, 25717, 51437};

    // Find next size    
    int s = 0;
    while(primeNumbers[s]!=tableSize){
        s++;
    }
    int new_size = primeNumbers[s+1];

   
    //create a temporary hashtable by copying actual one
    HashTable temp_hash;
    temp_hash.table = table;
    //resize it
    temp_hash.table.resize(new_size);
    temp_hash.tableSize = new_size;

    //inactivate all the copied values, now it is a empty table
    int i = 0;
    while(i<tableSize){
        temp_hash.table[i].active = false;
        i++;
    }

    //rearrange numberofItems and insert all the items in actual one 

    temp_hash.numberOfItems = 0;

    i = 0;
    while(i<tableSize){
        if(table[i].active && !table[i].deleted){
        temp_hash.insert_nearest_free_spot(table[i].key,table[i].value);
        }
        i++;
    }

    //copy all the values in temp hashtable into our resized actual hashtable
    table.resize(new_size);
    tableSize = new_size;
    table = temp_hash.table;
}

template <class T>
void HashTable<T>::print() {
    // Prints whole hash table.

    std::cout << "HashTable (tableSize=" << tableSize << " and numberOfItems=" << numberOfItems << ") <<--" << std::endl;

    for (int i = 0; i < tableSize; ++i) {
        std::cout << table[i] << std::endl;
    }

    std::cout << "-->>" << std::endl;
}

#endif //HASHTABLE_HPP