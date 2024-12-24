#pragma once

#ifndef FLATMAP_H
#define FLATMAP_H

#include <vector>
#include <algorithm>

template <class Key, class Value>
class FlatMap {
public:
    FlatMap() = default;
    FlatMap(const FlatMap& other_map) : keys(other_map.keys), values(other_map.values) {}
    ~FlatMap() = default;

    //оператор присваивания
    FlatMap& operator=(const FlatMap& other_map) {
        if (this != &other_map) {
            keys = other_map.keys;
            values = other_map.values;
        }
        return *this;
    }

    //получить количество элементов в таблице
    std::size_t size() const {
        return keys.size();
    }

    //доступ / вставка элемента по ключу
    Value& operator[](const Key& key) {
        auto it = std::lower_bound(keys.begin(), keys.end(), key);
        if (it != keys.end() && *it == key) {
            return values[std::distance(keys.begin(), it)];
        }
        else {
            std::size_t index = std::distance(keys.begin(), it);
            keys.insert(it, key);
            values.insert(values.begin() + index, Value{});
            return values[index];
        }
    }

    //возвращает true, если запись с таким ключом присутствует в таблице
    bool contains(const Key& key) const {
        return std::binary_search(keys.begin(), keys.end(), key);
    }

    //удаление элемента по ключу, возвращает количество удаленных элементов (0 или 1)
    std::size_t erase(const Key& key) {
        auto it = std::lower_bound(keys.begin(), keys.end(), key);
        if (it != keys.end() && *it == key) {
            std::size_t index = std::distance(keys.begin(), it);
            keys.erase(it);
            values.erase(values.begin() + index);
            return 1;
        }
        return 0;
    }

    //очистка таблицы
    void clear() {
        keys.clear();
        values.clear();
    }

    class Iterator {
    public:
        Iterator(typename std::vector<Key>::iterator k_it, typename std::vector<Value>::iterator v_it)
            : key_it(k_it), value_it(v_it) {
        }

        std::pair<Key, Value> operator*() const {
            return { *key_it, *value_it };
        }

        Key& first() {
            return *key_it;
        }

        Value& second() {
            return *value_it;
        }

        Iterator& operator++() {
            ++key_it;
            ++value_it;
            return *this;
        }

        Iterator operator++(int) {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

        bool operator==(const Iterator& other) const {
            return key_it == other.key_it;
        }

        bool operator!=(const Iterator& other) const {
            return key_it != other.key_it;
        }

    private:
        typename std::vector<Key>::iterator key_it;
        typename std::vector<Value>::iterator value_it;
    };

    // Получить итератор на первый элемент
    Iterator begin() {
        return Iterator(keys.begin(), values.begin());
    }

    // Получить итератор на элемент, следующий за последним
    Iterator end() {
        return Iterator(keys.end(), values.end());
    }

    // Получить итератор на элемент по ключу, или на end(), если ключ не найден
    Iterator find(const Key& key) {
        auto it = std::lower_bound(keys.begin(), keys.end(), key);
        if (it != keys.end() && *it == key) {
            return Iterator(it, values.begin() + std::distance(keys.begin(), it));
        }
        return end();
    }

private:
    std::vector<Key> keys;
    std::vector<Value> values;
};

#endif FLATMAP_H



