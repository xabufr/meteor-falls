#ifndef XMLDOCUMENTMANAGER_H
#define XMLDOCUMENTMANAGER_H

#include <string>
#include <map>
#include "precompiled/_rapidxml.h"
#include "../../Utils/singleton.h"

class XmlDocumentManager: public Singleton<XmlDocumentManager>
{
    friend class Singleton<XmlDocumentManager>;
    public:
        typedef std::pair<char*, rapidxml::xml_document<>*> Document;

        rapidxml::xml_document<>* getDocument(const std::string&);

        static XmlDocumentManager* get();

    protected:
        XmlDocumentManager();
        virtual ~XmlDocumentManager();

    private:
        std::map<std::string, Document> m_documents;

        Document m_loadDocument(const std::string&);
};

#endif // XMLDOCUMENTMANAGER_H
