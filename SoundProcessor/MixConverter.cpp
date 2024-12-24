#include "MixConverter.h"
//#include <algorithm>

MixConverter::MixConverter(std::shared_ptr<WavFile> mixFile, int start, int end) : mixFile(mixFile), start(start), end(end) {}

void MixConverter::apply(std::vector<int16_t>& samples, uint32_t sampleRate) {
    int startSample = start * sampleRate;
    int endSample = end * sampleRate;

    if (startSample >= samples.size()) return;  //интервал за пределами
    if (endSample > samples.size()) endSample = samples.size();

    auto& mixSamples = mixFile->getSamples();  //извлекаем сэмплы из файла mixFile
    if (mixSamples.empty()) {
        throw std::runtime_error("Mix file contains no samples");
    }
    int maxSamples = std::min(static_cast<int>(samples.size()), startSample + static_cast<int>(mixSamples.size()));

    for (int i = startSample; i < maxSamples && i < endSample; ++i) {
        samples[i] = static_cast<int16_t>((samples[i] + mixSamples[i - startSample]) / 2);
    }
}