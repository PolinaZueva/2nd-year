#include "PianoConverter.h"

PianoConverter::PianoConverter(uint32_t start, uint32_t end) : start(start), end(end) {}

void PianoConverter::apply(std::vector<int16_t>& samples, uint32_t sampleRate) {
    size_t startIndex = start * sampleRate;
    size_t endIndex = end * sampleRate;

    if (startIndex >= samples.size()) return;  //интервал за пределами
    if (endIndex > samples.size()) endIndex = samples.size();

    for (size_t i = startIndex; i < endIndex; ++i) {
        double baseFrequency = 440.0;  //A4 (440 Гц)
        double time = static_cast<double>(i) / sampleRate;
        const double PI = 3.14159265358979323846;
        double baseWave = sin(2 * PI * baseFrequency * time);  //синусоидальная волна для основной частоты

        //добавляем гармоники, которые определяют тембр звука
        double harmonic1 = 0.5 * sin(2 * PI * 2 * baseFrequency * time);  //вторая гармоника
        double harmonic2 = 0.25 * sin(2 * PI * 3 * baseFrequency * time); //третья гармоника

        double pianoWave = baseWave + harmonic1 + harmonic2;  //наша основная волна

        pianoWave = pianoWave / (1 + 0.5 + 0.25);  //нормализуем амплитуду, чтобы избежать искажений
        samples[i] = static_cast<int16_t>(samples[i] * pianoWave);
    }
}