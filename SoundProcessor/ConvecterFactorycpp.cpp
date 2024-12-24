#include "ConverterFactory.h"
#include "MuteConverter.h"
#include "MixConverter.h"
#include "PianoConverter.h"
#include <iostream>

std::unique_ptr<Converter> ConverterFactory::createConverter(const std::string& command, WavFile& file, const std::vector<std::string>& args) {
    double maxDuration = file.getDurationInSeconds();

    if (command == "mute") {
        if (args.size() < 2) {
            throw std::invalid_argument("Mute command requires start and end times");
        }

        int start = std::stoi(args[0]); //преобразуем из строки в число
        int end = std::stoi(args[1]);
        if (start >= end) {
            throw std::invalid_argument("Start time must be less than end time");
        }
        
        if (start >= maxDuration || end > maxDuration) {
            throw std::out_of_range("Mute command time range exceeds file duration");
        }

        return std::make_unique<MuteConverter>(start, end);
    }
    else if (command == "mix") {
        if (args.size() < 3) {
            throw std::invalid_argument("Mix command requires a file, start time and end time");
        }

        std::string mixFilename = args[0];
        int start = std::stoi(args[1]);
        int end = std::stoi(args[2]);

        if (start >= end) {
            throw std::invalid_argument("Start time must be less than end time");
        }

        if (start >= maxDuration || end > maxDuration) {
            throw std::out_of_range("Mix command time range exceeds file duration");
        }

        auto mixFile = std::make_shared<WavFile>(mixFilename);
        mixFile->readFile();
        return std::make_unique<MixConverter>(mixFile, start, end);
    }
    else if (command == "piano") {
        if (args.size() < 2) {
            throw std::invalid_argument("Piano command requires start and end times");
        }

        int start = std::stoi(args[0]);
        int end = std::stoi(args[1]);
        if (start >= end) {
            throw std::invalid_argument("Start time must be less than end time");
        }

        if (start >= maxDuration || end > maxDuration) {
            throw std::out_of_range("Piano command time range exceeds file duration");
        }

        return std::make_unique<PianoConverter>(start, end);
    }
    else {
        throw std::invalid_argument("Unknown command: " + command);
    }
}