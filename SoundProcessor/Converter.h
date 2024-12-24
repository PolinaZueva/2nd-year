#ifndef CONVERTER_H
#define CONVERTER_H

#include <vector>
#include <memory>
#include <string>

class Converter {
public:
    virtual ~Converter() = default;  
    virtual void apply(std::vector<int16_t>& samples, uint32_t sampleRate) = 0;
};

#endif // CONVERTER_H