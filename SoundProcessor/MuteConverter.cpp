#include "MuteConverter.h"

MuteConverter::MuteConverter(uint32_t start, uint32_t end) : start(start), end(end) {}

void MuteConverter::apply(std::vector<int16_t>& samples, uint32_t sampleRate) {
    //преобразуем секунды в индексы сэмплов
    size_t startIndex = start * sampleRate;  //sampleRate указывает, сколько сэмплов приходится на одну секунду
    size_t endIndex = end * sampleRate;
    
    if (startIndex >= samples.size()) return; //интервал за пределами
    if (endIndex > samples.size()) endIndex = samples.size();

    //заглушаем сэмплы в указанном интервале
    for (size_t i = startIndex; i < endIndex; ++i) {
        samples[i] = 0;
    }
}