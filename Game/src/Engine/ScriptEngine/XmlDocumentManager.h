#ifndef XMLDOCUMENTMANAGER_H
#define XMLDOCUMENTMANAGER_H

#include <string>
#include <map>
#include "../../Utils/singleton.h"
#include <boost/property_tree/ptree.hpp>

class XmlDocumentManager: public Singleton<XmlDocumentManager>
{
    friend class Singleton<XmlDocumentManager>;
    public:
        typedef boost::property_tree::ptree Document;

        Document& getDocument(const std::string&);

        static XmlDocumentManager* get();
		static Document& get(const std::string&);

    protected:
        XmlDocumentManager();
        virtual ~XmlDocumentManager();

    private:
        std::map<std::string, Document*> m_documents;

        Document& m_loadDocument(const std::string&);
};

#endif // XMLDOCUMENTMANAGER_H
