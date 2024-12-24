#include "CommandProcessor.h"
#include "ConverterFactory.h"
#include <iostream>
#include <fstream>
#include <sstream>

void CommandProcessor::processCommands(const std::string& commandFile, WavFile& outputWAV, const std::map<std::string, WavFile>& inputFiles) {
    std::ifstream file(commandFile);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open command file: " + commandFile);
    }

    std::string line;
    while (std::getline(file, line)) {  //считываем файл построчно
        if (line.empty() || line[0] == '#') continue;  //если пустая или комментарий

        //парсинг команды
        std::istringstream iss(line);  //строка line в поток
        std::string command; 
        iss >> command;  //извлекаем первое слово в command

        std::vector<std::string> args;  //будем хранить аргументы команды
        std::string arg;
        while (iss >> arg) {  //оператор ввода для последовательного извлечения аргументов из потока iss
            if (arg[0] == '$') {
                int fileIndex = std::stoi(arg.substr(1));  //берем подстроку аргумента arg, начиная со второго символа
                if (fileIndex < 1 || fileIndex > inputFiles.size()) {
                    throw std::invalid_argument("Invalid file reference: " + arg);
                }
                arg = std::next(inputFiles.begin(), fileIndex - 1)->first;
            }
            args.push_back(arg);
        }                

        auto converter = ConverterFactory::createConverter(command, outputWAV, args);
        auto samples = outputWAV.getSamples();
        converter->apply(samples, outputWAV.getSampleRate());
        outputWAV.setSamples(samples);
    }

    file.close();
}