#include "Xml.h"
#include <OgreColourValue.h>
namespace XmlUtils
{
	Vector3D getPosition(rapidxml::xml_node<>* node, const std::string& prefixe)
	{
		Vector3D position;
		position.x = getDouble(node->first_attribute((prefixe+"x").c_str()));
		position.y = getDouble(node->first_attribute((prefixe+"x").c_str()));
		position.z = getDouble(node->first_attribute((prefixe+"x").c_str()));
		return position;
	}
	Ogre::ColourValue getRGBA(rapidxml::xml_node<>* node)
	{
		Ogre::ColourValue color;
		color.r = getDouble(node->first_attribute("r"));
		color.g = getDouble(node->first_attribute("g"));
		color.b = getDouble(node->first_attribute("b"));
		color.a = getDouble(node->first_attribute("a"));
		return color;
	}
	Ogre::Quaternion getQuaternion(rapidxml::xml_node<>* node)
	{
		Ogre::Quaternion q;
		Vector3D vec(getPosition(node, "q"));
		q.x = vec.x;
		q.y = vec.y;
		q.z = vec.z;
		q.w = getDouble(node->first_attribute("qw"));
		return q;
	}
	int 		getInt 		(rapidxml::xml_base<>* base)
	{
		return getValue<int>(base);
	}
	float  		getFloat 	(rapidxml::xml_base<>* base)
	{
		return getValue<float>(base);
	}
	double  	getDouble 	(rapidxml::xml_base<>* base)
	{
		return getValue<double>(base);
	}
	bool 		getBool 	(rapidxml::xml_base<>* base)
	{
		std::string value(base->value());
		if(value=="true"||value=="TRUE")
			return true;
		else if(value=="false"||value=="FALSE") 
		{
			return false;
		}
		return getValue<bool>(base);
	}
}
