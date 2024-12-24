#include "FlatMap.h"

FlatMap::FlatMap() : keys(nullptr), values(nullptr), capacity(0), count(0) {}

// конструктор копирования
FlatMap::FlatMap(const FlatMap& other_map) : capacity(other_map.capacity), count(other_map.count) {
    keys = new std::string[capacity];
    values = new std::string[capacity];
    for (std::size_t i = 0; i < count; i++) {
        keys[i] = other_map.keys[i];
        values[i] = other_map.values[i];
    }
}

// оператор присваивания
FlatMap& FlatMap::operator=(const FlatMap& other_map) {
    if (this != &other_map) {
        delete[] keys;
        delete[] values;
        capacity = other_map.capacity;
        count = other_map.count;
        keys = new std::string[capacity];
        values = new std::string[capacity];
        for (std::size_t i = 0; i < count; i++) {
            keys[i] = other_map.keys[i];
            values[i] = other_map.values[i];
        }
    }
    return *this;
}

FlatMap::~FlatMap() {
    delete[] keys;
    delete[] values;
}

// получить количество элементов в таблице
std::size_t FlatMap::size() const {
    return count;
}

// доступ / вставка элемента по ключу
std::string& FlatMap::operator[](const std::string& key) {
    std::size_t index = binary_search(key);
    if (index < count&& keys[index] == key) {
        return values[index];
    }
    else {
        if (count == capacity) {
            resize();
        }
        for (std::size_t i = count; i > index; --i) {
            keys[i] = keys[i - 1];
            values[i] = values[i - 1];
        }

        keys[index] = key;
        values[index] = "";
        ++count;
        return values[index];
    }
}

// возвращает true, если запись с таким ключом присутствует в таблице
bool FlatMap::contains(const std::string& key) {
    if (keys == nullptr) return false;
    std::size_t index = binary_search(key);
    return keys[index] == key && index < count;
}

// удаление элемента по ключу, возвращает количество удаленных элементов (0 или 1)
std::size_t FlatMap::erase(const std::string& key) {
    std::size_t index = binary_search(key);
    if (index < count && keys[index] == key) {
        for (std::size_t i = index; i < count - 1; ++i) {
            keys[i] = keys[i + 1];
            values[i] = values[i + 1];
        }
        --count;
        return 1;
    }
    return 0;
}

// очистка таблицы, после которой size() возвращает 0, а contains() - false на любой ключ
void FlatMap::clear() {
    delete[] keys;
    delete[] values;
    keys = nullptr;
    values = nullptr;
    count = 0;
    capacity = 0;
}
