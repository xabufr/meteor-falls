#include "DataChecksum.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <boost/crc.hpp>

DataChecksum::DataChecksum()
{
    //ctor
}
DataChecksum::~DataChecksum()
{
    //dtor
}
void DataChecksum::addFile(std::string p_file)
{
    m_files.push_back(p_file);
}
void DataChecksum::addFiles(std::vector<std::string> p_files)
{
    int i;
    for(i=0;i<p_files.size();i++)
        m_files.push_back(p_files[i]);
}
void DataChecksum::process()
{
    int i;
    for(i=0;m_files.size();i++){
        boost::crc_32_type result;
        std::ifstream fichier(m_files[i].c_str()); // ouvre un fichier en lecture
        if(fichier) // échoue si le fichier n'est pas ouvert
        {
            std::stringstream buffer;
            buffer << fichier.rdbuf(); // copier le contenu du fichier dans le buffer
            fichier.close();
            result.process_bytes(buffer.str().c_str(), buffer.str().size());
            m_checksums[m_files[i]]=result.checksum();
        }
    }
}
std::map<std::string, checksum> DataChecksum::getChecksums()
{
    return m_checksums;
}
