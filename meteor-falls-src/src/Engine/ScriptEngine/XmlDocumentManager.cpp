#include "XmlDocumentManager.h"
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/json_parser.hpp>

XmlDocumentManager::XmlDocumentManager()
{
}
XmlDocumentManager::~XmlDocumentManager()
{
	for(std::pair<std::string, Document*> doc : m_documents)
		delete doc.second;
}
XmlDocumentManager::Document& XmlDocumentManager::getDocument(const std::string& path)
{
    auto it = m_documents.find(path);
    if(it == m_documents.end())
        return m_loadDocument(path);
    return *it->second;
}
XmlDocumentManager::Document& XmlDocumentManager::m_loadDocument(const std::string& path)
{
	Document *doc = new Document();
	try { //On tente de charger en XML
		boost::property_tree::read_xml(path, *doc);
	} catch (boost::property_tree::xml_parser_error& error) {
		try { // Si ça ne fonctionne pas, c'est peu-être du JSON
			boost::property_tree::read_json(path, *doc);
		} catch (boost::property_tree::json_parser_error& error) {
			delete doc;
			throw;
		}
	}
	m_documents.insert(std::pair<std::string, Document*>(path, doc));
    return *doc;
}
XmlDocumentManager* XmlDocumentManager::get()
{
    return Singleton<XmlDocumentManager>::get();
}
XmlDocumentManager::Document& XmlDocumentManager::get(const std::string& path)
{
	return get()->getDocument(path);
}
