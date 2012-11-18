#include "XmlDocumentManager.h"
#include "Utils/Exception/FileNotFound.h"
#include <fstream>

XmlDocumentManager::XmlDocumentManager()
{
    //ctor
}

XmlDocumentManager::~XmlDocumentManager()
{
    for(auto it : m_documents)
    {
        delete it.second.first;
        delete it.second.second;
    }
}
rapidxml::xml_document<>* XmlDocumentManager::getDocument(const std::string& path)
{
    auto it = m_documents.find(path);
    if(it == m_documents.end())
        return m_loadDocument(path).second;
    return it->second.second;
}
XmlDocumentManager::Document XmlDocumentManager::m_loadDocument(const std::string& path)
{
    std::ifstream file;
    file.open(path);
    if(!file)
        throw FileNotFound(path);
    file.seekg(0, std::ios_base::end);
    const int length = file.tellg();
    char *buffer = new char[length+1];
    file.seekg(0, std::ios_base::beg);
    file.read(buffer, length);
    buffer[length]=0;

    rapidxml::xml_document<> *xml = new rapidxml::xml_document<>();
    xml->parse<0>(buffer);

    Document doc;
    doc.first = buffer;
    doc.second = xml;

    m_documents[path] = doc;

    return doc;
}
