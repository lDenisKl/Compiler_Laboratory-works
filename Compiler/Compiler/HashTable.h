#pragma once

#include <iostream>
#include "HashNode.h"

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

        bufferForDeletingNode = new HashNode<K, V>("-1", "-1");
    }

    int hashCode(K key) { return key.size() % capacity; }

    void insertNode(K key, V value)
    {
        HashNode<K, V>* node = new HashNode<K, V>(key, value);

        int hashIndex = hashCode(key);

        while (table[hashIndex] != NULL && table[hashIndex]->key != key && table[hashIndex]->key != "-1") {
            hashIndex++;
            hashIndex %= capacity;
        }
        if (table[hashIndex] == NULL || table[hashIndex]->key == "-1") {
            size++;
        }
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


    void display()
    {
        for (int i = 0; i < capacity; i++) {
            if (table[i] != NULL && table[i]->key != "-1")
                std::cout << "key = " << table[i]->key
                << "  value = " << table[i]->value
                << '\n';
        }
    }
};

