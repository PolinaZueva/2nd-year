#ifndef WAVFILE_H
#define WAVFILE_H

#include <fstream>
#include <vector>
#include <string>

class WavFile {
private:
    std::string filename;
    std::vector<int16_t> samples;
    uint32_t sampleRate = 0;
    uint16_t bitsPerSample = 0;
    uint16_t numChannels = 0;

    struct WavHeader {
        char chunkID[4];        // "RIFF"
        uint32_t chunkSize;     // Общий размер файла
        char format[4];         // "WAVE"
        char subchunk1ID[4];    // "fmt"
        uint32_t subchunk1Size; // Размер субчанка
        uint16_t audioFormat;   // Формат аудио (1 для PCM)
        uint16_t numChannels;   // Количество каналов 
        uint32_t sampleRate;    // Частота дискретизации
        uint32_t byteRate;      // Байтовая скорость (sampleRate * numChannels * bitsPerSample / 8)
        uint16_t blockAlign;    // Выравнивание блока (numChannels * bitsPerSample / 8)
        uint16_t bitsPerSample; // Разрядность (16 бит)
        char subchunk2ID[4];    // "data"
        uint32_t subchunk2Size; // Размер данных
    };     

public:
    WavFile() = default;
    explicit WavFile(const std::string& file);
    void findDataChunk(std::ifstream& file, WavHeader& header);
    WavHeader prepareHeader() const;
    double getDurationInSeconds() const;
    bool readFile();
    bool writeFile(const std::string& outputFilename);
    void setSamples(const std::vector<int16_t>& newSamples);
    const std::vector<int16_t>& getSamples() const;
    uint32_t getSampleRate() const;
    uint16_t getBitsPerSample() const;
    uint16_t getNumChannels() const;
};

#endif // WAVFILE_H
