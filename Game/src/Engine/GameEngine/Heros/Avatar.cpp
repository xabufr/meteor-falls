#include "Avatar.h"
#include "ClasseHero.h"
#include "../../EngineMessage/EngineMessage.h"

Avatar::Avatar(int id, ClasseHero* cl): m_id(id), m_classe(cl), m_isDefault(false)
{

}
const std::string& Avatar::nom() const
{
    return m_nom;
}
int Avatar::id() const
{
    return m_id;
}
ClasseHero* Avatar::classe() const
{
    return m_classe;
}
bool Avatar::isDefault() const
{
    return m_isDefault;
}
void Avatar::serialize(EngineMessage* mes) const
{
    mes->ints[mf::EngineMessageKey::AVATAR_ID] = m_id;
    mes->strings[mf::EngineMessageKey::AVATAR_NAME] = m_nom;
    mes->ints[mf::EngineMessageKey::CLASS_ID] = m_classe->id();
    mes->ints[mf::EngineMessageKey::AVATAR_DEFAULT] = static_cast<int>(m_isDefault);
}
bool Avatar::loadFrom(EngineMessage* mes)
{
    m_isDefault = static_cast<bool>(mes->ints[mf::EngineMessageKey::AVATAR_DEFAULT]);
    m_nom       = mes->strings[mf::EngineMessageKey::AVATAR_NAME];
    m_id        = mes->ints[mf::EngineMessageKey::AVATAR_ID];
    return true;
}
