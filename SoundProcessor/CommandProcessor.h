#ifndef COMMANDPROCESSOR_H
#define COMMANDPROCESSOR_H

#include "WavFile.h"
#include <map>

//обрабатывает команды из текстового файла и применяет их к выходному WAV-файлу
class CommandProcessor {  
public:
    void processCommands(const std::string& commandFile, WavFile& outputWAV, const std::map<std::string, WavFile>& inputFiles);
};

#endif //COMMANDPROCESSOR_H