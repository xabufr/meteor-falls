#ifndef DATACHECKSUM_H
#define DATACHECKSUM_H

#include <string>
#include <vector>
#include <map>

typedef int checksum;

class DataChecksum
{
    public:
        DataChecksum();
        virtual ~DataChecksum();
        void addFile(std::string p_file);
        void addFiles(std::vector<std::string> p_files);
        void process();
        std::map<std::string, checksum> getChecksums();

    protected:

    private:
        std::vector<std::string> m_files;
        std::map<std::string, checksum> m_checksums;
};

#endif // DATACHECKSUM_H
