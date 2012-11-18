#ifndef XMLDOCUMENTMANAGER_H
#define XMLDOCUMENTMANAGER_H

#include <string>
#include <map>
#include <rapidxml.hpp>
#include "Utils/singleton.h"

class XmlDocumentManager: public Singleton<XmlDocumentManager>
{
    public:
        typedef std::pair<char*, rapidxml::xml_document<>*> Document;

        rapidxml::xml_document<>* getDocument(const std::string&);

    protected:
        XmlDocumentManager();
        virtual ~XmlDocumentManager();

    private:
        std::map<std::string, Document> m_documents;

        Document m_loadDocument(const std::string&);
};

#endif // XMLDOCUMENTMANAGER_H
