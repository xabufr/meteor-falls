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
}
