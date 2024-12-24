#include "Tuple.h"
#include "FlatMap.h"
#include "CsvParser.h"
#include <iostream>
#include <fstream>

void readFromStdin() {
    std::cout << "\n";
    std::cout << "Enter CSV data in the format <int>,<string>,<double>:\n";
    std::istream& inputStream = std::cin;

    try {
        CsvParser<int, std::string, double> parser(inputStream);
        for (const auto& r : parser) {
            std::cout << r << "\n";
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error while parsing input: " << e.what() << "\n";
    }
}

int main() {
    // Подзадача 1: Вывод tuple
	std::tuple<int, std::string, double> tuple1 = { 19, "polina", 20.05 };
	std::cout << tuple1 << "\n";

	std::tuple<int, int, int, int> tuple2 = { 6, 8, 9, 17 };
	std::cout << tuple2 << "\n";         
    std::cout << "\n";

    std::tuple<int, std::string, double, std::tuple<std::string, std::string>> t3 = { 42, "hello", 2.718, {"", ""} };
    std::cout << t3 << std::endl;

	// Подзадача 2: Вывод cvs-parser
    std::ifstream csv_stream1("test1.csv");
    std::ifstream csv_stream2("test2.csv");

    if (!csv_stream1 && !csv_stream2) {
        std::cerr << "Failed to open files!\n";
        return 1;
    }
        
    try {
        CsvParser<int, std::string, double> parser1(csv_stream1, 0);
        for (const auto& r1 : parser1) {  //const auto& - ссылка на неизменяемый объект
            std::cout << r1 << "\n";
        }

        CsvParser<int, int, std::string, int, int, double> parser2(csv_stream2, 0);
        for (const auto& r2 : parser2) {
            std::cout << r2 << "\n";
        }

    }
    catch (const std::exception& e) {
        std::cerr << "Error while parsing CSV: " << e.what() << "\n";
    }

    // Подзадача 3: FlatMap    
    FlatMap<int, std::string> map1;
    map1[7] = "Favorite number";
    std::cout << "\nFlatMap<int, std::string>:" << "\n";
    for (const auto& pair : map1) {
        std::cout << pair.first << ": " << pair.second << "\n";
    }

    FlatMap<std::string, double> map2;
    map2["Height"] = 174.1;
    std::cout << "\nFlatMap<std::string, double>:" << "\n";
    for (const auto& pair : map2) {
        std::cout << pair.first << ": " << pair.second << "\n";
    }

    readFromStdin();

	return 0;
}