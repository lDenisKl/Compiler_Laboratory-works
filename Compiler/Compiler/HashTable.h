#pragma once

#include <iostream>
#include <string>
#include "HashNode.h"
#include "token.h"

template <typename K, typename V>
class HashTable {
    HashNode<K, V>** table;
    int capacity;
    int size;
    HashNode<K, V>* bufferForDeletingNode;

public:
    HashTable()
    {
        size = 0;
        capacity = 50;
        table = new HashNode<K, V>* [capacity];

        for (int i = 0; i < capacity; i++)
            table[i] = NULL;

        bufferForDeletingNode = new HashNode<K, V>("-1", token(),0);
    }

    int hashCode(K key) { 
        long sum = 0;
        for (int i = 0; i < key.size(); ++i) {
            sum += (int)key[i];
        }
        return sum % capacity; 
    }

    void insertNode(K key, V value)
    {

        int hashIndex = hashCode(key);

        while (table[hashIndex] != NULL && table[hashIndex]->key != key && table[hashIndex]->key != "-1") {
            hashIndex++;
            hashIndex %= capacity;
        }
        if (table[hashIndex] == NULL || table[hashIndex]->key == "-1") {
            size++;
        }

        HashNode<K, V>* node = new HashNode<K, V>(key, value,hashIndex);
        table[hashIndex] = node;
    }


    V deleteNode(K key)
    {
        int hashIndex = hashCode(key);

        while (table[hashIndex] != NULL) {
            if (table[hashIndex]->key == key) {
                HashNode<K, V>* currentNode = table[hashIndex];
                table[hashIndex] = bufferForDeletingNode;
                size--;
                return currentNode->value;
            }
            hashIndex++;
            hashIndex %= capacity;
        }
        return NULL;
    }

    V get(K key)
    {
        int hashIndex = hashCode(key);
        int counter = 0;

        while (table[hashIndex] != NULL) { 

            if (counter++ > capacity) 
                return NULL;

            if (table[hashIndex]->key == key)
                return table[hashIndex]->value;
            hashIndex++;
            hashIndex %= capacity;
        }

        return NULL;
    }

    int getSize() { return size; }

    bool isEmpty() { return size == 0; }


    std::string display()
    {
        std::string answer = "";
        for (int i = 0; i < capacity; i++) {
            if (table[i] != NULL && table[i]->key != "-1") {
                answer += table[i]->key;
                LexemType lt = (table[i]->value).type;
                std::string type = "";
                switch (lt) {
                case LexemType::OPERATOR: 
                    type = "OP";  
                    break;
                case LexemType::KEYWORD: 
                    type = "KW";  
                    break;
                case LexemType::CONST: 
                    type = "CONST";  
                    break;
                case LexemType::ID: 
                    type = "ID";  
                    break;
                case LexemType::SEPARATOR:
                    type = "SEP"; 
                    break;
                }
                std::string in = std::to_string(table[i]->pos);
                answer += (" | " + type + " | "+ in + " \n");
            }
        }
        return answer;
    }
};

