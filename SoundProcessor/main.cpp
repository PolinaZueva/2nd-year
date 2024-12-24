#include "CommandProcessor.h"
#include <iostream>
#include <fstream>

int main(int argc, char* argv[]) {
    if (argc < 4) {
        std::cerr << "Usage: " << argv[0] << " <output.wav> <commands.txt> <input1.wav> [input2.wav ...]" << std::endl;
        return -1;
    }

    std::string outputFilename = argv[1];
    std::string commandFilename = argv[2];

    //список входных файлов
    std::map<std::string, WavFile> inputFiles;
    for (int i = 3; i < argc; ++i) {
        std::string inputFilename = argv[i];
        try {
            WavFile wav(inputFilename);
            wav.readFile();
            inputFiles[inputFilename] = std::move(wav);
        }
        catch (const std::exception& e) {
            std::cerr << "Error reading input file " << inputFilename << ": " << e.what() << std::endl;
            return -1;
        }
    }

    if (inputFiles.empty()) {
        std::cerr << "No input files provided" << std::endl;
        return -1;
    }

    WavFile outputWav = inputFiles.begin()->second;

    //обрабатываем команды из файла
    try {
        CommandProcessor processor;
        processor.processCommands(commandFilename, outputWav, inputFiles);
    }
    catch (const std::exception& e) {
        std::cerr << "Error processing commands: " << e.what() << std::endl;
        return -1;
    }

    //сохраняем выходной файл
    try {
        outputWav.writeFile(outputFilename);
        std::cout << "Output saved to " << outputFilename << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error saving output file: " << e.what() << std::endl;
        return -1;
    }

    return 0;
}