#pragma once

#ifndef CSVPARSER_H
#define CSVPARSER_H

#include <iostream>
#include <sstream>
#include <limits>
#include <tuple>
#include <string>
#include <vector>
#include <stdexcept>

template <typename... Args>
class CsvIterator;

template<typename... Args>
class CsvParser {
    std::istream& inputStream;  //поток для чтения данных из csv-файла
    unsigned skipLines;  //кол-во строк для пропуска

public:
    explicit CsvParser(std::istream& inputStream, unsigned skipLines = 0) : inputStream(inputStream), skipLines(skipLines) {
        for (unsigned i = 0; i < skipLines && inputStream.good(); ++i) {
            std::string temp;
            std::getline(inputStream, temp);
        }
    }

    CsvIterator<Args...> begin() {
        return CsvIterator<Args...>(inputStream);
    }

    CsvIterator<Args...>end() {
        return CsvIterator<Args...>();
    }
};

template<typename... Args>
class CsvIterator {
    std::istream* inputStream;  
    std::string currentLine;  //текущая строка из файла
    std::tuple<Args...> currentTuple;  //текущий кортеж
    bool end;  //флаг окончания итерации

    class Parsing {
    public:   
        template <typename Tuple, unsigned Index>
        static void parseElementTuple(std::istringstream& inputStream, Tuple&) {
            if (!inputStream.eof() && inputStream.peek() != '\n')
                throw std::runtime_error("Too many elements");
        }

        //парсим строку в кортеж
        template <typename... Args>
        static std::tuple<Args...>parseLineTuple(const std::string& inputLines) {  
            std::istringstream inputStream(inputLines);
            std::tuple<Args...> result;
            parseElementTuple<std::tuple<Args...>, 0, Args...>(inputStream, result);
            return result;
        }

        //парсим элемент кортежа
        template <typename Tuple, unsigned Index, typename T>
        static void parseCurElementTuple(std::istringstream& inputStream, Tuple& result, T& value) {
            std::string timeres;
            std::getline(inputStream, timeres, ',');

            if (timeres.empty()) {
                throw std::runtime_error("Failed");
            }

            std::istringstream timeresStream(timeres);
            timeresStream >> value;            

            if (timeresStream.fail() || !timeresStream.eof()) { 
                throw std::runtime_error("Failed");
            }
        }
        //парсим строки кортежа
        template <typename Tuple, unsigned Index, typename T>
        static void parseCurElementTuple(std::istringstream& inputStream, Tuple& result, std::string& value) {
            std::getline(inputStream, value, ',');
            if (value.empty()) {
                throw std::runtime_error("Failed");
            }
            if (std::all_of(value.begin(), value.end(), ::isdigit)) {
                throw std::runtime_error("Failed");
            }
        }      

        template <typename Tuple, unsigned Index, typename T, typename... Rec>
        static void parseElementTuple(std::istringstream& inputStream, Tuple& result) {
            parseCurElementTuple<Tuple, Index, T>(inputStream, result, std::get<Index>(result));
            parseElementTuple<Tuple, Index + 1, Rec...>(inputStream, result);
        }
};

public:
    CsvIterator() : inputStream(nullptr), end(true) {}

    explicit CsvIterator(std::istream& inputStream) : inputStream(&inputStream), end(false) {
        ++(*this);  //итератор пропускает начальное состояние и подготавливается к работе с первой строкой
    }

    //читаем следующую строку из файла и преобразуем её в кортеж
    CsvIterator& operator++() {
        if (std::getline(*inputStream, currentLine)) {  //считываем одну строку из потока и сохраняем в currentLine
            try {
                currentTuple = Parsing::template parseLineTuple<Args...>(currentLine);  //парсим строку и преобразуем ее в std::tuple
            }
            catch (const std::exception& e) {  //если не соответствует числу типов в Args...
                end = true;  //конец файла
                throw std::runtime_error("Failed");
            }
        }
        else {
            end = true;
        }
        return *this;
    }

    std::tuple<Args...>operator*() const { 
        return currentTuple; 
    }

    //сравниваем итераторы по флагу
    bool operator!=(const CsvIterator& iter) const {
        return end != iter.end;
    }
};
#endif CSVPARSER_H
