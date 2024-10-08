#pragma once


template <typename K, typename V>
class HashNode {
public:
    V value;
    K key;

    HashNode(K key, V value)
    {
        this->value = value;
        this->key = key;
    }
};