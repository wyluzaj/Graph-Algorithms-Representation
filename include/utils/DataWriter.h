// Zmieniona wersja DataWriter z kontrolą formatu i tabulatorami
#ifndef DATAWRITER_H
#define DATAWRITER_H

#include <fstream>
#include <string>
#include <stdexcept>
#include <filesystem>
#include <iomanip>

class DataWriter {
private:
    std::ofstream out;

public:
    DataWriter(const std::string &filename) {
        bool exists = std::filesystem::exists(filename);
        bool empty = !exists || std::filesystem::file_size(filename) == 0;

        out.open(filename, std::ios::app);
        if (!out.is_open()) {
            throw std::runtime_error("Nie można otworzyć pliku: " + filename);
        }
        if (empty) {
            out << "problem algorithm size density edges count avgTimeList avgTimeMatrix\n";
        }
    }

    ~DataWriter() {
        if (out.is_open()) out.close();
    }

    void write(const std::string &problem,
               const std::string &algorithm,
               int size,
               int density,
               int edges,
               int count,
               double avgTimeList,
               double avgTimeMatrix) {
        out << problem << ' '
            << algorithm << ' '
            << size << ' '
            << density << ' '
            << edges << ' '
            << count << ' '
            << std::fixed << std::setprecision(2) << avgTimeList << ' '
            << std::fixed << std::setprecision(2) << avgTimeMatrix << '\n';
    }
};

#endif // DATAWRITER_H
