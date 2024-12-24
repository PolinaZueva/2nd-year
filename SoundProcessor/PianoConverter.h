#ifndef PIANOCONVERTER_H
#define PIANOCONVERTER_H

#include "Converter.h"

class PianoConverter : public Converter {
private:
    uint32_t start;  
    uint32_t end;    

public:
    PianoConverter(uint32_t startSec, uint32_t endSec);
    void apply(std::vector<int16_t>& samples, uint32_t sampleRate) override;
};

#endif //PIANOCONVERTER_H