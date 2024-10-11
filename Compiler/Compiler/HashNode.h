#pragma once


template <typename K, typename V>
class HashNode {
public:
    V value;
    K key;
    int pos;

    HashNode(K key, V value,int pos)
    {
        this->value = value;
        this->key = key;
        this->pos = pos;
    }
};