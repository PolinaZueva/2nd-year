#include "WavFile.h"
#include <fstream>
#include <iostream>

WavFile::WavFile(const std::string& file) : filename(file) {}

void WavFile::findDataChunk(std::ifstream& file, WavHeader& header) {  //ищем размер аудиоданных
    file.seekg(36, std::ios::beg);  //перемещаем указатель чтения на 36-й байт от начала файла
    char chunkID[4];
    uint32_t chunkSize;
    while (file.read(chunkID, 4)) {
        file.read(reinterpret_cast<char*>(&chunkSize), sizeof(chunkSize));
        if (std::string(chunkID, 4) == "data") {
            header.subchunk2Size = chunkSize;
            return;
        }
        file.seekg(chunkSize, std::ios::cur);
    }
    throw std::runtime_error("Data chunk not found in file");
}

WavFile::WavHeader WavFile::prepareHeader() const {
    WavHeader header = {};  //инициализируем пустыми значениями 
    std::memcpy(header.chunkID, "RIFF", 4);  //копируем 4 байта из строки "RIFF" в массив header.chunkID
    std::memcpy(header.format, "WAVE", 4);
    std::memcpy(header.subchunk1ID, "fmt ", 4);
    std::memcpy(header.subchunk2ID, "data", 4);

    header.subchunk1Size = 16;
    header.audioFormat = 1;
    header.numChannels = numChannels;
    header.sampleRate = sampleRate;
    header.bitsPerSample = bitsPerSample;
    header.byteRate = sampleRate * numChannels * (bitsPerSample / 8);
    header.blockAlign = numChannels * (bitsPerSample / 8);
    header.subchunk2Size = samples.size() * sizeof(int16_t);
    header.chunkSize = 4 + (8 + header.subchunk1Size) + (8 + header.subchunk2Size);

    return header;
}

double WavFile::getDurationInSeconds() const {
    if (sampleRate == 0) return 0.0;
    return static_cast<double>(samples.size()) / sampleRate;
}

bool WavFile::readFile() {
    std::ifstream inputFile(filename, std::ios::binary);
    if (!inputFile) {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    WavHeader header;  //создаем объект header типа WavHeader
    inputFile.read(reinterpret_cast<char*>(&header), sizeof(header));  //преобразовываем адрес header в указатель на char*, так как функция read принимает указатель на массив байт

    if (!inputFile || std::string(header.chunkID, 4) != "RIFF") {
        throw std::runtime_error("Invalid WAV header in file: " + filename);
    }

    if (header.audioFormat != 1 || header.bitsPerSample != 16 || header.numChannels != 1) {
        throw std::runtime_error("Unsupported WAV format in file: " + filename);
    }

    findDataChunk(inputFile, header);
    samples.resize(header.subchunk2Size / sizeof(int16_t));  //выделяем память вектора кол-во сэмплов
    inputFile.read(reinterpret_cast<char*>(samples.data()), header.subchunk2Size);

    if (!inputFile) {
        throw std::runtime_error("Error reading samples from file: " + filename);
    }

    sampleRate = header.sampleRate;
    numChannels = header.numChannels;
    bitsPerSample = header.bitsPerSample;

    return true;
}

bool WavFile::writeFile(const std::string& outputFilename) {
    if (samples.empty()) {  //samples пуст?
        throw std::runtime_error("No audio samples to write.");
    }
    if (sampleRate == 0 || bitsPerSample == 0 || numChannels == 0) {
        throw std::runtime_error("Invalid WAV parameters.");
    }

    std::ofstream outFile(outputFilename, std::ios::binary);
    if (!outFile) {
        throw std::runtime_error("Cannot open file: " + outputFilename);
    }

    WavHeader header = prepareHeader();

    outFile.write(reinterpret_cast<const char*>(&header), sizeof(header));
    if (!outFile) {
        throw std::runtime_error("Error writing WAV header to file: " + outputFilename);
    }

    outFile.write(reinterpret_cast<const char*>(samples.data()), samples.size() * sizeof(int16_t));
    if (!outFile) {
        throw std::runtime_error("Error writing samples to file: " + outputFilename);
    }

    return true;
}

void WavFile::setSamples(const std::vector<int16_t>& newSamples) {
    samples = newSamples;
}

const std::vector<int16_t>& WavFile::getSamples() const { return samples; }

uint32_t WavFile::getSampleRate() const { return sampleRate; }

uint16_t WavFile::getBitsPerSample() const { return bitsPerSample; }

uint16_t WavFile::getNumChannels() const { return numChannels; }



    

    
