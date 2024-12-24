#ifndef MIXCONVERTER_H
#define MIXCONVERTER_H

#include "Converter.h"
#include "WavFile.h"

class MixConverter : public Converter {
private:
    std::shared_ptr<WavFile> mixFile; 
    int start;
    int end;

public:
    MixConverter(std::shared_ptr<WavFile> mixFile, int start, int end);
    void apply(std::vector<int16_t>& samples, uint32_t sampleRate) override;
};

#endif //MIXCONVERTER_H