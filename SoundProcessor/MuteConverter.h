#ifndef MUTECONVERTER_H
#define MUTECONVERTER_H

#include "Converter.h"

class MuteConverter : public Converter {
private:
    uint32_t start; 
    uint32_t end;   

public:
    MuteConverter(uint32_t startSec, uint32_t endSec);
    void apply(std::vector<int16_t>& samples, uint32_t sampleRate) override;
};

#endif //MUTECONVERTER_H