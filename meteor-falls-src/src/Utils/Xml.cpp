#include "Xml.h"
#include <OgreColourValue.h>
namespace XmlUtils
{
	Vector3D getPosition(boost::property_tree::ptree const & tree, const std::string& prefixe)
	{
		Vector3D position;
		position.x = tree.get(prefixe+"x", 0.f);
		position.y = tree.get(prefixe+"y", 0.f);
		position.z = tree.get(prefixe+"z", 0.f);
		return position;
	}
	Ogre::ColourValue getRGBA(const boost::property_tree::ptree& tree)
	{
		Ogre::ColourValue color;
		color.r = tree.get<double>("r");
		color.g = tree.get<double>("g");
		color.b = tree.get<double>("b");
		color.a = tree.get<double>("a");
		return color;
	}
	Ogre::Quaternion getQuaternion(boost::property_tree::ptree const & tree)
	{
		Ogre::Quaternion q;
		Vector3D vec(getPosition(tree, "q"));
		q.x = vec.x;
		q.y = vec.y;
		q.z = vec.z;
		q.w = tree.get("qw", 0.f);
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
