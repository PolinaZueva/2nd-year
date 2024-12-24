#ifndef CONVERTERFACTORY_H
#define CONVERTERFACTORY_H

#include "Converter.h"
#include "WavFile.h"

class ConverterFactory {
public:
    static std::unique_ptr<Converter> createConverter(const std::string& command, WavFile& file, const std::vector<std::string>& args);
};

#endif //CONVERTERFACTORY_H