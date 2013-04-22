#include "../precompiled/_rapidxml.h"
#include "../precompiled/lexical_cast.h"
#include <boost/exception/all.hpp>
#include "Vector3D.h"
#include <string>
#include <boost/property_tree/ptree.hpp>

namespace XmlUtils
{
	Vector3D getPosition(boost::property_tree::ptree const &, const std::string& = "");
	Ogre::ColourValue getRGBA(const boost::property_tree::ptree&);
	Ogre::Quaternion getQuaternion(boost::property_tree::ptree const &);
	template<class T> 
	T getValue(rapidxml::xml_base<>* element)
	{
		return boost::lexical_cast<T>(element->value());
	}
	int 		getInt 		(rapidxml::xml_base<>* base);
	float  		getFloat 	(rapidxml::xml_base<>* base);
	double  	getDouble 	(rapidxml::xml_base<>* base);
	bool 		getBool 	(rapidxml::xml_base<>* base);
}
