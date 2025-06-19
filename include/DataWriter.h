#ifndef AIZO_GRAFS_DATAWRITER_H
#define AIZO_GRAFS_DATAWRITER_H

#include <fstream>
#include <string>

//write results
class DataWriter {

public:
    DataWriter(const std::string &filename) {
        out.open(filename);
        if (!out.is_open()) {
            throw std::runtime_error("Can't open file: " + filename);
        }
        //header
        out << "problem\talgorithm\tsize\tdensity\tedges\tcount\tavgTime\n";
    }
    ~DataWriter() {
        if (out.is_open()) out.close();
    }
    void write(const std::string &problem,
               const std::string &algo,
               int size, double density,
               int edges, int count,
               double avgTime)
    {
        out << problem << '\t'
            << algo    << '\t'
            << size    << '\t'
            << density << '\t'
            << edges   << '\t'
            << count   << '\t'
            << avgTime << '\n';
    }
private:
    std::ofstream out;
};


#endif //AIZO_GRAFS_DATAWRITER_H
