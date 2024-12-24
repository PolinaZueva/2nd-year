#pragma once

#ifndef FLATMAP_H
#define FLATMAP_H

#include <string>

class FlatMap {
public:

    FlatMap();

    FlatMap(const FlatMap& other_map);

    ~FlatMap();

    FlatMap& operator=(const FlatMap& other_map);


    std::size_t size() const;

    std::string& operator[](const std::string& key);

    bool contains(const std::string& key);

    std::size_t erase(const std::string& key);

    void clear();

private:
    std::string* keys;
    std::string* values;
    std::size_t capacity = 0;
    std::size_t count = 0;


    std::size_t binary_search(const std::string& key) {
        std::size_t left = 0;
        std::size_t right = count;
        while (left < right) {
            std::size_t mid = (left + right) / 2;
            if (keys[mid] < key) {
                left = mid + 1;
            }
            else {
                right = mid;
            }
        }
        return left;
    }

    void resize() {
        std::size_t new_capacity = capacity == 0 ? 1 : capacity * 2;
        std::string* new_keys = new std::string[new_capacity];
        std::string* new_values = new std::string[new_capacity];
        for (std::size_t i = 0; i < count; i++) {
            new_keys[i] = keys[i];
            new_values[i] = values[i];
        }
        delete[] keys;
        delete[] values;
        keys = new_keys;
        values = new_values;
        capacity = new_capacity;
    }
};

#endif 