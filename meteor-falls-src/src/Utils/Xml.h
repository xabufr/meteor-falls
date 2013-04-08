#include "../precompiled/_rapidxml.h"
#include "../precompiled/lexical_cast.h"
#include <boost/exception/all.hpp>
#include "Vector3D.h"
#include <string>

namespace XmlUtils
{
	Vector3D getPosition(rapidxml::xml_node<>*, const std::string& = "");
	Ogre::ColourValue getRGBA(rapidxml::xml_node<>*);
	Ogre::Quaternion getQuaternion(rapidxml::xml_node<>*);
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
